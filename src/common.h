/*
Tavalliset jutskat.

(C) 1999 Tero Laitinen (Replica§)

*/

#ifndef __common_h
#define __common_h

// Hiirihärvelit
int Mox, Moy, Mob, Moldb; // X, Y, Nappi, Edellinennappi
Toptions *Opt = new Toptions;

bool Mousein(int x1, int y1, int x2, int y2); // Jos hiiri on tämän alueen
// sisällä
void UpdateMouse();                           // päivittää hiirtä
void SaveOptions();                           // tallentaa optionit
void LoadOptions();                           // lataa optionit
void InitAllegro();                           // käynnistää allegron
void DeInitAllegro();                         // poistuu allegrosta


bool Mousein(int x1, int y1, int x2, int y2)
{
    if (Mox >= x1)
        if (Mox <= x2)
            if (Moy >= y1)
                if (Moy <= y2)
                    return(true);
    return(false);

} // Mousein
void UpdateMouse()
{
    Moldb = Mob;

    Mob = mouse_b;
    Mox = mouse_x;
    Moy = mouse_y;
} // UpdateMouse

void SaveOptions()
{
    FILE * f = fopen("options.cfg", "wb+");
    fwrite(Opt, sizeof(Toptions), 1, f);
    fclose(f);
} // SaveOptions
void LoadOptions()
{
    FILE * f = fopen("options.cfg", "rb+");
    if (f != NULL)
    {
        fread(Opt, sizeof(Toptions), 1, f);
        fclose(f);
    } // (f != NULL)
} // LoadOptions
void InitAllegro()
{
    allegro_init();
    install_mouse();
    install_timer();
    install_keyboard();
} // Initallegro
void DeInitAllegro()
{
    allegro_exit();
} // DeInitallegro


#endif
