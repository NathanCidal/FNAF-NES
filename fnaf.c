#include "LIB/nesdoug.h"
#include "LIB/neslib.h"
#include "NES_ST/titleScreen.h"
#include "bg.h"

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
unsigned char text1[] = "FIVE NIGHTS";
unsigned char text2[] = "AT FREDDY'S";
unsigned char text3[] = "PRESS START";
unsigned char text4[] = "TO PLAY";

unsigned char pm12[] = "12 PM";
unsigned char am01[] = "01 AM";
unsigned char am02[] = "02 AM";
unsigned char am03[] = "03 AM";
unsigned char am04[] = "04 AM";
unsigned char am05[] = "05 AM";
unsigned char am06[] = "06 AM";

//Variaveis Globais
unsigned char screenIndex;
int address;        
unsigned char i;
unsigned char gasto;
unsigned char hora;

//Variaveis para renderização do Mapa
const unsigned char * p_maps;
unsigned char c_map[240];
unsigned char coordinates;
unsigned char temp1;
unsigned char temp_x;
unsigned char temp_y;

//Controles
unsigned char pad1;

//Prototype
void check_gasto(void);
void draw_bg(void);
void draw_show(void);
void exibit_TitleScreen(void);
void exibit_cam1(void);
void checkStartButton(void);
void draw_time(void);

//Teste
void player_ctrl(void);

//Paleta de cores da tela de titulo
const unsigned char tittleScreenPalette[16]={ 
    BLACK, BROWN, DARK_GREY,  GREY,
    BLACK,0x01,0x21,0x31,        // 01 (Blue)
    BLACK,0x06,0x16,0x26,        // 10 (Red)
    BLACK,0x09,0x19,0x29         // 11 (Green)
};

void exibit_TitleScreen(void){
    ppu_off();                          //Desliga a Tela
    pal_bg(tittleScreenPalette);        //Seta a paleta do Background para o array de char declarado
    bank_bg(0);                         //Utilizar somente a primeira parte do banco de Tiles
    vram_adr(NAMETABLE_A);              //Seto a posição inicial da VRAM no topo
    vram_unrle(titleScreen);            //Descompacto a imagem do Freddy
    ppu_on_all();                       //Ligo a tela
    ppu_wait_nmi();                     //Faço a VRAM esperar updates no nmi(usado para vídeo)
    set_vram_buffer();                  //Faço o ponteiro da VRAM estar para o nmi
    multi_vram_buffer_horz(text1, sizeof(text1), NTADR_A(4,4));		//Coloca texto
    multi_vram_buffer_horz(text2, sizeof(text2), NTADR_A(4,6));		//Coloca texto
    multi_vram_buffer_horz(text3, sizeof(text3),NTADR_A(4,17));     //Coloca texto
    multi_vram_buffer_horz(text4, sizeof(text4),NTADR_A(6, 18));    //Coloca texto
    ppu_wait_nmi();                     //Mando novamente, porém atualiza oque estava na imagem
}

void draw_bg(void){
    if(screenIndex == 0){
        exibit_TitleScreen();
    }

    if(screenIndex == 1){
        draw_show();
    }
}


void draw_show(void){
    ppu_off();
    bank_bg(1);
    p_maps = All_Bg_Maps[0];
    memcpy(c_map, p_maps, 240);
    vram_adr(NAMETABLE_A);

    for(temp_y = 0; temp_y < 15; ++temp_y){
        for(temp_x = 0; temp_x < 16; ++temp_x){
			temp1 = (temp_y << 4) + temp_x;

            if(c_map[temp1] == 0){
                vram_put(0);
                vram_put(0);
            }else if(c_map[temp1] == 1){
                vram_put(0x02);
                vram_put(0x03);
            }else if(c_map[temp1] == 2){
                vram_put(0x04);
                vram_put(0x05);
            }else if(c_map[temp1] == 3){
                vram_put(0x06);
                vram_put(0x07);
            }else if(c_map[temp1] == 4){
                vram_put(0x08);
                vram_put(0x09);
            }
		}
		
		// draw a second row of tiles
		for(temp_x = 0; temp_x < 16; ++temp_x){
			temp1 = (temp_y << 4) + temp_x;

            if(c_map[temp1] == 0){
                vram_put(0);
                vram_put(0);
            }else if(c_map[temp1] == 1){
                vram_put(0x12);
                vram_put(0x13);
            }else if(c_map[temp1] == 2){
                vram_put(0x14);
                vram_put(0x15);
            }else if(c_map[temp1] == 3){
                vram_put(0x16);
                vram_put(0x17);
            }else if(c_map[temp1] == 4){
                vram_put(0x18);
                vram_put(0x19);
            }
		}
    }
    

    check_gasto();
    
    ppu_on_all();
    draw_time();
}

