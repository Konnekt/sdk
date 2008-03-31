/**
 * @file
 * @deprecated
 */
#pragma once

#ifndef KONNEKT_SDK_SUPPRES_OBSOLETE_NOTICE
  #pragma message("Prosze przerobic kod tak, zeby NIE uzywac obsolete_defines.h !!!")
#endif

/** 
 * @addtogroup gr_shared 
 * @{ 
 */

/** 
 * @addtogroup net_
 * @{ 
 */

#define NET_FIRST         Net::first         ///< Wiadomoœæ dotrze do pierwszej wtyczki (dowolnej sieci), która potrafi j¹ obs³u¿yæ.
#define NET_BROADCAST     Net::broadcast     ///< Wiadomoœæ dotrze do wtyczek wszystkich sieci.
#define NET_BC            NET_BROADCAST      ///< Odpowiednik #NET_BROADCAST.
#define NET_NONE          Net::none          ///< Wiadomosci do rdzenia.

#define NET_SOUND         Net::sound         ///< DŸwiêk
#define NET_UPDATE        Net::update        ///< Update
#define NET_OTHER         Net::other         ///< Wtyczki nie posiadaj¹ce akcji, nie obs³uguj¹ce wiadomoœci itp.

#define NET_GG            Net::gg            ///< Wtyczki obs³uguj¹ce protokó³ GG
#define NET_ICQ           Net::icq           ///< Wtyczki obs³uguj¹ce protokó³ ICQ
#define NET_JABBER        Net::jabber        ///< Wtyczki obs³uguj¹ce protokó³ JABBER
#define NET_EMAIL         Net::email         ///< Wtyczki obs³uguj¹ce EMaile
#define NET_SMS           Net::sms           ///< Wtyczki obs³uguj¹ce SMSy
#define NET_KLAN          Net::klan 
#define NET_KSTYLE        Net::kstyle
#define NET_EXPIMP        Net::expimp
#define NET_KONNFERENCJA  Net::konnferencja

#define NET_AIM           Net::aim           ///< Wtyczki obs³uguj¹ce protokó³ AIM
#define NET_YAHOO         Net::yahoo         ///< Wtyczki obs³uguj¹ce protokó³ YAHOO
#define NET_MSN           Net::msn           ///< Wtyczki obs³uguj¹ce protokó³ MSN
#define NET_TLEN          Net::tlen          ///< Wtyczki obs³uguj¹ce protokó³ TLEN

#define NET_KTRANSFER     130                ///< kTransfer 

/** @} */

/*
 * -----------------------------------------------------------------------------------------------
 */

/** 
 * @addtogroup imt_
 * @{
 */
typedef unsigned int tIMtype;

/**
 * Wszystkie typy.
 */
#define IMT_ALL         Konnekt::imtAll
/**
 * Wiadomoœæ bezpoœrednio do rdzenia (lub UI).
 */
#define IMT_CORE        Konnekt::imtCore

/**
 * Wiadomoœci tekstowe.
 */
#define IMT_MESSAGE     Konnekt::imtMessage
/**
 * Protokó³ sieciowy.
 */
#define IMT_PROTOCOL    Konnekt::imtProtocol
/**
 * Kontakty.
 */
#define IMT_CONTACT     Konnekt::imtContact
/**
 * Konfiguracja.
 */
#define IMT_CONFIG      Konnekt::imtConfig
/**
 * Interfejs U¿ytkownika (u¿ywanie wtyczki UI).
 */
#define IMT_UI          Konnekt::imtUI
/** 
 * Wtyczka obs³uguje kontakty ca³ej swojej sieci.
 *
 * @attention Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
 * do list sieci w opcjach kontaktu (np. dodawanie, ignorowanie itp.)
 * Tylko @b jedna wtyczka z ca³ej sieci mo¿e mieæ ten typ ustawiony!!!
 * @sa #IM_PLUG_NETNAME @ref cnt
 */
#define IMT_NET         Konnekt::imtNet  // Rozpoznaje kontakty danej sieci (podczas dodawania, edycji)
/** 
 * Wtyczka obs³uguje wyszukiwanie kontaktów w swojej sieci.
 * @attention Podobnie jak w #IMT_UI Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
 * do list sieci w wyszukiwarce kontaktów
 * Tylko @b jedna wtyczka z ca³ej sieci mo¿e mieæ ten typ ustawiony!!!
 * @sa #IM_PLUG_NETNAME @ref cnt
 */
