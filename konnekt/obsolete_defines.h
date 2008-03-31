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

#define NET_FIRST         Net::first         ///< Wiadomo�� dotrze do pierwszej wtyczki (dowolnej sieci), kt�ra potrafi j� obs�u�y�.
#define NET_BROADCAST     Net::broadcast     ///< Wiadomo�� dotrze do wtyczek wszystkich sieci.
#define NET_BC            NET_BROADCAST      ///< Odpowiednik #NET_BROADCAST.
#define NET_NONE          Net::none          ///< Wiadomosci do rdzenia.

#define NET_SOUND         Net::sound         ///< D�wi�k
#define NET_UPDATE        Net::update        ///< Update
#define NET_OTHER         Net::other         ///< Wtyczki nie posiadaj�ce akcji, nie obs�uguj�ce wiadomo�ci itp.

#define NET_GG            Net::gg            ///< Wtyczki obs�uguj�ce protok� GG
#define NET_ICQ           Net::icq           ///< Wtyczki obs�uguj�ce protok� ICQ
#define NET_JABBER        Net::jabber        ///< Wtyczki obs�uguj�ce protok� JABBER
#define NET_EMAIL         Net::email         ///< Wtyczki obs�uguj�ce EMaile
#define NET_SMS           Net::sms           ///< Wtyczki obs�uguj�ce SMSy
#define NET_KLAN          Net::klan 
#define NET_KSTYLE        Net::kstyle
#define NET_EXPIMP        Net::expimp
#define NET_KONNFERENCJA  Net::konnferencja

#define NET_AIM           Net::aim           ///< Wtyczki obs�uguj�ce protok� AIM
#define NET_YAHOO         Net::yahoo         ///< Wtyczki obs�uguj�ce protok� YAHOO
#define NET_MSN           Net::msn           ///< Wtyczki obs�uguj�ce protok� MSN
#define NET_TLEN          Net::tlen          ///< Wtyczki obs�uguj�ce protok� TLEN

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
 * Wiadomo�� bezpo�rednio do rdzenia (lub UI).
 */
#define IMT_CORE        Konnekt::imtCore

/**
 * Wiadomo�ci tekstowe.
 */
#define IMT_MESSAGE     Konnekt::imtMessage
/**
 * Protok� sieciowy.
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
 * Interfejs U�ytkownika (u�ywanie wtyczki UI).
 */
#define IMT_UI          Konnekt::imtUI
/** 
 * Wtyczka obs�uguje kontakty ca�ej swojej sieci.
 *
 * @attention Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
 * do list sieci w opcjach kontaktu (np. dodawanie, ignorowanie itp.)
 * Tylko @b jedna wtyczka z ca�ej sieci mo�e mie� ten typ ustawiony!!!
 * @sa #IM_PLUG_NETNAME @ref cnt
 */
#define IMT_NET         Konnekt::imtNet  // Rozpoznaje kontakty danej sieci (podczas dodawania, edycji)
/** 
 * Wtyczka obs�uguje wyszukiwanie kontakt�w w swojej sieci.
 * @attention Podobnie jak w #IMT_UI Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
 * do list sieci w wyszukiwarce kontakt�w
 * Tylko @b jedna wtyczka z ca�ej sieci mo�e mie� ten typ ustawiony!!!
 * @sa #IM_PLUG_NETNAME @ref cnt
 */
#define IMT_NETSEARCH   Konnekt::imtNetSearch
/**
 * Wtyczka wykorzystuje system obs�ugi wiadomo�ci tekstowych zawarty w UI.
 */
#define IMT_MSGUI       Konnekt::imtMsgUI
/**
 * Kontakty w sieci posiadaj� UID (UserID)
 */
#define IMT_NETUID      Konnekt::imtNetUID
/**
 * Otrzyma w IM_MSG_RCV wszystkie wiadomo�ci, niezale�nie od @ref net_ "NET".
 */
#define IMT_ALLMESSAGES Konnekt::imtAllMessages
/**
 * B�dzie otrzymywa� IM_MSG_ACK.
 */
#define IMT_MESSAGEACK Konnekt::imtMessageAck

/** @} */ // imt_

typedef enPluginPriority PLUGP_enum;

