
/*
 Volcano 2 The great peli.
 (C) 1999 Tero Laitinen /Replica§
*/

unsigned _stklen = 16834*1024;

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <allegro.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <sstream>

#include "sound.h"    // äänihommelit
#include "util.h"

/*-----------------------------------------------------
 * Globals
 *----------------------------------------------------*/

bool Done = false; // Jos done == True niin veks pois hus
bool Exit = false;
bool Mustfadein = false;

// Timer, hmm... esimerkiksi soundien katkaisun ajoitus

// Multi, Frameskip... hitaammille koneille  kuinka monta kertaa päivitetään
// pelilogiikkaa ennen ruudunpäivitystä

// Lavatimer, laavan "päivittämistä" varten

int Timer, Multi = 0, Lavatimer;
int Curmenu = 0;
int Filescroll = 0;

// Names of *.map files, populated in Searchfiles()
// (hopefully) just an temporary hack
std::vector<std::string> mapFilenames;

/* Modules lacking compilation unit ... */

#include "types.h"    // tyyppimäärittelyt pelihahmot laavat maailma
#include "data.h"     // rutiinit datafilejen avaamista varten
#include "common.h"   // yleistä löpinää esim InitAllegro() löytyy täältä
#include "itemdata.h" // tavaroiden teknisemmät tiedot
#include "graph.h"    // omat graffarutiinit sekä InitGraph()
#include "engine.h"   // Pelimoottori(kaikki pelilogiikka ja piirtäminen)
#include "items.h"    // tiettyjen tavaroiden käyttämisfunktiot
#include "control.h"  // pelaajien kontrollointi


void Sayhello();                   // tervetulotoivotus
int main(int Argc, char ** Args); // pääohjelma
void Searchfiles();                // etsii .map päätteiset tiedostot
void Burntitle(BITMAP * bmp);      // Logon poltto
void Menutexts();                  // valikon tekstit
void Menu();                       // valikko
void Update_timers();              // Timereiden päivitys
void Game();                       // pääluuppi


void Sayhello()
{
  
    check_cpu();  // tarkistaa cpu:n tyypin
    if (cpu_mmx)  // jos mmx
    {
        printf("\nMMX found.");
    } // if (cpu_mmx)
    char * s;
    switch(os_type) // käyttis
    {
    case  OSTYPE_UNKNOWN :
        s = "unknown, or regular MSDOS";
        break;
    case  OSTYPE_WIN3    :
        s = "Windows 3.1 or earlier";
        break;
    case  OSTYPE_WIN95   :
        s = "Windows 95";
        break;
    case  OSTYPE_WIN98   :
        s = "Windows 98";
        break;
    case  OSTYPE_WINNT   :
        s = "Windows NT";
        break;
    case  OSTYPE_OS2     :
        s = "OS/2";
        break;
    case  OSTYPE_WARP    :
        s = "OS/2 Warp 3";
        break;
    case  OSTYPE_DOSEMU  :
        s = "Linux DOSEMU";
        break;
    case  OSTYPE_OPENDOS :
        s = "Caldera OpenDOS";
        break;
    default:
        s = "undetected";
        break;
    };
    printf("\nOperating system: %s", s);
    if (cpu_fpu) // fpu löyty
        printf("\nFloating point processor found.");
    fflush(stdout);
} // Sayhello
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

int main(int Argc, char ** Args)
{
    key_led_flag = 0; // numlockit capslock scrolllockit hus veks pois
    if (Argc > 1) Multi = atoi(Args[1]); // parametri (siis frameskip)
    InitAllegro(); // Allegro hyrräämään

    Sayhello();    // Terve
    if (file_exists("Options.cfg", 0, 0)) Loadoptions();
    else {
        Defaults();
    }

    if (Opt->sound.Sound) Init_Music(&Opt->sound); // Lataa module
    printf ("\nPress any key to continue");
    fflush(stdout);
    fade_out (4);

    InitData();   // Lataa graffat paletit ja muuta kivaa
    SCREEN_X = Opt->Xres;
    SCREEN_Y = Opt->Yres;
    InitGraph();  // Graffatila päälle
    InitEngine(); // Moottorin muistinvaraukset

    Menu();
    Saveoptions();
    if (Opt->sound.Sound) DeInit_Music(); // Vapautetaan musat
    DeInitEngine(); // Vapautetaan mootorin muistinvaraukset
    DeInitGraph();  // Graffatila pois ja tekstitila päälle
    DeInitData();   // Vapautetaan vielä vähän muistia
    DeInitAllegro();// Ja allegro pois päältä

	return 0;
} // main

/**
 * Populates the global vector<string> mapFilenames
 *
 * TODO: remove (hack)
 */
void Searchfiles()
{
    mapFilenames.clear();

    DIR* dirStream = opendir(".");
    struct dirent* entry = new dirent;
    struct dirent* next;

    readdir_r(dirStream, entry, &next);
    while (next) {
        std::string filename(next->d_name);
        std::string extension(".map");

        bool isMapFile = false;
        if(filename.length() > extension.length()) {
            size_t extPos = filename.length() - extension.length();
            std::string end = filename.substr(extPos);
            for(size_t i = 0; i < end.length(); i++) {
                end[i] = tolower(end[i]);
            }

            isMapFile = (end == extension);
        }

        if(isMapFile) {
            mapFilenames.push_back(filename);
        }

        readdir_r(dirStream, entry, &next);
    }
    
    closedir(dirStream);
    delete entry;
} // void Searchfiles()

