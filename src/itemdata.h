#ifndef __itemdata_h
#define __itemdata_h
#define BULLET_9MM              0
#define BULLET_ROCKET           1                // definet bulletteja
#define BULLET_SHELLS           2                // varten
#define BULLET_45               3
#define BULLET_GRENADE          4
#define BULLET_HMISSILE         5
#define BULLET_ENERGYCELL       6
#define BULLET_PLASMAPOD        7
#define BULLET_762              8

#define CLASS_PROJECTILEPISTOLS 0
#define CLASS_PROJECTILERIFLES  1
#define CLASS_ENERGYPISTOLS     2
#define CLASS_ENERGYRIFLES      3
#define CLASS_MELEEWEAPONS      4
#define CLASS_HEAVYWEAPONS      5
#define CLASS_BOMBS             6
#define CLASS_TOOLS             7
#define CLASS_BUILDINGS         8
#define CLASS_ACCESSORY         9
#define CLASS_MAX              10
char * Stuffname[] =    // tavaroiden nimet
{
    "Pistol",
    "Submachinegun",
    "Bazooka",
    "Lavatrap",
    "Super lavatrap",
    "Shotgun",
    "Magnum",
    "Grenade",
    "Homing missile launcher",
    "Laser rifle",
    "Laser pistol",
    "Plate",
    "Reinforced plate",
    "Pick-axe",
    "Drill",
    "Lavabomb",
    "Plasma pistol",
    "Targeting system",
    "Medikit",
    "Heavy plasma",
    "Sniper rifle",
    "Camouflage",
    "Machinegun",
    "Parachute",
    "Laser sabre",
    "Selfdestructor",
    "Laser cannon",
};
int Clipsize[] =        // lippaan koko
{
    13, // Pistol
    21, // SubMachinegun
    1, // Bazooka
    -1, // Lavatrap
    -1, // S. lavatrap
    1, // Shotgun
    9, // Magnum
    1, // grenade
    1, // Homing missile launcher
    26, // Laser rifle
    26, // Laser pistol
    -1, // Plate
    -1, // rplate
    -1, // Pick-axe
    -1, // Drill
    1, // Lavabomb
    7, // Plasma pistol
    -1, // Targeting
    0, // Medikit
    16, // Heavy plasma
    6, // Sniper rifle
    0, // Camouflage
    31, // Machinegun
    -1, // Parachute
    -1, // Laser sabre
    -1, // Selfdestructor
    26, // Laser cannon
};
int Itemclass[] =        // lippaan koko
{
    CLASS_PROJECTILEPISTOLS, // Pistol
    CLASS_PROJECTILERIFLES, // Machinegun
    CLASS_HEAVYWEAPONS, // Bazooka
    CLASS_BUILDINGS, // Lavatrap
    CLASS_BUILDINGS, // S. lavatrap
    CLASS_PROJECTILERIFLES, // Shotgun
    CLASS_PROJECTILEPISTOLS, // Magnum
    CLASS_BOMBS, // grenade
    CLASS_HEAVYWEAPONS, // Homing missile launcher
    CLASS_ENERGYRIFLES, // Laser rifle
    CLASS_ENERGYPISTOLS, // Laser pistol
    CLASS_BUILDINGS, // Plate
    CLASS_BUILDINGS, // rplate
    CLASS_TOOLS, // Pick-axe
    CLASS_TOOLS, // Drills
    CLASS_BOMBS, // lavabomb
    CLASS_ENERGYPISTOLS, // plasma pistol
    CLASS_ACCESSORY, // Targeting system
    CLASS_ACCESSORY, // Medikit
    CLASS_ENERGYRIFLES, // Heavy plasma
    CLASS_PROJECTILERIFLES, // Sniper rifle
    CLASS_TOOLS, // Camouflage
    CLASS_PROJECTILERIFLES, // Machinegun2
    CLASS_ACCESSORY, // Parachute
    CLASS_MELEEWEAPONS, // Laser sabre
    CLASS_BOMBS, // Selfdestructor
    CLASS_ENERGYRIFLES, // Laser cannon
};
int Buldamage[] = // kuinka paljon panokset tekevät vahinkoa rakennuksiin
{
    8,    // BUL_PISTOL
    0,    // BUL_BLOOD
    0,    // BUL_GORE
    0,    // BUL_BULLETSHELL
    0,    // BUL_SMOKE
    0,
}; // Buldamage
int Mindamage[] =
{
    1, // Pistol
    1, // Machinegun
    1, // Bazooka
    0, // Lavatrap
    0, // S. lavatrap
    1, // Shotgun
    2, // Magnum
    1, // Grenade
    1, // Hmissile
    1, // Laser rifle
    1, // laser pistol
    0, // Plate
    0, // Rplate
    0, // Pick-axe
    0, // Drill
    0, // Lavabomb
    3, // Plasma pistol
    0, // Targeting system
    0, // Medikit
    3, // Heavy plasma
    4, // Sniper rifle
    0, // Camouflage
    2, // Machinegun
    0, // Parachute
    1, // Laser sabre
    0, // Selfdestructor
    5, // Laser cannon
};
int Randomdamage[] =
{
    0, // Pistol
    0, // Machinegun
    0, // Bazooka
    0, // Lavatrap
    0, // S. lavatrap
    0, // Shotgun
    1, // Magnum
    1, // Grenade
    0, // Hmissile
    0, // Laser rifle
    0, // Laser pistol
    0, // Plate
    0, // Rplate
    0, // Pick-axe
    0, // Drill
    0, // Lavabomb
    0, // Plasma pistol
    0, // Targeting system
    0, // Medikit
    0, // Heavy plasma
    0, // Sniper rifle
    0, // Camouflage
    0, // Machinegun
    0, // Parachute
    1, // Laser sabre
    0, // Selfdestructor
    0, // Laser cannon
};
int Canitemselect[] =
{
    1, // Pistol
    1, // Machinegun
    1, // Bazooka
    1, // Lavatrap
    1, // S. lavatrap
    1, // Shotgun
    1, // Magnum
    1, // Grenade
    1, // Hmissile
    1, // Laser rifle
    1, // Laser pistol
    1, // Plate
    1, // Rplate
    1, // Pick-axe
    1, // Drill
    1, // Lavabomb
    1, // Plasma pistol
    0, // Targeting system
    1, // Medikit
    1, // Heavy plasma
    1, // Sniper rifle
    0, // Camouflage
    1, // Machinegun
    0, // Parachute
    1, // Laser sabre
    1, // Selfdestructor
    1, // Laser cannon
};