void checkStartButton(void){
    if(pad1 & PAD_START){
        screenIndex++;
        if(screenIndex >= 4) screenIndex = 0;
        draw_bg();
    }
}

void player_ctrl(void){
    if(pad1 & PAD_A){
        hora += 1;
        if(hora >= 7){ hora = 7; }
        gasto += 1;
        if(gasto <= 0){ gasto = 1; }
        if(gasto >= 5){ gasto = 4; }

        draw_bg();
        delay(10);
    }else if(pad1 & PAD_B){
        gasto -= 1;
        hora -= 1;
        if(hora <= 0){ hora = 1;}

        if(gasto <= 0){ gasto = 1; }
        if(gasto >= 5){ gasto = 4; }
        draw_bg();
        delay(10);
    }
}

void draw_time(void){
    ppu_wait_nmi();
    set_vram_buffer();
    switch (hora)
    {
    case 1: multi_vram_buffer_horz(pm12, sizeof(pm12), NTADR_A(8,24));	
        break;
    case 2: multi_vram_buffer_horz(am01, sizeof(am01), NTADR_A(8,24));	
        break;
    case 3: multi_vram_buffer_horz(am02, sizeof(am02), NTADR_A(8,24));	
        break;
    case 4: multi_vram_buffer_horz(am03, sizeof(am03), NTADR_A(8,24));	
        break;
    case 5: multi_vram_buffer_horz(am04, sizeof(am04), NTADR_A(8,24));	
        break;
    case 6: multi_vram_buffer_horz(am05, sizeof(am05), NTADR_A(8,24));	
        break;
    case 7: multi_vram_buffer_horz(am06, sizeof(am06), NTADR_A(8,24));	
        break;
    default: multi_vram_buffer_horz(pm12, sizeof(pm12), NTADR_A(8,24));	
        break;
    }

    ppu_wait_nmi();
}

void check_gasto(void){
    address = get_at_addr(0,0,0);       //Agora zeramos o Endereço
    vram_adr(address);                  // Setamos esse endereço na VRAM      

    for(i = 0; i < 5; ++i){
        vram_fill(0x0, 8);
    }

    if(gasto == 1){
        vram_fill(0xFF, 2);
        vram_fill(0x00, 1);
        vram_fill(0x00, 1);
    }

    if(gasto == 2){
        vram_fill(0xFF, 2);
        vram_fill(0x55, 1);
        vram_fill(0x00, 1);
    }

    if(gasto == 3){
        vram_fill(0xFF, 2);
        vram_fill(0x55, 1);
        vram_fill(0xAA, 1);
    }

    if(gasto == 4){
        vram_fill(0xAA, 2);
        vram_fill(0xAA, 1);
        vram_fill(0xAA, 1);
    }

    vram_fill(0x55, 1);
    vram_fill(0x55, 12);      //1 == Preenche só 2 Tiles : O
}



void main(){

    ppu_off();
    bank_bg(0);
    screenIndex = 0;
    hora = 1;
    gasto = 1;
    pal_bg(tittleScreenPalette);        //Seta a paleta do Background para o array de char declarado
    draw_bg();

    while(1){
        ppu_wait_nmi();
        pad1 = pad_poll(0);

        player_ctrl();
        checkStartButton();
    }
}
