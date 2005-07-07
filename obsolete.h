/*
  nazwa="Plug Obsolete"
  info="Sta�e i struktury kt�re zosta�e zast�pione przez inne."
*/

#pragma once

#ifndef KONNEKT_SDK_SUPPRES_OBSOLETE_NOTICE
#pragma message("Prosze przerobic kod tak, zeby NIE uzywac plug_obsolete.h !!!")
#endif
#pragma pack(push, 1)


        #define IMC_CFG_SETCOL 1001    ///< Rejestruje kolumn� w tabeli ustawie�.
                                        ///  \param p1 (sSETCOL*) parametry kolumny.
                                        ///  \attention Mo�e by� wysy�ane TYLKO PO otrzymaniu komunikatu
                                        ///  #IM_SETCOLS.
        #define IMC_CNT_SETCOL 1101    ///< Rejestruje kolumn� w tabeli kontakt�w.
                                        ///  \param p1 (sSETCOL*) parametry kolumny.
                                        ///  \attention Mo�e by� wysy�ane TYLKO PO otrzymaniu komunikatu
                                        ///  #IM_SETCOLS.
        /** Struktura u�ywana w #IMC_CFG_SETCOL i #IMC_CNT_SETCOL */
        struct sSETCOL {
            int id /// ID kolumny.
              , type /// Typ kolumny (patrz \ref dt_ct_)
              , def /// Domy�lna warto��.
              ;
            unsigned short s_size;
            const char * name; ///< Nazwa kolumny, konieczna, je�li tworzymy kolumn� typu Unique (z id == -1).
            sSETCOL(int _id=-1, int _type=0 , int _def=0 , const char* _name=""):s_size(sizeof(sSETCOL)),id(_id),type(_type),def(_def),name(_name) {} 
        };



#pragma pack(pop)