int Stufflimit[] = // kuinka monta niitä voi kantaa
{
    1, // Pistol
    1, // Machinegun
    1, // Bazooka
    6, // Lavatrap
    3, // S. lavatrap
    1, // Shotgun
    1, // Magnum
    9, // Grenade
    1, // Homing missile launcher
    1, // Laser rifle
    1, // Laser pistol
    10, // Plate
    10, // Rplate
    1, // Pick-axe
    1, // Drill
    2, // Lavabomb
    1, // Plasma pistol
    1, // Targeting system
    1, // Medikit
    1, // Heavy plasma
    1,// Sniper rifle
    1, // Camouflage
    1, // Machinegun
    1, // Parachute
    1, // Laser sabre
    1, // Selfdestructor
    1, // Laser cannon
};
int Bulletlimit[] = // kuinka monta bullettia voi kantaa
{
    160, // BULLET_9mm
    5, // ROCKET
    36, // Shotgun
    90, // BULLET_45
    9, // grenade
    5, // Hmis
    125, // Lasercell
    48, // Plasmapod
    150, // 762
};

int Weaponclip[] =  // mitä bullettia joku ase syö
{
    BULLET_9MM,   // Pistol
    BULLET_9MM,   // Machinegun
    BULLET_ROCKET,// Bazooka
    -1, // Lavatrap
    -1,  // S. lavatrap
    BULLET_SHELLS, // Shotgun
    BULLET_45, // Magnum
    BULLET_GRENADE, // Grenade
    BULLET_HMISSILE, // Hmissile
    BULLET_ENERGYCELL, // Laser rifle
    BULLET_ENERGYCELL, // Laser pistol
    -1, // Plate
    -1, // Rplate
    -1, // Pick-axe
    -1, // Drill
    -1, // Lavabomb
    BULLET_PLASMAPOD, // Plasma pistol
    -1, // Targeting system
    -1, // Medikit
    BULLET_PLASMAPOD, // Heavy plasma
    BULLET_45, // Sniper rifle
    -1, // Camouflage
    BULLET_762, // Machinegun
    -1, // Parachute
    -1, // Laser sabre
    -1, // Selfdestructor
    BULLET_ENERGYCELL, // Laser cannon
};
int Bulletcost[] = // paljon maksaa bulletti
{
    60, // 9MM
    800, // Rocket
    120, // Shells
    100, // Magnum
    800,
    1600, // Homing missile
    500, // Laser cell
    800, // Plasma pod
    200, // 762
};
int Itemcost[] = // paljon maksaa tavara
{
    200,   // Pistol
    4000,  // Machinegun
    8000, // Bazooka
    250, // Lavatrap
    2000, // S. Lavatrap
    3500, // Shotgun
    3000, // Magnum
    600, // Grenade
    13000, // Homing missile launcher
    9000, // Laser rifle
    5000, // Laser pistol
    500, // Plate
    1000, // Rplate
    1000, // Pick-axe
    4000, // Drill
    2000, // Lavabomb
    8500, // Plasma pistol
    5000, // TArgeting system
    2000, // Medikit
    12500, // Heavy plasma
    14000, // Sniper rifle
    1500, // Camouflage
    13000, // Machinegun
    5000, // Parachute
    5000, // Laser sabre
    3000, // Selfdestructor
    20000, // Laser cannon
};

