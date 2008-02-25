#pragma once

/**
 * @file 
 * Nag³ówek wtyczki SMS.
 * ¯eby wys³aæ wiadomoœæ sms nale¿y wstawiæ do kolejki wiadomoœci, lub wys³aæ
 * bezpoœrednio do wtyczki komunikatem #IM_MSG_SEND wiadomoœæ:
 *
 * @code
 * Message msg;
 * msg.setNet(Net::sms);
 * msg.setType(Message::typeSMS);
 * msg.setBody("TREŒÆ WIADOMOŒCI");
 * msg.setToUid("DOCELOWY NUMER");
 * msg.setOneFlag(Message::flagSend, true);
 * msg.setTime(_time64(0));
 * // W EXT ustawiamy parametry wysy³ania:
 * msg.setExtParam(Sms::extFrom, "PODPIS WYSY£AJ¥CEGO");  // nie zawsze wymagany
 * msg.setExtParam(Sms::extGate, "IDENTYFIKATOR BRAMKI"); // wymagany!
 * // Je¿eli NIE chcemy, ¿eby wtyczka SMS dzieli³a wiadomoœæ, ustawiamy parametr extPart...
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
     * Zwraca listê bramek obs³uguj¹cych podany numer, któr¹ mo¿na wype³niæ combobox (razem z opisami, bez ikon).
     *
     * @param p1 (const char *) numer telefonu do sprawdzenia
     * @return (const char *) lista bramek
     */
    const int getGatewaysComboText = IM_USER + 14001; 
    /** 
     * Zwraca limit znaków na wiadomoœæ wybranej bramki
     *
     * @param p1 (const char *) identyfikator bramki
     * @return (int) limit znaków
    */
    const int getGatewayLimit = IM_USER + 14002; 
  };
};