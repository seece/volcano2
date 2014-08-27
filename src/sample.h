#ifndef __sample_h
#define __sample_h

#define Maxsamples              30

#define SAMP_PISTOL             0
#define SAMP_ROCKET             1
#define SAMP_MACHINEGUN         2
#define SAMP_DIRT1              3
#define SAMP_FLESH1             4
#define SAMP_FLESH2             5
#define SAMP_FLESH3             6
#define SAMP_RELOAD1            7
#define SAMP_RELOAD2            8
#define SAMP_RELOAD3            9
#define SAMP_RELOAD4           10
#define SAMP_RELOAD5           11
#define SAMP_WATER1            12
#define SAMP_WATER2            13
#define SAMP_WATER3            14
#define SAMP_WATER4            15
#define SAMP_BOUNCE1           16
#define SAMP_EXP1              17
#define SAMP_EXP2              18
#define SAMP_LASER             19
#define SAMP_SHOTGUN           20
#define SAMP_MAGNUM            21
#define SAMP_PLASMA            22
#define SAMP_SNIPER            23
#define SAMP_EXP3              24
#define SAMP_BIGMACHINEGUN     25
#define SAMP_EMPTYSHELL        26

void Loadsamples(); // lataa samplet
void Free_sounds(); // vapauttaa muistin
// Neljä erilaista versiota playsamplesta
void Playsample(MSAMPLE *smp);
void Playsample(int smp,int Vol, int Pan);
void Playsample(int smp,int Vol, int Pan, int Freq);
void Playsample(MSAMPLE *smp,int Vol, int Pan, int Freq);

int Cursamp=Music->numchn;              // mille kanavalle menee tavaraa
MSAMPLE * Samp[Maxsamples];             // Kaikki samplet

void Loadsamples()
 {
   memset(&Samp, 0, 4*Maxsamples);
   Samp[SAMP_PISTOL]     = MW_LoadWavFN("sounds/pistol.wav");
   Samp[SAMP_ROCKET]     = MW_LoadWavFN("sounds/rlaunch.wav");
   Samp[SAMP_MACHINEGUN] = MW_LoadWavFN("sounds/machineg.wav");
   Samp[SAMP_DIRT1]      = MW_LoadWavFN("sounds/dirt1.wav");
   Samp[SAMP_FLESH1]     = MW_LoadWavFN("sounds/flesh1.wav");
   Samp[SAMP_FLESH2]     = MW_LoadWavFN("sounds/flesh2.wav");
   Samp[SAMP_FLESH3]     = MW_LoadWavFN("sounds/flesh3.wav");
   Samp[SAMP_RELOAD1]    = MW_LoadWavFN("sounds/reload1.wav");
   Samp[SAMP_RELOAD2]    = MW_LoadWavFN("sounds/reload2.wav");
   Samp[SAMP_RELOAD3]    = MW_LoadWavFN("sounds/reload3.wav");
   Samp[SAMP_RELOAD4]    = MW_LoadWavFN("sounds/reload4.wav");
   Samp[SAMP_RELOAD5]    = MW_LoadWavFN("sounds/reload5.wav");
   Samp[SAMP_WATER1]     = MW_LoadWavFN("sounds/water1.wav");
   Samp[SAMP_WATER2]     = MW_LoadWavFN("sounds/water2.wav");
   Samp[SAMP_WATER3]     = MW_LoadWavFN("sounds/water3.wav");
   Samp[SAMP_WATER4]     = MW_LoadWavFN("sounds/water4.wav");
   Samp[SAMP_BOUNCE1]    = MW_LoadWavFN("sounds/bounce1.wav");
   Samp[SAMP_EXP1]       = MW_LoadWavFN("sounds/exp1.wav");
   Samp[SAMP_EXP2]       = MW_LoadWavFN("sounds/exp2.wav");
   Samp[SAMP_SHOTGUN]    = MW_LoadWavFN("sounds/shotgun.wav");
   Samp[SAMP_MAGNUM]     = MW_LoadWavFN("sounds/magnum.wav");
   Samp[SAMP_LASER]      = MW_LoadWavFN("sounds/laser.wav");
   Samp[SAMP_PLASMA]     = MW_LoadWavFN("sounds/plasma.wav");
   Samp[SAMP_SNIPER]     = MW_LoadWavFN("sounds/sniper.wav");
   Samp[SAMP_EXP3]     = MW_LoadWavFN("sounds/exp3.wav");
   Samp[SAMP_BIGMACHINEGUN]     = MW_LoadWavFN("sounds/762.wav");
   Samp[SAMP_EMPTYSHELL]     = MW_LoadWavFN("sounds/emptys.wav");

 } // Loadsamples
void Free_sounds()
 {
   for (int i = 0; i < Maxsamples; i++) if (Samp[i])
    MW_FreeWav(Samp[i]);
 } // Load_sounds

void Playsample(MSAMPLE *smp,int Vol, int Pan, int Freq)
 {
 if (!Freq) Freq = smp->c2spd; // pitäis olla suht koht selvät...
 if (Opt->Sound){
            if (Cursamp < Music->numchn) Cursamp = Music->numchn;
	    MD_VoiceSetVolume(Cursamp,Vol);
	    MD_VoiceSetPanning(Cursamp,Pan);
            MD_VoiceSetFrequency(Cursamp,Freq);
            MD_VoicePlay(Cursamp,smp->handle,0,smp->length,0,0,smp->flags);
            Cursamp++;
            if (Cursamp >= md_numchn) Cursamp = Music->numchn;
            }
 } // Playsample
void Playsample(MSAMPLE *smp)
 {
   if (Opt->Sound)
   Playsample(smp, 0, 128, 0);
 } // Playsample
void Playsample(int smp,int Vol, int Pan)
 {
   Playsample(Samp[smp], Vol, Pan, 0);
 } // Playsample(int smp,int Vol, int Pan)
void Playsample(int smp,int Vol, int Pan, int Freq)
 {
   Playsample(Samp[smp], Vol, Pan, Freq);
 } // Playsample(int smp,int Vol, int Pan)
#endif
