#ifndef __ai_h
 #define __ai_h
/*
 **Artificial** "intelligence" routines for Volcano 2 bots.
 Copyright (C) 1999 - 2000 Tero Laitinen /Replica§
*/
void Bot_ninjarope(int i);
bool Bot_will_collide(int i);
void Bot_try_to_follow(int i);
void Bot_change_clip(int i);
void Bot_use_pistol(int i);
void Bot_use_magnum(int i);
void Bot_use_shotgun(int i);
void Bot_use_machinegun(int i);
void Bot_use_laserrifle(int i);
void Bot_use_bazooka(int i);
void Bot_use_homingmissilelauncher(int i);
void Bot_use_plasmapistol(int i);
void Bot_use_sniperrifle(int i);
void Bot_attack_target(int i);
int Bot_search_target(int i);
void Update_bot_ai(int i);

void Bot_ninjarope(int i)
 {
    Md->Bot[i].Ninjadir = Md->Bot[i].Dir;
    Md->Bot[i].Ninjarope = true;
    Md->Bot[i].Ninjaground = false;
    Md->Bot[i].Nmx = int(fcos(Md->Bot[i].Dir)*4)+(Md->Bot[i].Mx>>1);
    Md->Bot[i].Nmy = int(fsin(Md->Bot[i].Dir)*4)+(Md->Bot[i].My>>1);
    Md->Bot[i].Nx = Md->Bot[i].X;
    Md->Bot[i].Ny = Md->Bot[i].Y;
    Md->Bot[i].Ropeset = 10;
 } // Bot_ninjarope

bool Bot_will_collide(int i)
 {
  Tbot *Old = new Tbot;
  memcpy(Old, &Md->Bot[i], sizeof(Tbot));
  int xx, yy;
  for (int i2 = 0; i2 < 200; i2++)
   {
      Md->Bot[i].Oldfeet = Md->Bot[i].FeetOnGround;
      // Jalat maassa
      Md->Bot[i].FeetOnGround = Bot_feet_on_ground(i);
      // Etäisyys basesta.... Tarvitaan ostamiseen
      // Jos ei olla maassa niin tiputaan
      if (!Md->Bot[i].FeetOnGround) Md->Bot[i].My+=Gravity; else
       {
        // muuten jos ei hypitä niin nopeusvektori y = 0
        if (Md->Bot[i].Jump == false)
        Md->Bot[i].My = 0;
        // jos ei kävellä niin jarrutetaan
        if (Md->Bot[i].Walking==false)
          {
           // heplo homma 500 pykälin kohti nollaa
            if (Md->Bot[i].Mx > 0) {if (Md->Bot[i].Mx-500 > 0) Md->Bot[i].Mx -= 500; else Md->Bot[i].Mx = 0;}
            if (Md->Bot[i].Mx < 0) {if (Md->Bot[i].Mx+500 < 0) Md->Bot[i].Mx += 500; else Md->Bot[i].Mx = 0;}
          }  //       if (Md->Bot[i].Walking==false)
       } // Jos jalat ovat maassa

      // Jos jalkojen tila on muuttunut niin ylöspäin. Suoraan yytä ei momenttia
      if (Md->Bot[i].Oldfeet != Md->Bot[i].FeetOnGround) Md->Bot[i].Y -= Gravity;

      // Vanhat botin koordit
      Md->Bot[i].Ox = Md->Bot[i].X;
      Md->Bot[i].Oy = Md->Bot[i].Y;

      // Kalkulointi uusille koordeille
 if (!Md->Bot[i].Ninjarope)
  {
      Md->Bot[i].X = Md->Bot[i].X + Md->Bot[i].Mx; // Plus nopeusvektorit
      Md->Bot[i].Y = Md->Bot[i].Y + Md->Bot[i].My;
  }
      // Jos ollaan ruudusta veks
      Bot_bounce_check(i);
      if (Md->Bot[i].Bounce)
       {
           memcpy(&Md->Bot[i], Old, sizeof(Tbot));
           delete Old;
           return true;
       } //       if (Bot[i].Bounce)
      // desimaaliosa pois
      xx = Md->Bot[i].X BitR;
      yy = Md->Bot[i].Y BitR;

      // jos jalat maassa
      if (getpixel(Md->Map, xx,yy+4))
       {

    int d = Bot_distance_to_surface(i);
          // että voidaan kävellä ylämäkeen
         if (d < 6) {  Md->Bot[i].Y -= (d-1) BitL;} else
          {
           memcpy(&Md->Bot[i], Old, sizeof(Tbot));
           delete Old;
           return true;
           Md->Bot[i].Mx = 0; // töks
           Md->Bot[i].My = 0;
           Md->Bot[i].X = Md->Bot[i].Ox; // vanhat koordit
           Md->Bot[i].Y = Md->Bot[i].Oy;
          }
       }
   }
  memcpy(&Md->Bot[i], Old, sizeof(Tbot));
  delete Old;
  return false;
 } // bool Bot_will_collide(int i)
