#pragma once

#include "core_message.h"

/**
 * @file
 * Nag��wek wtyczki K.Notify wy�wietlaj�cej komunikaty nad zegarkiem systemowym.
 *
 * @defgroup knotify_shared_h Wtyczka K.Notify
 *
 * Wtyczka s�u�y do wy�wietlania informacji w ma�ym, skinowanym okienku
 * nad zasobnikiem systemowym.
 * 
 * Spos�b u�ycia na przyk�adzie:
 * @code
 * // Poka�e zwyk�y komunikat...
 * Ctrl->IMessage(&KNotify::sIMessage_notify("Hello!"));
 * // Poka�e komunikat b��du...
 * Ctrl->IMessage(&KNotify::sIMessage_notify("B��d!", 0, KNotify::sIMessage_notify::tError));
 * // Poka�e komunikat z ikonk� - Logo sieci GG...
 * Ctrl->IMessage(&KNotify::sIMessage_notify("Hello!", UIIcon(IT_LOGO, Net::gg, 0, 0)));
 * // Aby w��czy� mo�liwo�� klikania, trzeba to uruchomi� poza konstruktorem
 * KNotify::sIMessage_notify notify("Hello!", UIIcon(IT_LOGO, Net::gg, 0, 0));
 * notify._action = sUIAction( ); // Oczywi�cie trzeba poda� identyfikatory akcji
 * notify._actionParam = 1; // Akcja otrzyma sUIActionNotify_2params::notify1 == 1
 * Ctrl->IMessage(&notify);
 * @endcode
 *
 * @{
 */

namespace KNotify {
  const int net = 774;  
  const int icon = 774000; 

  /** 
   * Ikonki
   */
  namespace icons {
    const int inform = 774001;
    const int warning = 774002;
    const int error = 774003;
  }

  /** 
   * Akcje wtyczki
   */
  namespace UI {
    const int gCfg = 774000;
    const int aPrev = 774116;
    const int aExample1 = 774117;
    const int aExample2 = 774118;
    const int aExample3 = 774119;
    const int aOpenWnd =  774120;
  }

  namespace Cfg {
    const int bmp = 774110;
    const int dir = 774115;
    const int status = 774120;
    const int msg = 774121;
    const int delay = 774122;
    const int anim = 774123;
    const int waitclick = 774124;
    const int limit = 774125;
    const int lmbclose = 774126;
    const int fullscreen = 774127;
    const int kinfouse = 774128;
    const int showdescr = 774129;
    const int shwomsgbody = 774130;
    const int showmsglen = 774131;
    const int selfstatus = 774132;
    const int showdescrconn = 774133;
  }

  /**
   * --- API zewn�trzne ---
   */

  /**
   * Komunikaty przyjmowane przez wtyczk� 
   */
  namespace IM {
    /**
     * Wy�wietla informacj� nad zegarkiem systemowym.
     *
     * @return (int) identyfikator u�ywany do usuwania wiadomo�ci.
     * @sa KNotify::sIMessage_notify
     */
    const int show = 774201;
    /**
     * Ukrywa informacj�  wed�ug numeru identyfikacyjnego zwracanego podczas wstawiania wiadomo�ci
     *
     * @param p1 (int) identyfikator
     */
    const int hide = 774202;
  }

  /** 
   * Pozostawiany tylko dla kompatybilno�ci z wcze�niejsz� wersj�. Prosz� nie u�ywa�! 
   * @deprecated
   */
  struct sIMessage_notify_v1: public sIMessage_base {
    char *txt; UINT mask; UINT status; UINT cntnet; HICON ico; 
  };

  /** 
   * Struktura do przesy�ania komunikatu...
   *
   * Typ ikonki ustawiany jest przez konstruktor.
   * Je�eli nie podamy �adnej ikonki, K.Notify dobierze jak��
   * w zale�no�ci od typu wiadomo�ci.
   */
  class sIMessage_notify: public sIMessage_base {
  public:
    const static unsigned char itIcoID = 0;   ///< _icoType - u�ywa _icoID, lub nie podaje ikonki, gdy _icoID jest == 0
    const static unsigned char itHICON = 1;   ///< _icoType - u�ywa _ico
    const static unsigned char tInform = 0;   ///< _msgType - Domy�lny
    const static unsigned char tError = 1;    ///< _msgType - B��d
    const static unsigned char tWarning = 2;  ///< _msgType - Ostrze�enie

  public:
    const char * _text;             ///< Tre�� komunikatu
    unsigned char _icoType : 4;     ///< Typ ikonki @sa itIcoID itHICON
    unsigned char _msgType : 4;     ///< Typ komunikatu @sa tInform tError tWarning
    signed   char _timeToLive : 8;  ///< Jak d�ugo komunikat b�dzie dost�pny, jako wielokrotno�� wy�wietlania jednej linijki, lub -1 je�li ma czeka� na klikni�cie.
    unsigned char _clickable : 8;   ///< Czy dzia�a action @sa _action

  private:
    unsigned char align__ : 8;

