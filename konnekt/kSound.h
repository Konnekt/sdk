/** 
 * @file 
 * Nag³ówek wtyczki kSound
 *
 * @defgroup ksound_shared_h Wtyczka kSound.dll.
 * 
 * kSound odpowiada za odtwarzanie dŸwiêków. 
 * Przy pomocy kSound::SoundRegister() mo¿na dodaæ
 * nowy dŸwiêk do listy, a nastêpnie go odtworzyæ przez kSound::SoundPlay().
 * 
 * @warning kSound::SoundRegister() mo¿e byæ wywo³any @b tylko
 * w momencie otrzymania przez wtyczkê komunikatu kSound::IM::DOREGISTER.
 * DOREGISTER wywo³ywane jest dwukrotnie. Podczas rejestrowania kolumn i tworzenia
 * interfejsu.
 * Za ka¿dym razem trzeba zarejestrowaæ TE SAME dŸwiêki!
 *
 * Kolumny w konfiguracji nazywane s¹ jako "SOUND_" + nazwa_dŸwiêku.
 * Akcje w konfiguracji maj¹ identyfikatory (ID kolumny z dŸwiêkiem):
 * - kSound::action::Check - Checkbox
 * - kSound::action::Value - Wartoœæ
 * - kSound::action::Play  - Play/Stop
 *
 * Standardowe typy dŸwiêków:
 * - newUser - Ktoœ jest dostêpny.
 * - newMsg - Wiadomoœæ (zamkniête okno)
 * - newMsgAct - Wiadomoœæ, aktywne okno
 * - newMsgInact - Wiadomoœæ, nieaktywne okno rozmowy
 * - quickEvent - Zdarzenie (np. niedostarczenie wiadomoœci)
 * - msgSent - Wiadomoœæ wys³ana
 *
 * @{
 */

namespace kSound {
  const tNet net = Net::sound;

  namespace IM {
    const int REGISTER = IM_USER + 3000;
    const int PLAY = IM_USER + 3001;
    const int DOREGISTER = IM_USER + 3002;
    const int GETFILE = IM_USER + 3003;
  }

  /** 
   * Struktura do wys³ania razem z kSound::IM::SOUND_REGISTER
   */
  class sIMessage_SoundRegister: public sIMessage_base {
  public:
    const static int minimumSize = 16; ///< rozmiar poprzedniej wersji...

    int colID;              ///< konkretny identyfikator kolumny, lub -1
    const char * name;      ///< Jednoznaczna nazwa dŸwiêku (nazwa kolumny w konfiguracji i pola w XMLu)
    const char * info;      ///< Informacja przy polu w konfiguracji.
    int flags;              ///< Flagi kSound::flags .
    const char * defSound;  ///< Domyœlnie ustawiony dŸwiêk dla kolumny

    sIMessage_SoundRegister(const char * name, const char * info, int flags = 0, int colID = -1, const char* defSound = 0)
      : sIMessage_base(IM::REGISTER), colID(colID), name(name), info(info), flags(flags), defSound(defSound)
    {
      s_size = sizeof(*this);
      net = kSound::net;
      type = imtConfig;
    }
  };

  namespace flags {
    const char contacts = 1;            ///< Dla ka¿dego kontaktu przechowywane jest osobne ustawienie.
    const char no_column_register = 2;  ///< kSound nie zarejestruje kolumny w konfiguracji.
    const char no_action_register = 4;  ///< kSound nie utworzy akcji...
  };

  namespace action {
    const int Check = 0x1A000000;
    const int Play  = 0x1B000000;
    const int Value = 0x1C000000;
    const int mute  = kSound::net * 1000 + 20;
  };

  namespace Cfg {
    const int mute = kSound::net * 1000 + 1;
  };

  /** 
   * Rejestruje dŸwiêk. 
   */
  inline void SoundRegister(Controler * Ctrl, const char * name, const char * info, int flags = 0, int colID = -1, const char* defSound = 0) {
    sIMessage_SoundRegister sr(name, info, flags, colID, defSound);
    Ctrl->IMessage(&sr);
  }

  /** 
   * Odgrywa dŸwiêk.
   */
  inline void SoundPlay(Controler * Ctrl, const char * name, int cntID = 0) {
    Ctrl->IMessage(&sIMessage_2params(IM::PLAY, kSound::net, imtConfig, (int) name, cntID));
  }

  /** 
   * Pobiera œcie¿kê do pliku.
   */
  inline const char* GetSoundFile(Controler * Ctrl, const char * name, int cntID = 0) {
    return (const char*) Ctrl->IMessage(&sIMessage_2params(IM::GETFILE, kSound::net, imtConfig, (int) name, cntID));
  }
};

/// @}