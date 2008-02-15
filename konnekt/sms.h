/*
  nazwa="SMS"
  info="Nag��wek wtyczki SMS."
  author="Stamina"
*/

#pragma once
/**
@file 
Nag��wek wtyczki SMS.
�eby wys�a� wiadomo�� sms nale�y wstawi� do kolejki wiadomo�ci, lub wys�a�
bezpo�rednio do wtyczki komunikatem #IM_MSG_SEND wiadomo��:
@code
    cMessage m;
    m.net = Sms::net;
    m.type = MT_SMS;
    m.fromUid = "";
    m.body = "TRE�� WIADOMO�CI";
    m.toUid = "DOCELOWY NUMER";
    m.flag = MF_SEND;
    m.time = _time64(0);
	std::string ext;
	// W EXT ustawiamy parametry wysy�ania:
	ext = SetExtParam(ext, Sms::extFrom, "PODPIS WYSY�AJ�CEGO"); // nie zawsze wymagany
	ext = SetExtParam(ext, Sms::extGate, "IDENTYFIKATOR BRAMKI");  // wymagany!
	// Je�eli NIE chcemy, �eby wtyczka SMS dzieli�a wiadomo��, ustawiamy parametr extPart...
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
		/** Zwraca list� bramek obs�uguj�cych podany numer, kt�r� mo�na wype�ni� combobox (razem z opisami, bez ikon).
			@param p1 (const char *) numer telefonu do sprawdzenia
			@return (const char *) lista bramek
		*/
		const int getGatewaysComboText = IM_USER + 14001; 
		/** Zwraca limit znak�w na wiadomo�� wybranej bramki
			@param p1 (const char *) identyfikator bramki
			@return (int) limit znak�w
		*/
		const int getGatewayLimit = IM_USER + 14002; 
	};
};