  public:
    /** 
     * Ikonka
     */
    union {
      int _icoID; ///< Identyfikator ikonki. @sa #UIIcon
      HICON _ico; ///< Podajemy uchwyt do Windowsowej ikony.
    };
    sUIAction _action; ///< Akcja do wywo�ania w momencie klikni�cia
    int _actionParam;  ///< Parametr do przekazania razem z #ACTN_ACTION w momencie wywo�ania _action.

  public:
    /** 
     * Przesy�a wiadomo�� z identyfikatorem ikonki 
     */
    sIMessage_notify(const char * text, unsigned int icoID, const unsigned char msgType = tInform, unsigned char timeToLive = 1)
      : sIMessage_base(IM::show, (tNet) KNotify::net, imtAll) 
      , _text(text), _icoType(itIcoID), _icoID(icoID), _msgType(msgType), _timeToLive(timeToLive), _actionParam(0), _clickable(0) 
    {
      s_size = sizeof(sIMessage_notify);
      _action = sUIAction(0, 0, -2);
    }
    /** 
     * Przesy�a wiadomo�� z uchwytem do ikonki 
     */
    sIMessage_notify(const char * text, HICON ico, const unsigned char msgType = tInform, unsigned char timeToLive = 1)
      : sIMessage_base(IM::show, (tNet) KNotify::net, imtAll) 
      , _text(text), _icoType(itHICON), _msgType(msgType), _timeToLive(timeToLive), _actionParam(0), _clickable(0) 
    {
      s_size = sizeof(sIMessage_notify);
      _ico = ico;
      _action = sUIAction(0, 0, -2);
    }
    /** 
     * Przesy�a wiadomo�� jako tInform 
     */
    sIMessage_notify(const char * text)
      : sIMessage_base(IM::show, (tNet) KNotify::net, imtAll) 
      , _text(text), _icoType(0), _icoID(0), _msgType(tInform), _timeToLive(1), _actionParam(0), _clickable(0)
    {
      s_size = sizeof(sIMessage_notify);
      _action = sUIAction(0, 0, -2);
    }

    sIMessage_notify(sIMessage_notify * msg): sIMessage_base(msg) {
      s_size = sizeof(sIMessage_notify);

      if (msg->s_size == sizeof(sIMessage_notify_v1)) { 
        sIMessage_notify_v1 * msg1 = (sIMessage_notify_v1*) msg;
        this->_text = msg1->txt;
        this->_icoType = msg1->mask ? itIcoID : itHICON;
        this->_icoID = msg1->mask == 0 
          ? (int) msg1->ico 
          : msg1->mask == 1 
            ? UIIcon(IT_STATUS, msg1->cntnet, msg1->status, 0) 
            : msg1->mask == 2 
              ? UIIcon(IT_MESSAGE, 0, Message::typeMessage, 0) 
              : 0;
        this->_msgType = tInform;
        this->_timeToLive = 1;
        this->_actionParam = 0;
        this->_action = sUIAction(0, 0, -2);
        this->_clickable = 0;
      } else {
        *this = *msg;
      }
    }
  };

  /** 
   * Struktura do przesy�ania komunikatu rozszerzona o przesy�anie informacji dla K.Info (do innych aplikacji)...
   *
   * Rozszerzenie komunikatu wy�wietlania wiadomo�ci K.Notify o obs�ug� K.Info
   */
  class sIMessage_notify_kinfo: public sIMessage_notify {
  public:
    const static unsigned int tiStatus = 1;   ///< _type - typ komunikatu K.Info
    const static unsigned int tiMessage = 2;  ///< _type - typ komunikatu K.Info
    const static unsigned int tiFile = 3;     ///< _type - typ komunikatu K.Info
    const static unsigned int tiMail = 4;     ///< _type - typ komunikatu K.Info
    const static unsigned int tiURL = 5;      ///< _type - typ komunikatu K.Info

  public:
    char *_infoArgs;        ///< K.Info - Informacje do przes�ania @sa SetExtParam
    unsigned int _infoType; ///< K.Info - Typ wiadomo�ci @sa tiStatus tiMessage tiFile tiMail tiURL

  public:
    /** 
     * Przesy�a wiadomo�� z identyfikatorem ikonki
     */
    sIMessage_notify_kinfo(const char * text, unsigned int icoID, const unsigned char msgType = tInform, unsigned char timeToLive = 1)
      : sIMessage_notify(text, icoID, msgType, timeToLive), _infoType(0), _infoArgs(0)
    {
      s_size = sizeof(sIMessage_notify_kinfo);
    }
    /** 
     * Przesy�a wiadomo�� z uchwytem do ikonki
     */
    sIMessage_notify_kinfo(const char * text, HICON ico, const unsigned char msgType = tInform, unsigned char timeToLive = 1)
      : sIMessage_notify(text, ico, msgType, timeToLive), _infoType(0), _infoArgs(0)
    {
      s_size = sizeof(sIMessage_notify_kinfo);
    }
    /** 
     * Przesy�a wiadomo�� jako tInform 
     */
    sIMessage_notify_kinfo(const char * text)
      : sIMessage_notify(text), _infoType(0), _infoArgs(0)
    {
      s_size = sizeof(sIMessage_notify_kinfo);
    }
  };
}

/** @} */