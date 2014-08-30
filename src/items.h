#ifndef __items_h
#define __items_h
void Change_clip(int i)
{
    if (Reloadsample[Md->Pl[i].Item] > -1) // jos lataamisesta kuuluu ääni
    {
        // niin soitetaan ääni
        Playsample(Reloadsample[Md->Pl[i].Item], Opt->Soundvolume, 128, 0);
    } // if (Reloadsample[Md->Pl[i].Item] > -1)
    // vähennetään panoksia
    Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]--;
    // latausaikaa
    Md->Pl[i].Reload = Reloadtime[Md->Pl[i].Item];
    Md->Pl[i].Firegun = false;
    Md->Pl[i].Reloading = true;
} // Change_clip
void Use_pistol(int i)
{
    // jos latausaikaa ei ole ja panoksia on
    if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            // jos lipas on lopussa niin lataa
            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i);
            else
            {
                // muuten ammu

                // suuliekki
                Md->Pl[i].Gunfire = 5;
                // panoksia pois
                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] -- ;
                // hylsy
                Shoot(BUL_BULLETSHELL, Md->Pl[i].X, Md->Pl[i].Y, -3000+rand()%6000, -8000+rand()%1000);
                // panos
                Shoot(BUL_PISTOL, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-10000+rand()%20000, fsin(Md->Pl[i].Dir)*6-10000+rand()%20000,0,i,0);
                // pistoolin ääni
                Playsample(SAMP_PISTOL, Opt->Soundvolume, 128, 0);
                // latausaika
                Md->Pl[i].Reload = 80;
                // ja tärinä
                Md->Pl[i].Shake = 10;
            } //  if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // (Md->Pl[i].Reload == 0)
} // Use_pistol(int i)
void Use_bigmachinegun(int i)
{
    // jos latausaikaa ei ole ja panoksia on
    if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            // jos lipas on lopussa niin lataa
            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i);
            else
            {
                Md->Pl[i].Mx += fcos(Suunta(Md->Pl[i].Dir-itofix(128)))>>4;
                Md->Pl[i].My += fsin(Suunta(Md->Pl[i].Dir-itofix(128)))>>4;
                // muuten ammu

                // suuliekki
                Md->Pl[i].Gunfire = 5;
                // panoksia pois
                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] -- ;
                // hylsy
                Shoot(BUL_BULLETSHELL, Md->Pl[i].X, Md->Pl[i].Y, -3000+rand()%6000, -8000+rand()%1000);
                // panos
                Shoot(BUL_PISTOL, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-20000+rand()%40000, fsin(Md->Pl[i].Dir)*6-20000+rand()%40000,ITEM_BIGMACHINEGUN,i,0);
                // pistoolin ääni
                Playsample(SAMP_BIGMACHINEGUN, Opt->Soundvolume, 128, 0);
                // latausaika
                Md->Pl[i].Reload = 30;
                // ja tärinä
                Md->Pl[i].Shake = 10;
            } //  if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // (Md->Pl[i].Reload == 0)
} // Use_bigmachinegun(int i)
void Use_machinegun(int i)
{
    // jos latausaikaa ei ole ja panoksia on
    if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            // jos lipas on lopussa niin lataa
            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i);
            else
            {
                // muuten ammu

                // panoksia pois
                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] -- ;
                // pistoolinpanos
                Shoot(BUL_PISTOL, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-10000+rand()%20000, fsin(Md->Pl[i].Dir)*6-10000+rand()%20000,0,i,0);
                // hylsy
                Shoot(BUL_BULLETSHELL, Md->Pl[i].X, Md->Pl[i].Y, -3000+rand()%6000, -8000+rand()%1000);
                // takataka-ääni
                Playsample(SAMP_MACHINEGUN, (Opt->Soundvolume>>1), 128, 0);
                // latausaika
                Md->Pl[i].Reload = 130;
                // tärinä
                Md->Pl[i].Shake = 30;
                // suuliekki
                Md->Pl[i].Gunfire = 5;
                Md->Pl[i].Firegun = true;

            } // if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // (Md->Pl[i].Reload == 0)
    // neljä panosta sama homma

    if (Md->Pl[i].Reload == 115) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i);
            else
            {
                Md->Pl[i].Gunfire = 5;
                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] -- ;
                Shoot(BUL_PISTOL, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-10000+rand()%20000, fsin(Md->Pl[i].Dir)*6-10000+rand()%20000,0,i,0);
                Shoot(BUL_BULLETSHELL, Md->Pl[i].X, Md->Pl[i].Y, -3000+rand()%2000, -8000+rand()%1000);

            } // if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // if (Md->Pl[i].Reload == 115)
    if (Md->Pl[i].Reload == 100) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i);
            else
            {
                Md->Pl[i].Gunfire = 5;
                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] -- ;
                Shoot(BUL_PISTOL, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-10000+rand()%20000, fsin(Md->Pl[i].Dir)*6-10000+rand()%20000,0,i,0);
                Shoot(BUL_BULLETSHELL, Md->Pl[i].X, Md->Pl[i].Y, -3000+rand()%6000, -8000+rand()%1000,0);
            } // if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // if (Md->Pl[i].Reload == 100)
    if (Md->Pl[i].Reload == 85) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i);
            else
            {
                Md->Pl[i].Gunfire = 5;
                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] -- ;
                Shoot(BUL_PISTOL, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-10000+rand()%20000, fsin(Md->Pl[i].Dir)*6-10000+rand()%20000,0,i,0);
                Shoot(BUL_BULLETSHELL, Md->Pl[i].X, Md->Pl[i].Y, -3000+rand()%6000, -8000+rand()%1000,0);
            } // if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // if (Md->Pl[i].Reload == 85)
    //***********************************
    if (Md->Pl[i].Reload == 10)
        Md->Pl[i].Firegun = false;
} // Use_machinegun(int i)
void Use_lavatrap(int i)
{
    // jos latausaikaa ei ole ja laavatrappeja on
    if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Stuff[Md->Pl[i].Item]>0)
        {
            Md->Pl[i].Stuff[Md->Pl[i].Item]--;
            Md->Pl[i].Reload = 150;
            Create_building(BLD_LAVATRAP, Md->Pl[i].X, Md->Pl[i].Y, (fcos(Md->Pl[i].Dir))-5000+rand()%10000, (fsin(Md->Pl[i].Dir))-5000+rand()%10000,i);
            // SAMPLE REQUEST
        } // if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
} // void Use_lavatrap(int i)
void Use_superlavatrap(int i)
{
    // jos latausaikaa ei ole ja laavatrappeja on
    if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Stuff[Md->Pl[i].Item]>0)
        {
            Md->Pl[i].Stuff[Md->Pl[i].Item]--;
            Md->Pl[i].Reload = 200;
            Create_building(BLD_SUPERLAVATRAP, Md->Pl[i].X, Md->Pl[i].Y, (fcos(Md->Pl[i].Dir))-5000+rand()%10000, (fsin(Md->Pl[i].Dir))-5000+rand()%10000,i);
            // SAMPLE REQUEST
        } // if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
} // void Use_superlavatrap(int i)
void Use_shotgun(int i)
{
    // jos latausaikaa ei ole ja panoksia on
    if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            // jos lipas on lopussa niin lataa
            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]])
            {
                // muuten ammu

                // suuliekki
                Md->Pl[i].Gunfire = 5;
                // panoksia pois
                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] -- ;
                Playsample(SAMP_SHOTGUN, Opt->Soundvolume, 128, 0);
                // hylsy
                Shoot(BUL_SHOTGUNSHELL, Md->Pl[i].X, Md->Pl[i].Y, -3000+rand()%6000, -8000+rand()%1000);
                // panos
                Md->Pl[i].Mx += fcos(Suunta(Md->Pl[i].Dir-itofix(128)))>>1;
                Md->Pl[i].My += fsin(Suunta(Md->Pl[i].Dir-itofix(128)))>>1;

                Shoot(BUL_PISTOL, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-40000+rand()%80000, fsin(Md->Pl[i].Dir)*6-40000+rand()%80000,ITEM_SHOTGUN,i,0);
                Shoot(BUL_PISTOL, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-40000+rand()%80000, fsin(Md->Pl[i].Dir)*6-40000+rand()%80000,ITEM_SHOTGUN,i,0);
                Shoot(BUL_PISTOL, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-40000+rand()%80000, fsin(Md->Pl[i].Dir)*6-40000+rand()%80000,ITEM_SHOTGUN,i,0);
                Shoot(BUL_PISTOL, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-40000+rand()%80000, fsin(Md->Pl[i].Dir)*6-40000+rand()%80000,ITEM_SHOTGUN,i,0);
                Shoot(BUL_PISTOL, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-40000+rand()%80000, fsin(Md->Pl[i].Dir)*6-40000+rand()%80000,ITEM_SHOTGUN,i,0);
                Shoot(BUL_PISTOL, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-40000+rand()%80000, fsin(Md->Pl[i].Dir)*6-40000+rand()%80000,ITEM_SHOTGUN,i,0);
                // pistoolin ääni

                // latausaika
                Md->Pl[i].Reload = 400;
                // ja tärinä
                Md->Pl[i].Shake = 10;
            } //  if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // (Md->Pl[i].Reload == 0)
} // Use_shotgun(int i)