void Burntitle(BITMAP * bmp)
{
    int c, c1, c2, c3, c4, c5;
    for (int x = (bmp->w>>1)-270; x < (bmp->w>>1)+270; x++)
        for (int y = 31; y < 180; y++)
        {
            c = bmp->line[y+1][x-1];
            c1 = bmp->line[y+1][x];
            c2 = bmp->line[y+1][x+1];
            c3 = bmp->line[y][x-1];
            c4 = bmp->line[y][x+1];
            c5 = bmp->line[y+2][x];
            c = (c+c1+c2+c3+c4+c5)/6;
            if (c) c += -3+Rand()%7;
            c-=2;
            if (c > 192) c = 192;
            bmp->line[y][x] = 0;
            if (c>0)
                bmp->line[y][x] = c;
        } //   for (int y = 0; y < bmp->h; y++)   for (int x = 0; x < bmp->w; x++)
} // void Burntitle(BITMAP * bmp)

/**
 * Used to setup keys
 *
 * @return scancode
 */
int Getkey()
{    
    return readkey()>>8;
}

void Menutexts()
{
    int Length = 0;
    char * s = 0;
    char s2[20];
    std::string textbuffer;
    switch(Curmenu)
    {
    case 0:// Mainmenu
        s = "Start new game";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 220, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 220, (SCREEN_X>>1)+(Length>>1), 240))
            if (Mob==0) if (Moldb==1)
                {
                    if (Opt->Fileselected >= 0) if (Opt->Fileselected < mapFilenames.size())
                        {
                            Done = false;
                            Game();
                            StartMenuMusic();
                            fade_out(6);
                            clear(Scr);
                            draw_rle_sprite(Scr, (RLE_SPRITE*) Dat[TITLE].dat, (SCREEN_X>>1)-(((RLE_SPRITE*) Dat[TITLE].dat)->w>>1), 125-(((RLE_SPRITE*) Dat[TITLE].dat)->h>>1));
                            Burntitle(Scr);
                            textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 220, -1);
                            draw_sprite(Scr, (BITMAP*) Dat[TITLECOPYRIGHT].dat, SCREEN_X-((BITMAP*) Dat[TITLECOPYRIGHT].dat)->w, SCREEN_Y-10-((BITMAP*) Dat[TITLECOPYRIGHT].dat)->h);
                            Mustfadein = true;
                            key[KEY_ESC] = 0;
                        } else // Opt->Fileselected
                        {
                            textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, "Please select a valid map.", SCREEN_X>>1, 190, -1);
                        }
                } //       if (Mob==0) if (Moldb==1)
        s = "Options";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 250, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 250, (SCREEN_X>>1)+(Length>>1), 270))
            if (Mob==0) if (Moldb==1) Curmenu = 1;
        s = "Quit";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 280, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 280, (SCREEN_X>>1)+(Length>>1), 300))
            if (Mob==0) if (Moldb==1) Exit = true;
        break; // Mainmenu
    case 1: // Options
    {
        textbuffer = "Players:    ";
        s = &textbuffer[0];
        itoa_fake(Opt->Players, &s[9], 10);
        s[10] = 0;
 
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 220, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 220, (SCREEN_X>>1)+(Length>>1), 240))     if (Mob==0) if (Moldb==1)
                {
                    Opt->Players++;
                    if (Opt->Players >= 4) Opt->Players = 1;
                } //       if (Mousein((SCREEN_X>>1)-(Length), 220, (SCREEN_X>>1)+(Length>>1), 240))     if (Mob==0) if (Moldb==1)
        s = new char[40];
        memset(s, 0, 40);
        strcpy(s, "Map: ");
        if (Opt->Fileselected>=0) if (Opt->Fileselected < mapFilenames.size())
                strcat(s, mapFilenames[Opt->Fileselected].c_str());
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 250, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 250, (SCREEN_X>>1)+(Length>>1), 270))     if (Mob==0) if (Moldb==1)
                {
                    Curmenu = 2;
                } //       if (Mousein((SCREEN_X>>1)-(Length), 220, (SCREEN_X>>1)+(Length>>1), 240))     if (Mob==0) if (Moldb==1)
        delete[] s;
        s = "Keys";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 280, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 280, (SCREEN_X>>1)+(Length>>1), 310))     if (Mob==0) if (Moldb==1)
                    Curmenu = 3; // KEYS

        s = "Game options";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 310, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 310, (SCREEN_X>>1)+(Length>>1), 340))     if (Mob==0) if (Moldb==1)
                    Curmenu = 4; // Game options

        s = "Defaults";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 340, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 340, (SCREEN_X>>1)+(Length>>1), 370))     if (Mob==0) if (Moldb==1)
                {
                    memset(Opt, 0, sizeof(Toptions));
                    Defaults();
                }
        s= "Back";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 370, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 370, (SCREEN_X>>1)+(Length>>1), 390))     if (Mob==0) if (Moldb==1)
                    Curmenu = 0;
    }
    break; // Options
    case 2: // Select map
    {
        s = "Ok.";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 180, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 180, (SCREEN_X>>1)+(Length>>1), 205))     if (Mob==0) if (Moldb==1)
                    Curmenu = 1;
        for (int i = 0; i < 8; i++) if (Filescroll+i < mapFilenames.size()) if (Filescroll+i>=0)
                {
                    s = (char*)mapFilenames[Filescroll+i].c_str();
                    Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
                    textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 215+i*20, -1);
                    if (Mousein((SCREEN_X>>1)-(Length), 220+i*20, (SCREEN_X>>1)+(Length>>1), 238+i*20))
                    {
                        if (Mob == 1) Opt->Fileselected = Filescroll+i;
                    } // Mousein

                    if (Opt->Fileselected == Filescroll+i)
                    {
                        hline(Scr, (SCREEN_X>>1)-(Length>>1), 238+i*20, (SCREEN_X>>1)+(Length>>1), 230);
                        hline(Scr, (SCREEN_X>>1)-(Length>>1), 237+i*20, (SCREEN_X>>1)+(Length>>1), 222);
                    } // if (Opt->Fileselected == Filescroll+i)
                } //       for (int i = 0; i < 8; i++) if (Filescroll+i < Files) if (Filescroll+i>=0)
        if (Filescroll)
        {
            draw_sprite_v_flip(Scr, (BITMAP*) Dat[TITLEARROW].dat, (SCREEN_X>>1)-(((BITMAP*) Dat[TITLEARROW].dat)->w>>1), 200);
            if (Mousein( (SCREEN_X>>1)-(((BITMAP*) Dat[TITLEARROW].dat)->w>>1), 200, (SCREEN_X>>1)+(((BITMAP*) Dat[TITLEARROW].dat)->w>>1), 210))
                if (Mob)
                {
                    Timer++;
                    if (Timer > 8)
                    {
                        Timer = 0;
                        Filescroll--;
                    } // if (Timer > 10)
                } //         if (Mousein( (SCREEN_X>>1)-(((BITMAP*) Dat[TITLEARROW].dat)->w>>1), 380, (SCREEN_X>>1)+(((BITMAP*) Dat[TITLEARROW].dat)->w>>1), 400))
        } // Filescroll
        if (Filescroll+7 < mapFilenames.size()-1)
        {
            draw_sprite(Scr, (BITMAP*) Dat[TITLEARROW].dat, (SCREEN_X>>1)-(((BITMAP*) Dat[TITLEARROW].dat)->w>>1), 380);
            int size = abs( (((BITMAP*) Dat[TITLEARROW].dat)->w>>1));
            int x1 = (SCREEN_X>>1)- size;
            int x2 = (SCREEN_X>>1)+ size;
            if (Mob) if (Mousein(x1 , 380, x2, 400))
                {
                    Timer++;
                    if (Timer > 8)
                    {
                        Timer = 0;
                        Filescroll++;
                    } // if (Timer > 10)
                } //         if (Mousein( (SCREEN_X>>1)-(((BITMAP*) Dat[TITLEARROW].dat)->w>>1), 380, (SCREEN_X>>1)+(((BITMAP*) Dat[TITLEARROW].dat)->w>>1), 400))
        } //       if (Filescroll+8 < Files-1)
    }
    break; // Select map
    case 3: // keys
        s = "Player 1 keys";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 220, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 220, (SCREEN_X>>1)+(Length>>1), 250))     if (Mob==0) if (Moldb==1)
                    Curmenu = 5; // Pl1 keys
        s = "Player 2 keys";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 250, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 250, (SCREEN_X>>1)+(Length>>1), 280))     if (Mob==0) if (Moldb==1)
                    Curmenu = 6; // Pl2 keys
        s = "Player 3 keys";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 280, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 280, (SCREEN_X>>1)+(Length>>1), 310))     if (Mob==0) if (Moldb==1)
                    Curmenu = 7; // Pl3 keys
        s = "Back";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 310, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 310, (SCREEN_X>>1)+(Length>>1), 340))     if (Mob==0) if (Moldb==1)
                    Curmenu = 1;
        break; // Keys
    case 4: // Game options
    {
        s = "Game type:";
        memset(s2, 0, 20);
        strcpy(s2, Gametypename[Opt->Gametype]);
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100-(Length>>1), 180, -1);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 180, -1);
        if (Mousein((SCREEN_X>>1)-100-(Length), 180, (SCREEN_X>>1)+100+(Length), 200)) if (Mob==0) if (Moldb==1)
                {
                    Opt->Gametype ++;
                    if (Opt->Gametype >= MAXGAMETYPES) Opt->Gametype = 0;
                } // if (Mousein((SCREEN_X>>1)-100-(Length), 180, (SCREEN_X>>1)+100+(Length), 200)) if (Mob==0) if (Moldb==1)
        s = "Game type options";
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100-(Length>>1), 200, -1);
        if (Mousein((SCREEN_X>>1)-100-(Length), 200, (SCREEN_X>>1)+100+(Length), 220)) if (Mob==0) if (Moldb==1)
                {
                    Curmenu = 8;
                } // if (Mousein((SCREEN_X>>1)-100-(Length>>1), 180, (SCREEN_X>>1)+100+(Length), 200)) if (Mob==0) if (Moldb==1)

        s = new char[30];
        memset(s, 0, 30);
        strcpy(s, "Start cash: ");
        memset(s2, 0, 10);
        itoa_fake(Opt->Startcash, s2, 10);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100-(Length>>1), 220, -1);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 220, -1);
        delete[] s;
        textbuffer = "FPS:          ";
        s = &textbuffer[0];
        s[12] = 0;
        memset(s2, 0, 10);
        itoa_fake(Opt->Fps, s2, 10);
