#pragma once

#include <Stamina/Time64.h>

namespace Konnekt {
  using namespace Stamina;

  typedef unsigned int tCntId;

  const static tCntId cntNotExist = (tCntId) -1;


  class Contact {
  public:
    enum enGender {
      genUnknown,
      genFemale,
      genMale
    };

  public:
    Contact(tNet net, const StringRef& uid) : _cntId(cntNotExist) {
      *this = find(net, uid);
    }
    Contact(tCntId cntId) : _cntId(cntId) { }

  public:
    inline operator tCntId() const {
      return getID();
    }

    inline tCntId getID() const {
      return _cntId;
    }

  public:
    inline String getUid() const {
      return getString(colUid);
    }
    inline void setUid(const StringRef& uid) {
      setString(colUid, uid);
      changed();
    }

    inline tNet getNet() const {
      return (tNet) getInt(colNet);
    }
    inline void setNet(tNet net) {
      setInt(colNet, net);
      changed();
    }

    inline tStatus getStatus() const {
      return getInt(colStatus);
    }
    inline void setStatus(tStatus status) {
      setInt(colStatus, status);
    }

    inline String getStatusInfo() const {
      return getString(colStatusInfo);
    }
    inline void setStatusInfo(const StringRef& info) {
      setString(colStatusInfo, info);
    }

    inline int getNotify() const {
      return getInt(colNotify);
    }
    inline void setNofify(int notify) {
      setInt(colNotify, notify);
    }

    inline String getHost() const {
      return getString(colHost);
    }
    inline void setHost(const StringRef& host) {
      setString(colHost, host);
    }

    inline int getPort() const {
      return getInt(colPort);
    }
    inline void setPort(int port) {
      setInt(colPort, port);
    }

    inline Time64 getLastActivity() const {
      return getInt64(colLastActivity);
    }
    inline void setLastActivity(const Time64& t) {
      setInt64(colLastActivity, t);
    }

    inline String getName() const {
      return getString(colName);
    }
    inline void setName(const StringRef& name) {
      setString(colName, name);
    }

    inline String getSurname() const {
      return getString(colSurname);
    }
    inline void setSurname(const StringRef& surname) {
      setString(colSurname, surname);
    }

    inline String getNick() const {
      return getString(colNick);
    }
    inline void setNick(const StringRef& nick) {
      setString(colNick, nick);
    }

    inline String getDisplay() const {
      return getString(colDisplay);
    }
    inline void setDisplay(const StringRef& display) {
      setString(colDisplay, display);
    }

    inline String getEmail() const {
      return getString(colMail);
    }
    inline void setEmail(const StringRef& email) {
      setString(colMail, email);
    }

    inline enGender getGender() const {
      return (enGender) getInt(colGender);
    }
    inline void setGender(enGender gender) {
      setInt(colGender, gender);
    }

  public:
    inline String getString(tColId colId) const {
      return Tables::oTable(Tables::tableContacts)->getString(_cntId, colId);
    }
    inline void setString(tColId colId, const StringRef& value) {
      Tables::oTable(Tables::tableContacts)->setString(_cntId, colId, value);
    }

    inline int getInt(tColId colId) const {
      return Tables::oTable(Tables::tableContacts)->getInt(_cntId, colId);
    }
    inline void setInt(tColId colId, int value) {
      Tables::oTable(Tables::tableContacts)->setInt(_cntId, colId, value);
    }

    inline __int64 getInt64(tColId colId) const {
      return Tables::oTable(Tables::tableContacts)->getInt64(_cntId, colId);
    }
    inline void setInt64(tColId colId, __int64 value) {
      Tables::oTable(Tables::tableContacts)->setInt64(_cntId, colId, value);
    }

  public:
    bool inGroup(const StringRef& name) const;
    bool inActiveGroup() const;
    bool exists() const;

    bool isIgnored() const;
    void ignore();
    void unignore();

    bool remove(bool ask_user);
    void changed();

  public:
    static Contact create(tNet net, const StringRef& uid);
    static Contact find(tNet net, const StringRef& uid);
    static bool exists(tNet net, const StringRef& uid);

