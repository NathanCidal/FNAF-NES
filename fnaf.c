#include "LIB/nesdoug.h"
#include "LIB/neslib.h"

#define BLACK   0x0f
#define YELLOW  0x28
#define WHITE   0x30

unsigned char text[] = "Hello World!";

unsigned char paletteBasic[] = {
    BLACK, BLACK, BLACK, YELLOW,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0
};

void main(){

    //Inicialização
    ppu_off();
    pal_bg(paletteBasic);
    vram_adr(NTADR_A(8,13));
    vram_write(text, sizeof(text));
    ppu_on_all();

    while(1){
        //Loop Infinito
    }

}