void Bot_walk_idle(int i)
 {
  if (Md->Bot[i].Dir>>16 == Md->Bot[i].Targetdir>>16) if (rand()%20==0) Md->Bot[i].Targetdir = (rand()%255)<<16;


  if (Rand()%80 == 0) Bot_ninjarope(i);

    Md->Bot[i].Walking = true;
   if (Md->Bot[i].Ninjarope)
     {
      Md->Bot[i].Stuck++;
      if (Md->Bot[i].Stuck > 800) Md->Bot[i].Ninjarope = false;
       if (Md->Bot[i].Ninjaground)      if (Rand()%80 == 0)
       Md->Bot[i].Ninjarope = false;
     }
   if (Md->Bot[i].Ninjarope == false)
   if (Md->Bot[i].FeetOnGround)
    if (Bot_will_collide(i))
     {
      Md->Bot[i].Jump = true;
      Md->Bot[i].My = -52000;
     } // (Md->Pl[i].FeetOnGround)
   if (Md->Bot[i].Ninjarope == false)
   if (Md->Bot[i].Ox>>16 == Md->Bot[i].X>>16)
   if (Md->Bot[i].Oy>>16 == Md->Bot[i].Y>>16)
    {
      Md->Bot[i].Stuck++;
      if (Md->Bot[i].Stuck>50) {Md->Bot[i].Stuck = 0;Md->Bot[i].S = (Md->Bot[i].S==false);Md->Bot[i].Dir = Suunta(itofix(128)-Md->Bot[i].Dir);}
    } else Md->Bot[i].Stuck = 0;
 } // void Bot_walk_idle(int i)
void Bot_try_to_follow(int i)
 {
  Md->Bot[i].Jump = false;
  int p = Md->Bot[i].Target;
  if (Md->Bot[i].X < Md->Pl[p].X)
    {Md->Bot[i].S = 1;    Md->Bot[i].Walking = true;}
  if (Md->Bot[i].X > Md->Pl[p].X)
    {Md->Bot[i].S = 0;    Md->Bot[i].Walking = true;}
  if (Md->Bot[i].Walking)
   {
    if (Md->Bot[i].FeetOnGround)
     if (Bot_will_collide(i))
      {
       Md->Bot[i].Jump = true;
       Md->Bot[i].My = -52000;
      } // (Md->Pl[i].FeetOnGround)
   }
 } // void Bot_try_to_follow(int i)
void Bot_change_clip(int i)
 {
   if (Reloadsample[Md->Bot[i].Item] > -1) // jos lataamisesta kuuluu ääni
    {
     // niin soitetaan ääni
      bool Found = false;
      /* Jos on playereiden ruudussa */

      for (int i2 = 0; i2 < Opt->Players; i2++)
       if (Md->Bot[i].X>>16 > (Md->Pl[i2].X BitR) - (Clipx>>1))
       if (Md->Bot[i].X>>16 < (Md->Pl[i2].X BitR) + (Clipx>>1))
       if (Md->Bot[i].Y>>16 > (Md->Pl[i2].Y BitR) - (Clipy>>1))
       if (Md->Bot[i].Y>>16 < (Md->Pl[i2].Y BitR) + (Clipy>>1))
        Found = true;
       if (Found)
      Playsample(Reloadsample[Md->Bot[i].Item], Opt->Soundvolume, 128, 0); else
       Playsample(Reloadsample[Md->Bot[i].Item], Opt->Soundvolume>>1, 128, 0);
    } // if (Reloadsample[Md->Bot[i].Item] > -1)
   Md->Bot[i].Ammo= Clipsize[Md->Bot[i].Item]-1;
   // latausaikaa
   Md->Bot[i].Reload = Reloadtime[Md->Bot[i].Item];
   Md->Bot[i].Firegun = false;
   Md->Bot[i].Reloading = true;
 } // Change_clip

