#include <iostream.h>
#include <allegro.h>
#include <mikmod.h>
#include <ctype.h>
#define EDITOR
bool Done = false;
int Multi;
#include "lotlib.h"
int Hiti = 0, Wep, Lavatimer, Timer;
//#include "keyboard.h"
#include "types.h"
#include "data.h"
#include "common.h"
 #include "sound.h"

 #include "sample.h"
 #include "itemdata.h"
#include "graph.h"
#include "engine.h"
// #include "items.h"
// #include "control.h"

#define Maxlandpics             DATMAP9999-DATMAP0001
typedef struct
 {
   int x1,  y1,  x2,  y2;
   int Page;
 } Tbox;
Tbox Mapbox[Maxlandpics];

int Wx, Wy, Wdir, Wdist, Page;
bool Setspire;
unsigned _stklen = 16843*1024;
int Mapx, Mapy, Tool, Brush, Oldselx, Oldsely, Linex1, Liney1, Tilexsize, Tileysize;
int Subtool = 0, Botweapon;
bool Themap= true;

void main();
void Game();

void main()
 {
   InitAllegro();

   InitData();
   InitGraph();
   InitEngine();
   set_palette((PALETTE) Dat[DATPALETTE].dat);
   Game();
   DeInitEngine();
   DeInitGraph();
   DeInitData();
   DeInitAllegro();



 } // main
void Selectbotweapon()
 {
  bool Selected = false;
  do
   {
    clear(Scr);
    char * Text="";
    switch(Botweapon)
     {
      case ITEM_PISTOL:  Text = "pistol";break;
      case ITEM_MAGNUM:  Text = "magnum";break;
      case ITEM_SHOTGUN: Text = "shotgun";break;
      case ITEM_MACHINEGUN: Text = "machinegun";break;
      case ITEM_LASERRIFLE: Text = "laserrifle";break;
      case ITEM_BAZOOKA: Text = "bazooka";break;
      case ITEM_HMISLAUNCHER: Text = "homing missile launcher";break;
      case ITEM_PLASMAPISTOL: Text = "plasmapistol";break;
      case ITEM_SNIPERRIFLE: Text = "sniper rifle";break;
     }; //
    textprintf(Scr, font, 10, 10, 15, "Bot weapon: %s", Text);
    textprintf(Scr, font, 10, 20, 15, "A) Pistol");
    textprintf(Scr, font, 10, 30, 15, "B) Magnum");
    textprintf(Scr, font, 10, 40, 15, "C) Shotgun");
    textprintf(Scr, font, 10, 50, 15, "D) Machinegun");
    textprintf(Scr, font, 10, 60, 15, "E) Laserrifle");
    textprintf(Scr, font, 10, 70, 15, "F) Bazooka");
    textprintf(Scr, font, 10, 80, 15, "G) Homing missile launcher");
    textprintf(Scr, font, 10, 90, 15, "H) Plasmapistol");
    textprintf(Scr, font, 10, 100, 15, "I) Sniper rifle");
    Upscr();
    int Ch=-1;
    if (keypressed())
     Ch = readkey();
     char Ch2 = Ch;
    switch(toupper(Ch2))
     {
      case ' ': Selected = true; break;
      case 'A':Botweapon = ITEM_PISTOL;break;
      case 'B':Botweapon = ITEM_MAGNUM;break;
      case 'C':Botweapon = ITEM_SHOTGUN;break;
      case 'D':Botweapon = ITEM_MACHINEGUN;break;
      case 'E':Botweapon = ITEM_LASERRIFLE;break;
      case 'F':Botweapon = ITEM_BAZOOKA;break;
      case 'G':Botweapon = ITEM_HMISLAUNCHER;break;
      case 'H':Botweapon = ITEM_PLASMAPISTOL;break;
      case 'I':Botweapon = ITEM_SNIPERRIFLE;break;
     }; // switch(Ch)

   } while (!Selected);
 } // void Selectbotweapon()

