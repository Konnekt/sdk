#pragma once

/**
 * @file 
 * Nag��wek wtyczki SMS.
 * �eby wys�a� wiadomo�� sms nale�y wstawi� do kolejki wiadomo�ci, lub wys�a�
 * bezpo�rednio do wtyczki komunikatem #IM_MSG_SEND wiadomo��:
 *
 * @code
 * Message msg;
 * msg.setNet(Net::sms);
 * msg.setType(Message::typeSMS);
 * msg.setBody("TRE�� WIADOMO�CI");
 * msg.setToUid("DOCELOWY NUMER");
 * msg.setOneFlag(Message::flagSend, true);
 * msg.setTime(_time64(0));
 * // W EXT ustawiamy parametry wysy�ania:
 * msg.setExtParam(Sms::extFrom, "PODPIS WYSY�AJ�CEGO");  // nie zawsze wymagany
 * msg.setExtParam(Sms::extGate, "IDENTYFIKATOR BRAMKI"); // wymagany!
 * // Je�eli NIE chcemy, �eby wtyczka SMS dzieli�a wiadomo��, ustawiamy parametr extPart...
 * // msg.setExtParam(Sms::extPart, "0");
 * @endcode
 */

namespace Sms {
  const int net = Net::sms;
  const char extFrom[] = "SMSfrom";
  const char extGate[] = "SMSgate";
  const char extWindowID[] = "SMSwinID";
  const char extPart[] = "SMSpart";

  namespace IM {
    /** 
     * Zwraca list� bramek obs�uguj�cych podany numer, kt�r� mo�na wype�ni� combobox (razem z opisami, bez ikon).
     *
     * @param p1 (const char *) numer telefonu do sprawdzenia
     * @return (const char *) lista bramek
     */
    const int getGatewaysComboText = IM_USER + 14001; 
    /** 
     * Zwraca limit znak�w na wiadomo�� wybranej bramki
     *
     * @param p1 (const char *) identyfikator bramki
     * @return (int) limit znak�w
    */
    const int getGatewayLimit = IM_USER + 14002; 
  };
};