/*
 Sisältää Tyyppimäärittelyjä ja definejä.

 (C) 1999 Tero Laitinen (Replica§)

*/

#ifndef __types_h
#define __types_h

#define  BitL           << 16          // bitshiftit
#define  BitR           >> 16          // koska käytetään fixed point lukuja

#define Maxmapsizex              3000  // 3000x3000 = 9mb
#define Maxmapsizey              3000
#define Maxplayers              3
#define Maxobjects              6000   // 6000 karttapalaa max.
#define Maxeditdata             1000
#define Maxbullets              2000    // 2000 yhtäaikaista bullettia
#define Maxbuildings            500    // 500 rakennusta
#define Maxspires               20     // 20 lavasuihkua
#define Maxstuff                100    // 100 erilaista kamaa
#define Maxmenus                20     // 20 erilaista menua
#define Maxexp                  200    // räjähdyksiä
#define Maxlava                 3000   // laavaa
#define Maxspirelava            2000
#define Maxlavalife             300    // laavan elinikä
#define Maxbots                 50     // 25 bottia
#define Maxvehicles             100
#define Difbotweapons           9

#define MAXGAMETYPES 2
#define GAMETYPE_DEATHMATCH     0
#define GAMETYPE_BOTHUNT        1

char * Gametypename[]=
{
"Deathmatch",
"Bot hunt",
}; // char * Gametypename[]=
char * Botdifficultyname[]=
{
"Easy",
"Medium",
"Hard",
"Very hard",
"Extreme",
"Impossible",
};

// erilaisia menuja
#define MENU_MAIN               0
#define MENU_BUY                1
#define MENU_BUYWEAPONS         2
#define MENU_BUYPROJECTW        3
#define MENU_BUYENERGYW         4
#define MENU_BUYBOMBS           5
#define MENU_BUYTOOLS           6
#define MENU_BUYAMMO            7
#define MENU_INVENTORY          8
#define MENU_BUYBUILD           9
#define MENU_BUYARMOR           10
#define MENU_BUYTOOLS2          11
#define MENU_BUYVEHICLES        12

#define MAX_HMISSILE_SEARCH_RANGE 150
#define BOT_SEARCH_RANGE          400
typedef struct
 {
   bool Live;
   short X, Y, Type;
 } Tobject; // eli kartan sprite
typedef struct
 {
   int Version;
   int Mapsizex, Mapsizey;
   int Mapobjects;
   int Startpoint[Maxplayers][2];
 } Tlevel; // karttaheaderi
typedef struct
 {
  // Kartan lisädatat
  char Texturename[32];
 } Tadditional_data;
typedef struct
 { // Ox, Oy vanhat kordinaatit, X, Y, kordinaatit, Mx, My, momentit,
   // Sx Sy, viewpoint x ja y, Dir on piipun direction
   int Ox, Oy, X, Y, Mx, My, Sx, Sy, Dir;
   // monta elämää
   int Lives;
   // Animaation, kuva, counteri sekä S on oikealle vai vasemmalle
   int Anim, Picture, Count, S;
   // Mikä menu aktiivisena
   int Menu;
   int Ninjadir; // Ninjaropen suunta

   int Action; // esim. laattojen asettelu
   int Actionx, Actiony, Actionvar[5];

   int Laserbounce; // Mihin suuntaan laser kimpaantuu
   // Animaatio on pysähtynyt, Elossako?, Lataamassa, Onko tarpeeksi lähellä
   // tukikohtaa ostaakseen
   bool Animstopped, Live, Reloading, Canbuy;
   // Käveleekö, Vanha jalkojen tila, Jalat maassa, Hyppääkö, Ninjaropemaassa
   // Ninjarope päällä, Ampuminen
   bool Walking, Oldfeet,FeetOnGround, Jump, Ninjaground, Ninjarope, Firegun;
   // Tärinän kesto, Liekin kesto
   int Shake, Gunfire;
   // Ropelength = köyden pituus, Ropeset = haluttu köyden pituus
   // Nx, Ny = Ninjax, Nmx = Ninjamoment, Ntx = Ninja pullpower
   // Nmdir = Suuntamomentti

   int Ropelength, Ropeset, Nx, Ny, Nmx, Nmy, Ntx, Nty, Nmdir;
   bool Ninjacheck;
   // Latausaika, Aseen piippu, Käytössä oleva tavara, Valintaboksi menussa
   int Reload, Gun, Item, Selectx, Selecty, Selectrealx, Selectrealy;
   // Etäisyys basesta
   int Distancefrombase;
   // Rahat
   int Money;
   // Tapot
   int Kills[Maxplayers];
   // Panssari
   int Armor[3]; // Head, Torso, ...
   // Menujen valinta
   int Select[Maxmenus];
   // Mitä stuffia tää kantaa
   int Stuff[Maxstuff];
   // Mitä luoteja
   int Ammo[Maxstuff];
   // järjestetty inventaario
   int Inv[Maxstuff];
   // Paljonko vaaditaan kuteja tappamiseen
   int Killdamage[3];
   // Paljonko voi osua kuteja osua kaikenkaikkiaan ennen kuin kupsahtaa
   int Totaldamage;
   // osumat
   int Damage[3]; // Head, Torso,
   // vahinko // siis mikä näytetään ruudulla
   int Hits[3];
   int Lastweapon; // Mikä *ase* oli viimeiseksi kädessä
   int Killtimer;
   int Botskilled, Died;
   bool Camouflaged, Parachute, Parachuteshotdown;
   int Nocamo;
   char Camocolor[2];
   int Playsamplecounter;
   BITMAP * Bmp1, *Bmp2; // For camouflage
 } Tplayer;