#define IMT_NETSEARCH   Konnekt::imtNetSearch
/**
 * Wtyczka wykorzystuje system obs³ugi wiadomoœci tekstowych zawarty w UI.
 */
#define IMT_MSGUI       Konnekt::imtMsgUI
/**
 * Kontakty w sieci posiadaj¹ UID (UserID)
 */
#define IMT_NETUID      Konnekt::imtNetUID
/**
 * Otrzyma w IM_MSG_RCV wszystkie wiadomoœci, niezale¿nie od @ref net_ "NET".
 */
#define IMT_ALLMESSAGES Konnekt::imtAllMessages
/**
 * Bêdzie otrzymywaæ IM_MSG_ACK.
 */
#define IMT_MESSAGEACK Konnekt::imtMessageAck

/** @} */ // imt_

typedef enPluginPriority PLUGP_enum;

/** 
 * Grupy priorytetów dla #IM_PLUG_PRIORITY 
 */
const PLUGP_enum PLUGP_LOWEST = Konnekt::priorityLowest;
const PLUGP_enum PLUGP_LOW = Konnekt::priorityLow;
const PLUGP_enum PLUGP_STANDARD = Konnekt::priorityStandard;
const PLUGP_enum PLUGP_HIGH = Konnekt::priorityHigh;
const PLUGP_enum PLUGP_HIGHEST = Konnekt::priorityHighest;
const PLUGP_enum PLUGP_NONE = Konnekt::priorityNone;


/**
 * @addtogroup imerror_
 * @{
 */
#define IMERROR_NORESULT Konnekt::errorNoResult     ///< Wtyczka nie obs³u¿y³a wiadomoœci.
#define IMERROR_UNSUPPORTEDMSG IMERROR_NORESULT     ///< Wtyczka nie obs³u¿y³a wiadomoœci.
#define IMERROR_BADSENDER Konnekt::errorBadSender   ///< Wiadomoœæ wstrzymana, pojawi³ siê b³¹d...
#define IMERROR_BADPLUG Konnekt::errorBadPlugin     ///< Podana wtyczka nie istnieje.
#define IMERROR_THREADSAFE Konnekt::errorThreadSafe ///< Wiadomoœæ zosta³a wywo³ana w trybie bezpiecznym (bez oczekiwania na powrót).
#define IMERROR_SHUTDOWN Konnekt::errorShutdown     ///< Wiadomoœæ zosta³a anulowana z powodu zamykania programu.
#define IMERROR_BADPARAM Konnekt::errorBadParam     ///< Nieprawid³owe parametry.
#define IMERROR_BADSTRUCT Konnekt::errorBadStruct   ///< Niepoprawna struktura.

/** @} */ // imerror_

/**
 * @defgroup cnt_ Tabela Kontaktów
 * @{
 */