void Use_magnum(int i)
{
    // jos latausaikaa ei ole ja panoksia on
    if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            // jos lipas on lopussa niin lataa
            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i);
            else
            {
                // muuten ammu
                Md->Pl[i].Mx += fcos(Suunta(Md->Pl[i].Dir-itofix(128)))>>2;
                Md->Pl[i].My += fsin(Suunta(Md->Pl[i].Dir-itofix(128)))>>2;

                // suuliekki
                Md->Pl[i].Gunfire = 5;
                // panoksia pois
                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] -- ;
                Playsample(SAMP_MAGNUM, Opt->Soundvolume, 128, 0);

                // hylsy
                Shoot(BUL_BULLETSHELL, Md->Pl[i].X, Md->Pl[i].Y, -3000+rand()%6000, -8000+rand()%1000);
                // panos
                Shoot(BUL_PISTOL, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-10000+rand()%20000, fsin(Md->Pl[i].Dir)*6-10000+rand()%20000,ITEM_MAGNUM,i,0);
                // pistoolin ääni
                // latausaika
                Md->Pl[i].Reload = 110;
                // ja tärinä
                Md->Pl[i].Shake = 10;
            } //  if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // (Md->Pl[i].Reload == 0)
} // Use_magnum(int i)
void Use_grenade(int i)
{
    // jos latausaikaa ei ole ja laavatrappeja on
    if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Stuff[Md->Pl[i].Item]>0)
        {
            Md->Pl[i].Stuff[Md->Pl[i].Item]--;
            Md->Pl[i].Reload = 150;
            Shoot(BUL_GRENADE, Md->Pl[i].X, Md->Pl[i].Y, int((fcos(Md->Pl[i].Dir)>>1)*4.5-10000+rand()%20000), int((fsin(Md->Pl[i].Dir)>>1)*4.5-10000+rand()%20000),ITEM_GRENADE,i,0);
            // SAMPLE REQUEST
        } // if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
} // void Use_superlavatrap(int i)
void Use_bazooka(int i)
{
    // jos latausaikaa ei ole ja panoksia on
    if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            // jos lipas on lopussa niin lataa
            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] )
            {
                // muuten ammu
                // panoksia pois
                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]--;
                // panos
                Md->Pl[i].Gunfire = 30;
                Playsample(SAMP_ROCKET, Opt->Soundvolume, 128, 0);

                Md->Pl[i].Mx += fcos(Suunta(Md->Pl[i].Dir-itofix(128)));
                Md->Pl[i].My += fsin(Suunta(Md->Pl[i].Dir-itofix(128)));

                Shoot(BUL_ROCKET, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-5000+rand()%10000, fsin(Md->Pl[i].Dir)*6-5000+rand()%10000,ITEM_BAZOOKA,i,0, Md->Pl[i].Dir);
                // latausaika
                Md->Pl[i].Reload = 400;
                // ja tärinä
                Md->Pl[i].Shake = 10;
            } //  if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // (Md->Pl[i].Reload == 0)
} // Use_bazooka(int i)
void Use_homingmissilelauncher(int i)
{
    // jos latausaikaa ei ole ja panoksia on
    if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            // jos lipas on lopussa niin lataa
            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] )
            {
                // muuten ammu
                // panoksia pois
                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]--;
                // panos
                Md->Pl[i].Gunfire = 30;
                Playsample(SAMP_ROCKET, Opt->Soundvolume, 128, 0);
                Md->Pl[i].Mx += fcos(Suunta(Md->Pl[i].Dir-itofix(128)))>>1;
                Md->Pl[i].My += fsin(Suunta(Md->Pl[i].Dir-itofix(128)))>>1;

                Shoot(BUL_ROCKET, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*2-5000+rand()%10000, fsin(Md->Pl[i].Dir)*2-5000+rand()%10000,ITEM_HMISLAUNCHER,i,0, Md->Pl[i].Dir);
                // latausaika
                Md->Pl[i].Reload = 400;
                // ja tärinä
                Md->Pl[i].Shake = 10;
            } //  if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // (Md->Pl[i].Reload == 0)
} // Use_homing(int i)
void Use_laserrifle(int i)
{
    // jos latausaikaa ei ole ja panoksia on
    if (Md->Pl[i].Reload == 0)
        if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            // jos lipas on lopussa niin lataa
            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i);
            else
            {
                // muuten ammu
                // panoksia pois
                Playsample(SAMP_LASER, Opt->Soundvolume, 128, 0);

                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]--;
                Md->Pl[i].Gunfire = 30;
                Md->Pl[i].Reload = 30;
                // ja tärinä
                Md->Pl[i].Shake = 0;
            } //  if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // (Md->Pl[i].Reload == 0)
} // Use_laserrifle(int i)
void Hit(int X, int Y, int killer, int killertype)
{

    int Hit = 0; // mihin osutaa
    for (int i2 = 0; i2 < Opt->Players; i2++) if (Md->Pl[i2].Live) if (((killertype==0) && (killer != i2)) || (killertype == 1))
            {
                Hit = 0;
                if (X >= (Md->Pl[i2].X BitR) - 2)
                    if (X <= (Md->Pl[i2].X BitR) + 2)
                        if (Y >= (Md->Pl[i2].Y BitR) - 5)
                            if (Y <= (Md->Pl[i2].Y BitR) - 2)
                                Hit = 1; // Head;
                if (X >= (Md->Pl[i2].X BitR) - 2)
                    if (X <= (Md->Pl[i2].X BitR) + 2)
                        if (Y >= (Md->Pl[i2].Y BitR) - 1)
                            if (Y <= (Md->Pl[i2].Y BitR) + 1)
                                Hit = 2; // Torso
                if (X >= (Md->Pl[i2].X BitR) - 2)
                    if (X <= (Md->Pl[i2].X BitR) + 2)
                        if (Y >= (Md->Pl[i2].Y BitR) + 1)
                            if (Y <= (Md->Pl[i2].Y BitR) + 4)
                                Hit = 3; // Legs
                int r; // apumuuttuja suunnan määrittelylle
                if (Hit > 0)
                    for (int Count = 0; Count < 12; Count++) // verta
                    {
                        r = Rand()%255;
                        Shoot(BUL_BLOOD, Md->Pl[i2].X, Md->Pl[i2].Y - (3 BitL), (fcos(r BitL)>>4)-5000+Rand()%10000, (fsin(r BitL)>>4)-5000+Rand()%10000);
                    } // for (int Count = 0; Count < 12; Count++)

                if (Hit > 0)
                {
                    // Damagea
                    int Damage = 1;
                    if (Md->Pl[i2].Damage[Hit-1] < Md->Pl[i2].Killdamage[Hit-1])
                        Md->Pl[i2].Damage[Hit-1]+=Damage;
                    // jos tulee kuolo.. (Damaget suurempia kuin totaldamage)
                    if ((Md->Pl[i2].Damage[0]) + (Md->Pl[i2].Damage[1]) + (Md->Pl[i2].Damage[2]) >= Md->Pl[i2].Totaldamage)
                    {
                        Kill_player(i2, ITEM_PICKAXE, killer, killertype);
                        if (Md->Pl[i2].Damage[Hit-1] >= Md->Pl[i2].Killdamage[Hit-1])
                            Md->Pl[i2].Damage[Hit-1] = Md->Pl[i2].Killdamage[Hit-1];
                    } //                 if (Md->Pl[i2].Damage[0] + Md->Pl[i2].Damage[1] + Md->Pl[i2].Damage[2] >= Md->Pl[i2].Totaldamage)
                    // joku ruumiinosa pettää
                    if (Md->Pl[i2].Damage[Hit-1] >= Md->Pl[i2].Killdamage[Hit-1]) if (Md->Pl[i2].Live)
                        {
                            Kill_player(i2, ITEM_PICKAXE, killer, killertype);
                            Md->Pl[i2].Damage[Hit-1] = Md->Pl[i2].Killdamage[Hit-1];
                        } // if (Md->Pl[i2].Damage[Hit-1]>2)
                } // if (Hit > 0)

                if (Md->Pl[i2].Live) // Elossa vielä?? Mitä?
                    switch(Hit)
                    {   // Lits
                    case 1:
                        Playsample(SAMP_FLESH1, Opt->Soundvolume*2, 128);
                        break; // Läts
                    case 2:
                        Playsample(SAMP_FLESH2, Opt->Soundvolume*2, 128);
                        break; // Löts
                    case 3:
                        Playsample(SAMP_FLESH3, Opt->Soundvolume*2, 128);
                        break;
                    };

            } //      for (int i2 = 0; i2 < Opt->Players; i2++)
    for (int i2 = 0; i2 < Opt->Bots; i2++) if (Md->Bot[i2].Live)
        {
            Hit = 0;
            if (X >= (Md->Bot[i2].X BitR) - 2)
                if (X <= (Md->Bot[i2].X BitR) + 2)
                    if (Y >= (Md->Bot[i2].Y BitR) - 5)
                        if (Y <= (Md->Bot[i2].Y BitR) - 2)
                            Hit = 1; // Head;
            if (X >= (Md->Bot[i2].X BitR) - 2)
                if (X <= (Md->Bot[i2].X BitR) + 2)
                    if (Y >= (Md->Bot[i2].Y BitR) - 1)
                        if (Y <= (Md->Bot[i2].Y BitR) + 1)
                            Hit = 2; // Torso
            if (X >= (Md->Bot[i2].X BitR) - 2)
                if (X <= (Md->Bot[i2].X BitR) + 2)
                    if (Y >= (Md->Bot[i2].Y BitR) + 1)
                        if (Y <= (Md->Bot[i2].Y BitR) + 4)
                            Hit = 3; // Legs
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
                int Damage = 1;
                if (Md->Bot[i2].Damage[Hit-1] < Md->Bot[i2].Killdamage[Hit-1])
                    Md->Bot[i2].Damage[Hit-1]+=Damage;
                // jos tulee kuolo.. (Damaget suurempia kuin totaldamage)
                if ((Md->Bot[i2].Damage[0]) + (Md->Bot[i2].Damage[1]) + (Md->Bot[i2].Damage[2]) >= Md->Bot[i2].Totaldamage)
                {
                    Kill_bot(i2, ITEM_PICKAXE, killer, killertype);
                    if (Md->Bot[i2].Damage[Hit-1] >= Md->Bot[i2].Killdamage[Hit-1])
                        Md->Bot[i2].Damage[Hit-1] = Md->Bot[i2].Killdamage[Hit-1];
                } //                 if (Md->Bot[i2].Damage[0] + Md->Bot[i2].Damage[1] + Md->Bot[i2].Damage[2] >= Md->Bot[i2].Totaldamage)
                // joku ruumiinosa pettää
                if (Md->Bot[i2].Damage[Hit-1] >= Md->Bot[i2].Killdamage[Hit-1]) if (Md->Bot[i2].Live)
                    {
                        Kill_bot(i2, ITEM_PICKAXE, killer, killertype);
                        Md->Bot[i2].Damage[Hit-1] = Md->Bot[i2].Killdamage[Hit-1];
                    } // if (Md->Bot[i2].Damage[Hit-1]>2)
            } // if (Hit > 0)

            if (Md->Bot[i2].Live) // Elossa vielä?? Mitä?
                switch(Hit)
                {   // Lits
                case 1:
                    Playsample(SAMP_FLESH1, Opt->Soundvolume*2, 128);
                    break; // Läts
                case 2:
                    Playsample(SAMP_FLESH2, Opt->Soundvolume*2, 128);
                    break; // Löts
                case 3:
                    Playsample(SAMP_FLESH3, Opt->Soundvolume*2, 128);
                    break;
                };
        } //      for (int i2 = 0; i2 < Opt->Players; i2++)

}
void Use_pickaxe(int i)
{
    // jos latausaikaa ei ole
    if (Md->Pl[i].Reload == 0)
    {
        int X = (Md->Pl[i].X+(fcos(Md->Pl[i].Dir)<<3))>>16;
        int Y = (Md->Pl[i].Y+(fsin(Md->Pl[i].Dir)<<3))>>16;
        BITMAP * bmp = (BITMAP*) Dat[DATLASER04].dat;
        Emptypic(bmp, X-(bmp->w>>1), Y-(bmp->h>>1), 0, 0);
        Playsample(SAMP_DIRT1, Opt->Soundvolume>>1, 128);
        Shoot(BUL_DIRT, (X<<16)+(itofix(-1+Rand()%3)), (Y<<16)+(itofix(-1+Rand()%3)), fcos(itofix(Suunta(160+Rand()%65)))>>2, fsin(itofix(Suunta(160+Rand()%65)))>>2);
        Hit(X, Y, i, 0);

        Md->Pl[i].Reload = 60;
        // ja tärinä
        Md->Pl[i].Shake = 15;
    } // (Md->Pl[i].Reload == 0)
} // Use_pickaxe(int i)

