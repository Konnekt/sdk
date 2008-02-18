#pragma once

namespace kTransfer {
  const int net = NET_KTRANSFER;

  namespace Cfg {
    const int localIP = 130002;
    const int localPort = 130003;
    const int remoteIP = 130004;
    const int remotePort = 130005;
    const int autoAccept = 130029;
    const int autoResume = 130007;
    const int autoDropDir = 130009;
    const int behindNAT = 130010;
    const int autoDetect = 130011;
    const int portForwarding = 130012;
    const int sendToInvisible = 130028;

    // const int exWindow = 130030; // Rozszerzone okno
    const int asMessage = 130031; // informuje o nadjeœciu pliku zamiast otwieraæ okno
    const int showOnConnection = 130032; // Pokazuje ju¿ po nawi¹zaniu po³¹czenia
    const int notifyOnCompletion = 130033; // Informuje przez kNotify o zakoñczeniu pobierania

    const int closeWindowUp = 130035; 
    const int closeWindowDown = 130036; 
    const int saveToHistory = 130037; 
    const int slotsMax = 130038;
    const int dirSend = 130039;
    const int dirReceive = 130040;
    const int minDriveSpace = 130041;

    enum enAutoAccept {
      aaAskFirst  =  0,
      aaFromAllowed = 4,
      aaAlways = 8
    };
  };

  namespace Cnt {
    const int autoAccept = 130001;
    const int autoDropDir = 130002;
  };

  // autoAccept:
  namespace Act {
    const int gCfg = 130000; // Grupa w akcji w konfiguracji
    const int gInfo = 130001; // Grupa w akcji w konfiguracji
    const int plugStatus = 130010; // Status wtyczki w konfiguracji
    const int sendFile = 130020;
    const int receiveFile = 130021;
    const int start = 130030;
    const int stop = 130031;
    const int restart = 130032;

    #define IM_EX_TEST 130000  // Identyfikator wiadomoœci do wykorzystania przez inne wtyczki...
  };

  namespace IM {
    const int updateStatus = 130000;
  }
};

/*
#define CFG_PRX_USE     130020
#define CFG_PRX_IP      130021
#define CFG_PRX_PORT    130022
#define CFG_PRX_RPORT   130023
#define CFG_PRX_START   130024
#define CFG_PRX_REQAUTH 130025
#define CFG_PRX_USER    130026
#define CFG_PRX_PASS    130027
*/

#define IDI_P2P         130000  // Identyfikator ikonki
#define NET_P2P         kTransfer::net    // Wartosc net tej wtyczki