#define CNT_UID             ((unsigned int) 0)  ///< #ctypeString UID.
#define CNT_NET             1                   ///< #ctypeInt Sieæ.
#define CNT_STATUS          2                   ///< #ctypeInt Status.
#define CNT_STATUSINFO      18                  ///< #ctypeString Opis statusu.
#define CNT_NOTIFY          3                   ///< #ctypeInt | #cflagNoSave Ikonka powiadomienia.
#define CNT_HOST            4                   ///< #ctypeString | #cflagNoSave IP.
#define CNT_PORT            5                   ///< #ctypeInt | #cflagNoSave Port.
#define CNT_NAME            6                   ///< #ctypeString Imiê.
#define CNT_SURNAME         7                   ///< #ctypeString Nazwisko.
#define CNT_NICK            17                  ///< #ctypeString Pseudo.
#define CNT_DISPLAY         8                   ///< #ctypeString Nazwa wyœwietlana.
#define CNT_CELLPHONE       9                   ///< #ctypeString Komórka.
#define CNT_PHONE           10                  ///< #ctypeString Stacjonarny.
#define CNT_EMAIL           11                  ///< #ctypeString Email.
#define CNT_INFO            12                  ///< #ctypeString Info.
#define CNT_LOCALITY        13                  ///< #ctypeString Miejscowoœæ.
#define CNT_CITY            CNT_LOCALITY
#define CNT_COUNTRY         14                  ///< #ctypeString Kraj
#define CNT_BORN            19                  ///< #ctypeInt Urodzony YYYYMMDD (w hexie)
#define CNT_GENDER          20                  ///< #ctypeInt P³eæ @ref gender_
#define CNT_CLIENT          15                  ///< #ctypeString Nazwa i wersja u¿ywanego softu.
#define CNT_CLIENTVERSION   28                  ///< #ctypeInt Wersja Softu
#define CNT_LASTMSG         16                  ///< #ctypeInt | #cflagNoSave ID ostatniej wiadomoœci.
#define CNT_GROUP           21                  ///< #ctypeString Grupa do której nale¿y.
#define CNT_ACT_PARENT      22                  ///< #ctypeInt | #cflagNoSave Parent akcji powiadomienia.
#define CNT_ACT_ID          23                  ///< #ctypeInt | #cflagNoSave ID akcji powiadomienia.
#define CNT_INTERNAL        24                  ///< @internal
#define CNT_STREET          25                  ///< #ctypeString - ulica.
#define CNT_POSTALCODE      26                  ///< #ctypeString - kod pocztowy.
#define CNT_NOTIFY_MSG      27                  ///< #ctypeInt | #cflagNoSave ID wiadomoœci powiadomienia.
#define CNT_LASTACTIVITY    29                  ///< #ctypeInt64 Czas ostatniej aktywnoœci.
#define CNT_STATUS_ICON     30                  ///< #ctypeInt Identyfikator ikonki, która ma zast¹piæ ikonê statusu.


#define CNT_MIDDLENAME      31
#define CNT_EMAIL_MORE      32
#define CNT_PHONE_MORE      33
#define CNT_DESCRIPTION     34
#define CNT_FAX             35
#define CNT_URL             36
#define CNT_ADDRESS_MORE    37
#define CNT_REGION          38
#define CNT_POBOX           39

#define CNT_WORK_ORGANIZATION 50
#define CNT_WORK_ORG_UNIT     51
#define CNT_WORK_TITLE        52
#define CNT_WORK_ROLE         53
#define CNT_WORK_EMAIL        54
#define CNT_WORK_URL          55
#define CNT_WORK_PHONE        56
#define CNT_WORK_FAX          57
#define CNT_WORK_STREET       58
#define CNT_WORK_ADDRESS_MORE 59
#define CNT_WORK_POBOX        60
#define CNT_WORK_POSTALCODE   61
#define CNT_WORK_LOCALITY     62
#define CNT_WORK_REGION       63
#define CNT_WORK_COUNTRY      64
#define CNT_WORK_MORE         65

// 40 / 66 // ostatni

#define CNTM_STATUS     ST_MASK
#define CNTM_FLAG       0xFFFFFF00

/** @} */ // cnt_

/** 
 * @defgroup gender_ Oznaczenie p³ci
 * @{
 */

#define GENDER_UNKNOWN  0 ///< Nieznana
#define GENDER_FEMALE   1 ///< Kobieta
#define GENDER_MALE     2 ///< Mê¿czyzna

/** @} */ // gender_