int Bulpic[] = // Bulletin kuva
{
    DATBULLETPIC01, // Pistol
    DATBULLETPIC01, // Machinegun
    DATBULLETPIC03, // Bazooka
    -1, // Lavatrap
    -1, // S. Lavatrap
    DATBULLETPIC02, // Shotgun
    DATBULLETPIC04, // Magnum
    DATBULLETPIC05, // Grenade
    DATBULLETPIC07, // Hmissile
    DATBULLETPIC06, // Laser rifle
    DATBULLETPIC06, // Laser pistol
    -1, // Plate
    -1, // Rplate
    -1, // Pick-axe
    -1, // Drill
    DATBULLETPIC08, // Lavabomb
    DATBULLETPIC09, // Plasma pistol
    -1, // Targeting system
    -1, // Medikit
    DATBULLETPIC09, // Heavy plasma
    DATBULLETPIC04, // Sniper rifle
    -1, // Camouflage
    DATBULLETPIC10, // Machinegun
    -1, // Parachute
    -1, // Laser sabre
    -1, // Selfdestructor
    DATBULLETPIC06, // Laser cannon
};
int Dontneedammo[] =
{
    0, // Pistol
    0, // Machinegun
    0, // Bazooka
    0, // Lavatrap
    0, // S. Lavatrap
    0, // Shotgun
    0, // Magnum
    1, // Grenade
    0, // Hmisl
    0, // Laserrifl
    0, // Laser pistol
    0, // Plate
    0, // Rplate
    0, // Pick-axe
    0, // Drill
    0, // Lavabomb
    0, // Plasma pistol
    0, // Targeting system
    0, // Medikit
    0, // Heavy plasma
    0, // Sniper rifle
    0, // Camouflage
    0, // Machinegun
    0, // Parachute
    0, // Laser sabre
    0, // Selfdestructor
    0, // Laser cannon
};
int Reloadsample[] = // Lataussample
{
    SAMP_RELOAD1, // Pistol
    SAMP_RELOAD1, // Machinegun
    -1, // Bazooka
    -1, // Lavatrap
    -1, // S. Lavatrap
    SAMP_RELOAD2, // Shotgun
    SAMP_RELOAD1, // MAGNUM
    -1, // Grenade
    -1, // Homing
    SAMP_RELOAD1, // Laserr
    SAMP_RELOAD1, // Laser pistol
    -1, // Plate
    -1, // Rplate
    -1, // Pick-axe
    -1, // Drill
    -1, // Lavabomb
    SAMP_RELOAD1, // Plasma pistol
    -1, // Targeting system
    -1, // Medikit
    SAMP_RELOAD1, // Heavy Plasma
    SAMP_RELOAD1, // Sniper rifle
    -1, // Camouflage
    SAMP_RELOAD1, // Machginegun
    -1, // Parachute
    -1, // Laser sabre
    -1, // Selfdestructor
    SAMP_RELOAD2, // Laser cannon
};

