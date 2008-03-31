#pragma once

#include <Stamina/Time64.h>
#include <Stamina/String.h>

namespace Konnekt {
  using namespace Stamina;

  typedef unsigned int tCntId;
  const static tCntId cntNotExist = (tCntId) -1;

  class Contact {
  public:
    class IM {
    public:
      /** 
       * Klasa informuj¹ca o zmianach dotycz¹cych kontaktu.
       */
      class CntChanged: public sIMessage_base {
      public:
        /**
        * Co zosta³o zmienione.
        */
        enum enChanged {
          changedNone = 0,
          changedNet = 1,
          changedUid = 2,
          changedGroup = 4
        };

      public:
        CntChanged(tCntId cntID): cntID(cntID), changed(changedNone), oldNet(Net::none), oldUID(0) {
          this->id = imContactChanged;
          this->s_size = sizeof(*this);
        }

      public:
        tCntId cntID;         ///< ID kontaktu
        enChanged changed;    ///< Poprzednia wartoœæ net tego kontaktu
        unsigned int oldNet;  ///< Poprzednia wartoœæ net tego kontaktu
        const char * oldUID;  ///< Poprzednia wartoœæ UID
      };

      /** 
       * Klasa s³u¿¹ca do zmiany statusu i opisu kontaktu.
       */
      class StatusChange: public sIMessage_base {
      public:
        const static unsigned int sizeV1 = 12;

      public:
        StatusChange(tCntId cntID, unsigned int status, const StringRef& info = StringRef()) 
          : cntID(cntID), status(status), _info(info) 
        {
            this->id = imContactStatusChange;
            _chInfo = (char*) _info.a_str();
            this->s_size = sizeof(*this);
        }

      public:
        Stamina::String getInfo() const {
          return getObsoleteString(this->_info, this->_chInfo, this->isStructV2());
        }
        void setInfo(const Stamina::StringRef& info) {
          setObsoleteString(info, this->_info, this->_chInfo, this->isStructV2());
        }

        unsigned int structSize() const {
          return s_size;
        }

        bool isStructV2() const {
          return structSize() >= sizeof(*this);
        }

      public:
        tCntId cntID;         ///< ID kontaktu
        unsigned int status;  ///< Nowy status, który zaraz zostanie ustawiony. -1 oznacza brak zmiany.

      private:
        char * _chInfo;       ///< Nowy opis statusu, który zaraz zostanie ustawiony. 0 oznacza brak zmiany.
        Stamina::String _info;
      };

    public:
      /**
       * Sprawdza czy kontakt jest ignorowany.
       * 
       * @param p1 (int) net
       * @param p2 (char*) UID
       * 
       * @return true jeœli jest.
       */
      static const tIMCid imcContactIgnored = 310;

      /** 
       * Zwraca ID kontaktu.
       * Je¿eli @a net bêdzie ustawiony na Net::none w UID mo¿na przekazaæ (tekstem) ID kontaktu. 
       * Je¿eli kontakt o danym ID istnieje, ID zostanie zwrócone. Funkcjonalnoœæ ta mo¿e s³u¿yæ g³ównie do 
       * "przemycania" bezpoœrednich identyfikatorów kontaktów do f-cji które przyjmuj¹ tylko wartoœci net i uid.
       * 
       * @param p1 (int) net
       * @param p2 (char*) UID
       *
       * @return (int) ID
       */
      static const tIMCid imcFindContact = 200;

      /**
       * Sprawdza czy kontakt o podanym ID istnieje.
       * @param p1 (int) ID.
       */
      static const tIMCid imcContactIdExist = 233;

      /** 
       * Dodaje kontakt.
       * Po ustawieniu parametrów kontaktu, lub od razu po #imcContactAdd trzeba wys³aæ #imcContactChanged
       * 
       * @param p1 (int) sieæ
       * @param p2 (int) UID
       * 
       * @return (int) ID nowego kontaktu
       */
      static const tIMCid imcContactAdd = 230;

      /**
       * Usuwa kontakt
       * 
       * @param p1 (int) ID
       * @param p2 (bool) true - u¿ytkownik zostanie zapytany o zgodê.
       */
      static const tIMCid imcContactRemove = 231;

      /**
       * Zwraca iloœæ kontaktów.
       * @return (int) liczba kontaktów.
       */
      static const tIMCid imcContactCount = 201;

      /** 
       * Sprawdza czy podany kontakt znajduje sie w grupie.
       * 
       * @param p1 (int) ID kontaktu.
       * @param p2 (char*) - grupa do sprawdzenia (jeœli == 0 sprawdzi w grupie aktywnej)
       * 
       * @return (bool) true jeœli znajduje siê...
       */

      static const tIMCid imcContactInGroup = 305;

      /** 
       * Kontakt zosta³ zmieniony.
       * Komunikat powinien byæ wysy³any @b tylko w sytuacji zmiany Contact::colUid, Contact::colNet, lub zaraz po dodaniu!
       * Do wszystkich wtyczek z typem #IMT_CONTACT zostanie rozes³ane #imContactChanged, lub #imContactAdd.
       * Nie ma ju¿ potrzeby wysy³ania #IMI_REFRESH_CNT
       * 
       * @param p1 ID kontaktu.
       */
      static const tIMCid imcContactChanged = 232;