void Setboxes()
 {
   int Ax = 0, Ay = 0, Apage = 0;
   int Biggest=0;
   for (int i = 0; i < Maxlandpics; i++)
    {
      if (Ax+((BITMAP*) Dat[DATMAP0001+i].dat)->w> SCREEN_X)
      {
       Ax = 0;
       Ay += Biggest + 1;
       Biggest = 0;
       if (Ay+((BITMAP*) Dat[DATMAP0001+i].dat)->h> SCREEN_Y)
        {
          Apage++;
          Ax = 0;
          Ay= 0;
        }
      }

      Mapbox[i].x1 = Ax;
      Mapbox[i].y1 = Ay;
      Mapbox[i].x2 = Ax+((BITMAP*) Dat[DATMAP0001+i].dat)->w;
      Mapbox[i].y2 = Ay+((BITMAP*) Dat[DATMAP0001+i].dat)->h;
      if (Biggest< ((BITMAP*) Dat[DATMAP0001+i].dat)->h) Biggest = ((BITMAP*) Dat[DATMAP0001+i].dat)->h;
      Mapbox[i].Page = Apage;
      Ax+= ((BITMAP*) Dat[DATMAP0001+i].dat)->w+3;
      if (Ax> SCREEN_X)
      {
       Ax = 0;
       Ay += Biggest + 3;
       Biggest = 0;
       if (Ay+((BITMAP*) Dat[DATMAP0001+i].dat)->h> SCREEN_Y)
        {
          Apage++;
          Ax = 0;
          Ay= 0;
        } // if (Ay+((BITMAP*) Dat[DATMAP0001+i].dat)->h> SCREEN_Y)
      } // Ax > 640
    } // i < Maxpicutress
 } // Setboxes
void Selectbrush()
 {
 do
  {
    UpdateMouse();
    clear(Scr);

  for (int i = 0; i < Maxlandpics; i++)
    if (Mapbox[i].Page == Page)
     {
      if (Mob)
      if (Mox >= Mapbox[i].x1)
      if (Moy >= Mapbox[i].y1)
      if (Mox <= Mapbox[i].x2)
      if (Moy <= Mapbox[i].y2)
       {
         Done = true;
         Brush = i;
       }

       rect(Scr, Mapbox[i].x1, Mapbox[i].y1, Mapbox[i].x2+1, Mapbox[i].y2+1, 14);
       draw_sprite(Scr, (BITMAP*)Dat[DATMAP0001+i].dat, Mapbox[i].x1+1, Mapbox[i].y1+1);
     }
     Textint(Scr, font, Page+1, 0, 0, 15);
      draw_sprite(Scr, (BITMAP*) Dat[DATCURSOR].dat, Mox, Moy);
     if (kbhit())
       switch(getch())
      {
      case '-': if (Page) Page--; break;
      case '+': Page++; break;
      case 13: Done = true;break;
      };
     Upscr();
   } while (Done == false);
   Done = false;
  do
   {UpdateMouse();} while ((Mob > 0) || (Moldb > 0));
 } // Selectbrush
void Showminimap()
{
 if (Themap)
  {
   rect(Scr,0, 0, 200, 200, 15);
   stretch_blit(Md->Map, Scr, 0, 0,Lev->Mapsizex, Lev->Mapsizey, 0,0,200,200);
   putpixel(Scr, (1+(Mox+Mapx)*200)/Lev->Mapsizex, (1+(Moy+Mapy)*200)/Lev->Mapsizey, rand()%256);
  } // Themap

} //Showminimap
void Addspire(int X, int Y, int Dir, int Power)
 {
   for (int i = 0; i < Maxspires; i++)
    if(Md->Spire[i].Live==false)
     {
       Md->Spire[i].Live = true;
       Md->Spire[i].X = X;
       Md->Spire[i].Y = Y;
       Md->Spire[i].Dir = Dir;
       Md->Spire[i].Power = Power;

       i = Maxspires;
     } // if(Md->Spire[i].Live==false)
 } // Addspire
void Showspires()
 {
   for (int i = 0; i < Maxspires; i++)
    if (Md->Spire[i].Live)
    {
            line(Scr, Md->Spire[i].X-Mapx, Md->Spire[i].Y-Mapy, Md->Spire[i].X+fixtoi(fcos(Suunta(Md->Spire[i].Dir-itofix(16)))*Md->Spire[i].Power)-Mapx, Md->Spire[i].Y+fixtoi(fsin(Suunta(Md->Spire[i].Dir-itofix(16)))*Md->Spire[i].Power)-Mapy, 15);
            line(Scr, Md->Spire[i].X-Mapx, Md->Spire[i].Y-Mapy, Md->Spire[i].X+fixtoi(fcos(Suunta(Md->Spire[i].Dir+itofix(16)))*Md->Spire[i].Power)-Mapx, Md->Spire[i].Y+fixtoi(fsin(Suunta(Md->Spire[i].Dir+itofix(16)))*Md->Spire[i].Power)-Mapy, 15);
            circle(Scr, Md->Spire[i].X-Mapx, Md->Spire[i].Y-Mapy, 4, 4);
    }
 } // Showspires
