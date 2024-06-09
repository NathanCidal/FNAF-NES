#include "LIB/nesdoug.h"
#include "LIB/neslib.h"
#include "NES_ST/titleScreen.h"

//Defines para cores
#define BLACK      0x0f
#define YELLOW     0x28
#define WHITE      0x30
#define BROWN      0x17
#define DARK_GREY  0x00
#define GREY       0x10
#define LT_BLUE    0x31
#define LT_RED     0x26

//Variaveis de Texto
unsigned char text[] = "FIVE NIGHTS";
unsigned char text1[] = "AT FREDDY'S";
unsigned char text2[] = "PRESS START";
unsigned char text3[] = "TO PLAY";

//Variaveis Globais
int address;        
unsigned char i;

//Paleta de cores da tela de titulo
const unsigned char tittleScreenPalette[16]={ 
    BLACK, BROWN, DARK_GREY,  GREY,
    BLACK, BLACK, BLACK, BLACK,
    BLACK, BLACK, BLACK, BLACK,
    BLACK, BLACK, BLACK, BLACK
    };

void main(){

    //Inicialização
    ppu_off();                          //Desliga a Tela
    pal_bg(tittleScreenPalette);        //Seta a paleta do Background para o array de char declarado
    bank_bg(0);                         //Utilizar somente a primeira parte do banco de Tiles
    vram_adr(NAMETABLE_A);              //Seto a posição inicial da VRAM no topo
    vram_unrle(titleScreen);            //Descompacto a imagem do Freddy
    ppu_on_all();                       //Ligo a tela
    ppu_wait_nmi();                     //Faço a VRAM esperar updates no nmi(usado para vídeo)
    set_vram_buffer();                  //Faço o ponteiro da VRAM estar para o nmi
    multi_vram_buffer_horz(text, sizeof(text), NTADR_A(4,4));		//Coloca texto
    multi_vram_buffer_horz(text1, sizeof(text1), NTADR_A(4,6));		//Coloca texto
    multi_vram_buffer_horz(text2, sizeof(text2),NTADR_A(4,17));     //Coloca texto
    multi_vram_buffer_horz(text3, sizeof(text3),NTADR_A(6, 18));    //Coloca texto
    ppu_wait_nmi();                     //Mando novamente, porém atualiza oque estava na imagem

    while(1){
        //Loop
    }

}