/*
#define MT_MESSAGE      1    ///< Zwyk³a wiadomoœæ.
#define MT_QUICKEVENT   2    ///< Krótka notka (kasowana automatycznie w kolejce) (np. wiadomoœæ nie dosz³a itp.)
#define MT_CNTEVENT     3    ///< wydarzenie (np. ktoœ mnie doda³ do swojej listy itp.) zwi¹zane z kontaktem na liœcie
#define MT_EVENT        (MT_CNTEVENT | MT_MASK_NOTONLIST)   ///< wydarzenie (np. ktoœ mnie doda³ do swojej listy itp.)
#define MT_SERVEREVENT  (4 | MT_MASK_NOTONLIST)             ///< Wiadomoœæ od serwera.
#define MT_AUTHORIZE    5    ///< Proœba o autoryzacje (ICQ).
#define MT_CONFERENCE   6    ///< Wiadomoœæ konferencyjna.
#define MT_FILE         7    ///< Przes³anie pliku.
#define MT_MAIL         8    ///< Email.
#define MT_SMS          9    ///< Np. potwierdzenie dotarcia sms'ów.
#define MT_SOUND        10   ///< Rozmowa g³osowa.
#define MT_URL          (11 | MT_MASK_NOTONLIST)    ///< URL. 
                                                    ///< Jako dodatkowe parametry w ext przyjmuje Width i Heigth
#define MT_SPECIAL      12   ///< Nieokreslona wiadomosc.
#define MT_SPECIAL_NOL  (13 | MT_MASK_NOTONLIST)    ///< Nieokreslona wiadomosc spoza listy.
#define MT_IMAGE        15   ///< Obraz, sciezka do pliku w cMessage::ext - #MEX_FILE_PATH

#define MT_BOARD        16 

#define MT_MASK_NOTONLIST 0x1000  ///< Oznacza ¿e ta wiadomosc nie zostanie
                                  ///  wyœwietlona na liscie, ani nie zostanie
                                  ///  sprawdzone czy docelowy kontakt na liœcie
                                  ///  siê znajduje
#define MT_MASK         0xFFF     ///< Maskuje bity odpowiedzialne za sam typ wiadomoœci.
*/

#ifdef KONNEKT_OBSOLETE_ALL
  /**
   * @defgroup mf_ flagi wiadomoœci tekstowych
   * @{
  */
  #define MF_SEND         2           ///< Wiadomoœæ przeznaczona do wys³ania
  #define MF_NOEVENTS     4           ///< #MT_QUICKEVENT maj¹ nie byæ wysy³ane
  #define MF_NOSAVE       8           ///< Wiadomoœæ nie zostanie zapisana na dysk ...
  /**
   * @brief #IM_MSG_OPEN / #IM_MSG_SEND zostanie wys³ane z #IMC_MESSSAGEQUEUE tylko
   * gdy zostanie ono wywo³ane dla tego typu i sieci wiadomoœci.
   */
  #define MF_REQUESTOPEN  0x10
  #define MF_PROCESSING   0x20        ///< Flaga wewnêtrzna oznaczaj¹ca ¿e wiadomoœæ jest w trakcie przetwarzania, Nie powinna byæ u¿ywana!
  /**
   * Wiadomoœæ ju¿ zosta³a otwarta. Teraz czeka w kolejce na usuniêcie.
   * Flaga ta jest czyszczona podczas zamykania.
   */
  #define MF_OPENED       0x40
  #define MF_HANDLEDBYUI  0x80        ///< Wiadomoœæ zostanie obs³u¿ona przez UI
  /**
   * Wiadomoœæ zosta³a stworzona przez jakiœ "automatyczny"
   * proces, wiêc, gdy jesteœmy ukryci, nie powinna byæ wysy³ana.
   */
  #define MF_AUTOMATED    0x100
  /**
   * Treœæ wiadomoœci zawiera znaczniki HTML, a znaki specjalne s¹ kodowane (przynajmniej > = &gt; < = &lt; i " = &quot;
   * Html powinien byæ sformatowany jak XHTML (<img/>, wszystkie atrybuty w "" itd..)
   */
  #define MF_HTML         0x200
  /**
   * Interfejs obs³u¿y wyœwietlanie wiadomoœci w menu.
   * Za ikonkê pos³u¿y cMessage::notify, nazwê pozycji w menu ustawiamy
   * w Ext jako parametr "ActionTitle". Je¿eli ustawiona jest cMessage::action
   * zostanie ona wys³ana po otwarciu wiadomoœci. W przeciwnym razie zostanie
   * wywo³ane IM_MSG_OPEN.
   * Wtyczka musi w #IM_MSG_RCV zadeklarowaæ obs³ugê wiadomoœci.
   */
  #define MF_MENUBYUI     0x400 
  #define MF_LEAVEASIS    0x800       ///< Zabrania wtyczkom zmiany treœci, w tym wyœwietlania emotikon
  #define MF_HIDE         0x1000      ///< Nie wyœwietla wiadomoœci w interfejsie (w tej chwili w oknie rozmowy)
  #define MF_DONTADDTOHISTORY 0x2000  ///< Nie zapisuje w historii
  
  #define MF_QE_NORMAL    0x10000     ///< MT_QUICKEVENT narysuje zwyk³¹ czcionk¹...
  #define MF_QE_SHOWTIME  0x20000     ///< MT_QUICKEVENT poka¿e czas nadejœcia...

  /** @} */ // mf_