void Bot_use_pistol(int i)
 {
  // jos latausaikaa ei ole ja panoksia on
   if (Md->Bot[i].Reload == 0)
    {
     // jos lipas on lopussa niin lataa
     if (Md->Bot[i].Ammo % Clipsize[Md->Bot[i].Item] == 0) Bot_change_clip(i); else
      {
       // muuten ammu

       // suuliekki
       Md->Bot[i].Gunfire = 5;
       // panoksia pois
       Md->Bot[i].Ammo-- ;
       // hylsy
       Shoot(BUL_BULLETSHELL, Md->Bot[i].X, Md->Bot[i].Y, -3000+rand()%6000, -8000+rand()%1000);
       // panos
       Shoot(BUL_PISTOL, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*6-10000+rand()%20000, fsin(Md->Bot[i].Dir)*6-10000+rand()%20000,0,i,1);
       // pistoolin ääni

      bool Found = false;
      /* Jos on playereiden ruudussa */

      for (int i2 = 0; i2 < Opt->Players; i2++)
       if (Md->Bot[i].X>>16 > (Md->Pl[i2].X BitR) - (Clipx>>1))
       if (Md->Bot[i].X>>16 < (Md->Pl[i2].X BitR) + (Clipx>>1))
       if (Md->Bot[i].Y>>16 > (Md->Pl[i2].Y BitR) - (Clipy>>1))
       if (Md->Bot[i].Y>>16 < (Md->Pl[i2].Y BitR) + (Clipy>>1))
        Found = true;
       if (Found)
        Playsample(Samp[SAMP_PISTOL], Opt->Soundvolume, 128, 0); else
         Playsample(Samp[SAMP_PISTOL], Opt->Soundvolume>>1, 128, 0);
       // latausaika
       Md->Bot[i].Reload = 80;
       // ja tärinä
       Md->Bot[i].Shake = 10;
      } //  if (Md->Bot[i].Ammo[Weaponclip[Md->Bot[i].Item]] % Clipsize[Md->Bot[i].Item] == 0) Change_clip(i); else
    } // (Md->Bot[i].Reload == 0)
 } // Use_pistol(int i)
void Bot_use_sniperrifle(int i)
 {
  // jos latausaikaa ei ole ja panoksia on
   if (Md->Bot[i].Reload == 0)
    {
     // jos lipas on lopussa niin lataa
     if (Md->Bot[i].Ammo % Clipsize[Md->Bot[i].Item] == 0) Bot_change_clip(i); else
      {
      bool Found = false;
      /* Jos on playereiden ruudussa */
       // muuten ammu
       // suuliekki
       Md->Bot[i].Gunfire = 5;
       // panoksia pois
       Md->Bot[i].Ammo -- ;
       // panos
       int Mx, My;
       int t = Md->Bot[i].Target;

       Getmoments(Md->Bot[i].X BitR, Md->Bot[i].Y BitR, Md->Pl[t].X BitR, Md->Pl[t].Y BitR, &Mx, &My);
       Shoot(BUL_PISTOL, Md->Bot[i].X, Md->Bot[i].Y, Mx*3, My*3, ITEM_SNIPERRIFLE,i,0);
       // latausaika
       Md->Bot[i].Reload = 150;
       // ja tärinä
       Md->Bot[i].Shake = 5;

      for (int i2 = 0; i2 < Opt->Players; i2++)
       if (Md->Bot[i].X>>16 > (Md->Pl[i2].X BitR) - (Clipx>>1))
       if (Md->Bot[i].X>>16 < (Md->Pl[i2].X BitR) + (Clipx>>1))
       if (Md->Bot[i].Y>>16 > (Md->Pl[i2].Y BitR) - (Clipy>>1))
       if (Md->Bot[i].Y>>16 < (Md->Pl[i2].Y BitR) + (Clipy>>1))
        Found = true;
       if (Found)
        Playsample(Samp[SAMP_SNIPER], Opt->Soundvolume, 128, 0); else
         Playsample(Samp[SAMP_SNIPER], Opt->Soundvolume>>1, 128, 0);
      } //  if (Md->Bot[i].Ammo[Weaponclip[Md->Bot[i].Item]] % Clipsize[Md->Bot[i].Item] == 0) Change_clip(i); else
    } // (Md->Bot[i].Reload == 0)
 } // Use_sniperrifle(int i)
void Bot_use_magnum(int i)
 {
  // jos latausaikaa ei ole ja panoksia on
   if (Md->Bot[i].Reload == 0)
    {
     // jos lipas on lopussa niin lataa
     if (Md->Bot[i].Ammo % Clipsize[Md->Bot[i].Item] == 0) Bot_change_clip(i); else
      {
       Md->Bot[i].Mx += fcos(Suunta(Md->Bot[i].Dir-itofix(128)))>>2;
       Md->Bot[i].My += fsin(Suunta(Md->Bot[i].Dir-itofix(128)))>>2;
       // muuten ammu

       // suuliekki
       Md->Bot[i].Gunfire = 5;
       // panoksia pois
       Md->Bot[i].Ammo-- ;
       // hylsy
       Shoot(BUL_BULLETSHELL, Md->Bot[i].X, Md->Bot[i].Y, -3000+rand()%6000, -8000+rand()%1000);
       // panos
       Shoot(BUL_PISTOL, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*6-10000+rand()%20000, fsin(Md->Bot[i].Dir)*6-10000+rand()%20000,ITEM_MAGNUM,i,1);
       // pistoolin ääni

      bool Found = false;
      /* Jos on playereiden ruudussa */

      for (int i2 = 0; i2 < Opt->Players; i2++)
       if (Md->Bot[i].X>>16 > (Md->Pl[i2].X BitR) - (Clipx>>1))
       if (Md->Bot[i].X>>16 < (Md->Pl[i2].X BitR) + (Clipx>>1))
       if (Md->Bot[i].Y>>16 > (Md->Pl[i2].Y BitR) - (Clipy>>1))
       if (Md->Bot[i].Y>>16 < (Md->Pl[i2].Y BitR) + (Clipy>>1))
        Found = true;
       if (Found)
        Playsample(Samp[SAMP_MAGNUM], Opt->Soundvolume, 128, 0); else
         Playsample(Samp[SAMP_MAGNUM], Opt->Soundvolume>>1, 128, 0);
       // latausaika
       Md->Bot[i].Reload = 110;
       // ja tärinä
       Md->Bot[i].Shake = 10;
      } //  if (Md->Bot[i].Ammo[Weaponclip[Md->Bot[i].Item]] % Clipsize[Md->Bot[i].Item] == 0) Change_clip(i); else
    } // (Md->Bot[i].Reload == 0)
 } // Use_magnum(int i)
