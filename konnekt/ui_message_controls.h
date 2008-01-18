/*
  nazwa="UI message controls"
  info="Nag³ówek do obs³ugi kontrolek w oknach wiadomoœci i historii"
*/

/** \file
    Nag³ówek do obs³ugi kontrolek w oknach wiadomoœci i historii.

  W wersji UI 0.1.18 kontrolki obs³uguj¹ce okno wiadomoœci i historiê
  zosta³y zmienione tak, aby by³o mo¿liwe ich zast¹pienie.
  Obie akcje uznawane s¹ z góry za akcje typu #ACTT_HWND, niezale¿nie
  od ustawionego stylu. Za pozycjonowanie i rozmiar okna odpowiada
  sam interfejs. Komunikacja z interfejsem odbywa siê poprzez
  specjalne komunikaty akcji opisane w tym pliku...
  Jedynym stylem (nowym w tym UI), który dobrze by by³o dodaæ 
  jest #ACTR_SETCNT.
  W programie mo¿na podmieniæ 3 kontrolki, usuwaj¹c istniej¹ce
  przez #IMI_ACTION_REMOVE i tworz¹c w ich miejsce nowe o tym
  samym identyfikatorze...
  W oknie rozmowy:
  sUIAction(IMIG_MSGWND, konnekt::UI::act::msg_ctrlview)  -  podgl¹d rozmowy
  sUIAction(IMIG_MSGWND, konnekt::UI::act::msg_ctrlsend)  -  wpisywanie treœci
  W oknie historii:
  sUIAction(IMIG_HISTORYWND, konnekt::UI::act::msg_ctrlview)  -  podgl¹d rozmowy

  Uk³ad namespace'ów i nazwy sta³ych i klas mo¿e siê jeszcze zmieniæ!
*/

namespace Konnekt {
  namespace UI {
    namespace ACT {
      const int msg_ctrlview = 250; ///< Kontrolka, w której pojawiaj¹ siê wiadomoœci
      const int msg_ctrlsend = 251; ///< Kontrolka, z której wiadomoœci s¹ wysy³ane
      const int msg_ctrlsend_menu = 260; ///< Menu msg_ctrlsend
      const int msg_ctrlsend_menu_copy = 261;
      const int msg_ctrlsend_menu_paste = 262;
      const int msg_ctrlsend_menu_paste_nf = 263;
      const int msg_ctrlsend_menu_paste_qt = 264;
      const int msg_ctrlsend_menu_select = 265;
      const int msg_ctrlsend_menu_cut = 266;
      const int msg_ctrlsend_menu_delete = 267;
      const int msg_ctrlsend_menu_undo = 268;
      const int msg_ctrlsend_menu_redo = 269;
      const int msg_ctrlsend_menu_hist_previous = 270;
      const int msg_ctrlsend_menu_hist_next = 271;
      const int msg_ctrlsend_menu_hist_clear = 272;
    };

    namespace Notify {
      // kontrolka do wyœwietlania
      const int lock = 300;  ///< Odœwie¿anie okna powinno byæ zablokowane
      const int unlock = 301; ///< Odœwie¿anie okna powinno byæ przywrócone
      const int clear = 302; ///< Okno powinno byæ wyczyszczone
      const int insertMsg = 310; ///< Trzeba wstawiæ wiadomoœæ (_insertMsg *)
      const int insertStatus = 311;  ///< Trzeba wstawiæ info o zmianie statusu (_insertStatus *)

      // kontrolka do wpisywania
      const int getMessage = 312;  ///< Trzeba wstawiæ treœæ wpisanej wiadomoœci (dla kontrolek do pisania treœci)
      const int getMessageSize = 313;  /**< Trzeba zwróciæ rozmiar wpisanej wiadomoœci.*/

      const int getSelection = 314;  ///< Trzeba zwróciæ aktualne zaznaczenie (_getSelection *).
      const int getMessageLines = 315;  /**< Trzeba zwróciæ liczbê linijek w wiadomoœci.*/
      const int getMessageLine = 316;  /**< Trzeba zwróciæ numer linii, w której znajduje siê znak.
                                            @param notify1 (int)numer znaku
                                           */
      const int supportsFormatting = 317;  ///< Czy kontrolka (wpisywania) obs³uguje formatowanie
      const int setSelection = 318;  ///< Ustawia aktualne zaznaczenie (_setSelection *).
      const int insertText = 319;  ///< Ustawia aktualne zaznaczenie (_insertText *).

      class _insertMsg: public sUIActionNotify_base {
      public:
        cMessage * _message; ///< Wiadomoœæ do wyœwietlenia
        const char * _display; ///< Nazwa kontaktu jako autora (je¿eli "" - to na podstawie wiadomoœci)
        bool _scroll; ///< Czy przewin¹æ ekran do dodanej wiadomoœci

        _insertMsg(cMessage * message, const char * display, bool scroll): _message(message), _display(display), _scroll(scroll) {
          code = insertMsg;
          s_size = sizeof(*this);
        }
      };

      class _insertStatus: public sUIActionNotify_base {
      public:
        int _status; ///< Status
        const char * _info; ///< Opis

        _insertStatus(int status, const char * info): _status(status), _info(info) {
          code = insertStatus; s_size = sizeof(*this);
        }
      };

      class _getMessage: public sUIActionNotify_base {
      public:
        cMessage * _message; ///< Wiadomoœæ do wyœwietlenia. cMessage::body trzyma wskaŸnik do bufora, którego rozmiar zosta³ ustawiony w getMessageSize
        int _size;

        _getMessage(cMessage * message, int size): _message(message),_size(size) {
          code = getMessage; s_size = sizeof(*this);
        }
      };

      class _getSelection: public sUIActionNotify_base {
      public:
        int _start; ///< Pocz¹tek zaznaczenia
        int _end; ///< Koniec zaznaczenia.

        _getSelection(): sUIActionNotify_base(getSelection), _start(0), _end(0) {
          s_size = sizeof(*this);
        }
      };
      typedef _getSelection _setSelection;

      class _insertText: public sUIActionNotify_base {
      public:
        const char * _text; ///< Treœæ do wstawienia/zast¹pienia
        bool _isHtml; ///< Czy jest formatowana?
        int _position; ///< Miejsce do wklejenia. -1 - aktualna pozycja/zaznaczenie

        _insertText(): sUIActionNotify_base(insertText), _text(""), _isHtml(false), _position(-1) {
          s_size = sizeof(*this);
        }
      };
    };
  };
};

#pragma once