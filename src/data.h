/*
 Tiedostot ja datahommelit.

 (C) 1999 Tero Laitinen (Replica§)

*/

#ifndef __data_h
#define __data_h

#include "dtypes.h"  // definet datafileä varten
#include "exptypes.h"// define expdatafileä varten

DATAFILE * Dat;
DATAFILE * Exp;
void InitData(); // Lataa datafilet
void DeInitData(); // Vapauttaa muistin

void InitData()
{
    Dat = load_datafile("data.dat");
    Exp = load_datafile("exp.dat");
} // InitData
void DeInitData()
{
    unload_datafile(Dat);
    unload_datafile(Exp);
} // DeInitData



#endif