void Bot_use_shotgun(int i)
 {
  // jos latausaikaa ei ole ja panoksia on
   if (Md->Bot[i].Reload == 0)
    {
     // jos lipas on lopussa niin lataa
       // muuten ammu

       // suuliekki
       Md->Bot[i].Gunfire = 5;
       // panoksia pois
       bool Found = false;
      for (int i2 = 0; i2 < Opt->Players; i2++)
       if (Md->Bot[i].X>>16 > (Md->Pl[i2].X BitR) - (Clipx>>1))
       if (Md->Bot[i].X>>16 < (Md->Pl[i2].X BitR) + (Clipx>>1))
       if (Md->Bot[i].Y>>16 > (Md->Pl[i2].Y BitR) - (Clipy>>1))
       if (Md->Bot[i].Y>>16 < (Md->Pl[i2].Y BitR) + (Clipy>>1))
        Found = true;
       if (Found)
       Playsample(Samp[SAMP_SHOTGUN], Opt->Soundvolume, 128, 0); else
       Playsample(Samp[SAMP_SHOTGUN], Opt->Soundvolume>>1, 128, 0);
       // hylsy
       Shoot(BUL_SHOTGUNSHELL, Md->Bot[i].X, Md->Bot[i].Y, -3000+rand()%6000, -8000+rand()%1000);
       // panos
       Md->Bot[i].Mx += fcos(Suunta(Md->Bot[i].Dir-itofix(128)))>>1;
       Md->Bot[i].My += fsin(Suunta(Md->Bot[i].Dir-itofix(128)))>>1;

       Shoot(BUL_PISTOL, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*6-40000+rand()%80000, fsin(Md->Bot[i].Dir)*6-40000+rand()%80000,ITEM_SHOTGUN,i,1);
       Shoot(BUL_PISTOL, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*6-40000+rand()%80000, fsin(Md->Bot[i].Dir)*6-40000+rand()%80000,ITEM_SHOTGUN,i,1);
       Shoot(BUL_PISTOL, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*6-40000+rand()%80000, fsin(Md->Bot[i].Dir)*6-40000+rand()%80000,ITEM_SHOTGUN,i,1);
       Shoot(BUL_PISTOL, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*6-40000+rand()%80000, fsin(Md->Bot[i].Dir)*6-40000+rand()%80000,ITEM_SHOTGUN,i,1);
       Shoot(BUL_PISTOL, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*6-40000+rand()%80000, fsin(Md->Bot[i].Dir)*6-40000+rand()%80000,ITEM_SHOTGUN,i,1);
       Shoot(BUL_PISTOL, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*6-40000+rand()%80000, fsin(Md->Bot[i].Dir)*6-40000+rand()%80000,ITEM_SHOTGUN,i,1);
       // pistoolin ääni

       // latausaika
       Md->Bot[i].Reload = 400;
       // ja tärinä
       Md->Bot[i].Shake = 10;
    } // (Md->Bot[i].Reload == 0)
 } // Use_shotgun(int i)
