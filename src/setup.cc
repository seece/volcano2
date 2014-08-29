#include <stdio.h>
#include "keyboard.h"
typedef struct
 {
   int Musicvolume, Soundvolume;
   int Sndfreq;
   bool Sound, Bits16,Stereo,Interpolated;
   bool Vsync;
   char Players;
   char Multiplier;
   bool Set;
   bool Parallax;
   bool Realrope, Lava;
   struct
    {
      char Up, Left, Right, Down, Use, Change, Jump, Ninjarope;
    } Nap[3];


    int Startcash, Lives;
    char Mapname[13];
   int Fileselected;
   short Xres, Yres;
   char         Reserved[72];

 } Toptions;

Toptions *Opt = new Toptions;

void Saveoptions()
 {
  FILE * F = fopen("Options.Cfg", "wb");
  fwrite(Opt, sizeof(Toptions), 1, F);
  fclose(F);
 } // void Saveoptions()
void Loadoptions()
 {
  FILE * F = fopen("Options.Cfg", "rb");
  fread(Opt, sizeof(Toptions), 1, F);
  fclose(F);
 } // void Loadoptions()

void Defaults()                 // Options asetusten resetointi
 {
   Opt->Musicvolume = 50;    // ääntä
   Opt->Soundvolume = 100;
   Opt->Sndfreq = 44100;     // Laatua
   Opt->Bits16 = true;       // 16Bittinen tottakai
   Opt->Interpolated = true; // interpoloitu
   Opt->Sound = true;        // Ja vielä päälle

   Opt->Multiplier = 2;         // Frameskip 1 (käytännössä Pentium 3 800Mhz :)
   Opt->Players = 2;                   // pelaajat 2 max 3
   Opt->Parallax = true;
   // Näppäinten asettaminen
   Opt->Nap[2].Up =     SxI;
   Opt->Nap[2].Left =   SxJ;
   Opt->Nap[2].Right =  SxL;
   Opt->Nap[2].Down =   SxK;     // pelaaja kolme
   Opt->Nap[2].Use =    SxCOMMA;
   Opt->Nap[2].Change = SxN;
   Opt->Nap[2].Jump =   SxM;
   Opt->Nap[2].Ninjarope =   SxB;

   Opt->Nap[0].Up =     SxW;
   Opt->Nap[0].Left =   SxA;    // pelaaja yksi
   Opt->Nap[0].Right =  SxD;
   Opt->Nap[0].Down =   SxS;
   Opt->Nap[0].Use =    SxTAB;

   Opt->Lava = true;

   Opt->Nap[0].Change = SxCAPSLOCK;
   Opt->Nap[0].Jump =    SxSHIFTSxLEFT;
   Opt->Nap[0].Ninjarope = 41;


   Opt->Nap[1].Up =     SxUP;
   Opt->Nap[1].Left =   SxLEFT;
   Opt->Nap[1].Right =  SxRIGHT;
   Opt->Nap[1].Down =   SxDOWN;  // pelaaja 2
   Opt->Nap[1].Use =    SxENTER;
   Opt->Nap[1].Change = SxBACKSPACE;
   Opt->Nap[1].Jump =   SxSHIFTSxRIGHT;
   Opt->Nap[1].Ninjarope = 40;

   Opt->Realrope = false;

   Opt->Startcash = 2000;        // Rahhaa 5000
   Opt->Lives = 5;               // elämiä 5
 } // Defaults
void main()
 {
     if (file_exists("Options.cfg", 0, 0)) Loadoptions(); else {Defaults();}
   printf("\nVolcano 2 setup");
   printf("\nDo you want sounds:");
   printf("\n1 - yes\n2 - no");
char Ch = 1;
bool Done = false;
int Select = 0;
fflush(stdout); do {Ch= getch();
switch(Ch) {case '1': Done = true; Select = 1;break; case '2': Done = true; Select = 2;break;}; //case '3': Done = true; Select = 3;break;};
 }while (!Done);
if (Select == 1)
 {
   Opt->Sound = true;
   printf("
Select sound frequency:
1 - 11025
2 - 22050
3 - 44100");
 Ch = 1;
Select = 0;
fflush(stdout); do {Ch= getch();
switch(Ch) {case '1': Select = 1;break; case '2': Select = 2;break; case '3': Select = 3;break;};
 }while (Select==0);
switch(Select)
 {
   case 1: Opt->Sndfreq = 11025; break;
   case 2: Opt->Sndfreq = 22050; break;
   case 3: Opt->Sndfreq = 44100; break;
 };
printf("\n16 bit sound?\n1 - yes\n2 - no");
Select = 0;
fflush(stdout); do {Ch= getch();
switch(Ch) {case '1': Select = 1;break; case '2': Select = 2;break;}; //case '3': Select = 3;break;};
 }while (Select==0);
switch(Select)
{
  case 1: Opt->Bits16 = true; break;
  case 2: Opt->Bits16 = false; break;
};
printf("\nInterpolated sound?\n1 - yes\n2 - no");
Select = 0;
fflush(stdout); do {Ch= getch();
switch(Ch) {case '1': Select = 1;break; case '2': Select = 2;break;}; //case '3': Select = 3;break;};
 }while (Select==0);
switch(Select)
{
  case 1: Opt->Interpolated = true; break;
  case 2: Opt->Interpolated = false; break;
};
printf("\nStereo sound?\n1 - yes\n2 - no");
Select = 0;
fflush(stdout); do {Ch= getch();
switch(Ch) {case '1': Select = 1;break; case '2': Select = 2;break;}; //case '3': Select = 3;break;};
 }while (Select==0);
switch(Select)
{
  case 1: Opt->Stereo = true; break;
  case 2: Opt->Stereo = false; break;
};

 } else Opt->Sound = false;
 printf("\nSelect resolution:
1 - 640x400
2 - 640x480
3 - 800x600
4 - 1024x768");

 Ch = 1;
Select = 0;
fflush(stdout); do {Ch= getch();
switch(Ch) {case '1': Select = 1;break; case '2': Select = 2;break; case '3': Select = 3;break;case '4': Select = 4;break;};
 }while (Select==0);
switch(Select)
 {
   case 1: Opt->Xres = 640; Opt->Yres = 400;break;
   case 2: Opt->Xres = 640; Opt->Yres = 480;break;
   case 3: Opt->Xres = 800; Opt->Yres = 600;break;
   case 4: Opt->Xres =1024; Opt->Yres = 768;break;
 };

   Saveoptions();

 } // void main()

