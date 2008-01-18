#pragma once

namespace kJabber {
  const int net = 12;

  namespace CFG {
    /* const int server = 12100;
    const int user = 12101;
    const int pass = 12102;
    const int lastStatus = 12103;
    const int userDescription = 12104; */

    const int synchDirection = 12010;
    const int synchAddContacts = 12011;
    const int synchRemoveContacts = 12012;
    const int autoSubscribe = 12013;
    const int autoAuthorize = 12014;

    const int discoShowFeatures = 12100;
    const int discoReadAll = 12101;
    const int discoInfo = 12102;
    const int discoViewType = 12103;
    const int discoViewGrouping = 12104;
  }

  namespace CNT {
    // const int synched = 12000;
  }

  namespace IM {
    /** Zwraca obiekt jaberoo::Session */
    const int getSession = 12000;
  }

  namespace ACT {
    const int CfgGroup = 12000;

    const int Status = 12050;
    const int stOnline = 12062;
    const int stChat = 12063;
    const int stAway = 12064;
    const int stNA = 12065;
    const int stDND = 12066;
    const int stHidden = 12067;
    const int stOffline = 12068;

    const int subscription_off = 10;
    const int subscriptionNfo_off = 11;
    const int vcardRequest_off = 20;
    const int vcardSet_off = 21;

    const int subscription = (net * 1000) + subscription_off;
    const int subscriptionNfo = (net * 1000) + subscriptionNfo_off;
    const int subSubscribed = 12015;
    const int subShow = 12016;
    const int sendStatus = 12017;
    const int sendUnavailable = 12018;

    const int servers = 12030;
    const int registerAccount = 12031;
    const int editRegistration = 12032;

    const int vcardRequest = (net * 1000) + vcardRequest_off;
    const int vcardSet = (net * 1000) + vcardSet_off;

    const int services = 12040;
    // const int evtAuthorize = 12010;
  }

  namespace ICO {
    const int logo = 12000;
    const int online = 12001;
    const int away = 12002;
    const int offline = 12003;
  }
};