void Bot_use_machinegun(int i)
 {
  // jos latausaikaa ei ole ja panoksia on
   if (Md->Bot[i].Reload == 0)
    {
     // jos lipas on lopussa niin lataa
     if (Md->Bot[i].Ammo% Clipsize[Md->Bot[i].Item] == 0) Bot_change_clip(i); else
      {
       // muuten ammu

       // panoksia pois
       Md->Bot[i].Ammo-- ;
       // pistoolinpanos
       Shoot(BUL_PISTOL, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*6-10000+rand()%20000, fsin(Md->Bot[i].Dir)*6-10000+rand()%20000,0,i,1);
       // hylsy
       Shoot(BUL_BULLETSHELL, Md->Bot[i].X, Md->Bot[i].Y, -3000+rand()%6000, -8000+rand()%1000);
       // takataka-ääni
       bool Found = false;
      for (int i2 = 0; i2 < Opt->Players; i2++)
       if (Md->Bot[i].X>>16 > (Md->Pl[i2].X BitR) - (Clipx>>1))
       if (Md->Bot[i].X>>16 < (Md->Pl[i2].X BitR) + (Clipx>>1))
       if (Md->Bot[i].Y>>16 > (Md->Pl[i2].Y BitR) - (Clipy>>1))
       if (Md->Bot[i].Y>>16 < (Md->Pl[i2].Y BitR) + (Clipy>>1))
        Found = true;
       if (Found)
       Playsample(Samp[SAMP_MACHINEGUN], (Opt->Soundvolume>>1), 128, 0); else
               Playsample(Samp[SAMP_MACHINEGUN], (Opt->Soundvolume>>2), 128, 0);
       // latausaika
       Md->Bot[i].Reload = 130;
       // tärinä
       Md->Bot[i].Shake = 30;
       // suuliekki
       Md->Bot[i].Gunfire = 5;
       Md->Bot[i].Firegun = true;
      } // if (Md->Bot[i].Ammo% Clipsize[Md->Bot[i].Item] == 0) Bot_change_clip(i); else
    } // (Md->Bot[i].Reload == 0)
  // neljä panosta sama homma

   if (Md->Bot[i].Reload == 115)
    {
     if (Md->Bot[i].Ammo% Clipsize[Md->Bot[i].Item] == 0) Bot_change_clip(i); else
      {
       Md->Bot[i].Gunfire = 5;
       Md->Bot[i].Ammo -- ;
       Shoot(BUL_PISTOL, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*6-10000+rand()%20000, fsin(Md->Bot[i].Dir)*6-10000+rand()%20000,0,i,1);
       Shoot(BUL_BULLETSHELL, Md->Bot[i].X, Md->Bot[i].Y, -3000+rand()%2000, -8000+rand()%1000);
      } // if (Md->Bot[i].Ammo% Clipsize[Md->Bot[i].Item] == 0) Bot_change_clip(i); else
    } // if (Md->Bot[i].Reload == 115)
   if (Md->Bot[i].Reload == 100)
    {
     if (Md->Bot[i].Ammo% Clipsize[Md->Bot[i].Item] == 0) Bot_change_clip(i); else
      {
       Md->Bot[i].Gunfire = 5;
       Md->Bot[i].Ammo-- ;
       Shoot(BUL_PISTOL, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*6-10000+rand()%20000, fsin(Md->Bot[i].Dir)*6-10000+rand()%20000,0,i,1);
       Shoot(BUL_BULLETSHELL, Md->Bot[i].X, Md->Bot[i].Y, -3000+rand()%6000, -8000+rand()%1000,0);
      } // if (Md->Bot[i].Ammo% Clipsize[Md->Bot[i].Item] == 0) Bot_change_clip(i); else
    } // if (Md->Bot[i].Reload == 100)
   if (Md->Bot[i].Reload == 85)
    {
     if (Md->Bot[i].Ammo% Clipsize[Md->Bot[i].Item] == 0) Bot_change_clip(i); else
      {
       Md->Bot[i].Gunfire = 5;
       Md->Bot[i].Ammo-- ;
       Shoot(BUL_PISTOL, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*6-10000+rand()%20000, fsin(Md->Bot[i].Dir)*6-10000+rand()%20000,0,i,1);
       Shoot(BUL_BULLETSHELL, Md->Bot[i].X, Md->Bot[i].Y, -3000+rand()%6000, -8000+rand()%1000,0);
      } // if (Md->Bot[i].Ammo% Clipsize[Md->Bot[i].Item] == 0) Bot_change_clip(i); else
    } // if (Md->Bot[i].Reload == 85)
   //***********************************
   if (Md->Bot[i].Reload == 10)
    Md->Bot[i].Firegun = false;
 } // Bot_Use_machinegun(int i)
void Bot_use_laserrifle(int i)
 {
  // jos latausaikaa ei ole ja panoksia on
   if (Md->Bot[i].Reload == 0)
    {
     // jos lipas on lopussa niin lataa
     if (Md->Bot[i].Ammo % Clipsize[Md->Bot[i].Item] == 0) Bot_change_clip(i); else
      {
       // muuten ammu
       // panoksia pois
       bool Found = false;
      for (int i2 = 0; i2 < Opt->Players; i2++)
       if (Md->Bot[i].X>>16 > (Md->Pl[i2].X BitR) - (Clipx>>1))
       if (Md->Bot[i].X>>16 < (Md->Pl[i2].X BitR) + (Clipx>>1))
       if (Md->Bot[i].Y>>16 > (Md->Pl[i2].Y BitR) - (Clipy>>1))
       if (Md->Bot[i].Y>>16 < (Md->Pl[i2].Y BitR) + (Clipy>>1))
        Found = true;
       if (Found)
       Playsample(Samp[SAMP_LASER], Opt->Soundvolume, 128, 0); else
        Playsample(Samp[SAMP_LASER], Opt->Soundvolume>>1, 128, 0);
       Md->Bot[i].Ammo--;
       Md->Bot[i].Gunfire = 30;
       Md->Bot[i].Reload = 30;
       // ja tärinä
       Md->Bot[i].Shake = 0;
      } //  if (Md->Bot[i].Ammo % Clipsize[Md->Bot[i].Item] == 0) Change_clip(i); else
    } // (Md->Bot[i].Reload == 0)
 } // Use_laserrifle(int i)
