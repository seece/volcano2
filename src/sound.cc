
#include "sound.h"

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <ctime>
#include <mikmod.h>

using std::min;

const int maxChan = 64; // TODO: probably not reasonable

/*--------------------------
 * Globals
 *-------------------------*/

MODULE * gameMusic , *menuMusic;                 // Module
MODULE * currentMusic;
SAMPLE * Samp[SAMPLE_COUNT];             // Kaikki samplet
struct SoundOptions* soundOpt;
SWORD musicCurVolume;

/*-------------------------
 * Local declarations
 *------------------------*/

void Playsample(SAMPLE *smp);
void Playsample(SAMPLE *smp,int Vol, int Pan, int Freq);
void Startmusic();

/*-------------------------
 * Implementations
 *------------------------*/

void StartGameMusic()
{
    currentMusic = gameMusic;
    Startmusic();
}

void StartMenuMusic()
{
    currentMusic = menuMusic;
    Startmusic();
}

void Startmusic()
{
    // TODO: probably not a good idea to set volume instantly to 0
    musicCurVolume = 0;
    Player_SetVolume(musicCurVolume);
    if (soundOpt->Sound) Player_Start(currentMusic);         // start playing the music
}

bool Init_Music(SoundOptions* sndOpt)
{
    srandom(time(0));
    soundOpt = sndOpt;

    //  Initialize soundcard parameters.. you _have_ to do this
    //  before calling MD_Init(), and it's illegal to change them
    //  after you've called MD_Init()

    md_mixfreq = soundOpt->Sndfreq;                     /* standard mixing freq */
    md_mode = 0;
    if (soundOpt->Bits16)       md_mode |= DMODE_16BITS;
    if (soundOpt->Interpolated) md_mode |= DMODE_INTERP;
    if (soundOpt->Stereo)       md_mode |= DMODE_STEREO;

    MikMod_RegisterLoader(&load_s3m);
    MikMod_RegisterLoader(&load_xm);   // Register the loaders we want to use..

    MikMod_RegisterAllDrivers();

    if(!MikMod_Init(0)) {
        printf("\nMikMod_Init failure: %s\n",
               MikMod_strerror(MikMod_errno));
        return false;
    }

    gameMusic = Player_Load("5th_answ.xm", maxChan, 0);
    if(gameMusic==NULL) {
        printf("\nFile 5th_answ.xm not found.\n");
        return false;
    }

    menuMusic = Player_Load("main.xm", maxChan, 0);
    if(menuMusic==NULL) {
        printf("\nFile main.xm not found.\n");
        return false;
    }

    printf("\nUsing %s for %d bit %s %s sound at %uHz\n\n",
           md_driver->Name,
           (md_mode&DMODE_16BITS) ? 16:8,
           (md_mode&DMODE_INTERP) ? "interpolated":"normal",
           (md_mode&DMODE_STEREO) ? "stereo":"mono",
           md_mixfreq);
}


void DeInit_Music()
{
    Player_Stop();
    Player_Free(gameMusic);
    Player_Free(menuMusic);
    MikMod_Exit();

}

void Loadsamples()
{
    Samp[SAMP_PISTOL]        = Sample_Load("sounds/pistol.wav");
    Samp[SAMP_ROCKET]        = Sample_Load("sounds/rlaunch.wav");
    Samp[SAMP_MACHINEGUN]    = Sample_Load("sounds/machineg.wav");
    Samp[SAMP_DIRT1]         = Sample_Load("sounds/dirt1.wav");
    Samp[SAMP_FLESH1]        = Sample_Load("sounds/flesh1.wav");
    Samp[SAMP_FLESH2]        = Sample_Load("sounds/flesh2.wav");
    Samp[SAMP_FLESH3]        = Sample_Load("sounds/flesh3.wav");
    Samp[SAMP_RELOAD1]       = Sample_Load("sounds/reload1.wav");
    Samp[SAMP_RELOAD2]       = Sample_Load("sounds/reload2.wav");
    Samp[SAMP_RELOAD3]       = Sample_Load("sounds/reload3.wav");
    Samp[SAMP_RELOAD4]       = Sample_Load("sounds/reload4.wav");
    Samp[SAMP_RELOAD5]       = Sample_Load("sounds/reload5.wav");
    Samp[SAMP_WATER1]        = Sample_Load("sounds/water1.wav");
    Samp[SAMP_WATER2]        = Sample_Load("sounds/water2.wav");
    Samp[SAMP_WATER3]        = Sample_Load("sounds/water3.wav");
    Samp[SAMP_WATER4]        = Sample_Load("sounds/water4.wav");
    Samp[SAMP_BOUNCE1]       = Sample_Load("sounds/bounce1.wav");
    Samp[SAMP_EXP1]          = Sample_Load("sounds/exp1.wav");
    Samp[SAMP_EXP2]          = Sample_Load("sounds/exp2.wav");
    Samp[SAMP_SHOTGUN]       = Sample_Load("sounds/shotgun.wav");
    Samp[SAMP_MAGNUM]        = Sample_Load("sounds/magnum.wav");
    Samp[SAMP_LASER]         = Sample_Load("sounds/laser.wav");
    Samp[SAMP_PLASMA]        = Sample_Load("sounds/plasma.wav");
    Samp[SAMP_SNIPER]        = Sample_Load("sounds/sniper.wav");
    Samp[SAMP_EXP3]          = Sample_Load("sounds/exp3.wav");
    Samp[SAMP_BIGMACHINEGUN] = Sample_Load("sounds/762.wav");
    Samp[SAMP_EMPTYSHELL]    = Sample_Load("sounds/emptys.wav");
}

void Free_sounds()
{
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        Sample_Free(Samp[i]);
    }
}

void Playsample(SAMPLE *smp,int Vol, int Pan, int Freq)
{
    if (!Freq) Freq = smp->speed; // pitäis olla suht koht selvät...
    if (soundOpt->Sound) {
        SBYTE voiceIndex = Sample_Play(smp, 0, 0);
        Voice_SetVolume(voiceIndex,Vol);
        Voice_SetPanning(voiceIndex,Pan);
        Voice_SetFrequency(voiceIndex,Freq);
    }
}

void Playsample(SAMPLE *smp)
{
    Playsample(smp, 0, 128, 0);
}

void Playsample(int smp,int Vol, int Pan)
{
    Playsample(Samp[smp], Vol, Pan, 0);
}

void Playsample(int smp,int Vol, int Pan, int Freq)
{
    Playsample(Samp[smp], Vol, Pan, Freq);
}

void SoundUpdate(int elapsedMsec)
{
    if(soundOpt->Musicvolume != musicCurVolume) {
        // TODO: hackety hack / not going to work
        int change = min(elapsedMsec/20, 1);
        if(soundOpt->Musicvolume < musicCurVolume) {
            change = -change;
        }
        musicCurVolume += change;

        Player_SetVolume(musicCurVolume);
    }

    MikMod_Update();
}