void Line_helper(BITMAP* B, int x, int y, int c)
 {
  rect(Scr, Linex1+x*Tilexsize-Mapx, Liney1+y*Tileysize-Mapy, Linex1+(x+1)*Tilexsize-Mapx, Liney1+(y+1)*Tileysize-Mapy, 14);
  if (c > -1)
   {
     Insertobject(Linex1+x*Tilexsize, Liney1+y*Tileysize, Brush);
     BITMAP* apu = (BITMAP*) Dat[DATMAP0001+Brush].dat;
     draw_sprite(Md->Map, apu,Linex1+x*Tilexsize, Liney1+y*Tileysize);
   } //   if (c > -1)

 } // void Line_helper(BITMAP* B, int x, int y, int c)

void Game()
 {
 int ch;
   bool Done = false;
   Md->Map = create_bitmap(2000, 2000);
   Lev->Mapsizex = 2000;
   Lev->Mapsizey = 2000;
   clear(Md->Map);
   Setboxes();
   BITMAP * apu;
char * s = new char[13];
int ax, ay;
 strcpy(Add->Texturename, "texture1.pcx");
   do
    {
      Showmap(0, 0, SCREEN_X, SCREEN_Y, Mapx, Mapy);
      if (Mob == 0) if (Moldb == 0)
       {
        Oldselx = Mapx+Mox;
        Oldsely = Mapy+Moy;
       } // if (Mob == 0)
      UpdateMouse();
      switch(Tool)
      {
       case 0:
          for (int i = Maxobjects-1; i >= 0; i--)
           {
            apu = (BITMAP*) Dat[DATMAP0001+Md->Obj[i].Type].dat;
           if (Md->Obj[i].Live==true)
           if (Mox+Mapx > Md->Obj[i].X )
               if (Moy+Mapy > Md->Obj[i].Y)
                   if (Mox+Mapx < Md->Obj[i].X + (apu->w))
                       if (Moy+Mapy < Md->Obj[i].Y + (apu->h))
                        {
                         rect(Scr, Md->Obj[i].X - Mapx, Md->Obj[i].Y - Mapy, Md->Obj[i].X - Mapx + apu->w, Md->Obj[i].Y - Mapy + apu->h, 14);
                          i = -1;
                        }
            }
         apu = (BITMAP*) Dat[DATMAP0001+Brush].dat;
          draw_sprite(Scr, apu, Mox-(apu->w>>1),Moy-(apu->h>>1));
          if (Mob==1) if (Moldb == 0)
           {
             Insertobject(Mapx+Mox-(apu->w>>1), Mapy+Moy-(apu->h>>1), Brush);
             draw_sprite(Md->Map, apu,Mapx+Mox-(apu->w>>1), Mapy+Moy-(apu->h>>1));
//             Updatemap();
           }
          if (Mob==2) if (Moldb == 0)
           {
             Deleteobject(Mapx+Mox, Mapy+Moy);
             set_clip(Md->Map, Mapx+Mox-200, Mapy+Moy-200, Mapx+Mox+200, Mapy+Moy+200);
             Updatemap();
             set_clip(Md->Map, 0, 0, Lev->Mapsizex, Lev->Mapsizey);
           }
       break;
       case 1:
         if (Setspire == true)
          {
            Wdir  = Direction(Wx, Wy, Mox+Mapx, Moy+Mapy);
            Wdist = Distance(Wx, Wy, Mox+Mapx, Moy+Mapy)>>1;
            if (Wdist > 50) Wdist = 50;
            line(Scr, Wx-Mapx, Wy-Mapy, Wx+fixtoi(fcos(Suunta(Wdir-itofix(16)))*Wdist)-Mapx, Wy+fixtoi(fsin(Suunta(Wdir-itofix(16)))*Wdist)-Mapy, 15);
            line(Scr, Wx-Mapx, Wy-Mapy, Wx+fixtoi(fcos(Suunta(Wdir+itofix(16)))*Wdist)-Mapx, Wy+fixtoi(fsin(Suunta(Wdir+itofix(16)))*Wdist)-Mapy, 15);
            circle(Scr, Wx-Mapx, Wy-Mapy, 4, 4);
           } // if (Setspire == true)
           if (Mob == 2) if (Moldb == 0)
            {
              Setspire = false;
              for (int i = 0; i < Maxspires; i++)
               if (Md->Spire[i].Live)
                if (Mox+Mapx > Md->Spire[i].X-4)
                if (Moy+Mapy > Md->Spire[i].Y-4)
                if (Mox+Mapx < Md->Spire[i].X+4)
                if (Moy+Mapy < Md->Spire[i].Y+4)
                    Md->Spire[i].Live = false;
            }
           if (Mob == 1) if (Moldb == 0)
          {
            if (Setspire == false)
             {
              Setspire = true;
              Wx = Mox+Mapx;
              Wy = Moy+Mapy;
             } else
             {
              Setspire = false;
              Addspire(Wx, Wy, Wdir, Wdist);
             }
          } // if (Mob == 1) if (Moldb == 0)
       break;
       case 2:
         if (Brush > 2) Brush = 2;
         apu = (BITMAP*) Dat[Bldpic[Brush]].dat;
          draw_sprite(Scr, apu, Mox-(apu->w>>1),Moy-(apu->h>>1));
          if (Mob)
           {
             Lev->Startpoint[Brush][0] = Mox+Mapx-(apu->w>>1);
             Lev->Startpoint[Brush][1] = Moy+Mapy-(apu->h>>1);
           }
       break;
       case 3:
        {
         int X1 = Oldselx-(apu->w>>1);
         int Y1 = Oldsely-(apu->h>>1);
         int X2 = Mapx+Mox-(apu->w>>1);
         int Y2 = Mapy+Moy-(apu->h>>1);
         apu = (BITMAP*) Dat[DATMAP0001+Brush].dat;
          draw_sprite(Scr, apu, Mox-(apu->w>>1),Moy-(apu->h>>1));
         Tilexsize = apu->w;
         Tileysize = apu->h;
         Linex1 = X1%Tilexsize;
         Liney1 = Y1%Tileysize;

         if (Mob==1)
           {
            do_line(Scr, X1/Tilexsize, Y1/Tileysize, X2/Tilexsize, Y2/Tileysize, -1, Line_helper);
           }
          if (Mob==0) if (Moldb == 1)
           {
            do_line(Scr, X1/Tilexsize, Y1/Tileysize, X2/Tilexsize, Y2/Tileysize, 0, Line_helper);
           } // if (Mob==0) if (Moldb == 1)
        }
       break; // case 3:
       case 4:
        {
          apu = (BITMAP*) Dat[DATM4A1].dat;
          draw_sprite(Scr, apu, Mox-(apu->w>>1),Moy-(apu->h>>1));
        }
       break;
      };
   Showminimap();
  if (Tool != 0) draw_sprite(Scr, (BITMAP*) Dat[DATCURSOR].dat, Mox, Moy);
      if (Mox >= SCREEN_W-2) {Mapx+=5; }
      if (Moy >= SCREEN_H-2) {Mapy+=5;}
      if (Mox == 0) { Mapx-=5;if (Mapx<0) Mapx=0;}
      if (Moy == 0) { Mapy-=5;if (Mapy<0) Mapy=0;}
if (Mapx > Lev->Mapsizex-SCREEN_X) Mapx=Lev->Mapsizex-SCREEN_X;
if (Mapy > Lev->Mapsizey-SCREEN_Y) Mapy=Lev->Mapsizey-SCREEN_Y;
//Textint(Scr, font, (ch>>8), 10, 10, 12);
Showspires();
for (int i = 0; i < Maxplayers ; i++)
 draw_sprite(Scr, (BITMAP*) Dat[Bldpic[i]].dat, Lev->Startpoint[i][0]-Mapx, Lev->Startpoint[i][1]-Mapy);
              Upscr();

      if (keypressed())
        {
         ch = readkey();
         char ch2 = ch;
// jatka editdata
         switch(ch>>8)
         {
          case 41:
          for (int i = Maxobjects-1; i >= 0; i--)
           {
            apu = (BITMAP*) Dat[DATMAP0001+Md->Obj[i].Type].dat;
           if (Md->Obj[i].Live==true)
           if (Mox+Mapx > Md->Obj[i].X )
               if (Moy+Mapy > Md->Obj[i].Y)
                   if (Mox+Mapx < Md->Obj[i].X + (apu->w))
                       if (Moy+Mapy < Md->Obj[i].Y + (apu->h))
                        {
                          Brush = Md->Obj[i].Type;
                          i = -1;
                        }
            }

          break;
          case 46:
           {
            int Ob = Brush;
            Selectbrush();

              for (int i = 0; i < Maxobjects; i++)
               if (Md->Obj[i].Type == Ob) if (Md->Obj[i].Live)
                {
                 BITMAP * Bmp1 = (BITMAP*) Dat[DATMAP0001+Md->Obj[i].Type].dat;
                 Md->Obj[i].Type = Brush;
                 BITMAP * Bmp2 = (BITMAP*) Dat[DATMAP0001+Md->Obj[i].Type].dat;
                 int Y = Md->Obj[i].Y + Bmp1->h - Bmp2->h;
                 Md->Obj[i].Y = Y;
                } //              for (int i = 0; i < Maxobjects; i++)              if (Md->Obj[i].Type == Ob)
              Updatemap();
            }
          break; // case 99:

          case 20:
          clear(Scr);
          textout(Scr, font, "Please enter the filename for texture.", 1, 1, 12);
          textprintf(Scr, font, 1, 30, 7, "Current texture: %s", Add->Texturename);
          memset(s,0,13);
          Takestring(1,20, s, 12, 12, 0);
          strcpy(Add->Texturename, s);
          break; // case 't':
          case 57:
           switch(Tool)
            {
             case 4/*Bot*/:
              Selectbotweapon();
             break;
             default: Selectbrush(); break;
            }
          break;
          case 2: Tool = 0;
          break;
          case 3: Tool = 1;
          break;
          case 4: Tool = 2; Brush = 0;
          break;
          case 5: Tool = 3;
          break;
          case 6: Tool = 4;
          break;
          case 35:
          clear(Scr);
          textout(Scr, font, "Help for Volcano 2 Editor.", 1, 1, 12);

          textout(Scr, font, "+ and - = change brushes.", 1, 21, 12);
          textout(Scr, font, "q       = change map size.", 1, 31, 12);
          textout(Scr, font, "l       = load map", 1, 41, 12);
          textout(Scr, font, "s       = save map", 1, 51, 12);
          textout(Scr, font, "1       = draw brushes", 1, 61, 12);
          textout(Scr, font, "2       = set lavaspires(max 20)", 1, 71, 12);
          textout(Scr, font, "3       = set startpoints", 1, 81, 12);
          textout(Scr, font, "4       = line tool", 1, 91, 12);
          textout(Scr, font, "5       = bot tool", 1, 101, 12);
          textout(Scr, font, "tab     = map on/off     ", 1, 111, 12);
          textout(Scr, font, "space   = quick select   ", 1,121, 12);
          textout(Scr, font, "t       = change texturename ", 1,131, 12);

           Upscr();
          readkey();
          break;
          case 15:
           Themap = (Themap == false);
          break;
          case 16:
          clear(Scr);
          textout(Scr, font, "Please enter the dimensions of the map.", 1, 1, 12);
          textout(Scr, font, "X", 1, 20, 12);
          memset(s,0,13);
          Takestring(10,20, s, 12, 12, 0);
          ax = atoi(s);
          textout(Scr, font, "Y", 1, 30, 12);
          memset(s,0,13);
          Takestring(10,30, s, 12, 12, 0);
          ay = atoi(s);
           if (ax>0) if (ay >0) if (ax < Maxmapsizex+1) if (ay < Maxmapsizey+1)
          Setmapsize(ax,ay);
          Updatemap();
          break;
          case 31:
          clear(Scr);
          textout(Scr, font, "Please enter the filename for saving map. Make sure that you add the .map ext.", 1, 1, 12);
          memset(s,0,13);
          Takestring(1,20, s, 12, 12, 0);
          Save(s);
           break;
           case 38:

           clear(Scr);
          textout(Scr, font, "Please enter the filename for loading map. Make sure that you add the .map ext.", 1, 1, 12);
          memset(s,0,13);
          Takestring(1,20, s, 12, 12, 0);
          Load(s);

           break;

          case 1:
          {
          clear(Scr);
          textout_centre(Scr, font, "Are you sure you want to quit?", SCREEN_X>>1, (SCREEN_Y>>1)-4, 12);
          Upscr();
          do
           {
            ch = readkey();
            char ch2 = ch;
            if (toupper(ch2) == 'Y') Done = true;
            if (toupper(ch2) == 'N') break;
           } while (!Done);
          }
          break;
          case 78: Brush++; if (Brush > Maxlandpics) Brush= Maxlandpics; break;
          case 74: if (Brush)Brush--; break;
          case 55: Brush+=8; if (Brush > Maxlandpics) Brush= Maxlandpics; break;
          case 122: Brush-=8; if (Brush<0)Brush = 0;break;
         };
        } // (keypressed())

    } while (Done == false);

 } // Edit