//      strcat(s, s2);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100-(Length>>1), 240, -1);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 240, -1);
        if (Mousein((SCREEN_X>>1)-100-(Length), 240, (SCREEN_X>>1)+100+(Length), 260))
        {

            if (Mob==0) if (Moldb==1)         Opt->Fps++;
            if (Opt->Fps>=161) Opt->Fps = 1;
            if (Mob==0) if (Moldb==2)         Opt->Fps--;
            if (Opt->Fps<1) Opt->Fps = 10;
        }
        textbuffer = "Parallax:   ";
        s = &textbuffer[0];
        s[12] = 0;
        memset(s2, 0, 10);
        if (Opt->Parallax) strcpy(s2, "On");
        else strcpy(s2, "Off");
//      strcat(s, s2);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100-(Length>>1), 260, -1);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 260, -1);
        if (Mousein((SCREEN_X>>1)-100-(Length), 260, (SCREEN_X>>1)+100+(Length), 280)) if (Mob==0) if (Moldb==1)
                {
                    Opt->Parallax = (Opt->Parallax==false);
                } // if (Mousein((SCREEN_X>>1)-100-(Length), 240, (SCREEN_X>>1)+100+(Length), 260)) if (Mob==0) if (Moldb==1)
        textbuffer = "Lava:   ";
        s = &textbuffer[0];
        s[12] = 0;
        memset(s2, 0, 10);
        if (Opt->Lava) strcpy(s2, "On");
        else strcpy(s2, "Off");
