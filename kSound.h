/*
  nazwa="kSound API"
  data="2003-05-13"
  ver=""
  info="Nag��wek wtyczki kSound."
*/
/** @file Nag��wek wtyczki kSound


*/
/** @defgroup SOUND_shared_h Wtyczka kSound.dll.

 kSound odpowiada za odtwarzanie d�wi�k�w. 
 Przy pomocy kSound::SoundRegister() mo�na doda�
 nowy d�wi�k do listy, a nast�pnie go odtworzy� przez
 kSound::SoundPlay().

 @warning kSound::SoundRegister() mo�e by� wywo�any @b tylko
  w momencie otrzymania przez wtyczk� komunikatu
  kSound::DOREGISTER .
  DOREGISTER wywo�ywane jest dwukrotnie. Podczas rejestrowania kolumn i tworzenia
  interfejsu.
  Za ka�dym razem trzeba zarejestrowa� TE SAME d�wi�ki!

 Kolumny w konfiguracji nazywane s� jako "SOUND_" + nazwa_d�wi�ku.
 Akcje w konfiguracji maj� identyfikatory (@a id - ID kolumny z d�wi�kiem):
   kSound::action::Check | id - Checkbox
   kSound::action::Value | id - Warto��
   kSound::action::Play | id - Play/Stop
 @{
*/
namespace kSound {
	const int REGISTER = IM_USER + 3000;
	const int PLAY = IM_USER + 3001;
	const int DOREGISTER = IM_USER + 3002;
	/** Struktura do wys�ania razem z kSound::SOUND_REGISTER
	*/
	class sIMessage_SoundRegister: public sIMessage_base {
	public:
		int colID; ///< konkretny identyfikator kolumny, lub -1
		const char * name; ///< Jednoznaczna nazwa d�wi�ku (nazwa kolumny w konfiguracji i pola w XMLu)
		const char * info; ///< Informacja przy polu w konfiguracji.
		int flags; ///< Flagi kSound::flags .
		sIMessage_SoundRegister(const char * name , const char * info , int flags = 0 , int colID = -1):sIMessage_base(REGISTER) , colID(colID),name(name),info(info),flags(flags) {
			s_size = sizeof(*this);
			net = NET_SOUND;
			type = IMT_CONFIG;
		}
	};
	namespace flags {
		const char contacts=1; ///< Dla ka�dego kontaktu przechowywane jest osobne ustawienie.
		const char no_column_register=2; ///< kSound nie zarejestruje kolumny w konfiguracji.
		const char no_action_register=4; ///< kSound nie utworzy akcji...
	};
	namespace action {
		const int Check = 0x1A000000;
		const int Play =  0x1B000000;
		const int Value = 0x1C000000;
		const int mute = NET_SOUND * 1000 + 20;
	};
	namespace Cfg {
		const int mute = NET_SOUND * 1000 + 1;
	};
	/** Rejestruje d�wi�k. */
	inline void SoundRegister(cCtrl * Ctrl , const char * name , const char * info , int flags = 0 , int colID=-1) {
		sIMessage_SoundRegister sr(name , info , flags , colID);
		Ctrl->IMessage(&sr);
	}
	/** Odgrywa d�wi�k */
	inline void SoundPlay(cCtrl * Ctrl , const char * name , int cntID=0) {
		Ctrl->IMessage(&sIMessage_2params(PLAY , NET_SOUND , IMT_CONFIG , (int)name , cntID));
	}
};


/// @}