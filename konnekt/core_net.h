#pragma once



namespace Konnekt {

	/**
      "Sie�" (Net) wtyczki oznacza przynale�no�� do pewnej grupy.
      Na przyk�ad jeden protok� mo�e by� obs�ugiwany przez kilka niezale�nych
      od siebie wtyczek o tej samej warto�ci \a Net. <br> <br>
      Warto�� sieci u�ywana jest przede wszystkim podczas komunikacji
      pomi�dzy wtyczkami. W momencie wys�ania #IMessage , rdze�
      szuka wtyczki o podanej warto�ci \a Net obs�uguj�cej typ wysy�anej
      wiadomo�ci. W ten spos�b , mo�na rozsy�a� w systemie wiadomo�ci
      do \i wtyczek nawet nie wiedz�c o ich istnieniu (a przede wszystkim
      o ich identyfikatorach) ...<br><br>
      Numery sieci gotowych wtyczek b�d� do��czane do SDK...

      \attention \a Net jest typu <b>unsigned int</b> , przy czym
              warto�ci definiowane przez Was powinny by� wi�ksze od @b 255!
			  ale nie wi�ksze ni� 0xFFFF!
			  Warto�ci od 128-255 powinny by� WOLNE
      \sa info imt_ #IM_PLUG_NET
	
@todo Zaktualizowa� :)

	*/
	namespace Net {

		enum tNet {

			first = -2,		///< Komunikat dotrze do pierwszej wtyczki (dowolnej sieci), kt�ra potrafi j� obs�u�y�.
			broadcast = -1, ///< Komunikat dotrze do wtyczek wszystkich sieci.
			all = -1,
		    none = 0,       ///< Wiadomosci do rdzenia.
			core = 0,
			//net = 1,  
			//internal = 2,
			sound = 3,      ///< D�wi�k
			update = 4,     ///< Update
			other = 6,      ///< Wtyczki nie posiadaj�ce akcji, nie obs�uguj�ce wiadomo�ci itp.

			gg = 10,        ///< Wtyczki obs�uguj�ce protok� GG
			icq = 11,       ///< Wtyczki obs�uguj�ce protok� ICQ
			jabber = 12,    ///< Wtyczki obs�uguj�ce protok� JABBER
			email = 13,     ///< Wtyczki obs�uguj�ce EMaile
			sms = 14,       ///< Wtyczki obs�uguj�ce SMSy
			klan = 15,
			kstyle = 16,
			expimp = 17,
			konnferencja = 20,

			aim = 60,       ///< Wtyczki obs�uguj�ce protok� AIM
			yahoo = 61,     ///< Wtyczki obs�uguj�ce protok� YAHOO
			msn = 62,       ///< Wtyczki obs�uguj�ce protok� MSN
			tlen = 63,      ///< Wtyczki obs�uguj�ce protok� TLEN
	 

			ktransfer = 130,///< kTransfer 

			last = 0x0000FFFF,
		};

        /** Klasa broadcast pozwala sterowa� procesem rozsy�ania komunikatu do wielu wtyczek.

		Do f-cji rozsy�aj�cych komunikaty IMessage() opr�cz zwyk�ych warto�ci tNet
		mo�na przekazywa� warto�ci specjalne skonstruowane z pomoc� klasy Broadcast.

		Rozsy�anie komunikat�w dzieli si� na dwa rodzaje:
		- @b broadcast - rozsy�a komunikaty do wszystkich pasuj�cych wtyczek
		- @b first - wysy�a komunikat do pierwszej pasuj�cej wtyczki

		Rozsy�anie mo�na ogranicza� przez (nie mo�na ��czy�!):
		- pozycj� startu tPluginId - okre�laj�c� wtyczk� od kt�rej nale�y zacz�� wyszukiwanie
		- pozycj� startu int - okre�laj�c� po znalezieniu ilu @b pasuj�cych wtyczek ma zacz�� wysy�a� komunikaty (w ten spos�b mo�na zrobi� p�tl� wysy�ania broadcast�w typu @i first, zwi�kszaj�c pozycj� o 1 dop�ki nie pojawi si� b��d nie obs�u�enia komunikatu ( Ctrl::getError() )
		- warto�� tNet - ogranicza wtyczki do jednej warto�ci net

		Rozsy�anie mo�na modyfikowa� przez:
		- flag� odwracaj�c� kolejno�� wyszukiwania...
		- spos�b obs�ugi typu wtyczki (wszystkie flagi musz� by� obecne, dowolna musi by� obecna, �adna nie mo�e by� obecna)

		Zwr�con� warto�� mo�e by�:
		- ostatnio zwr�cona przez wtyczk� (domy�lnie)
		- sum� wszystkich zwr�conych
		- OR wszystkich zwr�conych
		- AND wszystkich zwr�conych


		Warto�� buduje si� przez wywo�ywanie kolejnych f-cji na obiekcie.
		Np. Je�eli chcemy wys�a� komunikat tylko do 3 pasuj�cej wtyczki od ko�ca:
		@code
		IMessage(IM_FOO, Net::Broadcast().setFirst().startOn(3).setReverse(), IMT_BAR);
		@endcode


		*/
		class Broadcast {
		public:

