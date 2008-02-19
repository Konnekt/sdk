#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500

#include <Stamina/Stamina.h>

#include <stdlib.h>

#include "plug_export.h"
#include "core_tables.h"
#include "core_message.h"
#include "core_assert.h"
#include "core_tools.h"

using namespace Konnekt;
using namespace Stamina;
using namespace Tables;

namespace Konnekt {
  const char* Message::extAddInfo = "AddInfo";
  const char* Message::extDisplay = "Display";
  const char* Message::extTitle   = "Title";
  const char* Message::extNoSound = "NoSound"; ///< Nie zostanie odegrany dŸwiêk
  const char* Message::extFile_Path = "FilePath";
  const char* Message::extFile_Size = "FileSize";
  const char* Message::extFile_Transfer_Time = "FileTransferTime";
  const char* Message::extFile_Transfered = "FileTransfered";
  const char* Message::extFile_Error = "FileError";


  // Message --------------------------------------------------

  Message::Message(const Message& msg) {
    *this = msg;
  }

  Message& Message::operator = (const Message& msg) {
    _id = msg._id;
    _net = msg._net;
    _type = msg._type;
    setFromUid(msg.getFromUid());
    setToUid(msg.getToUid());
    setBody(msg.getBody());
    setExt(msg.getExt());
    _flag = msg._flag;
    _action = msg._action;
    _notify = msg._notify;
    _time = msg._time;

    return *this;
  }

  /** 
   * Wczytuje wiadomoœæ z kolejki.
   */
  bool Message::loadFromQueue(unsigned int msgId) {
    oTable t (tableMessages);

    tRowId row = t->getRowPos(msgId);
    if (row == rowNotFound) return false;

    TableLocker(t, row);

    _id = msgId;
    setNet( (Net::tNet) t->getInt(row, Message::colNet) );
    setType( (Message::enType) t->getInt(row, Message::colType) );
    setFromUid( t->getString(row, Message::colFromUid) );
    setToUid( t->getString(row, Message::colToUid) );
    setBody( t->getString(row, Message::colBody) );
    setExt( t->getString(row, Message::colExt) );
    setFlags( (Message::enFlags) t->getInt(row, Message::colFlag) );
    setAction( sUIAction( t->getInt(row, Message::colActionP), t->getInt(row, Message::colActionI) ) );
    setNotify( t->getInt(row, Message::colNotify) );
    setTime( t->getInt64(row, Message::colTime) );

    return true;
  }

  /** 
   * Aktualizuje wiadomoœæ w kolejce.
   *
   * @warning Tylko dla wiadomoœci które ju¿ istniej¹ w kolejce!
   */
  bool Message::saveToQueue() {
    oTable t (tableMessages);
  
    tRowId row = t->getRowPos(getId());
    if (row == rowNotFound) return false;

    TableLocker(t, row);

    t->setInt(row, Message::colNet, getNet());
    t->setInt(row, Message::colType, getType());
    t->setString(row, Message::colFromUid, getFromUid());
    t->setString(row, Message::colToUid, getToUid());
    t->setString(row, Message::colBody, getBody());
    t->setString(row, Message::colExt, getExt());
    t->setInt(row, Message::colFlag, getFlags());
    t->setInt(row, Message::colActionP, _action.parent);
    t->setInt(row, Message::colActionI, _action.id);
    t->setInt(row, Message::colNotify, getNotify());
    t->setInt64(row, Message::colTime, getTime());

    return true;
  }

  /** 
   * Dodaje wiadomoœæ do kolejki.
   *
   * @return ID wiadomosci
   */
  unsigned int Message::addToQueue(bool runQueue, Controler* ctrl) {
    if (!ctrl) ctrl = Ctrl;
    Message::IM im (Message::IM::imcNewMessage, Net::core, imtCore, this);
    int result = ctrl->IMessage(&im);
    if (runQueue && result) {
      this->runQueue(ctrl);
    }
    return result;
  }

  /** 
   * Próbuje przyj¹æ / rozes³aæ t¹ wiadomoœæ.
   */
  void Message::runQueue(Controler* ctrl) {
    if (!ctrl) ctrl = Ctrl;
    MessageSelect ms;
    ms.id = this->_id;
    ms.runQueue(ctrl);
  }

  /** 
   * Usuwa wiadomoœæ z kolejki
   */
  void Message::removeFromQueue() {
    MessageSelect ms;
    ms.id = this->_id;
    ms.removeFromQueue(1);
  }

  /** 
   * Oznacza wiadomoœæ jako przetworzon¹.
   *
   * Po skoñczeniu przetwarzania wiadomoœci, na któr¹ odpowiedzieliœmy flag¹ IM_MSG_processing wysy³amy ten komunikat, by rdzeñ "odznaczy³" nasz¹ wiadomoœæ. 
   * #IMC_MESSAGEPROCESSED wysy³a siê tylko, gdy wiadomoœæ nie zosta³a od razu usuniêta.
   */
  void Message::setAsProcessed(bool setAsRemoved) {
    Message::IM im (Message::IM::imcSetProcessed, Net::core, imtCore, this, setAsRemoved);
    Ctrl->IMessage(&im);
  }

  bool Message::isBeingProcessed() const {
    return getProcessingChainPos() > 0;
  }

  unsigned int Message::getProcessingChainPos() const {
    if (!getId()) {
      return 0;
    }
    return getDTInt(tableMessages, getId(), colProcessing);
  }


  // -- MessageSelect ----------------------------------------------

  /** 
   * Sprawdza kolejkê wiadomoœci.
   * Próbuje przyj¹æ/rozes³aæ oczekuj¹ce wiadomoœci wg. podanych kryteriów.
   */
  void MessageSelect::runQueue(Controler* ctrl) {
    if (!ctrl) ctrl = Ctrl;
    MessageSelect::IM im (MessageSelect::IM::imcMessageQueue, this);
    ctrl->IMessage(&im);
  }

  /** 
   * Podaje ile wiadomoœci oczekuje w kolejce
   */
  int MessageSelect::getCount() {
    MessageSelect::IM im (MessageSelect::IM::imcMessageWaiting, this);
    return Ctrl->IMessage(&im);
  }

  /** 
   * Usuwa wybrane wiadomoœci 
   */
  int MessageSelect::removeFromQueue(unsigned int limit) {
    MessageSelect::IM im (MessageSelect::IM::imcMessageRemove, this, limit);
    return Ctrl->IMessage(&im);
  }

  bool MessageSelect::getMessage(Message& msg) {
    MessageSelect::IM im (MessageSelect::IM::imcMessageGet, this, (int)&msg);
    return Ctrl->IMessage(&im) != 0;
  }


  // -- MessageAck

  void MessageAck::broadcastAck() {
    MessageAck::IM im (MessageAck::IM::imcSendAck, Net::core, imtCore, this);
    Ctrl->IMessage(&im);
  }


  // -- MessageNotify

  void MessageNotify::getNotification() {
    MessageNotify::IM im (MessageNotify::IM::imcMessageNotify, this);
    Ctrl->IMessage(&im);
  }


  // -- MessageHandler

  bool MessageHandler::registerHandler(enMessageQueue queue, Konnekt::enPluginPriority priority) {
    MessageHandler::IM im (MessageHandler::IM::imcRegisterMessageHandler, this, queue, priority);
    return Ctrl->IMessage(&im) != 0;
  }
  bool MessageHandler::unregisterHandler(enMessageQueue queue, Konnekt::enPluginPriority priority) {
    MessageHandler::IM im (MessageHandler::IM::imcUnregisterMessageHandler, this, queue, priority);
    return Ctrl->IMessage(&im) != 0;
  }
}