int Reloadtime[] = // Latausaika
{
    200, // Pistol
    201, // Machinegun
    600, // Bazooka
    -1,  // Lavatrap
    -1,  // S. Lavatrap
    -1, // Shotgun
    230, // Magnum
    -1, // Grenade
    1000, // Homingmis
    250, // Laser rifle
    250, // Laser pistol
    -1, // Plate
    -1, // Rplate
    -1, // Pick-axe
    -1, // Drill
    0, // Lavabomb
    250, // Plasma pistol
    -1, // Targeting system
    -1, // Medikit
    250, // Heavy plasma
    400, // Sniper rifle
    -1, // Camouflage
    400, // Machinegun
    -1, // Parachute
    -1, // Laser sabre
    -1, // Selfdestructor
    800, // Laser cannon
};
int Weapongunpic[] = // Aseen piipun muoto
{
    0, // Pistol
    9, // Machineg
    2, // Bazooka,
    -1, // Lavatrap
    -1, // Lavatrap
    6, // Shotgun
    0, // Magnum
    -1, // Grenade
    2, // Homing missile launcher
    7, // Laser rifle
    8, // Laser pistol
    -1, // Plate
    -1, // Rplate
    3, // Pick-axe
    4, // Drill
    -1, // Lavabomb
    11, // Plasma pistol
    0, // Targeting system
    -1, // Medikit
    10, // Heavy plasma
    5, // Sniper rifle
    0, // Camouflage
    1, // Machinegun
    0, // Parachute
    12, // Laser sabre
    0, // Selfdestructor
    13, // Laser cannon
};
int Bldenergy[] = // rakennuksen energia
{
    1000,
    1000, // päämajat
    1000,
    60,   // laavatrappi
    120,  // superlaavatrappi
    50, // Plate
    100, // Rplate
};
int Itemicon[] = // Tavaran ikoni menussa
{
    DATMENUBUYPISTOL, // Pistol
    DATMENUBUYSUBMACHINEGUN, // Machineg
    DATMENUBUYBAZOOKA, // Bazooka
    DATMENUBUYLAVATRAP, // Lavatrap
    DATMENUBUYSUPERLAVATRAP, // S. Lavatrap
    DATMENUBUYSHOTGUN, // shotgun
    DATMENUBUYMAGNUM, // magnum
    DATMENUBUYGRENADE, // Grenade
    DATMENUBUYHMISLAUNCHER, // Homingmissilelauncher
    DATMENUBUYLASERRIFLE, // Laser rifle
    DATMENUBUYLASERPISTOL, // Laser rifle
    DATMENUBUYWHITEPLATE, // Plate
    DATMENUBUYGRAYPLATE, // Gray plate
    DATMENUBUYTOOLS, // Pick-axe
    DATMENUBUYDRILL, // Drill
    DATMENUBUYLAVABOMB, // Lavabomb
    DATMENUBUYPLASMAPISTOL, // Plasma pistol
    DATMENUBUYAIM,          // Targeting system
    DATMENUBUYMEDIKIT,      // Medikit
    DATMENUBUYHEAVYPLASMA,  // Heavy plasma
    DATMENUBUYSNIPER,       // Sniper rifle
    DATMENUBUYCAMOUFLAGE,   // Camouflage
    DATMENUBUYMACHINEGUN, // Machinegun
    DATMENUBUYPARACHUTE, // Parachute
    DATMENUBUYLASERSABRE, // Laser sabre
    DATMENUBUYSELFDESTRUCTOR, // Selfdestructor
    DATMENUBUYLASERCANNON, // Laser cannon
};
bool Gunfire[]= // tuleeko suuliekkiä
{
    true,  // Pistol
    true,  // Machinegun
    true, // Bazooka
    false, // LAVATRAP
    false, // S. Lavatrap
    true, /// Shotgun
    true, // Magnum
    false, // grenade
    true, // hmislaunch
    true, // Laser rifle
    true, // Laser pistol
    false, // Plate
    false, // R.Plate
    false, // Pick-axe
    false, // Drill
    false, // Lavabomb
    true, // Plasma pistol
    false, // Targeting system
    false, // Medikit
    true, // Heavy plasma
    true, // Sniper rifle
    false, // Camouflage
    true, // Machinegun
    false, // Parachute
    false, // Laser sabre
    false, // Selfdestructor
    false, // Laser cannon
};