			enum enResult {
				resultLast = 0,
				resultSum = 1,
				resultAnd = 2,
				resultOr = 3,
			};
			enum enType {
				typeBroadcast = 0, 
				typeFirst = 1
			};
			enum enIMType {
				imtypeAll = 0,
				imtypeAny = 1,
				imtypeNot = 2
			};


		public:

			Broadcast() {
				flag = 1;
			}

			/// Konstruuje broadcast na podstawie pe�nej warto�ci net
			Broadcast(tNet net) {
				*this = net;
			}

			Broadcast& operator = (tNet net) {
				if (net == broadcast) {
					value = Net::none;
					flag = 1;
					type = typeBroadcast;
				} else if (net == first) {
					value = Net::none;
					flag = 1;
					type = typeFirst;
				} else {
					value = net;
				}
				return *this;
			}

			operator tNet() const {
				return value;
			}

			bool isBroadcast() const {
				return flag;
			}

			/// Zwraca pe�n� warto�� net
			tNet toNet() const {
				return value;
			}

			inline Broadcast& setBroadcast() {
				this->flag = 1;
				this->type = typeBroadcast;
				return *this;
			}

			inline Broadcast& setFirst() {
				this->flag = 1;
				this->type = typeFirst;
				return *this;
			}
            
			inline Broadcast& startOn(int occurence) {
				this->startType = startOccurence;
				this->start = occurence;
				return *this;
			}

			inline Broadcast& startPlugin(tPluginId plugin) {
				this->startType = startPluginId;
				this->start = plugin;
				return *this;
			}

			inline Broadcast& onlyNet(tNet net) {
				this->startType = startNet;
				this->start = net;
				return *this;
			}

			inline Broadcast& notNet(tNet net) {
				this->startType = startNotNet;
				this->start = net;
				return *this;
			}

			inline Broadcast& setReverse() {
				this->reverse = true;
				return *this;
			}

			inline Broadcast& setIMType(enIMType type) {
				this->imtype = type;
				return *this;
			}

			inline Broadcast& setResult(enResult res) {
				this->result = res;
				return *this;
			}


			bool isReverse() const {
				return reverse;
			}


			enType getType() const {
				return type;
			}

			enIMType getIMType() const {
				return imtype;
			}

			tNet getOnlyNet() const {
				return (startType == startNet) ? (tNet)start : Net::all;
			}

			tNet getNotNet() const {
				return (startType == startNotNet) ? (tNet)start : Net::all;
			}

			int getStartOccurence() const {
				return (startType == startOccurence) ? start : 0;
			}

			tPluginId getStartPlugin() const {
				return (startType == startPluginId) ? (tPluginId)start : (tPluginId)0;
			}

			enResult getResultType() const {
				return result;
			}


		private:

			enum enStart {
				startOccurence = 0,
				startPluginId = 1,
				startNet = 2,
				startNotNet = 3,
			};

			union {

				tNet value;

				struct {
					unsigned start:32;
					unsigned _fill:19;
					enIMType imtype:2;
					unsigned reverse:1;
					enResult result:3;
					enStart startType:3;
					enType type:3;
					unsigned flag:1; // oznacza czy w og�le jest to broadcast
				};

			};

		};

		typedef Broadcast BC;


	};

	using Net::tNet;

};