//      strcat(s, s2);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100-(Length>>1), 280, -1);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 280, -1);
        if (Mousein((SCREEN_X>>1)-100-(Length), 280, (SCREEN_X>>1)+100+(Length), 300)) if (Mob==0) if (Moldb==1)
                {
                    Opt->Lava = (Opt->Lava==false);
                } // if (Mousein((SCREEN_X>>1)-100-(Length), 240, (SCREEN_X>>1)+100+(Length), 260)) if (Mob==0) if (Moldb==1)
        {   s= "Textured earth:      ";

            memset(s2, 0, 10);
            itoa_fake(Opt->Texturedearth, s2, 10);
//      strcat(s, s2);
            textout(Scr, (FONT*) Dat[TITLEFONT].dat, "Textured earth:", (SCREEN_X>>1)-100-(Length>>1), 300, -1);
            textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 300, -1);
        }
        if (Mousein((SCREEN_X>>1)-100-(Length), 300, (SCREEN_X>>1)+100+(Length), 320)) if (Mob==0) if (Moldb==1)
                {
                    Opt->Texturedearth++;
                    if (Opt->Texturedearth>2) Opt->Texturedearth = 0;
                } // if (Mousein((SCREEN_X>>1)-100-(Length), 240, (SCREEN_X>>1)+100+(Length), 260)) if (Mob==0) if (Moldb==1)
        s = "Back";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, SCREEN_X>>1, 340, -1);
        if (Mousein((SCREEN_X>>1)-(Length), 340, (SCREEN_X>>1)+(Length), 370))     if (Mob==0) if (Moldb==1)
                    Curmenu = 1;
    }
    if (Mousein((SCREEN_X>>1)-100-(Length>>1), 220, (SCREEN_X>>1)+100+(Length>>1), 250))     if (Mob==0) if (Moldb==1)
            {
                char * s = new char[10];
                itoa_fake(Opt->Startcash, s, 10);
                s = Takestring_centre((SCREEN_X>>1)+100, 220, s, 10, -1, 0);
                Opt->Startcash = atoi(s);
                delete[] s;
            } //        if (Mousein((SCREEN_X>>1)-(Length>>1), 220, (SCREEN_X>>1)+(Length>>1), 250))     if (Mob==0) if (Moldb==1)
    break; // Goptions
    case 5:
    case 6:
    case 7:
    {
        int Pl = Curmenu-5;
        s = "Up: ";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 200, -1);
        if (Mousein((SCREEN_X>>1)-100, 200, (SCREEN_X>>1)+160, 220)) if (Mob==0) if (Moldb==1)
                    Opt->Nap[Pl].Up =  Getkey();
        s = scancode_to_name(Opt->Nap[Pl].Up);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)+100, 200, -1);

        s = "Down: ";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 220, -1);
        if (Mousein((SCREEN_X>>1)-100, 220, (SCREEN_X>>1)+160, 240)) if (Mob==0) if (Moldb==1)
                    Opt->Nap[Pl].Down = Getkey();
        s = scancode_to_name(Opt->Nap[Pl].Down);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)+100, 220, -1);
        s = "Left: ";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 240, -1);
        if (Mousein((SCREEN_X>>1)-100, 240, (SCREEN_X>>1)+160, 260)) if (Mob==0) if (Moldb==1)
                    Opt->Nap[Pl].Left = Getkey();
        s = scancode_to_name(Opt->Nap[Pl].Left);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)+100, 240, -1);
        s = "Right: ";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 260, -1);
        if (Mousein((SCREEN_X>>1)-100, 260, (SCREEN_X>>1)+160, 280)) if (Mob==0) if (Moldb==1)
                    Opt->Nap[Pl].Right = Getkey();
        s = scancode_to_name(Opt->Nap[Pl].Right);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)+100, 260, -1);
        s = "Use: ";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 280, -1);
        if (Mousein((SCREEN_X>>1)-100, 280, (SCREEN_X>>1)+160, 300)) if (Mob==0) if (Moldb==1)
                    Opt->Nap[Pl].Use = Getkey();
        s = scancode_to_name(Opt->Nap[Pl].Use);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)+100, 280, -1);
        s = "Change: ";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 300, -1);
        if (Mousein((SCREEN_X>>1)-100, 300, (SCREEN_X>>1)+160, 320)) if (Mob==0) if (Moldb==1)
                    Opt->Nap[Pl].Change = Getkey();
        s = scancode_to_name(Opt->Nap[Pl].Change);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)+100, 300, -1);
        s = "Jump: ";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 320, -1);
        if (Mousein((SCREEN_X>>1)-100, 320, (SCREEN_X>>1)+160, 340)) if (Mob==0) if (Moldb==1)
                    Opt->Nap[Pl].Jump = Getkey();
        s = scancode_to_name(Opt->Nap[Pl].Jump);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)+100, 320, -1);
        s = "Ninjarope: ";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 340, -1);
        if (Mousein((SCREEN_X>>1)-100, 340, (SCREEN_X>>1)+160, 360)) if (Mob==0) if (Moldb==1)
                    Opt->Nap[Pl].Ninjarope = Getkey();
        s = scancode_to_name(Opt->Nap[Pl].Ninjarope);
        textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)+100, 340, -1);
        s = "Back";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1), 360, -1);
        if (Mousein((SCREEN_X>>1)-100, 360, (SCREEN_X>>1)+160, 380)) if (Mob==0) if (Moldb==1)
                    Curmenu = 3;

    }
    break; // Player keys
    case 8: // Game type options
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, Gametypename[Opt->Gametype], (SCREEN_X>>1), 180, -1);
        switch(Opt->Gametype)
        {
        case GAMETYPE_DEATHMATCH:
        {
            s = "Frag limit:   ";
            memset(s2, 0, 20);
            itoa_fake(Opt->Fraglimit, s2, 10);
            Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
            textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100-(Length>>1), 200, -1);
            textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 200, -1);
            if (Mousein((SCREEN_X>>1)-100-(Length), 200, (SCREEN_X>>1)+100+(Length>>1), 220)) if (Mob==0) if (Moldb)
                    {
                        if (Mob==0) if (Moldb== 1) Opt->Fraglimit +=5;
                        if (Mob==0) if (Moldb== 2) Opt->Fraglimit -=5;
                        if (Opt->Fraglimit >= 200) Opt->Fraglimit = 1;
                        if (Opt->Fraglimit <  1) Opt->Fraglimit = 200;
                    } // if (Mousein((SCREEN_X>>1)-100-(Length), 180, (SCREEN_X>>1)+100+(Length>>1), 200)) if (Mob==0) if (Moldb==1)
            s = "Back";
            Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
            textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1), 360, -1);
            if (Mousein((SCREEN_X>>1)-100, 360, (SCREEN_X>>1)+160, 380)) if (Mob==0) if (Moldb==1)
                        Curmenu = 4;
        }
        break;
        case GAMETYPE_BOTHUNT:
        {
            s = "Bots:     ";
            memset(s2, 0, 20);
            itoa_fake(Opt->Bots, s2, 10);
            Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
            textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100-(Length>>1), 200, -1);
            textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 200, -1);
            if (Mousein((SCREEN_X>>1)-100-(Length), 200, (SCREEN_X>>1)+100+(Length>>1), 220)) if (Mob==0) if (Moldb)
                    {
                        /*         if (Mob==0) if (Moldb== 1) Opt->Bots ++;
                                 if (Mob==0) if (Moldb== 2) Opt->Bots --;
                                 if (Opt->Bots > Maxbots) Opt->Bots = 1;
                                 if (Opt->Bots <  1) Opt->Bots = Maxbots;

                          */
                        Curmenu = 9;
                    } // if (Mousein((SCREEN_X>>1)-100-(Length), 180, (SCREEN_X>>1)+100+(Length>>1), 200)) if (Mob==0) if (Moldb==1)
            s = "Difficulty:   ";
            memset(s2, 0, 20);
            strcpy(s2, Botdifficultyname[Opt->Botdifficulty-1]);
            Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
            textout(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100-(Length>>1), 220, -1);
            textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 220, -1);
            if (Mousein((SCREEN_X>>1)-100-(Length), 220, (SCREEN_X>>1)+100+(Length>>1), 240)) if (Mob==0) if (Moldb)
                    {
                        if (Mob==0) if (Moldb== 1) Opt->Botdifficulty ++;
                        if (Mob==0) if (Moldb== 2) Opt->Botdifficulty --;
                        if (Opt->Botdifficulty > 6) Opt->Botdifficulty = 1;
                        if (Opt->Botdifficulty <  1) Opt->Botdifficulty = 6;
                    } // if (Mousein((SCREEN_X>>1)-100-(Length), 180, (SCREEN_X>>1)+100+(Length>>1), 200)) if (Mob==0) if (Moldb==1)
            s = "Back";
            Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
            textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1), 360, -1);
            if (Mousein((SCREEN_X>>1)-100, 360, (SCREEN_X>>1)+160, 380)) if (Mob==0) if (Moldb==1)
                        Curmenu = 4;
        }
        break;
        };
        break;
    case 9: // Select bot weapons
    {
        memset(s2, 0, 10);
        s = "Pistol bots:";
        itoa_fake(Opt->Botweapons[0], s2, 10);
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 200, -1);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 200, -1);
        if (Mousein((SCREEN_X>>1)-100, 200, (SCREEN_X>>1)+160, 220)) if (Mob==0) if (Moldb)
                {
                    Opt->Bots = 0;
                    for (int i2 = 0; i2 < Difbotweapons; i2++) Opt->Bots += Opt->Botweapons[i2];
                    if (Opt->Bots < Maxbots)
                        if (Moldb==1) Opt->Botweapons[0]++;
                    if (Moldb==2) if (Opt->Botweapons[0]) Opt->Botweapons[0]--;
                }
        memset(s2, 0, 10);
        s = "Magnum bots:";
        itoa_fake(Opt->Botweapons[7], s2, 10);
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 220, -1);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 220, -1);
        if (Mousein((SCREEN_X>>1)-100, 220, (SCREEN_X>>1)+160, 240)) if (Mob==0) if (Moldb)
                {
                    Opt->Bots = 0;
                    for (int i2 = 0; i2 < Difbotweapons; i2++) Opt->Bots += Opt->Botweapons[i2];
                    if (Opt->Bots < Maxbots)
                        if (Moldb==1) Opt->Botweapons[7]++;
                    if (Moldb==2) if (Opt->Botweapons[7]) Opt->Botweapons[7]--;
                }
        memset(s2, 0, 10);
        s = "Shotgun bots:";
        itoa_fake(Opt->Botweapons[1], s2, 10);
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 240, -1);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 240, -1);
        if (Mousein((SCREEN_X>>1)-100, 240, (SCREEN_X>>1)+160, 260)) if (Mob==0) if (Moldb)
                {
                    Opt->Bots = 0;
                    for (int i2 = 0; i2 < Difbotweapons; i2++) Opt->Bots += Opt->Botweapons[i2];
                    if (Opt->Bots < Maxbots)
                        if (Moldb==1) Opt->Botweapons[1]++;
                    if (Moldb==2) if (Opt->Botweapons[1]) Opt->Botweapons[1]--;
                }
        memset(s2, 0, 10);
        s = "Machinegun bots:";
        itoa_fake(Opt->Botweapons[2], s2, 10);
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 260, -1);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 260, -1);
        if (Mousein((SCREEN_X>>1)-100, 260, (SCREEN_X>>1)+160, 280)) if (Mob==0) if (Moldb)
                {
                    Opt->Bots = 0;
                    for (int i2 = 0; i2 < Difbotweapons; i2++) Opt->Bots += Opt->Botweapons[i2];
                    if (Opt->Bots < Maxbots)
                        if (Moldb==1) Opt->Botweapons[2]++;
                    if (Moldb==2) if (Opt->Botweapons[2]) Opt->Botweapons[2]--;
                }
        memset(s2, 0, 10);
        s = "Bazooka bots:";
        itoa_fake(Opt->Botweapons[3], s2, 10);
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 280, -1);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 280, -1);
        if (Mousein((SCREEN_X>>1)-100, 280, (SCREEN_X>>1)+160, 300)) if (Mob==0) if (Moldb)
                {
                    Opt->Bots = 0;
                    for (int i2 = 0; i2 < Difbotweapons; i2++) Opt->Bots += Opt->Botweapons[i2];
                    if (Opt->Bots < Maxbots)
                        if (Moldb==1) Opt->Botweapons[3]++;
                    if (Moldb==2) if (Opt->Botweapons[3]) Opt->Botweapons[3]--;
                }
        memset(s2, 0, 10);
        s = "Homing missile bots:";
        itoa_fake(Opt->Botweapons[4], s2, 10);
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 300, -1);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 300, -1);
        if (Mousein((SCREEN_X>>1)-100, 300, (SCREEN_X>>1)+160, 320)) if (Mob==0) if (Moldb)
                {
                    Opt->Bots = 0;
                    for (int i2 = 0; i2 < Difbotweapons; i2++) Opt->Bots += Opt->Botweapons[i2];
                    if (Opt->Bots < Maxbots)
                        if (Moldb==1) Opt->Botweapons[4]++;
                    if (Moldb==2) if (Opt->Botweapons[4]) Opt->Botweapons[4]--;
                }
        memset(s2, 0, 10);
        s = "Plasma pistol bots:";
        itoa_fake(Opt->Botweapons[5], s2, 10);
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 320, -1);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 320, -1);
        if (Mousein((SCREEN_X>>1)-100, 320, (SCREEN_X>>1)+160, 340)) if (Mob==0) if (Moldb)
                {
                    Opt->Bots = 0;
                    for (int i2 = 0; i2 < Difbotweapons; i2++) Opt->Bots += Opt->Botweapons[i2];
                    if (Opt->Bots < Maxbots)
                        if (Moldb==1) Opt->Botweapons[5]++;
                    if (Moldb==2) if (Opt->Botweapons[5]) Opt->Botweapons[5]--;
                }
        memset(s2, 0, 10);
        s = "Laser rifle bots:";
        itoa_fake(Opt->Botweapons[6], s2, 10);
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 340, -1);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 340, -1);
        if (Mousein((SCREEN_X>>1)-100, 340, (SCREEN_X>>1)+160, 360)) if (Mob==0) if (Moldb)
                {
                    Opt->Bots = 0;
                    for (int i2 = 0; i2 < Difbotweapons; i2++) Opt->Bots += Opt->Botweapons[i2];
                    if (Opt->Bots < Maxbots)
                        if (Moldb==1) Opt->Botweapons[6]++;
                    if (Moldb==2) if (Opt->Botweapons[6]) Opt->Botweapons[6]--;
                }
        memset(s2, 0, 10);
        s = "Sniper rifle bots:";
        itoa_fake(Opt->Botweapons[8], s2, 10);
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1)-100, 360, -1);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s2, (SCREEN_X>>1)+100, 360, -1);
        if (Mousein((SCREEN_X>>1)-100, 360, (SCREEN_X>>1)+160, 380)) if (Mob==0) if (Moldb)
                {
                    Opt->Bots = 0;
                    for (int i2 = 0; i2 < Difbotweapons; i2++) Opt->Bots += Opt->Botweapons[i2];
                    if (Opt->Bots < Maxbots)
                        if (Moldb==1) Opt->Botweapons[8]++;
                    if (Moldb==2) if (Opt->Botweapons[8]) Opt->Botweapons[8]--;
                }

        s = "Back";
        Length = text_length((FONT*) Dat[TITLEFONT].dat, s);
        textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, s, (SCREEN_X>>1), 380, -1);
        if (Mousein((SCREEN_X>>1)-100, 380, (SCREEN_X>>1)+160, 400)) if (Mob==0) if (Moldb==1)
                {
                    Curmenu = 8;
                    Opt->Bots = 0;
                    for (int i2 = 0; i2 < Difbotweapons; i2++) Opt->Bots += Opt->Botweapons[i2];
                }
    }
    break;
    };
} // Menutexts



