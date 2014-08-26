/*

Äänijutskat.

(C) 1999 Tero Laitinen (Replica§)

*/

#ifndef __sound_h
#define __sound_h

bool Onlyonce = false;
UNIMOD * Music , *Music2;                 // Module
void Tickhandler(void);         // soitetaan aina yks tikki modulestaq
void Startmusic();              // aloitetaan musiikinsoitto
void Init_Music();              // Ladataan musik
void DeInit_Music();            // vapautetaan musik

void Tickhandler(void)
{
	MP_HandleTick();    /* play 1 tick of the module */
	MD_SetBPM(mp_bpm);
}

void Startmusic()
 {
  mp_volume = 0;
  mp_loop = 1;
  if (Opt->Sound)    MD_PlayStart();         // start playing the music
  if (Opt->Sound)    if (Onlyonce==false)  {install_int (MD_Update, 10);  Onlyonce = true;}// update the buffer every 10 msec}
 } // Startmusic
void Init_Music()
{

    setvbuf(stdout, NULL, _IONBF, 0);
    srandom(_farpeekw(_dos_ds, 0x0046C));

//  Initialize soundcard parameters.. you _have_ to do this
//  before calling MD_Init(), and it's illegal to change them
//  after you've called MD_Init()

    md_mixfreq      =Opt->Sndfreq;                     /* standard mixing freq */
    md_dmabufsize   =4000;                     /* standard dma buf size */
    md_mode= 0;
    if (Opt->Bits16) md_mode+=DMODE_16BITS;
    if (Opt->Interpolated) md_mode+=DMODE_INTERP;
    if (Opt->Stereo) md_mode+=DMODE_STEREO;


    //md_mode         =DMODE_16BITS|DMODE_INTERP|DMODE_STEREO;              /* standard mixing mode */

   md_device       =0;                                                     /* standard device: autodetect */
    
    ML_RegisterLoader(&load_s3m);
    ML_RegisterLoader(&load_xm);   // Register the loaders we want to use..

	MD_RegisterDriver(&drv_nos);
#ifdef __OS2__
	MD_RegisterDriver(&drv_os2);
#elif defined(__WIN32__)
	MD_RegisterDriver(&drv_w95);
#else
	MD_RegisterDriver(&drv_ss);
	MD_RegisterDriver(&drv_sb);
	MD_RegisterDriver(&drv_gus);
#endif

    MD_RegisterPlayer(Tickhandler);

    text_mode (-1);

    if(!MD_Init())  // initialize soundcard 
        {
		printf("Driver error: %s.\n",myerr);
        allegro_exit();
         exit (1);
        }
    
   Music = ML_LoadFN("5th_answ.xm");
  if(Music==NULL)                // exit with errormsg
        {
         printf("\nFile 5th_answ.xm not found.\n");
         allegro_exit();
         exit (1);
        }
   Music2 = ML_LoadFN("main.xm");
  if(Music2==NULL)                // exit with errormsg
        {
        printf("\nFile main.xm not found.\n");
        allegro_exit();
        exit (1);
        }

    printf("\nUsing %s for %d bit %s %s sound at %uHz\n\n",
			md_driver->Name,
			(md_mode&DMODE_16BITS) ? 16:8,
			(md_mode&DMODE_INTERP) ? "interpolated":"normal",
			(md_mode&DMODE_STEREO) ? "stereo":"mono",
			md_mixfreq);

    MP_Init(Music);            // initialize modplayer to play this module

    md_numchn=Music->numchn+8;   // set the number of voices to use.. you
                            // could add extra channels here (e.g. md_numchn=mf->numchn+4; )
                            // to use for your own soundeffects:


}


void DeInit_Music()
 {
    MD_PlayStop();
    ML_Free(Music);
    ML_Free(Music2);
    MD_Exit();

 } // Deinit_music()


#endif
