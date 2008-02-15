/*
  nazwa="kLAN"
  info="Nag³ówek wtyczki kLAN."
  author="Stamina"
*/

#pragma once

#ifndef SHARED_KLAN_H
#define SHARED_KLAN_H

#include <vector>

namespace kLAN {
	const int net = 15;


	namespace Act {
		const int gCfg = 15000;
		const int cfgSearch = 15001;
		const int cfgHelp = 15002;

		const int gStatus = 15100;
		const int stOffline = 15100;
		const int stOnline = 15101;
		const int stAway = 15102;
		const int stDND = 15103;

		const int nfoSave = 15120;
		const int nfoRefresh = 15121;
	};

//CFG
	namespace Cfg {
		const int status = 15000;
		const int listOnly = 15001;
		const int mailSlot = 15002;
		const int winPopup = 15003;
		const int statusInfo = 15004;
	};

	// Pozycje parametrów w przekazywanych danych
	const int MS_ID = 0;
	const int MS_FROM = 1;
	const int MS_TO = 2;
	const int MS_COMM = 3;
	const int MS_PAR = 4;

	namespace IM {
		enum enEvent {
			eventSending = 1 ,
			eventReceiving = 2,
			eventStarted = 4,
			eventFinished = 8
		};
		class RegisterHandler : public sIMessage_base {
		public:
			const static int __msgID = IM_USER + 15000; // ID komunikatu
			int _request;
			RegisterHandler(int request):sIMessage_base(__msgID , kLAN::net , IMT_ALL) {
				_request= request;
				s_size = sizeof(*this);
			}
		};

		class SendCommand : public sIMessage_base {
		public:
			const static int __msgID = IM_USER + 15001; // ID komunikatu
			CStdString _to;
			CStdString _command;
			CStdString _params;
			SendCommand(const CStdString & to , const CStdString & command , const CStdString & params)
				:sIMessage_base(__msgID , kLAN::net , IMT_ALL)
				,_to(to),_command(command),_params(params) {
				s_size = sizeof(*this);
			}
		};
		class EventSendingCommand : public sIMessage_base {
		public:
			const static int __msgID = IM_USER + 15002; // ID komunikatu
			const CStdString & _to;
			const CStdString & _command;
			const CStdString & _params;
			EventSendingCommand(const CStdString & to , const CStdString & command , const CStdString & params)
				:sIMessage_base(__msgID , 0 , IMT_ALL)
				,_to(to),_command(command),_params(params) {
				s_size = sizeof(*this);
			}
		};

		class EventReceivingCommand : public sIMessage_base {
		public:
			const static int __msgID = IM_USER + 15003; // ID komunikatu
			typedef std::vector<CStdString> tParams;
			const tParams & _params;
			int _cnt;
			EventReceivingCommand(const tParams & params , int cnt)
				:sIMessage_base(__msgID , 0 , IMT_ALL),_params(params),_cnt(cnt){
				s_size = sizeof(*this);
			}
		};

		class Event : public sIMessage_base {
		public:
			const static int __msgID = IM_USER + 15004; // ID komunikatu
			enEvent _event;
			Event(enEvent event):sIMessage_base(__msgID),_event(event){
				s_size = sizeof(*this);
			}
		};

	};
};

#endif