void Menu()
{
    Searchfiles();
//  Game();
    set_palette((PALETTE) Dat[TITLEPAL].dat);
    StartMenuMusic();

    int Timer = 0;
    do
    {

        while (keypressed())  {
            readkey();
        }
        Timer++;
        if (Timer > 5)
        {
            Timer = 0;
            draw_rle_sprite(Scr, (RLE_SPRITE*) Dat[TITLE].dat, (SCREEN_X>>1)-(((RLE_SPRITE*) Dat[TITLE].dat)->w>>1), 125-(((RLE_SPRITE*) Dat[TITLE].dat)->h>>1));
            Burntitle(Scr);
        } //      if (Timer > 10)
        rectfill(Scr, 0, 0, SCREEN_X, 30, 0);
        rectfill(Scr, 0, 31, (Scr->w>>1)-269, 179, 0);
        rectfill(Scr, (Scr->w>>1)+270, 31,SCREEN_X , 179, 0);
        rectfill(Scr, 0, 180, SCREEN_X, SCREEN_Y, 0);
        rect(Scr, 0, -1, SCREEN_X, 179, 0);
        draw_sprite(Scr, (BITMAP*) Dat[TITLECOPYRIGHT].dat, SCREEN_X-((BITMAP*) Dat[TITLECOPYRIGHT].dat)->w, SCREEN_Y-10-((BITMAP*) Dat[TITLECOPYRIGHT].dat)->h);
        UpdateMouse();
        Menutexts();
        draw_sprite(Scr, (BITMAP*) Dat[TITLECURSOR].dat, Mox, Moy);
        Upscr();
        if (Mustfadein)
        {
            fade_in((PALETTE) Dat[TITLEPAL].dat, 6);
            Mustfadein = false;
        } //      if (Mustfadein)
        if (key[KEY_ESC]) Exit = true;
        if (key[KEY_F8]) {
            key[KEY_F8]=0;
            Takescrshot((PALETTE) Dat[TITLEPAL].dat);
        }
    } while (!Exit);
    fade_out(4);
} // Menu
void Update_timers()
{
    Lavatimer = 0;
    Timer++;
    if (Timer % 50==0) Lavatimer=1;
    if (Timer % 15==0) {
        Dirtsample = false;
        Expsample = false;
    }
} // Update_timers

