/*

Äänijutskat.

(C) 1999 Tero Laitinen (Replica§)

*/

#ifndef SOUND_H
#define SOUND_H

struct SoundOptions {
    int Musicvolume, Soundvolume;
    int Sndfreq;
    bool Sound, Bits16,Stereo,Interpolated;
};

enum Samples {
    SAMP_PISTOL,
    SAMP_ROCKET,
    SAMP_MACHINEGUN,
    SAMP_DIRT1,
    SAMP_FLESH1,
    SAMP_FLESH2,
    SAMP_FLESH3,
    SAMP_RELOAD1,
    SAMP_RELOAD2,
    SAMP_RELOAD3,
    SAMP_RELOAD4,
    SAMP_RELOAD5,
    SAMP_WATER1,
    SAMP_WATER2,
    SAMP_WATER3,
    SAMP_WATER4,
    SAMP_BOUNCE1,
    SAMP_EXP1,
    SAMP_EXP2,
    SAMP_SHOTGUN,
    SAMP_MAGNUM,
    SAMP_LASER,
    SAMP_PLASMA,
    SAMP_SNIPER,
    SAMP_EXP3,
    SAMP_BIGMACHINEGUN,
    SAMP_EMPTYSHELL,
    SAMPLE_COUNT
};


void Loadsamples(); // lataa samplet
void Free_sounds(); // vapauttaa muistin
// Neljä erilaista versiota playsamplesta

void Playsample(int smp,int Vol, int Pan);
void Playsample(int smp,int Vol, int Pan, int Freq);
void StartGameMusic();
void StartMenuMusic();
void StartMusic();

void SoundUpdate(int elapsedMsec);

/**
 * Inits MikMod / prints error messages.
 *
 * @return true on success
 */
bool Init_Music();


void DeInit_Music();            // vapautetaan musik

#endif
