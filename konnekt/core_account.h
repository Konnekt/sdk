#pragma once

namespace Konnekt {
  using namespace Stamina;

  typedef unsigned int tAccountId;
  const static tCntId accountNotExist = (tAccountId) -1;

  class Account {
  public:
    class IM {
    public:
      /** 
       * Dodaje konto.
       * 
       * @param p1 (int) sieæ
       * @param p2 (char*) nazwa
       * 
       * @return (tAccountId) ID nowego konta
       */
      static const tIMCid imcAccountAdd = 361;

      /**
       * Usuwa kontakt
       * 
       * @param p1 (tAccountId) ID
       */
      static const tIMCid imcAccountRemove = 362;

      /** 
       * Konto zosta³o zmienione.
       * Komunikat powinien byæ wysy³any w sytuacji zmiany colUid.
       * 
       * @param p1 (tAccountId) ID konta.
       */
      static const tIMCid imcAccountChanged = 363;

      /** 
       * Zwraca ID kontaktu.
       * Je¿eli @a net bêdzie ustawiony na Net::all w UID mo¿na przekazaæ nazwe konta.
       * Je¿eli konto o danym ID istnieje, ID zostanie zwrócone.
       * 
       * @param p1 (int) net
       * @param p2 (char*) UID
       *
       * @return (tAccountId) ID
       */
      static const tIMCid imcFindAccount = 364;

      /**
       * Sprawdza czy konto o podanym ID istnieje.
       * @param p1 (tAccountId) ID.
       */
      static const tIMCid imcAccountIdExist = 365;

      /**
       * Zwraca iloœæ kont.
       * @return (int) liczba kont.
       */
      static const tIMCid imcAccountCount = 366;

      /**
       * Konto zosta³o dodane
       * @param p1 (tAccountId) ID konta
       */
      static const tIMCid imAccountAdd = IM_BASE + 4020;

      /**
       * Konto zaraz zostanie usuniête.
       *
       * @param p1 (tAccountId) ID konta
       */
      static const tIMCid imAccountRemove = IM_BASE + 4021;

      /** 
       * Konto zosta³o usuniête.
       *
       * @param p1 (tAccountId) ID konta
       */
      static const tIMCid imAccountRemoved = IM_BASE + 4022;

      /** 
       * Uid przypisany do konta zosta³ zmieniony.
        *
       * @param p1 (tAccountId) ID konta
       */
      static const tIMCid imAccountChanged = IM_BASE + 4023;
    };

  public:
    Account(tAccountId accountId) : _accountId(accountId) { }

  public:
    inline operator tAccountId() const {
      return getID();
    }

    inline tAccountId getID() const {
      return _accountId;
    }

  public:
    inline String getUid() const {
      return getString(colUid);
    }
    inline void setUid(const StringRef& uid) {
      setString(colUid, uid);
      changed();
    }

    inline String getPassword() const {
      return getString(colPassword);
    }
    inline void setPassword(const StringRef& password) {
      setString(colPassword, password);
     }

    inline tNet getNet() const {
      return (tNet) getInt(colNet);
    }

    inline tStatus getStartStatus() const {
      return getInt(colStartStatus);
    }
    inline void setStartStatus(tStatus status) {
      setInt(colStartStatus, status);
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

    inline String getDisplay() const {
      return getString(colDisplay);
    }
    inline void setDisplay(const StringRef& display) {
      setString(colDisplay, display);
    }

  public:
    inline String getString(tColId col) const {
      return Tables::oTable(Tables::tableAccounts)->getString(getID(), col);
    }
    inline void setString(tColId col, const StringRef& value) {
      Tables::oTable(Tables::tableAccounts)->setString(getID(), col, value);
    }

    inline int getInt(tColId col) const {
      return Tables::oTable(Tables::tableAccounts)->getInt(getID(), col);
    }
    inline void setInt(tColId col, int value) {
      Tables::oTable(Tables::tableAccounts)->setInt(getID(), col, value);
    }

    inline __int64 getInt64(tColId col) const {
      return Tables::oTable(Tables::tableAccounts)->getInt64(getID(), col);
    }
    inline void setInt64(tColId col, __int64 value) {
      Tables::oTable(Tables::tableAccounts)->setInt64(getID(), col, value);
    }

  public:
    bool exists() const;

    bool remove();
    void changed();

  public:
    static Account create(tNet net, const StringRef& display);
    static Account find(tNet net, const StringRef& uid);
    static Account find(const StringRef& display);
    static bool exists(tNet net, const StringRef& uid);
    static bool exists(const StringRef& display);

  public:
    const static tColId colUid                 = (unsigned int) 0; ///< (#ctypeString) UID.
    const static tColId colPassword            = 1;  ///< (#ctypeString) Has³o.
    const static tColId colDisplay             = 2;  ///< (#ctypeString) Nazwa.
    const static tColId colNet                 = 3;  ///< (#ctypeInt) Sieæ.
    const static tColId colStartStatus         = 4;  ///< (#ctypeInt | #cflagNoSave) Ikonka powiadomienia.
    const static tColId colStatus              = 5;  ///< (#ctypeString | #cflagNoSave) IP.
    const static tColId colStatusInfo          = 6;  ///< (#ctypeInt | #cflagNoSave) Port.

  private:
    tAccountId _accountId;
  };
};