void Game()
{
    while (keypressed())  {
        readkey();
    }
    fade_out(6);

    clear(Scr);
    Upscr();
    Load((char*)mapFilenames[Opt->Fileselected].c_str());  // engine.h // Lataa kartan
    Format();
    Createparallax();

    StartGameMusic();
    Playsample(0, 0, 0);      // alkusample koska muuten ei ensimmäinen soi
    Do_game_logic();
    Animate();
    Do_drawings();
    Upscr();
    fade_in((PALETTE) Dat[DATPALETTE].dat, 6);
    int Quit = 0;
    Game_logic_update_counter = 0;
    do
    {
        Update_clock();
        Update_timers();          // Timereiden päivitys
        do
        {
            Do_game_logic();          // engine.h // pelilogiikan päivitys
            Animate();                // engine.h // Animoi
            Game_logic_update_counter--;
        } while (Game_logic_update_counter>0);
        Do_drawings();            // engine.h // Graffanpiirto
        Setclipping(-1);          // engine.h // Clippaus kokoruudulle
        Upscr();                  // graph.h  // Muistista näytölle
        Checkkeys();              // control.h// Pelaajien kontrolli ja muuta kivaa

        if (Opt->Gametype == GAMETYPE_BOTHUNT) if (Botsalive==0) Quit++;
        if (Opt->Gametype == GAMETYPE_DEATHMATCH)
        {
            for (int i = 0; i < Opt->Players; i++)
                for (int i2 = 0; i2 < Opt->Players; i2++) if (i != i2)
                        if (Md->Pl[i].Kills[i2] >= Opt->Fraglimit)
                            Quit++;
        } // if (Opt->Gametype == GAMETYPE_DEATHMATCH)

        if (Quit > 200) Done = true;

    } while (Done == false);
    // TODO Replace with this fadeout with something else later.
    /*
    do
    {
        mp_volume--;
        vsync();
        vsync();
    } while (mp_volume>0); */
    if (Opt->Gametype == GAMETYPE_BOTHUNT)
    {
        fade_out(4);
        clear(Scr);
        Upscr();
        std::stringstream stream;

        for (int i = 0; i < Opt->Players; i++)
        {
            Setclipping(i);
            stream << "Player ";
            stream << (i+1);
            textout_centre(Scr, (FONT*) Dat[FONT1].dat, stream.str().c_str(), Clipx1+((Clipx2-Clipx1)>>1), Clipy1+((Clipy2-Clipy1)>>1)-40, -1);
            stream.str(""); stream.clear();
            stream << "Killed ";
            stream << (Md->Pl[i].Botskilled);
            stream << " / ";
            stream << Opt->Bots;
            stream << " bots.";
            textout_centre(Scr, (FONT*) Dat[FONT1].dat, stream.str().c_str(), Clipx1+((Clipx2-Clipx1)>>1), Clipy1+((Clipy2-Clipy1)>>1)-20, -1);
            stream.str(""); stream.clear();
            stream << "Died ";
            stream << (Md->Pl[i].Died);
            stream << " times.";
            textout_centre(Scr, (FONT*) Dat[FONT1].dat, stream.str().c_str(), Clipx1+((Clipx2-Clipx1)>>1), Clipy1+((Clipy2-Clipy1)>>1), -1);
        } // for (int i = 0; i < Opt->Players; i++)
        Upscr();
        fade_in((PALETTE) Dat[DATPALETTE].dat, 6);
        while (keypressed())  {
            readkey();
        }
        readkey();
    } //     if (Opt->Gametype == GAMETYPE_BOTHUNT)
    if (Opt->Gametype == GAMETYPE_DEATHMATCH)
    {
        fade_out(4);
        clear(Scr);
        Upscr();
        std::stringstream stream;
        for (int i = 0; i < Opt->Players; i++)
        {
            Setclipping(i);
            stream << "Player ";
            stream << (i+1);
            textout_centre(Scr, (FONT*) Dat[FONT1].dat, stream.str().c_str(), Clipx1+((Clipx2-Clipx1)>>1), Clipy1+((Clipy2-Clipy1)>>1)-40, -1);
            stream.str(""); stream.clear();
            stream << "Killed";
            textout_centre(Scr, (FONT*) Dat[FONT1].dat, stream.str().c_str(), Clipx1+((Clipx2-Clipx1)>>1), Clipy1+((Clipy2-Clipy1)>>1)-20, -1);
            for (int i2 =0 ; i2 < Opt->Players; i2++)
            {
                stream.str(""); stream.clear();
                stream << "Player ";
                stream << (i2+1);
                stream << ": ";
                stream << (Md->Pl[i].Kills[i2]);
                stream << " times.";
                textout_centre(Scr, (FONT*) Dat[FONT1].dat, stream.str().c_str(), Clipx1+((Clipx2-Clipx1)>>1), Clipy1+((Clipy2-Clipy1)>>1)+i2*20, -1);
            }
            stream.str(""); stream.clear();
            stream << "Died ";
            stream << (Md->Pl[i].Died);
            stream << " times.";
            textout_centre(Scr, (FONT*) Dat[FONT1].dat, stream.str().c_str(), Clipx1+((Clipx2-Clipx1)>>1), Clipy1+((Clipy2-Clipy1)>>1)+20+Opt->Players*20, -1);
        } // for (int i = 0; i < Opt->Players; i++)
        Upscr();
        fade_in((PALETTE) Dat[DATPALETTE].dat, 6);
        while (keypressed())  {
            readkey();
        }
        readkey();
    } //     if (Opt->Gametype == GAMETYPE_DEATHMATCH)
    Setclipping(-1);
} // Game