void Bot_use_bazooka(int i)
 {
  // jos latausaikaa ei ole ja panoksia on
   if (Md->Bot[i].Reload == 0)
    {
     // jos lipas on lopussa niin lataa
       // muuten ammu
       // panoksia pois
       // panos
       Md->Bot[i].Gunfire = 30;
       bool Found = false;
      for (int i2 = 0; i2 < Opt->Players; i2++)
       if (Md->Bot[i].X>>16 > (Md->Pl[i2].X BitR) - (Clipx>>1))
       if (Md->Bot[i].X>>16 < (Md->Pl[i2].X BitR) + (Clipx>>1))
       if (Md->Bot[i].Y>>16 > (Md->Pl[i2].Y BitR) - (Clipy>>1))
       if (Md->Bot[i].Y>>16 < (Md->Pl[i2].Y BitR) + (Clipy>>1))
        Found = true;
       if (Found)
       Playsample(Samp[SAMP_ROCKET], Opt->Soundvolume, 128, 0); else
       Playsample(Samp[SAMP_ROCKET], Opt->Soundvolume>>1, 128, 0);
  
       Shoot(BUL_ROCKET, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*6-5000+rand()%10000, fsin(Md->Bot[i].Dir)*6-5000+rand()%10000,ITEM_BAZOOKA,i,1, Md->Bot[i].Dir);
       // latausaika
       Md->Bot[i].Reload = 400;
       // ja tärinä
       Md->Bot[i].Shake = 10;
    } // (Md->Bot[i].Reload == 0)
 } // Use_bazooka(int i)
void Bot_use_homingmissilelauncher(int i)
 {
  // jos latausaikaa ei ole ja panoksia on
   if (Md->Bot[i].Reload == 0)
    {
     // jos lipas on lopussa niin lataa
       // muuten ammu
       // panoksia pois
       // panos
       Md->Bot[i].Gunfire = 30;
       bool Found = false;
      for (int i2 = 0; i2 < Opt->Players; i2++)
       if (Md->Bot[i].X>>16 > (Md->Pl[i2].X BitR) - (Clipx>>1))
       if (Md->Bot[i].X>>16 < (Md->Pl[i2].X BitR) + (Clipx>>1))
       if (Md->Bot[i].Y>>16 > (Md->Pl[i2].Y BitR) - (Clipy>>1))
       if (Md->Bot[i].Y>>16 < (Md->Pl[i2].Y BitR) + (Clipy>>1))
        Found = true;
       if (Found)
       Playsample(Samp[SAMP_ROCKET], Opt->Soundvolume, 128, 0); else
        Playsample(Samp[SAMP_ROCKET], Opt->Soundvolume>>1, 128, 0);
       Shoot(BUL_ROCKET, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*2-5000+rand()%10000, fsin(Md->Bot[i].Dir)*2-5000+rand()%10000,ITEM_HMISLAUNCHER,i,1, Md->Bot[i].Dir);
       // latausaika
       Md->Bot[i].Reload = 400;
       // ja tärinä
       Md->Bot[i].Shake = 10;
    } // (Md->Bot[i].Reload == 0)
 } // Use_homing(int i)

void Bot_use_plasmapistol(int i)
 {
   if (Md->Bot[i].Reload == 0)
    {
     // jos lipas on lopussa niin lataa
     if (Md->Bot[i].Ammo% Clipsize[Md->Bot[i].Item] == 0) Bot_change_clip(i); else
      {
       // muuten ammu
       // suuliekki
       Md->Bot[i].Gunfire = 5;
       // panoksia pois
       Md->Bot[i].Ammo -- ;
       // panos
       Shoot(BUL_PLASMA, Md->Bot[i].X, Md->Bot[i].Y, fcos(Md->Bot[i].Dir)*6-20000+rand()%40000, fsin(Md->Bot[i].Dir)*6-20000+rand()%40000,ITEM_PLASMAPISTOL,i,1);
       // pistoolin ääni
       bool Found = false;
      for (int i2 = 0; i2 < Opt->Players; i2++)
       if (Md->Bot[i].X>>16 > (Md->Pl[i2].X BitR) - (Clipx>>1))
       if (Md->Bot[i].X>>16 < (Md->Pl[i2].X BitR) + (Clipx>>1))
       if (Md->Bot[i].Y>>16 > (Md->Pl[i2].Y BitR) - (Clipy>>1))
       if (Md->Bot[i].Y>>16 < (Md->Pl[i2].Y BitR) + (Clipy>>1))
        Found = true;
       if (Found)
       Playsample(Samp[SAMP_PLASMA], Opt->Soundvolume, 128, 0); else
              Playsample(Samp[SAMP_PLASMA], Opt->Soundvolume>>1, 128, 0);
       // latausaika
       Md->Bot[i].Reload = 200;
       // ja tärinä
       Md->Bot[i].Shake = 10;
      } //  if (Md->Bot[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
    } // (Md->Pl[i].Reload == 0)
 } // void Use_superlavatrap(int i)