// menujen nimet
char * Menu1text[]=
{
    "Buy menu\0",
    "Inventory\0"
};
char * Menu2text[]=
{
    "Weapons\0",
    "Ammo\0",
    "Items\0",
};
char * Menu3text[]=
{
    "Projectile weapons\0",
    "Energy weapons\0",
    "Bombs\0"
};
char * Menu4text[]=
{
    "Pistol, $200\0",
    "Magnum, $3000\0",
    "Shotgun, $3500\0",
    "Submachinegun, $4000\0",
    "Machinegun, $13000\0",
    "Bazooka, $8000\0",
    "Homing missile launcher, $13000\0",
    "Sniper rifle, $14000",
};
char * Menu4text2[]=
{
    "9mm bullets, $60",
    ".45 bullets $100",
    "Shells, $120",
    "9mm bullets, $60",
    "7.62 bullets $200",
    "Rocket $800",
    "Homing missile $1600",
    ".45 bullets $100",
};
char * Menu5text[]=
{
    "Tools\0",
    "Buildable items\0",
    "Armors\0",
    "Vehicles(In next version)\0",
};
char * Menu6text[]=
{
    "9mm bullets, $60",
    "Shells, $120",
    ".45 bullets $100",
    "7.62 bullets $200",
    "Rocket $800",
    "Homing missile $1600",
    "Laser cell $500",
    "Plasma pod $800",
};
char * Menu7text[]=
{
    "Lavatrap, $200\0",
    "Super lavatrap, $2000\0",
    "Plate, $500\0",
    "Reinforced plate, $1000\0",
};
char * Menu8text[]=
{
    "Grenades, $600\0",
    "Lavabomb, $2000\0",
    "Selfdestructor, $3000\0",
};
char * Menu9text[]=
{
    "Laser sabre, $5000\0",
    "Laser pistol, $5000\0",
    "Laser rifle, $9000\0",
    "Laser cannon, $20000\0",
    "Plasma pistol, $8500\0",
    "Heavy plasma, $12500\0",
};
char * Menu9text2[]=
{
    "No ammo",
    "Laser cell $500",
    "Laser cell $500",
    "Laser cell $500",
    "Plasma pod $800",
    "Plasma pod $800",
};

char * Menu10text[]=
{
    "Kevlar helmet, $1000",
    "Kevlar vest, $1000",
    "Kevlar pants, $1000",
    "Spectra helmet, $2000",
    "Spectra vest, $2000",
    "Spectra pants, $2000",
    "Camouflage, $1500",
};
char * Menu11text[]=
{
    "Pick-axe, $1000",
    "Drill, $4000",
    "Targeting system, $5000",
    "Medikit, $2000",
    "Parachute $5000",
};
char *Menu12text[]=
{
    "Walker, $20000",
    "Transport, $10000",
};
// **********************************************************
int Animspeed[] = // Animaation nopeus
{
    12, // Ani_Walk
    4, // Ani_plasmadeath
}; // int Animspeed[] =
int Animpicture[] = // Animaation kuva
{   9, // Ani_Walk
    12, // Ani_plasmadeath
}; // int Animpicture[] =


// VEHICLET
char * Vehiclename[]=
{
    "Walker",
    "Transport",
};
int Vehicleenergy[]=
{
    100,
    40,
};
int Vehiclecost[]=
{
    20000,
    10000,
};

int Bldpic[]= // Base anim
{
    DATBLD0001, // Hq
    DATBLD0002, // Hq
    DATBLD0003, // Hq
    DATBLD0004, // Lavcatrap
    DATBLD0005, // Slavatrap
    DATBLD0006, // PLate
    DATBLD0007, // Reinfplate
}; // int Bldpics[]=
int Bldhq1animdata[]=
{
    10, // Speed
    4, // How many pics
// + Pic numbers
    0,
    1,
    0,
    2
}; // int Bldanimdata[]=
int Bldlavatrapanimdata[]=
{
    10, // Speed
    8, // How many pics
// + Pic numbers
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7
}; // int Bldanimdata[]=
int *Bldanim[]=
{
    Bldhq1animdata, // Hq
    Bldhq1animdata, // Hq
    Bldhq1animdata, // Hq
    Bldlavatrapanimdata, // Lavcatrap
    Bldhq1animdata, // Slavatrap
    Bldhq1animdata, // PLate
    Bldhq1animdata, // Reinfplate

};

int Bldexp[]=
{
    1, // Hq
    1, // Hq
    1, // Hq
    4, // Lavcatrap
    4, // Slavatrap
    4, // PLate
    4, // Reinfplate
}; // int Bldexp[]=

#endif