  public:
    const static tColId colUid                 = (unsigned int) 0; ///< #DT_CT_PCHAR UID.
    const static tColId colNet                 = 1;  ///< #DT_CT_INT Sieæ.
    const static tColId colStatus              = 2;  ///< #DT_CT_INT Status.
    const static tColId colStatusInfo          = 18; ///< #DT_CT_INT Opis statusu.
    const static tColId colNotify              = 3;  ///< #DT_CT_INT | #DT_CF_NOSAVE Ikonka powiadomienia.
    const static tColId colHost                = 4;  ///< #DT_CT_PCHAR | #DT_CF_NOSAVE IP.
    const static tColId colPort                = 5;  ///< #DT_CT_INT | #DT_CF_NOSAVE Port.
    const static tColId colName                = 6;  ///< #DT_CT_PCHAR Imiê.
    const static tColId colSurname             = 7;  ///< #DT_CT_PCHAR Nazwisko.
    const static tColId colNick                = 17; ///< #DT_CT_PCHAR Pseudo.
    const static tColId colDisplay             = 8;  ///< #DT_CT_PCHAR Nazwa wyœwietlana.
    const static tColId colCellPhone           = 9;  ///< #DT_CT_PCHAR Komórka.
    const static tColId colPhone               = 10; ///< #DT_CT_PCHAR Stacjonarny.
    const static tColId colMail                = 11; ///< #DT_CT_PCHAR Email.
    const static tColId colInfo                = 12; ///< #DT_CT_PCHAR Info.
    const static tColId colLocality            = 13; ///< #DT_CT_PCHAR Miejscowoœæ.
    const static tColId colCity                = colLocality;
    const static tColId colCountry             = 14; ///< #DT_CT_PCHAR Kraj
    const static tColId colBorn                = 19; ///< #DT_CT_INT Urodzony YYYYMMDD (w hexie)
    const static tColId colGender              = 20; ///< #DT_CT_INT P³eæ \ref gender_
    const static tColId colClient              = 15; ///< #DT_CT_PCHAR Nazwa i wersja u¿ywanego softu.
    const static tColId colClientVersion       = 28; ///< #DT_CT_INT Wersja Softu
    const static tColId colLastMsg             = 16; ///< #DT_CT_INT | #DT_CF_NOSAVE ID ostatniej wiadomoœci.
    const static tColId colGroup               = 21; ///< #DT_CT_PCHAR Grupa do której nale¿y.
    const static tColId colActParent           = 22; ///< #DT_CT_INT | #DT_CF_NOSAVE Parent akcji powiadomienia.
    const static tColId colActId               = 23; ///< #DT_CT_INT | #DT_CF_NOSAVE ID akcji powiadomienia.
    const static tColId colInternal            = 24; ///< Dla rdzenia.
    const static tColId colStreet              = 25; ///< #DT_CT_PCHAR - ulica.
    const static tColId colPostalCode          = 26; ///< #DT_CT_PCHAR - kod pocztowy.
    const static tColId colNotifyMsg           = 27; ///< #DT_CT_INT | #DT_CF_NOSAVE ID wiadomoœci powiadomienia.
    const static tColId colLastActivity        = 29; ///< #DT_CT_64 Czas ostatniej aktywnoœci.
    const static tColId colStatusIcon          = 30; ///< #DT_CT_INT Identyfikator ikonki, która ma zast¹piæ ikonê statusu.

    const static tColId colMiddleName          = 31;
    const static tColId colMailMore            = 32;
    const static tColId colPhoneMore           = 33;
    const static tColId colDescription         = 34;
    const static tColId colFax                 = 35;
    const static tColId colUrl                 = 36;
    const static tColId colAddressMore         = 37;
    const static tColId colRegion              = 38;
    const static tColId colPoBox               = 39;

    const static tColId colWorkOrganization    = 50;
    const static tColId colWorkOrgUnit         = 51;
    const static tColId colWorkTitle           = 52;
    const static tColId colWorkRole            = 53;
    const static tColId colWorkMail            = 54;
    const static tColId colWorkUrl             = 55;
    const static tColId colWorkPhone           = 56;
    const static tColId colWorkFax             = 57;
    const static tColId colWorkStreet          = 58;
    const static tColId colWorkAdressMore      = 59;
    const static tColId colWorkPoBox           = 60;
    const static tColId colWorkPostalCode      = 61;
    const static tColId colWorkLocality        = 62;
    const static tColId colWorkRegion          = 63;
    const static tColId colWorkCountry         = 64;
    const static tColId colWorkMore            = 65;

  private:
    tCntId _cntId;
  };
};