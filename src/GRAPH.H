
/*

Tänne taas tulee kaikki grafiikkajutskat.

(C) 1999 Tero Laitinen (Replica§)

*/
#ifndef __graph_h       // jos ei ole includettu jo
#define __graph_h
#include "tstring.h"
int             SCREEN_X               = 640; // Ruudun leveys
int             SCREEN_Y               = 480; // ja korkeus
// Upscr() makro
#define         Upscr()                 blit(Scr, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); Frames++;

COLOR_MAP rgb_table; // värien sekoitusta varten
COLOR_MAP light_table;


PALETTE           Pal;// paletti
int Frames;           // että voidaan laskea monta ruutua sekunnissa
// Ottaa screenshotin
void Takescrshot(PALETTE Pal);

// Ottaa merkkijonon
char *Takestring(int x1, int y1, char * s, int maxlen, int col, int bcol);
// kirjoittaa numeron
void Textint(BITMAP *bmp, FONT * fnt, int i, int x, int y, int col);
// kääntää bitmapin
void Invertbmp(BITMAP * bmp);

void InitGraph();
void DeInitGraph();

BITMAP * Scr;

void Takescrshot(PALETTE Pal)
 {
  Tstring String;
  for (int i = 1; i < 9999; i++)
   {
    String = "Shot";
    String + i;
    String += ".pcx";
    if (__file_exists(String.Str())==0)
     {
      save_pcx(String.Str(), Scr, Pal);
      i = 10000;
     } // if (!__file_exists(String.Str()))
   } // for (int i = 1; i < 9999; i++)
 } // void Takescrshot()

char *Takestring_centre(int x1, int y1, char * s, int maxlen, int col, int bcol)
 {
   bool Listbox1editdone = false, Cancel = false;
   bool Takech = false, Notallocated = false;
   int Ch2, Ch3;
   char Ch;
   char *S = new char[maxlen+1];
   memset(S, 0, maxlen+1);
   int pos = strlen(s);
   if (s)
   strcpy(S, s); else Notallocated = true;
   do
    {
     if (Takech)
      {
        S[pos++] = Ch;
      } // Takech

     textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, S, x1, y1, col);
      Upscr();
      Takech = true;
      Ch3 = readkey();
      
      textout_centre(Scr, (FONT*) Dat[TITLEFONT].dat, S, x1, y1, bcol);
     
      Ch2 = Ch3 >> 8;
//        Ch2 = getch();
      Ch = Ch3;

      if (Ch == 9) Takech = false;
      if (Ch == 8) if (pos > 0) {memcpy(&S[pos-1], &S[pos], maxlen-pos+1); S[maxlen] = 0;pos--;Takech = false;}
      if  (Ch == 13) Listbox1editdone = true;
      if  (Ch == 27) { Listbox1editdone = true; Cancel = true; }
      if (pos >= maxlen) Listbox1editdone = true;
     } while (Listbox1editdone == false);
     if (Cancel == false)
      {
        if (Notallocated==true)
          {
           s = new char[maxlen+1];
           memcpy(s,S, maxlen+1);
           delete S;
          } else
          {
            strcpy(s,S);
            delete S;
          }

      } // Cancel == false
     return(s);
 } // Takestring
char *Takestring(int x1, int y1, char * s, int maxlen, int col, int bcol)
 {
   bool Listbox1editdone = false, Cancel = false;
   bool Takech = false, Notallocated = false;
   int Ch2, Ch3;
   char Ch;
   char *S = new char[maxlen+1];
   memset(S, 0, maxlen+1);
   int pos = strlen(s);
   if (s)
   strcpy(S, s); else Notallocated = true;
   do
    {
     if (Takech)
      {
        S[pos++] = Ch;
      } // Takech

     textout(Scr, font, S, x1, y1, col);
     textout(Scr, font, "_\0", x1+pos*8, y1, col);
      Upscr();
      Takech = true;
      Ch3 = readkey();
      textout(Scr, font, S, x1, y1, bcol);
      textout(Scr, font, "_\0", x1+pos*8, y1, bcol);
     
      Ch2 = Ch3 >> 8;
      Ch = Ch3;
      if (Ch2 == 75) {Takech = false; pos--;}
      if (Ch2 == 77) {Takech = false; pos++;}
      if ((Ch2 == 80) || (Ch2 == 72)) Takech = false;
      if (Ch == 9) Takech = false;
      if (Ch == 8) if (pos > 0) {memcpy(&S[pos-1], &S[pos], maxlen-pos+1); S[maxlen] = 0;pos--;Takech = false;}
      if  (Ch == 13) Listbox1editdone = true;
      if  (Ch == 27) { Listbox1editdone = true; Cancel = true; }
      if (pos >= maxlen) Listbox1editdone = true;
     } while (Listbox1editdone == false);
     if (Cancel == false)
      {
        if (Notallocated==true)
          {
           s = new char[maxlen+1];
           memcpy(s,S, maxlen+1);
           delete S;
          } else
          {
            strcpy(s,S);
            delete S;
          }

      } // Cancel == false
     return(s);
 } // Takestring

void Textint(BITMAP *bmp , FONT * fnt, int i, int x, int y, int col)
 {
   char * s = new char[30];
   itoa (i,s,10);
   textout(bmp,fnt, s, x, y, col);
   delete s;

 } // Textint

void Invertbmp(BITMAP * bmp)
 {

  for (int y = 0; y < bmp->h-1; y++)
   {
     for (int x = 0; x < ((bmp->w)>>1); x++)
      {
        int apu = bmp->line[y][bmp->w-x-1];
        bmp->line[y][bmp->w-x-1] = bmp->line[y][x];
        bmp->line[y][x] = apu;
      }
   }
 } // Invertbmp

void InitGraph()
 {
    if (set_gfx_mode(GFX_AUTODETECT, SCREEN_X, SCREEN_Y, 0, 0) < 0)
     {
      printf("\nCurrent resolution not supported!\nChanging to 640x480");
      fflush(stdout);
      readkey();
      SCREEN_X = 640;
      SCREEN_Y = 480;
      set_gfx_mode(GFX_AUTODETECT, SCREEN_X, SCREEN_Y, 0, 0);
     } //     if (set_gfx_mode(GFX_AUTODETECT, SCREEN_X, SCREEN_Y, 0, 0) < 0)
    Scr = create_bitmap(SCREEN_W, SCREEN_H);
    clear(Scr);
    text_mode(-1);

    set_palette((PALETTE)Dat[DATPALETTE].dat);
    PALLETE pal;
    PALETTE Pal;
    create_trans_table(&rgb_table, (PALETTE)Dat[DATPALETTE].dat, 192, 192, 192, NULL);
    create_light_table(&light_table, (PALETTE)Dat[DATPALETTE].dat, 255, 255, 255, NULL);
    color_map = &rgb_table;


 } // Initgraph
void DeInitGraph()
 {
   destroy_bitmap(Scr);
   text_mode(0);
 } // DeInitgraph


#endif

