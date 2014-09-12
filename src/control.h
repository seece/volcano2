/*
  Pelaajien kontrollointi
*/
#ifndef __control_h
#define __control_h
void Buyvehicle(int i, int t);
void Buyitem(int i,int t);  // ostaa tavaran
void Buyammo(int i,int t);  // ostaa panoksia
void PlayerLeft(int i);     // pelaaja painaa  vasemmalle
void PlayerRight(int i);    // ---             oikealle
void PlayerUp(int i);       // ---             ylös
void PlayerDown(int i);     // ---             alas
void PlayerJump(int i);     // hyppää
void PlayerNinjarope(int i);// viskoo ninjaropen
void PlayerUse(int i);      // käyttää tavaraa
void PlayerChange(int i);   // painaa change nappulaa(menut)
void Checkkeys();           // tarkistaa mitä nappeja pelaaja painaa

void Buyvehicle(int i, int t)
{
    if (Md->Pl[i].Money >= Vehiclecost[t])
    {
        Md->Pl[i].Money -= Vehiclecost[t];
        Addvehicle(Md->Pl[i].X, Md->Pl[i].Y, 0, -10000, t);
    } // if (Md->Pl[i].Money >= Vehiclecost[t])
} // void Buyvehicle(int i, int t)
void Buyitem(int i, int t)
{
    // jos on rahaa ja jaksaa kantaa
    if (Md->Pl[i].Money>= Itemcost[t])
        if (Md->Pl[i].Stuff[t] < Stufflimit[t])
        {
            // vähennetään hinta
            Md->Pl[i].Money -= Itemcost[t];
            // lisätään tavara
            Md->Pl[i].Stuff[t]++;
            if (Canitemselect[t])
                Md->Pl[i].Item = t;
            // jos tulee lipas mukaan niin otetaan sellainenkin
            if (Weaponclip[t]!=-1)
                Md->Pl[i].Ammo[Weaponclip[t]]+= Clipsize[t];
            // jos piippua pitää vaihtaa niin vaihdetaan
            if (Weapongunpic[t]>-1) Md->Pl[i].Gun = Weapongunpic[t];
        } // if (Md->Pl[i].Stuff[t] < Stufflimit[t])
} // Buyitem
void Buyammo(int i, int t)
{
    // jos on ase mihin panokset käy ja rahaa ja jaksaa kantaa
    if (Md->Pl[i].Stuff[t]>0)
        if (Md->Pl[i].Money>= Bulletcost[Weaponclip[t]])
            if (Md->Pl[i].Ammo[Weaponclip[t]] < Bulletlimit[Weaponclip[t]])
            {
                // raha vaihtaa omistajaa
                Md->Pl[i].Money -= Bulletcost[Weaponclip[t]];
                // samoin panokset
                if (Weaponclip[t]!= -1)
                    Md->Pl[i].Ammo[Weaponclip[t]]+= Clipsize[t];
                Md->Pl[i].Item = t;
                // jos piippua vaihdetaan niin vaihdetaan
                if (Weapongunpic[t]>-1) Md->Pl[i].Gun = Weapongunpic[t];
            } // if (Md->Pl[i].Stuff[t] < Stufflimit[t])
} // Buyitem
void PlayerLeft(int i)
{
    if (Md->Pl[i].Live)
    {
        if ((Md->Pl[i].Action == 0) || (Md->Pl[i].Action == ACTION_LASERCANNON))
        {
            if (Md->Pl[i].Menu == -1) // jos menu ei ole aktiivinen
            {
                Md->Pl[i].Laserbounce = -1;
                if (Md->Pl[i].S == 1) // jos pelaaja katsoo oikealle niin käännös
                {
                    Md->Pl[i].S = 0;
                    Md->Pl[i].Dir = Suunta(itofix(128)- Md->Pl[i].Dir);
                } // (Md->Pl[i].S == 0)
                if (Md->Pl[i].Action == 0)
                    Md->Pl[i].Walking = true;
                // kävelyanimaatio päälle ja vauhtia
            } else// if (Md->Pl[i].Menu == -1)
            {
                key[Opt->Nap[i].Left] = 0;
                // jos menussa niin kohdistinta liikutetaan
                if (Md->Pl[i].Select[Md->Pl[i].Menu]) Md->Pl[i].Select[Md->Pl[i].Menu]--;
            } // if (Md->Pl[i].Menu == -1);
        } // Action == 0
        if (Md->Pl[i].Action == ACTION_SETPLATE)
        {
            if (Distance(Md->Pl[i].X>>16, Md->Pl[i].Y>>16, Md->Pl[i].Actionx-1, Md->Pl[i].Actiony)<100)
                if (getpixel(Md->Map, Md->Pl[i].Actionx-1, Md->Pl[i].Actiony) == 0)
                    if (getpixel(Md->Map, Md->Pl[i].Actionx-5, Md->Pl[i].Actiony-4) == 0)
                        if (getpixel(Md->Map, Md->Pl[i].Actionx-5, Md->Pl[i].Actiony+5) == 0)
                            Md->Pl[i].Actionx--;
        } // if (Md->Pl[i].Action == ACTION_SETPLATE)
        if (Md->Pl[i].Action == ACTION_SNIPER)
        {
            if (Md->Pl[i].Actionx) if (Strictshockwave(Md->Pl[i].X BitR, Md->Pl[i].Y BitR, Md->Pl[i].Actionx-2, Md->Pl[i].Actiony)) Md->Pl[i].Actionx-=2;
            Md->Pl[i].Dir = Direction(Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Actionx BitL, Md->Pl[i].Actiony BitL);
            if (Suunta(Md->Pl[i].Dir-itofix(64)) >= itofix(128)) Md->Pl[i].S = 1;
            else Md->Pl[i].S = 0;
        } // if (Md->Pl[i].Action == ACTION_SETPLATE)
    } else// live
    {
        Md->Pl[i].Sx-=1;
        if (Md->Pl[i].Sx<0) Md->Pl[i].Sx = 0;
    }
} // PlayerLeft(int i)
void PlayerRight(int i)
{
    if (Md->Pl[i].Live)
    {
        if ((Md->Pl[i].Action == 0) || (Md->Pl[i].Action == ACTION_LASERCANNON))
        {
            if (Md->Pl[i].Menu == -1) // jos menu ei ole aktiivinen
            {
                Md->Pl[i].Laserbounce = -1;
                if (Md->Pl[i].S == 0) // pelaaja katsoo vasemmalle niin käännös
                {
                    Md->Pl[i].S = 1;
                    Md->Pl[i].Dir = Suunta(itofix(128)- Md->Pl[i].Dir);
                } // (Md->Pl[i].S == 0)
                if (Md->Pl[i].Action == 0)
                    Md->Pl[i].Walking = true;
                // kävely päälle
            } else// if (Md->Pl[i].Menu == -1)
            {
                key[Opt->Nap[i].Right] = 0;
                // jos menussa niin liikutetaan kohdistinta
                switch(Md->Pl[i].Menu)
                {
                case MENU_BUYBUILD:
                    if (Md->Pl[i].Select[Md->Pl[i].Menu] < 3) Md->Pl[i].Select[Md->Pl[i].Menu]++;
                    break;
                case MENU_INVENTORY:
                    if (Md->Pl[i].Select[Md->Pl[i].Menu] < Maxstuff) Md->Pl[i].Select[Md->Pl[i].Menu]++;
                case MENU_MAIN:
                    if (Md->Pl[i].Select[Md->Pl[i].Menu] < 1) Md->Pl[i].Select[Md->Pl[i].Menu]++;
                    break;
                case MENU_BUY:
                    if (Md->Pl[i].Select[Md->Pl[i].Menu] < 2) Md->Pl[i].Select[Md->Pl[i].Menu]++;
                    break;
                case MENU_BUYWEAPONS:
                    if (Md->Pl[i].Select[Md->Pl[i].Menu] < 2) Md->Pl[i].Select[Md->Pl[i].Menu]++;
                    break;
                case MENU_BUYPROJECTW:
                    if (Md->Pl[i].Select[Md->Pl[i].Menu] < 7) Md->Pl[i].Select[Md->Pl[i].Menu]++;
                    break;
                case MENU_BUYENERGYW:
                    if (Md->Pl[i].Select[Md->Pl[i].Menu] < 5) Md->Pl[i].Select[Md->Pl[i].Menu]++;
                    break;
                case MENU_BUYTOOLS:
                    if (Md->Pl[i].Select[Md->Pl[i].Menu] < 3) Md->Pl[i].Select[Md->Pl[i].Menu]++;
                    break;
                case MENU_BUYARMOR:
                    if (Md->Pl[i].Select[Md->Pl[i].Menu] < 6) Md->Pl[i].Select[Md->Pl[i].Menu]++;
                    break;
                case MENU_BUYTOOLS2:
                    if (Md->Pl[i].Select[Md->Pl[i].Menu] < 4) Md->Pl[i].Select[Md->Pl[i].Menu]++;
                    break;
                case MENU_BUYAMMO:
                    if (Md->Pl[i].Select[Md->Pl[i].Menu] < 7) Md->Pl[i].Select[Md->Pl[i].Menu]++;
                    break;
                case MENU_BUYBOMBS:
                    if (Md->Pl[i].Select[Md->Pl[i].Menu] < 2) Md->Pl[i].Select[Md->Pl[i].Menu]++;
                    break;
                case MENU_BUYVEHICLES:
                    if (Md->Pl[i].Select[Md->Pl[i].Menu] < 1) Md->Pl[i].Select[Md->Pl[i].Menu]++;
                    break;


                };
            } // if (Md->Pl[i].Menu == -1);
        } // Action == 0
        if (Md->Pl[i].Action == ACTION_SETPLATE)
        {
            if (Distance(Md->Pl[i].X>>16, Md->Pl[i].Y>>16, Md->Pl[i].Actionx+1, Md->Pl[i].Actiony)<100)
                if (getpixel(Md->Map, Md->Pl[i].Actionx+1, Md->Pl[i].Actiony) == 0)
                    if (getpixel(Md->Map, Md->Pl[i].Actionx+6, Md->Pl[i].Actiony-4) == 0)
                        if (getpixel(Md->Map, Md->Pl[i].Actionx+6, Md->Pl[i].Actiony+5) == 0)
                            Md->Pl[i].Actionx++;
        } // if (Md->Pl[i].Action == ACTION_SETPLATE)
        if (Md->Pl[i].Action == ACTION_SNIPER)
        {
            if (Md->Pl[i].Actionx < Lev->Mapsizex-1)
                if (Strictshockwave(Md->Pl[i].X BitR, Md->Pl[i].Y BitR, Md->Pl[i].Actionx+2, Md->Pl[i].Actiony))
                    Md->Pl[i].Actionx+=2;
            Md->Pl[i].Dir = Direction(Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Actionx BitL, Md->Pl[i].Actiony BitL);
            if (Suunta(Md->Pl[i].Dir-itofix(64)) >= itofix(128)) Md->Pl[i].S = 1;
            else Md->Pl[i].S = 0;
        } // if (Md->Pl[i].Action == ACTION_SNIPER)

    } // Live
    {
        Md->Pl[i].Sx+=1;
        if (Md->Pl[i].Sx >= Lev->Mapsizex-Clipx) Md->Pl[i].Sx = Lev->Mapsizex-Clipx-1;
    }
} // PlayerRight(int i)
void PlayerUp(int i)
{
    if (Md->Pl[i].Live)
    {
        if ((Md->Pl[i].Action == 0) || (Md->Pl[i].Action == ACTION_LASERCANNON))
        {
            if (Md->Pl[i].Menu == -1) // jos menu ei ole aktiivinen
            {
                Md->Pl[i].Laserbounce = -1;
                if (Md->Pl[i].S == 0) // pelaaja katsoo vasemmalle
                    Md->Pl[i].Dir = Suunta(Md->Pl[i].Dir+itofix(1));
                else
                    Md->Pl[i].Dir = Suunta(Md->Pl[i].Dir-itofix(1));
                if (Md->Pl[i].S == 1) // oikealle
                    if (Md->Pl[i].Dir <= itofix(192))
                        if (Md->Pl[i].Dir >= itofix(190))
                        {
                            Md->Pl[i].Dir = itofix(192);
                        }
                if (Md->Pl[i].S == 0) // ja vasemmalle
                    if (Md->Pl[i].Dir >= itofix(190))
                        if (Md->Pl[i].Dir <= itofix(195))
                        {
                            Md->Pl[i].Dir = itofix(192);
                        }
            } // if (Md->Pl[i].Menu == -1)
        } // action == 0
        if (Md->Pl[i].Action == ACTION_SETPLATE)
        {
            if (Distance(Md->Pl[i].X>>16, Md->Pl[i].Y>>16, Md->Pl[i].Actionx, Md->Pl[i].Actiony-1)<100)
                if (getpixel(Md->Map, Md->Pl[i].Actionx, Md->Pl[i].Actiony-1) == 0)
                    if (getpixel(Md->Map, Md->Pl[i].Actionx-4, Md->Pl[i].Actiony-5) == 0)
                        if (getpixel(Md->Map, Md->Pl[i].Actionx+5, Md->Pl[i].Actiony-5) == 0)
                            Md->Pl[i].Actiony--;
        } // if (Md->Pl[i].Action == ACTION_SETPLATE)
        if (Md->Pl[i].Action == ACTION_SNIPER)
        {
            if (Md->Pl[i].Actiony) if (Strictshockwave(Md->Pl[i].X BitR, Md->Pl[i].Y BitR, Md->Pl[i].Actionx, Md->Pl[i].Actiony-2)) Md->Pl[i].Actiony-=2;
            Md->Pl[i].Dir = Direction(Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Actionx BitL, Md->Pl[i].Actiony BitL);
            if (Suunta(Md->Pl[i].Dir-itofix(64)) >= itofix(128)) Md->Pl[i].S = 1;
            else Md->Pl[i].S = 0;

        } // if (Md->Pl[i].Action == ACTION_SETPLATE)
    } else
    {
        Md->Pl[i].Sy-=1;
        if (Md->Pl[i].Sy<0) Md->Pl[i].Sy = 0;
    }

} // PlayerUp(int i)
void PlayerDown(int i)
{
    if (Md->Pl[i].Live)
    {
        if ((Md->Pl[i].Action == 0) || (Md->Pl[i].Action == ACTION_LASERCANNON))
        {
            Md->Pl[i].Laserbounce = -1;
            if (Md->Pl[i].Menu == -1) // jos menu ei ole aktiivinen
            {
                if (Md->Pl[i].S == 0) // ja pelaaja katsoo vasemmalle
                    Md->Pl[i].Dir = Suunta(Md->Pl[i].Dir-itofix(1));
                else
                    Md->Pl[i].Dir = Suunta(Md->Pl[i].Dir+itofix(1));
                if (Md->Pl[i].S == 1) // oikealle
                    if (Md->Pl[i].Dir > itofix(60))
                        if (Md->Pl[i].Dir < itofix(62))
                            Md->Pl[i].Dir = itofix(60);
                if (Md->Pl[i].S == 0) // ja vasemmalle
                    if (Md->Pl[i].Dir < itofix(68))
                        if (Md->Pl[i].Dir > itofix(66))
                            Md->Pl[i].Dir = itofix(68);
            } // if (Md->Pl[i].Menu == -1)
        } // Action == 0
        if (Md->Pl[i].Action == ACTION_SETPLATE)
        {
            if (Distance(Md->Pl[i].X>>16, Md->Pl[i].Y>>16, Md->Pl[i].Actionx, Md->Pl[i].Actiony+1)<100)
                if (getpixel(Md->Map, Md->Pl[i].Actionx, Md->Pl[i].Actiony+1) == 0)
                    if (getpixel(Md->Map, Md->Pl[i].Actionx+5, Md->Pl[i].Actiony+6) == 0)
                        if (getpixel(Md->Map, Md->Pl[i].Actionx-4, Md->Pl[i].Actiony+6) == 0)
                            Md->Pl[i].Actiony++;
        } // if (Md->Pl[i].Action == ACTION_SETPLATE)
        if (Md->Pl[i].Action == ACTION_SNIPER)
        {
            if (Md->Pl[i].Actiony < Lev->Mapsizey-1) if (Strictshockwave(Md->Pl[i].X BitR, Md->Pl[i].Y BitR, Md->Pl[i].Actionx, Md->Pl[i].Actiony+2)) Md->Pl[i].Actiony+=2;
            Md->Pl[i].Dir = Direction(Md->Pl[i].X, Md->Pl[i].Y, Md->Pl[i].Actionx BitL, Md->Pl[i].Actiony BitL);
            if (Suunta(Md->Pl[i].Dir-itofix(64)) >= itofix(128)) Md->Pl[i].S = 1;
            else Md->Pl[i].S = 0;
        } // if (Md->Pl[i].Action == ACTION_SETPLATE)

    } else
    {
        Md->Pl[i].Sy+=1;
        if (Md->Pl[i].Sy >= Lev->Mapsizey-Clipy) Md->Pl[i].Sy = Lev->Mapsizey-Clipy-1;
    }
} // PlayerDown(int i)
void PlayerJump(int i)
{

    if (Md->Pl[i].Action == 0)
    {
        if (Md->Pl[i].Ninjarope == false)
            if (Md->Pl[i].Live)
                if (!Md->Pl[i].FeetOnGround)
                    if (Md->Pl[i].Stuff[ITEM_PARACHUTE]) if (Md->Pl[i].My>40000)
                            if (Md->Pl[i].Parachuteshotdown == false)
                            {
                                Md->Pl[i].Parachute = (Md->Pl[i].Parachute == false);
                                key[Opt->Nap[i].Jump] = 0;
                            } //     if (Md->Pl[i].Ninjarope == false)     if (Md->Pl[i].Live)      if (!Md->Pl[i].FeetOnGround)

        Md->Pl[i].Laserbounce = -1;
        Md->Pl[i].Ninjarope = false;
        if (Md->Pl[i].Live) if (Md->Pl[i].Menu == -1) // jos ei ole menussa niin
                if (Md->Pl[i].FeetOnGround)                  // hyppää
                {
                    key[Opt->Nap[i].Jump] = 0;
                    Md->Pl[i].Jump = true;
                    Md->Pl[i].My = -52000;
                } // (Md->Pl[i].FeetOnGround)
    }
} // PlayerJump(int i)
void PlayerNinjarope(int i)
{
    if (Md->Pl[i].Action == 0)
    {
        if (Md->Pl[i].Menu == -1) // jos ei ole menussa niin heitä ninjarope
        {
            Md->Pl[i].Parachute = false;
            Md->Pl[i].Ninjadir = Md->Pl[i].Dir;
            Md->Pl[i].Ninjarope = true;
            Md->Pl[i].Ninjaground = false;
            Md->Pl[i].Nmx = int(fcos(Md->Pl[i].Dir)*4)+(Md->Pl[i].Mx>>1);
            Md->Pl[i].Nmy = int(fsin(Md->Pl[i].Dir)*4)+(Md->Pl[i].My>>1);
            Md->Pl[i].Nx = Md->Pl[i].X;
            Md->Pl[i].Ny = Md->Pl[i].Y;
            Md->Pl[i].Ropeset = 20;
        } // if (Md->Pl[i].Menu == -1)
    } // Action
} // PlayerNinjarope(int i)
void PlayerUse(int i)
{
    if (Md->Pl[i].Action == ACTION_SETPLATE) if (key[Opt->Nap[i].Use])
        {
            if (Md->Pl[i].Stuff[Md->Pl[i].Item]>0)
            {
                Md->Pl[i].Stuff[Md->Pl[i].Item] -- ;
                int Type=0;
                switch(Md->Pl[i].Item)
                {
                case ITEM_PLATE:
                    Type = BLD_PLATE;
                    break;
                case ITEM_REINFPLATE:
                    Type = BLD_REINFPLATE;
                    break;
                };
                Addbuilding(Type, Md->Pl[i].Actionx<<16, Md->Pl[i].Actiony<<16, 0, 0);
            } //     if (Md->Pl[i].Stuff[Md->Pl[i].Item]>0)

            Md->Pl[i].Action = 0;
            key[Opt->Nap[i].Use] = 0;

        } //   if (Action == ACTION_SETPLATE)
    if (Md->Pl[i].Action == ACTION_SNIPER) if (key[Opt->Nap[i].Use]) if (Md->Pl[i].Live)
            {
                Md->Pl[i].Nocamo = 50;
                Use_sniper(i);
                key[Opt->Nap[i].Use] = 0;
            } //   if (Action == ACTION_SNIPER
    if (Md->Pl[i].Action == 0) if (key[Opt->Nap[i].Use])
        {
            // jos pelaaja ei ole lataamassa eikä menu ole aktiivinen
            if (Md->Pl[i].Live) if (Md->Pl[i].Reloading == false) if (Md->Pl[i].Menu == -1)
                    {
                        switch(Md->Pl[i].Item)
                        {
                        case ITEM_PISTOL        :
                            Use_pistol(i);
                            break;
                        case ITEM_MACHINEGUN    :
                            Use_machinegun(i);
                            break;
                        case ITEM_BIGMACHINEGUN    :
                            Use_bigmachinegun(i);
                            break;
                        case ITEM_LAVATRAP      :
                            Use_lavatrap(i);
                            break;
                        case ITEM_SUPERLAVATRAP :
                            Use_superlavatrap(i);
                            break;
                        case ITEM_MAGNUM        :
                            Use_magnum(i);
                            break;
                        case ITEM_SHOTGUN       :
                            Use_shotgun(i);
                            break;
                        case ITEM_GRENADE       :
                            Use_grenade(i);
                            break;
                        case ITEM_BAZOOKA       :
                            Use_bazooka(i);
                            break;
                        case ITEM_HMISLAUNCHER  :
                            Use_homingmissilelauncher(i);
                            break;
                        case ITEM_LASERRIFLE    :
                            Use_laserrifle(i);
                            break;
                        case ITEM_LASERCANNON   :
                            Use_lasercannon(i);
                            break;
                        case ITEM_LASERPISTOL   :
                            Use_laserrifle(i);
                            break;
                        case ITEM_PICKAXE       :
                            Use_pickaxe(i);
                            break;
                        case ITEM_DRILL         :
                            Use_drill(i);
                            break;
                        case ITEM_LAVABOMB      :
                            Use_lavabomb(i);
                            break;
                        case ITEM_SELFDESTRUCTOR:
                            Use_selfdestructor_remote(i);
                            break;
                        case ITEM_PLASMAPISTOL  :
                            Use_plasmapistol(i);
                            break;
                        case ITEM_HEAVYPLASMA   :
                            Use_heavyplasma(i);
                            break;
                        case ITEM_LASERSABRE    :
                            Use_lasersabre(i);
                            break;
                        case ITEM_SNIPERRIFLE:
                            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]])
                            {
                                if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i);
                                if (Md->Pl[i].Reload == 0)
                                {
                                    key[Opt->Nap[i].Use] = 0;
                                    Md->Pl[i].Actionx = (Md->Pl[i].X+fcos(Md->Pl[i].Dir)*15)>>16;
                                    Md->Pl[i].Actiony = (Md->Pl[i].Y+fsin(Md->Pl[i].Dir)*15)>>16;
                                    if (Md->Pl[i].Stuff[Md->Pl[i].Item]) Md->Pl[i].Action = ACTION_SNIPER;
                                } // if (Md->Pl[i].Reload == 0)
                            }
                            break;
                        case ITEM_PLATE         :
                        case ITEM_REINFPLATE    :
                            key[Opt->Nap[i].Use] = 0;
                            Md->Pl[i].Actionx = Md->Pl[i].X>>16;
                            Md->Pl[i].Actiony = Md->Pl[i].Y>>16;
                            if (Md->Pl[i].Stuff[Md->Pl[i].Item]) Md->Pl[i].Action = ACTION_SETPLATE;
                            break;
                        case ITEM_MEDIKIT:
                            if (Md->Pl[i].Stuff[Md->Pl[i].Item])
                            {
                                key[Opt->Nap[i].Use] = 0;
                                Md->Pl[i].Stuff[Md->Pl[i].Item]--;
                                for (int i2 = 0; i2 < 3; i2++) // Ei damagea
                                    Md->Pl[i].Damage[i2] = 0;
                                for (int i2 = 0; i2 < 3; i2++)
                                    Md->Pl[i].Hits[i2] = 0;
                                Md->Pl[i].Item = Md->Pl[i].Lastweapon;
                                Md->Pl[i].Gun = Weapongunpic[Md->Pl[i].Lastweapon];
                            } // if (Md->Pl[i].Stuff[Md->Pl[i].Item])
                            break; // case ITEM_MEDIKIT:
                        }; // switch(Md->Pl[i].Weapon)
                        Md->Pl[i].Nocamo = 50;
                    } // if ei menu

            if (Md->Pl[i].Menu != -1) // jos pelaaja on menussa
            {
                int Vanhamenu = Md->Pl[i].Menu;
                key[Opt->Nap[i].Use] = 0;
                // inventoryssä.... valitaan tavara
                if (Md->Pl[i].Menu == MENU_INVENTORY) if (Md->Pl[i].Inv[Md->Pl[i].Select[Vanhamenu]] > -1)
                        if (Canitemselect[Md->Pl[i].Inv[Md->Pl[i].Select[Vanhamenu]]])
                        {
                            Md->Pl[i].Item = Md->Pl[i].Inv[Md->Pl[i].Select[Vanhamenu]];
                            Md->Pl[i].Gun = Weapongunpic[Md->Pl[i].Item];
                            Md->Pl[i].Reload = 50;


                        } // if (Md->Pl[i].Menu == MENU_INVENTORY)
                // ostetaan kamaa
                if (Md->Pl[i].Menu == MENU_BUYPROJECTW)
                {
                    if (Md->Pl[i].Select[Vanhamenu] == 0) {
                        if (Md->Pl[i].Stuff[ITEM_PISTOL] ==0) Buyitem(i, ITEM_PISTOL);
                        else Buyammo(i, ITEM_PISTOL);
                    }
                    if (Md->Pl[i].Select[Vanhamenu] == 1) {
                        if (Md->Pl[i].Stuff[ITEM_MAGNUM] ==0) Buyitem(i, ITEM_MAGNUM);
                        else Buyammo(i, ITEM_MAGNUM);
                    }
                    for (int speeder = 0; speeder < 5; speeder++)
                        if (Md->Pl[i].Select[Vanhamenu] == 2) {
                            if (Md->Pl[i].Stuff[ITEM_SHOTGUN] ==0) Buyitem(i, ITEM_SHOTGUN);
                            else Buyammo(i, ITEM_SHOTGUN);
                        }
                    if (Md->Pl[i].Select[Vanhamenu] == 3) {
                        if (Md->Pl[i].Stuff[ITEM_MACHINEGUN] ==0) Buyitem(i, ITEM_MACHINEGUN);
                        else Buyammo(i, ITEM_MACHINEGUN);
                    }
                    if (Md->Pl[i].Select[Vanhamenu] == 4) {
                        if (Md->Pl[i].Stuff[ITEM_BIGMACHINEGUN] ==0) Buyitem(i, ITEM_BIGMACHINEGUN);
                        else Buyammo(i, ITEM_BIGMACHINEGUN);
                    }
                    if (Md->Pl[i].Select[Vanhamenu] == 5) {
                        if (Md->Pl[i].Stuff[ITEM_BAZOOKA] ==0) Buyitem(i, ITEM_BAZOOKA);
                        else Buyammo(i, ITEM_BAZOOKA);
                    }
                    if (Md->Pl[i].Select[Vanhamenu] == 6) {
                        if (Md->Pl[i].Stuff[ITEM_HMISLAUNCHER] ==0) Buyitem(i, ITEM_HMISLAUNCHER);
                        else Buyammo(i, ITEM_HMISLAUNCHER);
                    }
                    if (Md->Pl[i].Select[Vanhamenu] == 7) {
                        if (Md->Pl[i].Stuff[ITEM_SNIPERRIFLE] ==0) Buyitem(i, ITEM_SNIPERRIFLE);
                        else Buyammo(i, ITEM_SNIPERRIFLE);
                    }
                } // if (Md->Pl[i].Menu == MENU_BUYPROJECTW)
                if (Md->Pl[i].Menu == MENU_BUYTOOLS2)
                {
                    if (Md->Pl[i].Select[Vanhamenu] == 0) Buyitem(i, ITEM_PICKAXE);
                    if (Md->Pl[i].Select[Vanhamenu] == 1) Buyitem(i, ITEM_DRILL);
                    if (Md->Pl[i].Select[Vanhamenu] == 2) Buyitem(i, ITEM_TARGETINGSYSTEM);
                    if (Md->Pl[i].Select[Vanhamenu] == 3) Buyitem(i, ITEM_MEDIKIT);
                    if (Md->Pl[i].Select[Vanhamenu] == 4) Buyitem(i, ITEM_PARACHUTE);
                } // if (Md->Pl[i].Menu == MENU_BUYTOOLS2)
                if (Md->Pl[i].Menu == MENU_BUYARMOR)
                {
                    if (Md->Pl[i].Select[Vanhamenu] == 0) if (Md->Pl[i].Money >= 1000)
                            if (Md->Pl[i].Armor[0]==0)
                            {
                                Md->Pl[i].Armor[0] = 1;
                                Md->Pl[i].Money -= 1000;
                            } //       if (Md->Pl[i].Select[Vanhamenu] == 0)
                    if (Md->Pl[i].Select[Vanhamenu] == 1) if (Md->Pl[i].Money >= 1000)
                            if (Md->Pl[i].Armor[1]==0)
                            {
                                Md->Pl[i].Armor[1] = 1;
                                Md->Pl[i].Money -= 1000;
                            } //       if (Md->Pl[i].Select[Vanhamenu] == 0)
                    if (Md->Pl[i].Select[Vanhamenu] == 2) if (Md->Pl[i].Money >= 1000)
                            if (Md->Pl[i].Armor[2]==0)
                            {
                                Md->Pl[i].Armor[2] = 1;
                                Md->Pl[i].Money -= 1000;
                            } //       if (Md->Pl[i].Select[Vanhamenu] == 0)
                    if (Md->Pl[i].Select[Vanhamenu] == 3) if (Md->Pl[i].Money >= 2000)
                            if (Md->Pl[i].Armor[0]<2)
                            {
                                Md->Pl[i].Armor[0] = 2;
                                Md->Pl[i].Money -= 2000;
                            } //       if (Md->Pl[i].Select[Vanhamenu] == 0)
                    if (Md->Pl[i].Select[Vanhamenu] == 4) if (Md->Pl[i].Money >= 2000)
                            if (Md->Pl[i].Armor[1]<2)
                            {
                                Md->Pl[i].Armor[1] = 2;
                                Md->Pl[i].Money -= 2000;
                            } //       if (Md->Pl[i].Select[Vanhamenu] == 0)
                    if (Md->Pl[i].Select[Vanhamenu] == 5) if (Md->Pl[i].Money >= 2000)
                            if (Md->Pl[i].Armor[2]<2)
                            {
                                Md->Pl[i].Armor[2] = 2;
                                Md->Pl[i].Money -= 2000;
                            } //       if (Md->Pl[i].Select[Vanhamenu] == 0)
                    if (Md->Pl[i].Select[Vanhamenu] == 6) Buyitem(i, ITEM_CAMOUFLAGE);
                } // if (Md->Pl[i].Menu == MENU_BUYARMOR)
                if (Md->Pl[i].Menu == MENU_BUYAMMO)
                {
                    if (Md->Pl[i].Select[Vanhamenu] == 0) {
                        if (Md->Pl[i].Item == ITEM_PISTOL) Buyammo(i, ITEM_PISTOL);
                        else Buyammo(i, ITEM_MACHINEGUN);
                    }
                    if (Md->Pl[i].Select[Vanhamenu] == 1)Buyammo(i, ITEM_SHOTGUN);
                    if (Md->Pl[i].Select[Vanhamenu] == 2) {
                        if (Md->Pl[i].Item == ITEM_MAGNUM) Buyammo(i, ITEM_MAGNUM);
                        else Buyammo(i, ITEM_SNIPERRIFLE);
                    }
                    if (Md->Pl[i].Select[Vanhamenu] == 3) Buyammo(i, ITEM_BIGMACHINEGUN);
                    if (Md->Pl[i].Select[Vanhamenu] == 4) Buyammo(i, ITEM_BAZOOKA);
                    if (Md->Pl[i].Select[Vanhamenu] == 5) Buyammo(i, ITEM_HMISLAUNCHER);
                    if (Md->Pl[i].Select[Vanhamenu] == 6) {
                        if (Md->Pl[i].Item == ITEM_LASERPISTOL) Buyammo(i, ITEM_LASERPISTOL);
                        else Buyammo(i, ITEM_LASERRIFLE);
                    }
                    if (Md->Pl[i].Select[Vanhamenu] == 7) {
                        if (Md->Pl[i].Item == ITEM_PLASMAPISTOL) Buyammo(i, ITEM_PLASMAPISTOL);
                        else Buyammo(i, ITEM_HEAVYPLASMA);
                    }
                } // if (Md->Pl[i].Menu == MENU_BUYPROJECTW)
                if (Md->Pl[i].Menu == MENU_BUYBUILD)
                {
                    if (Md->Pl[i].Select[Vanhamenu] == 0) Buyitem(i, ITEM_LAVATRAP);
                    if (Md->Pl[i].Select[Vanhamenu] == 1) Buyitem(i, ITEM_SUPERLAVATRAP);
                    if (Md->Pl[i].Select[Vanhamenu] == 2) Buyitem(i, ITEM_PLATE);
                    if (Md->Pl[i].Select[Vanhamenu] == 3) Buyitem(i, ITEM_REINFPLATE);
                } // if (Md->Pl[i].Menu == MENU_BUYBUILD)
                if (Md->Pl[i].Menu == MENU_BUYBOMBS)
                {
                    if (Md->Pl[i].Select[Vanhamenu] == 0) Buyitem(i, ITEM_GRENADE);
                    if (Md->Pl[i].Select[Vanhamenu] == 1) Buyitem(i, ITEM_LAVABOMB);
                    if (Md->Pl[i].Select[Vanhamenu] == 2) Buyitem(i, ITEM_SELFDESTRUCTOR);
                } // if (Md->Pl[i].Menu == MENU_BUYBUILD)
                if (Md->Pl[i].Menu == MENU_BUYENERGYW)
                {
                    if (Md->Pl[i].Select[Vanhamenu] == 0) {
                        if (Md->Pl[i].Stuff[ITEM_LASERSABRE]==0) Buyitem(i, ITEM_LASERSABRE);
                    }
                    if (Md->Pl[i].Select[Vanhamenu] == 1) {
                        if (Md->Pl[i].Stuff[ITEM_LASERPISTOL]==0) Buyitem(i, ITEM_LASERPISTOL);
                        else Buyammo(i, ITEM_LASERPISTOL);
                    }
                    if (Md->Pl[i].Select[Vanhamenu] == 2) {
                        if (Md->Pl[i].Stuff[ITEM_LASERRIFLE]==0) Buyitem(i, ITEM_LASERRIFLE);
                        else Buyammo(i, ITEM_LASERRIFLE);
                    }
                    if (Md->Pl[i].Select[Vanhamenu] == 3) {
                        if (Md->Pl[i].Stuff[ITEM_LASERCANNON]==0) Buyitem(i, ITEM_LASERCANNON);
                        else Buyammo(i, ITEM_LASERCANNON);
                    }
                    if (Md->Pl[i].Select[Vanhamenu] == 4) {
                        if (Md->Pl[i].Stuff[ITEM_PLASMAPISTOL]==0) Buyitem(i, ITEM_PLASMAPISTOL);
                        else Buyammo(i, ITEM_PLASMAPISTOL);
                    }
                    if (Md->Pl[i].Select[Vanhamenu] == 5) {
                        if (Md->Pl[i].Stuff[ITEM_HEAVYPLASMA]==0) Buyitem(i, ITEM_HEAVYPLASMA);
                        else Buyammo(i, ITEM_HEAVYPLASMA);
                    }
                } // if (Md->Pl[i].Menu == MENU_BUYENERGYW)
                if (Md->Pl[i].Menu == MENU_BUYTOOLS)
                {
                    if (Md->Pl[i].Select[Vanhamenu] == 0) Md->Pl[i].Menu = MENU_BUYTOOLS2;
                    if (Md->Pl[i].Select[Vanhamenu] == 1) Md->Pl[i].Menu = MENU_BUYBUILD;
                    if (Md->Pl[i].Select[Vanhamenu] == 2) Md->Pl[i].Menu = MENU_BUYARMOR;
// PUBLISHVERSIO      if (Md->Pl[i].Select[Vanhamenu] == 3) Md->Pl[i].Menu = MENU_BUYVEHICLES;
                } // if (Md->Pl[i].Menu == MENU_BUYTOOLS)
                if (Md->Pl[i].Menu == MENU_BUYVEHICLES)
                {
                    if (Md->Pl[i].Select[Vanhamenu] == 0) Buyvehicle(i, VEH_WALKER);
                    if (Md->Pl[i].Select[Vanhamenu] == 1) Buyvehicle(i, VEH_WALKER);
                } // if (Md->Pl[i].Menu == MENU_BUYVEHICLES)


                if (Md->Pl[i].Menu == MENU_BUYWEAPONS) if (Md->Pl[i].Select[Vanhamenu] == 0)
                        if (Md->Pl[i].Canbuy) Md->Pl[i].Menu = MENU_BUYPROJECTW;
                if (Md->Pl[i].Menu == MENU_BUYWEAPONS) if (Md->Pl[i].Select[Vanhamenu] == 1)
                        if (Md->Pl[i].Canbuy) Md->Pl[i].Menu = MENU_BUYENERGYW;
                if (Md->Pl[i].Menu == MENU_BUYWEAPONS) if (Md->Pl[i].Select[Vanhamenu] == 2)
                        if (Md->Pl[i].Canbuy) Md->Pl[i].Menu = MENU_BUYBOMBS;
                if (Md->Pl[i].Menu == MENU_BUY) if (Md->Pl[i].Select[Vanhamenu] == 2)
                        Md->Pl[i].Menu = MENU_BUYTOOLS;
                if (Md->Pl[i].Menu == MENU_BUY) if (Md->Pl[i].Select[Vanhamenu] == 1)
                        Md->Pl[i].Menu = MENU_BUYAMMO;
                if (Md->Pl[i].Menu == MENU_BUY) if (Md->Pl[i].Select[Vanhamenu] == 0)
                        Md->Pl[i].Menu = MENU_BUYWEAPONS;
                if (Md->Pl[i].Menu == MENU_MAIN) if (Md->Pl[i].Select[Vanhamenu] == 1)
                        Md->Pl[i].Menu = MENU_INVENTORY;
                if (Md->Pl[i].Menu == MENU_MAIN) if (Md->Pl[i].Select[Vanhamenu] == 0)
                        if (Md->Pl[i].Canbuy) Md->Pl[i].Menu = MENU_BUY;

            } // if (Md->Pl[i].Menu != -1)
        } // Action == 0
} // PlayerUse(int i)
void PlayerChange(int i)
{
    if (Md->Pl[i].Action)
    {
        Md->Pl[i].Action = 0;
        key[Opt->Nap[i].Change] = 0;
        return;
    } // if (Md->Pl[i].Action == ACTION_SNIPER)
// poistumisnappi... poistuu erilaisista menuista
    if (Md->Pl[i].Menu == -1) Md->Pl[i].Menu = MENU_MAIN;
    else
    {
        if (Md->Pl[i].Menu == MENU_MAIN) Md->Pl[i].Menu = -1;
        if (Md->Pl[i].Menu == MENU_BUY)  Md->Pl[i].Menu = MENU_MAIN;
        if (Md->Pl[i].Menu == MENU_INVENTORY)  Md->Pl[i].Menu = MENU_MAIN;
        if (Md->Pl[i].Menu == MENU_BUYTOOLS)  Md->Pl[i].Menu = MENU_BUY;
        if (Md->Pl[i].Menu == MENU_BUYBUILD)  Md->Pl[i].Menu = MENU_BUYTOOLS;
        if (Md->Pl[i].Menu == MENU_BUYWEAPONS)  Md->Pl[i].Menu = MENU_BUY;
        if (Md->Pl[i].Menu == MENU_BUYPROJECTW)  Md->Pl[i].Menu = MENU_BUYWEAPONS;
        if (Md->Pl[i].Menu == MENU_BUYENERGYW)  Md->Pl[i].Menu = MENU_BUYWEAPONS;
        if (Md->Pl[i].Menu == MENU_BUYBOMBS)  Md->Pl[i].Menu = MENU_BUYWEAPONS;
        if (Md->Pl[i].Menu == MENU_BUYARMOR)  Md->Pl[i].Menu = MENU_BUYTOOLS;
        if (Md->Pl[i].Menu == MENU_BUYAMMO)      Md->Pl[i].Menu = MENU_BUY;
        if (Md->Pl[i].Menu == MENU_BUYTOOLS2)      Md->Pl[i].Menu = MENU_BUYTOOLS;
        if (Md->Pl[i].Menu == MENU_BUYVEHICLES)      Md->Pl[i].Menu = MENU_BUYTOOLS;
    } // if (Md->Pl[i].Menu == -1) ; else
    key[Opt->Nap[i].Change] = 0;
} // PlayerChange(int i)
void Formatplayer(int i)
{

    for (int i2 = 0; i2 < 3; i2++) // Ei damagea
        Md->Pl[i].Damage[i2] = 0;
    Md->Pl[i].Lives = Opt->Lives; // elämiä
    Md->Pl[i].Live = true; // ELOSSA?
    Md->Pl[i].Mx = 0;
    Md->Pl[i].My = 0;

    Md->Pl[i].X  = Lev->Startpoint[i][0] BitL; // Alotuspaikka
    Md->Pl[i].Y  = Lev->Startpoint[i][1] BitL;
    Md->Pl[i].Sx = Lev->Startpoint[i][0] - (Clipx>>1); // Ruudun paikka
    Md->Pl[i].Sy = Lev->Startpoint[i][1] - (Clipy>>1);

    Md->Pl[i].Menu = -1; // Ei menuja päälle


}
void Checkkeys()
{
    // escillä pois
    if (key[KEY_ESC]) Done = true;

    for (int i = 0; i < Opt->Players; i++)
    {
        Md->Pl[i].Jump = false;
        Md->Pl[i].Walking = false;
        // tavaroiden käyttö
        if (Md->Pl[i].Reload) Md->Pl[i].Reload--;
        if (Md->Pl[i].Reload<=0) Md->Pl[i].Reloading = false;
        if ((key[Opt->Nap[i].Use]) || (Md->Pl[i].Firegun))    PlayerUse(i);
        if (Md->Pl[i].Reload) Md->Pl[i].Reload--;
        if (Md->Pl[i].Reload<=0) Md->Pl[i].Reloading = false;
        if ((key[Opt->Nap[i].Use]) || (Md->Pl[i].Firegun))    PlayerUse(i);
        // liikkumiset
        if (key[Opt->Nap[i].Left])  PlayerLeft(i);
        if (key[Opt->Nap[i].Right]) PlayerRight(i);
        /*     if (key[Opt->Nap[i].Ninjarope])
             if (key[Opt->Nap[i].Left])
              if (key[Opt->Nap[i].Right]) Formatplayer(i);
        */
        if (key[Opt->Nap[i].Up])    PlayerUp(i);
        if (key[Opt->Nap[i].Down])   PlayerDown(i);
        if (key[Opt->Nap[i].Change])  PlayerChange(i);
        if (key[Opt->Nap[i].Ninjarope])  PlayerNinjarope(i);
        if (key[Opt->Nap[i].Jump])   PlayerJump(i);

        if (key[KEY_F8]) {
            Takescrshot(*(PALETTE*) Dat[DATPALETTE].dat);
            key[KEY_F8] = 0;
        }
    } // for (int i = 0; i < Opt->Players; i++)
} // Checkkeys

#endif
