





/*
Moottori.

(C) 1999 Tero Laitinen (Replica§)
*/
#ifndef __engine_h
#define __engine_h


// Animaatioiden definet
#define         ANI_WALK        0
#define         ANI_PLASMADEATH 1

// The painovoima

#define         Gravity         400

#define         FAST_PUTPIXEL(bmp, x, y, c)  if (x >= bmp->cl) if (y >= bmp->ct) \
                if (x < bmp->cr) if (y < bmp->cb) \
                bmp->line[y][x] = c
#define         FAST_GETPIXEL(bmp, x, y, c)  if (x >= bmp->cl) if (y >= bmp->ct) \
                if (x < bmp->cr) if (y < bmp->cb) \
                c = bmp->line[y][x]
// Eri tavaroiden definet

#define         ITEM_PISTOL             0
#define         ITEM_MACHINEGUN         1
#define         ITEM_BAZOOKA            2
#define         ITEM_LAVATRAP           3
#define         ITEM_SUPERLAVATRAP      4
#define         ITEM_SHOTGUN            5
#define         ITEM_MAGNUM             6
#define         ITEM_GRENADE            7
#define         ITEM_HMISLAUNCHER       8
#define         ITEM_LASERRIFLE         9
#define         ITEM_LASERPISTOL       10
#define         ITEM_PLATE             11
#define         ITEM_REINFPLATE        12
#define         ITEM_PICKAXE           13
#define         ITEM_DRILL             14
#define         ITEM_LAVABOMB          15
#define         ITEM_PLASMAPISTOL      16
#define         ITEM_TARGETINGSYSTEM   17
#define         ITEM_MEDIKIT           18
#define         ITEM_HEAVYPLASMA       19
#define         ITEM_SNIPERRIFLE       20
#define         ITEM_CAMOUFLAGE        21
#define         ITEM_BIGMACHINEGUN     22
#define         ITEM_PARACHUTE         23
#define         ITEM_LASERSABRE        24
#define         ITEM_SELFDESTRUCTOR    25
#define         ITEM_LASERCANNON       26


#define         ITEM_LAVA       1000
#define         ITEM_FALL       1001

// Eri bullettien nimet
#define         BUL_PISTOL       0
#define         BUL_BLOOD        1
#define         BUL_GORE         2
#define         BUL_BULLETSHELL  3
#define         BUL_SMOKE        4
#define         BUL_SHOTGUNSHELL 5
#define         BUL_GRENADE      6
#define         BUL_ROCKET       7
#define         BUL_HOMER        8
#define         BUL_PLASMA       9
#define         BUL_LAVABOMB    10
#define         BUL_PLASMA2     11
#define         BUL_PLASMA3     12
#define         BUL_SHRAPNEL    13
#define         BUL_BIGLASER    14

#define         BUL_DIRT        2000

// Ensimmäiset kolme ovat pelaajien päämajoja
#define         BLD_LAVATRAP         3
#define         BLD_SUPERLAVATRAP    4
#define         BLD_PLATE            5
#define         BLD_REINFPLATE       6

#define         VEH_WALKER           0
#define         VEH_TRANSPORT        1


#define         ACTION_SETPLATE      1
#define         ACTION_SNIPER        2
#define         ACTION_SABRE         3
#define         ACTION_LASERCANNON   4

#define MAXRANDOM       100000
int Frame1, Frame2;
time_t Clock1, Clock2, Framecount;
float Fps;

int *Random = new int[MAXRANDOM];
int Randloc = 0;
int Nextbot=-1, Botsalive=0;
// Onko dirtsample päällä
bool  Dirtsample = false;
bool Expsample = false;
// Clippausrajat
int Clipx1, Clipy1 ,Clipx2, Clipy2, Clipx, Clipy;
int Lavacount=0;
int Keyboard_update_counter = 0;
int Game_logic_update_counter = 0;

// Maindatti
Tmaindat * Md;
Tlevel   * Lev;
Tadditional_data * Add;
BITMAP * Parallax;

char * Burn;

// Makrot Burn kartan käsittelyyn
#define Putlava(x, y)           Burn[(y>>2)*(Lev->Mapsizex>>2)+(x>>2)] = 1
#define Dellava(x, y)           Burn[(y>>2)*(Lev->Mapsizex>>2)+(x>>2)] = 0
#define Getlava(x, y)           Burn[(y>>2)*(Lev->Mapsizex>>2)+(x>>2)]

void Getmoments(int x1, int y1, int x2, int y2, int *mx, int *my);
void Keyboard_timer_routine();
void Game_logic_timer_routine();
void Update_clock();
int Rand();
fixed Suunta(fixed s);                  // clippaa suunnan rajoihin 0 - 255 << 16
int Delta(long a1, long a2);            // Delta? Delta. Delta!!!
int Direction(int x1,int y1,int x2,int y2); // Suunta Arctanilla
int Distance(int x1,int y1,int x2,int y2); // Etäisyys pytagoraalla
int Quickdist(int x1,int y1,int x2,int y2); // Etäisyys (deltax+deltay)/2
#ifndef EDITOR
void Search_free_place_for_bot(int *x, int *y);
void Format();                          // Alustaa pelin tiedot
void Addvehicle(int X, int Y, int Mx, int My, int Type);
void Addlava(int X, int Y, int Mx, int My, char spire); // Lisää laavaa
void Addexp(int Type, int X, int Y, char breaka, char owner, char ownertype);        // Lisää räjähdyksen
void Addbuilding(int Type, int X, int Y, int Mx, int My); // Lisää rakennuksen
// Kolme eri versiota Shootista
void Shoot(int Type, int X, int Y, int Mx, int My);
void Shoot(int Type, int X, int Y, int Mx, int My, int Dat);
void Shoot(int Type, int X, int Y, int Mx, int My, int Dat, int Owner, char ownertype);
void Shoot(int Type, int X, int Y, int Mx, int My, int Dat, int Owner, char ownertype, int Dir);
// Luo rakennuksen tyyppiä Type koordinaattiin X, Y. Se liikkuu Mx, My ja on Ownerin omistuksessa.
void Create_building(int Type, int X, int Y, int Mx, int My, int Owner);
bool Feet_on_ground(int Count); // Onko pelaajalla(Count) jalat maassa?
bool Bot_feet_on_ground(int Count); // Onko botilla(Count) jalat maassa?
bool Vehicle_feet_on_ground(int Count); // Onko botilla(Count) jalat maassa?
int  Distance_to_surface(int Count); // etäisyys maasta pelaajalla(Count)
int  Distance_from_surface(int Count); // etäisyys maasta pelaajalla(Count)
int Bot_distance_to_surface(int Count); // etäisyys maasta botilla(Count)
int Vehicle_distance_to_surface(int Count); // etäisyys maasta botilla(Count)
void Player_Hitground(int Count); // Osuuko pelaaja(count) maahan?
void Player_bounce_check(int Count); // Kimmotus kartan reunasta
void Vehicle_bounce_check(int Count); // Kimmotus kartan reunasta
void Bot_bounce_check(int Count); // Kimmotus kartan reunasta
void Player_walk(int Count); // Pelaajan(Count) Kävely
void Update_ninjarope(int i); // Päivittää pelaajan(i) ninjaropea
void Update_bot_ninjarope(int i); // Päivittää botin(i) ninjaropea
void Calc_player_damages(); // Laskee pelaajien todelliset vauriot
void Calc_bot_damages(); // Laskee bottien todelliset vauriot
void Randomlavahit(int i); // Satunnainen osuma laavasta
void Fall_damage(int i);
void Update_inventory(int i); // Päivittää inventaariota
void Update_laserrifle(int i, int i2); // Jos ammutaan laserriflelllä
void Update_bot_laserrifle(int i, int i2); // Jos ammutaan laserriflelllä
void Test_camouflage(int i);
void Update_players(); // Päivittää pelaajia
void Update_vehicles(); // Päivittää vehicles
void Update_bots(); // Päivittää botteja
void Destroy_building(int i); // Tuhoaa rakennuksen
void Kill_player(int i, int weapon, int Killer, char killertype); // Tappaa pelaajan(i) aseella weapon ja tappaja on killer
void Kill_bot(int i, int weapon, int Killer, char killertype); // Tappaa botin(i) aseella weapon ja tappaja on killer
void Explode_player(int i, int Killer, char killertype); // Räjäyttää pelaajan
void Explode_bot(int i, int Killer, char killertype); // Räjäyttää botin
void Yummy_explosion(int i, int Killer, char killertype); // -"-
void Yummy_bot_explosion(int i, int Killer, char killertype); // -"-
int Hit_player(int P, int X, int Y); // Palauttaa kohdan mihin osuu... (jos osuu)
int Hit_bot(int P, int X, int Y);  // Palauttaa kohdan mihin osuu... (jos osuu)
void Update_pistol(int i, int X, int Y); // Päivittää pistoolinluotia(i) pisteessä X, Y
void Update_dirt(int i, int X, int Y); // Päivittää maata(i) pisteessä X, Y
void Update_blood(int i, int X, int Y); // Päivittää verta(i) pisteessä X, Y
void Update_gore(int i, int X, int Y); // Päivittää ruumiinosaa(i) pisteessä X, Y
void Update_bulletshell(int i, int X, int Y); // Päivittää hylsyä(i) pisteessä X, Y
void Update_grenade(int i, int X, int Y); // Päivittää kranaattia pisteessä X, Y
void Update_lavabomb(int i, int X, int Y); // Päivittää laavapommia pisteessä X, Y
void Update_shrapnel(int i, int X, int Y); // Päivittää sirpaletta pisteessä X, Y
void Update_shotgunshell(int i, int X, int Y); // Päivittää hylsyä(i) pisteessä X, Y
void Update_smoke(int i, int X, int Y); // Päivittää savua(i) pisteessä X, Y
void Update_plasma(int i, int X, int Y); // Päivittää plasma-ammusta(i) pisteessä X, Y
void Update_plasma2(int i, int X, int Y); // Päivittää plasmaa(i) pisteessä X, Y
void Update_plasma3(int i, int X, int Y); // Päivittää plasmaa(i) pisteessä X, Y
int Dirvali(int S, int Ms);
void Rotateangle(int * Angle, int Dest);
void Update_rocket(int i, int X,int Y);
void Update_bullets(); // Päivittää bulletteja
void Emptypic(BITMAP * bmp, int x, int y, int typem, char dir);
bool Shockwave(int X1, int Y1, int X2, int Y2); // Paineallon tarkistus
bool Strictshockwave(int X1, int Y1, int X2, int Y2);
void Randomexphit(int i, int killer, char killertype);
void Bot_randomexphit(int i, int killer, char killertype);
void Update_explosions(); // Päivittää Räjähdyksiä
void Update_lava(); // --- Laavaa
int  Distance_to_uprock(int x, int y);
int  Distance_to_downrock(int x, int y);
void Update_spire(); // --- Laavasuihkuja
int  Destroylava(int x1, int y1, int x2, int y2); // tuhoaa alueelta laavan ja palauttaa tuhottujen laavapisteiden määrän
void Update_plate(int i);  // Päivittää platea
void Update_bld_lavatrap(int i);      // Päivittää lavatrappia
void Update_bld_superlavatrap(int i); // Päivittää superlavatrappia
void Update_buildings(); // --- rakennuksia
void Do_game_logic(); // Päivittää pelilogiikkaa
void Animate_players(); // Animoi pelaajia
void Animate_bots(); // Animoi botteja
void Animate_buildings(); // Animoi rakennuksia
void Animate(); // Animoi kaikkea
void Action_setplate(int Screen); // Laatan asettaminen
void Action_sniper(int Screen); // Sniper
void Draw_Background(int Screen); // Piirtää pelaajalle (SCREEN) ruudun
void Draw_ninjarope(int Screen, int Count2); // Piirtää Pelaajan (Screen) ruutuun Pelaajan(Count2) ninjaropen
void Draw_bot_ninjarope(int Screen, int Count2); // Piirtää Pelaajan (Screen) ruutuun Botin(Count2) ninjaropen
void Camouflage_bitmap(BITMAP * bmp, BITMAP * from, int p);
void Show_targeting_system(int Screen);
void Draw_Players(int Screen); // Piirtää pelaajat
void Draw_vehicles(int Screen); // piirtää ajoneuvot
void Draw_Bots(int Screen); // Piirtää botit
void Draw_Bullets(int Screen); // Piirtää bulletsit
void Draw_Playerdata(int Screen); // Näyttää hudin eli pelaajan tiedot
void Draw_Buildings(int Screen); // piirtää rakennukset
void Draw_Explosions(int Screen); // piirtää räjähdykset
void Draw_Lava(int Screen); // piirtää laavan
void Draw_Menus(int Screen); // piirtää menut
void Do_drawings(); // piirtää kaiken
#endif
void Setclipping(int mode); // Asettaa ruudun clippaukset
void Save(char * S); // Tallentaa kartan S nimellä'
unsigned char * Get_texture_colors(BITMAP * Tex);
void Put_texture();
void Createparallax(); // Tekee parallaxin
void Load(char * S); // Lataa kartan S nimellä
void Insertobject(int X, int Y, int type); // Asettaa karttaobjektin pisteeseen X, Y
void Deleteobject(int X, int Y); // Tuhoaa objektin X, Y pisteestä
void Setmapsize(int X, int Y); // Asettaa kartan koon
void Updatemap(); // Päivittää karttaa
void Showmap(int X1, int Y1, int X2, int Y2, int X, int Y); // Näyttää kartan ruudulla (X1 - X2, Y1 - Y2) pisteessä X, Y
void InitEngine(); // Käynnistää pelimoottorin
void DeInitEngine(); // Sammuttaa pelimoottorin
#ifndef EDITOR
void Defaults();                 // Options asetusten resetointi

#include "ai.h"
void Checkkeys(); // control.h
void Use_selfdestructor(int i); // items.h
#endif

void Getmoments(int x1, int y1, int x2, int y2, int *mx, int *my)
{
    int dx = x2-x1;
    int dy = y2-y1;
    int d = 0, neg=0;
    *mx = 0;
    *my = 0;

    if (abs(dx) < abs(dy)) d = 0;
    else d=1;
    switch(d)
    {
    case 0:
        if (dy < 0) neg = 1;
        break;
    case 1:
        if (dx < 0) neg = 1;
        break;
    };
    switch(d)
    {
    case 0:
        switch(neg)
        {
        case 0:
            *my = 1<<16;
            if (dx != 0) if (dy != 0)
                    *mx = int(dx*65535/abs(dy));
            break;
        case 1:
            *my = -(1<<16);
            if (dx != 0) if (dy != 0)
                    *mx = int(dx*65535/abs(dy));
            break;
        };
        break;
    case 1:
        switch(neg)
        {
        case 0:
            *mx = 1<<16;
            if (dx != 0) if (dy != 0)
                    *my = int(dy*65535/abs(dx));
            break;
        case 1:
            *mx = -(1<<16);
            if (dx != 0) if (dy != 0)
                    *my = int(dy*65535/abs(dx));
            break;
        };
        break;
    };
} // void Getmoments(int x1, int y1, int x2, int y2, int *mx, int *my)
void Keyboard_timer_routine()
{
    Keyboard_update_counter++;
} // void Keyboard_timer_routine()
END_OF_FUNCTION(Keyboard_timer_routine);
void Game_logic_timer_routine()
{
    Game_logic_update_counter++;
} // void Game_logic_timer_routine()
END_OF_FUNCTION(Game_logic_timer_routine);
void Update_clock()
{
    if (Framecount==0)
    {
        Frame1 = Frames;
        Clock1 = clock();
    } //   if (Framecount==0)
    Framecount++;
    if (Framecount>=100)
    {
        Frame2 = Frames;
        Clock2 = clock();
        Fps =  (float)(Frame2-Frame1) / (float)((Clock2-Clock1)/(float)91);
        Framecount = 0;
    } //   if (Framecount==0)
} // void Update_clock()
int Rand()
{
    if (Randloc>= MAXRANDOM) Randloc = 0;
    return Random[Randloc++];
} // int Rand()
fixed Suunta(fixed s)
{
    if (fixtoi(s) < 0) s = s + itofix(255); // jos pienempi kuin nolla niin +255
    if (fixtoi(s) > 255) s = s - itofix(255); // janiiin
    return(s);
} // Suunta
int Delta(int a1, int a2)
{
    return(abs(a2-a1)); // selvä juttu itseisarvo a2-a1 erotuksesta
} // Delta
int Direction(int x1,int y1,int x2,int y2)
{
    fixed s;
    fixed vx = Delta(x1,x2);     // vähän matikkaa
    fixed vy = Delta(y1,y2);

    if ((x1 != x2) && (y1 != y2))
        s =fatan2(vx,vy); // enemmän
    if (x2 < x1) if (y2 < y1)  s = itofix(255) - s;
    if (x2 > x1) if (y2 > y1)  s = itofix(128)-s;  // sitten suunta oikein
    if (x2 < x1) if (y2 > y1)  s = s + itofix(128);

    s = s + itofix(192);

    if (s > itofix(255)) s = s - itofix(255);
    if (s < 0) s = s + itofix(255);
    if (y2 == y1) if (x2 < x1) s = 0;
    if (y2 == y1) if (x2 > x1) s = itofix(128);
    if (x2 == x1) if (y2 < y1) s = itofix(192);
    if (x2 == x1) if (y2 > y1) s = itofix(64);
    s = Suunta(s);
    return(s);
}
int Distance(int x1,int y1,int x2,int y2)
{
    int Dx = Delta(x1,x2);
    int Dy = Delta(y1,y2);

    int A = int(sqrt(Dx*Dx+Dy*Dy)); // Pytagoraan a^2 + b^2 = c^2
    return(A);
} // fixed Distance(int x1,int y1,int x2,int y2)
int Quickdist(int x1,int y1,int x2,int y2)
{
    int A = abs((x2-x1)+(y2-y1))>>1;
    return(A);
} // fixed Distance(int x1,int y1,int x2,int y2)

#ifndef EDITOR
void Search_free_place_for_bot(int *x, int *y)
{
    bool Found = false;
    char Apu = 0;
    int Dist = Clipx+20;
    if (Clipy > Dist) Dist = Clipy+20;
    do
    {
        *x = Rand()%Lev->Mapsizex;
        *y = Rand()%Lev->Mapsizey;
        for (int i2 = 0; i2 < Lev->Mapsizey; i2++)
            if (getpixel(Md->Map, *x, *y) == 0) *y = (*y) + 1;
            else i2 = Lev->Mapsizey;
        *y = (*y) - 6;
        Apu = 0;
        for (int i = 0; i < Opt->Players; i++)
            if (Distance(*x, *y, Md->Pl[i].X BitR, Md->Pl[i].Y BitR) > Dist) Apu++;
        if (getpixel(Md->Map, *x, (*y)-1) == 0)
            if (Apu == Opt->Players) Found = true;
    } while (!Found);
    *x = (*x) << 16;
    *y = (*y) << 16;
} // void Search_free_place_for_bot(int *x, int *y)
void Format()
{
    Setclipping(-1);
    memset(&Md->Bul, 0, sizeof(Tbullet)*Maxbullets);
    memset(&Md->Bld, 0, sizeof(Tbuilding)*Maxbuildings);
    memset(&Md->Lava, 0, sizeof(Tlava)*Maxlava);
    memset(&Md->Pl, 0, sizeof(Tplayer)*Maxplayers);
    for (int i = 0; i < Opt->Players; i++) // Pelaajat resetoidaan
    {
        memset(&Md->Pl[i], 0, sizeof(Tplayer)); // Nollaus
        Md->Pl[i].Armor[0] = 0;
        Md->Pl[i].Armor[1] = 0; // Panssari päälle
        Md->Pl[i].Armor[2] = 0;
        Md->Pl[i].Money = Opt->Startcash; // Rahaa
        for (int i2 = 0; i2 < 3; i2++) // Ei damagea
            Md->Pl[i].Damage[i2] = 0;
        Md->Pl[i].Item = ITEM_PISTOL; // Pistooli käteeen
        Md->Pl[i].Gun = Weapongunpic[Md->Pl[i].Item]; // Pistoolinpiippu
        Md->Pl[i].Stuff[Md->Pl[i].Item] = 1; // Eli yks pistooli reppanissa
        Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] = Clipsize[Md->Pl[i].Item]*3; // ja kuteja
        Md->Pl[i].S = 1; // Oikealle katso
        Md->Pl[i].Lives = Opt->Lives; // elämiä
        Md->Pl[i].Live = true; // ELOSSA?
        Md->Pl[i].X  = (Lev->Startpoint[i][0]) BitL; // Alotuspaikka
        Md->Pl[i].Y  = (Lev->Startpoint[i][1]) BitL;
        Md->Pl[i].Sx = Lev->Startpoint[i][0] - (Clipx>>1); // Ruudun paikka
        Md->Pl[i].Sy = Lev->Startpoint[i][1] - (Clipy>>1);

        Md->Pl[i].Menu = -1; // Ei menuja päälle

        Md->Bld[i].Live = true; // Päämajat
        Md->Bld[i].X = Md->Pl[i].X-(((BITMAP*) Dat[DATBLD0001].dat)->w>>1);
        Md->Bld[i].Pic = 0;
        Md->Bld[i].Anim = 0;
        Md->Bld[i].Y = Md->Pl[i].Y;
        Md->Bld[i].Type = i; // pelaajan tyyppinen
        Md->Bld[i].Energy = Bldenergy[i];

    } // for (int i = 0; i < Maxplayers; i ++)
    memset(&Md->Bot, 0, sizeof(Tbot)*Maxbots); // Nollaus
    char Copybots[Difbotweapons];
    memcpy(&Copybots, &Opt->Botweapons, Difbotweapons);
    Opt->Bots = 0;
    for (int i2 = 0; i2 < Difbotweapons; i2++) Opt->Bots += Copybots[i2];
    if (Opt->Gametype == GAMETYPE_BOTHUNT)
        for (int i = 0; i < Opt->Bots; i++)
        {
            Md->Bot[i].S = 1; // Oikealle katso
            Search_free_place_for_bot(&Md->Bot[i].X, &Md->Bot[i].Y);
            Md->Bot[i].Live = true;
            Md->Bot[i].Target = -1;
            int Next = 0;
            for (int i2 = 0; i2 < Difbotweapons; i2++) if (Copybots[i2]) {
                    Copybots[i2]--;
                    Next = i2;
                    i2=Difbotweapons;
                }
            int Wep = Next;
            Md->Bot[i].Search_range = BOT_SEARCH_RANGE;
            switch(Wep)
            {
            case 0:
                Md->Bot[i].Item = ITEM_PISTOL;
                break;
            case 1:
                Md->Bot[i].Item = ITEM_SHOTGUN;
                break;
            case 2:
                Md->Bot[i].Item = ITEM_MACHINEGUN;
                break;
            case 3:
                Md->Bot[i].Item = ITEM_BAZOOKA;
                break;
            case 4:
                Md->Bot[i].Item = ITEM_HMISLAUNCHER;
                break;
            case 5:
                Md->Bot[i].Item = ITEM_PLASMAPISTOL;
                break;
            case 6:
                Md->Bot[i].Item = ITEM_LASERRIFLE;
                Md->Bot[i].Search_range = BOT_SEARCH_RANGE*4;
                break;
            case 7:
                Md->Bot[i].Item = ITEM_MAGNUM;
                break;
            case 8:
                Md->Bot[i].Item = ITEM_SNIPERRIFLE;
                break;
            }; //       switch(Wep)
            Md->Bot[i].Gun = Weapongunpic[Md->Bot[i].Item]; // Pistoolinpiippu
        } //    for (int i = 0; i < Opt->Bots; i++)
} // Format

void Addvehicle(int X, int Y, int Mx, int My, int Type)
{
    for (int i = 0; i < Maxvehicles; i++)
        if (Md->Veh[i].Live == false)
        {
            memset(&Md->Veh[i], 0, sizeof(Tvehicle));
            Md->Veh[i].X = X;
            Md->Veh[i].Live = true;
            Md->Veh[i].Y = Y;
            Md->Veh[i].Mx = Mx;
            Md->Veh[i].My = My;
            Md->Veh[i].S = 1;
            Md->Veh[i].Type = Type;
            i = Maxvehicles;
        } //   for (int i = 0; i < Maxvehicles; i++)   if (Md->Veh[i].Live == false)
} // void Addvehicle(int X, int Y, int Mx, int My, int Type)
void Addlava(int X, int Y, int Mx, int My, char spire)
{
    int Max= (spire==1) ? Maxspirelava : Maxlava;
    for (int i = Max-1; i >= 0; i--)
        if (Md->Lava[i].Live==false)
        {
            Md->Lava[i].C = 32; // Väri
            Md->Lava[i].X = X;
            Md->Lava[i].Y = Y;
            Md->Lava[i].Mx = Mx; // Nopeusvektori
            Md->Lava[i].My = My;
            Md->Lava[i].Life = Maxlavalife-Rand()%100; // Elämä
            Md->Lava[i].Live = true;
            i = -1;
        } //     if (Md->Lava[i].Live==false)
} // Addlava
void Addexp(int Type, int X, int Y, char breaka, char owner, char ownertype)
{
    for (int i = 0; i < Maxexp; i++)
        if (Md->Exp[i].Live == false)
        {
            Md->Exp[i].Onlyonce = false;
            Md->Exp[i].Sampled = false;
            Md->Exp[i].Check  = false;
            Md->Exp[i].Owner = owner;
            Md->Exp[i].Ownertype = ownertype;
            Md->Exp[i].Break = breaka;
            Md->Exp[i].Term = false;
            Md->Exp[i].Live = true;
            Md->Exp[i].Delay = Rand()%5;
            Md->Exp[i].X = X;
            Md->Exp[i].Y = Y;
            Md->Exp[i].Type = Type;
            switch (Md->Exp[i].Type)
            {
            case 0:
                Md->Exp[i].Frame = a01Exp; // eri räjähdyksien alkuframet
                break; // 0
            case 1:
                Md->Exp[i].Frame = a09Exp;
                break; // 1
            case 2:
                Md->Exp[i].Frame = a23Exp;
                break; // 2
            case 3:
                Md->Exp[i].Frame = a29Exp;
                break; // 3
            case 4:
                Md->Exp[i].Frame = a35Exp;
                break; // 3
            case 5:
                Md->Exp[i].Frame = a41Exp;
                break; // 3
            case 6:
                Md->Exp[i].Frame = DATLASER01;
                break;
            }; // switch (Md->Exp[i].Type)

            i = Maxexp;
        } //   for (int i = 0; i < Maxexp; i++) if (Md->Exp[i].Live == false)

} // Addexp(int Type, int X, int Y)
void Addbuilding(int Type, int X, int Y, int Mx, int My)
{
    for (int i = 0; i < Maxbuildings; i++)
        if (Md->Bld[i].Live == false)
        {
            memset(&Md->Bld[i], 0, sizeof(Tbuilding));
            Md->Bld[i].Live = true;
            Md->Bld[i].X = X;
            Md->Bld[i].Y = Y;
            Md->Bld[i].Mx = Mx; // Nopeusvektori
            Md->Bld[i].My = My;
            Md->Bld[i].Type = Type;
            i = Maxbuildings;
        } // if (Md->Bld[i].Live == false)
} // Addbuilding(int Type, int X, int Y, int Mx, int My)

void Shoot(int Type, int X, int Y, int Mx, int My)
{
    Shoot(Type, X, Y, Mx, My, 0, 0, 0, 0); // Ampuu bulletin Type
} // Shoot(int Type, int X, int Y, int Mx, int My)
void Shoot(int Type, int X, int Y, int Mx, int My, int Dat)
{
    Shoot(Type, X, Y, Mx, My, Dat, 0, 0, 0);
} // Shoot(int Type, int X, int Y, int Mx, int My, int Dat)
void Shoot(int Type, int X, int Y, int Mx, int My, int Dat, int Owner, char ownertype)
{
    Shoot(Type, X, Y, Mx, My, Dat, Owner, ownertype, 0);
} // Shoot(int Type, int X, int Y, int Mx, int My, int Dat)
void Shoot(int Type, int X, int Y, int Mx, int My, int Dat,int Owner, char ownertype, int Dir)
{
    for (int i = 0; i < Maxbullets; i++)
        if (Md->Bul[i].Live==false)
        {
            memset(&Md->Bul[i], 0, sizeof(Tbullet));
            for (int Count = 0; Count < 10; Count++)
                Md->Bul[i].Dat[Count] = 0;
            Md->Bul[i].Dir = Dir;
            Md->Bul[i].Dat[0] = Dat;
            Md->Bul[i].Type = Type;
            Md->Bul[i].X    = X;
            Md->Bul[i].Y    = Y;
            Md->Bul[i].Mx   = Mx;
            Md->Bul[i].My   = My;
            Md->Bul[i].Live = true;
            Md->Bul[i].Life = 2000;
            if (Type == BUL_GRENADE)      Md->Bul[i].Life = 200;
            Md->Bul[i].Owner = Owner;
            Md->Bul[i].Ownertype = ownertype;
            i = Maxbullets;
        } //     if (Md->Bul[i].Live==false)
} // Shoot(int Type, int X, int Y, int Mx, int My)
void Create_building(int Type, int X, int Y, int Mx, int My, int Owner)
{
    for (int i = 0; i < Maxbuildings; i++) if (Md->Bld[i].Live == false)
        {
            // Nollataan rakennuksen data
            memset(&Md->Bld[i], 0, sizeof(Tbuilding));
            Md->Bld[i].Live  = true; // herätetään eloon

            Md->Bld[i].Energy = Bldenergy[Type];
            Md->Bld[i].Type  = Type; // asetetaan tiedot
            Md->Bld[i].X     = X;
            Md->Bld[i].Y     = Y;
            Md->Bld[i].Mx    = Mx;
            Md->Bld[i].My    = My;
            Md->Bld[i].Owner = Owner;

            i = Maxbuildings; // ei haluta Maxbuildings määrää rakennuksia
        } // for (int i = 0; i < Maxbuildings; i++)
} // Create_building(int Type, int X, int Y, int Mx, int My, int Owner)
bool Feet_on_ground(int Count)
{
    // eli jos vähän ukon alta löytyvä pikseli != 0 niin maassa ollaan
    if (getpixel(Md->Map, (Md->Pl[Count].X BitR),(Md->Pl[Count].Y BitR)+7)==0) return(false);
    return(true);
} // FeetOnground
bool Bot_feet_on_ground(int Count)
{
    // eli jos vähän ukon alta löytyvä pikseli != 0 niin maassa ollaan
    if (getpixel(Md->Map, (Md->Bot[Count].X BitR),(Md->Bot[Count].Y BitR)+7)==0) return(false);
    return(true);
} // FeetOnground
bool Vehicle_feet_on_ground(int Count)
{
    // eli jos vähän ukon alta löytyvä pikseli != 0 niin maassa ollaan
    if (getpixel(Md->Map, (Md->Veh[Count].X BitR),(Md->Veh[Count].Y BitR)+8)==0) return(false);
    return(true);
} // FeetOnground
int Distance_to_surface(int Count)
{
    // ollaanko maassa? jos ollaan niin kuinka kaukana
    for (int d = 0; d < 10; d++)
        if (getpixel(Md->Map,(Md->Pl[Count].X BitR),(Md->Pl[Count].Y BitR)+7-d)==0) return(d);
    return(100); // muuten 100
} // DistanceToSurface
int Distance_from_surface(int Count)
{
    // ollaanko maassa? jos ollaan niin kuinka kaukana
    for (int d = 0; d < 15; d++)
        if (getpixel(Md->Map,(Md->Pl[Count].X BitR),(Md->Pl[Count].Y BitR)+7+d)!=0) return(d);
    return(100); // muuten 100
} // DistanceToSurface
int Bot_distance_to_surface(int Count)
{
    // ollaanko maassa? jos ollaan niin kuinka kaukana
    for (int d = 0; d < 10; d++)
        if (getpixel(Md->Map,(Md->Bot[Count].X BitR),(Md->Bot[Count].Y BitR)+7-d)==0) return(d);
    return(100); // muuten 100
} // DistanceToSurface
int Vehicle_distance_to_surface(int Count)
{
    // ollaanko maassa? jos ollaan niin kuinka kaukana
    for (int d = 0; d < 10; d++)
        if (getpixel(Md->Map,(Md->Veh[Count].X BitR),(Md->Veh[Count].Y BitR)+8-d)==0) return(d);
    return(100); // muuten 100
} // DistanceToSurface

void Player_Hitground(int Count)
{
    Md->Pl[Count].My = 0; // Nopeusvektori y pysähtyy törmätessä

    int D = Distance_to_surface(Count); // Etäisyys maasta
    if (Md->Pl[Count].Mx != 0) // Jos liikutaan vähänkin sivulle niin
    {

        if (D < 6) Md->Pl[Count].Y -= (D) BitL; // pieni pomppu (tosi pieni)
        else
        {
            Md->Pl[Count].Mx = 0;             // Täysi pysähtyminen
            Md->Pl[Count].My = 0;             // ja vanhat koordit paikalleen
            Md->Pl[Count].X = Md->Pl[Count].Ox;
            Md->Pl[Count].Y = Md->Pl[Count].Oy;
        } // else (D < 6)
    } // (Mx != 0
    if (Md->Pl[Count].FeetOnGround) Md->Pl[Count].Mx = 0; // Jos jalat maassa
    // niin nopeusvektori x
    // pois(kunnon kitka miehen tiellä pitää)



} // Player_Hitground
void Player_bounce_check(int Count)
{
    for (int i = 0; i < Opt->Players; i++) if (Md->Pl[i].Live) if (i != Count)
            {
                int X1, Y1, X2, Y2;
                X1 = Md->Pl[Count].X BitR;
                Y1 = Md->Pl[Count].Y BitR;
                X2 = Md->Pl[i].X BitR;
                Y2 = Md->Pl[i].Y BitR;
                if (Y1+3 >= Y2-3)
                    if (Y1-3 <= Y2+3)
                    {
                        if (X1+4 > X2-4)
                            if (X1+4 < X2)
                            {
                                Md->Pl[Count].Mx = -(Md->Pl[Count].Mx); // Bounce = -(Mx / 2)
                            }
                        if (X1-4 > X2)
                            if (X1-4 < X2+4)
                            {
                                Md->Pl[Count].Mx = abs(Md->Pl[Count].Mx); // Bounce = (Mx / 2)
                            }
                    }

            } //    for (int i = 0; i < Opt->Bots; i++)
    for (int i = 0; i < Opt->Bots; i++) if (Md->Bot[i].Live)
        {
            int X1, Y1, X2, Y2;
            X1 = Md->Pl[Count].X BitR;
            Y1 = Md->Pl[Count].Y BitR;
            X2 = Md->Bot[i].X BitR;
            Y2 = Md->Bot[i].Y BitR;
            if (Y1+3 >= Y2-3)
                if (Y1-3 <= Y2+3)
                {
                    if (X1+4 > X2-4)
                        if (X1+4 < X2)
                        {
                            Md->Pl[Count].Mx = -(Md->Pl[Count].Mx); // Bounce = -(Mx / 2)
                        }
                    if (X1-4 > X2)
                        if (X1-4 < X2+4)
                        {
                            Md->Pl[Count].Mx = abs(Md->Pl[Count].Mx); // Bounce = (Mx / 2)
                        }
                }

        } //    for (int i = 0; i < Opt->Bots; i++)

    if (Md->Pl[Count].X < 0) // X pienempi ku ruudun reunat
    {
        Md->Pl[Count].Mx = abs(Md->Pl[Count].Mx) >> 1; // Bounce = Mx / 2
        Md->Pl[Count].X = Md->Pl[Count].Ox; // Vanhat koordit
        Md->Pl[Count].Y = Md->Pl[Count].Oy;
    } // (Md->Pl[Count].X < 0)
    if (Md->Pl[Count].Y < 0) // Yläbounce
    {
        Md->Pl[Count].X = Md->Pl[Count].Ox; // Vanhat koordit
        Md->Pl[Count].Y = Md->Pl[Count].Oy;
        Md->Pl[Count].My = 0; // Vapaa tippuminen ei bouncea
    } // (Md->Pl[Count].Y < 0)

    if ((Md->Pl[Count].X BitR)> Lev->Mapsizex-5) // Oikea reuna
    {
        Md->Pl[Count].Mx = -(Md->Pl[Count].Mx>>1); // Bounce = -(Mx / 2)
        Md->Pl[Count].X = Md->Pl[Count].Ox; // Vanhat koordit
        Md->Pl[Count].Y = Md->Pl[Count].Oy;
    } // (Md->Pl[Count].X BitR < Lev->Mapsizex-1)
    if (Md->Pl[Count].Y BitR> Lev->Mapsizey-5) // Alareuna
    {
        Md->Pl[Count].Live = false; // Kuolu tulee
    } // (Md->Pl[Count].Y BitR < Lev->Mapsizey-1)
} // Player_bounce_check
void Vehicle_bounce_check(int Count)
{
    Md->Veh[Count].Bounce = false;
    for (int i = 0; i < Opt->Players; i++) if (Md->Pl[i].Live)
        {
            int X1, Y1, X2, Y2;
            X1 = Md->Veh[Count].X BitR;
            Y1 = Md->Veh[Count].Y BitR;
            X2 = Md->Pl[i].X BitR;
            Y2 = Md->Pl[i].Y BitR;
            if (Y1+3 >= Y2-3)
                if (Y1-3 <= Y2+3)
                {
                    if (X1+4 > X2-4)
                        if (X1+4 < X2)
                        {
                            Md->Veh[Count].Bounce = true;
                            Md->Veh[Count].Mx = -(Md->Veh[Count].Mx); // Bounce = -(Mx / 2)
                        }
                    if (X1-4 > X2)
                        if (X1-4 < X2+4)
                        {
                            Md->Veh[Count].Bounce = true;
                            Md->Veh[Count].Mx = abs(Md->Veh[Count].Mx); // Bounce = (Mx / 2)
                        }
                }

        } //    for (int i = 0; i < Opt->Bots; i++)
    for (int i = 0; i < Opt->Bots; i++) if (Md->Veh[i].Live) if (i != Count)
            {
                int X1, Y1, X2, Y2;
                X1 = Md->Veh[Count].X BitR;
                Y1 = Md->Veh[Count].Y BitR;
                X2 = Md->Veh[i].X BitR;
                Y2 = Md->Veh[i].Y BitR;
                if (Y1+3 >= Y2-3)
                    if (Y1-3 <= Y2+3)
                    {
                        if (X1+4 > X2-4)
                            if (X1+4 < X2)
                            {
                                Md->Veh[Count].Bounce = true;
                                Md->Veh[Count].Mx = -(Md->Veh[Count].Mx); // Bounce = -(Mx / 2)
                            }
                        if (X1-4 > X2)
                            if (X1-4 < X2+4)
                            {
                                Md->Veh[Count].Bounce = true;
                                Md->Veh[Count].Mx = abs(Md->Veh[Count].Mx); // Bounce = (Mx / 2)
                            }
                    }

            } //    for (int i = 0; i < Opt->Bots; i++)

    if (Md->Veh[Count].X < 0) // X pienempi ku ruudun reunat
    {
        Md->Veh[Count].X = Md->Veh[Count].Ox; // Vanhat koordit
        Md->Veh[Count].Y = Md->Veh[Count].Oy;
        Md->Veh[Count].Mx = abs(Md->Veh[Count].Mx) >> 1; // Bounce = Mx / 2
    } // (Md->Veh[Count].X < 0)
    if (Md->Veh[Count].Y < 0) // Yläbounce
    {
        Md->Veh[Count].Bounce = true;
        Md->Veh[Count].X = Md->Veh[Count].Ox; // Vanhat koordit
        Md->Veh[Count].Y = Md->Veh[Count].Oy;
        Md->Veh[Count].My = 0; // Vapaa tippuminen ei bouncea
    } // (Md->Veh[Count].Y < 0)

    if ((Md->Veh[Count].X BitR)> Lev->Mapsizex-5) // Oikea reuna
    {
        Md->Veh[Count].Mx = -(Md->Veh[Count].Mx>>1); // Bounce = -(Mx / 2)
        Md->Veh[Count].X = Md->Veh[Count].Ox; // Vanhat koordit
        Md->Veh[Count].Y = Md->Veh[Count].Oy;
    } // (Md->Veh[Count].X BitR < Lev->Mapsizex-1)
    if (Md->Veh[Count].Y BitR> Lev->Mapsizey-5) // Alareuna
    {
        Md->Veh[Count].Live = false; // Kuolu tulee
    } // (Md->Veh[Count].Y BitR < Lev->Mapsizey-1)
} // Vehicle_bounce_check

void Bot_bounce_check(int Count)
{
    Md->Bot[Count].Bounce = false;
    for (int i = 0; i < Opt->Players; i++) if (Md->Pl[i].Live)
        {
            int X1, Y1, X2, Y2;
            X1 = Md->Bot[Count].X BitR;
            Y1 = Md->Bot[Count].Y BitR;
            X2 = Md->Pl[i].X BitR;
            Y2 = Md->Pl[i].Y BitR;
            if (Y1+3 >= Y2-3)
                if (Y1-3 <= Y2+3)
                {
                    if (X1+4 > X2-4)
                        if (X1+4 < X2)
                        {
                            Md->Bot[Count].Bounce = true;
                            Md->Bot[Count].Mx = -(Md->Bot[Count].Mx); // Bounce = -(Mx / 2)
                        }
                    if (X1-4 > X2)
                        if (X1-4 < X2+4)
                        {
                            Md->Bot[Count].Bounce = true;
                            Md->Bot[Count].Mx = abs(Md->Bot[Count].Mx); // Bounce = (Mx / 2)
                        }
                }

        } //    for (int i = 0; i < Opt->Bots; i++)
    for (int i = 0; i < Opt->Bots; i++) if (Md->Bot[i].Live) if (i != Count)
            {
                int X1, Y1, X2, Y2;
                X1 = Md->Bot[Count].X BitR;
                Y1 = Md->Bot[Count].Y BitR;
                X2 = Md->Bot[i].X BitR;
                Y2 = Md->Bot[i].Y BitR;
                if (Y1+3 >= Y2-3)
                    if (Y1-3 <= Y2+3)
                    {
                        if (X1+4 > X2-4)
                            if (X1+4 < X2)
                            {
                                Md->Bot[Count].Bounce = true;
                                Md->Bot[Count].Mx = -(Md->Bot[Count].Mx); // Bounce = -(Mx / 2)
                            }
                        if (X1-4 > X2)
                            if (X1-4 < X2+4)
                            {
                                Md->Bot[Count].Bounce = true;
                                Md->Bot[Count].Mx = abs(Md->Bot[Count].Mx); // Bounce = (Mx / 2)
                            }
                    }

            } //    for (int i = 0; i < Opt->Bots; i++)

    if (Md->Bot[Count].X < 0) // X pienempi ku ruudun reunat
    {
        Md->Bot[Count].X = Md->Bot[Count].Ox; // Vanhat koordit
        Md->Bot[Count].Y = Md->Bot[Count].Oy;
        Md->Bot[Count].Mx = abs(Md->Bot[Count].Mx) >> 1; // Bounce = Mx / 2
    } // (Md->Bot[Count].X < 0)
    if (Md->Bot[Count].Y < 0) // Yläbounce
    {
        Md->Bot[Count].Bounce = true;
        Md->Bot[Count].X = Md->Bot[Count].Ox; // Vanhat koordit
        Md->Bot[Count].Y = Md->Bot[Count].Oy;
        Md->Bot[Count].My = 0; // Vapaa tippuminen ei bouncea
    } // (Md->Bot[Count].Y < 0)

    if ((Md->Bot[Count].X BitR)> Lev->Mapsizex-5) // Oikea reuna
    {
        Md->Bot[Count].Mx = -(Md->Bot[Count].Mx>>1); // Bounce = -(Mx / 2)
        Md->Bot[Count].X = Md->Bot[Count].Ox; // Vanhat koordit
        Md->Bot[Count].Y = Md->Bot[Count].Oy;
    } // (Md->Bot[Count].X BitR < Lev->Mapsizex-1)
    if (Md->Bot[Count].Y BitR> Lev->Mapsizey-5) // Alareuna
    {
        Md->Bot[Count].Live = false; // Kuolu tulee
    } // (Md->Bot[Count].Y BitR < Lev->Mapsizey-1)
} // Bot_bounce_check
void Player_walk(int Count)
{
    if (Md->Pl[Count].S == 0) // Eli vasemmalle
        if (Md->Pl[Count].Mx > -32000) // Pehmeä kiihtyminen
        {   //(16000 koska 16000 >> 16 = 0.245 jotain)
            if (Md->Pl[Count].FeetOnGround) // Jos jalat maassa kävellään nopsammin
                Md->Pl[Count].Mx -= 1000;
            else
                Md->Pl[Count].Mx -= 200; // Muuten liidellään
        } // if (Md->Pl[Count].S == 0)
    if (Md->Pl[Count].S == 1) // Oikealle
        if (Md->Pl[Count].Mx < 32000) // Pehmeä kiihtyminen
        {
            if (Md->Pl[Count].FeetOnGround) // Jos jalat maassa
                Md->Pl[Count].Mx += 1000;
            else
                Md->Pl[Count].Mx += 200; // Liidellään
        } // if (Md->Pl[Count].S == 1)

} // Player_walk(int Count)
void Bot_walk(int Count)
{
    if (Md->Bot[Count].S == 0) // Eli vasemmalle
        if (Md->Bot[Count].Mx > -32000) // Pehmeä kiihtyminen
        {   //(16000 koska 16000 >> 16 = 0.245 jotain)
            if (Md->Bot[Count].FeetOnGround) // Jos jalat maassa kävellään nopsammin
                Md->Bot[Count].Mx -= 1000;
            else
                Md->Bot[Count].Mx -= 200; // Muuten liidellään
        } // if (Md->Bot[Count].S == 0)
    if (Md->Bot[Count].S == 1) // Oikealle
        if (Md->Bot[Count].Mx < 32000) // Pehmeä kiihtyminen
        {
            if (Md->Bot[Count].FeetOnGround) // Jos jalat maassa
                Md->Bot[Count].Mx += 1000;
            else
                Md->Bot[Count].Mx += 200; // Liidellään
        } // if (Md->Bot[Count].S == 1)

} // Bot_walk(int Count)

void Update_ninjarope(int i)
{
    Md->Pl[i].Nx = Md->Pl[i].Nx + Md->Pl[i].Nmx; // Oikea äks = oikea äks + nopeusvektori äks
    Md->Pl[i].Ny = Md->Pl[i].Ny + Md->Pl[i].Nmy; // Oikea yy = oikea yy + nopeusvektoriy yy
// kartan reunat:
    if (Md->Pl[i].Nx < 0) Md->Pl[i].Nx = 0;
    if (Md->Pl[i].Ny < 0) Md->Pl[i].Ny = 0;
    if (Md->Pl[i].Nx BitR> Lev->Mapsizex-1) Md->Pl[i].Nx = (Lev->Mapsizex-1) BitL;
    if (Md->Pl[i].Ny BitR> Lev->Mapsizey-1) Md->Pl[i].Ny = (Lev->Mapsizey-1) BitL;
// ***************
    Md->Pl[i].Nmy += Gravity<<1;

    // Eli ihme juttu ku ninjaropeen vaikuttaa vaan puolikas painovoima
    if (getpixel(Md->Map, Md->Pl[i].Nx BitR, Md->Pl[i].Ny BitR)>0) // Jos maassa kii
    {
        Md->Pl[i].Nmx = 0; // Pysähdys nopeusvektoreille
        Md->Pl[i].Nmy = 0;

        int s = Direction(Md->Pl[i].X BitR, Md->Pl[i].Y BitR, Md->Pl[i].Nx BitR, Md->Pl[i].Ny BitR);
// Suunta Pelaajan ja köyden pään välillä
        Md->Pl[i].Ropelength = Distance(Md->Pl[i].X BitR, Md->Pl[i].Y BitR, Md->Pl[i].Nx BitR, Md->Pl[i].Ny BitR);
// Köyden pituus
        if (Md->Pl[i].Ninjaground == false)        // Joskus tulevaisuudessa
            Md->Pl[i].Ropeset = Md->Pl[i].Ropelength; // voi (ehkä) itse säätään nartsan pituuden

        Md->Pl[i].Ninjaground = true;
        if (Opt->Realrope == false)
        {
            Md->Pl[i].Ninjadir = s;

            int a = (fcos(s)*Md->Pl[i].Ropelength*18);
            Md->Pl[i].Ntx = fixtoi(a); // Pullllll power x eli paljon pelaajaa kiskotaan

            a = (fsin(s)*Md->Pl[i].Ropelength*18);
            Md->Pl[i].Nty = fixtoi(a); // Pullllll power y
// Jos narun pituus on pienempi kuin narun haluttu pituus niin pelaajaa ei kiskota niin kovaa
            if (Md->Pl[i].Ropelength < Md->Pl[i].Ropeset )
            {
                Md->Pl[i].Mx += int(Md->Pl[i].Ntx * 0.3); // Pelaajan kiskomiset
                Md->Pl[i].My += int(Md->Pl[i].Nty * 0.3+100);
            } // if (Md->Pl[i].Ropelength < Md->Pl[i].Ropeset )
// Jos narun pituus on suurempi kuin narun haluttu pituus niin pelaajaa kiskotaan kovempaa
            if (Md->Pl[i].Ropelength > Md->Pl[i].Ropeset )
            {
                Md->Pl[i].Mx += int(Md->Pl[i].Ntx * 0.5); // Pelaajan kiskomiset
                Md->Pl[i].My += int(Md->Pl[i].Nty * 0.5)+100;
            } // if (Md->Pl[i].Ropelength > Md->Pl[i].Ropeset )
        } else// Realrope == false
        {
            if (Md->Pl[i].Ninjacheck==false)
            {
                Md->Pl[i].Nmdir = 0;
                Md->Pl[i].Ninjadir = Direction(Md->Pl[i].Nx BitR, Md->Pl[i].Ny BitR, Md->Pl[i].X BitR, Md->Pl[i].Y BitR);
                Md->Pl[i].Ninjacheck = true;
            } // if (Md->Pl[i].Ninjacheck==false)
            Md->Pl[i].Ninjadir += Md->Pl[i].Nmdir;
            if (Md->Pl[i].Ninjadir>>16 > 0) Md->Pl[i].Nmdir-=30;
            if (Md->Pl[i].Ninjadir>>16 < 0) Md->Pl[i].Nmdir+=30;
            if (Md->Pl[i].Nmdir > 0) Md->Pl[i].Nmdir-=3;
            if (Md->Pl[i].Nmdir < 0) Md->Pl[i].Nmdir+=3;

            int Nx = Md->Pl[i].Nx + fsin(Md->Pl[i].Ninjadir) * Md->Pl[i].Ropeset;
            int Ny = Md->Pl[i].Ny + fcos(Md->Pl[i].Ninjadir) * Md->Pl[i].Ropeset;
            if (getpixel(Md->Map, Nx>>16, Ny>>16)==0)
            {
                if ((Md->Pl[i].Ninjadir>>16 < 64) ||
                        (Md->Pl[i].Ninjadir>>16 > 192))
                {
                    int Ox = Md->Pl[i].X;
                    int Oy = Md->Pl[i].Y;
                    Md->Pl[i].X = Nx;
                    Md->Pl[i].Y = Ny;
                    Md->Pl[i].Mx = Delta(Ox, Md->Pl[i].X);
                    Md->Pl[i].My = Delta(Oy, Md->Pl[i].Y);
                }
            } else //    if (getpixel(Md->Map, Nx, Ny)==0)
            {
                Md->Pl[i].Mx = 0;
                Md->Pl[i].My = 0;
            } // else osuu maahan
        } // realrope == true
    } else// Ninjarope on maassa
    {
        Md->Pl[i].Ninjacheck = false;
        Md->Pl[i].Nmdir = 0;
    }
} // Update_ninjarope
void Update_bot_ninjarope(int i)
{
    Md->Bot[i].Nx = Md->Bot[i].Nx + Md->Bot[i].Nmx; // Oikea äks = oikea äks + nopeusvektori äks
    Md->Bot[i].Ny = Md->Bot[i].Ny + Md->Bot[i].Nmy; // Oikea yy = oikea yy + nopeusvektoriy yy
// kartan reunat:
    if (Md->Bot[i].Nx < 0) Md->Bot[i].Nx = 0;
    if (Md->Bot[i].Ny < 0) Md->Bot[i].Ny = 0;
    if (Md->Bot[i].Nx BitR> Lev->Mapsizex-1) Md->Bot[i].Nx = (Lev->Mapsizex-1) BitL;
    if (Md->Bot[i].Ny BitR> Lev->Mapsizey-1) Md->Bot[i].Ny = (Lev->Mapsizey-1) BitL;
// ***************
    Md->Bot[i].Nmy += Gravity<<1;

    // Eli ihme juttu ku ninjaropeen vaikuttaa vaan puolikas painovoima
    if (getpixel(Md->Map, Md->Bot[i].Nx BitR, Md->Bot[i].Ny BitR)>0) // Jos maassa kii
    {
        Md->Bot[i].Nmx = 0; // Pysähdys nopeusvektoreille
        Md->Bot[i].Nmy = 0;

        int s = Direction(Md->Bot[i].X BitR, Md->Bot[i].Y BitR, Md->Bot[i].Nx BitR, Md->Bot[i].Ny BitR);
// Suunta Pelaajan ja köyden pään välillä
        Md->Bot[i].Ropelength = Distance(Md->Bot[i].X BitR, Md->Bot[i].Y BitR, Md->Bot[i].Nx BitR, Md->Bot[i].Ny BitR);
// Köyden pituus
        if (Md->Bot[i].Ninjaground == false)        // Joskus tulevaisuudessa
            Md->Bot[i].Ropeset = Md->Bot[i].Ropelength; // voi (ehkä) itse säätään nartsan pituuden

        Md->Bot[i].Ninjaground = true;
        Md->Bot[i].Ninjadir = s;

        int a = (fcos(s)*Md->Bot[i].Ropelength*9);
        Md->Bot[i].Ntx = fixtoi(a); // Pullllll power x eli paljon pelaajaa kiskotaan

        a = (fsin(s)*Md->Bot[i].Ropelength*9);
        Md->Bot[i].Nty = fixtoi(a); // Pullllll power y
// Jos narun pituus on pienempi kuin narun haluttu pituus niin pelaajaa ei kiskota niin kovaa
        if (Md->Bot[i].Ropelength < Md->Bot[i].Ropeset )
        {
            Md->Bot[i].Mx += int(Md->Bot[i].Ntx * 0.2); // Pelaajan kiskomiset
            Md->Bot[i].My += int(Md->Bot[i].Nty * 0.2+100);
        } // if (Md->Bot[i].Ropelength < Md->Bot[i].Ropeset )
// Jos narun pituus on suurempi kuin narun haluttu pituus niin pelaajaa kiskotaan kovempaa
        if (Md->Bot[i].Ropelength > Md->Bot[i].Ropeset )
        {
            Md->Bot[i].Mx += int(Md->Bot[i].Ntx * 0.4); // Pelaajan kiskomiset
            Md->Bot[i].My += int(Md->Bot[i].Nty * 0.4)+100;
        } // if (Md->Bot[i].Ropelength > Md->Bot[i].Ropeset )
    } else// Ninjarope on maassa
    {
        Md->Bot[i].Ninjacheck = false;
        Md->Bot[i].Nmdir = 0;
    }
} // Update_ninjarope

void Calc_player_damages()
{
    // Lasketaan näytettävät pelaajien vahingot
    for (int i = 0; i < Opt->Players; i ++)
    {
        for (int i2 = 0; i2 < 3; i2++)
        {
            // Paljonko tarvitaan tappamaan pelaaja päälle, torsolle ja jaloille
            switch(i2)
            {
            case 0:
                Md->Pl[i].Killdamage[i2] = 2 + (Md->Pl[i].Armor[i2]*2);
                break;
            case 1:
                Md->Pl[i].Killdamage[i2] = 3 + (Md->Pl[i].Armor[i2]*2);
                break;
            case 2:
                Md->Pl[i].Killdamage[i2] = 4 + (Md->Pl[i].Armor[i2]*2);
                break;
            }; // switch(i2)
            // Vaikka pelaaja olisi ollut niin onnekas että osumat ovat tasaisesti
            // jakautuneet pitkin kehoa niin Totaldamage on se joka tappaa aina
            // Siis 5 + Armorit
            // Monta osumaa tarvitaan kokonaisvaltaisesti tappamaan pelaaja
            Md->Pl[i].Totaldamage = 5 + Md->Pl[i].Armor[0] + Md->Pl[i].Armor[1] + Md->Pl[i].Armor[2];
            Md->Pl[i].Hits[i2] = int(double((Md->Pl[i].Damage[i2])*3)/Md->Pl[i].Killdamage[i2]);
            // vahingon ja tappovahingon suhde kerrottuna kolmella
            // Jos on enemmän jostain syystä hitsejä kuin lääkäri määrää
            // esim. kuollessa niin clipataan ne kolmeen
            if (Md->Pl[i].Hits[i2] > 3) Md->Pl[i].Hits[i2] = 3;
        } // for (int i2 = 0; i2 < 3; i2++)

    } // for (int i = 0; i < Opt->Players;i ++)

} // Calc_player_damages()
void Calc_bot_damages()
{
    // Lasketaan näytettävät bottien vahingot
    for (int i = 0; i < Opt->Bots; i ++)
    {
        for (int i2 = 0; i2 < 3; i2++)
        {
            // Paljonko tarvitaan tappamaan pelaaja päälle, torsolle ja jaloille
            switch(i2)
            {
            case 0:
                Md->Bot[i].Killdamage[i2] = 2 + (Md->Bot[i].Armor[i2]*2);
                break;
            case 1:
                Md->Bot[i].Killdamage[i2] = 3 + (Md->Bot[i].Armor[i2]*2);
                break;
            case 2:
                Md->Bot[i].Killdamage[i2] = 4 + (Md->Bot[i].Armor[i2]*2);
                break;
            }; // switch(i2)
            // Vaikka botti olisi ollut niin onnekas että osumat ovat tasaisesti
            // jakautuneet pitkin kehoa niin Totaldamage on se joka tappaa aina
            // Siis 5
            // Monta osumaa tarvitaan kokonaisvaltaisesti tappamaan pelaaja
            Md->Bot[i].Totaldamage = 5 + Md->Bot[i].Armor[0] + Md->Bot[i].Armor[1] + Md->Bot[i].Armor[2];;
            Md->Bot[i].Hits[i2] = int(double((Md->Bot[i].Damage[i2])*3)/Md->Bot[i].Killdamage[i2]);
            // vahingon ja tappovahingon suhde kerrottuna kolmella
            // Jos on enemmän jostain syystä hitsejä kuin lääkäri määrää
            // esim. kuollessa niin clipataan ne kolmeen
            if (Md->Bot[i].Hits[i2] > 3) Md->Bot[i].Hits[i2] = 3;
        } // for (int i2 = 0; i2 < 3; i2++)

    } // for (int i = 0; i < Opt->Bots;i ++)

} // Calc_bot_damages()
void Randomlavahit(int i)
{
    int r = 0; // SAVUA pyöreästi
    for (int count = 0; count < 50; count++)
    {
        r = Suunta(itofix(Rand()%255) + Rand()%65535);
        Shoot(BUL_SMOKE, Md->Pl[i].X - 10000 + Rand()%20000, Md->Pl[i].Y - 10000 + Rand()%20000, (fcos(r)/50) - 1000 + Rand()%2000,(fsin(r)/50) - 1000 + Rand()%2000);
    }


    int Hit = 1+Rand()%3; // oZUMAkohta
    if (Hit > 0)
    {
        // jos vielä ei oo kuollut
        if (Md->Pl[i].Damage[Hit-1] < Md->Pl[i].Killdamage[Hit-1])
            Md->Pl[i].Damage[Hit-1]++;
        // jos kuolee yleisestio...
        if ((Md->Pl[i].Damage[0]) + (Md->Pl[i].Damage[1]) + (Md->Pl[i].Damage[2]) >= Md->Pl[i].Totaldamage)
        {
            Kill_player(i, ITEM_LAVA, -1, 0);
        } //                 if (Md->Pl[i].Damage[0] + Md->Pl[i].Damage[1] + Md->Pl[i].Damage[2] >= Md->Pl[i].Totaldamage)
        // tai joku ruumiinosa pettää
        if (Md->Pl[i].Damage[Hit-1] >= Md->Pl[i].Killdamage[Hit-1]) if (Md->Pl[i].Live)
            {
                Kill_player(i, ITEM_LAVA, -1, 0);
            } // if (Md->Pl[i].Damage[Hit-1]>2)
    } // if (Hit > 0)
} // Randomlavahit
void Fall_damage(int i)
{
    int Dodamage = 0;
    int Hit = 1+Rand()%3; // oZUMAkohta
    if ((abs(Md->Pl[i].Mx) > 60000) || (abs(Md->Pl[i].My) > 60000))
    {
        bool Doit = false;
        if (Md->Pl[i].Mx>0)
            if (getpixel(Md->Map, (Md->Pl[i].X>>16)+4, (Md->Pl[i].Y>>16)) > 0)
            {
                Doit = true;
                Hit = 2;
            }
        if (Md->Pl[i].Mx<0)
            if (getpixel(Md->Map, (Md->Pl[i].X>>16)-4, (Md->Pl[i].Y>>16)) > 0)
            {
                Doit = true;
                Hit = 2;
            }
        if (Doit)
        {
            for (int a = 0; a < (abs(Md->Pl[i].Mx)-60000)/(10000); a++)
                Dodamage++;
            Md->Pl[i].Mx = 0;
        } // if (Doit)
        Doit = false;
        if (Md->Pl[i].My>0)
            if (getpixel(Md->Map, (Md->Pl[i].X>>16), (Md->Pl[i].Y>>16)+8) > 0)
            {
                Doit = true;
                Hit = 3;
            }
        if (Md->Pl[i].My<0)
            if (getpixel(Md->Map, (Md->Pl[i].X>>16), (Md->Pl[i].Y>>16)-10) > 0)
            {
                Doit = true;
                Hit = 1;
            }

        if (Doit)
        {
            for (int a = 0; a < (abs(Md->Pl[i].My)-60000)/(10000); a++)
                Dodamage++;
            Md->Pl[i].My = 0;
        } // if (Doit)
    } //if ((abs(Md->Pl[i].Mx>>16) > 5) || (abs(Md->Pl[i].My>>16) > 5))

    for (int e = 0; e < Dodamage; e++)
    {
        for (int i2 = 0; i2 < 15; i2 ++) // verta... ei kuitenkaan niin paljon
        {
            int r = Rand()%255;
            int pow = rand()%50;
            Shoot(BUL_BLOOD, Md->Pl[i].X, Md->Pl[i].Y - (3 BitL), (fcos(r BitL)*pow/200), (fsin(r BitL)*pow/200));
        } // for (int i2 = 0; i2 < 12; i2 ++)


        if (Hit > 0)
        {
            // jos vielä ei oo kuollut
            if (Md->Pl[i].Damage[Hit-1] < Md->Pl[i].Killdamage[Hit-1])
                Md->Pl[i].Damage[Hit-1]++;
            // jos kuolee yleisestio...
            if (Md->Pl[i].Live)
                if ((Md->Pl[i].Damage[0]) + (Md->Pl[i].Damage[1]) + (Md->Pl[i].Damage[2]) >= Md->Pl[i].Totaldamage)
                {
                    Kill_player(i, ITEM_FALL, -1, 0);
                } //                 if (Md->Pl[i].Damage[0] + Md->Pl[i].Damage[1] + Md->Pl[i].Damage[2] >= Md->Pl[i].Totaldamage)
            // tai joku ruumiinosa pettää
            if (Md->Pl[i].Live)
                if (Md->Pl[i].Damage[Hit-1] >= Md->Pl[i].Killdamage[Hit-1]) if (Md->Pl[i].Live)
                    {
                        Kill_player(i, ITEM_FALL, -1, 0);
                    } // if (Md->Pl[i].Damage[Hit-1]>2)
        } // if (Hit > 0)
    } // Dodamage
    if (Dodamage) if (Md->Pl[i].Live)
            switch(Rand()%3)
            {
            case 0:
                Playsample(SAMP_FLESH1, Opt->sound.Soundvolume*2, 128);
                break; // Läts
            case 1:
                Playsample(SAMP_FLESH2, Opt->sound.Soundvolume*2, 128);
                break; // Löts
            case 2:
                Playsample(SAMP_FLESH3, Opt->sound.Soundvolume*2, 128);
                break;
            }; // Rand sound
} // void Fall_damage(int i)

void Update_inventory()
{   // Päivitetään inventory listaan jossa tyhjät skipataan
    for (int i = 0; i < Opt->Players; i++)
    {
        memset(&Md->Pl[i].Inv, -1, Maxstuff*4); // int = *4 tavua
        for (int cla = 0; cla < CLASS_MAX; cla++)
            for (int i2 = 0; i2 < Maxstuff; i2++) if (Itemclass[i2] == cla)
                    if (Canitemselect[i2])
                    {
                        if (Md->Pl[i].Stuff[i2] > 0)
                        {
                            for (int i3 = 0; i3 < Maxstuff; i3++)
                                if (Md->Pl[i].Inv[i3] == -1) {
                                    Md->Pl[i].Inv[i3] = i2;
                                    i3 = Maxstuff;
                                }
                        }
                    } // for (int i2 = 0; i2 < Maxstuff; i2++)
    } // for (int i = 0; i < Opt->Players; i++)
} // Update_inventory
void Update_laserrifle(int i, int i2)
{
    int X, Y, Get;
    int Hit = 0, Bounce = 0;
    if (Md->Pl[i2].Live)
        if ((Md->Pl[i2].Item == ITEM_LASERRIFLE) || (Md->Pl[i2].Item == ITEM_LASERPISTOL))
            if (Md->Pl[i2].Gunfire)
            {
                int Ax = Md->Pl[i2].X, Ay = Md->Pl[i2].Y+((Md->Pl[i2].Item == ITEM_LASERRIFLE)? itofix(2) : 0), Mx = fcos(Md->Pl[i2].Dir), My = fsin(Md->Pl[i2].Dir);
                bool Found = false;
                int Length = (Md->Pl[i2].Item == ITEM_LASERRIFLE) ? 1000 : 500;
                int Startlength = Length;
                do
                {
                    if (Length) Length--;
                    else Found = true;
                    Ax += Mx;
                    Ay += My;

                    X = (Ax>>16) - Md->Pl[i].Sx;
                    Y = (Ay>>16) - Md->Pl[i].Sy;
                    if (X+Clipx1>= Clipx1)
                        if (Y>= Clipy1)
                            if (X+Clipx1< Clipx2)
                                if (Y< Clipy2)
                                    Scr->line[Y][X+Clipx1] =  32+(Rand()%12);
                    if (Ax>>16 >= 0)
                        if (Ay>>16 >= 0)
                            if (Ax>>16 < Lev->Mapsizex)
                                if (Ay>>16 < Lev->Mapsizey)
                                    Get = Md->Map->line[Ay>>16][Ax>>16];
                    if ((Get > 121) && (Get < 143))

                    {
                        Bounce++;
                        int Stuck = 0;
                        if (Md->Pl[i2].Laserbounce == -1)
                        {
                            do
                            {
                                int r = itofix(Rand()%255);
                                Mx = fcos(r)*5;
                                My = fsin(r)*5;
                                Md->Pl[i2].Laserbounce = r;
                                Stuck++;
                            } while ((getpixel(Md->Map, (Ax+Mx)>>16, (Ay+My)>>16)!= 0) && (Stuck<100));
                        } //                if (Laserbounce == -1)
                        int Apurand = 0;
                        Stuck = 0;
                        if (Bounce > 1)
                            do
                            {
                                int r = itofix(Rand()%255);
                                Mx = fcos(r)*5;
                                My = fsin(r)*5;
                                Apurand = r;
                                Stuck++;
                            } while ((getpixel(Md->Map, (Ax+Mx)>>16, (Ay+My)>>16)!= 0) && (Stuck<100));

                        int r = (Bounce < 2) ? Md->Pl[i2].Laserbounce : Apurand;
                        Mx = fcos(r);
                        My = fsin(r);
                    } else if (Get != 0) Found = true;

// osuuko pelaajaan
                    for (int i3 = 0; i3 < Opt->Players; i3++) if (Md->Pl[i3].Live) if (((i3 == i2) && (Length < Startlength - 10)) || (i3 != i2))
                                if (Ax>>16 >= (Md->Pl[i3].X BitR) - 4)
                                    if (Ax>>16 <= (Md->Pl[i3].X BitR) + 4)
                                        if (Ay>>16 >= (Md->Pl[i3].Y BitR) - 6)
                                            if (Ay>>16 <= (Md->Pl[i3].Y BitR) + 6)

                                            {
                                                Hit = Hit_player(i3, Ax>>16, Ay>>16);
                                                if (Hit)
                                                {
                                                    switch(Md->Pl[i2].Item)
                                                    {
                                                    case ITEM_LASERRIFLE:
                                                        if (Rand()%20>0) Hit = 0;
                                                        break;
                                                    case ITEM_LASERPISTOL:
                                                        if (Rand()%30>0) Hit = 0;
                                                        break;
                                                    };
//              if (Timer % ((Md->Pl[i2].Item == ITEM_LASERRIFLE) ? 15 : 20)) Hit = 0;
                                                    Found = true;
                                                }
                                                int r; // apumuuttuja suunnan määrittelylle
                                                if (Hit > 0)
                                                    for (int Count = 0; Count < 12; Count++) // verta
                                                    {
                                                        r = Rand()%255;
                                                        Shoot(BUL_BLOOD, Md->Pl[i3].X, Md->Pl[i3].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000);
                                                    } // for (int Count = 0; Count < 12; Count++)

                                                if (Hit > 0)
                                                {
                                                    int Damage = Mindamage[Md->Bul[i].Dat[0]]+Rand()%(Randomdamage[Md->Bul[i].Dat[0]]+1);
                                                    if (Md->Pl[i3].Damage[Hit-1] < Md->Pl[i3].Killdamage[Hit-1])
                                                        Md->Pl[i3].Damage[Hit-1]+=Damage;
                                                    // jos tulee kuolo.. (Damaget suurempia kuin totaldamage)
                                                    if ((Md->Pl[i3].Damage[0]) + (Md->Pl[i3].Damage[1]) + (Md->Pl[i3].Damage[2]) >= Md->Pl[i3].Totaldamage)
                                                    {
                                                        Kill_player(i3, Md->Pl[i2].Item, i2, 0);
                                                        if (Md->Pl[i3].Damage[Hit-1] >= Md->Pl[i3].Killdamage[Hit-1])
                                                            Md->Pl[i3].Damage[Hit-1] = Md->Pl[i3].Killdamage[Hit-1];
                                                    } //                 if (Md->Pl[i3].Damage[0] + Md->Pl[i3].Damage[1] + Md->Pl[i3].Damage[2] >= Md->Pl[i3].Totaldamage)
                                                    // joku ruumiinosa pettää
                                                    if (Md->Pl[i3].Damage[Hit-1] >= Md->Pl[i3].Killdamage[Hit-1]) if (Md->Pl[i3].Live)
                                                        {
                                                            Kill_player(i3, Md->Pl[i2].Item, i2, 0);
                                                            Md->Pl[i3].Damage[Hit-1] = Md->Pl[i3].Killdamage[Hit-1];
                                                        } // if (Md->Pl[i3].Damage[Hit-1]>2)
                                                } // if (Hit > 0)
                                            } // for
                    for (int i3 = 0; i3 < Opt->Bots; i3++) if (Md->Bot[i3].Live) if (((i3 == i2) && (Length < Startlength - 10)) || (i3 != i2))
                                if (Ax>>16 >= (Md->Bot[i3].X BitR) - 4)
                                    if (Ax>>16 <= (Md->Bot[i3].X BitR) + 4)
                                        if (Ay>>16 >= (Md->Bot[i3].Y BitR) - 6)
                                            if (Ay>>16 <= (Md->Bot[i3].Y BitR) + 6)
                                            {
                                                Hit = Hit_bot(i3, Ax>>16, Ay>>16);
                                                if (Hit)
                                                {
                                                    switch(Md->Pl[i2].Item)
                                                    {
                                                    case ITEM_LASERRIFLE:
                                                        if (Rand()%20>0) Hit = 0;
                                                        break;
                                                    case ITEM_LASERPISTOL:
                                                        if (Rand()%30>0) Hit = 0;
                                                        break;
                                                    };
                                                    Found = true;
                                                }
                                                int r; // apumuuttuja suunnan määrittelylle
                                                if (Hit > 0)
                                                    for (int Count = 0; Count < 12; Count++) // verta
                                                    {
                                                        r = Rand()%255;
                                                        Shoot(BUL_BLOOD, Md->Bot[i3].X, Md->Bot[i3].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000, 1);
                                                    } // for (int Count = 0; Count < 12; Count++)

                                                if (Hit > 0)
                                                {
                                                    int Damage = Mindamage[Md->Bul[i].Dat[0]]+Rand()%(Randomdamage[Md->Bul[i].Dat[0]]+1);
                                                    if (Md->Bot[i3].Damage[Hit-1] < Md->Bot[i3].Killdamage[Hit-1])
                                                        Md->Bot[i3].Damage[Hit-1]+=Damage;
                                                    // jos tulee kuolo.. (Damaget suurempia kuin totaldamage)
                                                    if ((Md->Bot[i3].Damage[0]) + (Md->Bot[i3].Damage[1]) + (Md->Bot[i3].Damage[2]) >= Md->Bot[i3].Totaldamage)
                                                    {
                                                        Kill_bot(i3, Md->Pl[i2].Item, i2, 0);
                                                        if (Md->Bot[i3].Damage[Hit-1] >= Md->Bot[i3].Killdamage[Hit-1])
                                                            Md->Bot[i3].Damage[Hit-1] = Md->Bot[i3].Killdamage[Hit-1];
                                                    } //                 if (Md->Bot[i3].Damage[0] + Md->Bot[i3].Damage[1] + Md->Bot[i3].Damage[2] >= Md->Bot[i3].Totaldamage)
                                                    // joku ruumiinosa pettää
                                                    if (Md->Bot[i3].Damage[Hit-1] >= Md->Bot[i3].Killdamage[Hit-1]) if (Md->Bot[i3].Live)
                                                        {
                                                            Kill_bot(i3, Md->Pl[i2].Item, i2, 0);
                                                            Md->Bot[i3].Damage[Hit-1] = Md->Bot[i3].Killdamage[Hit-1];
                                                        } // if (Md->Bot[i3].Damage[Hit-1]>2)
                                                } // if (Hit > 0)
                                            } // for

                    if (Ax <= 0) Found = true;
                    if (Ay <= 0) Found = true;
                    if (Ax>>16 >= Lev->Mapsizex) Found = true;
                    if (Ay>>16 >= Lev->Mapsizey) Found = true;
                } while (!Found);
                if (i2 == i)
                    Addexp(6, Ax>>16, Ay>>16, 0, i, 0);
            } // if (Md->Pl[i].Live)       if (Md->Pl[i].Item == ITEM_LASERRIFLE)        if (Md->Pl[i].Gunfire)
} // void Update_laserrifle(int i)
void Update_bot_laserrifle(int i, int i2)
{
    int Hit = 0, Bounce = 0, X, Y, Get, Stuck;
    if (Md->Bot[i2].Live)
        if ((Md->Bot[i2].Item == ITEM_LASERRIFLE) || (Md->Bot[i2].Item == ITEM_LASERPISTOL))
            if (Md->Bot[i2].Gunfire)
            {
                int Ax = Md->Bot[i2].X, Ay = Md->Bot[i2].Y+((Md->Bot[i2].Item == ITEM_LASERRIFLE) ? itofix(2) : 0), Mx = fcos(Md->Bot[i2].Dir), My = fsin(Md->Bot[i2].Dir);
                bool Found = false;
                int Length = (Md->Bot[i2].Item == ITEM_LASERRIFLE) ? 1000 : 500;
                int Startlength = Length;
                do
                {
                    if (Length) Length--;
                    else Found = true;
                    Ax += Mx;
                    Ay += My;

                    X = (Ax>>16) - Md->Pl[i].Sx;
                    Y = (Ay>>16) - Md->Pl[i].Sy;
                    if (X+Clipx1>= Clipx1)
                        if (Y>= Clipy1)
                            if (X+Clipx1< Clipx2)
                                if (Y< Clipy2)
                                    Scr->line[Y][X+Clipx1] =  32+(Rand()%12);
                    if (Ax>>16 >= 0)
                        if (Ay>>16 >= 0)
                            if (Ax>>16 < Lev->Mapsizex)
                                if (Ay>>16 < Lev->Mapsizey)
                                    Get = Md->Map->line[Ay>>16][Ax>>16];
                    if (Get > 121)
                        if (Get < 143)
                        {
                            Bounce++;
                            if (Md->Bot[i2].Laserbounce == -1)
                            {
                                Stuck = 0;
                                do
                                {
                                    int r = itofix(Rand()%255);
                                    Mx = fcos(r)*5;
                                    My = fsin(r)*5;
                                    Md->Bot[i2].Laserbounce = r;
                                    Stuck++;
                                } while ((getpixel(Md->Map, (Ax+Mx)>>16, (Ay+My)>>16)!= 0) && (Stuck<100));
                            } //                if (Laserbounce == -1)
                            Stuck = 0;
                            int Apurand = 0;
                            if (Bounce > 1)
                                do
                                {
                                    int r = itofix(Rand()%255);
                                    Mx = fcos(r)*5;
                                    My = fsin(r)*5;
                                    Apurand = r;
                                    Stuck++;
                                } while ((getpixel(Md->Map, (Ax+Mx)>>16, (Ay+My)>>16)!= 0) && (Stuck < 100));

                            int r = (Bounce < 2) ? Md->Bot[i2].Laserbounce : Apurand;
                            Mx = fcos(r);
                            My = fsin(r);
                        } else if (Get != 0) Found = true;

// osuuko pelaajaan
                    for (int i3 = 0; i3 < Opt->Players; i3++) if (Md->Pl[i3].Live) if (((i3 == i2) && (Length < Startlength - 10)) || (i3 != i2))
                                if (Ax>>16 >= (Md->Pl[i3].X BitR) - 4)
                                    if (Ax>>16 <= (Md->Pl[i3].X BitR) + 4)
                                        if (Ay>>16 >= (Md->Pl[i3].Y BitR) - 6)
                                            if (Ay>>16 <= (Md->Pl[i3].Y BitR) + 6)
                                            {

                                                Hit = Hit_player(i3, Ax>>16, Ay>>16);
                                                if (Hit)
                                                {
                                                    switch(Md->Bot[i2].Item)
                                                    {
                                                    case ITEM_LASERRIFLE:
                                                        if (Rand()%20>0) Hit = 0;
                                                        break;
                                                    case ITEM_LASERPISTOL:
                                                        if (Rand()%30>0) Hit = 0;
                                                        break;
                                                    };
                                                    Found = true;
                                                }
                                                int r; // apumuuttuja suunnan määrittelylle
                                                if (Hit > 0)
                                                    for (int Count = 0; Count < 12; Count++) // verta
                                                    {
                                                        r = Rand()%255;
                                                        Shoot(BUL_BLOOD, Md->Pl[i3].X, Md->Pl[i3].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000);
                                                    } // for (int Count = 0; Count < 12; Count++)

                                                if (Hit > 0)
                                                {
                                                    int Damage = Mindamage[Md->Bul[i].Dat[0]]+Rand()%(Randomdamage[Md->Bul[i].Dat[0]]+1);
                                                    if (Md->Pl[i3].Damage[Hit-1] < Md->Pl[i3].Killdamage[Hit-1])
                                                        Md->Pl[i3].Damage[Hit-1]+=Damage;
                                                    // jos tulee kuolo.. (Damaget suurempia kuin totaldamage)
                                                    if ((Md->Pl[i3].Damage[0]) + (Md->Pl[i3].Damage[1]) + (Md->Pl[i3].Damage[2]) >= Md->Pl[i3].Totaldamage)
                                                    {
                                                        Kill_player(i3, Md->Bot[i2].Item, i2, 1);
                                                        if (Md->Pl[i3].Damage[Hit-1] >= Md->Pl[i3].Killdamage[Hit-1])
                                                            Md->Pl[i3].Damage[Hit-1] = Md->Pl[i3].Killdamage[Hit-1];
                                                    } //                 if (Md->Pl[i3].Damage[0] + Md->Pl[i3].Damage[1] + Md->Pl[i3].Damage[2] >= Md->Pl[i3].Totaldamage)
                                                    // joku ruumiinosa pettää
                                                    if (Md->Pl[i3].Damage[Hit-1] >= Md->Pl[i3].Killdamage[Hit-1]) if (Md->Pl[i3].Live)
                                                        {
                                                            Kill_player(i3, Md->Bot[i2].Item, i2, 1);
                                                            Md->Pl[i3].Damage[Hit-1] = Md->Pl[i3].Killdamage[Hit-1];
                                                        } // if (Md->Pl[i3].Damage[Hit-1]>2)
                                                } // if (Hit > 0)
                                            } // for
                    for (int i3 = 0; i3 < Opt->Bots; i3++) if (Md->Bot[i3].Live) if (((i3 == i2) && (Length < Startlength - 10)) || (i3 != i2))
                                if (Ax>>16 >= (Md->Bot[i3].X BitR) - 4)
                                    if (Ax>>16 <= (Md->Bot[i3].X BitR) + 4)
                                        if (Ay>>16 >= (Md->Bot[i3].Y BitR) - 6)
                                            if (Ay>>16 <= (Md->Bot[i3].Y BitR) + 6)
                                            {

                                                Hit = Hit_bot(i3, Ax>>16, Ay>>16);
                                                if (Hit)
                                                {
                                                    switch(Md->Bot[i2].Item)
                                                    {
                                                    case ITEM_LASERRIFLE:
                                                        if (Rand()%20>0) Hit = 0;
                                                        break;
                                                    case ITEM_LASERPISTOL:
                                                        if (Rand()%30>0) Hit = 0;
                                                        break;
                                                    };
                                                    Found = true;
                                                }
                                                int r; // apumuuttuja suunnan määrittelylle
                                                if (Hit > 0)
                                                    for (int Count = 0; Count < 12; Count++) // verta
                                                    {
                                                        r = Rand()%255;
                                                        Shoot(BUL_BLOOD, Md->Bot[i3].X, Md->Bot[i3].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000, 1);
                                                    } // for (int Count = 0; Count < 12; Count++)

                                                if (Hit > 0)
                                                {
                                                    int Damage = Mindamage[Md->Bul[i].Dat[0]]+Rand()%(Randomdamage[Md->Bul[i].Dat[0]]+1);
                                                    if (Md->Bot[i3].Damage[Hit-1] < Md->Bot[i3].Killdamage[Hit-1])
                                                        Md->Bot[i3].Damage[Hit-1]+=Damage;
                                                    // jos tulee kuolo.. (Damaget suurempia kuin totaldamage)
                                                    if ((Md->Bot[i3].Damage[0]) + (Md->Bot[i3].Damage[1]) + (Md->Bot[i3].Damage[2]) >= Md->Bot[i3].Totaldamage)
                                                    {
                                                        Kill_bot(i3, Md->Bot[i2].Item, i2, 1);
                                                        if (Md->Bot[i3].Damage[Hit-1] >= Md->Bot[i3].Killdamage[Hit-1])
                                                            Md->Bot[i3].Damage[Hit-1] = Md->Bot[i3].Killdamage[Hit-1];
                                                    } //                 if (Md->Bot[i3].Damage[0] + Md->Bot[i3].Damage[1] + Md->Bot[i3].Damage[2] >= Md->Bot[i3].Totaldamage)
                                                    // joku ruumiinosa pettää
                                                    if (Md->Bot[i3].Damage[Hit-1] >= Md->Bot[i3].Killdamage[Hit-1]) if (Md->Bot[i3].Live)
                                                        {
                                                            Kill_bot(i3, Md->Bot[i2].Item, i2, 1);
                                                            Md->Bot[i3].Damage[Hit-1] = Md->Bot[i3].Killdamage[Hit-1];
                                                        } // if (Md->Bot[i3].Damage[Hit-1]>2)
                                                } // if (Hit > 0)
                                            } // for

                    if (Ax <= 0) Found = true;
                    if (Ay <= 0) Found = true;
                    if (Ax>>16 >= Lev->Mapsizex) Found = true;
                    if (Ay>>16 >= Lev->Mapsizey) Found = true;
                } while (!Found);
                Addexp(6, Ax>>16, Ay>>16, 0, i, 0);
            } // if (Md->Pl[i].Live)       if (Md->Pl[i].Item == ITEM_LASERRIFLE)        if (Md->Pl[i].Gunfire)
} // void Update_bot_laserrifle(int i)
void Test_camouflage(int i)
{

    if (Md->Pl[i].FeetOnGround)
    {

        int Colors = 0, x, y;
        int Stuck = 0;
        bool Stop = false;
        if (abs(Md->Pl[i].Mx+Md->Pl[i].My)>2000)
            Md->Pl[i].Nocamo = 50;
        if ((Md->Pl[i].Camouflaged == false) )
            do
            {
                Stuck++;
                x = (Md->Pl[i].X>>16)-8+Rand()%16;
                y = (Md->Pl[i].Y>>16)-8+Rand()%16;
                if (getpixel(Md->Map, x, y)> 0) Md->Pl[i].Camocolor[Colors++] = getpixel(Md->Map, x, y);
                if (Colors >= 2) Stop = true;
                if (Stuck > 100) Stop = true;
            } while (!Stop);
        if (Md->Pl[i].Nocamo < 0) Md->Pl[i].Nocamo = 1;
        if (Md->Pl[i].Nocamo==0)
            Md->Pl[i].Camouflaged = true;
        else {
            Md->Pl[i].Nocamo--;
            Md->Pl[i].Camouflaged = false;
        }
    } // if (Md->Pl[i].FeetOnGround)
    else Md->Pl[i].Camouflaged = false;
} // void Test_camouflage(int i)
void Hurteverybody(int X,int Y, int Ownertype, int Owner)
{
    X = X >> 16;
    Y = Y >> 16;
    int Hit = 0; // mihin osutaa
    for (int i2 = 0; i2 < Opt->Players; i2++) if (Md->Pl[i2].Live)
            if (((Ownertype == 0) && (Owner != i2)) || (Ownertype != 0))
            {
                Hit = Hit_player(i2, X, Y);
                int r; // apumuuttuja suunnan määrittelylle
                if (Hit > 0)
                    for (int Count = 0; Count < 24; Count++) // verta
                    {
                        r = Rand()%255;
                        Shoot(BUL_BLOOD, Md->Pl[i2].X, Md->Pl[i2].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000);
                    } // for (int Count = 0; Count < 12; Count++)

                if (Hit > 0)
                {
                    // Damagea
                    int Damage = Mindamage[ITEM_LASERSABRE]+Rand()%(Randomdamage[ITEM_LASERSABRE]+1);
                    if (Md->Pl[i2].Damage[Hit-1] < Md->Pl[i2].Killdamage[Hit-1])
                        Md->Pl[i2].Damage[Hit-1]+=Damage;
                    // jos tulee kuolo.. (Damaget suurempia kuin totaldamage)
                    if ((Md->Pl[i2].Damage[0]) + (Md->Pl[i2].Damage[1]) + (Md->Pl[i2].Damage[2]) >= Md->Pl[i2].Totaldamage)
                    {
                        Kill_player(i2, ITEM_LASERSABRE, Owner, Ownertype);
                        if (Md->Pl[i2].Damage[Hit-1] >= Md->Pl[i2].Killdamage[Hit-1])
                            Md->Pl[i2].Damage[Hit-1] = Md->Pl[i2].Killdamage[Hit-1];
                    } //                 if (Md->Pl[i2].Damage[0] + Md->Pl[i2].Damage[1] + Md->Pl[i2].Damage[2] >= Md->Pl[i2].Totaldamage)
                    // joku ruumiinosa pettää
                    if (Md->Pl[i2].Live)
                        if (Md->Pl[i2].Damage[Hit-1] >= Md->Pl[i2].Killdamage[Hit-1]) if (Md->Pl[i2].Live)
                            {
                                Kill_player(i2, ITEM_LASERSABRE, Owner, Ownertype);
                                Md->Pl[i2].Damage[Hit-1] = Md->Pl[i2].Killdamage[Hit-1];
                            } // if (Md->Pl[i2].Damage[Hit-1]>2)
                } // if (Hit > 0)

                if (Md->Pl[i2].Live) // Elossa vielä?? Mitä?
                    switch(Hit)
                    {   // Lits
                    case 1:
                        Playsample(SAMP_FLESH1, Opt->sound.Soundvolume*2, 128);
                        Md->Pl[i2].Mx += 50000 >> 3; // iso tönäsy
                        Md->Pl[i2].My += 50000 >> 3;
                        break; // Läts
                    case 2:
                        Playsample(SAMP_FLESH2, Opt->sound.Soundvolume*2, 128);
                        Md->Pl[i2].Mx += 50000 >> 4; // tönäsy
                        Md->Pl[i2].My += 50000 >> 4;
                        break; // Löts
                    case 3:
                        Playsample(SAMP_FLESH3, Opt->sound.Soundvolume*2, 128);
                        Md->Pl[i2].Mx += 50000 >> 5; // pikku tönäsy
                        Md->Pl[i2].My += 50000 >> 5;
                        break;
                    };

            } //      for (int i2 = 0; i2 < Opt->Players; i2++)
    for (int i2 = 0; i2 < Opt->Bots; i2++) if (Md->Bot[i2].Live)
        {
            Hit = Hit_bot(i2, X, Y);
            int r; // apumuuttuja suunnan määrittelylle
            if (Hit > 0)
                for (int Count = 0; Count < 12; Count++) // verta
                {
                    r = Rand()%255;
                    Shoot(BUL_BLOOD, Md->Bot[i2].X, Md->Bot[i2].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000, 1);
                } // for (int Count = 0; Count < 12; Count++)

            if (Hit > 0)
            {
                // Damagea
                int Damage = Mindamage[ITEM_LASERSABRE]+Rand()%(Randomdamage[ITEM_LASERSABRE]+1);
                if (Md->Bot[i2].Damage[Hit-1] < Md->Bot[i2].Killdamage[Hit-1])
                    Md->Bot[i2].Damage[Hit-1]+=Damage;
                // jos tulee kuolo.. (Damaget suurempia kuin totaldamage)
                if ((Md->Bot[i2].Damage[0]) + (Md->Bot[i2].Damage[1]) + (Md->Bot[i2].Damage[2]) >= Md->Bot[i2].Totaldamage)
                {
                    Kill_bot(i2, ITEM_LASERSABRE, Owner, Ownertype);
                    if (Md->Bot[i2].Damage[Hit-1] >= Md->Bot[i2].Killdamage[Hit-1])
                        Md->Bot[i2].Damage[Hit-1] = Md->Bot[i2].Killdamage[Hit-1];
                } //                 if (Md->Bot[i2].Damage[0] + Md->Bot[i2].Damage[1] + Md->Bot[i2].Damage[2] >= Md->Bot[i2].Totaldamage)
                // joku ruumiinosa pettää
                if (Md->Bot[i2].Damage[Hit-1] >= Md->Bot[i2].Killdamage[Hit-1]) if (Md->Bot[i2].Live)
                    {
                        Kill_bot(i2, ITEM_LASERSABRE, Owner, Ownertype);
                        Md->Bot[i2].Damage[Hit-1] = Md->Bot[i2].Killdamage[Hit-1];
                    } // if (Md->Bot[i2].Damage[Hit-1]>2)
            } // if (Hit > 0)

            if (Md->Bot[i2].Live) // Elossa vielä?? Mitä?
                switch(Hit)
                {   // Lits
                case 1:
                    Playsample(SAMP_FLESH1, Opt->sound.Soundvolume*2, 128);
                    Md->Bot[i2].Mx += 50000 >> 3; // iso tönäsy
                    Md->Bot[i2].My += 50000 >> 3;
                    break; // Läts
                case 2:
                    Playsample(SAMP_FLESH2, Opt->sound.Soundvolume*2, 128);
                    Md->Bot[i2].Mx += 50000 >> 4; // tönäsy
                    Md->Bot[i2].My += 50000 >> 4;
                    break; // Löts
                case 3:
                    Playsample(SAMP_FLESH3, Opt->sound.Soundvolume*2, 128);
                    Md->Bot[i2].Mx += 50000 >> 5; // pikku tönäsy
                    Md->Bot[i2].My += 50000 >> 5;
                    break;
                };
        } //      for (int i2 = 0; i2 < Opt->Players; i2++)


} // void Hurteverybody(int X,int Y)
void Laser_sabre_kimpoaminen(int i)
{
    int X, Y;
    for (int i2 = 0; i2 < 10; i2++)
    {
        X = (Md->Pl[i].X+fcos(Md->Pl[i].Dir)*(i2*2)) BitR;
        Y = ((Md->Pl[i].Y+fsin(Md->Pl[i].Dir)*(i2*2)) BitR) +2;
        for (int i3 = 0; i3 < Maxbullets; i3++)
            if (Md->Bul[i3].Live) if (Md->Bul[i3].Type == BUL_PISTOL)
                {
                    if (Delta(Md->Bul[i3].X BitR, X) < 4)
                        if (Delta(Md->Bul[i3].Y BitR, Y) < 4)
                        {
                            Md->Bul[i3].X = Md->Bul[i3].Ox;
                            Md->Bul[i3].Y = Md->Bul[i3].Oy;
                            Md->Bul[i3].Mx = -Md->Bul[i3].Mx - 5000 + rand()%10001;
                            Md->Bul[i3].My = -Md->Bul[i3].My - 5000 + rand()%10001;
                            Playsample(SAMP_BOUNCE1, int(Opt->sound.Soundvolume*(50+Rand()%50)/100), 128, 5050+Rand()%20000);
                        } //        if (Delta(Md->Bul[i3].X BitR, X) < 3)        if (Delta(Md->Bul[i3].Y BitR, Y) < 3)
                } //     for (int i3 = 0; i3 < Maxbullets; i3++)     if (Md->Bul[i3].Live)
    } // for (int i2 = 0; i2 < 10; i2++)


} // void Laser_sabre_kimpoaminen()
void Laser_cannon_action(int i)
{
    Md->Pl[i].Actionvar[0]++;
    if (Md->Pl[i].Actionvar[0] > 3)
    {
        Md->Pl[i].Actionvar[0] = 0;
        Md->Pl[i].Actionvar[1]--;
        if (Md->Pl[i].Actionvar[1] == 0)
        {
            Md->Pl[i].Action = 0;
            Playsample(SAMP_PLASMA, Opt->sound.Soundvolume, 128, 0);
            Md->Pl[i].Mx += fcos(Suunta(Md->Pl[i].Dir-itofix(128)));
            Md->Pl[i].My += fsin(Suunta(Md->Pl[i].Dir-itofix(128)));
            Shoot(BUL_BIGLASER, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)-10000+rand()%20000, fsin(Md->Pl[i].Dir)-10000+rand()%20000,ITEM_LASERCANNON,i,0);
        } // if (Md->Pl[i].Actionvar[1] == 0)
    } // if (Md->Pl[i].Actionvar[0] > 10)
} // void Laser_cannon_action(int i)
void Update_players()
{
    int X, Y,xx,yy;

    Calc_player_damages(); // Lasketaan pelaajien damaget
    if (Timer%50==0) Update_inventory(); // välillä inventoryn päivitys
    // nopeutus eli frameskip

    for (int i = 0; i < Opt->Players; i++)
    {
        if (Md->Pl[i].Selectx < Md->Pl[i].Selectrealx) Md->Pl[i].Selectx++;
        if (Md->Pl[i].Selectx > Md->Pl[i].Selectrealx) Md->Pl[i].Selectx--;
        if (Md->Pl[i].Selecty < Md->Pl[i].Selectrealy) Md->Pl[i].Selecty++;
        if (Md->Pl[i].Selecty > Md->Pl[i].Selectrealy) Md->Pl[i].Selecty--;
        Md->Pl[i].Gun = Weapongunpic[Md->Pl[i].Item];
        if (Md->Pl[i].Item == ITEM_LASERSABRE) if (Md->Pl[i].Live)
                Laser_sabre_kimpoaminen(i);
        if (Md->Pl[i].Action == ACTION_LASERCANNON)
            Laser_cannon_action(i);
        if (Md->Pl[i].Action == ACTION_SABRE) if (Md->Pl[i].Live)
            {
                Hurteverybody(Md->Pl[i].X+fcos(Md->Pl[i].Dir)*7, Md->Pl[i].Y+fsin(Md->Pl[i].Dir)*7, 0, i);
                Hurteverybody(Md->Pl[i].X+fcos(Md->Pl[i].Dir)*2, Md->Pl[i].Y+fsin(Md->Pl[i].Dir)*2, 0, i);
                Hurteverybody(Md->Pl[i].X+fcos(Md->Pl[i].Dir)*10, Md->Pl[i].Y+fsin(Md->Pl[i].Dir)*10, 0, i);
                Md->Pl[i].Actionvar[0]+=5;
                if (Md->Pl[i].Actionvar[0] < 128)
                {
                    switch(Md->Pl[i].S)
                    {
                    case 0:
                        Md->Pl[i].Dir = Suunta((-32-Md->Pl[i].Actionvar[0])<<16);
                        break;
                    case 1:
                        Md->Pl[i].Dir = Suunta((-96+Md->Pl[i].Actionvar[0])<<16);
                        break;
                    }; // switch(Md->Pl[i].S)
                } // if (Md->Pl[i].Actionvar[0] < 128)
                else
                {
                    switch(Md->Pl[i].S)
                    {
                    case 0:
                        Md->Pl[i].Dir = Suunta((96+(Md->Pl[i].Actionvar[0]-128))<<16);
                        break;
                    case 1:
                        Md->Pl[i].Dir = Suunta((32-(Md->Pl[i].Actionvar[0]-128))<<16);
                        break;
                    }; // switch(Md->Pl[i].S)
                }
                if (Md->Pl[i].Actionvar[0] >= 160)
                {
                    Md->Pl[i].Action = 0;
                } // if (Md->Pl[i].Actionvar[0] >= 128)
            } // if (Md->Pl[i].Action == ACTION_SABRE)
        // tärinä jos liikutaan sniper kädessä
        if (Md->Pl[i].Action == ACTION_SNIPER)
        {
            int rx = (abs(Md->Pl[i].Mx*10)>>16);
            int ry = (abs(Md->Pl[i].My*10)>>16);
            if (rx == 0) rx = 1;
            if (ry == 0) ry = 1;

            int Nx = -(abs(Md->Pl[i].Mx*10)>>17)+Rand()%rx;
            int Ny = -(abs(Md->Pl[i].My*10)>>17)+Rand()%ry;
            if (Strictshockwave(Md->Pl[i].X BitR, Md->Pl[i].Y BitR, Md->Pl[i].Actionx+Nx, Md->Pl[i].Actiony+Ny))
            {
                Md->Pl[i].Actionx += Nx;
                Md->Pl[i].Actiony += Ny;
            } // if (Strictshockwave(Md->Pl[i].X BitR, Md->Pl[i].Y BitR, Md->Pl[i].Actionx+Nx, Md->Pl[i].Actiony+Ny))
        } // if (Md->Pl[i].Action == ACTION_SNIPER)
        if (Md->Pl[i].Live) if (Md->Pl[i].Stuff[ITEM_CAMOUFLAGE])
                Test_camouflage(i);
        if (!Md->Pl[i].Live) // Jos ei elossa
        {
            Md->Pl[i].Action = 0;
            Md->Pl[i].Killtimer++;
            if (Md->Pl[i].Killtimer >= 375)
            {
                Md->Pl[i].Anim = ANI_WALK;
                Md->Pl[i].Picture = 0;
                Lev->Startpoint[i][0] = (Md->Bld[i].X BitR)+(((BITMAP*) Dat[DATBLD0001].dat)->w>>1);
                Lev->Startpoint[i][1] = (Md->Bld[i].Y BitR)+(((BITMAP*) Dat[DATBLD0001].dat)->h>>1);
                if (Md->Pl[i].Sx < Lev->Startpoint[i][0] - (Clipx>>1)) Md->Pl[i].Sx+=5;
                if (Md->Pl[i].Sy < Lev->Startpoint[i][1] - (Clipy>>1)) Md->Pl[i].Sy+=5;
                if (Md->Pl[i].Sx > Lev->Startpoint[i][0] - (Clipx>>1)) Md->Pl[i].Sx-=5;
                if (Md->Pl[i].Sy > Lev->Startpoint[i][1] - (Clipy>>1)) Md->Pl[i].Sy-=5;
                if (Md->Pl[i].Killtimer >= 600)
                {

                    Md->Pl[i].Ninjarope = false;
                    Md->Pl[i].Armor[0] = 0;
                    Md->Pl[i].Armor[1] = 0; // Panssari päälle
                    Md->Pl[i].Armor[2] = 0;
                    Md->Pl[i].Stuff[ITEM_CAMOUFLAGE] = 0;
                    for (int i2 = 0; i2 < 3; i2++) // Ei damagea
                        Md->Pl[i].Damage[i2] = 0;
                    Md->Pl[i].Live = true; // ELOSSA?
                    Md->Pl[i].X  = Lev->Startpoint[i][0] BitL; // Alotuspaikka
                    Md->Pl[i].Y  = Lev->Startpoint[i][1] BitL;
                    Md->Pl[i].Mx = 0;
                    Md->Pl[i].My = 0;
                    Md->Pl[i].Gunfire = 0;
                    Md->Pl[i].Menu = -1; // Ei menuja päälle
                    Md->Pl[i].Killtimer = 0;
                } //           if (Md->Pl[i].Killtimer >= 500)
            } //         if (Md->Pl[i].Killtimer >= 300)
        } // if (Md->Pl[i].Live)
        if (Md->Pl[i].Live) // Jos elossa ja ninjaropessa
            if (Md->Pl[i].Ninjarope) Update_ninjarope(i);

        // Vanha jalkojen tila
        Md->Pl[i].Oldfeet = Md->Pl[i].FeetOnGround;
        // Jalat maassa
        Md->Pl[i].FeetOnGround = Feet_on_ground(i);
        // Etäisyys basesta.... Tarvitaan ostamiseen
        Md->Pl[i].Distancefrombase = Distance(Md->Bld[i].X BitR, Md->Bld[i].Y BitR, Md->Pl[i].X BitR, Md->Pl[i].Y BitR);
        // Jos tarpeeksi lähellä niin saa ostaa
        if (Md->Pl[i].Distancefrombase < 60) Md->Pl[i].Canbuy = true;
        else Md->Pl[i].Canbuy = false;
        // Jos on laskuvarjo niin hidastetaan
        if (Md->Pl[i].Parachute)
            if (Md->Pl[i].My > 50000)
            {
                Md->Pl[i].My -= Gravity<<1;
            } //       if (Md->Pl[i].Parachute)       if (Md->Pl[i].My > 50000)

        // Jos ei olla maassa niin tiputaan
        if (!Md->Pl[i].FeetOnGround) Md->Pl[i].My+=Gravity;
        else
        {
            Md->Pl[i].Parachuteshotdown = false;
            Md->Pl[i].Parachute = false;
            // muuten jos ei hypitä niin nopeusvektori y = 0
            if (Md->Pl[i].Jump == false)
                Md->Pl[i].My = 0;
            // jos ei kävellä niin jarrutetaan
            if (Md->Pl[i].Walking==false)
            {
                // heplo homma 500 pykälin kohti nollaa
                if (Md->Pl[i].Mx > 0) {
                    if (Md->Pl[i].Mx-1000 > 0) Md->Pl[i].Mx -= 1000;
                    else Md->Pl[i].Mx = 0;
                }
                if (Md->Pl[i].Mx < 0) {
                    if (Md->Pl[i].Mx+1000 < 0) Md->Pl[i].Mx += 1000;
                    else Md->Pl[i].Mx = 0;
                }
            }  //       if (Md->Pl[i].Walking==false)
        } // Jos jalat ovat maassa

        // Jos jalkojen tila on muuttunut niin ylöspäin. Suoraan yytä ei momenttia
        if (Md->Pl[i].Oldfeet != Md->Pl[i].FeetOnGround) Md->Pl[i].Y -= Gravity;

        // Vanhat pelaajan koordit
        Md->Pl[i].Ox = Md->Pl[i].X;
        Md->Pl[i].Oy = Md->Pl[i].Y;

        // Kalkulointi uusille koordeille
        if ((!Md->Pl[i].Ninjarope) || (Opt->Realrope == false))
        {
            Md->Pl[i].X = Md->Pl[i].X + Md->Pl[i].Mx; // Plus nopeusvektorit
            Md->Pl[i].Y = Md->Pl[i].Y + Md->Pl[i].My;
        }
        if (Opt->Realistic_falling_damage) if (Md->Pl[i].Live)
                Fall_damage(i);

        // Jos ollaan ruudusta veks
        Player_bounce_check(i);

        // desimaaliosa pois
        xx = Md->Pl[i].X BitR;
        yy = Md->Pl[i].Y BitR;

        // pelaajanruudun koordi
        if (Md->Pl[i].Live) if (Md->Pl[i].Action != ACTION_SNIPER)
            {
                Md->Pl[i].Sx = xx - (Clipx>>1);
                Md->Pl[i].Sy = yy - (Clipy>>1);
            } // if (Md->Pl[i].Live)

        // jos jalat maassa
        if (getpixel(Md->Map, xx,yy+7))
        {
            // Etäisyys maasta
            int d = Distance_to_surface(i);
            // että voidaan kävellä ylämäkeen
            if (d < 6) {
                Md->Pl[i].Y -= (d-1) BitL;
            }
            else
            {

                Md->Pl[i].Mx = 0; // töks
                Md->Pl[i].My = 0;
                Md->Pl[i].X = Md->Pl[i].Ox; // vanhat koordit
                Md->Pl[i].Y = Md->Pl[i].Oy;
            }

        } //       if (getpixel(Md->Map, xx, yy)) if (Md->Pl[i].Walking) if (DistanceToSurface(i) < 4)

        if (Md->Pl[i].Live) // elossa ja kävelemässä
            if (Md->Pl[i].Walking) Player_walk(i);

        if (Md->Pl[i].Live) // elossa ja laavassa
            if (Getlava(xx, yy))
            {
                for (int apu = 0; apu < Maxlava; apu++) // sitten katotaan
                    if (Md->Lava[apu].Live)                // mikä laava se
                        if (Md->Lava[apu].X BitR >= xx-1)     // oikein kutittaa...
                            if (Md->Lava[apu].Y BitR >= yy-1)
                                if (Md->Lava[apu].X BitR <= xx+1)
                                    if (Md->Lava[apu].Y BitR <= yy+1)
                                        Md->Lava[apu].Live = false;
                Dellava(xx,yy); // pois se laava
                Randomlavahit(i); // ja sihahduksen saattelema osuma
            } //   if (Getlava(xx, yy))
    } // for (int Count = 0; Count < Opt->Players; Count++)
} // Update_players()
void Update_vehicles()
{
    int X, Y,xx,yy;

    // nopeutus eli frameskip
    for (int i = 0; i < Opt->Bots; i++)
    {
        // Vanha jalkojen tila
        Md->Veh[i].Oldfeet = Md->Veh[i].FeetOnGround;
        // Jalat maassa
        Md->Veh[i].FeetOnGround = Vehicle_feet_on_ground(i);
        // Etäisyys basesta.... Tarvitaan ostamiseen
        // Jos ei olla maassa niin tiputaan
        if (!Md->Veh[i].FeetOnGround) Md->Veh[i].My+=Gravity;
        else
        {
            // muuten jos ei hypitä niin nopeusvektori y = 0
            if (Md->Veh[i].Jump == false)
                Md->Veh[i].My = 0;
            // jos ei kävellä niin jarrutetaan
            if (Md->Veh[i].Walking==false)
            {
                // heplo homma 500 pykälin kohti nollaa
                if (Md->Veh[i].Mx > 0) {
                    if (Md->Veh[i].Mx-500 > 0) Md->Veh[i].Mx -= 500;
                    else Md->Veh[i].Mx = 0;
                }
                if (Md->Veh[i].Mx < 0) {
                    if (Md->Veh[i].Mx+500 < 0) Md->Veh[i].Mx += 500;
                    else Md->Veh[i].Mx = 0;
                }
            }  //       if (Md->Veh[i].Walking==false)
        } // Jos jalat ovat maassa

        // Jos jalkojen tila on muuttunut niin ylöspäin. Suoraan yytä ei momenttia
        if (Md->Veh[i].Oldfeet != Md->Veh[i].FeetOnGround) Md->Veh[i].Y -= Gravity;

        // Vanhat botin koordit
        Md->Veh[i].Ox = Md->Veh[i].X;
        Md->Veh[i].Oy = Md->Veh[i].Y;

        // Kalkulointi uusille koordeille
        Md->Veh[i].X = Md->Veh[i].X + Md->Veh[i].Mx; // Plus nopeusvektorit
        Md->Veh[i].Y = Md->Veh[i].Y + Md->Veh[i].My;
        // Jos ollaan ruudusta veks
        Vehicle_bounce_check(i);

        // desimaaliosa pois
        xx = Md->Veh[i].X BitR;
        yy = Md->Veh[i].Y BitR;

        // jos jalat maassa
        if (getpixel(Md->Map, xx,yy+4))
        {
            // Etäisyys maasta
            int d = Vehicle_distance_to_surface(i);
            // että voidaan kävellä ylämäkeen
            if (d < 6) {
                Md->Veh[i].Y -= (d-1) BitL;
            }
            else
            {
                Md->Veh[i].Mx = 0; // töks
                Md->Veh[i].My = 0;
                Md->Veh[i].X = Md->Veh[i].Ox; // vanhat koordit
                Md->Veh[i].Y = Md->Veh[i].Oy;
            }

        } //       if (getpixel(Md->Map, xx, yy)) if (Md->Veh[i].Walking) if (DistanceToSurface(i) < 4)
    } // for (int Count = 0; Count < Opt->Players; Count++)
} // void Update_vehicles()
void Update_bots()
{
    int X, Y,xx,yy;

    Calc_bot_damages(); // Lasketaan pelaajien damaget
    // nopeutus eli frameskip
    Botsalive = 0;
    for (int i = 0; i < Opt->Bots; i++)
    {
        if (Md->Bot[i].Live) {
            Botsalive++;
        }
        Update_bot_ai(i);
        if (Md->Bot[i].Live) // Jos elossa ja ninjaropessa
            if (Md->Bot[i].Ninjarope) Update_bot_ninjarope(i);

        // Vanha jalkojen tila
        Md->Bot[i].Oldfeet = Md->Bot[i].FeetOnGround;
        // Jalat maassa
        Md->Bot[i].FeetOnGround = Bot_feet_on_ground(i);
        // Etäisyys basesta.... Tarvitaan ostamiseen
        // Jos ei olla maassa niin tiputaan
        if (!Md->Bot[i].FeetOnGround) Md->Bot[i].My+=Gravity;
        else
        {
            // muuten jos ei hypitä niin nopeusvektori y = 0
            if (Md->Bot[i].Jump == false)
                Md->Bot[i].My = 0;
            // jos ei kävellä niin jarrutetaan
            if (Md->Bot[i].Walking==false)
            {
                // heplo homma 500 pykälin kohti nollaa
                if (Md->Bot[i].Mx > 0) {
                    if (Md->Bot[i].Mx-500 > 0) Md->Bot[i].Mx -= 500;
                    else Md->Bot[i].Mx = 0;
                }
                if (Md->Bot[i].Mx < 0) {
                    if (Md->Bot[i].Mx+500 < 0) Md->Bot[i].Mx += 500;
                    else Md->Bot[i].Mx = 0;
                }
            }  //       if (Md->Bot[i].Walking==false)
        } // Jos jalat ovat maassa

        // Jos jalkojen tila on muuttunut niin ylöspäin. Suoraan yytä ei momenttia
        if (Md->Bot[i].Oldfeet != Md->Bot[i].FeetOnGround) Md->Bot[i].Y -= Gravity;

        // Vanhat botin koordit
        Md->Bot[i].Ox = Md->Bot[i].X;
        Md->Bot[i].Oy = Md->Bot[i].Y;

        // Kalkulointi uusille koordeille
        Md->Bot[i].X = Md->Bot[i].X + Md->Bot[i].Mx; // Plus nopeusvektorit
        Md->Bot[i].Y = Md->Bot[i].Y + Md->Bot[i].My;
        // Jos ollaan ruudusta veks
        Bot_bounce_check(i);

        // desimaaliosa pois
        xx = Md->Bot[i].X BitR;
        yy = Md->Bot[i].Y BitR;

        // jos jalat maassa
        if (getpixel(Md->Map, xx,yy+4))
        {
            // Etäisyys maasta
            int d = Bot_distance_to_surface(i);
            // että voidaan kävellä ylämäkeen
            if (d < 6) {
                Md->Bot[i].Y -= (d-1) BitL;
            }
            else
            {
                Md->Bot[i].Mx = 0; // töks
                Md->Bot[i].My = 0;
                Md->Bot[i].X = Md->Bot[i].Ox; // vanhat koordit
                Md->Bot[i].Y = Md->Bot[i].Oy;
            }

        } //       if (getpixel(Md->Map, xx, yy)) if (Md->Bot[i].Walking) if (DistanceToSurface(i) < 4)

        if (Md->Bot[i].Live) // elossa ja kävelemässä
            if (Md->Bot[i].Walking) Bot_walk(i);
    } // for (int Count = 0; Count < Opt->Players; Count++)

} // Update_bots()
void Destroy_building(int i)
{
    Md->Bld[i].Live = false;
    for (int b = 0; b < 10; b++)
    {
        Addexp(Bldexp[Md->Bld[i].Type], (Md->Bld[i].X BitR)-30+rand()%60, (Md->Bld[i].Y BitR)-30+rand()%60, 2, 0, 5);
    } // for (int b = 0; b < 10; b++)
} // void Destroy_building(int i)
void Kill_player(int i, int weapon, int Killer, char killertype)
{
    if (Md->Pl[i].Stuff[ITEM_SELFDESTRUCTOR])
        Use_selfdestructor(i);
    int r;
    Playsample(SAMP_FLESH1, Opt->sound.Soundvolume*2, 64);
    Playsample(SAMP_FLESH2, Opt->sound.Soundvolume*2, 128);
    Playsample(SAMP_FLESH3, Opt->sound.Soundvolume*2, 192);
    if (Md->Pl[i].Anim != ANI_PLASMADEATH)
    {
        if (Md->Pl[i].Live) Md->Pl[i].Died++;
        // tarvitaan siihen ettei lennä kahta ruumista
        if (killertype == 0) if (Killer>=0) // Jos tappaja onkin pelaaja niin kill counteria plussataan
                if (Md->Pl[i].Live)
                {
                    Md->Pl[Killer].Kills[i]++;
                } // if (Md->Pl[i].Live)
    }
    bool Bodyfly = false; // eli lentääkö ruumis

    if (weapon != ITEM_PLASMAPISTOL)
        Md->Pl[i].Live = false;
    else// ja pelaaja kuolee pois
    {
        Md->Pl[i].Anim = ANI_PLASMADEATH;
        for (int i2 = 0; i2 < 50; i2 ++) // verta
        {   r = Rand()%255;
            Shoot(BUL_BLOOD, Md->Pl[i].X, Md->Pl[i].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000);
        }
        // for (int i2 = 0; i2 < 12; i2 ++)
        // ruumis pään kanssa hieman pyörien
        for (int i2 = 0; i2 < 10; i2 ++)
        {   r = Suunta(128+Rand()%128);          // ruumiinosia enemmän pyörien
            Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx+fcos(itofix(r))>>2,Md->Pl[i].My+fsin(itofix(r))>>2, DATGORE01+Rand()%8);
        } // for (int i = 0; i < 4; i ++)
    }
    if (weapon==ITEM_FALL)
    {
        Bodyfly = true;
        Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, -50000+Rand()%100000, -50000+Rand()%100000,  DATGORELEGS1);
        Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, -50000+Rand()%100000, -50000+Rand()%100000,  DATGORELEGS2);

        for (int i2 = 0; i2 < 2; i2++)
        {
            r = rand()%255;
            switch(i) // (väri pelaajan mukaan)
            {
            case 0:
                Shoot(BUL_GORE, Md->Pl[i].X+((-3+rand()%7) BitL), Md->Pl[i].Y+((-3+rand()%7) BitL), fcos(r)>>2, fsin(r)>>2, DATGOREHAND11+i2);
                break;
            case 1:
                Shoot(BUL_GORE, Md->Pl[i].X+((-3+rand()%7) BitL), Md->Pl[i].Y+((-3+rand()%7) BitL), fcos(r)>>2, fsin(r)>>2, DATGOREHAND21+i2);
                break;
            case 2:
                Shoot(BUL_GORE, Md->Pl[i].X+((-3+rand()%7) BitL), Md->Pl[i].Y+((-3+rand()%7) BitL), fcos(r)>>2, fsin(r)>>2, DATGOREHAND31+i2);
                break;
            }; // switch
        }
        for (int i2 = 0; i2 < 20; i2 ++)
        {
            r = rand()%255;
            // ruumiinosia enemmän pyörien
            int pow = rand()%100;
            Shoot(BUL_GORE, Md->Pl[i].X+((-3+rand()%7) BitL), Md->Pl[i].Y - (3 BitL)+((-3+rand()%7) BitL), fcos(itofix(r))*pow/100,fsin(itofix(r))*pow/100, DATGORE01+Rand()%8);
        } // for (int i = 0; i < 4; i ++)
        for (int i2 = 0; i2 < 50; i2 ++) // verta... ei kuitenkaan niin paljon
        {
            r = Rand()%255;
            int pow = rand()%50;
            Shoot(BUL_BLOOD, Md->Pl[i].X, Md->Pl[i].Y - (3 BitL), (fcos(r BitL)*pow/200), (fsin(r BitL)*pow/200));
        } // for (int i2 = 0; i2 < 12; i2 ++)
    } // if (weapon==ITEM_FALL)
    if (weapon == ITEM_LAVA)
    {
        Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx, Md->Pl[i].My,  DATWITHHEAD5);
    } //  if (weapon == ITEM_LAVA)
    if (weapon != ITEM_LAVA) if (weapon != ITEM_PLASMAPISTOL) if (!Bodyfly)
            {
// yleinen kuolinsyy....
                if (Md->Pl[i].Damage[0]+Md->Pl[i].Damage[1]+Md->Pl[i].Damage[2] >= Md->Pl[i].Totaldamage)
                {
                    for (int i2 = 0; i2 < 50; i2 ++) // verta
                    {
                        r = Rand()%255;
                        Shoot(BUL_BLOOD, Md->Pl[i].X, Md->Pl[i].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000);
                    } // for (int i2 = 0; i2 < 12; i2 ++)
                    // ruumis pään kanssa hieman pyörien

                    Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx, Md->Pl[i].My,  DATWITHHEAD1+i);
                    Bodyfly = true;
                    for (int i2 = 0; i2 < 15; i2 ++)
                    {
                        r = Suunta(128+Rand()%128);
                        // ruumiinosia enemmän pyörien
                        Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx+fcos(itofix(r))>>2,Md->Pl[i].My+fsin(itofix(r))>>2, DATGORE01+Rand()%8);
                    } // for (int i = 0; i < 4; i ++)
                } // if (Md->Pl[i].Damage[0]+1+Md->Pl[i].Damage[1]+1+Md->Pl[i].Damage[2]+1 == Md->Pl[i].Totaldamage)
// päähän sattu
                if (Md->Pl[i].Damage[0]>=Md->Pl[i].Killdamage[0]) if (!Bodyfly)
                    {
                        for (int i2 = 0; i2 < 36; i2 ++) // verta... ei kuitenkaan niin paljon
                        {
                            r = Rand()%255;
                            Shoot(BUL_BLOOD, Md->Pl[i].X, Md->Pl[i].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000);
                        } // for (int i2 = 0; i2 < 12; i2 ++)
                        if (Rand()%2 == 0) // jos arpa on 0 niin pää irti
                        {
                            if (Bodyfly == false)
                            {
                                // päätön ruumis
                                Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx, Md->Pl[i].My,  DATHEADLESS1+i);
                                // pyörivä pää
                                Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx, Md->Pl[i].My-12000, DATSEVEREHEAD);
                            } //         if (Bodyfly == false)
                        } else // muuten pää räjähtää :)
                        {
                            for (int i2 = 0; i2 < 10; i2 ++)
                            {
                                r = Suunta(128+Rand()%128); // muutama ruumiinosa
                                Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx+fcos(itofix(r))>>2,Md->Pl[i].My+fsin(itofix(r))>>2, DATGORE01+Rand()%8);
                            } // for (int i = 0; i < 4; i ++)
                            if (Bodyfly == false) // jos ei ole lentänyt ruumista niin päätön sellainen tulee
                            {
                                Bodyfly = true;
                                Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx, Md->Pl[i].My,  DATHEADLESS1+i);
                            } // (Bodyfly == false)
                        } //       if (Rand()%2 == 0) ; else
                    } // if (Md->Pl[i].Damage[0]==Md->Pl[i].Killdamage[0])
// Mahaan sattu
                if (Md->Pl[i].Damage[1]>=Md->Pl[i].Killdamage[1]) if (!Bodyfly)
                    {
                        for (int i2 = 0; i2 < 60; i2 ++) // paljon verta
                        {
                            r = Rand()%255;
                            Shoot(BUL_BLOOD, Md->Pl[i].X, Md->Pl[i].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000);
                        } // for (int i2 = 0; i2 < 12; i2 ++)
                        if (Bodyfly == false)
                        {
                            // ruumis pään kanssa
                            Bodyfly = true;
                            Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx, Md->Pl[i].My,  DATHANDLESS1+i);
                        } //      if (Bodyfly == false)

                        for (int i3 = 0; i3 < 2; i3++) // käsiä
                        {
                            r = Suunta(128+Rand()%128);

                            switch(i) // (väri pelaajan mukaan)
                            {
                            case 0:
                                Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx+fcos(r)>>2, Md->Pl[i].My+fsin(r)>>2, DATGOREHAND11+i3);
                                break;
                            case 1:
                                Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx+fcos(r)>>2, Md->Pl[i].My+fsin(r)>>2, DATGOREHAND21+i3);
                                break;
                            case 2:
                                Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx+fcos(r)>>2, Md->Pl[i].My+fsin(r)>>2, DATGOREHAND31+i3);
                                break;
                            }; // switch
                        } // for i3
                        for (int i2 = 0; i2 < 10; i2 ++) // muutama kimpale
                        {
                            r = Suunta(128+Rand()%128);
                            Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx+fcos(itofix(r))>>2,Md->Pl[i].My+fsin(itofix(r))>>2, DATGORE01+Rand()%8);
                        } // for (int i = 0; i < 4; i ++)
                    } // if (Md->Pl[i].Damage[1]==Md->Pl[i].Killdamage[1])
// jalkoihin sattu
                if (Md->Pl[i].Damage[2]>=Md->Pl[i].Killdamage[2]) if (!Bodyfly)
                    {
                        for (int i2 = 0; i2 < 50; i2 ++) // verta
                        {
                            r = Rand()%255;
                            Shoot(BUL_BLOOD, Md->Pl[i].X, Md->Pl[i].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000);
                        } // for (int i2 = 0; i2 < 25; i2 ++)

                        if (Bodyfly == false)
                        {
                            Bodyfly = true;
                            // ruumis pään kanssa
                            Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx, Md->Pl[i].My,  DATLEGLESS1+i);
                        } // if (Bodyfly == false)
                        // kaksi jalkaa
                        Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx-50000+Rand()%100000, Md->Pl[i].My-50000+Rand()%100000,  DATGORELEGS1);
                        Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx-50000+Rand()%100000, Md->Pl[i].My-50000+Rand()%100000,  DATGORELEGS2);
                        for (int i2 = 0; i2 < 12; i2 ++) // + kimpaleita
                        {
                            r = Suunta(128+Rand()%128);
                            Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx+fcos(itofix(r))>>2,Md->Pl[i].My+fsin(itofix(r))>>2, DATGORE01+Rand()%8);
                        } // for (int i = 0; i < 4; i ++)
                    } // if (Md->Pl[i].Damage[2]==Md->Pl[i].Killdamage[2])
            } // Inte lava
} // Kill_player(int i)
void Kill_bot(int i, int weapon, int Killer, char killertype)
{
    int r;
    bool Bodyfly = false; // eli lentääkö ruumis
    if (Md->Bot[i].Anim != ANI_PLASMADEATH)
    {
        // tarvitaan siihen ettei lennä kahta ruumista
        Playsample(SAMP_FLESH1, Opt->sound.Soundvolume*2, 64);
        Playsample(SAMP_FLESH2, Opt->sound.Soundvolume*2, 128);
        Playsample(SAMP_FLESH3, Opt->sound.Soundvolume*2, 192);
        if (Md->Bot[i].Live)
            if (killertype == 0) if (Killer>=0) // Jos tappaja onkin pelaaja niin kill counteria plussataan
                    Md->Pl[Killer].Botskilled++;
        if (weapon != ITEM_PLASMAPISTOL)
            Md->Bot[i].Live = false; // ja pelaaja kuolee pois
// yleinen kuolinsyy....
    }
    if (weapon==ITEM_PLASMAPISTOL)
    {
        Md->Bot[i].Anim = ANI_PLASMADEATH;
        Md->Bot[i].Picture = 0;
        for (int i2 = 0; i2 < 40; i2 ++) // verta
        {
            r = Rand()%255;
            Shoot(BUL_BLOOD, Md->Bot[i].X, Md->Bot[i].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000, 1);
        } // for (int i2 = 0; i2 < 12; i2 ++)
        // ruumis pään kanssa hieman pyörien
        for (int i2 = 0; i2 < 8; i2 ++)
        {
            r = Suunta(128+Rand()%128);
            // ruumiinosia enemmän pyörien
            Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx+fcos(itofix(r))>>2,Md->Bot[i].My+fsin(itofix(r))>>2, DATGORE11+Rand()%8);
        } // for (int i = 0; i < 4; i ++)
    }


    if (weapon != ITEM_PLASMAPISTOL)
    {

        if (Md->Bot[i].Damage[0]+Md->Bot[i].Damage[1]+Md->Bot[i].Damage[2] == Md->Bot[i].Totaldamage)
        {
            for (int i2 = 0; i2 < 40; i2 ++) // verta
            {
                r = Rand()%255;
                Shoot(BUL_BLOOD, Md->Bot[i].X, Md->Bot[i].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000, 1);
            } // for (int i2 = 0; i2 < 12; i2 ++)
            // ruumis pään kanssa hieman pyörien
            Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx, Md->Bot[i].My,  DATWITHHEAD4);
            Bodyfly = true;
            for (int i2 = 0; i2 < 8; i2 ++)
            {
                r = Suunta(128+Rand()%128);
                // ruumiinosia enemmän pyörien
                Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx+fcos(itofix(r))>>2,Md->Bot[i].My+fsin(itofix(r))>>2, DATGORE11+Rand()%8);
            } // for (int i = 0; i < 4; i ++)
        } // if (Md->Bot[i].Damage[0]+1+Md->Bot[i].Damage[1]+1+Md->Bot[i].Damage[2]+1 == Md->Bot[i].Totaldamage)
// päähän sattu
        if (Md->Bot[i].Damage[0]>=Md->Bot[i].Killdamage[0])
        {
            for (int i2 = 0; i2 < 36; i2 ++) // verta... ei kuitenkaan niin paljon
            {
                r = Rand()%255;
                Shoot(BUL_BLOOD, Md->Bot[i].X, Md->Bot[i].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000, 1);
            } // for (int i2 = 0; i2 < 12; i2 ++)
            if (Rand()%2 == 0) // jos arpa on 0 niin pää irti
            {
                if (Bodyfly == false)
                {
                    // päätön ruumis
                    Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx, Md->Bot[i].My,  DATHEADLESS4);
                    // pyörivä pää
                    Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx, Md->Bot[i].My-12000, DATSEVEREHEAD2);
                } //         if (Bodyfly == false)
            } else // muuten pää räjähtää :)
            {
                for (int i2 = 0; i2 < 4; i2 ++)
                {
                    r = Suunta(128+Rand()%128); // muutama ruumiinosa
                    Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx+fcos(itofix(r))>>2,Md->Bot[i].My+fsin(itofix(r))>>2, DATGORE11+Rand()%8);
                } // for (int i = 0; i < 4; i ++)
                if (Bodyfly == false) // jos ei ole lentänyt ruumista niin päätön sellainen tulee
                {
                    Bodyfly = true;
                    Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx, Md->Bot[i].My,  DATHEADLESS4);
                } // (Bodyfly == false)
            } //       if (Rand()%2 == 0) ; else
        } // if (Md->Bot[i].Damage[0]==Md->Bot[i].Killdamage[0])
// Mahaan sattu
        if (Md->Bot[i].Damage[1]>=Md->Bot[i].Killdamage[1])
        {
            for (int i2 = 0; i2 < 25; i2 ++) // paljon verta
            {
                r = Rand()%255;
                Shoot(BUL_BLOOD, Md->Bot[i].X, Md->Bot[i].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000, 1);
            } // for (int i2 = 0; i2 < 12; i2 ++)
            if (Bodyfly == false)
            {
                // ruumis pään kanssa
                Bodyfly = true;
                Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx, Md->Bot[i].My,  DATHANDLESS4);
            } //      if (Bodyfly == false)

            for (int i3 = 0; i3 < 2; i3++) // käsiä
            {
                r = Suunta(128+Rand()%128);
                Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx+fcos(r)>>2, Md->Bot[i].My+fsin(r)>>2, DATGOREHAND41+i3);
            } // for i3
            for (int i2 = 0; i2 < 4; i2 ++) // muutama kimpale
            {
                r = Suunta(128+Rand()%128);
                Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx+fcos(itofix(r))>>2,Md->Bot[i].My+fsin(itofix(r))>>2, DATGORE11+Rand()%8);
            } // for (int i = 0; i < 4; i ++)
        } // if (Md->Bot[i].Damage[1]==Md->Bot[i].Killdamage[1])
// jalkoihin sattu
        if (Md->Bot[i].Damage[2]>=Md->Bot[i].Killdamage[2])
        {
            for (int i2 = 0; i2 < 25; i2 ++) // verta
            {
                r = Rand()%255;
                Shoot(BUL_BLOOD, Md->Bot[i].X, Md->Bot[i].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000, 1);
            } // for (int i2 = 0; i2 < 25; i2 ++)

            if (Bodyfly == false)
            {
                Bodyfly = true;
                // ruumis pään kanssa
                Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx, Md->Bot[i].My,  DATLEGLESS4);
            } // if (Bodyfly == false)
            // kaksi jalkaa
            Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx-50000+Rand()%100000, Md->Bot[i].My-50000+Rand()%100000,  DATGORELEGS21);
            Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx-50000+Rand()%100000, Md->Bot[i].My-50000+Rand()%100000,  DATGORELEGS22);
            for (int i2 = 0; i2 < 5; i2 ++) // + kimpaleita
            {
                r = Suunta(128+Rand()%128);
                Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx+fcos(itofix(r))>>2,Md->Bot[i].My+fsin(itofix(r))>>2, DATGORE11+Rand()%8);
            } // for (int i = 0; i < 4; i ++)
        } // if (Md->Bot[i].Damage[2]==Md->Bot[i].Killdamage[2])
    }
} // Kill_bot(int i)
void Explode_player(int i, int Killer, char killertype)
{
    if (Md->Pl[i].Live) Md->Pl[i].Died++;
    Md->Pl[i].Damage[0] = Md->Pl[i].Killdamage[0];
    Md->Pl[i].Damage[1] = Md->Pl[i].Killdamage[1];
    Md->Pl[i].Damage[2] = Md->Pl[i].Killdamage[2];
    if(killertype==0)
        if (Killer>=0) if (Md->Pl[i].Live)// Jos tappaja onkin pelaaja niin kill counteria plussataan
                Md->Pl[Killer].Kills[i]++;
    Md->Pl[i].Live = false; // ja pelaaja kuolee pois
    int r;
    for (int i2 = 0; i2 < 80; i2 ++) // verta
    {
        r = Rand()%255;
        double Power = double(Rand()%200)/double(100);
        Shoot(BUL_BLOOD, Md->Pl[i].X, Md->Pl[i].Y - (3 BitL), (Md->Pl[i].Mx)+int(((fcos(r BitL)>>4)-5000+Rand()%10000)*Power), (Md->Pl[i].My)+int(Power*((fsin(r BitL)>>4)-5000+Rand()%10000)));
    } // for (int i2 = 0; i2 < 12; i2 ++)
    // ruumis pään kanssa hieman pyörien
    for (int i2 = 0; i2 < 20; i2 ++)
    {
        r = Suunta(128+Rand()%128);
        // ruumiinosia enemmän pyörien
        double power = double(Rand()%200)/double(100);
        Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, int((Md->Pl[i].Mx+fcos(itofix(r))>>2)*power),int((Md->Pl[i].My+fsin(itofix(r))>>2)*power), DATGORE01+Rand()%8);
    } // for (int i = 0; i < 4; i ++)
    Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx, Md->Pl[i].My-12000, DATSEVEREHEAD);
    Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx-50000+Rand()%100000, Md->Pl[i].My-50000+Rand()%100000,  DATGORELEGS1);
    Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx-50000+Rand()%100000, Md->Pl[i].My-50000+Rand()%100000,  DATGORELEGS2);

    for (int i3 = 0; i3 < 2; i3++) // käsiä
    {
        r = Suunta(128+Rand()%128);

        switch(i) // (väri pelaajan mukaan)
        {
        case 0:
            Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx+fcos(r)>>2, Md->Pl[i].My+fsin(r)>>2, DATGOREHAND11+i3);
            break;
        case 1:
            Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx+fcos(r)>>2, Md->Pl[i].My+fsin(r)>>2, DATGOREHAND21+i3);
            break;
        case 2:
            Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx+fcos(r)>>2, Md->Pl[i].My+fsin(r)>>2, DATGOREHAND31+i3);
            break;
        }; // switch
    } // for i3

} // Kill_player(int i)
void Explode_bot(int i, int Killer, char killertype)
{
    Md->Bot[i].Damage[0] = Md->Bot[i].Killdamage[0];
    Md->Bot[i].Damage[1] = Md->Bot[i].Killdamage[1];
    Md->Bot[i].Damage[2] = Md->Bot[i].Killdamage[2];
    if (Md->Bot[i].Live)  if(killertype==0)
            if (Killer>=0) if (Md->Pl[Killer].Live)// Jos tappaja onkin pelaaja niin kill counteria plussataan
                    Md->Pl[Killer].Botskilled++;
    Md->Bot[i].Live = false; // ja pelaaja kuolee pois
    int r;
    for (int i2 = 0; i2 < 80; i2 ++) // verta
    {
        r = Rand()%255;
        double Power = double(Rand()%200)/double(100);
        Shoot(BUL_BLOOD, Md->Bot[i].X, Md->Bot[i].Y - (3 BitL), (Md->Bot[i].Mx)+int(((fcos(r BitL)>>4)-5000+Rand()%10000)*Power), (Md->Bot[i].My)+int(Power*((fsin(r BitL)>>4)-5000+Rand()%10000)), 1);
    } // for (int i2 = 0; i2 < 12; i2 ++)
    // ruumis pään kanssa hieman pyörien
    for (int i2 = 0; i2 < 20; i2 ++)
    {
        r = Suunta(128+Rand()%128);
        // ruumiinosia enemmän pyörien
        double power = double(Rand()%200)/double(100);
        Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, int((Md->Bot[i].Mx+fcos(itofix(r))>>2)*power),int((Md->Bot[i].My+fsin(itofix(r))>>2)*power), DATGORE11+Rand()%8);
    } // for (int i = 0; i < 4; i ++)
    Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx, Md->Bot[i].My-12000, DATSEVEREHEAD2);
    Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx-50000+Rand()%100000, Md->Bot[i].My-50000+Rand()%100000,  DATGORELEGS21);
    Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx-50000+Rand()%100000, Md->Bot[i].My-50000+Rand()%100000,  DATGORELEGS22);

    for (int i3 = 0; i3 < 2; i3++) // käsiä
    {
        r = Suunta(128+Rand()%128);
        Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, Md->Bot[i].Mx+fcos(r)>>2, Md->Bot[i].My+fsin(r)>>2, DATGOREHAND41+i3);
    } // for i3

} // Kill_player(int i)

void Yummy_explosion(int i, int Killer, char killertype)
{
    if (Md->Pl[i].Live) Md->Pl[i].Died++;
    Md->Pl[i].Damage[0] = Md->Pl[i].Killdamage[0];
    Md->Pl[i].Damage[1] = Md->Pl[i].Killdamage[1];
    Md->Pl[i].Damage[2] = Md->Pl[i].Killdamage[2];
    if(killertype==0)
        if (Killer>=0) if (Md->Pl[i].Live)// Jos tappaja onkin pelaaja niin kill counteria plussataan
                Md->Pl[Killer].Kills[i]++;
    Md->Pl[i].Live = false; // ja pelaaja kuolee pois
    int r;
    for (int i2 = 0; i2 < 100; i2 ++) // verta
    {
        r = Rand()%255;
        double Power = double(Rand()%400)/double(100);
        Shoot(BUL_BLOOD, Md->Pl[i].X, Md->Pl[i].Y - (3 BitL), int(((fcos(r BitL)>>4)-5000+Rand()%10000)*Power), int(Power*((fsin(r BitL)>>4)-5000+Rand()%10000)));
    } // for (int i2 = 0; i2 < 12; i2 ++)
    // ruumis pään kanssa hieman pyörien
    for (int i2 = 0; i2 < 60; i2 ++)
    {
        r = Suunta(128+Rand()%128);
        // ruumiinosia enemmän pyörien
        double power = double(Rand()%400)/double(100);
        Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, int((fcos(itofix(r))>>2)*power),int((fsin(itofix(r))>>2)*power), DATGORE01+Rand()%8);
    } // for (int i = 0; i < 4; i ++)
    Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx, Md->Pl[i].My-12000, DATSEVEREHEAD);
    for (int i3 = 0; i3 < 2; i3++) // käsiä
    {
        r = Suunta(128+Rand()%128);

        switch(i) // (väri pelaajan mukaan)
        {
        case 0:
            Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx+fcos(r)>>2, Md->Pl[i].My+fsin(r)>>2, DATGOREHAND11+i3);
            break;
        case 1:
            Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx+fcos(r)>>2, Md->Pl[i].My+fsin(r)>>2, DATGOREHAND21+i3);
            break;
        case 2:
            Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx+fcos(r)>>2, Md->Pl[i].My+fsin(r)>>2, DATGOREHAND31+i3);
            break;
        }; // switch
    } // for i3
    Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx-50000+Rand()%100000, Md->Pl[i].My-50000+Rand()%100000,  DATGORELEGS1);
    Shoot(BUL_GORE, Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Mx-50000+Rand()%100000, Md->Pl[i].My-50000+Rand()%100000,  DATGORELEGS2);

} // Kill_player(int i)
void Yummy_bot_explosion(int i, int Killer, char killertype)
{
    Md->Bot[i].Damage[0] = Md->Bot[i].Killdamage[0];
    Md->Bot[i].Damage[1] = Md->Bot[i].Killdamage[1];
    Md->Bot[i].Damage[2] = Md->Bot[i].Killdamage[2];
    if (Md->Bot[i].Live)  if(killertype==0)
            if (Killer>=0) if (Md->Pl[Killer].Live)// Jos tappaja onkin pelaaja niin kill counteria plussataan
                    Md->Pl[Killer].Botskilled++;
    Md->Bot[i].Live = false; // ja pelaaja kuolee pois
    int r;
    for (int i2 = 0; i2 < 100; i2 ++) // verta
    {
        r = Rand()%255;
        double Power = double(Rand()%400)/double(100);
        Shoot(BUL_BLOOD, Md->Bot[i].X, Md->Bot[i].Y - (3 BitL), int(((fcos(r BitL)>>4)-5000+Rand()%10000)*Power), int(Power*((fsin(r BitL)>>4)-5000+Rand()%10000)), 1);
    } // for (int i2 = 0; i2 < 12; i2 ++)
    // ruumis pään kanssa hieman pyörien
    for (int i2 = 0; i2 < 60; i2 ++)
    {
        r = Suunta(128+Rand()%128);
        // ruumiinosia enemmän pyörien
        double power = double(Rand()%400)/double(100);
        Shoot(BUL_GORE, Md->Bot[i].X, Md->Bot[i].Y, int((fcos(itofix(r))>>2)*power),int((fsin(itofix(r))>>2)*power), DATGORE11+Rand()%8);
    } // for (int i = 0; i < 4; i ++)

} // Kill_player(int i)

int Hit_player(int P, int X, int Y)
{
    int X2 = (Md->Pl[P].X BitR);
    int Y2 = (Md->Pl[P].Y BitR);
    if (Md->Pl[P].S == 1)
    {
        if (X >= X2 - 1)
            if (X <= X2 + 3)
                if (Y >= Y2 - 6)
                    if (Y <= Y2 - 1)
                        return 1; // Head;
    } // if (Md->Pl[p].S == 1) else
    {
        if (X >= X2 - 3)
            if (X <= X2 + 1)
                if (Y >= Y2 - 6)
                    if (Y <= Y2 - 1)
                        return 1; // Head;
    } // if (Md->Pl[p].S != 1)
    if (X >= X2 - 4)
        if (X <= X2 + 4)
            if (Y >= Y2 - 2)
                if (Y <= Y2 + 2)
                    return 2; // Torso
    if (X >= X2 - 3)
        if (X <= X2 + 3)
            if (Y >= Y2 + 3)
                if (Y <= Y2 + 6)
                    return 3; // Legs
    return 0;
} // int Hit_player(int P, int X, int Y)
int Hit_bot(int P, int X, int Y)
{
    int X2 = (Md->Bot[P].X BitR);
    int Y2 = (Md->Bot[P].Y BitR);
    if (Md->Bot[P].S == 1)
    {
        if (X >= X2 - 1)
            if (X <= X2 + 3)
                if (Y >= Y2 - 6)
                    if (Y <= Y2 - 1)
                        return 1; // Head;
    } // if (Md->Pl[p].S == 1) else
    {
        if (X >= X2 - 3)
            if (X <= X2 + 1)
                if (Y >= Y2 - 6)
                    if (Y <= Y2 - 1)
                        return 1; // Head;
    } // if (Md->Pl[p].S != 1)
    if (X >= X2 - 4)
        if (X <= X2 + 4)
            if (Y >= Y2 - 2)
                if (Y <= Y2 + 2)
                    return 2; // Torso
    if (X >= X2 - 3)
        if (X <= X2 + 3)
            if (Y >= Y2 + 3)
                if (Y <= Y2 + 6)
                    return 3; // Legs
    return 0;
} // int Hit_bot(int P, int X, int Y)
void Update_pistol(int i, int X, int Y)
{
    if (Md->Bul[i].Dat[0] == ITEM_SNIPERRIFLE)
        Md->Bul[i].My -= Gravity;
    int apu = getpixel(Md->Map, X, Y); // tarvitaan törmäyscheckkiin

    if (apu>0) // jos ei ole kalliossa
        if ((apu < 121) || (apu > 143))
        {
            int Ax = Md->Bul[i].Ox BitR;
            int Ay = Md->Bul[i].Oy BitR;
            line(Md->Map, X, Y, Ax, Ay, 0);
            circlefill(Md->Map, X, Y, 2, 0);
            if (Opt->Parallax)
            {
                line(Parallax, X>>1, Y>>1, Ax>>1, Ay>>1, 0);
                circlefill(Parallax, X>>1, Y>>1, 1, 0);
            } //      if (Opt->Parallax)

            bool Found = false;
            /* Jos on playereiden ruudussa */

            for (int i2 = 0; i2 < Opt->Players; i2++)
                if (X > (Md->Pl[i2].X BitR) - (Clipx>>1))
                    if (X < (Md->Pl[i2].X BitR) + (Clipx>>1))
                        if (Y > (Md->Pl[i2].Y BitR) - (Clipy>>1))
                            if (Y < (Md->Pl[i2].Y BitR) + (Clipy>>1))
                                Found = true;
            if (Dirtsample == false)
            {
                if (Found) // Jos on playereiden ruudussa niin soi kovempaa
                    Playsample(SAMP_DIRT1, Opt->sound.Soundvolume>>1, 128);
                else;
                Playsample(SAMP_DIRT1, int(Opt->sound.Soundvolume/1.5), 128);
                Dirtsample = true;
            } // Dirtsample == false

            Md->Bul[i].Live = false; // bulletti kuoli
            for (int Count = 0; Count < 6; Count++) // kakkua lentää
                Shoot(BUL_DIRT, Md->Bul[i].X+(itofix(-1+Rand()%3)), Md->Bul[i].Y+(itofix(-1+Rand()%3)), fcos(itofix(Suunta(160+Rand()%65)))>>2, fsin(itofix(Suunta(160+Rand()%65)))>>2);
        }  // if (getpixel(Md->Map, X, Y))
    if ((apu >= 121) && (apu <= 143)) // kallioon osuminen
    {
        if (Rand()%5==0) // kimpoaminen, ääni saadaan taajuutta vaihtamalla
            Playsample(SAMP_BOUNCE1, int(Opt->sound.Soundvolume*(50+Rand()%50)/100), 128, 5050+Rand()%20000);
        if (Md->Bul[i].Dat[1]) Md->Bul[i].Live = false; // jos kiven sisällä
        Md->Bul[i].Dat[1]++; // "kiven sisällä" countteri
        if (Md->Bul[i].Mx > 0) // kimpo x
            Md->Bul[i].Mx = -(Md->Bul[i].Mx>>1)-100000+Rand()%200000;
        else
            Md->Bul[i].Mx = abs(Md->Bul[i].Mx>>1)-100000+Rand()%200000;
        if (Md->Bul[i].My > 0) // kimpo y
            Md->Bul[i].My = -(Md->Bul[i].My>>1)-100000+Rand()%200000;
        else
            Md->Bul[i].My = abs(Md->Bul[i].My>>1)-100000+Rand()%200000;
    } //     if ((apu >= 121) && (apu <= 143))
    for (int i2 = 0; i2 < Maxbuildings; i2++) if (Md->Bld[i2].Live)
        {
            if (X >= (Md->Bld[i2].X BitR) )
                if (X <= (Md->Bld[i2].X BitR) + (((BITMAP*) Dat[Bldpic[Md->Bld[i2].Type]+Md->Bld[i2].Pic].dat)->w))
                    if (Y >= (Md->Bld[i2].Y BitR) )
                        if (Y <= (Md->Bld[i2].Y BitR) + (((BITMAP*) Dat[Bldpic[Md->Bld[i2].Type]+Md->Bld[i2].Pic].dat)->h))
                        {
                            int r = 0; // SAVUA pyöreästi
                            for (int count = 0; count < 20; count++)
                            {
                                r = Suunta(itofix(Rand()%255) + Rand()%65535);
                                Shoot(BUL_SMOKE, Md->Bul[i].X - 10000 + Rand()%20000, Md->Bul[i].Y - 10000 + Rand()%20000, (fcos(r)/50) - 1000 + Rand()%2000,(fsin(r)/50) - 1000 + Rand()%2000);
                            }

                            Md->Bld[i2].Energy -= 1;
                            if (Md->Bld[i2].Energy < 0)
                                Destroy_building(i2);
                            Md->Bul[i].Live = false;
                            // SAMPLE REQUEST
                        } //
        } // for (int i2 = 0; i2 < Maxbuildings; i2++) if (Md->Bld[i2].Live)
    int Hit = 0; // mihin osutaa
    if (Md->Bul[i].Life < 1998) // ettei vaan osu omaan sormeen
        for (int i2 = 0; i2 < Opt->Players; i2++) if (Md->Pl[i2].Live)
            {
                Hit = Hit_player(i2, X, Y);
                int r; // apumuuttuja suunnan määrittelylle
                if (Hit > 0)
                    for (int Count = 0; Count < 24; Count++) // verta
                    {
                        r = Rand()%255;
                        Shoot(BUL_BLOOD, Md->Pl[i2].X, Md->Pl[i2].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000);
                    } // for (int Count = 0; Count < 12; Count++)
                if (X >= (Md->Pl[i2].X BitR) - 6)
                    if (X <= (Md->Pl[i2].X BitR) + 8)
                        if (Y >= (Md->Pl[i2].Y BitR) - 16)
                            if (Y <= (Md->Pl[i2].Y BitR) - 6)
                                if (Md->Pl[i2].Parachute)
                                {
                                    Md->Pl[i2].Parachuteshotdown = true;
                                    Md->Pl[i2].Parachute = false;
                                } //                 if (Hit < 3)                 if (Md->Pl[i2].Parachute)
                if (Hit > 0)
                {

                    // Damagea
                    int Damage = Mindamage[Md->Bul[i].Dat[0]]+Rand()%(Randomdamage[Md->Bul[i].Dat[0]]+1);
                    if (Md->Pl[i2].Damage[Hit-1] < Md->Pl[i2].Killdamage[Hit-1])
                        Md->Pl[i2].Damage[Hit-1]+=Damage;
                    // jos tulee kuolo.. (Damaget suurempia kuin totaldamage)
                    if ((Md->Pl[i2].Damage[0]) + (Md->Pl[i2].Damage[1]) + (Md->Pl[i2].Damage[2]) >= Md->Pl[i2].Totaldamage)
                    {
                        Kill_player(i2, Md->Bul[i].Dat[0], Md->Bul[i].Owner, Md->Bul[i].Ownertype);
                        if (Md->Pl[i2].Damage[Hit-1] >= Md->Pl[i2].Killdamage[Hit-1])
                            Md->Pl[i2].Damage[Hit-1] = Md->Pl[i2].Killdamage[Hit-1];
                    } //                 if (Md->Pl[i2].Damage[0] + Md->Pl[i2].Damage[1] + Md->Pl[i2].Damage[2] >= Md->Pl[i2].Totaldamage)
                    // joku ruumiinosa pettää
                    if (Md->Pl[i2].Damage[Hit-1] >= Md->Pl[i2].Killdamage[Hit-1]) if (Md->Pl[i2].Live)
                        {
                            Kill_player(i2, Md->Bul[i].Dat[0], Md->Bul[i].Owner, Md->Bul[i].Ownertype);
                            Md->Pl[i2].Damage[Hit-1] = Md->Pl[i2].Killdamage[Hit-1];
                        } // if (Md->Pl[i2].Damage[Hit-1]>2)
                } // if (Hit > 0)

                if (Md->Pl[i2].Live) // Elossa vielä?? Mitä?
                    switch(Hit)
                    {   // Lits
                    case 1:
                        Playsample(SAMP_FLESH1, Opt->sound.Soundvolume*2, 128);
                        Md->Pl[i2].Mx += Md->Bul[i].Mx >> 3; // iso tönäsy
                        Md->Pl[i2].My += Md->Bul[i].My >> 3;
                        break; // Läts
                    case 2:
                        Playsample(SAMP_FLESH2, Opt->sound.Soundvolume*2, 128);
                        Md->Pl[i2].Mx += Md->Bul[i].Mx >> 4; // tönäsy
                        Md->Pl[i2].My += Md->Bul[i].My >> 4;
                        break; // Löts
                    case 3:
                        Playsample(SAMP_FLESH3, Opt->sound.Soundvolume*2, 128);
                        Md->Pl[i2].Mx += Md->Bul[i].Mx >> 5; // pikku tönäsy
                        Md->Pl[i2].My += Md->Bul[i].My >> 5;
                        break;
                    };

                if (Hit) Md->Bul[i].Live = false; // jos osunut niin luoti varmaan katoaa
            } //      for (int i2 = 0; i2 < Opt->Players; i2++)
    if (Md->Bul[i].Life < 1998) // ettei vaan osu omaan sormeen
        for (int i2 = 0; i2 < Opt->Bots; i2++) if (Md->Bot[i2].Live)
            {
                Hit = Hit_bot(i2, X, Y);
                int r; // apumuuttuja suunnan määrittelylle
                if (Hit > 0)
                    for (int Count = 0; Count < 12; Count++) // verta
                    {
                        r = Rand()%255;
                        Shoot(BUL_BLOOD, Md->Bot[i2].X, Md->Bot[i2].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000, 1);
                    } // for (int Count = 0; Count < 12; Count++)

                if (Hit > 0)
                {
                    // Damagea
                    int Damage = Mindamage[Md->Bul[i].Dat[0]]+Rand()%(Randomdamage[Md->Bul[i].Dat[0]]+1);
                    if (Md->Bot[i2].Damage[Hit-1] < Md->Bot[i2].Killdamage[Hit-1])
                        Md->Bot[i2].Damage[Hit-1]+=Damage;
                    // jos tulee kuolo.. (Damaget suurempia kuin totaldamage)
                    if ((Md->Bot[i2].Damage[0]) + (Md->Bot[i2].Damage[1]) + (Md->Bot[i2].Damage[2]) >= Md->Bot[i2].Totaldamage)
                    {
                        Kill_bot(i2, Md->Bul[i].Dat[0], Md->Bul[i].Owner, Md->Bul[i].Ownertype);
                        if (Md->Bot[i2].Damage[Hit-1] >= Md->Bot[i2].Killdamage[Hit-1])
                            Md->Bot[i2].Damage[Hit-1] = Md->Bot[i2].Killdamage[Hit-1];
                    } //                 if (Md->Bot[i2].Damage[0] + Md->Bot[i2].Damage[1] + Md->Bot[i2].Damage[2] >= Md->Bot[i2].Totaldamage)
                    // joku ruumiinosa pettää
                    if (Md->Bot[i2].Damage[Hit-1] >= Md->Bot[i2].Killdamage[Hit-1]) if (Md->Bot[i2].Live)
                        {
                            Kill_bot(i2, Md->Bul[i].Dat[0], Md->Bul[i].Owner, Md->Bul[i].Ownertype);
                            Md->Bot[i2].Damage[Hit-1] = Md->Bot[i2].Killdamage[Hit-1];
                        } // if (Md->Bot[i2].Damage[Hit-1]>2)
                } // if (Hit > 0)

                if (Md->Bot[i2].Live) // Elossa vielä?? Mitä?
                    switch(Hit)
                    {   // Lits
                    case 1:
                        Playsample(SAMP_FLESH1, Opt->sound.Soundvolume*2, 128);
                        Md->Bot[i2].Mx += Md->Bul[i].Mx >> 3; // iso tönäsy
                        Md->Bot[i2].My += Md->Bul[i].My >> 3;
                        break; // Läts
                    case 2:
                        Playsample(SAMP_FLESH2, Opt->sound.Soundvolume*2, 128);
                        Md->Bot[i2].Mx += Md->Bul[i].Mx >> 4; // tönäsy
                        Md->Bot[i2].My += Md->Bul[i].My >> 4;
                        break; // Löts
                    case 3:
                        Playsample(SAMP_FLESH3, Opt->sound.Soundvolume*2, 128);
                        Md->Bot[i2].Mx += Md->Bul[i].Mx >> 5; // pikku tönäsy
                        Md->Bot[i2].My += Md->Bul[i].My >> 5;
                        break;
                    };
                if (Hit) Md->Bul[i].Live = false; // jos osunut niin luoti varmaan katoaa
            } //      for (int i2 = 0; i2 < Opt->Players; i2++)


} // Update_pistol
void Update_dirt(int i, int X, int Y)
{
    if (Md->Bul[i].Dat[0] == 0) // värin määrittäminen maaston perusteella
    {
        Md->Bul[i].Dat[0] = 1;
        int apu = 0, stuck = 0;
        bool Don = false;
        do
        {
            apu = getpixel(Md->Map, X-2+Rand()%5, Y+Rand()%4);
            if (apu > 121) if (apu < 143) apu = 0;
            Md->Bul[i].Dat[1] = apu;
            stuck++;
            if (apu > 0) Don = true;
            if (stuck > 20) Don = true;
        } while (Don == false);
        if (Md->Bul[i].Dat[1] == 0) Md->Bul[i].Live = false;
    } // if (Md->Bul[i].Dat[0] == 0)
    // jos törmää johonkin niin jää kiinni
    if ((getpixel(Md->Map, X-1, Y)>0) ||
            (getpixel(Md->Map, X+1, Y)>0) ||
            (getpixel(Md->Map, X, Y-1)>0) ||
            (getpixel(Md->Map, X, Y+1)>0))
    {
        putpixel(Md->Map, X, Y, Md->Bul[i].Dat[1]);
        if (Opt->Parallax)
        {
            drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
            putpixel(Parallax, X>>1, Y>>1, Md->Bul[i].Dat[1]);
            drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
        }
        Md->Bul[i].Live = false; // ja nirri pois bulletilta
    } // if (getpixel(Md->Map, X, Y))
} // Update_pistol
void Update_blood(int i, int X, int Y)
{
    if (Md->Bul[i].Dat[2] == 0) // värin määritys (vain kerran)
    {
        Md->Bul[i].Dat[2] = 1;
        switch(Md->Bul[i].Dat[0])
        {
        case 0:
            Md->Bul[i].Dat[1] = 32+Rand()%6;
            break;
        case 1:
            Md->Bul[i].Dat[1] = 67+Rand()%6;
            break;
        };
    } // if (Md->Bul[i].Dat[0] == 0)
    if ((getpixel(Md->Map, X, Y)>0)) // jos jää johonkin kiinni
    {
        putpixel(Md->Map, X, Y, Md->Bul[i].Dat[1]); // veri maastoon
        if (Opt->Parallax)
        {
            drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
            putpixel(Parallax, X>>1, Y>>1, Md->Bul[i].Dat[1]); // veri maastoon
            drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
        }
        Md->Bul[i].Live = false; // nirri pois
    } // if (getpixel(Md->Map, X, Y))
} // Update_blood
void Update_gore(int i, int X, int Y)
{
    char Dropblood = 0; // tippuuko verikaari
    switch(Md->Bul[i].Dat[0]) // minkä tyyppinen ruumiinosa
    {
        // Jos kuuluu näihin niin verta tippuu
    case DATGORE01:
    case DATGORE02:
    case DATGORE03:
    case DATGORE04:
    case DATGORE05:
    case DATGORE06:
    case DATGORE07:
    case DATGORE08:
    case DATGOREHAND11:
    case DATGOREHAND12:
    case DATGOREHAND21:
    case DATGOREHAND22:
    case DATGOREHAND31:
    case DATGOREHAND32:
    case DATGORELEGS1:
    case DATGORELEGS2:
    case DATHEADLESS1:
    case DATHEADLESS2:
    case DATHEADLESS3:
    case DATLEGLESS1:
    case DATLEGLESS2:
    case DATLEGLESS3:
    case DATHANDLESS1:
    case DATHANDLESS2:
    case DATHANDLESS3:
    case DATSEVEREHEAD:
    case DATWITHHEAD1:
    case DATWITHHEAD2:
    case DATWITHHEAD3:
        Dropblood =1;
        break;
    case DATGORE11:
    case DATGORE12:
    case DATGORE13:
    case DATGORE14:
    case DATGORE15:
    case DATHANDLESS4:
    case DATLEGLESS4:
    case DATGORE16:
    case DATGORE17:
    case DATGORE18:
    case DATGOREHAND41:
    case DATGOREHAND42:
    case DATGORELEGS21:
    case DATGORELEGS22:
    case DATHEADLESS4:
    case DATSEVEREHEAD2:
    case DATWITHHEAD4:
        Dropblood =2;
        break;
    case DATWITHHEAD5:
    {
        int r = 0; // SAVUA pyöreästi
        r = Suunta(itofix(Rand()%255) + Rand()%65535);
        Shoot(BUL_SMOKE, Md->Bul[i].X - 10000 + Rand()%20000, Md->Bul[i].Y - 10000 + Rand()%20000, (fcos(r)/50) - 1000 + Rand()%2000,(fsin(r)/50) - 1000 + Rand()%2000);
    }
    break;
    }; //    switch(Md->Bul[i].Dat[0])


    Md->Bul[i].Dat[7]++; // 20 väliä ja sitten verta
    if (Md->Bul[i].Dat[7]==20) if (Dropblood)
        {
            Md->Bul[i].Dat[7] = 0;
            // verta josta nopeusvektorit ovat puolet raajat nopeusvektoreista
            Shoot(BUL_BLOOD, Md->Bul[i].X, Md->Bul[i].Y, Md->Bul[i].Mx>>1, Md->Bul[i].My>>1, (Dropblood==2) ? 1 : 0);
        } // if (Md->Bul[i].Dat[7]==6)
    BITMAP * bmp; // apumuuttuja kuvan koon määrittämiseen
    if (Md->Bul[i].Dat[8]==0) // pyörimissuunta ja vauhti(vain kerran)
    {
        Md->Bul[i].Dat[8] = 1;
        Md->Bul[i].Dat[2] = (-1500+Rand()%3000)*100;
    } //    if (Md->Bul[i].Dat[8]==0)
    Md->Bul[i].Dat[1] += Md->Bul[i].Dat[2]; // kulma
    // jos pyörii yli 255 astetta niin suunta clipataan
    if (Md->Bul[i].Dat[1] > itofix(255)) Md->Bul[i].Dat[1] = Suunta(Md->Bul[i].Dat[1]);
    // jos pyörii nolla ali niin suunta clipataan
    if (Md->Bul[i].Dat[1] < 0) Md->Bul[i].Dat[1] = Suunta(Md->Bul[i].Dat[1]);
    // jää jonnekin kiinni?
    if ((getpixel(Md->Map, X-1, Y)>0) ||
            (getpixel(Md->Map, X+1, Y)>0) ||
            (getpixel(Md->Map, X, Y-1)>0) ||
            (getpixel(Md->Map, X, Y+1)>0))
    {
        bmp = (BITMAP * ) Dat[Md->Bul[i].Dat[0]].dat;
        // mikä on lopullinen koordi
        rotate_sprite(Md->Map, bmp, X - (bmp->w>>1), Y- (bmp->h>>1), Md->Bul[i].Dat[1]);
        if (Opt->Parallax)
        {
            rotate_scaled_sprite(Parallax, bmp, (X - (bmp->w>>1))>>1, (Y- (bmp->h>>1))>>1, Md->Bul[i].Dat[1], 1<<15);
        }

        Md->Bul[i].Live = false;
    } // if (getpixel(Md->Map, X, Y))
} // Update_blood
void Update_bulletshell(int i, int X, int Y)
{
    if (Md->Bul[i].Dat[0] == 0) // värin määritys(vain kerran)
    {
        Md->Bul[i].Dat[0] = 1;
        Md->Bul[i].Dat[1] = 52+Rand()%4;
    } // if (Md->Bul[i].Dat[0] == 0)
    if ((getpixel(Md->Map, X, Y)>0)) // jos jää maastoon kiinni
    {
        putpixel(Md->Map, X, Y, Md->Bul[i].Dat[1]);
        bool Found = false;
        /* Jos on playereiden ruudussa */

        for (int i2 = 0; i2 < Opt->Players; i2++)
            if (X > (Md->Pl[i2].X BitR) - (Clipx>>1))
                if (X < (Md->Pl[i2].X BitR) + (Clipx>>1))
                    if (Y > (Md->Pl[i2].Y BitR) - (Clipy>>1))
                        if (Y < (Md->Pl[i2].Y BitR) + (Clipy>>1))
                            Found = true;
        if (Found) // Jos on playereiden ruudussa niin soi kovempaa
            Playsample(SAMP_EMPTYSHELL, int(Opt->sound.Soundvolume*(50+Rand()%50)/200), 128);
        else
            Playsample(SAMP_EMPTYSHELL, int(Opt->sound.Soundvolume*(50+Rand()%50)/250), 128);
        Md->Bul[i].Live = false;
    } // if (getpixel(Md->Map, X, Y))
} // void Update_bulletshell(int i, int X, int Y)
void Update_grenade(int i, int X, int Y)
{
    if (Md->Bul[i].Dat[8]==0) // pyörimissuunta ja vauhti(vain kerran)
    {
        Md->Bul[i].Dat[8] = 1;
        Md->Bul[i].Dat[2] = (-1500+Rand()%3000)*100;
    } //    if (Md->Bul[i].Dat[8]==0)
    if (Md->Bul[i].Dat[3] < 3)
        Md->Bul[i].Dat[1] += Md->Bul[i].Dat[2]; // kulma
    // jos pyörii yli 255 astetta niin suunta clipataan
    if (Md->Bul[i].Dat[1] > itofix(255)) Md->Bul[i].Dat[1] = Suunta(Md->Bul[i].Dat[1]);
    // jos pyörii nolla ali niin suunta clipataan
    if (Md->Bul[i].Dat[1] < 0) Md->Bul[i].Dat[1] = Suunta(Md->Bul[i].Dat[1]);

    int apu = getpixel(Md->Map, X, Y); // tarvitaan törmäyscheckkiin

    if (apu>0) // jos ei ole kalliossa
        if ((apu < 121) || (apu > 143))
        {
            Md->Bul[i].X = Md->Bul[i].Ox;
            Md->Bul[i].Y = Md->Bul[i].Oy;
            if (Md->Bul[i].Mx > 0) // kimpo x
                Md->Bul[i].Mx = -(Md->Bul[i].Mx>>2);
            else
                Md->Bul[i].Mx = abs(Md->Bul[i].Mx>>2);
            if (Md->Bul[i].My > 0) // kimpo y
                Md->Bul[i].My = -(Md->Bul[i].My>>2);
            else
                Md->Bul[i].My = abs(Md->Bul[i].My>>2);
            Md->Bul[i].Dat[2] = (-1500+Rand()%3000)*100;
        }  // if (getpixel(Md->Map, X, Y))
    if ((apu >= 121) && (apu <= 143)) // kallioon osuminen
    {
        Md->Bul[i].Dat[2] = (-1500+Rand()%3000)*100;
        Md->Bul[i].X = Md->Bul[i].Ox;
        Md->Bul[i].Y = Md->Bul[i].Oy;
        Md->Bul[i].Dat[3]++; // "kiven sisällä" countteri
        if (Md->Bul[i].Mx > 0) // kimpo x
            Md->Bul[i].Mx = -(Md->Bul[i].Mx>>1);
        else
            Md->Bul[i].Mx = abs(Md->Bul[i].Mx>>1);
        if (Md->Bul[i].My > 0) // kimpo y
            Md->Bul[i].My = -(Md->Bul[i].My>>1);
        else
            Md->Bul[i].My = abs(Md->Bul[i].My>>1);
    } //     if ((apu >= 16) && (apu <= 31))
    if (getpixel(Md->Map, X, Y) == 0) Md->Bul[i].Dat[3] = 0;
    if (Md->Bul[i].Dat[3] > 3)
    {
        Md->Bul[i].X  -= Md->Bul[i].Mx;
        Md->Bul[i].Y  -= Md->Bul[i].My;
        Md->Bul[i].Mx = 0;
        Md->Bul[i].My = 0;
    }
} // void Update_grenade(int i, int X, int Y)
void Update_lavabomb(int i, int X, int Y)
{
    if (Md->Bul[i].Dat[8]==0) // pyörimissuunta ja vauhti(vain kerran)
    {
        Md->Bul[i].Dat[8] = 1;
        Md->Bul[i].Dat[2] = (-1500+Rand()%3000)*100;
    } //    if (Md->Bul[i].Dat[8]==0)
    if (Md->Bul[i].Dat[3] < 3)
        Md->Bul[i].Dat[1] += Md->Bul[i].Dat[2]; // kulma
    // jos pyörii yli 255 astetta niin suunta clipataan
    if (Md->Bul[i].Dat[1] > itofix(255)) Md->Bul[i].Dat[1] = Suunta(Md->Bul[i].Dat[1]);
    // jos pyörii nolla ali niin suunta clipataan
    if (Md->Bul[i].Dat[1] < 0) Md->Bul[i].Dat[1] = Suunta(Md->Bul[i].Dat[1]);

    int apu = getpixel(Md->Map, X, Y); // tarvitaan törmäyscheckkiin

    if (apu>0) // jos ei ole kalliossa
    {
        Md->Bul[i].Live = false;
        int i3 = 0;
        for (int i2 = 0; i2 < Maxlava; i2++)
        {
            int r = 0; // SAVUA pyöreästi
            r = Suunta(itofix(Rand()%255) + Rand()%65535);
            Addlava(Md->Bul[i].X - 50000 + Rand()%100000, Md->Bul[i].Y - 50000 + Rand()%100000, (fcos(r)*4) - 1000 + Rand()%2000,((fsin(r)*4)) - 1000 + Rand()%2000, 0);
            i3++;
            if (i3 >= 1500) i2 = Maxlava;
        }
    }  // if (getpixel(Md->Map, X, Y))
} // void Update_lavabomb(int i, int X, int Y)
void Update_shrapnel(int i, int X, int Y)
{
    if (Md->Bul[i].Dat[8]==0) // pyörimissuunta ja vauhti(vain kerran)
    {
        Md->Bul[i].Dat[4] = rand()%3; // Sirpaletyyppi
        Md->Bul[i].Dat[8] = 1;
        Md->Bul[i].Dat[2] = (-3000+Rand()%6000)*100;
    } //    if (Md->Bul[i].Dat[8]==0)
    if (Md->Bul[i].Dat[3] < 3)
        Md->Bul[i].Dat[1] += Md->Bul[i].Dat[2]; // kulma
    // jos pyörii yli 255 astetta niin suunta clipataan
    if (Md->Bul[i].Dat[1] > itofix(255)) Md->Bul[i].Dat[1] = Suunta(Md->Bul[i].Dat[1]);
    // jos pyörii nolla ali niin suunta clipataan
    if (Md->Bul[i].Dat[1] < 0) Md->Bul[i].Dat[1] = Suunta(Md->Bul[i].Dat[1]);

    int apu = getpixel(Md->Map, X, Y); // tarvitaan törmäyscheckkiin
    int Hit = 0; // mihin osutaa
    for (int i2 = 0; i2 < Opt->Players; i2++) if (Md->Pl[i2].Live)
        {
            Hit = Hit_player(i2, X, Y);
            if (Hit) apu = 1;
        } //      for (int i2 = 0; i2 < Opt->Players; i2++)
    for (int i2 = 0; i2 < Opt->Bots; i2++) if (Md->Bot[i2].Live)
        {
            Hit = Hit_bot(i2, X, Y);
            int r; // apumuuttuja suunnan määrittelylle
            if (Hit) apu = 1;
        } //      for (int i2 = 0; i2 < Opt->Players; i2++)

    if (apu>0) // jos ei ole kalliossa
    {
        Md->Bul[i].Live = false;
        Addexp(4, Md->Bul[i].X>>16, Md->Bul[i].Y>>16, 0, Md->Bul[i].Owner,  Md->Bul[i].Ownertype);
    }  // if (getpixel(Md->Map, X, Y))
} // void Update_shrapnel(int i, int X, int Y)
void Update_shotgunshell(int i, int X, int Y)
{
    if (Md->Bul[i].Dat[0] == 0) // värin määritys(vain kerran)
    {
        Md->Bul[i].Dat[0] = 1;
        Md->Bul[i].Dat[1] = 32+Rand()%6;
    } // if (Md->Bul[i].Dat[0] == 0)
    if ((getpixel(Md->Map, X, Y)>0)) // jos jää maastoon kiinni
    {
        putpixel(Md->Map, X, Y, Md->Bul[i].Dat[1]);
        Md->Bul[i].Live = false;
    } // if (getpixel(Md->Map, X, Y))
} // void Update_bulletshell(int i, int X, int Y)
void Update_biglaser(int i, int X, int Y)
{
    Md->Bul[i].Life = 1000;
    if (Md->Bul[i].Dat[1] == 0) // savun väri sekä elämän pituus(vain kerran)
    {
        Md->Bul[i].Dat[1] = 1;
        Md->Bul[i].Dat[2] = 0;
    } // if (Md->Bul[i].Dat[0] == 0)
    Md->Bul[i].My -= Gravity; // kevyempää kuin ilma
    int r = (rand()%255)<<16;
    Shoot(BUL_PLASMA2, Md->Bul[i].X - 10000 + Rand()%20000, Md->Bul[i].Y - 10000 + Rand()%20000, (fcos(r)/20) - 1000 + Rand()%2000,(fsin(r)/20) - 1000 + Rand()%2000, ITEM_LASERCANNON);
    FAST_GETPIXEL(Md->Map, X, Y, r);
    if (r == 0) Md->Bul[i].Dat[2] = 0;
    else Md->Bul[i].Dat[2]++;
    if (Md->Bul[i].Dat[2] > 100)
    {
        Md->Bul[i].Live = false;
        Addexp(1, X, Y, 2, Md->Bul[i].Owner, Md->Bul[i].Ownertype);
    } // if (Md->Bul[i].Dat[4] > 100)
} // Update_smoke(int i, int X, int Y)
void Update_smoke(int i, int X, int Y)
{
    if (Md->Bul[i].Dat[0] == 0) // savun väri sekä elämän pituus(vain kerran)
    {
        Md->Bul[i].Dat[0] = 1;
        Md->Bul[i].Dat[1] = 24+Rand()%8;
        Md->Bul[i].Dat[2] = 500+Rand()%200;
    } // if (Md->Bul[i].Dat[0] == 0)
    Md->Bul[i].Dat[2]--; // elämää pois
    if (Md->Bul[i].Dat[2]<=0) Md->Bul[i].Live = false; // kuolo
    Md->Bul[i].My -= Gravity; // kevyempää kuin ilma
} // Update_smoke(int i, int X, int Y)
void Update_plasma(int i, int X, int Y)
{
    for (int i2 = 0; i2 < 2; i2++)
    {
        int r = 0;
        r = Suunta(itofix(Rand()%255) + Rand()%65535);
        if (Md->Bul[i].Dat[0]==ITEM_PLASMAPISTOL)
            Shoot(BUL_PLASMA2, Md->Bul[i].X - 20000 + Rand()%40000, Md->Bul[i].Y - 20000 + Rand()%40000, (fcos(r)/100) - 1000 + Rand()%2000,(fsin(r)/100) - 1000 + Rand()%2000);
        else
            Shoot(BUL_PLASMA3, Md->Bul[i].X - 20000 + Rand()%40000, Md->Bul[i].Y - 20000 + Rand()%40000, (fcos(r)/100) - 1000 + Rand()%2000,(fsin(r)/100) - 1000 + Rand()%2000);
    }
    for (int i2 = 0; i2 < 2; i2++)
    {
        int r = 0;
        r = Suunta(itofix(Rand()%255) + Rand()%65535);
        if (Md->Bul[i].Dat[0]==ITEM_PLASMAPISTOL)
            Shoot(BUL_PLASMA2, (Md->Bul[i].X-(Md->Bul[i].Mx>>1)) - 20000 + Rand()%40000, (Md->Bul[i].Y-(Md->Bul[i].My>>1)) - 20000 + Rand()%40000, (fcos(r)/100) - 1000 + Rand()%2000,(fsin(r)/100) - 1000 + Rand()%2000);
        else
            Shoot(BUL_PLASMA3, (Md->Bul[i].X-(Md->Bul[i].Mx>>1)) - 20000 + Rand()%40000, (Md->Bul[i].Y-(Md->Bul[i].My>>1)) - 20000 + Rand()%40000, (fcos(r)/100) - 1000 + Rand()%2000,(fsin(r)/100) - 1000 + Rand()%2000);
    }
    int apu = getpixel(Md->Map, X, Y); // tarvitaan törmäyscheckkiin

    if (apu>0) // jos ei ole kalliossa
    {
        Addexp(2, Md->Bul[i].X>>16, Md->Bul[i].Y>>16, 0, Md->Bul[i].Owner,  Md->Bul[i].Ownertype);
        Md->Bul[i].Live = false;
    } //     if (apu > 0)
    for (int i2 = 0; i2 < Maxbuildings; i2++) if (Md->Bld[i2].Live)
        {
            if (X >= (Md->Bld[i2].X BitR) )
                if (X <= (Md->Bld[i2].X BitR) + (((BITMAP*) Dat[Bldpic[Md->Bld[i2].Type]+Md->Bld[i2].Pic].dat)->w))
                    if (Y >= (Md->Bld[i2].Y BitR) )
                        if (Y <= (Md->Bld[i2].Y BitR) + (((BITMAP*) Dat[Bldpic[Md->Bld[i2].Type]+Md->Bld[i2].Pic].dat)->h))
                        {
                            int r = 0; // SAVUA pyöreästi
                            for (int count = 0; count < 20; count++)
                            {
                                r = Suunta(itofix(Rand()%255) + Rand()%65535);
                                Shoot(BUL_SMOKE, Md->Bul[i].X - 10000 + Rand()%20000, Md->Bul[i].Y - 10000 + Rand()%20000, (fcos(r)/50) - 1000 + Rand()%2000,(fsin(r)/50) - 1000 + Rand()%2000);
                            }
                            Addexp(2, Md->Bul[i].X>>16, Md->Bul[i].Y>>16, 0, Md->Bul[i].Owner,  Md->Bul[i].Ownertype);
                            Md->Bld[i2].Energy -= 1;
                            if (Md->Bld[i2].Energy < 0)
                                Destroy_building(i2);
                            Md->Bul[i].Live = false;
                            // SAMPLE REQUEST
                        } //
        } // for (int i2 = 0; i2 < Maxbuildings; i2++) if (Md->Bld[i2].Live)
    int Hit = 0; // mihin osutaa
    if (Md->Bul[i].Life < 1998) // ettei vaan osu omaan sormeen
        for (int i2 = 0; i2 < Opt->Players; i2++) if (Md->Pl[i2].Live)
            {
                Hit = Hit_player(i2, X, Y);
                int r; // apumuuttuja suunnan määrittelylle
                if (Hit > 0)
                    for (int Count = 0; Count < 12; Count++) // verta
                    {
                        r = Rand()%255;
                        Shoot(BUL_BLOOD, Md->Pl[i2].X, Md->Pl[i2].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000);
                    } // for (int Count = 0; Count < 12; Count++)

                if (Hit > 0)
                {
                    Addexp(2, Md->Bul[i].X>>16, Md->Bul[i].Y>>16, 0, Md->Bul[i].Owner,  Md->Bul[i].Ownertype);
                } // if (Hit > 0)

                if (Md->Pl[i2].Live) // Elossa vielä?? Mitä?
                    switch(Hit)
                    {   // Lits
                    case 1:
                        Playsample(SAMP_FLESH1, Opt->sound.Soundvolume*2, 128);
                        Md->Pl[i2].Mx += Md->Bul[i].Mx >> 3; // iso tönäsy
                        Md->Pl[i2].My += Md->Bul[i].My >> 3;
                        break; // Läts
                    case 2:
                        Playsample(SAMP_FLESH2, Opt->sound.Soundvolume*2, 128);
                        Md->Pl[i2].Mx += Md->Bul[i].Mx >> 4; // tönäsy
                        Md->Pl[i2].My += Md->Bul[i].My >> 4;
                        break; // Löts
                    case 3:
                        Playsample(SAMP_FLESH3, Opt->sound.Soundvolume*2, 128);
                        Md->Pl[i2].Mx += Md->Bul[i].Mx >> 5; // pikku tönäsy
                        Md->Pl[i2].My += Md->Bul[i].My >> 5;
                        break;
                    };

                if (Hit) Md->Bul[i].Live = false; // jos osunut niin luoti varmaan katoaa
            } //      for (int i2 = 0; i2 < Opt->Players; i2++)

    if (Md->Bul[i].Life < 1998) // ettei vaan osu omaan sormeen
        for (int i2 = 0; i2 < Opt->Bots; i2++) if (Md->Bot[i2].Live)
            {
                Hit = Hit_bot(i2, X, Y);
                int r; // apumuuttuja suunnan määrittelylle
                if (Hit > 0)
                    for (int Count = 0; Count < 12; Count++) // verta
                    {
                        r = Rand()%255;
                        Shoot(BUL_BLOOD, Md->Bot[i2].X, Md->Bot[i2].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000, 1);
                    } // for (int Count = 0; Count < 12; Count++)

                if (Hit > 0)
                {
                    Addexp(2, Md->Bul[i].X>>16, Md->Bul[i].Y>>16, 0, Md->Bul[i].Owner,  Md->Bul[i].Ownertype);
                } // if (Hit > 0)

                if (Md->Bot[i2].Live) // Elossa vielä?? Mitä?
                    switch(Hit)
                    {   // Lits
                    case 1:
                        Playsample(SAMP_FLESH1, Opt->sound.Soundvolume*2, 128);
                        Md->Bot[i2].Mx += Md->Bul[i].Mx >> 3; // iso tönäsy
                        Md->Bot[i2].My += Md->Bul[i].My >> 3;
                        break; // Läts
                    case 2:
                        Playsample(SAMP_FLESH2, Opt->sound.Soundvolume*2, 128);
                        Md->Bot[i2].Mx += Md->Bul[i].Mx >> 4; // tönäsy
                        Md->Bot[i2].My += Md->Bul[i].My >> 4;
                        break; // Löts
                    case 3:
                        Playsample(SAMP_FLESH3, Opt->sound.Soundvolume*2, 128);
                        Md->Bot[i2].Mx += Md->Bul[i].Mx >> 5; // pikku tönäsy
                        Md->Bot[i2].My += Md->Bul[i].My >> 5;
                        break;
                    };
                if (Hit) Md->Bul[i].Live = false; // jos osunut niin luoti varmaan katoaa
            } //      for (int i2 = 0; i2 < Opt->Players; i2++)

    Md->Bul[i].My -= Gravity;
} // Update_plasma
void Update_plasma2(int i, int X, int Y)
{
    int apu = getpixel(Md->Map, X, Y); // tarvitaan törmäyscheckkiin
    Md->Bul[i].My -= Gravity;

    if (apu>0) // jos ei ole kalliossa
    {
        Md->Bul[i].Live = false;
    } //     if (apu > 0)
    Md->Bul[i].Dat[3]++;
    if (Md->Bul[i].Dat[2]==0)
    {
        Md->Bul[i].Dat[2]=1;
        Md->Bul[i].Dat[3]=64;
    } // if (Md->Bul[i].Dat[2]==0)
    if (Md->Bul[i].Dat[3]>=78) Md->Bul[i].Live = false;
} // void Update_plasma2(int i, int X, int Y)
void Update_plasma3(int i, int X, int Y)
{   Md->Bul[i].Life = 1000;
    Md->Bul[i].My -= Gravity;
    if (Md->Bul[i].Dat[0] == ITEM_LASERCANNON)
    {
        circlefill(Md->Map, X, Y, 2, 0);
        if (Opt->Parallax)
        {
            circlefill(Parallax, X>>1, Y>>1, 1, 0);
        } // if (Opt->Parallax)
    } // if (Md->Bul[i].Dat[0] == 0)
    Md->Bul[i].Dat[3]++;
    if (Md->Bul[i].Dat[2]!=1)
    {
        Md->Bul[i].Dat[2]=1;
        Md->Bul[i].Dat[3]=32;
    } // if (Md->Bul[i].Dat[2]==0)
    if (Md->Bul[i].Dat[3]>=44) Md->Bul[i].Live = false;
} // void Update_plasma2(int i, int X, int Y)

int Dirvali(int S, int Ms)
{
    if (Ms < S) return(S-Ms);
    if (Ms > S) return(S+(255-Ms));


} // Dirvali
void Rotateangle(int *p, int i)
{
    if (Dirvali(*p>>16, i>>16) < 128)
    {
        if ((*p)>>16 != (i)>>16) *p  = (*p) - (1<<16);
        if (*p < 0) *p= 255<<16;
    }
    else
    {
        if ((*p)>>16 != (i)>>16) *p  = (*p) +(1<<16);
        if (*p >  255<<16) p = 0;
    }
} // Rotateship
void Update_rocket(int i, int X,int Y)
{
    if (Md->Bul[i].Dat[0] == ITEM_HMISLAUNCHER)
    {
        bool Found = false;
        if (Md->Bul[i].Ownertype == 0)
            for (int i2 = 0; i2 < Opt->Bots; i2++) if (Md->Bot[i2].Live)
                    if (Quickdist(X, Y, Md->Bot[i2].X>>16, Md->Bot[i2].Y>>16) < MAX_HMISSILE_SEARCH_RANGE)
                        if (Distance(X, Y, Md->Bot[i2].X>>16, Md->Bot[i2].Y>>16) < MAX_HMISSILE_SEARCH_RANGE)
                        {
                            int Dir = Direction(X, Y, Md->Bot[i2].X>>16, Md->Bot[i2].Y>>16);
                            Found = true;
                            Rotateangle(&Md->Bul[i].Dir, Dir);
                            Md->Bul[i].Mx = int(fcos(Md->Bul[i].Dir)*1.2);
                            Md->Bul[i].My = int(fsin(Md->Bul[i].Dir)*1.2);
                        } //      for (int i2 = 0; i2 < Opt->Players; i2++) if (Md->Bot[i2].Live)
        if (Found == false)
            for (int i2 = 0; i2 < Opt->Players; i2++) if (Md->Pl[i2].Live) if (i2 != Md->Bul[i].Owner)
                        if (Quickdist(X, Y, Md->Pl[i2].X>>16, Md->Pl[i2].Y>>16) < MAX_HMISSILE_SEARCH_RANGE)
                            if (Distance(X, Y, Md->Pl[i2].X>>16, Md->Pl[i2].Y>>16) < MAX_HMISSILE_SEARCH_RANGE)
                            {
                                int Dir = Direction(X, Y, Md->Pl[i2].X>>16, Md->Pl[i2].Y>>16);
                                Found = true;
                                Rotateangle(&Md->Bul[i].Dir, Dir);
                                Md->Bul[i].Mx = int(fcos(Md->Bul[i].Dir)*1.2);
                                Md->Bul[i].My = int(fsin(Md->Bul[i].Dir)*1.2);
                            } //      for (int i2 = 0; i2 < Opt->Players; i2++) if (Md->Pl[i2].Live)

        if (!Found) Md->Bul[i].Dir = Direction(Md->Bul[i].Ox, Md->Bul[i].Oy, Md->Bul[i].X, Md->Bul[i].Y);
    } // Hmislauncher
    int Exp = (Md->Bul[i].Dat[0] == ITEM_BAZOOKA) ? 6 : 3;

    for (int i2 = 0; i2 < Maxbuildings; i2++) if (Md->Bld[i2].Live)
            if (X >= (Md->Bld[i2].X BitR) )
                if (X <= (Md->Bld[i2].X BitR) + (((BITMAP*) Dat[Bldpic[Md->Bld[i2].Type]+Md->Bld[i2].Pic].dat)->w))
                    if (Y >= (Md->Bld[i2].Y BitR) )
                        if (Y <= (Md->Bld[i2].Y BitR) + (((BITMAP*) Dat[Bldpic[Md->Bld[i2].Type]+Md->Bld[i2].Pic].dat)->h))
                        {
                            for (int i3 = 0; i3 < Exp; i3++)
                                Addexp(1, (Md->Bul[i].X>>16)-40+Rand()%80, (Md->Bul[i].Y>>16)-40+Rand()%80, 2, Md->Bul[i].Owner, Md->Bul[i].Ownertype);
                            Md->Bul[i].Live = false; // nirri pois
                        } // for (int i2 = 0; i2 < Maxbuildings; i2++) if (Md->Bld[i2].Live)


    if (Md->Bul[i].Life < 1985) // ettei vaan osu omaan sormeen
        for (int i2 = 0; i2 < Opt->Players; i2++) if (Md->Pl[i2].Live)
            {
                if (X >= (Md->Pl[i2].X BitR) - 4)
                    if (X <= (Md->Pl[i2].X BitR) + 4)
                        if (Y >= (Md->Pl[i2].Y BitR) - 6)
                            if (Y <= (Md->Pl[i2].Y BitR) + 6)
                            {
                                Yummy_explosion(i2, Md->Bul[i].Owner, Md->Bul[i].Ownertype);
                                for (int i3= 0; i3 < Exp; i3++)
                                    Addexp(1, (Md->Bul[i].X>>16)-40+Rand()%80, (Md->Bul[i].Y>>16)-40+Rand()%80, 2, Md->Bul[i].Owner,  Md->Bul[i].Ownertype);
                                Md->Bul[i].Live = false; // nirri pois
                            }
            }
    if (Md->Bul[i].Life < 1985) // ettei vaan osu omaan sormeen
        for (int i2 = 0; i2 < Opt->Bots; i2++) if (Md->Bot[i2].Live)
            {
                if (X >= (Md->Bot[i2].X BitR) - 4)
                    if (X <= (Md->Bot[i2].X BitR) + 4)
                        if (Y >= (Md->Bot[i2].Y BitR) - 6)
                            if (Y <= (Md->Bot[i2].Y BitR) + 6)
                            {
                                Yummy_bot_explosion(i2, Md->Bul[i].Owner, Md->Bul[i].Ownertype);
                                for (int i3= 0; i3 < Exp; i3++)
                                    Addexp(1, (Md->Bul[i].X>>16)-40+Rand()%80, (Md->Bul[i].Y>>16)-40+Rand()%80, 2, Md->Bul[i].Owner,  Md->Bul[i].Ownertype);
                                Md->Bul[i].Live = false; // nirri pois
                            }
            }

    int r = itofix(Rand()%255);
    Shoot(BUL_SMOKE, Md->Bul[i].X - 10000 + Rand()%20000, Md->Bul[i].Y - 10000 + Rand()%20000, (fcos(r)/50) - 1000 + Rand()%2000,(fsin(r)/50) - 1000 + Rand()%2000);
    if ((getpixel(Md->Map, X, Y)>0)) // jos jää johonkin kiinni
    {
        for (int i2 = 0; i2 < Exp; i2++)
            Addexp(1, (Md->Bul[i].X>>16)-40+Rand()%80, (Md->Bul[i].Y>>16)-40+Rand()%80, 2, Md->Bul[i].Owner, Md->Bul[i].Ownertype);
        Md->Bul[i].Live = false; // nirri pois
    } // if (getpixel(Md->Map, X, Y))
} // void Update_rocket(int i, int X,int Y)
void Update_bullets()
{
    int X, Y ,Speed=1; // Abumuuttujat
    for (int i = 0; i < Maxbullets; i++) // kaikille
        if (Md->Bul[i].Live) // jos elossa
        {
            Speed = 1;
            if (Md->Bul[i].Dat[0] == ITEM_SNIPERRIFLE) Speed = 5;
            if (Md->Bul[i].Dat[0] == ITEM_LASERCANNON) Speed = 25;
            for (int Speeder2 = 0; Speeder2 < Speed; Speeder2++)
            {
                // vanhat koordit
                Md->Bul[i].Ox = Md->Bul[i].X;
                Md->Bul[i].Oy = Md->Bul[i].Y;

                // plus nopeusvektorit
                Md->Bul[i].X  += Md->Bul[i].Mx;
                Md->Bul[i].Y  += Md->Bul[i].My;

                // desimaaliosa pois (oikealle 16 bittiä)
                X = Md->Bul[i].X BitR;
                Y = Md->Bul[i].Y BitR;

                // painovoima
                Md->Bul[i].My += Gravity;

                // elämän lyhennys
                if (Md->Bul[i].X < 0) Md->Bul[i].Life = 0;
                if (Md->Bul[i].Y < 0) Md->Bul[i].Life = 0;
                if (Md->Bul[i].X > Lev->Mapsizex<<16) Md->Bul[i].Life = 0;
                if (Md->Bul[i].Y > Lev->Mapsizey<<16) Md->Bul[i].Life = 0;
                if (Md->Bul[i].Life) Md->Bul[i].Life--;
                else
                {
                    Md->Bul[i].Live = false;
                    if (Md->Bul[i].Type == BUL_GRENADE)
                    {
                        Addexp(1, Md->Bul[i].X>>16, Md->Bul[i].Y>>16, 1, Md->Bul[i].Owner, Md->Bul[i].Ownertype);
                        // Sirpaleita
                        for (int i3 = 0; i3 < 10; i3++)
                        {
                            int r = itofix(rand()%255)+rand()%65535;
                            int p = rand()%400;
                            Shoot(BUL_SHRAPNEL, Md->Bul[i].X+itofix(-3+rand()%7), Md->Bul[i].Y+itofix(-3+rand()%7), fcos(r)*p/100, fsin(r)*p/100, 0, Md->Bul[i].Owner, Md->Bul[i].Ownertype, Md->Bul[i].Dir);
                        } // for (int i3 = 0; i3 < 10; i3++)
                    } // if (Md->Bul[i].Type == BUL_GRENADE)
                } // Live == false

                if (Md->Bul[i].Live) // Jos vieläkin elossa?
                {
                    switch(Md->Bul[i].Type) // minkä tyyppinen
                    {
                    case BUL_PISTOL:
                        Update_pistol(i, X, Y);
                        break;
                    case BUL_SHOTGUNSHELL:
                        Update_shotgunshell(i, X, Y);
                        break;
                    case BUL_DIRT:
                        Update_dirt(i, X, Y);
                        break;
                    case BUL_BLOOD:
                        Update_blood(i, X, Y);
                        break;
                    case BUL_GORE:
                        Update_gore(i, X, Y);
                        break;
                    case BUL_BULLETSHELL:
                        Update_bulletshell(i, X, Y);
                        break;
                    case BUL_SMOKE:
                        Update_smoke(i, X, Y);
                        break;
                    case BUL_GRENADE:
                        Update_grenade(i, X, Y);
                        break;
                    case BUL_ROCKET:
                        Update_rocket(i, X, Y);
                        break;
                    case BUL_PLASMA:
                        Update_plasma(i, X, Y);
                        break;
                    case BUL_PLASMA2:
                        Update_plasma2(i, X, Y);
                        break;
                    case BUL_PLASMA3:
                        Update_plasma3(i, X, Y);
                        break;
                    case BUL_LAVABOMB:
                        Update_lavabomb(i, X, Y);
                        break;
                    case BUL_SHRAPNEL:
                        Update_shrapnel(i, X, Y);
                        break;
                    case BUL_BIGLASER:
                        Update_biglaser(i, X, Y);
                        break;
                    }; // switch(Md->Bul[i].Type)
                } // Speeder2
            } // (Md->Bul[i].Live)
        } //    for (int i = 0; i < Maxbullets; i++)

} // Update_bullets
void Emptypic(BITMAP * bmp, int X, int Y, int type, char dirt)
{
    int apu = 0;
    for (int y = 0; y < bmp->h; y++)
        for (int x = 0; x < bmp->w; x++) if (bmp->line[y][x]) if (X+x < Md->Map->w)
                    if (Y+y < Md->Map->h) if (Y+y >= 0) if (X+x >= 0)
                            {
                                apu = Md->Map->line[Y+y][X+x];
                                if (type == 0)
                                {
                                    if (((apu >= 121) && (apu <= 143)) || (apu == 25)) // kallioon osuminen
                                        {  } else // if ((apu >= 16) && (apu <= 31)) // kallioon osuminen
                                    {
                                        if (Opt->Parallax)
                                            Parallax->line[(Y+y)>>1][(X+x)>>1] = 0;
                                        Md->Map->line[Y+y][X+x] = 0;
                                    }
                                    if (dirt)
                                        if (Rand()%4==0)  Shoot(BUL_DIRT, (X+x<<16)+(itofix(-1+Rand()%3)), (y+Y<<16)+(itofix(-1+Rand()%3)), fcos(itofix(Suunta(160+Rand()%65)))>>2, fsin(itofix(Suunta(160+Rand()%65)))>>2);

                                }   // type == 0
                                if (type == 1)
                                {
                                    if ((apu <= 121) || (apu >= 143))
                                    {
                                        if (Opt->Parallax)
                                            Parallax->line[(Y+y)>>1][(X+x)>>1] = 0;
                                        Md->Map->line[Y+y][X+x] = 0;
                                        if (dirt)
                                            if (Rand()%4==0)  Shoot(BUL_DIRT, (X+x<<16)+(itofix(-1+Rand()%3)), (y+Y<<16)+(itofix(-1+Rand()%3)), fcos(itofix(Suunta(160+Rand()%65)))>>2, fsin(itofix(Suunta(160+Rand()%65)))>>2);
                                    }
                                    if (((apu > 121) && (apu <= 130)) || (apu == 25))
                                        if (Rand()%4==0)
                                        {
                                            if (Opt->Parallax)
                                                Parallax->line[(Y+y)>>1][(X+x)>>1] = 0;
                                            Md->Map->line[Y+y][X+x] = 0;
                                        }
                                }
                                if (type == 2)
                                {
                                    if ((apu <= 121) || (apu >= 143))
                                    {
                                        if (Opt->Parallax)
                                            Parallax->line[(Y+y)>>1][(X+x)>>1] = 0;
                                        Md->Map->line[Y+y][X+x] = 0;
                                        if (dirt)
                                            if (Rand()%4==0)  Shoot(BUL_DIRT, (X+x<<16)+(itofix(-1+Rand()%3)), (y+Y<<16)+(itofix(-1+Rand()%3)), fcos(itofix(Suunta(160+Rand()%65)))>>2, fsin(itofix(Suunta(160+Rand()%65)))>>2);
                                    }
                                    if (((apu > 121) && (apu < 143)) || (apu == 25))
                                        if (Rand()%4==0)
                                        {
                                            if (Opt->Parallax)
                                                Parallax->line[(Y+y)>>1][(X+x)>>1] = 0;
                                            Md->Map->line[Y+y][X+x] = 0;
                                        }
                                }
                            } // for
} // void Emptypic(BITMAP * bmp, int x, int y, int type)
int Sgn(long a)
{
    if (a == 0) return(0);
    if (a < 0) return(-1);
    if (a > 0) return(+1);
}
bool Shockwave(int X1, int Y1, int X2, int Y2)
{
    int abab;

    bool Found = true;
    double u,s,v,d1x,d1y,d2x,d2y,m,n;
    int i;
    u   = X2 - X1;
    v   = Y2 - Y1;
    d1x = Sgn(int(u));
    d1y = Sgn(int(v));
    d2x = Sgn(int(u));
    d2y = 0;
    m   = fabs(u);
    n   = fabs(v);
    if (!(m>n))
    {
        d2x = 0;
        d2y = Sgn(int(v));
        m = fabs(v);
        n = fabs(u);
    } // if
    s = m / 2;
    for (i = 0; i <= m; i++)
    {
        if (getpixel(Md->Map, X1, Y1) > 0) {
            abab++;
            if (abab > 6) {
                Found = false;
                return(Found);
            }
        }
        else abab = 0;

        s = s + n;
        if (!(s<m))
        {
            s = s - m;
            X1 = int(X1 + d1x);
            Y1 = int(Y1 + d1y);
        } else
        {
            X1 = int(X1 + d2x);
            Y1 = int(Y1 + d2y);
        }
    }
    return(Found);
}
bool Strictshockwave(int X1, int Y1, int X2, int Y2)
{
    int abab=10;

    bool Found = true;
    double u,s,v,d1x,d1y,d2x,d2y,m,n;
    int i;
    u   = X2 - X1;
    v   = Y2 - Y1;
    d1x = Sgn(int(u));
    d1y = Sgn(int(v));
    d2x = Sgn(int(u));
    d2y = 0;
    m   = fabs(u);
    n   = fabs(v);
    if (!(m>n))
    {
        d2x = 0;
        d2y = Sgn(int(v));
        m = fabs(v);
        n = fabs(u);
    } // if
    s = m / 2;
    for (i = 0; i <= m; i++)
    {
        if (abab) abab--;
        else if (getpixel(Md->Map, X1, Y1) > 0) {
            return false;
        }

        s = s + n;
        if (!(s<m))
        {
            s = s - m;
            X1 = int(X1 + d1x);
            Y1 = int(Y1 + d1y);
        } else
        {
            X1 = int(X1 + d2x);
            Y1 = int(Y1 + d2y);
        }
    }
    return(Found);
}
void Randomplasmahit(int i, int killer, char killertype)
{
    int Hit = 1+Rand()%3; // oZUMAkohta
    if (Hit > 0)
    {
        // jos vielä ei oo kuollut
        if (Md->Pl[i].Damage[Hit-1] < Md->Pl[i].Killdamage[Hit-1])
            Md->Pl[i].Damage[Hit-1]+=3;
        // jos kuolee yleisestio...
        if ((Md->Pl[i].Damage[0]) + (Md->Pl[i].Damage[1]) + (Md->Pl[i].Damage[2]) >= Md->Pl[i].Totaldamage)
        {
            Kill_player(i, ITEM_PLASMAPISTOL, killer, killertype);
        } //                 if (Md->Pl[i].Damage[0] + Md->Pl[i].Damage[1] + Md->Pl[i].Damage[2] >= Md->Pl[i].Totaldamage)
        // tai joku ruumiinosa pettää
        if (Md->Pl[i].Damage[Hit-1] >= Md->Pl[i].Killdamage[Hit-1]) if (Md->Pl[i].Live)
            {
                Kill_player(i, ITEM_PLASMAPISTOL, killer, killertype);
            } // if (Md->Pl[i].Damage[Hit-1]>2)
    } // if (Hit > 0)
} // Randomlavahit
void Randomplasmahit_bot(int i, int killer, char killertype)
{
    int Hit = 1+Rand()%3; // oZUMAkohta
    if (Hit > 0)
    {
        // jos vielä ei oo kuollut
        if (Md->Bot[i].Damage[Hit-1] < Md->Bot[i].Killdamage[Hit-1])
            Md->Bot[i].Damage[Hit-1]+=3;
        // jos kuolee yleisestio...
        if ((Md->Bot[i].Damage[0]) + (Md->Bot[i].Damage[1]) + (Md->Bot[i].Damage[2]) >= Md->Bot[i].Totaldamage)
        {
            Kill_bot(i, ITEM_PLASMAPISTOL, killer, killertype);
        } //                 if (Md->Bot[i].Damage[0] + Md->Bot[i].Damage[1] + Md->Bot[i].Damage[2] >= Md->Bot[i].Totaldamage)
        // tai joku ruumiinosa pettää
        if (Md->Bot[i].Damage[Hit-1] >= Md->Bot[i].Killdamage[Hit-1]) if (Md->Bot[i].Live)
            {
                Kill_bot(i, ITEM_PLASMAPISTOL, killer, killertype);
            } // if (Md->Bot[i].Damage[Hit-1]>2)
    } // if (Hit > 0)
} // Randomlavahit
void Randomexphit(int i, int killer, char killertype)
{
    int Hit = 1+Rand()%3; // oZUMAkohta
    if (Hit > 0)
    {
        // jos vielä ei oo kuollut
        if (Md->Pl[i].Damage[Hit-1] < Md->Pl[i].Killdamage[Hit-1])
            Md->Pl[i].Damage[Hit-1]++;
        // jos kuolee yleisestio...
        if ((Md->Pl[i].Damage[0]) + (Md->Pl[i].Damage[1]) + (Md->Pl[i].Damage[2]) >= Md->Pl[i].Totaldamage)
        {
            Explode_player(i, killer, killertype);
        } //                 if (Md->Pl[i].Damage[0] + Md->Pl[i].Damage[1] + Md->Pl[i].Damage[2] >= Md->Pl[i].Totaldamage)
        // tai joku ruumiinosa pettää
        if (Md->Pl[i].Damage[Hit-1] >= Md->Pl[i].Killdamage[Hit-1]) if (Md->Pl[i].Live)
            {
                Explode_player(i, killer, killertype);
            } // if (Md->Pl[i].Damage[Hit-1]>2)
    } // if (Hit > 0)
} // Randomlavahit
void Bot_randomexphit(int i, int killer, char killertype)
{
    int Hit = 1+Rand()%3; // oZUMAkohta
    if (Hit > 0)
    {
        // jos vielä ei oo kuollut
        if (Md->Bot[i].Damage[Hit-1] < Md->Bot[i].Killdamage[Hit-1])
            Md->Bot[i].Damage[Hit-1]++;
        // jos kuolee yleisestio...
        if ((Md->Bot[i].Damage[0]) + (Md->Bot[i].Damage[1]) + (Md->Bot[i].Damage[2]) >= Md->Bot[i].Totaldamage)
        {
            Explode_bot(i, killer, killertype);
        } //                 if (Md->Bot[i].Damage[0] + Md->Bot[i].Damage[1] + Md->Bot[i].Damage[2] >= Md->Bot[i].Totaldamage)
        // tai joku ruumiinosa pettää
        if (Md->Bot[i].Damage[Hit-1] >= Md->Bot[i].Killdamage[Hit-1]) if (Md->Bot[i].Live)
            {
                Explode_bot(i, killer, killertype);
            } // if (Md->Bot[i].Damage[Hit-1]>2)
    } // if (Hit > 0)
} // Randomlavahit

void Update_explosions()
{
    for (int i = 0; i < Maxexp; i++) // Näihin sitten tulee vahingon aiheutus
        if (Md->Exp[i].Live)            // sekä shockwave
        {
            if (Md->Exp[i].Count == 0) if (Md->Exp[i].Type != 6)
                {
                    if (Md->Exp[i].Type == 2)  if (Md->Exp[i].Onlyonce ==false)
                        {
                            Md->Exp[i].Onlyonce = true;
                            for (int p = 0; p < Opt->Players; p++)
                                if (Md->Pl[p].Live) if (Quickdist(Md->Exp[i].X, Md->Exp[i].Y, Md->Pl[p].X>>16, Md->Pl[p].Y>>16)<60)
                                    {
                                        int D = Distance(Md->Exp[i].X, Md->Exp[i].Y, Md->Pl[p].X>>16, Md->Pl[p].Y>>16);
                                        if (D < 30) Randomplasmahit(p, Md->Exp[i].Owner, Md->Exp[i].Ownertype);
                                    } //          for (int p = 0; p < Opt->Players; p++)          if (Md->Pl[p].Live) if (Shockwave(Md->Exp[i].X, Md->Exp[i].Y, Md->Pl[p].X>>16, Md->Pl[p].Y>>16))
                            for (int p = 0; p < Opt->Bots; p++)
                                if (Md->Bot[p].Live) if (Quickdist(Md->Exp[i].X, Md->Exp[i].Y, Md->Bot[p].X>>16, Md->Bot[p].Y>>16)<60)
                                    {
                                        int D = Distance(Md->Exp[i].X, Md->Exp[i].Y, Md->Bot[p].X>>16, Md->Bot[p].Y>>16);
                                        if (D < 30) Randomplasmahit_bot(p, Md->Exp[i].Owner, Md->Exp[i].Ownertype);
                                    } //          for (int p = 0; p < Opt->Players; p++)          if (Md->Pl[p].Live) if (Shockwave(Md->Exp[i].X, Md->Exp[i].Y, Md->Pl[p].X>>16, Md->Pl[p].Y>>16))
                            for (int p = 0; p < Maxbuildings; p++)
                                if (Md->Bld[p].Live) if (Quickdist(Md->Exp[i].X, Md->Exp[i].Y, Md->Bld[p].X>>16, Md->Bld[p].Y>>16)<60)
                                    {
                                        int D = Distance(Md->Exp[i].X, Md->Exp[i].Y, Md->Bld[p].X>>16, Md->Bld[p].Y>>16);
                                        if (D < 30) Md->Bld[p].Energy-=25+rand()%25;
                                        if (Md->Bld[p].Energy <= 0)
                                            Destroy_building(p);
                                    } // for (int p = 0; p < Maxbuildings; p++)
                        } // if (Md->Exp[i].Type == 2)
                    if (Expsample == false) if (Md->Exp[i].Sampled==false)
                        {
                            if (Md->Exp[i].Type != 4)
                                Playsample(SAMP_EXP1, Opt->sound.Soundvolume, 128, 0);
                            else
                                Playsample(SAMP_EXP1, Opt->sound.Soundvolume>>2, 128, 0);


                            Md->Exp[i].Sampled = true;
                            Expsample = true;
                        } //          if (Md->Exp[i].Sampled == false)

                    if (Md->Exp[i].Type != 2)
                        for (int p = 0; p < Opt->Players; p++)
                            if (Md->Pl[p].Live) if (Quickdist(Md->Exp[i].X, Md->Exp[i].Y, Md->Pl[p].X>>16, Md->Pl[p].Y>>16)<120)
                                    if (Shockwave(Md->Exp[i].X, Md->Exp[i].Y, Md->Pl[p].X>>16, Md->Pl[p].Y>>16))
                                    {
                                        int D = Distance(Md->Exp[i].X, Md->Exp[i].Y, Md->Pl[p].X>>16, Md->Pl[p].Y>>16);
                                        if (D < ((Md->Exp[i].Type != 4) ? 80 : 20))
                                        {
                                            int Dir = Direction(Md->Exp[i].X, Md->Exp[i].Y, Md->Pl[p].X>>16, Md->Pl[p].Y>>16);
                                            if (Md->Exp[i].Type != 4)
                                            {
                                                Md->Pl[p].Mx += fcos(Dir)/2;
                                                Md->Pl[p].My += fsin(Dir)/2;
                                            } // if (Md->Exp[i].Type != 4)
                                            D = (((Md->Exp[i].Type != 4) ? 80 : 20)-D) / 10;
                                            for (int i2 = 0; i2 < D; i2++)
                                                Randomexphit(p, Md->Exp[i].Owner, Md->Exp[i].Ownertype);
                                        } // if (D < 80)

                                    } // for (int p = 0; p < Opt->Players; p++) if (Pl[p].Live) if (Shockwave(Md->Exp[i].X, Md->Exp[i].Y, Pl[p].X>>16, Pl[p].Y>>16))
                    if (Md->Exp[i].Type != 2)
                        for (int p = 0; p < Opt->Bots; p++)
                            if (Md->Bot[p].Live) if (Quickdist(Md->Exp[i].X, Md->Exp[i].Y, Md->Bot[p].X>>16, Md->Bot[p].Y>>16)<120)
                                    if (Shockwave(Md->Exp[i].X, Md->Exp[i].Y, Md->Bot[p].X>>16, Md->Bot[p].Y>>16))
                                    {
                                        int D = Distance(Md->Exp[i].X, Md->Exp[i].Y, Md->Bot[p].X>>16, Md->Bot[p].Y>>16);
                                        if (D < ((Md->Exp[i].Type != 4) ? 80 : 20))
                                        {
                                            int Dir = Direction(Md->Exp[i].X, Md->Exp[i].Y, Md->Bot[p].X>>16, Md->Bot[p].Y>>16);
                                            if (Md->Exp[i].Type != 4)
                                            {
                                                Md->Bot[p].Mx += fcos(Dir)/2;
                                                Md->Bot[p].My += fsin(Dir)/2;
                                            } // if (Md->Exp[i].Type != 4)
                                            D = (((Md->Exp[i].Type != 4) ? 80 : 20)-D) / 10;
                                            for (int i2 = 0; i2 < D; i2++)
                                                Bot_randomexphit(p, Md->Exp[i].Owner, Md->Exp[i].Ownertype);
                                        } // if (D < 80)
                                    } // for (int p = 0; p < Opt->Bots; p++) if (Bot[p].Live) if (Shockwave(Md->Exp[i].X, Md->Exp[i].Y, Bot[p].X>>16, Bot[p].Y>>16))
                    if (Md->Exp[i].Type != 2)
                        for (int p = 0; p < Maxbuildings; p++)
                            if (Md->Bld[p].Live) if (Quickdist(Md->Exp[i].X, Md->Exp[i].Y, Md->Bld[p].X>>16, Md->Bld[p].Y>>16)<60)
                                    if (Shockwave(Md->Exp[i].X, Md->Exp[i].Y, Md->Bld[p].X>>16, Md->Bld[p].Y>>16))
                                    {
                                        int D = Distance(Md->Exp[i].X, Md->Exp[i].Y, Md->Bld[p].X>>16, Md->Bld[p].Y>>16);
                                        if (D < ((Md->Exp[i].Type != 4) ? 80 : 20))
                                        {
                                            int Dir = Direction(Md->Exp[i].X, Md->Exp[i].Y, Md->Bld[p].X>>16, Md->Bld[p].Y>>16);
                                            if (Md->Exp[i].Type != 4)
                                            {
                                                Md->Bld[p].Mx += fcos(Dir)/8;
                                                Md->Bld[p].My += fsin(Dir)/8;
                                            } // if (Md->Exp[i].Type != 4)
                                            Md->Bld[p].Energy-=(D>>2);
                                            if (Md->Bld[p].Energy <= 0)
                                                Destroy_building(p);
                                        } // if (D < 80)
                                    } // for (int p = 0; p < Maxbuidlings; p++) if (Bot[p].Live) if (Shockwave(Md->Exp[i].X, Md->Exp[i].Y, Bot[p].X>>16, Bot[p].Y>>16))
                } // if (Md->Exp[i].Count == 0)

            Md->Exp[i].Count++;


        } //    for (int i = 0; i < Maxexp; i++)
} // void Update_explosions()
void Update_lava()
{
    Lavacount = 0;
    int x, y,r ,apu; // x, y, selvät r = suunta apu = apu
    // aih.... ei oikein optimoitu... nollataan burn taulukko
    memset(Burn, 0, (Lev->Mapsizex>>2)*(Lev->Mapsizey>>2));

    for (int i = 0; i < Maxlava; i++) // joka laavalle
        if (Md->Lava[i].Live) // jos elossa
        {
            Lavacount++; // lavacounteri
            if (Md->Lava[i].Life) // elämän lyhennys
                Md->Lava[i].Life--;

            if(Md->Lava[i].Life<=0)
            {
                Md->Lava[i].Live = false;
            } // if(Md->Lava[i].Life<=0)

            Md->Lava[i].My += (Gravity*20); // 20 * painovoima !!!

            // koordit + nopeusvektorit
            Md->Lava[i].X = Md->Lava[i].X + Md->Lava[i].Mx;
            Md->Lava[i].Y = Md->Lava[i].Y + Md->Lava[i].My;

            // desimaaliosa pois
            x = Md->Lava[i].X BitR;
            y = Md->Lava[i].Y BitR;
            // clippaukset
            if (x < 1) {
                x = 0;
                Md->Lava[i].Live = false;
            }
            if (y < 1) {
                x = 0;
                Md->Lava[i].Live = false;
            }
            if (x > Lev->Mapsizex-2) {
                x= Lev->Mapsizex-2;
                Md->Lava[i].Live = false;
            }
            if (y > Lev->Mapsizey-2) {
                y = Lev->Mapsizey-2;
                Md->Lava[i].Live = false;
            }
            // **********
            if (Md->Lava[i].Live)
            {
                // jos on ilmassa niin ei liiku mihinkään suuntaan
                if (Md->Map->line[y+1][x]>0)
                    if (Md->Map->line[y][x-1]>0)
                        if (Md->Map->line[y][x+1]>0)
                            Md->Lava[i].S = 0;

                // jos maassa
                if (Md->Map->line[y+1][x]>0)
                {

                    Md->Lava[i].My = -(Gravity*20); // painovoima veks

                    if (Md->Lava[i].S == 0) // suunnan vaihto
                        if (Timer%2==0) Md->Lava[i].S = 1;
                        else Md->Lava[i].S = -1;
                    // jos oikealla on "seinä"
                    if (Md->Map->line[y][x-1]>0)
                        Md->Lava[i].S = 1;
                    // tai ruudun reuna
                    if (x == 0) Md->Lava[i].S = 1;

                    if (x < Lev->Mapsizex)
                        if (Md->Map->line[y][x+1]>0)
                            Md->Lava[i].S = -1;
                    if (x == Lev->Mapsizex) Md->Lava[i].S = -1;
                    // nopeusvekille x vähän vauhtia
                    if (Md->Lava[i].S == 1) Md->Lava[i].Mx = 15000+abs(Md->Lava[i].My+1);
                    if (Md->Lava[i].S == -1) Md->Lava[i].Mx = -15000-abs(Md->Lava[i].My+1);
                } // Mapget
                // jos vasemmalla on seinä
                if (Md->Map->line[y][x-1]>0)
                {
                    // X pysäytetään kumoalla nopeusvek x
                    Md->Lava[i].X=Md->Lava[i].X-Md->Lava[i].Mx;
                    // ja nopeusvek x käännetään
                    if (Md->Lava[i].Mx < 0) Md->Lava[i].Mx = (abs(Md->Lava[i].Mx)+1) >>1;
                } // vasemmalla seinä
                // ylhäällä seinä
                if (Md->Map->line[y-1][x]>0)
                {
                    // kumotaan nopeusvek y
                    Md->Lava[i].Y=Md->Lava[i].Y-Md->Lava[i].My;
                    // ja nopeusvek y käännetään
                    if (Md->Lava[i].My < 0) Md->Lava[i].My = abs(Md->Lava[i].My+1) >>1;
                } // yseinä
                // oikealla seinä
                if (Md->Map->line[y][x+1]>0)
                {
                    // nopeusvek X kumotaan
                    Md->Lava[i].X=Md->Lava[i].X-Md->Lava[i].Mx;
                    // ja käännetään
                    if (Md->Lava[i].Mx > 0) Md->Lava[i].Mx = -(Md->Lava[i].Mx-1) >>1;
                }

                // jos on maan sisällä kunnolla
                if (Md->Map->line[y-1][x]>0)
                    if (Md->Map->line[y+1][x]>0)
                        if (Md->Map->line[y][x-1]>0)
                            if (Md->Map->line[y][x+1]>0)
                                Md->Lava[i].Live = false;
                // ****************************

                // jos maan sisällä niin ylöspäin
                if (Md->Map->line[y][x]>0)
                    Md->Lava[i].My -= 5000;
                // jos lähellä on kavereita
                if (Getlava(x, y))
                {
                    // jos vasemmalla vähemmän kavereita kuin oikealla niin vasemmalle
                    if (Getlava(x-4, y)< Getlava(x+4,y)) Md->Lava[i].Mx -= 2750;
                    else if (Getlava(x-4, y)> Getlava(x+4,y)) Md->Lava[i].Mx += 2750;
                    // muuten oikealle
                    // Mielenkiintoinen käänteinen 23 - kertainen painovoima
                    Md->Lava[i].My -= (Gravity*23);
                }
                // puiden palamischeckit
                if (Lavatimer) // n - framea ja check
                {
                    // Tämä tarkistaa onko laavapikselin lähellä puita joita voisi polttaa
                    // jos on niin siihen kohtaa syntyy uusi laavapikseli ja puu tuhoutuu...
                    apu = Md->Map->line[y+1][x];
                    // jos alhaalla on puita(tietynvärisiä pikseleitä)
                    if (((apu >= 64) && (apu <= 79)) || ((apu >= 235) && (apu <= 239)) || (apu == 2) || (apu == 10))
                    {
                        Md->Map->line[y+1][x] = 0;
                        Parallax->line[(y+1)>>1][x>>1] = 0;
                        Addlava(itofix(x), itofix(y+1), 0, 0, 1);
                    } // if (((apu >= 66) && (apu <= 79)) || ((apu >= 235) && (apu <= 239)))
                    apu = Md->Map->line[y-1][x];
                    // jos ylhäällä on puita
                    if (((apu >= 64) && (apu <= 79)) || ((apu >= 235) && (apu <= 239)) || (apu == 2) || (apu == 10))
                    {
                        Md->Map->line[y-1][x] = 0;
                        Parallax->line[(y-1)>>1][x>>1] = 0;
                        Addlava(itofix(x), itofix(y-1), 0, 0, 1);
                    } // if (((apu >= 66) && (apu <= 79)) || ((apu >= 235) && (apu <= 239)))
                    apu = Md->Map->line[y][x+1];
                    // jos oikealla puita
                    if (((apu >= 64) && (apu <= 79)) || ((apu >= 235) && (apu <= 239)) || (apu == 2) || (apu == 10))
                    {
                        Md->Map->line[y][x+1] = 0;
                        Parallax->line[(y)>>1][(x+1)>>1] = 0;
                        Addlava(itofix(x+1), itofix(y), 0, 0, 1);
                    } // if (((apu >= 66) && (apu <= 79)) || ((apu >= 235) && (apu <= 239)))
                    apu = Md->Map->line[y][x-1];
                    // vasemmalla puita
                    if (((apu >= 64) && (apu <= 79)) || ((apu >= 235) && (apu <= 239)) || (apu == 2) || (apu == 10))
                    {
                        Md->Map->line[y][x-1] = 0;
                        Parallax->line[(y)>>1][(x-1)>>1] = 0;
                        Addlava(itofix(x-1), itofix(y), 0, 0, 1);
                    } // if (((apu >= 66) && (apu <= 79)) || ((apu >= 235) && (apu <= 239)))
                    // laava tummuu jos ei ole kavereita lähellä
                    Md->Lava[i].C+=2;
                    if (Getlava(x-4,y)) Md->Lava[i].C-=1;
                    if (Getlava(x+4,y)) Md->Lava[i].C-=1;
                    if (Getlava(x,y-4)) Md->Lava[i].C-=1;
                    if (Getlava(x,y+4)) Md->Lava[i].C-=1;
                    if (Md->Lava[i].C > 39) Md->Lava[i].C = 39;
                    if (Md->Lava[i].C < 32) Md->Lava[i].C = 32;
                    // ********************
                }
                // ja merkataan että tässä X>>2 , Y>>2 rykelmässä on ollut laava
                Putlava(Md->Lava[i].X BitR, Md->Lava[i].Y BitR);
            } // Live
        } // for i < Maxlava
} // Update_lava
int Distance_to_uprock(int x, int y)
{
    int D = 0;
    do
    {
        int apu = getpixel(Md->Map, x, y);
        if ((apu <= 130) || (apu >= 143))
            return D;
        if (apu != 0) return 1000;
        if (D > 60) return D;
        y--;
        D++;
    } while (1 == 2);
} // int Distance_to_uprock(int x, int y)
int Distance_to_downrock(int x, int y)
{
    int D = 0;
    do
    {
        int apu = getpixel(Md->Map, x, y);
        if ((apu <= 130) || (apu >= 143))
            return D;
        if (apu != 0) return 1000;
        if (D > 60) return D;
        y++;
        D++;
    } while (1 == 2);
} // int Distance_to_downrock(int x, int y)
void Update_spire()
{
    Md->Boomtimer++;
    if (Md->Boomtimer>250)   // jos on aika räjähtää
    {
        Md->Boomtimer = 0;
        if (Lavacount < Maxlava) // jos on tarpeeksi laavaa
        {
            int apu=0;
            // chekataan että onko mahdollista purkautua missään...
            bool Possible = false;
            for (int i = 0; i < Maxspires; i++)
                if (Md->Spire[i].Live == true) if (Md->Spire[i].Boom == false) Possible = true;
            // ******* ******* ******* ******* ******* ******* ******* *******
            if (Possible) // on mahdollista!
                do
                {
                    // etsitään niin kauan kunnes löytyy
                    apu = Rand()%Maxspires;
                    if (Md->Spire[apu].Live == true) if (Md->Spire[apu].Boom == false)
                        {
                            Md->Spire[apu].Boom = true; // purkaus päälle
                            Md->Spire[apu].Time = 100 + Rand()%400; // kesto
                            Md->Spire[apu].Multi=1+Rand()%3; // multiplier eli monikertainen?
                            Done = true; // enää ei tarvitse etsiä...
                        } // Löytyi
                } while (Done == false);
            Done = false;
        } // if (Lavacount < Maxlava >> 1)
    } // if (Md->Boomtimer>100)
    // Spirejen päivitys
    for (int i = 0; i < Maxspires; i++)
        if (Md->Spire[i].Live) // elossa
        {
            // jos spire on ilmassa
            if (getpixel(Md->Map, Md->Spire[i].X, Md->Spire[i].Y) == 0)
            {
                bool Found = false;
                if (Distance_to_uprock(Md->Spire[i].X, Md->Spire[i].Y)<50) {
                    Md->Spire[i].Y--;
                    Found=true;
                }
                if (Distance_to_downrock(Md->Spire[i].X, Md->Spire[i].Y)<50) {
                    Md->Spire[i].Y++;
                    Found=true;
                }
                if (Found == false) Md->Spire[i].Live = false;
            }
            // jos spire on purkautumassa
            if (Md->Spire[i].Boom)
            {
                // kestoa vähennetään
                Md->Spire[i].Time--;
                // jos purkaus on loppu
                if (Md->Spire[i].Time < 0) Md->Spire[i].Boom = 0;
                // sitten multiplier * addlava
                for (int count = 0; count < Md->Spire[i].Multi; count++)
                    Addlava(itofix(Md->Spire[i].X-3+(Rand()%6)), itofix(Md->Spire[i].Y-3+Rand()%6), fcos(Suunta(Md->Spire[i].Dir+itofix(-16+Rand()%33)))*(Md->Spire[i].Power/10)-20000+Rand()%40000,fsin(Suunta(Md->Spire[i].Dir+itofix(-16+Rand()%33)))*(Md->Spire[i].Power/10)-20000+Rand()%40000, 1);
            } //       if (Md->Spire[i].Boom)
        } // for (int i = 0; i < Maxspires; i++)
} // Update_spire
int Destroylava(int x1, int y1, int x2, int y2)
{
    int Count = 0;
    for (int i = 0; i < Maxlava; i++) if (Md->Lava[i].Live) // laavapiste elossa
            if (Md->Lava[i].X BitR >= x1)
                if (Md->Lava[i].Y BitR >= y1) // laavapiste on alueen sisällä
                    if (Md->Lava[i].X BitR <= x2)
                        if (Md->Lava[i].Y BitR <= y2)
                        {
                            Count++;
                            Md->Lava[i].Live = false;
                        }
    return(Count);
} // int Destroylava(int x1, int y1, int x2, int y2)
void Update_plate(int i)
{
    Md->Bld[i].My = 0;
    Md->Bld[i].Dat[1] ++;
    if (Md->Bld[i].Dat[1] > 40)
    {
        Md->Bld[i].Dat[1] = 0;
        Md->Bld[i].Dat[0]++;
        if (Md->Bld[i].Dat[0] == 9)
        {
            BITMAP * bmp;
            switch(Md->Bld[i].Type)
            {
            case BLD_PLATE:
                bmp = (BITMAP*) Dat[DATWHITEPLATE].dat;
                break; // BLD_PLATE:
            case BLD_REINFPLATE:
                bmp = (BITMAP*) Dat[DATGRAYPLATE].dat;
                break; // BLD_REINFPLATE:
            }; // switch(Md->Bld[i].Type)
            draw_sprite(Md->Map, bmp, (Md->Bld[i].X>>16)-(Md->Bld[i].Dat[0]>>1), (Md->Bld[i].Y>>16)-(Md->Bld[i].Dat[0]>>1));
            stretch_sprite(Parallax, bmp, ((Md->Bld[i].X>>16)-(Md->Bld[i].Dat[0]>>1))>>1, ((Md->Bld[i].Y>>16)-(Md->Bld[i].Dat[0]>>1))>>1, Md->Bld[i].Dat[0]>>1, Md->Bld[i].Dat[0]>>1);
            Md->Bld[i].Live = false;
        } //      if (Md->Bld[i].Dat[0] == 9)
    } //    if (Md->Bld[i].Dat[1] > 20)
} // void Update_plate(int i)
void Update_bld_lavatrap(int i)
{
    // 160 välein
    Md->Bld[i].Dat[0]++;
    if (Md->Bld[i].Dat[0]>300)
    {
        Md->Bld[i].Dat[0] = 0;
        // jos laavaa on
        if (Getlava((Md->Bld[i].X BitR) + (((BITMAP*) Dat[Bldpic[Md->Bld[i].Type]+Md->Bld[i].Pic].dat)->w>>1), Md->Bld[i].Y BitR))
        {
            int Cashplus = Destroylava((Md->Bld[i].X BitR),
                                       (Md->Bld[i].Y BitR) - 2,
                                       (Md->Bld[i].X BitR) + (((BITMAP*) Dat[Bldpic[Md->Bld[i].Type]+Md->Bld[i].Pic].dat)->w),
                                       (Md->Bld[i].Y BitR) + (((BITMAP*) Dat[Bldpic[Md->Bld[i].Type]+Md->Bld[i].Pic].dat)->h));
            Md->Pl[Md->Bld[i].Owner].Money += Cashplus*3;
        } // if (Getlava(Md->Bld[i].X BitR, Md->Bld[i].Y BitR))
    } // if (Md->Bld[i].Dat[0]>80)
} // Update_bld_lavatrap(int i)
void Update_bld_superlavatrap(int i)
{
    // 40 välein
    Md->Bld[i].Dat[0]++;
    if (Md->Bld[i].Dat[0]>150)
    {
        Md->Bld[i].Dat[0] = 0;
        // jos laavaa on
        if (Getlava((Md->Bld[i].X BitR) + (((BITMAP*) Dat[Bldpic[Md->Bld[i].Type]+Md->Bld[i].Pic].dat)->w>>1), Md->Bld[i].Y BitR))
        {
            int Cashplus = Destroylava((Md->Bld[i].X BitR) - 2,
                                       (Md->Bld[i].Y BitR) - 4,
                                       (Md->Bld[i].X BitR) + (((BITMAP*) Dat[Bldpic[Md->Bld[i].Type]+Md->Bld[i].Pic].dat)->w) + 2,
                                       (Md->Bld[i].Y BitR) + (((BITMAP*) Dat[Bldpic[Md->Bld[i].Type]+Md->Bld[i].Pic].dat)->h));
            Md->Pl[Md->Bld[i].Owner].Money += Cashplus*3;
        } // if (Getlava(Md->Bld[i].X BitR, Md->Bld[i].Y BitR))
    } // if (Md->Bld[i].Dat[0]>40)
} // Update_bld_superlavatrap(int i)
void Update_buildings()
{
    BITMAP * bmp; // apubitmappi
    int x, y; // apuintit
    for (int i = 0; i < Maxbuildings; i++) if (Md->Bld[i].Live)
        {
            // liikutetaan koordeja nopeusvekkien mukaan
            Md->Bld[i].X += Md->Bld[i].Mx;
            Md->Bld[i].Y += Md->Bld[i].My;
            x = Md->Bld[i].X BitR;
            y = Md->Bld[i].Y BitR;

            bmp = (BITMAP*) Dat[Bldpic[Md->Bld[i].Type]+Md->Bld[i].Pic].dat;

            Md->Bld[i].My += Gravity;

            // maahan törmätessä vauhti pysähtyy
            bool One = false;
            if (x+(bmp->w) > Lev->Mapsizex)
            {
                Md->Bld[i].Mx = -(Md->Bld[i].Mx / 2);
                Md->Bld[i].X = Lev->Mapsizex-bmp->w;
            } // if (x+(bmp->w>>1) > Lev->Mapsizex)
            if (x < 0)
            {
                Md->Bld[i].Mx = -(Md->Bld[i].Mx / 2);
                Md->Bld[i].X = 0;
            } // if (x < 0)
            if (getpixel(Md->Map, x+(bmp->w>>1), y+(bmp->h)) > 0)
            {
                Md->Bld[i].My = 0;
                Md->Bld[i].Mx = -(Md->Bld[i].Mx / 2);
                One = true;
            } // if (getpixel(Md->Map, x+(bmp->w>>1), y+(bmp->h)) > 0)
            if (getpixel(Md->Map, x+2, y+(bmp->h)) > 0) if (!One)
                {
                    One = true;
                    Md->Bld[i].Mx = -(Md->Bld[i].Mx / 2);
                } // if (getpixel(Md->Map, x+(bmp->w>>1), y+(bmp->h)) > 0)
            if (getpixel(Md->Map, x+(bmp->w)-2, y+(bmp->h)) > 0) if (!One)
                {
                    Md->Bld[i].Mx = -(Md->Bld[i].Mx / 2);
                } // if (getpixel(Md->Map, x+(bmp->w>>1), y+(bmp->h)) > 0)
            switch(Md->Bld[i].Type)
            {
            case BLD_LAVATRAP:
                Update_bld_lavatrap(i);
                break; // Lavatrap
            case BLD_SUPERLAVATRAP:
                Update_bld_superlavatrap(i);
                break; // Superlavatrap
            case BLD_PLATE:
            case BLD_REINFPLATE:
                Update_plate(i);
                break;
            }; // switch(Md->Bld[i].Type)
        } // for (int i = 0; i < Maxbuildings; i++)
} // Update_buildings()
void Do_game_logic()
{
    Update_players();
    Update_vehicles();
    Update_bots();
    Update_bullets();
    Update_explosions();
    if (Timer % 5==0) Update_lava(); // todella hidasta pakko tinkiä vähän...
    if (Opt->Lava)
        Update_spire();
    Update_buildings();
} // Do_game_logic
void Animate_players()
{
    for (int Count = 0; Count < Opt->Players; Count++) // joka pelaajalle
        if (Md->Pl[Count].Live)
        {
            // animointi päälle
            Md->Pl[Count].Animstopped = false;
            // jos on kävelyanimaatio päällä eikä pelaaja kävele niin pysähtyminen
            // tapahtuu
            if (Md->Pl[Count].Anim == ANI_WALK) if (!Md->Pl[Count].Walking) Md->Pl[Count].Animstopped = true;
            // jos ei ole pysähtynyt niin Countia eteenpäin
            if (Md->Pl[Count].Animstopped == false)
                Md->Pl[Count].Count++;

            if (Md->Pl[Count].Count>Animspeed[Md->Pl[Count].Anim])
            {
                Md->Pl[Count].Count = 0;
                Md->Pl[Count].Picture++; // framea eteenpäin
                // jos meni yli animaation kuvista
                if (Md->Pl[Count].Picture >= Animpicture[Md->Pl[Count].Anim])
                {
                    Md->Pl[Count].Picture = 0;
                    if (Md->Pl[Count].Anim == ANI_PLASMADEATH)
                    {
                        Md->Pl[Count].Live = false;
                    }
                }
            } // if (Md->Pl[Count].Count>Animspeed[Md->Pl[Count].Anim])
        } // for (int Count = 0; Count < Opt->Players; Count++)
} // Animate_players()
void Animate_bots()
{
    for (int Count = 0; Count < Opt->Bots; Count++) // joka pelaajalle
        if (Md->Bot[Count].Live)
        {
            // animointi päälle
            Md->Bot[Count].Animstopped = false;
            // jos on kävelyanimaatio päällä eikä pelaaja kävele niin pysähtyminen
            // tapahtuu
            if (Md->Bot[Count].Anim == ANI_WALK) if (!Md->Bot[Count].Walking) Md->Bot[Count].Animstopped = true;
            // jos ei ole pysähtynyt niin Countia eteenpäin
            if (Md->Bot[Count].Animstopped == false)
                Md->Bot[Count].Count++;

            if (Md->Bot[Count].Count>Animspeed[Md->Bot[Count].Anim])
            {
                Md->Bot[Count].Count = 0;
                Md->Bot[Count].Picture++; // framea eteenpäin
                // jos meni yli animaation kuvista
                if (Md->Bot[Count].Picture >= Animpicture[Md->Bot[Count].Anim])
                {
                    Md->Bot[Count].Picture = 0;
                    if (Md->Bot[Count].Anim == ANI_PLASMADEATH) Md->Bot[Count].Live = false;
                }
            } // if (Md->Bot[Count].Count>Animspeed[Md->Bot[Count].Anim])
        } // for (int Count = 0; Count < Opt->Players; Count++)
} // Animate_bots()
void Animate_buildings()
{
    for (int i = 0; i < Maxbuildings; i++)
        if (Md->Bld[i].Live)
        {
            int *Dat = Bldanim[Md->Bld[i].Type];
            int *Anim = &Dat[2];
            Md->Bld[i].Counter++;
            int Pics = Dat[1];
            int Speed = Dat[0];
            Setclipping(-1);
            if (Md->Bld[i].Counter > Speed)
            {
                Md->Bld[i].Counter = 0;
                Md->Bld[i].Picpos++;
                if (Md->Bld[i].Picpos >= Pics) Md->Bld[i].Picpos = 0;
                Md->Bld[i].Pic = Anim[Md->Bld[i].Picpos];
            } // if (Md->Bld[i].Counter > Speed)
        } //   for (int i = 0; i < Maxbuildings; i++)   if (Md->Bld[i].Live)
} // void Animate_buildings()
void Animate()
{
    Animate_players();
    Animate_bots();
    Animate_buildings();
} // Animate
void Action_setplate(int Screen)
{
    int X = Md->Pl[Screen].Actionx - Md->Pl[Screen].Sx;
    int Y = Md->Pl[Screen].Actiony - Md->Pl[Screen].Sy;
    rect(Scr, Clipx1+X-4, Y-4, Clipx1+X+5, Y+5, 14);
    line (Scr,Clipx1+X-4, Y-4, Clipx1+X+5, Y+5, 14);
    line (Scr,Clipx1+X-4, Y+4, Clipx1+X+5, Y-4, 14);

    if (Distance(Md->Pl[Screen].X>>16, Md->Pl[Screen].Y>>16, Md->Pl[Screen].Actionx, Md->Pl[Screen].Actiony)>100)
        Md->Pl[Screen].Action = 0;
} // void Action_setplate(int Screen)
void Action_sniper(int Screen)
{
    int X = Md->Pl[Screen].Actionx - Md->Pl[Screen].Sx;
    int Y = Md->Pl[Screen].Actiony - Md->Pl[Screen].Sy;
    BITMAP * bmp = (BITMAP*) Dat[DATMENUBUYAIM].dat;
    draw_sprite(Scr, bmp, Clipx1+ X-(bmp->w>>1), Y-(bmp->h>>1));
    Md->Pl[Screen].Sx = Md->Pl[Screen].Actionx - (Clipx>>1);
    Md->Pl[Screen].Sy = Md->Pl[Screen].Actiony - (Clipy>>1);
    if (Md->Pl[Screen].Sx < 0) Md->Pl[Screen].Sx = 0;
    if (Md->Pl[Screen].Sy < 0) Md->Pl[Screen].Sy = 0;
    if (Md->Pl[Screen].Sx > Lev->Mapsizex-Clipx) Md->Pl[Screen].Sx = Lev->Mapsizex-Clipx;
    if (Md->Pl[Screen].Sy > Lev->Mapsizey-Clipy) Md->Pl[Screen].Sy = Lev->Mapsizey-Clipy;
} // void Action_setplate(int Screen)

void Draw_Background(int Screen)
{
    // Pelaajan(Screen) ruudun piirto
    // Clipataan piirtopaikka
    if (Md->Pl[Screen].Sx < 0) Md->Pl[Screen].Sx = 0;
    if (Md->Pl[Screen].Sy < 0) Md->Pl[Screen].Sy = 0;
    if (Md->Pl[Screen].Sx > Lev->Mapsizex-Clipx) Md->Pl[Screen].Sx = Lev->Mapsizex-Clipx;
    if (Md->Pl[Screen].Sy > Lev->Mapsizey-Clipy) Md->Pl[Screen].Sy = Lev->Mapsizey-Clipy;
    // ***********************
    // ja sitten piirretään
    Showmap(Clipx1, Clipy1, Clipx2, Clipy2, Md->Pl[Screen].Sx, Md->Pl[Screen].Sy);
} // Draw_Background(int Screen)
void Draw_ninjarope(int Screen, int Count2)
{
    // X = Ninjaropen x paikka ilman desimaaleja
    // Y = Ninjaropen y paikka ilman desimaaleja
    // Xx = Pelaajan x paikka ilman desimaaleja
    // Yy = Pelaajan y paikka ilman desimaaleja
    // Tx = Ninjaropen bittikartan x piirtokohta
    // Ty = Ninjaropen bittikartan y piirtokohta
    int X = Md->Pl[Count2].Nx BitR, Y = Md->Pl[Count2].Ny BitR;
    int Xx = Md->Pl[Count2].X BitR, Yy = Md->Pl[Count2].Y BitR;
    int Tx = (Md->Pl[Count2].Nx BitR) - (((BITMAP*) Dat[DATNINJAROPE].dat)->w>>1), Ty = (Md->Pl[Count2].Ny BitR) - (((BITMAP*) Dat[DATNINJAROPE].dat)->h>>1);
    // Sitten piirretään pää
    rotate_sprite(Scr, (BITMAP*) Dat[DATNINJAROPE].dat,Clipx1+ Tx - Md->Pl[Screen].Sx, Ty - Md->Pl[Screen].Sy, Md->Pl[Screen].Ninjadir);
    // ja naru
    line(Scr, Clipx1+ X - Md->Pl[Screen].Sx, Y - Md->Pl[Screen].Sy, Clipx1+ Xx - Md->Pl[Screen].Sx, Yy - Md->Pl[Screen].Sy, 6);
} // Draw_ninjarope
void Draw_bot_ninjarope(int Screen, int Count2)
{
    // X = Ninjaropen x paikka ilman desimaaleja
    // Y = Ninjaropen y paikka ilman desimaaleja
    // Xx = Pelaajan x paikka ilman desimaaleja
    // Yy = Pelaajan y paikka ilman desimaaleja
    // Tx = Ninjaropen bittikartan x piirtokohta
    // Ty = Ninjaropen bittikartan y piirtokohta
    int X = Md->Bot[Count2].Nx BitR, Y = Md->Bot[Count2].Ny BitR;
    int Xx = Md->Bot[Count2].X BitR, Yy = Md->Bot[Count2].Y BitR;
    int Tx = (Md->Bot[Count2].Nx BitR) - (((BITMAP*) Dat[DATNINJAROPE].dat)->w>>1), Ty = (Md->Bot[Count2].Ny BitR) - (((BITMAP*) Dat[DATNINJAROPE].dat)->h>>1);
    // Sitten piirretään pää
    rotate_sprite(Scr, (BITMAP*) Dat[DATNINJAROPE].dat,Clipx1+ Tx - Md->Pl[Screen].Sx, Ty - Md->Pl[Screen].Sy, Md->Pl[Screen].Ninjadir);
    // ja naru
    line(Scr, Clipx1+ X - Md->Pl[Screen].Sx, Y - Md->Pl[Screen].Sy, Clipx1+ Xx - Md->Pl[Screen].Sx, Yy - Md->Pl[Screen].Sy, 6);
} // Draw_bot_ninjarope
void Camouflage_bitmap(BITMAP * bmp, BITMAP * from, int p)
{
    int a = 0;
    for (int y = 0; y < bmp->h; y++)
        for (int x = 0; x < bmp->w; x++) if (getpixel(from, x, y) > 0)
                FAST_PUTPIXEL(bmp, x, y, Md->Pl[p].Camocolor[(a++)%2]);
    // putpixel(bmp, x, y, Md->Pl[p].Camocolor[(a++)%2]);
} // void Camouflage_bitmap(BITMAP * bmp, BITMAP * from, int p)

void Show_targeting_system(int Screen)
{
    int Nx = Clipx1+ ((Md->Pl[Screen].X>>16) + ((fcos(Md->Pl[Screen].Dir)*20>>16)) - Md->Pl[Screen].Sx);
    int Ny = Clipy1+ ((Md->Pl[Screen].Y>>16) + ((fsin(Md->Pl[Screen].Dir)*20>>16)) - Md->Pl[Screen].Sy);
    FAST_PUTPIXEL(Scr, Nx-1, Ny, 12);
    FAST_PUTPIXEL(Scr, Nx+1, Ny, 12);
    FAST_PUTPIXEL(Scr, Nx, Ny-1, 12);
    FAST_PUTPIXEL(Scr, Nx, Ny+1, 12);
    FAST_PUTPIXEL(Scr, Nx-1, Ny-1, 4);
    FAST_PUTPIXEL(Scr, Nx+1, Ny-1, 4);
    FAST_PUTPIXEL(Scr, Nx-1, Ny+1, 4);
    FAST_PUTPIXEL(Scr, Nx+1, Ny+1, 4);
} // void Show_targeting_system(int Screen)
void Draw_Players(int Screen)
{
    int Baseanim=0, X, Y; // Baseanim on animaation frame
    // X = Pelaajan (Count2) X ilman desimaaleja
    // Y = Pelaajan (Count2) Y ilman desimaaleja

    BITMAP * bmp, *bmp2, *bmp3;
    // kolme apumuuttuujaa ettei tarvitse kirjoittaa
    // niin paljon esim. ((BITMAP*) Dat[DATGUN0001+Md->Pl[Count2].Gun].dat)->w
    // (piipun bittikartan leveys)
    if (Md->Pl[Screen].Action == ACTION_SETPLATE) Action_setplate(Screen);
    if (Md->Pl[Screen].Action == ACTION_SNIPER) Action_sniper(Screen);
    if (Md->Pl[Screen].Live)
        if ((Md->Pl[Screen].Stuff[ITEM_TARGETINGSYSTEM]) || (Md->Pl[Screen].Gun == -1)) if (Md->Pl[Screen].Gun != 12) Show_targeting_system(Screen);
    if (Md->Pl[Screen].Action == ACTION_LASERCANNON)
    {
        X = (Md->Pl[Screen].X + fcos(Suunta(((Md->Pl[Screen].Dir>>16)-Md->Pl[Screen].Actionvar[1])<<16))*15) BitR;
        Y = (Md->Pl[Screen].Y + fsin(Suunta(((Md->Pl[Screen].Dir>>16)-Md->Pl[Screen].Actionvar[1])<<16))*15) BitR;
        putpixel(Scr, Clipx1+X - Md->Pl[Screen].Sx, Y - Md->Pl[Screen].Sy, 12);
        X = (Md->Pl[Screen].X + fcos(Suunta(((Md->Pl[Screen].Dir>>16)+Md->Pl[Screen].Actionvar[1])<<16))*15) BitR;
        Y = (Md->Pl[Screen].Y + fsin(Suunta(((Md->Pl[Screen].Dir>>16)+Md->Pl[Screen].Actionvar[1])<<16))*15) BitR;
        putpixel(Scr, Clipy1+X - Md->Pl[Screen].Sx, Y - Md->Pl[Screen].Sy, 12);
    } // if (Md->Pl[Screen].Action == ACTION_LASERCANNON)

    for (int Count2 = 0; Count2 < Opt->Players; Count2++)
        if (Md->Pl[Count2].Live) // pelaaja elossa
        {
            if (Weapongunpic[Md->Pl[Count2].Item] > -1)
                Md->Pl[Count2].Lastweapon = Md->Pl[Count2].Item;
            // laserrifle on special joten tässä se on
            if ((Md->Pl[Count2].Item == ITEM_LASERRIFLE) || (Md->Pl[Count2].Item == ITEM_LASERPISTOL))
                Update_laserrifle(Screen, Count2);
            // laserrifle end**
            // Pelaaja käyttää ropea
            if (Md->Pl[Count2].Ninjarope) Draw_ninjarope(Screen, Count2);
            // Desimaaliosat pois
            X = Md->Pl[Count2].X BitR;
            Y = Md->Pl[Count2].Y BitR;

            switch(Count2) // valitaan pelaajan tyyppinen animaatio(pelaajilla eri värit)
            {
            case 0:
                switch(Md->Pl[Count2].Anim)
                {
                case ANI_WALK: // kävelyanimaatio
                    if (Md->Pl[Count2].Gun != -1)
                        Baseanim = DATM1B1+Md->Pl[Count2].Picture;
                    else
                        Baseanim = DATM1A1+Md->Pl[Count2].Picture;
                    break;
                }; // switch(Md->Pl[Count2].Anim)
                break;
            case 1:
                switch(Md->Pl[Count2].Anim)
                {
                case ANI_WALK: // kävelyanimaatio
                    if (Md->Pl[Count2].Gun != -1)
                        Baseanim = DATM2B1+Md->Pl[Count2].Picture;
                    else
                        Baseanim = DATM2A1+Md->Pl[Count2].Picture;
                    break;
                }; // switch(Md->Pl[Count2].Anim)
                break;
            case 2:

                switch(Md->Pl[Count2].Anim)
                {
                case ANI_WALK: // kävelyanimaatio
                    if (Md->Pl[Count2].Gun != -1)
                        Baseanim = DATM3B1+Md->Pl[Count2].Picture;
                    else
                        Baseanim = DATM3A1+Md->Pl[Count2].Picture;
                    break;
                }; // switch(Md->Pl[Count2].Anim)
                break;
            }; // switch(Count2)
            switch(Md->Pl[Count2].Anim)
            {
            case ANI_PLASMADEATH: // kävelyanimaatio
                Baseanim = DATPLASMADEATH01+Md->Pl[Count2].Picture;
                break;
            }; // switch(Md->Pl[Count2].Anim)

            // Piipun bitmap
            bmp2 = 0;
            if (Md->Pl[Count2].Gun!=-1)
            {
                if (Md->Pl[Count2].S == 1)
                    bmp2 = (BITMAP*) Dat[DATGUN0001+Md->Pl[Count2].Gun].dat;
                else
                    bmp2 = (BITMAP*) Dat[DATGUNL0001+Md->Pl[Count2].Gun].dat;
            } // if (Md->Pl[Count2].Gun!=-1)
            // Suuliekin bitmap
            bmp3 = 0;
            if (Md->Pl[Count2].Gun!=-1)
                bmp3 = (BITMAP*) Dat[DATGUNF0001+Md->Pl[Count2].Gun].dat;
            // Ukon bitmap
            bmp = (BITMAP*) Dat[Baseanim].dat;
            if (Md->Pl[Count2].Camouflaged)
            {
                if (Md->Pl[Count2].Bmp1==0)
                {
                    Md->Pl[Count2].Bmp1 = create_bitmap(bmp->w, bmp->h);
                    clear(Md->Pl[Count2].Bmp1 );
                    Camouflage_bitmap(Md->Pl[Count2].Bmp1 , bmp, Count2);
                    bmp = Md->Pl[Count2].Bmp1;
                } // if (Md->Pl[Count2].Bmp1==0)
                if (Md->Pl[Count2].Bmp2==0) if (bmp2)
                    {
                        Md->Pl[Count2].Bmp2  = create_bitmap(bmp2->w, bmp2->h);
                        clear(Md->Pl[Count2].Bmp2);
                        Camouflage_bitmap(Md->Pl[Count2].Bmp2, bmp2, Count2);
                        bmp2 = Md->Pl[Count2].Bmp2;
                    } // if (Md->Pl[Count2].Bmp2==0)
            } // if (Md->Pl[Count2].Camouflaged)
            int Rx=0, Ry=0; // apumuuttujat tärinälle
            switch(Md->Pl[Count2].Gun)
            {
            case 0:
            case 8:// Pistols
                Rx = (Md->Pl[Count2].S==1) ? (2) : (-1);
                Ry -=2;
                break; // case 0: case 8:
            case 5: // Sniper rifle
                Ry -=2;
                break; // case 5:

            case 1:
            case 9:
                Ry -=1;
                Rx = (Md->Pl[Count2].S==1) ? (0) : (1);
                break; // Machinegun
            case 12:
                Ry -=1;
                Rx = (Md->Pl[Count2].S==0) ? (-2) : (3);
                break;
            case 2: // BAzooka
                Rx = (Md->Pl[Count2].S==1) ? (-1) : (2);
                Ry -=2;
                break; // case 0:
            }; // switch(Md->Pl[Count2].Gun)
            if (Md->Pl[Count2].Shake) // Jos piipun pitää täristä
            {   // esim. ammuttaessa
                Md->Pl[Count2].Shake--;
                Rx += -1+Rand()%3; // pientä tärinää
                Ry += -1+Rand()%3;
            } // (Md->Pl[Count2].Shake)
            if (Md->Pl[Count2].Parachute)
            {
                BITMAP * Bmp2 = (BITMAP*) Dat[DATPARACHUTE].dat;
                draw_sprite(Scr, Bmp2, Clipx1+ (X - Md->Pl[Screen].Sx)-(Bmp2->w>>1), Y - Md->Pl[Screen].Sy - (Bmp2->h>>1)-10);
            } // if (Md->Pl[Count2].Parachute)

            switch(Md->Pl[Count2].S)
            {
            case 1: // oikealle
                draw_sprite(Scr, bmp, Clipx1+ (X - Md->Pl[Screen].Sx - (bmp->w>>1)), Y - Md->Pl[Screen].Sy - (bmp->h>>1));

                if (Md->Pl[Count2].Gun!=-1) if (bmp2)
                        rotate_sprite(Scr, bmp2, Rx+Clipx1+ (X - Md->Pl[Screen].Sx - (bmp->w>>1))-22, Ry+Y+5 - Md->Pl[Screen].Sy - (bmp->h>>1), Md->Pl[Count2].Dir);

                // jos suuliekki täytyy piirtää
                if (Md->Pl[Count2].Gunfire) if (Gunfire[Md->Pl[Count2].Item])
                    {
                        if (Md->Pl[Count2].Gunfire)
                            Md->Pl[Count2].Gunfire--;
                        if (bmp3)
                            rotate_sprite(Scr, bmp3, Rx+Clipx1+ (X - Md->Pl[Screen].Sx - (bmp->w>>1))-22, Ry+Y+5 - Md->Pl[Screen].Sy - (bmp->h>>1), Md->Pl[Count2].Dir);
                    } // if (Md->Pl[Count2].Gunfire)

                break;
            case 0: // vasemmalle
                draw_sprite_h_flip(Scr, bmp, Clipx1+(X - Md->Pl[Screen].Sx - (bmp->w>>1)), Y - Md->Pl[Screen].Sy - (bmp->h>>1));
                if (Md->Pl[Count2].Gun!=-1) if (bmp2)
                        rotate_sprite(Scr, bmp2, Rx+Clipx1-19+ (X - Md->Pl[Screen].Sx - (bmp->w>>1)), Ry+Y+5 - Md->Pl[Screen].Sy - (bmp->h>>1), Md->Pl[Count2].Dir);
                // jos suuliekki täytyy piirtää
                if (Md->Pl[Count2].Gunfire) if (Gunfire[Md->Pl[Count2].Item])
                    {
                        if (Md->Pl[Count2].Gunfire)
                            Md->Pl[Count2].Gunfire--;
                        if (bmp3)
                            rotate_sprite(Scr, bmp3, Rx+Clipx1-19+ (X - Md->Pl[Screen].Sx - (bmp->w>>1)), Ry+Y+5 - Md->Pl[Screen].Sy - (bmp->h>>1), Md->Pl[Count2].Dir);
                    } // if (Md->Pl[Count2].Gunfire) if (Gunfire[Md->Pl[Count2].Item])
                break;
            }; // switch(Md->Pl[Count2].S)
            if (Md->Pl[Count2].Camouflaged)
            {
                if (Md->Pl[Count2].Bmp1)
                {
                    destroy_bitmap(Md->Pl[Count2].Bmp1);
                    Md->Pl[Count2].Bmp1 = 0;
                } // if (Md->Pl[Count2].Bmp1)
                if (Md->Pl[Count2].Bmp2)
                {
                    destroy_bitmap(Md->Pl[Count2].Bmp2);
                    Md->Pl[Count2].Bmp2 = 0;
                } // if (Md->Pl[Count2].Bmp1)
            } // if (Md->Pl[Count2].Camouflaged)

        } // for (int Count2 = 0; Count2 < Opt->Players; Count2++)

} // Draw_Players
void Draw_vehicles(int Screen)
{
    int Baseanim=0, X, Y; // Baseanim on animaation frame
    // X = Pelaajan (Count2) X ilman desimaaleja
    // Y = Pelaajan (Count2) Y ilman desimaaleja

    BITMAP * bmp, *bmp2, *bmp3;
    // kolme apumuuttuujaa ettei tarvitse kirjoittaa
    // niin paljon esim. ((BITMAP*) Dat[DATGUN0001+Md->Pl[Count2].Gun].dat)->w
    // (piipun bittikartan leveys)
    for (int Count2 = 0; Count2 < Maxvehicles; Count2++)
        if (Md->Veh[Count2].Live) // pelaaja elossa
        {
            // Desimaaliosat pois
            X = Md->Veh[Count2].X BitR;
            Y = Md->Veh[Count2].Y BitR;
            switch(Md->Veh[Count2].Type)
            {
            case VEH_WALKER:
            {
                Baseanim = DATVEHICLE1_01;

                bmp2 = (BITMAP*) Dat[DATVEHICLE1_12].dat;
                // Suuliekin bitmap
                bmp3 = (BITMAP*) Dat[DATVEHICLE1_13].dat;
                // Ukon bitmap
                bmp = (BITMAP*) Dat[Baseanim].dat;
            }
            break; // case VEH_WALKER:
            case VEH_TRANSPORT:
            {
                Baseanim = DATVEHICLE2_01;

                bmp2 = 0;
                // Suuliekin bitmap
                bmp3 = 0;
                // Ukon bitmap
                bmp = (BITMAP*) Dat[Baseanim].dat;
            }
            break; // case VEH_TRANSPORT:
            }; // switch(Md->Veh[Count2].Type)

            int Rx=0, Ry=0; // apumuuttujat tärinälle
            if (Md->Veh[Count2].Shake) // Jos piipun pitää täristä
            {   // esim. ammuttaessa
                Md->Veh[Count2].Shake--;
                Rx = -1+Rand()%3; // pientä tärinää
                Ry = -1+Rand()%3;
            } // (Md->Veh[Count2].Shake)
            switch(Md->Veh[Count2].S)
            {
            case 1: // oikealle
                draw_sprite(Scr, bmp, Clipx1+ (X - Md->Pl[Screen].Sx - (bmp->w>>1)), Y - Md->Pl[Screen].Sy - (bmp->h>>1));
                if (bmp2)
                    rotate_sprite(Scr, bmp2, Rx+Clipx1+6+ (X - Md->Pl[Screen].Sx - (bmp->w>>1))-8, Ry+Y+1 - Md->Pl[Screen].Sy - (bmp->h>>1), Md->Veh[Count2].Dir);
                // jos suuliekki täytyy piirtää
                if (Md->Veh[Count2].Gunfire)
                {
                    Md->Veh[Count2].Gunfire--;
                    if (bmp3)
                        rotate_sprite(Scr, bmp3, Rx+Clipx1+6+ (X - Md->Pl[Screen].Sx - (bmp->w>>1))-8, Ry+Y+1 - Md->Pl[Screen].Sy - (bmp->h>>1), Md->Veh[Count2].Dir);
                } // if (Md->Veh[Count2].Gunfire)

                break;
            case 0: // vasemmalle
                draw_sprite_h_flip(Scr, bmp, Clipx1+(X - Md->Pl[Screen].Sx - (bmp->w>>1)), Y - Md->Pl[Screen].Sy - (bmp->h>>1));
                if (bmp2)
                    rotate_sprite(Scr, bmp2, Rx+Clipx1-5+ (X - Md->Pl[Screen].Sx - (bmp->w>>1)), Ry+Y - Md->Pl[Screen].Sy - (bmp->h>>1), Md->Veh[Count2].Dir);
                // jos suuliekki täytyy piirtää
                if (Md->Veh[Count2].Gunfire)
                {
                    Md->Veh[Count2].Gunfire--;
                    if (bmp3)
                        rotate_sprite(Scr, bmp3, Rx+Clipx1-5+ (X - Md->Pl[Screen].Sx - (bmp->w>>1)), Ry+Y - Md->Pl[Screen].Sy - (bmp->h>>1), Md->Veh[Count2].Dir);
                } // if (Md->Veh[Count2].Gunfire) if (Gunfire[Md->Veh[Count2].Item])
                break;
            }; // switch(Md->Veh[Count2].S)
        } // for (int Count2 = 0; Count2 < Opt->Players; Count2++)
} // void Draw_vehicles(int Screen)
void Draw_Bots(int Screen)
{
    int Baseanim=0, X, Y; // Baseanim on animaation frame
    // X = Pelaajan (Count2) X ilman desimaaleja
    // Y = Pelaajan (Count2) Y ilman desimaaleja

    BITMAP * bmp, *bmp2, *bmp3;
    // kolme apumuuttuujaa ettei tarvitse kirjoittaa
    // niin paljon esim. ((BITMAP*) Dat[DATGUN0001+Md->Pl[Count2].Gun].dat)->w
    // (piipun bittikartan leveys)
    for (int Count2 = 0; Count2 < Opt->Bots; Count2++)
        if (Md->Bot[Count2].Live) // pelaaja elossa
        {
            // laserrifle on special joten tässä se on
            if ((Md->Bot[Count2].Item == ITEM_LASERRIFLE) || (Md->Bot[Count2].Item == ITEM_LASERPISTOL))
                Update_bot_laserrifle(Screen, Count2);
            // laserrifle end**
            // Pelaaja käyttää ropea
            if (Md->Bot[Count2].Ninjarope) Draw_bot_ninjarope(Screen, Count2);
            // Desimaaliosat pois
            X = Md->Bot[Count2].X BitR;
            Y = Md->Bot[Count2].Y BitR;

            switch(Md->Bot[Count2].Anim)
            {
            case ANI_WALK: // kävelyanimaatio
                Baseanim = DATM4A1+Md->Bot[Count2].Picture;
                break;
            }; // switch(Md->Bot[Count2].Anim)
            switch(Md->Bot[Count2].Anim)
            {
            case ANI_PLASMADEATH: // kävelyanimaatio
                Baseanim = DATPBDEATH01+Md->Bot[Count2].Picture;
                break;
            }; // switch(Md->Pl[Count2].Anim)
            // Piipun bitmap
            bmp2 = 0;
            if (Md->Bot[Count2].Gun!=-1)
            {
                if (Md->Bot[Count2].Gs == 1)
                    bmp2 = (BITMAP*) Dat[DATGUNB01+Md->Bot[Count2].Gun].dat;
                else
                    bmp2 = (BITMAP*) Dat[DATGUNBL01+Md->Bot[Count2].Gun].dat;
            } // if (Md->Pl[Count2].Gun!=-1)
            // Suuliekin bitmap
            bmp3 = 0;
            if (Md->Bot[Count2].Gun!=-1)
                bmp3 = (BITMAP*) Dat[DATGUNF0001+Md->Bot[Count2].Gun].dat;
            bmp = (BITMAP*) Dat[Baseanim].dat;
            int Rx=0, Ry=0; // apumuuttujat tärinälle
            switch(Md->Bot[Count2].Gun)
            {
            case 0:
            case 8:// Pistols
                Rx = (Md->Bot[Count2].Gs==1) ? (2) : (-1);
                Ry -=2;
                break; // case 0: case 8:
            case 5: // Sniper rifle
                Ry -=2;
                break; // case 5:
            case 1:
            case 9:
                Ry -=1;
                Rx = (Md->Bot[Count2].Gs==1) ? (0) : (1);
                break; // Machinegun
            case 2: // BAzooka
                Rx = (Md->Bot[Count2].Gs==1) ? (-1) : (2);
                Ry -=2;
                break; // case 0:
            }; // switch(Md->Pl[Count2].Gun)
            if (Md->Bot[Count2].Shake) // Jos piipun pitää täristä
            {   // esim. ammuttaessa
                Md->Bot[Count2].Shake--;
                Rx += -1+Rand()%3; // pientä tärinää
                Ry += -1+Rand()%3;
            } // (Md->Bot[Count2].Shake)
            switch(Md->Bot[Count2].Gs)
            {
            case 1: // oikealle
                draw_sprite(Scr, bmp, Clipx1+ (X - Md->Pl[Screen].Sx - (bmp->w>>1)), Y - Md->Pl[Screen].Sy - (bmp->h>>1));
                if (Md->Bot[Count2].Gun!=-1)
                    rotate_sprite(Scr, bmp2, Rx+Clipx1+ (X - Md->Pl[Screen].Sx - (bmp->w>>1))-22, Ry+Y+5 - Md->Pl[Screen].Sy - (bmp->h>>1), Md->Bot[Count2].Dir);
                // jos suuliekki täytyy piirtää
                if (Md->Bot[Count2].Gunfire) if (Gunfire[Md->Bot[Count2].Item])
                    {
                        if (Md->Bot[Count2].Gunfire)
                            Md->Bot[Count2].Gunfire--;
                        rotate_sprite(Scr, bmp3, Rx+Clipx1+ (X - Md->Pl[Screen].Sx - (bmp->w>>1))-22, Ry+Y+5 - Md->Pl[Screen].Sy - (bmp->h>>1), Md->Bot[Count2].Dir);
                    } // if (Md->Bot[Count2].Gunfire)

                break;
            case 0: // vasemmalle
                draw_sprite_h_flip(Scr, bmp, Clipx1+(X - Md->Pl[Screen].Sx - (bmp->w>>1)), Y - Md->Pl[Screen].Sy - (bmp->h>>1));
                if (Md->Bot[Count2].Gun!=-1)
                    rotate_sprite(Scr, bmp2, Rx+Clipx1-19+ (X - Md->Pl[Screen].Sx - (bmp->w>>1)), Ry+Y+5 - Md->Pl[Screen].Sy - (bmp->h>>1), Md->Bot[Count2].Dir);
                // jos suuliekki täytyy piirtää
                if (Md->Bot[Count2].Gunfire) if (Gunfire[Md->Bot[Count2].Item])
                    {
                        if (Md->Bot[Count2].Gunfire)
                            Md->Bot[Count2].Gunfire--;
                        rotate_sprite(Scr, bmp3, Rx+Clipx1-19+ (X - Md->Pl[Screen].Sx - (bmp->w>>1)), Ry+Y+5 - Md->Pl[Screen].Sy - (bmp->h>>1), Md->Bot[Count2].Dir);
                    } // if (Md->Bot[Count2].Gunfire) if (Gunfire[Md->Bot[Count2].Item])
                break;
            }; // switch(Md->Bot[Count2].S)
//             Textint(Scr, font, Dirvali(Md->Bot[Count2].Dir>>16, Md->Bot[Count2].Targetdir>>16), Clipx1+(X - Md->Pl[Screen].Sx), Y - Md->Pl[Screen].Sy, 15);
//             Textint(Scr, font, Md->Bot[Count2].Forgettarget, Clipx1+(X - Md->Pl[Screen].Sx), Y - Md->Pl[Screen].Sy+10, 15);
//              Textint(Scr, font, Md->Bot[Count2].Targetdir>>16, Clipx1+(X - Md->Pl[Screen].Sx), Y - Md->Pl[Screen].Sy+20, 15);
        } // for (int Count2 = 0; Count2 < Opt->Players; Count2++)
} // Draw_Bots
void Draw_Bullets(int Screen)
{
    // Piirtää bulletit pelaajan(Screen) ruutuun
    bool Show = false; // Apumuuttuja (näytetäänkö panos)
    int X, Y,Xx, Yy; // Uusi ja vanha X, Y desimaaliosat pois
    int XX, YY;
    BITMAP * bmp; // apumuuttuja ettei tarvitse kirjoittaa paljon...
    for (int i = 0; i < Maxbullets; i++)
        if (Md->Bul[i].Live)
        {
            X = Md->Bul[i].X BitR;
            Y = Md->Bul[i].Y BitR;
            Xx = Md->Bul[i].Ox BitR;
            Yy = Md->Bul[i].Oy BitR;

            Show = false;
            // jos ruudulla
            if (X - Md->Pl[Screen].Sx + Clipx1> Clipx1-30)
                if (Y - Md->Pl[Screen].Sy > Clipy1-30)
                    if (X - Md->Pl[Screen].Sx + Clipx1 < Clipx2+30)
                        if (Y - Md->Pl[Screen].Sy < Clipy2+30)
                            Show = true;
            YY = Y - Md->Pl[Screen].Sy;
            XX = Clipx1+(X- Md->Pl[Screen].Sx);
            if (Show) // näytetään panos
            {
                switch(Md->Bul[i].Type)
                {
                case BUL_PISTOL: // tavallinen panos
                    if (XX >= Clipx1) if (YY >= Clipy1)
                            if (XX <  Clipx2) if (YY < Clipy2)
                                    Scr->line[YY][XX] = 7;
                    break; // BUL_DIRT
                case BUL_DIRT: // "kakkua" esim... maata
                    if (XX >= Clipx1) if (YY >= Clipy1)
                            if (XX <  Clipx2) if (YY < Clipy2)
                                    Scr->line[YY][XX] = Md->Bul[i].Dat[1];
                    break; // BUL_DIRT
                case BUL_BLOOD: // verta
                    if (XX >= Clipx1) if (YY >= Clipy1)
                            if (XX <  Clipx2) if (YY < Clipy2)
                                    Scr->line[YY][XX] = Md->Bul[i].Dat[1];
                    break; // BUL_BLOOD
                case BUL_GORE: // ruumiinosia
                    bmp = (BITMAP * ) Dat[Md->Bul[i].Dat[0]].dat;
                    rotate_sprite(Scr, bmp, Clipx1+(X- Md->Pl[Screen].Sx)- (bmp->w>>1), Y - Md->Pl[Screen].Sy-(bmp->h>>1), Md->Bul[i].Dat[1]);
                    break;
                case BUL_SHOTGUNSHELL: // hylsyjä
                case BUL_BULLETSHELL: // hylsyjä
                    if (XX >= Clipx1) if (YY >= Clipy1)
                            if (XX <  Clipx2) if (YY < Clipy2)
                                    Scr->line[YY][XX] = Md->Bul[i].Dat[1];
                    break;
                case BUL_GRENADE:
                    bmp = (BITMAP * ) Dat[DATBULLETPIC05].dat;
                    rotate_sprite(Scr, bmp, Clipx1+(X- Md->Pl[Screen].Sx)- (bmp->w>>1), Y - Md->Pl[Screen].Sy-(bmp->h>>1), Md->Bul[i].Dat[1]);
                    break;
                case BUL_ROCKET:
                    bmp = (BITMAP * ) Dat[DATBAZOOKA].dat;
                    rotate_sprite(Scr, bmp, Clipx1+(X- Md->Pl[Screen].Sx)- (bmp->w>>1), Y - Md->Pl[Screen].Sy-(bmp->h>>1), Md->Bul[i].Dir);
                    break;
                case BUL_SMOKE: // savua
                    if (XX >= Clipx1) if (YY >= Clipy1)
                            if (XX <  Clipx2) if (YY < Clipy2)
                                    Scr->line[YY][XX] = Md->Bul[i].Dat[1];
                    break;
                case BUL_PLASMA2:
                case BUL_PLASMA3:
                    if (XX >= Clipx1) if (YY >= Clipy1)
                            if (XX <  Clipx2) if (YY < Clipy2) //if (Md->Bul[i].Dat[2])
                                {
                                    Scr->line[YY][XX] = Md->Bul[i].Dat[3];
                                    if (XX>Clipx1)
                                        Scr->line[YY][XX+1] = Md->Bul[i].Dat[3]+2;
                                    if (XX< Clipx2-1)
                                        Scr->line[YY][XX-1] = Md->Bul[i].Dat[3]+2;
                                    if (YY< Clipy2-1)
                                        Scr->line[YY+1][XX] = Md->Bul[i].Dat[3]+2;
                                    if (YY> Clipy1)
                                        Scr->line[YY-1][XX] = Md->Bul[i].Dat[3]+2;
                                }
                    break;
                case BUL_LAVABOMB:
                    bmp = (BITMAP * ) Dat[DATBULLETPIC08].dat;
                    rotate_sprite(Scr, bmp, Clipx1+(X- Md->Pl[Screen].Sx)- (bmp->w>>1), Y - Md->Pl[Screen].Sy-(bmp->h>>1), Md->Bul[i].Dat[1]);
                    break;
                case BUL_SHRAPNEL:
                    bmp = (BITMAP * ) Dat[DATSHRAPNEL01+Md->Bul[i].Dat[4]].dat;
                    rotate_sprite(Scr, bmp, Clipx1+(X- Md->Pl[Screen].Sx)- (bmp->w>>1), Y - Md->Pl[Screen].Sy-(bmp->h>>1), Md->Bul[i].Dat[1]);
                    break;
                }; // switch(Md->Bul[i].Type)
            } // Show
        } //    for (int i = 0; i < Maxbullets; i++)     if (Md->Bul[i].Live)
} // Draw_Bullets(int Screen)
void Draw_Playerdata(int Screen)
{
    if (Md->Pl[Screen].Live == false)
    {
        hline(Scr, Clipx1, 0, Clipx1+(Md->Pl[Screen].Killtimer*Clipx/600), 8);
    } //    if (Md->Pl[Screen].Live == false)
    if (Md->Bld[Screen].Live)
    {
        hline(Scr, Clipx1, 1, Clipx1+(Md->Bld[Screen].Energy*Clipx/Bldenergy[0]), 10);
    } //    if (Md->Pl[Screen].Live == false)
//­   Textint(Scr, font, Md->Pl[Screen].Select[Md->Pl[Screen].Menu], Clipx1+20, 2, 15);
    // kehikko vahingon näyttämiseen
    draw_sprite(Scr, (BITMAP * ) Dat[DATDAMAGE001+Screen].dat, Clipx1 + 2, 2);
    // piirretään osumat
    for (int i = 0; i < 3; i++) if (Md->Pl[Screen].Hits[i])
        {
            switch(i)
            {
            case 0:
                draw_sprite(Scr, (BITMAP * ) Dat[DATDHEAD1 +Md->Pl[Screen].Hits[i]-1].dat, Clipx1 + 2, 2);
                break;
            case 1:
                draw_sprite(Scr, (BITMAP * ) Dat[DATDTORSO1+Md->Pl[Screen].Hits[i]-1].dat, Clipx1 + 2, 2);
                break;
            case 2:
                draw_sprite(Scr, (BITMAP * ) Dat[DATDLEGS1 +Md->Pl[Screen].Hits[i]-1].dat, Clipx1 + 2, 2);
                break;
            };  // Switch i

            /*          Textint(Scr, font, Md->Pl[Screen].Armor[i], Clipx1+2, 2+i*10,10);
            Textint(Scr, font, Md->Pl[Screen].Killdamage[i], Clipx1+12, 2+i*10,10);
                 Textint(Scr, font, Md->Pl[Screen].Hits[i], Clipx1+2, 40+i*10,10);
            */
        }
    // piirretään panssarit
    for (int i = 0; i < 3; i++) if (Md->Pl[Screen].Armor[i])
        {
            switch(i)
            {
            case 0:
                draw_sprite(Scr, (BITMAP * ) Dat[DATARMORHEAD1+(3*(Md->Pl[Screen].Armor[i]-1))+Screen].dat, Clipx1 + 2, 2);
                break;
            case 1:
                draw_sprite(Scr, (BITMAP * ) Dat[DATARMORTORSO1+(3*(Md->Pl[Screen].Armor[i]-1))+Screen].dat, Clipx1 + 2, 2);
                break;
            case 2:
                draw_sprite(Scr, (BITMAP * ) Dat[DATARMORLEGS1+(3*(Md->Pl[Screen].Armor[i]-1))+Screen].dat, Clipx1 + 2, 2);
                break;
            };  // Switch i
        }
    // piirretään Itemlaatikko
    draw_sprite(Scr, (BITMAP * )Dat[DATITEMBOX].dat, Clipx2 - 40, 2);
    // piirretään monta kappaletta on kädessä
    if (Md->Pl[Screen].Item>-1) if (Stufflimit[Md->Pl[Screen].Item]>1)
        {
            char * s = new char[5]; // varataan muistia
            memset(s, 0, 5);        // tyhjennetään se
            itoa(Md->Pl[Screen].Stuff[Md->Pl[Screen].Item], s, 10); // sijoitetaan Money sinne 10 - järjestelmässä
            // ja piirretään merkkijono
            textout_centre(Scr, (FONT*) Dat[SMALLFONT].dat, s, Clipx2-20, 20, -1);
            delete s; // wapautetaan muisti
        } // if (Md->Pl[Screen].Item)

    // ja käytettävä itemi sinne sisään
    draw_sprite(Scr, (BITMAP * )Dat[DATITEM001+Md->Pl[Screen].Item].dat, Clipx2 - 37, 10);
    // hieno rahalogo
    draw_sprite(Scr, (BITMAP *) Dat[DATMONEY].dat, Clipx2-80, 3);
    // sitten muutetaan numero to merkkijono
    char * s = new char[13]; // varataan muistia
    memset(s, 0, 13);        // tyhjennetään se
    itoa(Md->Pl[Screen].Money, s, 10); // sijoitetaan Money sinne 10 - järjestelmässä
    // ja piirretään merkkijono
    textout_centre(Scr, (FONT*) Dat[SMALLFONT].dat, s, Clipx2-70, 2, -1);
    delete s; // wapautetaan muisti
    int Bullets, Clips; // Pelaajan panokset sekä lipppaat
    if (Clipsize[Md->Pl[Screen].Item]) if (Md->Pl[Screen].Stuff[Md->Pl[Screen].Item])
            if ((Md->Pl[Screen].Ammo[Weaponclip[Md->Pl[Screen].Item]]) || (Dontneedammo[Md->Pl[Screen].Item]))
            {
                // Jakojäännös totalpanoksista/lippaan koosta
                Bullets = Md->Pl[Screen].Ammo[Weaponclip[Md->Pl[Screen].Item]] % Clipsize[Md->Pl[Screen].Item];
                // Jako totalpanoksista/lippaan koosta
                Clips   = Md->Pl[Screen].Ammo[Weaponclip[Md->Pl[Screen].Item]] / Clipsize[Md->Pl[Screen].Item];
                if (Md->Pl[Screen].Item == ITEM_GRENADE) Clips = Md->Pl[Screen].Stuff[ITEM_GRENADE];
                if (Clipsize[Md->Pl[Screen].Item] == 1) {
                    Bullets = Clips;
                    Clips = 0;
                }
                // piirretään lippaat
                for (int i = 0; i < Clips; i ++)
                    putpixel(Scr, Clipx1 + 20 + i * 2, 2, 14);
                BITMAP * bmp  = (BITMAP*) Dat[Bulpic[Md->Pl[Screen].Item]].dat;
                // piirretään bulletit
                for (int i = 0; i < Bullets; i++)
                    draw_sprite(Scr, bmp, Clipx1 + 26 + i* (bmp->w+1),4);

            } // if (Clipsize[Md->Pl[Screen].Item])
    for (int i = 0; i < Opt->Players; i++)
    {
        // Piirretään Playereiden tapot
        Textint(Scr, (FONT*) Dat[SMALLFONT].dat, Md->Pl[Screen].Kills[i],  Clipx1 + 2, 40+i*10, -1);
    }

} // Draw_Playerdata(int Screen)
void Draw_Buildings(int Screen)
{
    // Apumuuttujat, mistä rakennuksen positio (desimaaliosa pois)- pelaajan
    // ruudun positio
    int X, Y;

    // apumuuttuja, piirretäänkö rakennus
    bool Show;

    // apumuuttuja, ettei tarvitse kirjoittaa tätä rimpsua joka kerta:
    // (BITMAP*) Dat[DATBLD0001+Md->Bld[Count].Type].dat
    BITMAP * bmp;
    for (int Count = 0; Count < Maxbuildings; Count++)
        if (Md->Bld[Count].Live) // rakennus "elossa"
        {
            // desimaaliosa veks ja otetaan ruudun koordit huomioon
            X = (Md->Bld[Count].X BitR) - Md->Pl[Screen].Sx;
            Y = (Md->Bld[Count].Y BitR) - Md->Pl[Screen].Sy;
            // vakiona ei näytetä
            Show = false;
            // nimen lyhennys
            bmp = (BITMAP*) Dat[Bldpic[Md->Bld[Count].Type]+Md->Bld[Count].Pic].dat;
            if ((Md->Bld[Count].Type == BLD_LAVATRAP) || (Md->Bld[Count].Type == BLD_SUPERLAVATRAP))
            {
                bmp = (BITMAP*) Dat[Bldpic[Md->Bld[Count].Type]+Md->Bld[Count].Owner*8+Md->Bld[Count].Pic].dat;
            } // if (Md->Bld[Count].Type == BLD_LAVATRAP)
            // jos on pelaajan ruudussa(clippausrajojen sisässä)
            if (X + Clipx1 > Clipx1-(bmp->w))
                if (Y > Clipy1-(bmp->h))
                    if (X + Clipx1 < Clipx2+(bmp->w>>1))
                        if (Y < Clipy2+(bmp->h>>1))
                            Show = true; // silloin näytetään
            if (Show)
            {
                // piirretään bittikartta
                if (Md->Bld[Count].Type != BLD_PLATE)
                    if (Md->Bld[Count].Type != BLD_REINFPLATE)
                        draw_sprite(Scr, bmp, Clipx1 + X, Clipy1 + Y);
                switch(Md->Bld[Count].Type)
                {
                case BLD_PLATE:
                    stretch_sprite(Scr, (BITMAP*) Dat[DATWHITEPLATE].dat, Clipx1 + X - (Md->Bld[Count].Dat[0]>>1), Clipy1 + Y - (Md->Bld[Count].Dat[0]>>1), Md->Bld[Count].Dat[0], Md->Bld[Count].Dat[0]);
                    break; //                  case BLD_PLATE:
                case BLD_REINFPLATE:
                    stretch_sprite(Scr, (BITMAP*) Dat[DATGRAYPLATE].dat, Clipx1 + X - (Md->Bld[Count].Dat[0]>>1), Clipy1 + Y - (Md->Bld[Count].Dat[0]>>1), Md->Bld[Count].Dat[0], Md->Bld[Count].Dat[0]);
                    break; //                  case BLD_REINFPLATE:
                }; //                switch(Md->Bld[Count].Type)

            } // (Show)
        } // for (int Count = 0; Count < Maxbuildings; Count++)
} // Draw_Buildings(int Screen)
void Draw_Explosions(int Screen)
{
    // apumuuttujat räjähdyksen positio - pelaajan (screen) ruudun
    // positio
    int X, Y;

    // näytetäänkö räjähdys
    bool Show;

    // nimen lyhennystä varten
    BITMAP * bmp;
    for (int i = 0; i < Maxexp; i++)
        if (Md->Exp[i].Live)
        {
            // miinustetaan ruudun koordi
            X = Md->Exp[i].X - Md->Pl[Screen].Sx;
            Y = Md->Exp[i].Y - Md->Pl[Screen].Sy;
            // räjähdyscounter
            Md->Exp[i].Count ++;
            if (Md->Exp[i].Count>15)
            {
                Md->Exp[i].Count = 0;
                if (Md->Exp[i].Delay)
                {
                    Md->Exp[i].Delay--;
                } else Md->Exp[i].Frame++;
                // seuraava kuva
            } // if (Md->Exp[i].Count>15)

            // lyhennetään nimi
            bmp = (BITMAP*) Exp[Md->Exp[i].Frame].dat;
            if (Md->Exp[i].Type == 6) bmp = (BITMAP*) Dat[Md->Exp[i].Frame].dat;
            // defaulttina ei näytetä
            Show = false;
            // jos pelaajan ruudussa(clippausrajojen sisällä)
            if (X + Clipx1 > Clipx1-(bmp->w))
                if (Y > Clipy1-(bmp->h))
                    if (X + Clipx1 < Clipx2+(bmp->w>>1))
                        if (Y < Clipy2+(bmp->h>>1))
                            Show = true; // näytetään räjähdys
            if (Md->Exp[i].Delay) Show = false;
            if (Show) // piirretään läpinäkyvä räjähdys
                draw_trans_sprite(Scr, bmp, Clipx1+X-(bmp->w>>1), Y-(bmp->h>>1));
            // tuhotaan räjähdys jos animaatio on lopussa
            // räjähdyskuvat ovat tiedostossa putkena ja ne ovat eripituisia
            // joten täytyy vain tietää mikä frame on viimeinen
            switch (Md->Exp[i].Type)
            {
            case 0:
                if (Md->Exp[i].Frame == a08) Md->Exp[i].Live = false;
                break; // 0
            case 1:
                if (Md->Exp[i].Frame == a14) if (Md->Exp[i].Check==false)
                    {
                        Emptypic(bmp, Md->Exp[i].X-(bmp->w>>1), Md->Exp[i].Y-(bmp->h>>1), Md->Exp[i].Break, 1);
                        Md->Exp[i].Check = true;
                    }
                if (Md->Exp[i].Frame == a16) Md->Exp[i].Live = false;
                break; // 1
            case 2:
                if (Md->Exp[i].Frame == a24) if (Md->Exp[i].Check==false)
                    {
                        Md->Exp[i].Check = true;
                        Emptypic(bmp, Md->Exp[i].X-(bmp->w>>1), Md->Exp[i].Y-(bmp->h>>1), Md->Exp[i].Break, 1);
                    }

                if (Md->Exp[i].Frame == a28) Md->Exp[i].Live = false;
                break; // 2
            case 3:
                if (Md->Exp[i].Frame == a34) Md->Exp[i].Live = false;
                break; // 3
            case 4:
                if (Md->Exp[i].Frame == a38) if (Md->Exp[i].Check==false)
                    {
                        Md->Exp[i].Check = true;
                        Emptypic(bmp, Md->Exp[i].X-(bmp->w>>1), Md->Exp[i].Y-(bmp->h>>1), Md->Exp[i].Break, 1);
                    } // if (Md->Exp[i].Frame == a38) if (Md->Exp[i].Check==false)

                if (Md->Exp[i].Frame == a40) Md->Exp[i].Live = false;
                break; // 3
            case 5:
                if (Md->Exp[i].Frame == a47) Md->Exp[i].Live = false;
                break; // 3
            case 6:
                Emptypic(bmp, Md->Exp[i].X-(bmp->w>>1), Md->Exp[i].Y-(bmp->h>>1), Md->Exp[i].Break, 0);
                if (Md->Exp[i].Frame == DATLASER03) Md->Exp[i].Live = false;
                break;
            }; // switch (Md->Exp[i].Type)
        } //    for (int i = 0; i < Maxexp; i++)
} // void Draw_Explosions(int Screen)
void Draw_Lava(int Screen)
{
    int x , y;
    for (int i = 0; i < Maxlava; i++)
        if (Md->Lava[i].Live)
        {
            // Clipx1 on ruudun reuna
            // (Md->Lava[i].X BitR) laavan kordinaatti mistä desimaaliosa on katkaistu
            // Md->Pl[Screen].Sx on pelaajan screen ruudun x
            x = Clipx1+(Md->Lava[i].X BitR) - Md->Pl[Screen].Sx;
            y = (Md->Lava[i].Y BitR) - Md->Pl[Screen].Sy;
            // jos laava täytyy piirtää niin piirretään
            if (x >= Clipx1)
                if (x < Clipx2)
                    if (y >= Clipy1)
                        if (y < Clipy2) Scr->line[y][x] = Md->Lava[i].C;
        } // for (int i = 0; i < Maxlava; i++)
} // Draw_Lava
void Draw_Menus(int Screen)
{


    int Rx=0, Ry=0;
    // apumuuttujat Rx, Ry ovat menun alkupisteet
    if (Md->Pl[Screen].Menu>-1) // jos menu on päällä
    {
        // katsotaan mihin menu kuuluu
        switch(Md->Pl[Screen].Menu)
        {
        case MENU_MAIN:
            Rx = 0;
            Ry = 0;
            break;
        case MENU_BUY:
            Rx=-18;
            Ry = -20;
            break;
        case MENU_BUYWEAPONS:
            Rx=-18;
            Ry = -40;
            break;
        case MENU_BUYTOOLS:
            Rx=-18;
            Ry = -40;
            break;
        case MENU_BUYPROJECTW:
            Rx-=54;
            Ry = -60;
            break;
        case MENU_BUYENERGYW:
            Rx-=18;
            Ry = -60;
            break;
        case MENU_BUYBOMBS:
            Rx-=18;
            Ry = -60;
            break;
        case MENU_BUYAMMO:
            Rx-=36;
            Ry = -40;
            break;
        case MENU_BUYARMOR:
            Rx-=36;
            Ry = -60;
            break;
        case MENU_INVENTORY:
            Rx-=82;
            Ry = -106;
            break;
        case MENU_BUYBUILD:
            Rx-=18;
            Ry = -60;
            break;
        case MENU_BUYTOOLS2:
            Rx=-18;
            Ry = -60;
            break;
        case MENU_BUYVEHICLES:
            Rx=-18;
            Ry = -60;
            break;
        }; // switch(Md->Pl[Screen].Menu)
        if (Md->Pl[Screen].Menu == MENU_INVENTORY)
        {
            int Times = Md->Pl[Screen].Select[Md->Pl[Screen].Menu] / 10;
            Ry+= Times*18;
        } //       if (Md->Pl[Screen].Menu == MENU_INVENTORY)
        // sitten missä kohdassa kohdistin on
        switch(Md->Pl[Screen].Select[Md->Pl[Screen].Menu] % 10)
        {
        case 0:
            Rx += 0;
            break;
        case 1:
            Rx += 18;
            break;
        case 2:
            Rx += 36;
            break;
        case 3:
            Rx += 54;
            break;
        case 4:
            Rx += 72;
            break;
        case 5:
            Rx += 90;
            break;
        case 6:
            Rx += 108;
            break;
        case 7:
            Rx += 126;
            break;
        case 8:
            Rx += 144;
            break;
        }; // switch(Md->Pl[Screen].Select[Md->Pl[Screen].Menu])
        Md->Pl[Screen].Selectrealx = Rx;
        Md->Pl[Screen].Selectrealy = Ry;
        // piirretään perusmenut
        draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUY].dat, Clipx1 + (Clipx>>1)-(((BITMAP * ) Dat[DATMENUBUY].dat)->w>>1), (Clipy>>1)-10-(((BITMAP * ) Dat[DATMENUBUY].dat)->h>>1));
        draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUINVENTORY].dat, Clipx1 + 18+ (Clipx>>1)-(((BITMAP * ) Dat[DATMENUBUY].dat)->w>>1), (Clipy>>1)-10-(((BITMAP * ) Dat[DATMENUBUY].dat)->h>>1));

        // jos ei voi ostaa piirretään ruksi
        if (Md->Pl[Screen].Canbuy == false)
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUCROSS].dat, Clipx1 + (Clipx>>1)-(((BITMAP * ) Dat[DATMENUCROSS].dat)->w>>1), (Clipy>>1)-10-(((BITMAP * ) Dat[DATMENUCROSS].dat)->h>>1));
        // jos menu on main
        if (Md->Pl[Screen].Menu==MENU_MAIN)
        {
            // piirretään menu mainin teksti
            textout(Scr, (FONT*) Dat[FONT1].dat, Menu1text[Md->Pl[Screen].Select[Md->Pl[Screen].Menu]], Clipx1+40, 20, -1);
        } // if (Md->Pl[Screen].Menu==MENU_MAIN)
        // jos ollaan ostomenussa
        if ((Md->Pl[Screen].Menu==MENU_BUY) || (Md->Pl[Screen].Menu==MENU_BUYWEAPONS)|| (Md->Pl[Screen].Menu==MENU_BUYPROJECTW) || (Md->Pl[Screen].Menu==MENU_BUYENERGYW) || (Md->Pl[Screen].Menu==MENU_BUYBOMBS) || (Md->Pl[Screen].Menu==MENU_BUYTOOLS)  || (Md->Pl[Screen].Menu==MENU_BUYAMMO) ||(Md->Pl[Screen].Menu == MENU_BUYBUILD) ||(Md->Pl[Screen].Menu == MENU_BUYARMOR) || (Md->Pl[Screen].Menu == MENU_BUYTOOLS2) || (Md->Pl[Screen].Menu==MENU_BUYVEHICLES))
        {
            // jos ei voida ostaa niin palataan takaisin
            if (Md->Pl[Screen].Canbuy == false) Md->Pl[Screen].Menu = MENU_MAIN;
            // piirretään menuikonit
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYWEAPONS].dat, Clipx1 + (Clipx>>1)-18-(((BITMAP * ) Dat[DATMENUBUYWEAPONS].dat)->w>>1), (Clipy>>1)-30-(((BITMAP * ) Dat[DATMENUBUYWEAPONS].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYAMMO].dat, Clipx1 + (Clipx>>1)-(((BITMAP * ) Dat[DATMENUBUYAMMO].dat)->w>>1), (Clipy>>1)-30-(((BITMAP * ) Dat[DATMENUBUYAMMO].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYTOOLS].dat, Clipx1 + (Clipx>>1)+18-(((BITMAP * ) Dat[DATMENUBUYTOOLS].dat)->w>>1), (Clipy>>1)-30-(((BITMAP * ) Dat[DATMENUBUYTOOLS].dat)->h>>1));
            // ****
            // piirretään teksti jos ollaan buy menussa
            if (Md->Pl[Screen].Menu==MENU_BUY)
                textout(Scr, (FONT*) Dat[FONT1].dat, Menu2text[Md->Pl[Screen].Select[Md->Pl[Screen].Menu]], Clipx1+40, 20, -1);
        } // if (Md->Pl[Screen].Menu==MENU_BUY)
        // aseidenostomenu
        if ((Md->Pl[Screen].Menu==MENU_BUYWEAPONS) || (Md->Pl[Screen].Menu==MENU_BUYPROJECTW) || (Md->Pl[Screen].Menu==MENU_BUYENERGYW) || (Md->Pl[Screen].Menu==MENU_BUYBOMBS))
        {
            // jos ei voi ostaa niin palataan takaisin
            if (Md->Pl[Screen].Canbuy == false) Md->Pl[Screen].Menu = MENU_MAIN;
            // piirretään menuikonit
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYPROJECTW].dat, Clipx1 + (Clipx>>1)-18-(((BITMAP * ) Dat[DATMENUBUYPROJECTW].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUYPROJECTW].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYENERGYW].dat, Clipx1 + (Clipx>>1)-(((BITMAP * ) Dat[DATMENUBUYENERGYW].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUYENERGYW].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYBOMB].dat, Clipx1 + (Clipx>>1)+18-(((BITMAP * ) Dat[DATMENUBUYBOMB].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUYBOMB].dat)->h>>1));
            // ****
            // jos ollaan buyweapons menussa niin piirretään teksti
            if (Md->Pl[Screen].Menu==MENU_BUYWEAPONS)
                textout(Scr, (FONT*) Dat[FONT1].dat, Menu3text[Md->Pl[Screen].Select[Md->Pl[Screen].Menu]], Clipx1+40, 20, -1);
        } // if (Md->Pl[Screen].Menu==MENU_BUYWEAPONS)
        if (Md->Pl[Screen].Menu==MENU_BUYPROJECTW)
        {
            // jos ei voida ostaa niin palataan takaisin
            if (Md->Pl[Screen].Canbuy == false) Md->Pl[Screen].Menu = MENU_MAIN;
            // piirretään menuikonit
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYPISTOL].dat, Clipx1 + (Clipx>>1)-54-(((BITMAP * ) Dat[DATMENUBUYPISTOL].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYPISTOL].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYMAGNUM].dat, Clipx1 + (Clipx>>1)-36-(((BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYSHOTGUN].dat, Clipx1 + (Clipx>>1)-18-(((BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYSUBMACHINEGUN].dat, Clipx1 + (Clipx>>1)-(((BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat, Clipx1 + (Clipx>>1)+18-(((BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYBAZOOKA].dat, Clipx1 + (Clipx>>1)+36-(((BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYHMISLAUNCHER].dat, Clipx1 + (Clipx>>1)+54-(((BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYSNIPER].dat, Clipx1 + (Clipx>>1)+72-(((BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYMACHINEGUN].dat)->h>>1));
            // ****
            // jos ollaan projektiiliaseiden ostomenussa niin piirretään teksti
            if (Md->Pl[Screen].Menu==MENU_BUYPROJECTW)
            {
                textout(Scr, (FONT*) Dat[FONT1].dat, Menu4text[Md->Pl[Screen].Select[Md->Pl[Screen].Menu]], Clipx1+40, 20, -1);
                textout(Scr, (FONT*) Dat[FONT1].dat, Menu4text2[Md->Pl[Screen].Select[Md->Pl[Screen].Menu]], Clipx1+40, 40, -1);
            } // if (Md->Pl[Screen].Menu==MENU_BUYPROJECTW)
        } // if (Md->Pl[Screen].Menu==MENU_BUYPROJECTW)
        if (Md->Pl[Screen].Menu==MENU_BUYENERGYW)
        {
            // jos ei voida ostaa niin palataan takaisin
            if (Md->Pl[Screen].Canbuy == false) Md->Pl[Screen].Menu = MENU_MAIN;
            // piirretään menuikonit
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYLASERSABRE].dat, Clipx1 + (Clipx>>1)-18-(((BITMAP * ) Dat[DATMENUBUYPISTOL].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYPISTOL].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYLASERPISTOL].dat, Clipx1 + (Clipx>>1)-(((BITMAP * ) Dat[DATMENUBUYPISTOL].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYPISTOL].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYLASERRIFLE].dat, Clipx1 + (Clipx>>1)+18-(((BITMAP * ) Dat[DATMENUBUYPISTOL].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYPISTOL].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYLASERCANNON].dat, Clipx1 + (Clipx>>1)+36-(((BITMAP * ) Dat[DATMENUBUYPISTOL].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYPISTOL].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYPLASMAPISTOL].dat, Clipx1 + (Clipx>>1)+54-(((BITMAP * ) Dat[DATMENUBUYPISTOL].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYPISTOL].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYHEAVYPLASMA].dat, Clipx1 + (Clipx>>1)+72-(((BITMAP * ) Dat[DATMENUBUYPISTOL].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYPISTOL].dat)->h>>1));
            // ****
            if (Md->Pl[Screen].Menu==MENU_BUYENERGYW)
            {
                textout(Scr, (FONT*) Dat[FONT1].dat, Menu9text[Md->Pl[Screen].Select[Md->Pl[Screen].Menu]], Clipx1+40, 20, -1);
                textout(Scr, (FONT*) Dat[FONT1].dat, Menu9text2[Md->Pl[Screen].Select[Md->Pl[Screen].Menu]], Clipx1+40, 40, -1);
            }
        } // if (Md->Pl[Screen].Menu==MENU_BUYENERGYW)
        if (Md->Pl[Screen].Menu==MENU_BUYBOMBS)
        {
            // jos ei voida ostaa niin palataan takaisin
            if (Md->Pl[Screen].Canbuy == false) Md->Pl[Screen].Menu = MENU_MAIN;
            // piirretään menuikonit
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYGRENADE].dat, Clipx1 + (Clipx>>1)-18-(((BITMAP * ) Dat[DATMENUBUYGRENADE].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYGRENADE].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYLAVABOMB].dat, Clipx1 + (Clipx>>1)-(((BITMAP * ) Dat[DATMENUBUYGRENADE].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYGRENADE].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYSELFDESTRUCTOR].dat, Clipx1 + (Clipx>>1)+18-(((BITMAP * ) Dat[DATMENUBUYGRENADE].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYGRENADE].dat)->h>>1));
            // ****
            if (Md->Pl[Screen].Menu==MENU_BUYBOMBS)
                textout(Scr, (FONT*) Dat[FONT1].dat, Menu8text[Md->Pl[Screen].Select[Md->Pl[Screen].Menu]], Clipx1+40, 20, -1);
        } // if (Md->Pl[Screen].Menu==MENU_BUYPROJECTW)

        // tools menu
        if ((Md->Pl[Screen].Menu==MENU_BUYTOOLS) || (Md->Pl[Screen].Menu==MENU_BUYBUILD) || (Md->Pl[Screen].Menu==MENU_BUYARMOR) || (Md->Pl[Screen].Menu==MENU_BUYTOOLS2) || (Md->Pl[Screen].Menu==MENU_BUYVEHICLES))
        {
            // jos ei voida ostaa niin palataan takaisin
            if (Md->Pl[Screen].Canbuy == false) Md->Pl[Screen].Menu = MENU_MAIN;
            // piirretään menuikonit
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYTOOLSTOOLS].dat, Clipx1 + (Clipx>>1)-18-(((BITMAP * ) Dat[DATMENUBUYTOOLSTOOLS].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUYTOOLSTOOLS].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYBUILD].dat, Clipx1 + (Clipx>>1)-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUARMOR].dat, Clipx1 + (Clipx>>1)+18-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYVEHICLE1].dat, Clipx1 + (Clipx>>1)+36-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->h>>1));
            // ****
            // jos ollaan tavaroiden ostomenussa niin piirretään teksti
            if (Md->Pl[Screen].Menu==MENU_BUYTOOLS)
                textout(Scr, (FONT*) Dat[FONT1].dat, Menu5text[Md->Pl[Screen].Select[Md->Pl[Screen].Menu]], Clipx1+40, 20, -1);
        } // if (Md->Pl[Screen].Menu==MENU_BUYPROJECTW)
        if (Md->Pl[Screen].Menu==MENU_BUYARMOR)
        {
            // jos ei voida ostaa niin palataan takaisin
            if (Md->Pl[Screen].Canbuy == false) Md->Pl[Screen].Menu = MENU_MAIN;
            // piirretään menuikonit
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYHELMET].dat, Clipx1 + (Clipx>>1)-36-(((BITMAP * ) Dat[DATMENUBUYTOOLSTOOLS].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYTOOLSTOOLS].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYVEST].dat, Clipx1 + (Clipx>>1)-18-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYKEVLARPANTS].dat, Clipx1 + (Clipx>>1)-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYHELMET2].dat, Clipx1 + (Clipx>>1)+18-(((BITMAP * ) Dat[DATMENUBUYTOOLSTOOLS].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYTOOLSTOOLS].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYVEST2].dat, Clipx1 + (Clipx>>1)+36-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYKEVLARPANTS2].dat, Clipx1 + (Clipx>>1)+54-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYCAMOUFLAGE].dat, Clipx1 + (Clipx>>1)+72-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->h>>1));
            // ****
            // jos ollaan tavaroiden ostomenussa niin piirretään teksti
            if (Md->Pl[Screen].Menu==MENU_BUYARMOR)
                textout(Scr, (FONT*) Dat[FONT1].dat, Menu10text[Md->Pl[Screen].Select[Md->Pl[Screen].Menu]], Clipx1+40, 20, -1);
        } // if (Md->Pl[Screen].Menu==MENU_BUYPROJECTW)
        if (Md->Pl[Screen].Menu==MENU_BUYTOOLS2)
        {
            // jos ei voida ostaa niin palataan takaisin
            if (Md->Pl[Screen].Canbuy == false) Md->Pl[Screen].Menu = MENU_MAIN;
            // piirretään menuikonit
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYTOOLS].dat, Clipx1 + (Clipx>>1)-18-(((BITMAP * ) Dat[DATMENUBUYTOOLSTOOLS].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYTOOLSTOOLS].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYDRILL].dat, Clipx1 + (Clipx>>1)-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYAIM].dat, Clipx1 + (Clipx>>1)+18-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYMEDIKIT].dat, Clipx1 + (Clipx>>1)+36-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYPARACHUTE].dat, Clipx1 + (Clipx>>1)+54-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->h>>1));
            // ****
            if (Md->Pl[Screen].Menu==MENU_BUYTOOLS2)
                textout(Scr, (FONT*) Dat[FONT1].dat, Menu11text[Md->Pl[Screen].Select[Md->Pl[Screen].Menu]], Clipx1+40, 20, -1);
        } // if (Md->Pl[Screen].Menu==MENU_BUYPROJECTW)
        if (Md->Pl[Screen].Menu==MENU_BUYVEHICLES)
        {
            // jos ei voida ostaa niin palataan takaisin
            if (Md->Pl[Screen].Canbuy == false) Md->Pl[Screen].Menu = MENU_MAIN;
            // piirretään menuikonit
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYVEHICLE1].dat, Clipx1 + (Clipx>>1)-18-(((BITMAP * ) Dat[DATMENUBUYTOOLSTOOLS].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYTOOLSTOOLS].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYVEHICLE2].dat, Clipx1 + (Clipx>>1)-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYBUILD].dat)->h>>1));
            // ****
            if (Md->Pl[Screen].Menu==MENU_BUYVEHICLES)
                textout(Scr, (FONT*) Dat[FONT1].dat, Menu12text[Md->Pl[Screen].Select[Md->Pl[Screen].Menu]], Clipx1+40, 20, -1);
        } // if (Md->Pl[Screen].Menu==MENU_BUYPROJECTW)
        if (Md->Pl[Screen].Menu==MENU_BUYAMMO)
        {
            // jos ei voida ostaa niin palataan takaisin
            if (Md->Pl[Screen].Canbuy == false) Md->Pl[Screen].Menu = MENU_MAIN;
            // piirretään menuikonit
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUY9MM].dat, Clipx1 + (Clipx>>1)-36-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYSHELLS].dat, Clipx1 + (Clipx>>1)-18-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUY45].dat, Clipx1 + (Clipx>>1)-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUY762].dat, Clipx1 + (Clipx>>1)+18-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYBAZOOKAAMMO].dat, Clipx1 + (Clipx>>1)+36-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYHOMER].dat, Clipx1 + (Clipx>>1)+54-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYCELLS].dat, Clipx1 + (Clipx>>1)+72-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYPLASMAPODS].dat, Clipx1 + (Clipx>>1)+90-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->w>>1), (Clipy>>1)-50-(((BITMAP * ) Dat[DATMENUBUY9MM].dat)->h>>1));
            // ***
            // jos ollaan panostenostomenussa niin piirretään teksti
            if (Md->Pl[Screen].Menu==MENU_BUYAMMO)
                textout(Scr, (FONT*) Dat[FONT1].dat, Menu6text[Md->Pl[Screen].Select[Md->Pl[Screen].Menu]], Clipx1+40, 20, -1);
        } // if (Md->Pl[Screen].Menu==MENU_BUYPROJECTW)
        // inventory eli pelaajan tavarat
        if (Md->Pl[Screen].Menu==MENU_INVENTORY)
        {
            int Ax=0, Ay=0; // apukoordi
            for (int i = 0; i < Maxstuff; i++)
            {
                if (Md->Pl[Screen].Inv[i] > -1) // piirretään tavarat
                {
                    if (Itemicon[Md->Pl[Screen].Inv[i]] > -1)
                        draw_trans_sprite(Scr, (BITMAP *) Dat[Itemicon[Md->Pl[Screen].Inv[i]]].dat, Clipx1 + (Clipx>>1) - 90 + Ax*18, (Clipy1+((Clipy2-Clipy1)>>1)) - 125 + Ay*18);
                    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
                    char * s = new char[5]; // varataan muistia
                    memset(s, 0, 5);        // tyhjennetään se
                    itoa(Md->Pl[Screen].Stuff[Md->Pl[Screen].Inv[i]], s, 10); // sijoitetaan Money sinne 10 - järjestelmässä
                    // ja piirretään merkkijono
                    if (Md->Pl[Screen].Stuff[Md->Pl[Screen].Inv[i]]>1)
                        textout_centre(Scr, (FONT*) Dat[SMALLFONT].dat, s, Clipx1 + (Clipx>>1) -90 + Ax*18+9, (Clipy1+((Clipy2-Clipy1)>>1)) - 125 + Ay*18-3, -1);
                    delete s; // wapautetaan muisti
                } // if (Md->Pl[Screen].Inv[i] != -1)
                Ax++;
                if (Ax >= 10) {
                    Ax = 0;
                    Ay++;
                }

                drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);

            } // for (int i = 0; i < Maxstuff; i++)
        } // if (Md->Pl[Screen].Menu==MENU_INVENTORY)
        if (Md->Pl[Screen].Menu == MENU_BUYBUILD)
        {
            // jos ei voida ostaa niin palataan takaisin
            if (Md->Pl[Screen].Canbuy == false) Md->Pl[Screen].Menu = MENU_MAIN;
            // piirretään menuikonit
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYLAVATRAP].dat, Clipx1 + (Clipx>>1)-18-(((BITMAP * ) Dat[DATMENUBUYLAVATRAP].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYLAVATRAP].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYSUPERLAVATRAP].dat, Clipx1 + (Clipx>>1)-(((BITMAP * ) Dat[DATMENUBUYSUPERLAVATRAP].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYSUPERLAVATRAP].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYWHITEPLATE].dat, Clipx1 + (Clipx>>1)+18-(((BITMAP * ) Dat[DATMENUBUYSUPERLAVATRAP].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYSUPERLAVATRAP].dat)->h>>1));
            draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBUYGRAYPLATE].dat, Clipx1 + (Clipx>>1)+36-(((BITMAP * ) Dat[DATMENUBUYSUPERLAVATRAP].dat)->w>>1), (Clipy>>1)-70-(((BITMAP * ) Dat[DATMENUBUYSUPERLAVATRAP].dat)->h>>1));
            // ***
            textout(Scr, (FONT*) Dat[FONT1].dat, Menu7text[Md->Pl[Screen].Select[Md->Pl[Screen].Menu]], Clipx1+40, 20, -1);
        } // (Md->Pl[Screen].Menu == MENU_BUYBUILD)
        // piirretään kohdistin
        draw_trans_sprite(Scr, (BITMAP * ) Dat[DATMENUBOX].dat, Clipx1 + (Clipx>>1)+Md->Pl[Screen].Selectx-(((BITMAP * ) Dat[DATMENUBOX].dat)->w>>1), (Clipy>>1)-10-(((BITMAP * ) Dat[DATMENUBOX].dat)->h>>1)+Md->Pl[Screen].Selecty);
    } // if (Md->Pl[Screen].Menu>-1)
} // Draw_Menus(int Screen)
void Do_drawings()
{
    // kaikki piirto jokaiselle pelaajalle
    for (int Count = 0; Count < Opt->Players; Count++)
    {
        Setclipping(Count);    // clippausrajat
        Draw_Background(Count);// tausta
        Draw_Bullets(Count);   // panokset
        Draw_Buildings(Count); // rakennukset
        Draw_Bots(Count);   // botit
        Draw_vehicles(Count); // autot
        Draw_Players(Count);   // pelaajat


        Draw_Lava(Count);      // laava
        Draw_Explosions(Count);// räjähdykset
        Draw_Playerdata(Count);// pelaajan hud
        Draw_Menus(Count);     // ja menut
    } // for (int Count = 0; Count < Opt->Players; Count++)
    Setclipping(-1);
//     textprintf(Scr, font, 0, SCREEN_Y-10, 15, "Fps: %f", Fps);
} // Do_drawings()
#endif

void Setclipping(int mode)
{
    // Asetetaan clippausrajat riippuen pelaajamäärästä ja pelaajasta
    switch (Opt->Players)
    {
        // jos vain yksi pelaaja niin koko ruutu
    case 1:
        Clipx = SCREEN_X;
        Clipy = SCREEN_Y;
        Clipx1 = 0;
        Clipy1 = 0;
        Clipx2 = SCREEN_X;
        Clipy2 = SCREEN_Y;
        break;
        // jos kaksi niin puolet ruudusta
    case 2:
        Clipx = SCREEN_X>>1;
        Clipy = SCREEN_Y;
        if (mode == 0)
        {
            Clipx1 = 0;
            Clipy1 = 0;
            Clipx2 = SCREEN_X>>1;
            Clipy2 = SCREEN_Y;
        }
        if (mode == 1)
        {
            Clipx1 = SCREEN_X>>1;
            Clipy1 = 0;
            Clipx2 = SCREEN_X;
            Clipy2 = SCREEN_Y;
        }
        break;
        // jos kolme niin 1/3 ruudusta
    case 3:
        Clipx = (SCREEN_X/3);
        Clipy = SCREEN_Y;
        if (mode == 0)
        {
            Clipx1 = 0;
            Clipy1 = 0;
            Clipx2 = 1+(SCREEN_X/3);
            Clipy2 = SCREEN_Y;
        }
        if (mode == 1)
        {
            Clipx1 = 1+(SCREEN_X/3);
            Clipy1 = 0;
            Clipx2 = 1+(SCREEN_X/3*2);
            Clipy2 = SCREEN_Y;
        }
        if (mode == 2)
        {
            Clipx1 = 1+(SCREEN_X/3*2);
            Clipy1 = 0;
            Clipx2 = SCREEN_X;
            Clipy2 = SCREEN_Y;
        }
        break;

    }; // switch Opt->Players
    // koko ruutu jos ei pelaajaa valittu
    if (mode == -1)
    {
        Clipx1 = 0;
        Clipy1 = 0;
        Clipx2 = SCREEN_X;
        Clipy2 = SCREEN_Y;
    } // if (mode == -1)
    set_clip(Scr, Clipx1, Clipy1, Clipx2, Clipy2);
} // Setclipping
void Save(char * S)
{
    // Kartan tallennus


    // avataan tiedosto
    PACKFILE * f = pack_fopen(S, "wp");
    Lev->Version = 4;
    // nollataan karttaobjektien määrä
    Lev->Mapobjects =0;

    // sitten lasketaan monta niitä on
    for (int i = 0; i < Maxobjects; i++)
        if (Md->Obj[i].Live) Lev->Mapobjects++;

    // tallennetaan "headeri"
    pack_fwrite(Lev, sizeof(Tlevel),  f);

    // sitten karttapalat
    for (int i = 0; i < Maxobjects; i++)
        if (Md->Obj[i].Live) pack_fwrite(&Md->Obj[i],sizeof(Tobject),  f);
    // monta on spirejä..
    int apu = 0;
    // lasketaan spiret
    for (int i = 0; i < Maxspires; i++)
        if (Md->Spire[i].Live) apu++;
    // tallennetaan spirejen lukumäärä
    pack_fwrite(&apu, sizeof(apu), f);
    // tallennetaan spiret
    for (int i = 0; i < Maxspires; i++)
        if (Md->Spire[i].Live) pack_fwrite(&Md->Spire[i], sizeof(Tspire), f);
    // suljetaan tiedosto

    // Textuurin nimi
    pack_fwrite(&Add->Texturename, 32, f);
    apu = 0;
    for (int i = 0; i < Maxeditdata; i++)
        if (Md->Editdata[i].Live)
            apu++;
    pack_fwrite(&apu, sizeof(apu), f);
    for (int i = 0; i < Maxeditdata; i++)
        if (Md->Editdata[i].Live)
            pack_fwrite(&Md->Editdata[i], sizeof(Teditordata), f);


    pack_fclose(f);
} // Save(char * S)
unsigned char * Get_texture_colors(BITMAP * Tex, int *Colors)
{
    int colors = 0;
    unsigned char * Color=0;
    int C;
    char Hepcolor[255]= {0};
    bool Found = false;
    int Size = 199;
    for (int y = 0; y < Tex->h; y++)
    {
        for (int x = 0; x < Tex->w; x++)
        {
            Hepcolor[Tex->line[y][x]] = 1;
        } //   for (int y = 0; y < Tex->h; y++)   for (int x = 0; x < Tex->w; x++)
    }

    for (int i = 0; i < 255; i++)
        if (Hepcolor[i]) colors++;
    Color = new unsigned char[colors*2];
    int i2 = 0;
    for (int i = 0; i < 255; i++)
        if (Hepcolor[i])
            Color[i2++] = i;
    for (int i3 = 0; i3 < colors; i3++)
        Color[colors+i3] = color_map->data[Color[i3]][192];
    colors *= 2;

    *Colors = colors;
    return Color;
} // char * Get_texture_colors(BITMAP * Tex)

void Put_texture()
{
    BITMAP * Tex = load_pcx(Add->Texturename, 0);
    int Max = Lev->Mapsizey*Opt->Texturedearth;
    int Size=199;
    rect(Scr, (SCREEN_X>>1)-(Size>>1)+1, (SCREEN_Y>>1)+20-5+1, (SCREEN_X>>1)+(Size>>1)-1, (SCREEN_Y>>1)+20+5-1, 22);
    rect(Scr, (SCREEN_X>>1)-(Size>>1), (SCREEN_Y>>1)+20-5, (SCREEN_X>>1)+(Size>>1), (SCREEN_Y>>1)+20+5, 21);
    rect(Scr, (SCREEN_X>>1)-(Size>>1)-1, (SCREEN_Y>>1)+20-5-1, (SCREEN_X>>1)+(Size>>1)+1, (SCREEN_Y>>1)+20+5+1, 22);
    for (int y = 0; y < Lev->Mapsizey; y++)
    {
        for (int x = 0; x < Lev->Mapsizex; x++)
        {
            if (Md->Map->line[y][x]>=232)
                if (Md->Map->line[y][x]<=234)
                    Md->Map->line[y][x] = Tex->line[y%Tex->h][x%Tex->w];
        } //   for (int y = 0; y < Lev->Mapsizey; y++)   for (int x = 0; x < Lev->Mapsizex; x++)
        if (y%10 == 0)
        {
            rect(Scr, (SCREEN_X>>1)-(Size>>1)+1, (SCREEN_Y>>1)+20-5+2, (SCREEN_X>>1)-(Size>>1)+1+(y*Size/(Max)), (SCREEN_Y>>1)+20+5-1, 23);
            Upscr();
        } // if (y%20 == 0)

    }

    int Colors = 0;
    unsigned char * Color = Get_texture_colors(Tex, &Colors);
    bool Upd = false;
    int C;
    color_map = &light_table;
    bool Isit = false;
    if (Opt->Texturedearth > 1)
        for (int y = 0; y < Lev->Mapsizey; y++)
        {
            for (int x = 0; x < Lev->Mapsizex; x++)
            {
                IN_HALF_COLORS(Color, Colors, Md->Map->line[y][x], Isit);
                if (Isit)
                {

                    Upd = false;
                    FAST_GETPIXEL(Md->Map, x-4, y-4, C);
                    IN_COLORS(Color, Colors, C, Isit);
                    if (!Isit) Upd = true;
                    FAST_GETPIXEL(Md->Map, x+4, y-4, C);
                    IN_COLORS(Color, Colors, C, Isit);
                    if (!Isit) Upd = true;
                    FAST_GETPIXEL(Md->Map, x-4, y+4, C);
                    IN_COLORS(Color, Colors, C, Isit);
                    if (!Isit) Upd = true;
                    FAST_GETPIXEL(Md->Map, x+4, y+4, C);
                    IN_COLORS(Color, Colors, C, Isit);
                    if (!Isit) Upd = true;
                    if (Upd)
                    {
                        Md->Map->line[y][x]++; //= color_map->data[128][Md->Map->line[y][x]];
                    }
//         Md->Map->line[y][x]++;
                }
            } //   for (int x = 0; x < Lev->Mapsizex; x++)
            if (y%10 == 0)
            {
                rect(Scr, (SCREEN_X>>1)-(Size>>1)+1, (SCREEN_Y>>1)+20-5+2, (SCREEN_X>>1)-(Size>>1)+1+((y+Lev->Mapsizey)*Size/(Max)), (SCREEN_Y>>1)+20+5-1, 23);
                Upscr();
            } // if (y%10 == 0)
        } // for (int y = 0; y < Lev->Mapsizey; y++)
    color_map = &rgb_table;
    delete Color;
    destroy_bitmap(Tex);
} // void Put_texture()

void Createparallax()
{
    clear(Scr);
    Upscr();
    fade_out(64);
    textout_centre(Scr, (FONT*) Dat[FONT1].dat, "Loading...", SCREEN_X>>1, (SCREEN_Y>>1)-10, -1);
    Upscr();
    fade_in((PALETTE) Dat[DATPALETTE].dat, 6);
    if(Opt->Texturedearth)
        Put_texture();
    clear(Parallax);
    BITMAP * Apu;
    {
        Apu = create_bitmap(Parallax->w, Parallax->h);
        clear(Apu);
        stretch_sprite(Apu, Md->Map, 0, 0, Lev->Mapsizex>>1, Lev->Mapsizey>>1);

        color_map = &light_table;
        draw_lit_sprite(Parallax, Apu, 0, 0, 128);
        color_map = &rgb_table;
        destroy_bitmap(Apu);
    }
    Setclipping(-1);
    {
        Apu = create_bitmap((Clipx>>1), Lev->Mapsizey>>1);
        clear(Apu);
        blit(Parallax, Apu, (Lev->Mapsizex>>1)-(Clipx>>1), 0, 0, 0, (Clipx>>1), Lev->Mapsizey>>1);
        draw_sprite_h_flip(Parallax, Apu, (Lev->Mapsizex>>1), 0);
        destroy_bitmap(Apu);
    }
    {
        Apu = create_bitmap(Lev->Mapsizex>>1, Clipy>>1);
        clear(Apu);
        blit(Parallax, Apu, 0, (Lev->Mapsizey>>1)-(Clipy>>1), 0, 0, Lev->Mapsizex>>1, (Clipy>>1));
        draw_sprite_v_flip(Parallax, Apu, 0, (Lev->Mapsizey>>1));
        destroy_bitmap(Apu);
    }
    {
        Apu = create_bitmap(Clipx>>1, Clipy>>1);
        clear(Apu);
        blit(Parallax, Apu, (Lev->Mapsizex>>1)-(Clipx>>1), (Lev->Mapsizey>>1)-(Clipy>>1), 0, 0, (Clipx>>1), (Clipy>>1));
        draw_sprite_vh_flip(Parallax, Apu, (Lev->Mapsizex>>1), (Lev->Mapsizey>>1));
        destroy_bitmap(Apu);
    }
    // TODO Replace this fadeout with something else later.
    /*
    do
    {
        mp_volume--;
        for (int i = 0; i < 20; i++) vsync();
    } while (mp_volume > 0); */
    fade_out(6);
    clear(Scr);
    Upscr();


} // void Createparallax()

void Load(char * S)
{
    // nollataan spiret
    memset(&Md->Spire, 0, sizeof(Tspire) * Maxspires);
    // avataan tiedosto
    PACKFILE * f = pack_fopen(S, "rp");
    // jos avaaminen onnistui
    if (f)
    {
        // luetaan headeri
        pack_fread(Lev, sizeof(Tlevel),  f);
        // nollataan karttapalat
        for(int i = 0; i < Maxobjects; i++)
        {
            Md->Obj[i].Live= false;
        }
        // jos versio on 1 tai suurempi
        if (Lev->Version >= 1)
        {
            // luetaan karttapalat
            for (int i = 0; i < Lev->Mapobjects; i++)
                pack_fread(&Md->Obj[i],sizeof(Tobject),  f);
        } // Lev->Version >= 1
        // jos versio on 2 tai suurempi
        if (Lev->Version >= 2)
        {
            int apu;
            // spirejen lukumäärä
            pack_fread(&apu, sizeof(apu), f);
            // ja luetaan spiret
            for (int i = 0; i < apu; i++)
                pack_fread(&Md->Spire[i], sizeof(Tspire), f);
        } // if (Lev->Version >= 2)
        if (Lev->Version >= 3)
        {
            // Textuurin nimi
            pack_fread(&Add->Texturename, 32, f);
        } else // if (Lev->Version >= 3)
            strcpy(Add->Texturename, "texture1.pcx");
        if (Lev->Version >= 4)
        {
            int apu;
            pack_fread(&apu, sizeof(apu), f);
            memset(&Md->Editdata, 0, sizeof(Teditordata)*Maxeditdata);
            for (int i = 0; i < apu; i++)
                pack_fread(&Md->Editdata[i], sizeof(Teditordata), f);

        } // if (Lev->Version >= 4)
        // suljetaan tiedosto
        pack_fclose(f);
    } // (f)
    // asetetaan kartan koko
    Setmapsize(Lev->Mapsizex, Lev->Mapsizey);
    // tehdään uusi burn taulukko
    if (Burn) delete Burn;
    Burn = new char[(Lev->Mapsizex>>2)*(Lev->Mapsizey>>2)];
    memset(Burn, 0, (Lev->Mapsizex>>2)*(Lev->Mapsizey>>2));
    // *****
    Updatemap();

//    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
//    rectfill(Parallax, 0, 0, Parallax->w, Parallax->h, 30);
//    drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);

    // piirretään karttapalat kartalle
} // Load(char * S)
void Insertobject(int X, int Y, int type)
{
    // aseta uusi karttapala(karttaeditori käyttää tätä)
    for (int i =0; i < Maxobjects; i++)
        if (Md->Obj[i].Live==false)
        {
            Md->Obj[i].X    = X;
            Md->Obj[i].Y    = Y;
            Md->Obj[i].Type = type;
            Md->Obj[i].Live = true;
            i = Maxobjects;
        } // if (Md->Obj[i].Live==false)
} // Insertobject
void Deleteobject(int X, int Y)
{
    BITMAP * apu;
    // tuhoaa karttapalan
    for (int i =Maxobjects-1; i >= 0; i--)
    {
        apu = (BITMAP *) Dat[DATMAP0001+Md->Obj[i].Type].dat;
        if (Md->Obj[i].Live==true)
            if (X > Md->Obj[i].X )
                if (Y > Md->Obj[i].Y)
                    if (X < Md->Obj[i].X + (apu->w))
                        if (Y < Md->Obj[i].Y + (apu->h))
                        {
                            Md->Obj[i].Live = false;
                            i = 0;
                        } // if (Md->Obj[i].Live==false)
    } //for
} // Deleteobject
void Setmapsize(int X, int Y)
{
    // muuttaa kartan kokoa
    BITMAP * apu =Md->Map;
    if (Parallax) destroy_bitmap(Parallax);
    int psizex = (X>>1)+(SCREEN_X>>1);
    int psizey = (Y>>1)+(SCREEN_Y>>1);
    Parallax = create_bitmap(psizex, psizey);
    Md->Map = create_bitmap(X, Y);
    clear(Md->Map);
    Lev->Mapsizex = X;
    Lev->Mapsizey = Y;
    destroy_bitmap(apu);
} // Setmapsize

void Updatemap()
{
    // ** piirtää karttapalat kartalle **

    // tyhjentää kartan
    clear(Md->Map);
    // piirtää palat
    for (int i= 0; i < Maxobjects; i ++)
        if (Md->Obj[i].Live)
            draw_sprite(Md->Map, (BITMAP*) Dat[DATMAP0001+Md->Obj[i].Type].dat, Md->Obj[i].X,Md->Obj[i].Y);
} // Updatemap
void Showmap(int X1, int Y1, int X2, int Y2, int X, int Y)
{
    // näyttää palan karttaa
    //
    // .......................... X ja Y ovat koordi pelin kartalla
    // .   X1, Y1               . X?, Y? ovat koordi näytöllä
    // .    .......             .
    // .    .X, Y .             .
    // .    .......X2, Y2       .
    // .                        .
    // ..........................
    if (Opt->Parallax == true)
    {
        int px = X>>1;
        int py = Y>>1;
        blit(Parallax, Scr, px, py, X1, Y1, X2-X1, Y2-Y1);
        masked_blit(Md->Map, Scr, X, Y, X1, Y1, X2-X1, Y2-Y1);
    } else
        blit(Md->Map, Scr, X, Y, X1, Y1, X2-X1, Y2-Y1);
} // Showmap(int X1, int Y1, int X2, int Y2, int X, int Y)

void InitEngine()
{
    // alustaa pelidatan
    Md = new Tmaindat;
    memset(Md, 0, sizeof(Tmaindat));
    Lev = new Tlevel;
    memset(Lev, 0, sizeof(Tlevel));
    Add = new Tadditional_data;
    memset(Add, 0, sizeof(Tadditional_data));
    Setclipping(-1);
    // *****
    for (int i = 0; i < MAXRANDOM; i++)
        Random[i] = rand();
    LOCK_FUNCTION(Keyboard_timer_routine);
    LOCK_VARIABLE(Keyboard_update_counter);
    LOCK_VARIABLE(Game_logic_update_counter);
    install_int(Keyboard_timer_routine, 6);
    LOCK_FUNCTION(Game_logic_timer_routine);
    if (Opt->Fps == 0)
        Opt->Fps = 40;
    install_int_ex(Game_logic_timer_routine, BPS_TO_TIMER(Opt->Fps));
} // InitEngine
void DeInitEngine()
{
    remove_int(Keyboard_timer_routine);
    // vapauttaa muistin
    delete Md;
    delete Lev;
    delete Add;
} // DeInitEngine
#ifndef EDITOR
void Defaults()                 // Options asetusten resetointi
{
    memset(Opt, 0, sizeof(Toptions));
    Opt->Texturedearth = 2;
    Opt->Musicvolume = 50;    // ääntä
    Opt->sound.Soundvolume = 100;
    Opt->Sndfreq = 44100;     // Laatua
    Opt->Bits16 = true;       // 16Bittinen tottakai
    Opt->Interpolated = true; // interpoloitu
    Opt->Sound = true;        // Ja vielä päälle
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
    Opt->Realistic_falling_damage = true;

    Opt->Gametype  = GAMETYPE_DEATHMATCH;
    Opt->Fraglimit = 10;
    Opt->Bots = 0;
    Opt->Botdifficulty = 1;
    Opt->Startcash = 20000;        // Rahhaa 5000
    Opt->Lives = 5;               // elämiä 5
    Opt->Fps = 40;
} // Defaults
#endif
#endif
