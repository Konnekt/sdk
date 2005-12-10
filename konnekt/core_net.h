#pragma once



namespace Konnekt {

	/**
      "Sieæ" (Net) wtyczki oznacza przynale¿noœæ do pewnej grupy.
      Na przyk³ad jeden protokó³ mo¿e byæ obs³ugiwany przez kilka niezale¿nych
      od siebie wtyczek o tej samej wartoœci \a Net. <br> <br>
      Wartoœæ sieci u¿ywana jest przede wszystkim podczas komunikacji
      pomiêdzy wtyczkami. W momencie wys³ania #IMessage , rdzeñ
      szuka wtyczki o podanej wartoœci \a Net obs³uguj¹cej typ wysy³anej
      wiadomoœci. W ten sposób , mo¿na rozsy³aæ w systemie wiadomoœci
      do \i wtyczek nawet nie wiedz¹c o ich istnieniu (a przede wszystkim
      o ich identyfikatorach) ...<br><br>
      Numery sieci gotowych wtyczek bêd¹ do³¹czane do SDK...

      \attention \a Net jest typu <b>unsigned int</b> , przy czym
              wartoœci definiowane przez Was powinny byæ wiêksze od @b 255!
			  ale nie wiêksze ni¿ 0xFFFF!
			  Wartoœci od 128-255 powinny byæ WOLNE
      \sa info imt_ #IM_PLUG_NET
	
@todo Zaktualizowaæ :)

	*/
	namespace Net {

		enum tNet {

			first = -2,		///< Komunikat dotrze do pierwszej wtyczki (dowolnej sieci), która potrafi j¹ obs³u¿yæ.
			broadcast = -1, ///< Komunikat dotrze do wtyczek wszystkich sieci.
			all = -1,
		    none = 0,       ///< Wiadomosci do rdzenia.
			core = 0,
			//net = 1,  
			//internal = 2,
			sound = 3,      ///< DŸwiêk
			update = 4,     ///< Update
			other = 6,      ///< Wtyczki nie posiadaj¹ce akcji, nie obs³uguj¹ce wiadomoœci itp.

			gg = 10,        ///< Wtyczki obs³uguj¹ce protokó³ GG
			icq = 11,       ///< Wtyczki obs³uguj¹ce protokó³ ICQ
			jabber = 12,    ///< Wtyczki obs³uguj¹ce protokó³ JABBER
			email = 13,     ///< Wtyczki obs³uguj¹ce EMaile
			sms = 14,       ///< Wtyczki obs³uguj¹ce SMSy
			klan = 15,
			kstyle = 16,
			expimp = 17,
			konnferencja = 20,

			aim = 60,       ///< Wtyczki obs³uguj¹ce protokó³ AIM
			yahoo = 61,     ///< Wtyczki obs³uguj¹ce protokó³ YAHOO
			msn = 62,       ///< Wtyczki obs³uguj¹ce protokó³ MSN
			tlen = 63,      ///< Wtyczki obs³uguj¹ce protokó³ TLEN
	 

			ktransfer = 130,///< kTransfer 

			last = 0x0000FFFF,
		};

        /** Klasa broadcast pozwala sterowaæ procesem rozsy³ania komunikatu do wielu wtyczek.

		Do f-cji rozsy³aj¹cych komunikaty IMessage() oprócz zwyk³ych wartoœci tNet
		mo¿na przekazywaæ wartoœci specjalne skonstruowane z pomoc¹ klasy Broadcast.

		Rozsy³anie komunikatów dzieli siê na dwa rodzaje:
		- @b broadcast - rozsy³a komunikaty do wszystkich pasuj¹cych wtyczek
		- @b first - wysy³a komunikat do pierwszej pasuj¹cej wtyczki

		Rozsy³anie mo¿na ograniczaæ przez (nie mo¿na ³¹czyæ!):
		- pozycjê startu tPluginId - okreœlaj¹c¹ wtyczkê od której nale¿y zacz¹æ wyszukiwanie
		- pozycjê startu int - okreœlaj¹c¹ po znalezieniu ilu @b pasuj¹cych wtyczek ma zacz¹æ wysy³aæ komunikaty (w ten sposób mo¿na zrobiæ pêtlê wysy³ania broadcastów typu @i first, zwiêkszaj¹c pozycjê o 1 dopóki nie pojawi siê b³¹d nie obs³u¿enia komunikatu ( Ctrl::getError() )
		- wartoœæ tNet - ogranicza wtyczki do jednej wartoœci net

		Rozsy³anie mo¿na modyfikowaæ przez:
		- flagê odwracaj¹c¹ kolejnoœæ wyszukiwania...
		- sposób obs³ugi typu wtyczki (wszystkie flagi musz¹ byæ obecne, dowolna musi byæ obecna, ¿adna nie mo¿e byæ obecna)

		Zwrócon¹ wartoœæ mo¿e byæ:
		- ostatnio zwrócona przez wtyczkê (domyœlnie)
		- sum¹ wszystkich zwróconych
		- OR wszystkich zwróconych
		- AND wszystkich zwróconych


		Wartoœæ buduje siê przez wywo³ywanie kolejnych f-cji na obiekcie.
		Np. Je¿eli chcemy wys³aæ komunikat tylko do 3 pasuj¹cej wtyczki od koñca:
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

			/// Konstruuje broadcast na podstawie pe³nej wartoœci net
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

			/// Zwraca pe³n¹ wartoœæ net
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
					unsigned flag:1; // oznacza czy w ogóle jest to broadcast
				};

			};

		};

		typedef Broadcast BC;


	};

	using Net::tNet;

};