typedef struct
 { // Ox, Oy vanhat kordinaatit, X, Y, kordinaatit, Mx, My, momentit,
   // Sx Sy, viewpoint x ja y, Dir on piipun direction
   int Ox, Oy, X, Y, Mx, My, Sx, Sy, Dir;
  // Animaation, kuva, counteri sekä S on oikealle vai vasemmalle
   int Anim, Picture, Count, S, Gs;
   // Mikä menu aktiivisena
   int Ninjadir; // Ninjaropen suunta

   int Laserbounce; // Mihin suuntaan laser kimpaantuu
   // Animaatio on pysähtynyt, Elossako?, Lataamassa
   bool Animstopped, Live, Reloading;
   // Käveleekö, Vanha jalkojen tila, Jalat maassa, Hyppääkö, Ninjaropemaassa
   // Ninjarope päällä, Ampuminen
   bool Walking, Oldfeet,FeetOnGround, Jump, Ninjaground, Ninjarope, Firegun;
   // Tärinän kesto, Liekin kesto
   int Shake, Gunfire;
   // Ropelength = köyden pituus, Ropeset = haluttu köyden pituus
   // Nx, Ny = Ninjax, Nmx = Ninjamoment, Ntx = Ninja pullpower
   // Nmdir = Suuntamomentti
   int Ropelength, Ropeset, Nx, Ny, Nmx, Nmy, Ntx, Nty, Nmdir;
   bool Ninjacheck;
   int Reload, Gun, Item;
   int Armor[3]; // Head, Torso, ...
   int Killdamage[3];
   // Paljonko voi osua kuteja osua kaikenkaikkiaan ennen kuin kupsahtaa
   int Totaldamage;
   // osumat
   int Damage[3]; // Head, Torso,
   // vahinko // siis mikä näytetään ruudulla
   int Hits[3];
   int Target, Targettype, Counter, Targetdir, Targetdist, Visualtarget, Stuck;
   int Ammo;
   bool Bounce;
   int Timer;
   char Forgettarget;
   int Search_range;
 } Tbot;

typedef struct
 { // Ox, Oy vanhat kordinaatit, X, Y, kordinaatit, Mx, My, momentit,
   // Sx Sy, viewpoint x ja y, Dir on piipun direction
   int Ox, Oy, X, Y, Mx, My, Sx, Sy, Dir;
   int Type;
  // Animaation, kuva, counteri sekä S on oikealle vai vasemmalle
   int Anim, Picture, Count, S;
   bool Animstopped, Live, Reloading;
   bool Walking, Oldfeet,FeetOnGround, Jump, Firegun;
   // Tärinän kesto, Liekin kesto
   char Shake, Gunfire;
   short Reload, Gun, Item;
   char Damage; // Head, ja muu osa,
   // vahinko // siis mikä näytetään ruudulla
   bool Bounce;
 } Tvehicle;