/** 
 * Grupy priorytet�w dla #IM_PLUG_PRIORITY 
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
#define IMERROR_NORESULT Konnekt::errorNoResult     ///< Wtyczka nie obs�u�y�a wiadomo�ci.
#define IMERROR_UNSUPPORTEDMSG IMERROR_NORESULT     ///< Wtyczka nie obs�u�y�a wiadomo�ci.
#define IMERROR_BADSENDER Konnekt::errorBadSender   ///< Wiadomo�� wstrzymana, pojawi� si� b��d...
#define IMERROR_BADPLUG Konnekt::errorBadPlugin     ///< Podana wtyczka nie istnieje.
#define IMERROR_THREADSAFE Konnekt::errorThreadSafe ///< Wiadomo�� zosta�a wywo�ana w trybie bezpiecznym (bez oczekiwania na powr�t).
#define IMERROR_SHUTDOWN Konnekt::errorShutdown     ///< Wiadomo�� zosta�a anulowana z powodu zamykania programu.
#define IMERROR_BADPARAM Konnekt::errorBadParam     ///< Nieprawid�owe parametry.
#define IMERROR_BADSTRUCT Konnekt::errorBadStruct   ///< Niepoprawna struktura.

/** @} */ // imerror_

/**
 * @defgroup cnt_ Tabela Kontakt�w
 * @{
 */