void Use_drill(int i)
{
    // jos latausaikaa ei ole
    if (Md->Pl[i].Reload == 0)
    {
        int X = (Md->Pl[i].X+(fcos(Md->Pl[i].Dir)<<3))>>16;
        int Y = (Md->Pl[i].Y+(fsin(Md->Pl[i].Dir)<<3))>>16;
        BITMAP * bmp = (BITMAP*) Dat[DATLASER04].dat;
        Emptypic(bmp, X-(bmp->w>>1), Y-(bmp->h>>1), 1, 0);
        Md->Pl[i].Playsamplecounter++;
        if (Md->Pl[i].Playsamplecounter%3==0)
        {
            Playsample(SAMP_DIRT1, Opt->Soundvolume>>1, 128);
            if (Distance_from_surface(i) < 10)
            {
                Md->Pl[i].Mx = Md->Pl[i].Mx >> 1;
                Md->Pl[i].My = Md->Pl[i].My >> 1;
            } // if (Md->Pl[i].FeetOnGround)
        } // if (Playsamplecounter%3==0)
        Shoot(BUL_DIRT, (X<<16)+(itofix(-1+Rand()%3)), (Y<<16)+(itofix(-1+Rand()%3)), fcos(itofix(Suunta(160+Rand()%65)))>>2, fsin(itofix(Suunta(160+Rand()%65)))>>2);

        Hit(X, Y, i, 0);
        Md->Pl[i].Reload = 10;
        // ja tärinä
        Md->Pl[i].Shake = 30;
    } // (Md->Pl[i].Reload == 0)
} // Use_drill(int i)
void Use_lavabomb(int i)
{
    // jos latausaikaa ei ole ja laavatrappeja on
    if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Stuff[Md->Pl[i].Item]>0)
        {
            Md->Pl[i].Stuff[Md->Pl[i].Item]--;
            Md->Pl[i].Reload = 300;
            Shoot(BUL_LAVABOMB, Md->Pl[i].X, Md->Pl[i].Y, int((fcos(Md->Pl[i].Dir)>>1)*2.5-5000+rand()%10000), int((fsin(Md->Pl[i].Dir)>>1)*2.5-5000+rand()%10000),ITEM_LAVABOMB,i,0);
        } // if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
} // void Use_superlavatrap(int i)
void Use_plasmapistol(int i)
{
    if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            // jos lipas on lopussa niin lataa
            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i);
            else
            {
                // muuten ammu
                // suuliekki
                Md->Pl[i].Gunfire = 5;
                // panoksia pois
                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] -- ;
                // panos
                Shoot(BUL_PLASMA, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-20000+rand()%40000, fsin(Md->Pl[i].Dir)*6-20000+rand()%40000,ITEM_PLASMAPISTOL,i,0);
                // pistoolin ääni
                Playsample(SAMP_PLASMA, Opt->Soundvolume, 128, 0);
                // latausaika
                Md->Pl[i].Reload = 200;
                // ja tärinä
                Md->Pl[i].Shake = 10;
            } //  if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // (Md->Pl[i].Reload == 0)
} // void Use_superlavatrap(int i)
void Use_heavyplasma(int i)
{
    if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            // jos lipas on lopussa niin lataa
            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i);
            else
            {
                // muuten ammu
                // suuliekki
                Md->Pl[i].Gunfire = 5;
                // panoksia pois
                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] -- ;
                // panos
                Shoot(BUL_PLASMA, Md->Pl[i].X, Md->Pl[i].Y, fcos(Md->Pl[i].Dir)*6-40000+rand()%80000, fsin(Md->Pl[i].Dir)*6-40000+rand()%80000,ITEM_HEAVYPLASMA,i,0);
                // pistoolin ääni
                Playsample(SAMP_PLASMA, Opt->Soundvolume, 96, 0);
                // latausaika
                Md->Pl[i].Reload = 80;
                // ja tärinä
                Md->Pl[i].Shake = 20;
            } //  if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // (Md->Pl[i].Reload == 0)
} // void Use_superlavatrap(int i)
void Use_sniper(int i)
{
    if (Md->Pl[i].Reload == 0) if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            // jos lipas on lopussa niin lataa

            {
                // muuten ammu
                // suuliekki
                Md->Pl[i].Gunfire = 5;
                // panoksia pois
                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] -- ;
                // panos
                int Mx, My;
                Getmoments(Md->Pl[i].X BitR, Md->Pl[i].Y BitR, Md->Pl[i].Actionx, Md->Pl[i].Actiony, &Mx, &My);
                Shoot(BUL_PISTOL, Md->Pl[i].X, Md->Pl[i].Y, Mx*3, My*3, ITEM_SNIPERRIFLE,i,0);
                // pistoolin ääni
                Playsample(SAMP_SNIPER, Opt->Soundvolume, 128, 0);
                // latausaika
                Md->Pl[i].Reload = 150;
                // ja tärinä
                Md->Pl[i].Shake = 5;
            } //  if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // (Md->Pl[i].Reload == 0)
} // void Use_sniper(int i)
void Use_lasersabre(int i)
{
    // ääni
    Playsample(SAMP_PLASMA, Opt->Soundvolume>>1, 128, 0);
    // latausaika
    Md->Pl[i].Reload = 150;
    // ja tärinä
    Md->Pl[i].Shake = 5;
    Md->Pl[i].Action = ACTION_SABRE;
    Md->Pl[i].Actionvar[0] = 0;
} // void Use_lasersabre(int i)
void Use_selfdestructor_remote(int i)
{
    Kill_player(i, ITEM_SELFDESTRUCTOR, -1, -1);
} // void Use_selfdestructor_remote(int i)

void Use_selfdestructor(int i)
{
    for (int b = 0; b < 20; b++)
    {
        int D = (rand()%255)<<16;
        int Power = rand()%10000;
        Addexp(1, (Md->Pl[i].X  +fcos(D)*Power/100) BitR, (Md->Pl[i].Y+ fsin(D)*Power/100) BitR, 2, 0, 5);
    } // for (int b = 0; b < 10; b++)
    Md->Pl[i].Stuff[ITEM_SELFDESTRUCTOR] = 0;
} // void Use_selfdestructor(int i)
void Use_lasercannon(int i)
{
    if (Md->Pl[i].Reload == 0)
        if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]>0)
        {
            // jos lipas on lopussa niin lataa
            if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i);
            else
            {
                // muuten ammu
                // panoksia pois

                Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]]--;
                Md->Pl[i].Action = ACTION_LASERCANNON;
                Md->Pl[i].Actionvar[0] = 0;
                Md->Pl[i].Actionvar[1] = 64;
            } //  if (Md->Pl[i].Ammo[Weaponclip[Md->Pl[i].Item]] % Clipsize[Md->Pl[i].Item] == 0) Change_clip(i); else
        } // (Md->Pl[i].Reload == 0)
} // void Use_lasercannon(int i)
#endif