typedef struct
 {
   bool Live;
   int Ox, Oy, X, Y, Mx, My, Speed, Dir;
   int Life;
   int Type;
   int Owner;
   char Ownertype;
   int Dat[10]; // Erilaiset muuttujat

 } Tbullet; // luoti, pääosin samat kuin Tplayerissä
typedef struct
 {
   bool Live;
   int Pic;
   char Anim, Picpos;
   char Counter;
   int Ox, Oy, X, Y, Mx, My, Dir, Owner;
   int Energy;
   int Type;
   int Dat[10];
 } Tbuilding; // Rakennus
typedef struct
 {
   bool Live;
   int X, Y, Power, Dir;
   int Boom;
   int Time;
   int Multi;
   int Reserved[61];
 } Tspire; // Lavasuihku
typedef struct
 {
   bool Live, Term;
   int X, Y, Frame, Count;
   char Break, Owner, Delay, Ownertype;
   bool Check, Onlyonce, Sampled;
   int Type;

 } Texp; // Räjähdys
typedef struct
 {
   bool Live;
   int X, Y, Mx, My,S;
   int C, Life;
 } Tlava; // LAava
typedef struct
 {
  int Type;
  int Dat[16];
  int Timelimit;
 } Tobjective;
typedef struct
 {
  char Name[64];
  Tobjective *Obj;
  int Objs;
  char **Briefing;
 } Tmission;
typedef struct
 {
  bool Live;
  short X, Y;
  unsigned char Type;
  short Var[4];
 } Teditordata;
typedef struct
 {
   Tplayer      Pl[Maxplayers];
   Tvehicle     Veh[Maxvehicles];
   Tobject      Obj[Maxobjects];
   Tbullet      Bul[Maxbullets];
   Tbuilding    Bld[Maxbuildings];
   Tspire       Spire[Maxspires];
   Texp         Exp[Maxexp];
   Tlava        Lava[Maxlava];
   Tbot         Bot[Maxbots];

   Teditordata  Editdata[Maxeditdata];
   Tmission     Mission;
   int          Boomtimer;

   BITMAP * Map;

 } Tmaindat; // Maindata missä kaikki on kiinni
typedef struct
 {
   struct SoundOptions sound;
   bool Vsync;
   char Players;
   unsigned char Fps;
   bool Set;
   bool Parallax;
   bool Realrope, Lava;
   struct
    {
      char Up, Left, Right, Down, Use, Change, Jump, Ninjarope;
    } Nap[Maxplayers];


    int Startcash, Lives;
    char Mapname[13];
   int Fileselected;
   short Xres, Yres;
   unsigned char Bots, Gametype, Fraglimit, Botdifficulty;
   char Texturedearth;
   char Botweapons[Difbotweapons]; // Eri aseita
   bool Realistic_falling_damage;
   bool Use_fixed_bot_places;
   char         Reserved[57];

 } Toptions;

#define ADD_SOMETHING(Pointer, Count, Type) \
   if (Count==0)                      \
    {                                       \
      Count = 1;                      \
      Pointer = new (##Type[Count]);\
      memset(&Pointer[Count-1], 0, sizeof(##Type));\
    } \
     else\
      {\
        (Count)++;\
        ##Type * Apu = new (##Type[Count]);\
        for (int Count2 = 0; Count2 < Count-1; Count2++)\
         memcpy(&Apu[Count2], &Pointer[Count2], sizeof(##Type));\
         delete Pointer;\
         Pointer = Apu;\
         memset(&Pointer[Count-1], 0, sizeof(##Type));\
      } // else (if (Count==0))
#define IN_COLORS(color, colors, c, isit)  \
{\
isit = false;\
for (int i = 0; i < colors; i++)\
 if (color[i] == c) isit = true;\
}
#define IN_HALF_COLORS(color, colors, c, isit)  \
{\
isit = false;\
for (int i = 0; i < colors/2; i++)\
 if (color[i] == c) isit = true;\
}

#endif
