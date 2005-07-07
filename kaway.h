/*
  K.Away

  Copyright © 2004 Sija.NET
  Copyright © 2004 KPlugins team

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License Version
  2.1 as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#pragma once

  // definiujemy sta³e
  #define kNET 666
  #define kNET1000 kNET * 1000
  #define kNAME "K.Away"
  #define kSHORT "K.Away"
  #define kVERSION "0.3.0.0"

  // data kompilacji
  #define COMPILE __DATE__
  #define DATE __TIME__

  // definiujemy ikonki
  #define kICON kNET1000 + 0
  #define kICON_ABOUT kNET1000 + 1
  #define kICON_MUTE kNET1000 + 2
  #define kICON_ON kNET1000 + 3
  #define kICON_OFF kNET1000 + 4

  // definiujemy identyfikatory
  #define kID_OPT_GRP kNET1000 + 10
  #define kID_OPT_STATUS kNET1000 + 11
  #define kID_OPT_NOSILENTON kNET1000 + 12
  #define kID_OPT_REMEMBER kNET1000 + 13
  #define kID_OPT_FULLSCREEN kNET1000 + 14
  #define kID_OPT_SYNCAAWAY kNET1000 + 15
  #define kID_OPT_RESPONSE kNET1000 + 16
  #define kID_OPT_FLOODTIME kNET1000 + 17
  #define kID_CNT_GRP kNET1000 + 18
  #define kID_OPT_SMSTIME kNET1000 + 19
  #define kID_OPT_STATUSTXTON kNET1000 + 20
  #define kID_MAIN_GRP_ONOFF kNET1000 + 21
  #define kID_OPT_AWAYMSG kNET1000 + 22
  #define kID_OPT_SHOWINMAIN kNET1000 + 23
  #define kID_OPT_SHOWINCNT kNET1000 + 24
  #define kID_OPT_IRCCMD kNET1000 + 25
  #define kID_CNT_GRP_ONOFF kNET1000 + 26
  #define kID_OPT_USENOTIFY kNET1000 + 27
  #define kID_OPT_USEQEVENT kNET1000 + 28
  #define kID_OPT_NOSILENTOFF kNET1000 + 29
  #define kID_OPT_CNT_NOSILENTON kNET1000 + 30
  #define kID_OPT_CNT_NOSILENTOFF kNET1000 + 31
  #define kID_OPT_CNT_RESPONSE kNET1000 + 32
  #define kID_OPT_CNT_NONSTDRESP kNET1000 + 33
  #define kID_OPT_NOSILENTAWAY kNET1000 + 34
  #define kID_OPT_CNT_NOSILENTAWAY kNET1000 + 35
  #define kID_OPT_USEHTML kNET1000 + 36
  #define kID_OPT_AWAYDATE kNET1000 + 37
  #define kID_OPT_AWAYTIME kNET1000 + 38
  #define kID_OPT_STATUSTXTOFF kNET1000 + 39
  #define kID_OPT_STATUSCHG kNET1000 + 40
  #define kID_OPT_SILENTONTXT kNET1000 + 41
  #define kID_OPT_SILENTOFFTXT kNET1000 + 42
  #define kID_OPT_CNT_LASTMSGT kNET1000 + 43
  #define kID_OPT_SMSNR kNET1000 + 44
  #define kID_OPT_SMSGATES kNET1000 + 45
  #define kID_OPT_SMSGATE kNET1000 + 46
  #define kID_OPT_MSGCOUNT kNET1000 + 47
  #define kID_OPT_LASTMSGFROM kNET1000 + 48
  #define kID_OPT_SMSMSG kNET1000 + 49
  #define kID_OPT_RAPMSGCOUNT kNET1000 + 50
  #define CFG_MIG_MSG 229011// kMigacz