#define CNT_UID             ((unsigned int) 0)  ///< #ctypeString UID.
#define CNT_NET             1                   ///< #ctypeInt Sie�.
#define CNT_STATUS          2                   ///< #ctypeInt Status.
#define CNT_STATUSINFO      18                  ///< #ctypeString Opis statusu.
#define CNT_NOTIFY          3                   ///< #ctypeInt | #cflagNoSave Ikonka powiadomienia.
#define CNT_HOST            4                   ///< #ctypeString | #cflagNoSave IP.
#define CNT_PORT            5                   ///< #ctypeInt | #cflagNoSave Port.
#define CNT_NAME            6                   ///< #ctypeString Imi�.
#define CNT_SURNAME         7                   ///< #ctypeString Nazwisko.
#define CNT_NICK            17                  ///< #ctypeString Pseudo.
#define CNT_DISPLAY         8                   ///< #ctypeString Nazwa wy�wietlana.
#define CNT_CELLPHONE       9                   ///< #ctypeString Kom�rka.
#define CNT_PHONE           10                  ///< #ctypeString Stacjonarny.
#define CNT_EMAIL           11                  ///< #ctypeString Email.
#define CNT_INFO            12                  ///< #ctypeString Info.
#define CNT_LOCALITY        13                  ///< #ctypeString Miejscowo��.
#define CNT_CITY            CNT_LOCALITY
#define CNT_COUNTRY         14                  ///< #ctypeString Kraj
#define CNT_BORN            19                  ///< #ctypeInt Urodzony YYYYMMDD (w hexie)
#define CNT_GENDER          20                  ///< #ctypeInt P�e� @ref gender_
#define CNT_CLIENT          15                  ///< #ctypeString Nazwa i wersja u�ywanego softu.
#define CNT_CLIENTVERSION   28                  ///< #ctypeInt Wersja Softu
#define CNT_LASTMSG         16                  ///< #ctypeInt | #cflagNoSave ID ostatniej wiadomo�ci.
#define CNT_GROUP           21                  ///< #ctypeString Grupa do kt�rej nale�y.
#define CNT_ACT_PARENT      22                  ///< #ctypeInt | #cflagNoSave Parent akcji powiadomienia.
#define CNT_ACT_ID          23                  ///< #ctypeInt | #cflagNoSave ID akcji powiadomienia.
#define CNT_INTERNAL        24                  ///< @internal
#define CNT_STREET          25                  ///< #ctypeString - ulica.
#define CNT_POSTALCODE      26                  ///< #ctypeString - kod pocztowy.
#define CNT_NOTIFY_MSG      27                  ///< #ctypeInt | #cflagNoSave ID wiadomo�ci powiadomienia.
#define CNT_LASTACTIVITY    29                  ///< #ctypeInt64 Czas ostatniej aktywno�ci.
#define CNT_STATUS_ICON     30                  ///< #ctypeInt Identyfikator ikonki, kt�ra ma zast�pi� ikon� statusu.


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
 * @defgroup gender_ Oznaczenie p�ci
 * @{
 */

#define GENDER_UNKNOWN  0 ///< Nieznana
#define GENDER_FEMALE   1 ///< Kobieta
#define GENDER_MALE     2 ///< M�czyzna

/** @} */ // gender_


/*
#define MT_MESSAGE      1    ///< Zwyk�a wiadomo��.
#define MT_QUICKEVENT   2    ///< Kr�tka notka (kasowana automatycznie w kolejce) (np. wiadomo�� nie dosz�a itp.)
#define MT_CNTEVENT     3    ///< wydarzenie (np. kto� mnie doda� do swojej listy itp.) zwi�zane z kontaktem na li�cie
#define MT_EVENT        (MT_CNTEVENT | MT_MASK_NOTONLIST)   ///< wydarzenie (np. kto� mnie doda� do swojej listy itp.)
#define MT_SERVEREVENT  (4 | MT_MASK_NOTONLIST)             ///< Wiadomo�� od serwera.
#define MT_AUTHORIZE    5    ///< Pro�ba o autoryzacje (ICQ).
#define MT_CONFERENCE   6    ///< Wiadomo�� konferencyjna.
#define MT_FILE         7    ///< Przes�anie pliku.
#define MT_MAIL         8    ///< Email.
#define MT_SMS          9    ///< Np. potwierdzenie dotarcia sms'�w.
#define MT_SOUND        10   ///< Rozmowa g�osowa.
#define MT_URL          (11 | MT_MASK_NOTONLIST)    ///< URL. 
                                                    ///< Jako dodatkowe parametry w ext przyjmuje Width i Heigth
#define MT_SPECIAL      12   ///< Nieokreslona wiadomosc.
#define MT_SPECIAL_NOL  (13 | MT_MASK_NOTONLIST)    ///< Nieokreslona wiadomosc spoza listy.
#define MT_IMAGE        15   ///< Obraz, sciezka do pliku w cMessage::ext - #MEX_FILE_PATH

#define MT_BOARD        16 

#define MT_MASK_NOTONLIST 0x1000  ///< Oznacza �e ta wiadomosc nie zostanie
                                  ///  wy�wietlona na liscie, ani nie zostanie
                                  ///  sprawdzone czy docelowy kontakt na li�cie
                                  ///  si� znajduje
#define MT_MASK         0xFFF     ///< Maskuje bity odpowiedzialne za sam typ wiadomo�ci.
*/

#ifdef KONNEKT_OBSOLETE_ALL
  /**
   * @defgroup mf_ flagi wiadomo�ci tekstowych
   * @{
  */
  #define MF_SEND         2           ///< Wiadomo�� przeznaczona do wys�ania
  #define MF_NOEVENTS     4           ///< #MT_QUICKEVENT maj� nie by� wysy�ane
  #define MF_NOSAVE       8           ///< Wiadomo�� nie zostanie zapisana na dysk ...
  /**
   * @brief #IM_MSG_OPEN / #IM_MSG_SEND zostanie wys�ane z #IMC_MESSSAGEQUEUE tylko
   * gdy zostanie ono wywo�ane dla tego typu i sieci wiadomo�ci.
   */
  #define MF_REQUESTOPEN  0x10
  #define MF_PROCESSING   0x20        ///< Flaga wewn�trzna oznaczaj�ca �e wiadomo�� jest w trakcie przetwarzania, Nie powinna by� u�ywana!
  /**
   * Wiadomo�� ju� zosta�a otwarta. Teraz czeka w kolejce na usuni�cie.
   * Flaga ta jest czyszczona podczas zamykania.
   */
  #define MF_OPENED       0x40
  #define MF_HANDLEDBYUI  0x80        ///< Wiadomo�� zostanie obs�u�ona przez UI
  /**
   * Wiadomo�� zosta�a stworzona przez jaki� "automatyczny"
   * proces, wi�c, gdy jeste�my ukryci, nie powinna by� wysy�ana.
   */
  #define MF_AUTOMATED    0x100
  /**
   * Tre�� wiadomo�ci zawiera znaczniki HTML, a znaki specjalne s� kodowane (przynajmniej > = &gt; < = &lt; i " = &quot;
   * Html powinien by� sformatowany jak XHTML (<img/>, wszystkie atrybuty w "" itd..)
   */
  #define MF_HTML         0x200
  /**
   * Interfejs obs�u�y wy�wietlanie wiadomo�ci w menu.
   * Za ikonk� pos�u�y cMessage::notify, nazw� pozycji w menu ustawiamy
   * w Ext jako parametr "ActionTitle". Je�eli ustawiona jest cMessage::action
   * zostanie ona wys�ana po otwarciu wiadomo�ci. W przeciwnym razie zostanie
   * wywo�ane IM_MSG_OPEN.
   * Wtyczka musi w #IM_MSG_RCV zadeklarowa� obs�ug� wiadomo�ci.
   */
  #define MF_MENUBYUI     0x400 
  #define MF_LEAVEASIS    0x800       ///< Zabrania wtyczkom zmiany tre�ci, w tym wy�wietlania emotikon
  #define MF_HIDE         0x1000      ///< Nie wy�wietla wiadomo�ci w interfejsie (w tej chwili w oknie rozmowy)
  #define MF_DONTADDTOHISTORY 0x2000  ///< Nie zapisuje w historii
  
  #define MF_QE_NORMAL    0x10000     ///< MT_QUICKEVENT narysuje zwyk�� czcionk�...
  #define MF_QE_SHOWTIME  0x20000     ///< MT_QUICKEVENT poka�e czas nadej�cia...

  /** @} */ // mf_
#endif

/** @} */

#ifdef KONNEKT_OBSOLETE_MESSAGE
  #define IMC_NEWMESSAGE Message::imcNewMessage

  #define IMC_MESSAGEQUEUE imcMessageQueue 
  #define IMC_MESSAGENOTIFY  
  /**
   * @param p1 (sMESSAGESELECT*) kt�re wiadomo�ci maj� zosta� uwzgl�dnione
   * @return (int) liczba wiadomo�ci spe�niaj�cych kryteria
   */
  #define IMC_MESSAGEWAITING    103
  /**
   * Usuwa wiadomo�ci z kolejki.
   * 
   * @param p1 (sMESSAGESELECT*) Rodzaj wiadomo�ci do usuni�cia
   * @param p2 (int) Ile maxymalnie usun��
   * @return false gdy si� nie powiedzie
   */
  #define IMC_MESSAGEREMOVE     104
  /**
   * Pobiera pierwsz� wiadomo�� kt�ra spe�nia kryteria.
   * 
   * @param p1 (sMESSAGESELECT*) Rodzaj wiadomo�ci do pobrania.
   * @param p2 (cMessage*) Struktura do kt�rej zostanie zapisana wiadomo��.
   * @retrun 1 - je�li si� powiod�o
   */
  #define IMC_MESSAGEGET        106
  /**
   * Potwierdzenie wys�ania wiadomo�ci.
   * W cMessageAck::id @b musimy poda� ID potwierdzanej wiadomo�ci.
   * Ustawienie msg i ext jest opcjonalne.
   *
   * @param p1 (cMessageAck*) Struktura z potwierdzeniem.
   */
  #define IMC_MESSAGEACK        107
  /**
   * Zako�czenie przetwarzania.
   * Po sko�czeniu przetwarzania wiadomo�ci, na kt�r� odpowiedzieli�my flag� IM_MSG_processing
   * wysy�amy ten komunikat, by rdze� "odznaczy�" nasz� wiadomo��. 
   * #IMC_MESSAGEPROCESSED wysy�a si� tylko, gdy wiadomo�� nie zosta�a od razu usuni�ta.
   *
   * @param p1 (int) ID wiadomo�ci.
   * @param p2 (bool) true - wiadomo�� mo�e zosta� usuni�ta
   */
  #define IMC_MESSAGEPROCESSED  108


  /** 
   * Wtyczka powinna sprawdzi� czy obs�uguje dany typ wiadomo�ci.
   * Wtyczki odpytywane s� "od ko�ca". Ostatnia, kt�ra zwr�ci
   * IM_MSG_RCV_ok b�dzie otrzymywa� r�wnie� IM_MSG_OPEN.
   *
   * @param p1 (cMessage *) wiadomo��.
   * @param p2 (bool) @e true - wiadomo�� w�a�nie przysz�a, @e false - wiadomo�� zosta�a za�adowana z pliku.
   * @return (int) Po��czone flagi @ref im_msg_, lub 0 je�li nie obs�uguje takich wiadomo�ci.
   */
  #define IM_MSG_RCV            IM_BASE + 100

  /** 
   * Wiadomo�� powinna zosta� wys�ana.
   *
   * @param p1 (cMessage *) Wiadomo��
   * @return Je�li si� uda�o powinno zr�ci� @ref im_msg_.
   */
  #define IM_MSG_SEND           IM_SHARE + 100

  /** 
   * Wiadomo�� powinna zosta� otwarta.
   *
   * @param p1 (cMessage *) Wiadomo��
   * @return Je�li si� uda�o powinno zr�ci� @ref im_msg_.
   */
  #define IM_MSG_OPEN           IM_SHARE + 101
#endif