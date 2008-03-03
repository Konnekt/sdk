#pragma once

namespace kUpdate {
  namespace CFG {
    const int lastID = 4000; ///< ID ostatnich przesylek
    const int lastCheck = 4001; ///< "Identyfikator" ostatniego sprawdzania
    const int centrals = 4002; ///< Adresy dodatkowych centralek
    const int checkInterval = 4003; ///< Co ile minut sprawdzaæ?
    const int lastCheckTime = 4004; ///< Kiedy ostatnio cos pobieral
    const int checkAtStart = 4005; ///< Kiedy ostatnio cos pobieral
    const int userCentrals = 4006; ///< Adresy dodatkowych centralek
    // const int type = 4002; ///< Rodzaj u¿ytkownika normal/beta
  };

  namespace IMIA {
    const int gUpdate = 4000;
    const int check = 4001;
    const int getMOTD = 4002;
    const int getInfo = 4003;
    const int getMsg = 4004;
    const int getUpdate = 4005;
    const int runUnfinished = 4006;

    const int gCfg = 4100;
    const int gCfgCentrals = 4101;
    // const int defCentral = 4101;
    const int showHelp = 4102;
  };

  namespace IM {
    const int startInterface = 4000; ///< @internal
    const int destroyInterface = 4001; ///< @internal
  };
};