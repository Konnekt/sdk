/*
  nazwa="UI message controls"
  info="Nag��wek do obs�ugi kontrolek w oknach wiadomo�ci i historii"
*/

/** \file
    Nag��wek do obs�ugi kontrolek w oknach wiadomo�ci i historii.

  W wersji UI 0.1.18 kontrolki obs�uguj�ce okno wiadomo�ci i histori�
  zosta�y zmienione tak, aby by�o mo�liwe ich zast�pienie.
  Obie akcje uznawane s� z g�ry za akcje typu #ACTT_HWND, niezale�nie
  od ustawionego stylu. Za pozycjonowanie i rozmiar okna odpowiada
  sam interfejs. Komunikacja z interfejsem odbywa si� poprzez
  specjalne komunikaty akcji opisane w tym pliku...
  Jedynym stylem (nowym w tym UI), kt�ry dobrze by by�o doda� 
  jest #ACTR_SETCNT.
  W programie mo�na podmieni� 3 kontrolki, usuwaj�c istniej�ce
  przez #IMI_ACTION_REMOVE i tworz�c w ich miejsce nowe o tym
  samym identyfikatorze...
  W oknie rozmowy:
  sUIAction(IMIG_MSGWND, konnekt::UI::act::msg_ctrlview)  -  podgl�d rozmowy
  sUIAction(IMIG_MSGWND, konnekt::UI::act::msg_ctrlsend)  -  wpisywanie tre�ci
  W oknie historii:
  sUIAction(IMIG_HISTORYWND, konnekt::UI::act::msg_ctrlview)  -  podgl�d rozmowy

  Uk�ad namespace'�w i nazwy sta�ych i klas mo�e si� jeszcze zmieni�!
*/

namespace Konnekt {
  namespace UI {
    namespace ACT {
      const int msg_ctrlview = 250; ///< Kontrolka, w kt�rej pojawiaj� si� wiadomo�ci
      const int msg_ctrlsend = 251; ///< Kontrolka, z kt�rej wiadomo�ci s� wysy�ane
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
      // kontrolka do wy�wietlania
      const int lock = 300;  ///< Od�wie�anie okna powinno by� zablokowane
      const int unlock = 301; ///< Od�wie�anie okna powinno by� przywr�cone
      const int clear = 302; ///< Okno powinno by� wyczyszczone
      const int insertMsg = 310; ///< Trzeba wstawi� wiadomo�� (_insertMsg *)
      const int insertStatus = 311;  ///< Trzeba wstawi� info o zmianie statusu (_insertStatus *)

      // kontrolka do wpisywania
      const int getMessage = 312;  ///< Trzeba wstawi� tre�� wpisanej wiadomo�ci (dla kontrolek do pisania tre�ci)
      const int getMessageSize = 313;  /**< Trzeba zwr�ci� rozmiar wpisanej wiadomo�ci.*/

      const int getSelection = 314;  ///< Trzeba zwr�ci� aktualne zaznaczenie (_getSelection *).
      const int getMessageLines = 315;  /**< Trzeba zwr�ci� liczb� linijek w wiadomo�ci.*/
      const int getMessageLine = 316;  /**< Trzeba zwr�ci� numer linii, w kt�rej znajduje si� znak.
                                            @param notify1 (int)numer znaku
                                           */
      const int supportsFormatting = 317;  ///< Czy kontrolka (wpisywania) obs�uguje formatowanie
      const int setSelection = 318;  ///< Ustawia aktualne zaznaczenie (_setSelection *).
      const int insertText = 319;  ///< Ustawia aktualne zaznaczenie (_insertText *).

      class _insertMsg: public sUIActionNotify_base {
      public:
        cMessage * _message; ///< Wiadomo�� do wy�wietlenia
        const char * _display; ///< Nazwa kontaktu jako autora (je�eli "" - to na podstawie wiadomo�ci)
        bool _scroll; ///< Czy przewin�� ekran do dodanej wiadomo�ci

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
        cMessage * _message; ///< Wiadomo�� do wy�wietlenia. cMessage::body trzyma wska�nik do bufora, kt�rego rozmiar zosta� ustawiony w getMessageSize
        int _size;

        _getMessage(cMessage * message, int size): _message(message),_size(size) {
          code = getMessage; s_size = sizeof(*this);
        }
      };

      class _getSelection: public sUIActionNotify_base {
      public:
        int _start; ///< Pocz�tek zaznaczenia
        int _end; ///< Koniec zaznaczenia.

        _getSelection(): sUIActionNotify_base(getSelection), _start(0), _end(0) {
          s_size = sizeof(*this);
        }
      };
      typedef _getSelection _setSelection;

      class _insertText: public sUIActionNotify_base {
      public:
        const char * _text; ///< Tre�� do wstawienia/zast�pienia
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