void Bot_attack_target(int i)
 {
  int p = Md->Bot[i].Target;
  Md->Bot[i].Visualtarget = Shockwave(Md->Pl[p].X>>16, Md->Pl[p].Y>>16, Md->Bot[i].X>>16, Md->Bot[i].Y>>16);
  Md->Bot[i].Targetdir = Direction(Md->Bot[i].X>>16, Md->Bot[i].Y>>16, Md->Pl[p].X>>16, Md->Pl[p].Y>>16);

  if (Md->Bot[i].Visualtarget==false)
   Md->Bot[i].Forgettarget++; else Md->Bot[i].Forgettarget = 0;
 if (Md->Bot[i].Forgettarget>((Md->Pl[p].Camouflaged) ? 10 : 20))
    Md->Bot[i].Target = -1;

  if (Md->Bot[i].Visualtarget==false)
   for (int i2 = 0; i2 < Opt->Players; i2++) if (i2 != p)
    if (Md->Pl[i2].Live)
    if (Distance(Md->Pl[i2].X>>16, Md->Pl[i2].Y>>16, Md->Bot[i].X>>16, Md->Bot[i].Y>>16) < Md->Bot[i].Search_range)
     if (Shockwave(Md->Bot[i].X>>16, Md->Bot[i].Y>>16, Md->Pl[i2].X>>16, Md->Pl[i2].Y>>16))
      {
       bool Findit = true;
       if (Md->Pl[i2].Camouflaged) if (Distance(Md->Pl[i2].X>>16, Md->Pl[i2].Y>>16, Md->Bot[i].X>>16, Md->Bot[i].Y>>16) > 40)
        Findit = false;
       if (Findit)
        Md->Bot[i].Target = i2;
      }

  if (Md->Pl[p].Live == false) Md->Bot[i].Target = -1;
  Md->Bot[i].Targetdist = Distance(Md->Bot[i].X>>16, Md->Bot[i].Y>>16, Md->Pl[p].X>>16, Md->Pl[p].Y>>16);
  if (Md->Bot[i].Targetdist>Md->Bot[i].Search_range<<1)Md->Bot[i].Target = -1;
  if ((Md->Bot[i].Targetdist>BOT_SEARCH_RANGE>>1)) Bot_try_to_follow(i);
  if (Md->Bot[i].Ninjaground) if (Rand()%80 == 0)
   Md->Bot[i].Ninjarope = false;

 } // void Bot_attack_target(int i)
int Bot_search_target(int i)
 {
  int p;
  bool Possible = false;
  for (int i2 = 0; i2 < Opt->Players; i2++)
   if (Md->Pl[i2].Live) if (Distance(Md->Pl[i2].X>>16, Md->Pl[i2].Y>>16, Md->Bot[i].X>>16, Md->Bot[i].Y>>16) < Md->Bot[i].Search_range)
    if (Shockwave(Md->Pl[i2].X>>16, Md->Pl[i2].Y>>16, Md->Bot[i].X>>16, Md->Bot[i].Y>>16))   Possible = true;
  int Stuck = 0;
  if (Possible)
  do
   {
    Stuck++;
    if (Stuck > 10) return -1;
    p = Rand()%Opt->Players;
    if (Distance(Md->Pl[p].X>>16, Md->Pl[p].Y>>16, Md->Bot[i].X>>16, Md->Bot[i].Y>>16) < Md->Bot[i].Search_range)
   if (Shockwave(Md->Pl[p].X>>16, Md->Pl[p].Y>>16, Md->Bot[i].X>>16, Md->Bot[i].Y>>16))
    {
     bool Findit = true;
     if (Md->Pl[p].Camouflaged) if (Distance(Md->Pl[p].X>>16, Md->Pl[p].Y>>16, Md->Bot[i].X>>16, Md->Bot[i].Y>>16) > 40)
      Findit = false;
     if (Findit)
      return p;
    }
   } while (1==1);
   return -1;
 } // int Search_target(int i)

