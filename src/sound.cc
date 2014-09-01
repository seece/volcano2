
#include "sound.h"

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <ctime>
#include <mikmod.h>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>

const int maxChan = 64; // TODO: probably not reasonable

/*--------------------------
 * Thread messaging
 *-------------------------*/

enum class SMesgT {
    PLAY_SAMPLE,
    START_GAME_MUSIC,
    START_MENU_MUSIC,
    STOP_UPDATER
};

struct SoundMessage {
    SMesgT type;
    int sampleIndex;
    int sampleVolume;
    int samplePan;
    int sampleFreq;
    SoundMessage(SMesgT t) : type(t) {}
};


struct SoundMessageQueue {
    std::queue<SoundMessage> messages;
    std::atomic<unsigned> ticketCounter;
    std::atomic<unsigned> nextTicket;

    SoundMessageQueue() : ticketCounter(0), nextTicket(0) {}

    void send(SoundMessage mesg)
    {
        lock();
        messages.push(mesg);
        unlock();
    }

    void lock()
    {
        unsigned ticketNum = ticketCounter++;
        std::unique_lock<std::mutex> waitLock;
        while(nextTicket < ticketNum) {
            // Spin lock
        }
    }

    void unlock()
    {
        nextTicket++;
    }
};

/*--------------------------
 * Globals
 *-------------------------*/

MODULE * gameMusic , *menuMusic;                 // Module
SAMPLE * Samp[SAMPLE_COUNT];             // Kaikki samplet
struct SoundOptions* soundOpt;

std::thread updaterThread;
SoundMessageQueue soundMessages;


/*-------------------------
 * Local declarations
 *------------------------*/

void playSample(SAMPLE *smp,int Vol, int Pan, int Freq);
void startMusic();
void loadSamples();
void freeSamples();
void audioUpdater(SoundMessageQueue* smessages);
bool processSoundMessages(SoundMessageQueue& smessages);

/*-------------------------
 * Implementations
 *------------------------*/

void StartGameMusic()
{
    soundMessages.send(SoundMessage(SMesgT::START_GAME_MUSIC));
}

void StartMenuMusic()
{
    soundMessages.send(SoundMessage(SMesgT::START_MENU_MUSIC));
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
    md_mode |= DMODE_SOFT_MUSIC;
    md_mode |= DMODE_SOFT_SNDFX;

    MikMod_RegisterLoader(&load_s3m);
    MikMod_RegisterLoader(&load_xm);   // Register the loaders we want to use..

    MikMod_RegisterAllDrivers();

    if (MikMod_Init(0) != 0) {
        printf("\nMikMod_Init failure: %s\n",
               MikMod_strerror(MikMod_errno));
        return false;
    }

    MikMod_SetNumVoices(maxChan, maxChan);

    gameMusic = Player_Load("5th_answ.xm", maxChan, 0);
    if (gameMusic == NULL) {
        printf("\nFile 5th_answ.xm not found.\n");
        return false;
    }

    menuMusic = Player_Load("main.xm", maxChan, 0);
    if (menuMusic == NULL) {
        printf("\nFile main.xm not found.\n");
        return false;
    }

    printf("\nUsing %s for %d bit %s %s sound at %uHz\n\n",
           md_driver->Name,
           (md_mode&DMODE_16BITS) ? 16:8,
           (md_mode&DMODE_INTERP) ? "interpolated":"normal",
           (md_mode&DMODE_STEREO) ? "stereo":"mono",
           md_mixfreq);

    loadSamples();

    Player_SetVolume(100);
    MikMod_EnableOutput();

    updaterThread = std::thread(audioUpdater, &soundMessages);

    return true;
}


void DeInit_Music()
{
    soundMessages.send(SoundMessage(SMesgT::STOP_UPDATER));
    updaterThread.join();
    Player_Stop();
    Player_Free(gameMusic);
    Player_Free(menuMusic);
    MikMod_DisableOutput();
    freeSamples();
    MikMod_Exit();
}

void loadSamples()
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

void freeSamples()
{
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        Sample_Free(Samp[i]);
    }
}

void Playsample(int smp,int Vol, int Pan)
{
    Playsample(smp, Vol, Pan, 0);
}

void Playsample(int smp,int Vol, int Pan, int Freq)
{
    SoundMessage mesg(SMesgT::PLAY_SAMPLE);
    mesg.sampleIndex = smp;
    mesg.sampleVolume = Vol;
    mesg.samplePan = Pan;
    mesg.sampleFreq = Freq;
    soundMessages.send(mesg);
}

void startMusic(MODULE* mus)
{
    if (soundOpt->Sound) {
        Player_SetPosition(0);
        Player_Start(mus);
    }
}

void playSample(SAMPLE *smp,int Vol, int Pan, int Freq)
{
    if (!Freq) Freq = smp->speed; // pitäis olla suht koht selvät...
    if (soundOpt->Sound) {
        SBYTE voiceIndex = Sample_Play(smp, 0, 0);
        Voice_SetVolume(voiceIndex,Vol);
        Voice_SetPanning(voiceIndex,Pan);
        Voice_SetFrequency(voiceIndex,Freq);
    }
}


/**
 * Process messages in audioUpdater threads message queue
 *
 * @param the message queue
 * @return true if there was no stop message
 */
bool processSoundMessages(SoundMessageQueue& smessages)
{
    bool ret = true;

    std::queue<SoundMessage> messages;
    smessages.lock();
    messages.swap(smessages.messages);
    smessages.unlock();

    while(!messages.empty() && ret) {
        SoundMessage& mesg = messages.front();

        switch(mesg.type) {
        case SMesgT::PLAY_SAMPLE: {
            playSample(Samp[mesg.sampleIndex],
                       mesg.sampleVolume,
                       mesg.samplePan,
                       mesg.sampleFreq);
            break;
        }

        case SMesgT::START_GAME_MUSIC: {
            startMusic(gameMusic);
            break;
        }

        case SMesgT::START_MENU_MUSIC: {
            startMusic(menuMusic);
            break;
        }

        case SMesgT::STOP_UPDATER: {
            ret = false;
            break;
        }

        }

        messages.pop();
    }

    return ret;
}

void audioUpdater(SoundMessageQueue* smessages)
{
    bool run = true;
    while(run) {
        run = processSoundMessages(*smessages);
        if(!Player_Active()) {
            startMusic(Player_GetModule());
        }
        MikMod_Update();
    }
}