#endif

/** @} */

#ifdef KONNEKT_OBSOLETE_MESSAGE
  #define IMC_NEWMESSAGE Message::imcNewMessage

  #define IMC_MESSAGEQUEUE imcMessageQueue 
  #define IMC_MESSAGENOTIFY  
  /**
   * @param p1 (sMESSAGESELECT*) które wiadomoœci maj¹ zostaæ uwzglêdnione
   * @return (int) liczba wiadomoœci spe³niaj¹cych kryteria
   */
  #define IMC_MESSAGEWAITING    103
  /**
   * Usuwa wiadomoœci z kolejki.
   * 
   * @param p1 (sMESSAGESELECT*) Rodzaj wiadomoœci do usuniêcia
   * @param p2 (int) Ile maxymalnie usun¹æ
   * @return false gdy siê nie powiedzie
   */
  #define IMC_MESSAGEREMOVE     104
  /**
   * Pobiera pierwsz¹ wiadomoœæ która spe³nia kryteria.
   * 
   * @param p1 (sMESSAGESELECT*) Rodzaj wiadomoœci do pobrania.
   * @param p2 (cMessage*) Struktura do której zostanie zapisana wiadomoœæ.
   * @retrun 1 - jeœli siê powiod³o
   */
  #define IMC_MESSAGEGET        106
  /**
   * Potwierdzenie wys³ania wiadomoœci.
   * W cMessageAck::id @b musimy podaæ ID potwierdzanej wiadomoœci.
   * Ustawienie msg i ext jest opcjonalne.
   *
   * @param p1 (cMessageAck*) Struktura z potwierdzeniem.
   */
  #define IMC_MESSAGEACK        107
  /**
   * Zakoñczenie przetwarzania.
   * Po skoñczeniu przetwarzania wiadomoœci, na któr¹ odpowiedzieliœmy flag¹ IM_MSG_processing
   * wysy³amy ten komunikat, by rdzeñ "odznaczy³" nasz¹ wiadomoœæ. 
   * #IMC_MESSAGEPROCESSED wysy³a siê tylko, gdy wiadomoœæ nie zosta³a od razu usuniêta.
   *
   * @param p1 (int) ID wiadomoœci.
   * @param p2 (bool) true - wiadomoœæ mo¿e zostaæ usuniêta
   */
  #define IMC_MESSAGEPROCESSED  108


  /** 
   * Wtyczka powinna sprawdziæ czy obs³uguje dany typ wiadomoœci.
   * Wtyczki odpytywane s¹ "od koñca". Ostatnia, która zwróci
   * IM_MSG_RCV_ok bêdzie otrzymywaæ równie¿ IM_MSG_OPEN.
   *
   * @param p1 (cMessage *) wiadomoœæ.
   * @param p2 (bool) @e true - wiadomoœæ w³aœnie przysz³a, @e false - wiadomoœæ zosta³a za³adowana z pliku.
   * @return (int) Po³¹czone flagi @ref im_msg_, lub 0 jeœli nie obs³uguje takich wiadomoœci.
   */
  #define IM_MSG_RCV            IM_BASE + 100

  /** 
   * Wiadomoœæ powinna zostaæ wys³ana.
   *
   * @param p1 (cMessage *) Wiadomoœæ
   * @return Jeœli siê uda³o powinno zróciæ @ref im_msg_.
   */
  #define IM_MSG_SEND           IM_SHARE + 100

  /** 
   * Wiadomoœæ powinna zostaæ otwarta.
   *
   * @param p1 (cMessage *) Wiadomoœæ
   * @return Jeœli siê uda³o powinno zróciæ @ref im_msg_.
   */
  #define IM_MSG_OPEN           IM_SHARE + 101
#endif