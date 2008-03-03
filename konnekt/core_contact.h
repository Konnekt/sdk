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
    inline String getString(tColId col) const {
      return Tables::oTable(Tables::tableContacts)->getString(getID(), col);
    }
    inline void setString(tColId col, const StringRef& value) {
      Tables::oTable(Tables::tableContacts)->setString(getID(), col, value);
    }

    inline int getInt(tColId col) const {
      return Tables::oTable(Tables::tableContacts)->getInt(getID(), col);
    }
    inline void setInt(tColId col, int value) {
      Tables::oTable(Tables::tableContacts)->setInt(getID(), col, value);
    }

    inline __int64 getInt64(tColId col) const {
      return Tables::oTable(Tables::tableContacts)->getInt64(getID(), col);
    }
    inline void setInt64(tColId col, __int64 value) {
      Tables::oTable(Tables::tableContacts)->setInt64(getID(), col, value);
    }

  public:
    bool inGroup(const StringRef& name) const;
    bool inActiveGroup() const;
    bool exists() const;

    bool isIgnored() const;
    bool ignore();
    void unignore();

    bool remove(bool ask_user);
    void changed();

  public:
    static Contact create(tNet net, const StringRef& uid);
    static Contact find(tNet net, const StringRef& uid);
    static bool exists(tNet net, const StringRef& uid);

  public:
    const static tColId colUid                 = (unsigned int) 0; ///< (#ctypeString) UID.
    const static tColId colNet                 = 1;  ///< (#ctypeInt) Sieæ.
    const static tColId colStatus              = 2;  ///< (#ctypeInt) Status.
    const static tColId colStatusInfo          = 18; ///< (#ctypeInt) Opis statusu.
    const static tColId colNotify              = 3;  ///< (#ctypeInt | #cflagNoSave) Ikonka powiadomienia.
    const static tColId colHost                = 4;  ///< (#ctypeString | #cflagNoSave) IP.
    const static tColId colPort                = 5;  ///< (#ctypeInt | #cflagNoSave) Port.
    const static tColId colName                = 6;  ///< (#ctypeString) Imiê.
    const static tColId colSurname             = 7;  ///< (#ctypeString) Nazwisko.
    const static tColId colNick                = 17; ///< (#ctypeString) Pseudo.
    const static tColId colDisplay             = 8;  ///< (#ctypeString) Nazwa wyœwietlana.
    const static tColId colCellPhone           = 9;  ///< (#ctypeString) Komórka.
    const static tColId colPhone               = 10; ///< (#ctypeString) Stacjonarny.
    const static tColId colMail                = 11; ///< (#ctypeString) Email.
    const static tColId colInfo                = 12; ///< (#ctypeString) Info.
    const static tColId colLocality            = 13; ///< (#ctypeString) Miejscowoœæ.
    const static tColId colCity                = colLocality;
    const static tColId colCountry             = 14; ///< (#ctypeString) Kraj
    const static tColId colBorn                = 19; ///< (#ctypeInt) Urodzony YYYYMMDD (w hexie)
    const static tColId colGender              = 20; ///< (#ctypeInt) P³eæ @ref gender_
    const static tColId colClient              = 15; ///< (#ctypeString) Nazwa i wersja u¿ywanego softu.
    const static tColId colClientVersion       = 28; ///< (#ctypeInt) Wersja Softu
    const static tColId colLastMsg             = 16; ///< (#ctypeInt | #cflagNoSave) ID ostatniej wiadomoœci.
    const static tColId colGroup               = 21; ///< (#ctypeString) Grupa do której nale¿y.
    const static tColId colActParent           = 22; ///< (#ctypeInt | #cflagNoSave) Parent akcji powiadomienia.
    const static tColId colActId               = 23; ///< (#ctypeInt | #cflagNoSave) ID akcji powiadomienia.
    const static tColId colInternal            = 24; ///< Dla rdzenia.
    const static tColId colStreet              = 25; ///< (#ctypeString) - ulica.
    const static tColId colPostalCode          = 26; ///< (#ctypeString) - kod pocztowy.
    const static tColId colNotifyMsg           = 27; ///< (#ctypeInt | #cflagNoSave) ID wiadomoœci powiadomienia.
    const static tColId colLastActivity        = 29; ///< (#ctypeInt64) Czas ostatniej aktywnoœci.
    const static tColId colStatusIcon          = 30; ///< (#ctypeInt) Identyfikator ikonki, która ma zast¹piæ ikonê statusu.

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