void Update_bot_ai(int i)
 {
   int Times = 0, Speed=1;
  if (Md->Bot[i].Live)
   {
    Md->Bot[i].Counter++;
    if (Md->Bot[i].Counter > 20)
     {
      Md->Bot[i].Walking = false;
      Md->Bot[i].Counter=0;
      if (Md->Bot[i].Target==-1) Md->Bot[i].Target = Bot_search_target(i);
      if (Md->Bot[i].Target!=-1) Bot_attack_target(i);
      if (Md->Bot[i].Target==-1) Bot_walk_idle(i);
      if (Md->Bot[i].X>>16 < 10) Md->Bot[i].S= 1;
      if (Md->Bot[i].X>>16 > Lev->Mapsizex-10) Md->Bot[i].S= 0;
     } //   if (Md->Bot[i].Counter > 20)
     if (Md->Bot[i].Target!=-1)
      {
         int p = Md->Bot[i].Target; int rnd=0;
   switch(Opt->Botdifficulty)
    {
      case 1: Speed = 20; Times = 1; rnd = 10; break;
      case 2: Speed = 15; Times = 1; rnd = 6; {for (int a = 0; a < 3; a++) Md->Bot[i].Armor[a] = 1;}break;
      case 3: Speed = 10; Times = 1; rnd = 0; {for (int a = 0; a < 3; a++) Md->Bot[i].Armor[a] = 1;} break;
      case 4: Speed = 5; Times = 1; {for (int a = 0; a < 3; a++) Md->Bot[i].Armor[a] = 1;} break;
      case 5: Speed = 3; Times = 1; {for (int a = 0; a < 3; a++) Md->Bot[i].Armor[a] = 2;} break;
      case 6: Speed = 1; Times = 1; {for (int a = 0; a < 3; a++) Md->Bot[i].Armor[a] = 2;} break;
    };

            if (Md->Bot[i].Timer % Speed==0)
         Md->Bot[i].Targetdir = Direction(Md->Bot[i].X>>16, Md->Bot[i].Y>>16, Md->Pl[p].X>>16, Md->Pl[p].Y>>16)-(itofix(rnd>>1)+itofix(Rand()%(rnd+1)));

         for (int i3 = 0; i3 < 2; i3 ++)
          {
         if (Md->Bot[i].Reload) Md->Bot[i].Reload-=1;
          if (Md->Bot[i].Reload<=0) Md->Bot[i].Reloading = false;
         if ((Md->Bot[i].Dir>>16) > (Md->Bot[i].Targetdir>>16)-3)
         if ((Md->Bot[i].Dir>>16) < (Md->Bot[i].Targetdir>>16)+3)
         if (Md->Bot[i].Visualtarget)
          {
           switch(Md->Bot[i].Item)
            {
             case ITEM_PISTOL:  Bot_use_pistol(i); break;
             case ITEM_MAGNUM:  Bot_use_magnum(i); break;
             case ITEM_SHOTGUN: Bot_use_shotgun(i); break;
             case ITEM_MACHINEGUN: Bot_use_machinegun(i); break;
             case ITEM_LASERRIFLE: Bot_use_laserrifle(i); break;
             case ITEM_BAZOOKA: Bot_use_bazooka(i); break;
             case ITEM_HMISLAUNCHER: Bot_use_homingmissilelauncher(i); break;
             case ITEM_PLASMAPISTOL: Bot_use_plasmapistol(i); break;
             case ITEM_SNIPERRIFLE: Bot_use_sniperrifle(i); break;

            }; // switch(Md->Bot[i].Item)
          } // Visualtarget
      } //      if (Md->Bot[i].Target)
      }
 if (Md->Bot[i].Dir>>16 != Md->Bot[i].Targetdir>>16) Md->Bot[i].Laserbounce = -1;
   Times = 1; Speed=1;
   switch(Opt->Botdifficulty)
    {
      case 1: Speed = 4; Times = 1; break;
      case 2: Speed = 3; Times = 1; break;
      case 3: Speed = 2; Times = 1; break;
      case 4: Speed = 1; Times = 1; break;
      case 5: Speed = 1; Times = 2; break;
      case 6: Speed = 1; Times = 3; break;
    };
   Md->Bot[i].Timer++;
   if (Md->Bot[i].Timer % Speed==0)
    for (int speeder = 0; speeder < Times; speeder++)
     Rotateangle(&Md->Bot[i].Dir, Md->Bot[i].Targetdir);
   Md->Bot[i].Dir = Suunta(Md->Bot[i].Dir);
  Md->Bot[i].Gs = 1;
   if (fixtoi(Md->Bot[i].Dir) >= 64)
    if (fixtoi(Md->Bot[i].Dir) <= 192) Md->Bot[i].Gs = 0;
  } //   if (Md->Bot[i].Live)
 } // void Update_bot_ai(int i)
#endif

