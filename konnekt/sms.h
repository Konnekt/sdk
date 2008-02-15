/*
  nazwa="SMS"
  info="Nag³ówek wtyczki SMS."
  author="Stamina"
*/

#pragma once
/**
@file 
Nag³ówek wtyczki SMS.
¯eby wys³aæ wiadomoœæ sms nale¿y wstawiæ do kolejki wiadomoœci, lub wys³aæ
bezpoœrednio do wtyczki komunikatem #IM_MSG_SEND wiadomoœæ:
@code
    cMessage m;
    m.net = Sms::net;
    m.type = MT_SMS;
    m.fromUid = "";
    m.body = "TREŒÆ WIADOMOŒCI";
    m.toUid = "DOCELOWY NUMER";
    m.flag = MF_SEND;
    m.time = _time64(0);
	std::string ext;
	// W EXT ustawiamy parametry wysy³ania:
	ext = SetExtParam(ext, Sms::extFrom, "PODPIS WYSY£AJ¥CEGO"); // nie zawsze wymagany
	ext = SetExtParam(ext, Sms::extGate, "IDENTYFIKATOR BRAMKI");  // wymagany!
	// Je¿eli NIE chcemy, ¿eby wtyczka SMS dzieli³a wiadomoœæ, ustawiamy parametr extPart...
	// ext = SetExtParam(ext, Sms::extPart, "0");
	
	m.ext = (char*) ext.c_str();

@endcode

*/

namespace Sms {
	const int net = NET_SMS;
	const char * extFrom = "SMSfrom";
	const char * extGate = "SMSgate";
	const char * extWindowID = "SMSwinID";
	const char * extPart = "SMSpart";
	namespace IM {
		/** Zwraca listê bramek obs³uguj¹cych podany numer, któr¹ mo¿na wype³niæ combobox (razem z opisami, bez ikon).
			@param p1 (const char *) numer telefonu do sprawdzenia
			@return (const char *) lista bramek
		*/
		const int getGatewaysComboText = IM_USER + 14001; 
		/** Zwraca limit znaków na wiadomoœæ wybranej bramki
			@param p1 (const char *) identyfikator bramki
			@return (int) limit znaków
		*/
		const int getGatewayLimit = IM_USER + 14002; 
	};
};