      /**
       * Zmienia status kontaktu.
       * @sa sIMessage_StatusChange
       */
      static const tIMCid imcContactSetStatus = 234;

      /**
       * @sa #imcContactIgnored
       */
      static const tIMCid imcContactIgnoredFind = imcContactIgnored;

      /**
       * Dodaje kontakt do listy ignorowanych.
       * 
       * @param p1 (int) sieæ
       * @param p2 (char*) UID
       */
      static const tIMCid imcContactIgnore = 311;

      /**
       * Usuwa kontakt z listy ignorowanych.
       * 
       * @param p1 (int) sieæ
       * @param p2 (char*) UID
       */
      static const tIMCid imcContactUnignore = 312;

      /**
       * Informacje o kontakcie @a p1 zosta³y zmienione i moga byæ np. zapisane na serwerze.
       *
       * @param p1 (int) ID kontaktu do wys³ania
       * @param p2 (bool) 
       *   - 0 - info powinno byæ wczytywane bezpoœrednio z tabeli.
       *   - 1 - info powinno byæ ustawione jako wartoœci odpowiednich akcji w oknie z informacjami o kontakcie (u¿ywaj¹c UIActionCfgSetValue())
       */
      static const tIMCid imContactUpload = IM_SHARE + 4000;

      /**
       * Informacje o kontakcie @a p1 powinny zostaæ zaktualizowane (np. pobrane z serwera).
       * 
       * @param p1 (int) ID kontaktu do pobrania
       * @param p2 (bool) 0 - info powinno zostaæ zapisane bezpoœrednio w tabeli. 
       */
      static const tIMCid imContactDownload = IM_SHARE + 4001;

      /**
       * Kontakt zaraz zostanie usuniêty.
       *
       * @param p1 (int) ID kontaktu
       * @param p2 (bool) true - usuniêcie zosta³o potwierdzone przez uzytkownika.
       */
      static const tIMCid imContactRemove = IM_BASE + 4002;
 
      /** 
       * Kontakt zosta³ usuniety.
       *
       * @param p1 (int) ID kontaktu
       * @param p2 (bool) true - usuniêcie zosta³o potwierdzone przez uzytkownika.
       */
      static const tIMCid imContactRemoved = IM_BASE + 4005;

      /**
       * Kontakt zosta³ dodany
       * @param p1 (int) ID kontaktu
       */
      static const tIMCid imContactAdd = IM_BASE + 4003;

      /**
       * Kontakt jest w trakcie tworzenia (które mo¿e zostaæ ew. przerwane)
       * Parametry kontaktu nie s¹ jeszcze ustalone.
       *
       * @param p1 (int) ID kontaktu
       */
      static const tIMCid imContactAdding = IM_BASE + 4004;

      /** 
       * ¯¹danie szukania kontaktu (np. w katalogu sieci)
       * @param p1 (sCNTSEARCH *) parametry wyszukiwania
       */
      static const tIMCid imContactSearch = IM_BASE + 4010;

      /** 
       * Któraœ z cech kontaktu (np. UID) zosta³a zmieniona. Przesy³ane przy pomocy CntChanged. 
       * Je¿eli przecastujesz to na sIMessage_2params to @a p1 jest ID kontaktu.
       */
      static const tIMCid imContactChanged = IM_BASE + 4006;

      /**
       * Status kontaktu zaraz ulegnie zmianie.
       * @return (sIMessage_StatusChange*)
       */
      static const tIMCid imContactStatusChange = IM_BASE + 4011;

      /** 
       * U¿ytkownik pisze wiadomoœæ do wskazanego kontaktu. Wys³ane do interfejsu spowoduje 
       * rozes³anie #imContactComposing do wszystkich wtyczek i je¿eli w przeci¹gu kilkunastu 
       * sekund nie zostanie wys³ane ponownie, rozeœle #imContactComposingStop.
       * 
       * @param p1 (int) ID kontaktu
       */
      static const tIMCid imContactComposing = IM_SHARE + 4030;

      /** 
       * U¿ytkownik przesta³ pisaæ do wskazanego kontaktu.
       * Wys³ane do interfejsu spowoduje rozes³anie do wtyczek #imContactComposingStop je¿eli w przeci¹gu
       * ostatnich kilkunastu sekund wyst¹pi³o zdarzenie #imContactComposing z tym samym kontaktem.
       *
       * @param p1 (int) ID kontaktu
       */
      static const tIMCid imContactComposingStop = IM_SHARE + 4031;

      /**
       * Lista ignorowanych kontaktów uleg³a zmianie.
       * 
       * @param p1 (int) sieæ > 0 - kontakt zosta³ dodany, < 0 - usuniêty
       * @param p2 (char*) 
       */
      static const tIMCid imContactIgnoreChanged = IM_BASE + 4021;
    };

    enum enGender {
      genderUnknown,
      genderFemale,
      genderMale
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
