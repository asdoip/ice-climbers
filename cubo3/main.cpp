#include <stdio.h>
#include <allegro.h>
#include <time.h>
#include "mov.h"

#define MAX_ALTURA_nivel_1 69
#define MAX_ANCHURA  34
#define MAX_ALTURA_nivel_2 82
#define ALTURA_REAL  36
#define DOS 2
#define TRES 3
#define SEIS 6
#define OCHO 8
#define NUEVE 9
#define CINCO 5
#define CUATRO 4
#define DIEZ 10

void Encontrar_enemigos(char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA],int desicion,char Montana_2[MAX_ALTURA_nivel_2][MAX_ANCHURA]);

struct posicion pez[NUEVE];
struct posicion ave[DOS];
struct posicion nube[TRES];
struct posicion alien;
struct posicion personaje;

int main(){
    int contador_secundario=1,desicion=0,control_de_reinicio=0,puntaje=0,contador=0,contador_i,contador_j,revisador_nuve;                     /*funcion principal*/
    char selector='p';
    allegro_init();
    install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,660,570,0,0);
    buffer= create_bitmap(660,570);

    FILE *Mapa_en_Texto;
    FILE *Ranking = fopen("Ranking.txt","r+t");
    SAMPLE *sonido_ciclo;
    SAMPLE *sonido_de_menu;
    SAMPLE *sonido_de_ganar;
    SAMPLE *sonido_de_perdida;
    SAMPLE *sonido_de_menu_secundario;
    SAMPLE *sonido_de_roptura_de_ladrillo;
    SAMPLE *sonido_de_recoleccion_de_fruta;
    sonido_de_recoleccion_de_fruta=load_wav("./musica/FRUTA.wav");
    sonido_de_roptura_de_ladrillo=load_wav("./musica/LADRILLO.wav");
    sonido_de_menu_secundario=load_wav("./musica/MENU.wav");
    sonido_de_perdida=load_wav("./musica/F.wav");
    sonido_de_ganar=load_wav("./musica/W.wav");
    sonido_ciclo=load_wav("./musica/J.wav");
    sonido_de_menu=load_wav("./musica/M.wav");
    play_sample(sonido_de_menu,150,0,1000,3);

    char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA];
    char Montana_de_Respaldo[MAX_ALTURA_nivel_1][MAX_ANCHURA];
    char Montana_2[MAX_ALTURA_nivel_2][MAX_ANCHURA];
    char Montana_de_Respaldo_2[MAX_ALTURA_nivel_2][MAX_ANCHURA];

    BITMAP *Ladrillo_Amarillo;
    BITMAP *Ladrillo_Azul;
    BITMAP *Personaje_Cactus_bmp;
    BITMAP *Personaje_Cactus;
    BITMAP *Enemigo_Pez;
    BITMAP *Enemigo_Pez_bmp;
    BITMAP *Enemigo_Murcielago;
    BITMAP *Enemigo_Murcielago_bmp;
    BITMAP *Aliado_Nave_Espacial_Parte_1;
    BITMAP *Aliado_Nave_Espacial_Parte_1_bmp;
    BITMAP *Aliado_Nave_Espacial_Parte_2;
    BITMAP *Aliado_Nave_Espacial_Parte_2_bmp;
    BITMAP *Aliado_Nave_Espacial_Parte_3;
    BITMAP *Aliado_Nave_Espacial_Parte_3_bmp;
    BITMAP *Fruta;
    BITMAP *Nube_Parte_1;
    BITMAP *Nube_Parte_1_bmp;
    BITMAP *Nube_Parte_2;
    BITMAP *Nube_Parte_2_bmp;
    BITMAP *Nube_Parte_3;
    BITMAP *Nube_Parte_3_bmp;

    Ladrillo_Amarillo=load_bitmap("./bmp/me3.bmp",NULL);
    Ladrillo_Azul=load_bitmap("./bmp/me2.bmp",NULL);
    Personaje_Cactus_bmp=load_bitmap("./bmp/jackcactus2.bmp",NULL);
    Personaje_Cactus=create_bitmap(20,30);
    Enemigo_Pez_bmp=load_bitmap("./bmp/pez2.bmp",NULL);
    Enemigo_Pez=create_bitmap(20,15);
    Enemigo_Murcielago_bmp=load_bitmap("./bmp/ave.bmp",NULL);
    Enemigo_Murcielago=create_bitmap(20,15);
    Aliado_Nave_Espacial_Parte_1_bmp=load_bitmap("./bmp/nave.bmp",NULL);
    Aliado_Nave_Espacial_Parte_1=create_bitmap(20,15);
    Aliado_Nave_Espacial_Parte_2_bmp=load_bitmap("./bmp/nave.bmp",NULL);
    Aliado_Nave_Espacial_Parte_2=create_bitmap(20,15);
    Aliado_Nave_Espacial_Parte_3_bmp=load_bitmap("./bmp/nave.bmp",NULL);
    Aliado_Nave_Espacial_Parte_3=create_bitmap(20,15);
    Fruta=load_bitmap("./bmp/fruta.bmp",NULL);
    Nube_Parte_1_bmp=load_bitmap("./bmp/nube.bmp",NULL);
    Nube_Parte_1=create_bitmap(20,15);
    Nube_Parte_2_bmp=load_bitmap("./bmp/nube.bmp",NULL);
    Nube_Parte_2=create_bitmap(20,15);
    Nube_Parte_3_bmp=load_bitmap("./bmp/nube.bmp",NULL);
    Nube_Parte_3=create_bitmap(20,15);

    clear_to_color(buffer,0x000000);           /*Pantalla de inicio*/
    while(!key[KEY_K] && !key[KEY_L]){
        textout_centre(buffer, font,"presione l para iniciar el nivel 2",300, 215, 0x3BFF14);
        textout_centre(buffer, font,"presione k para iniciar",300, 200, 0x3BFF14);
        textout_centre(buffer, font,"presione ESC para salir",300, 230, 0x3BFF14);
        blit(buffer,screen,0,0,0,0,660,570);
        clear(buffer);
        if(key[KEY_ESC]){
            return 0;
        }
    }
    if(key[KEY_K]){
        Mapa_en_Texto = fopen("./mapas/mapa12.txt","r+t");
        desicion=1;
        Replicador_de_Mapa(Mapa_en_Texto,desicion,Montana,Montana_de_Respaldo);
    }
    if(key[KEY_L]){
        Mapa_en_Texto = fopen("./mapas/mapa2.txt","r+t");
        desicion=2;
    Replicador_de_Mapa_2(Mapa_en_Texto,desicion,Montana_2,Montana_de_Respaldo_2);
    }
    Encontrar_enemigos(Montana,desicion,Montana_2);
    stop_sample(sonido_de_menu);
    play_sample(sonido_de_menu_secundario,200,0,1000,0);

    _entidad Personaje_Cactus_Valores; /*catus*/

    Personaje_Cactus_Valores.Direccion=0;
    Personaje_Cactus_Valores.Posicion_X=personaje.x;
    Personaje_Cactus_Valores.Posicion_Y=personaje.y;
    Personaje_Cactus_Valores.medidor_de_altura=0;
    Personaje_Cactus_Valores.contador=0;
    Personaje_Cactus_Valores.contador_secundario=0;
    Personaje_Cactus_Valores.altura_maxima_de_salto=0;
    Personaje_Cactus_Valores.contador_de_altura=0;
    Personaje_Cactus_Valores.bloque_inferior=0;
    Personaje_Cactus_Valores.impresion=0;
    Personaje_Cactus_Valores.contador_terciario=0;
    Personaje_Cactus_Valores.indicador_de_perdida=0;
    Personaje_Cactus_Valores.puntos=0;
    Personaje_Cactus_Valores.estado_y=2;
    Personaje_Cactus_Valores.estado_x=1;


    struct _entidad Enemigo_Pez_Valores_Numero_[NUEVE];

    for(contador_secundario=0;contador_secundario<NUEVE;contador_secundario++){
        Enemigo_Pez_Valores_Numero_[contador_secundario].Direccion=0;
        Enemigo_Pez_Valores_Numero_[contador_secundario].Posicion_X=pez[contador_secundario].x;
        Enemigo_Pez_Valores_Numero_[contador_secundario].Posicion_Y=pez[contador_secundario].y;
        Enemigo_Pez_Valores_Numero_[contador_secundario].medidor_de_altura=0;
        Enemigo_Pez_Valores_Numero_[contador_secundario].indicador_de_perdida=0;
    }

    struct _entidad Enemigo_Murcielago_Valores[DOS];

    for(contador_secundario=0;contador_secundario<DOS;contador_secundario++){
        Enemigo_Murcielago_Valores[contador_secundario].Direccion=0;
        Enemigo_Murcielago_Valores[contador_secundario].Posicion_X=ave[contador_secundario].x;
        Enemigo_Murcielago_Valores[contador_secundario].Posicion_Y=ave[contador_secundario].y;
        Enemigo_Murcielago_Valores[contador_secundario].medidor_de_altura=0;
        Enemigo_Murcielago_Valores[contador_secundario].indicador_de_perdida=0;
    }

    _entidad_nave Nave_Espacial;    /*ovni*/
    Nave_Espacial.Direccion_Nave=0;
    Nave_Espacial.Posicion_X_Parte_1=alien.x;
    Nave_Espacial.Posicion_X_Parte_2=alien.x+20;
    Nave_Espacial.Posicion_X_Parte_3=alien.x+40;
    Nave_Espacial.Posicion_Y_Parte_1=alien.y;
    Nave_Espacial.Posicion_Y_Parte_2=alien.y;
    Nave_Espacial.Posicion_Y_Parte_3=alien.y;
    Nave_Espacial.ganar=0;

    struct _entidad_nave Nube[TRES];

    for(contador_secundario=0;contador_secundario<TRES;contador_secundario++){
    Nube[contador_secundario].contador=0;
    Nube[contador_secundario].Posicion_X_Parte_1=nube[contador_secundario].x;
    Nube[contador_secundario].Posicion_X_Parte_2=nube[contador_secundario].x+20;
    Nube[contador_secundario].Posicion_X_Parte_3=nube[contador_secundario].x+40;
    Nube[contador_secundario].Posicion_Y_Parte_1=nube[contador_secundario].y;
    Nube[contador_secundario].Posicion_Y_Parte_2=nube[contador_secundario].y;
    Nube[contador_secundario].Posicion_Y_Parte_3=nube[contador_secundario].y;
    }

    switch(desicion){
        case 1:{
            play_sample(sonido_ciclo,200,0,1000,3);
            Personaje_Cactus_Valores.medidor_de_altura=MAX_ALTURA_nivel_1-36;
            Personaje_Cactus_Valores=Ascenso_Montana(Personaje_Cactus_Valores,Montana);

            while(!key[KEY_ESC]){
                if(contador<2000){
                    contador++;
                }
                if(contador==2000){
                    contador=0;
                    puntaje--;
                }
                if(Personaje_Cactus_Valores.puntos>0){
                    puntaje=puntaje+Personaje_Cactus_Valores.puntos;
                    Personaje_Cactus_Valores.puntos=0;
                }
                revisador_nuve=Revisar_subido_nuve(Personaje_Cactus_Valores,Nube);
                Personaje_Cactus_Valores=Personaje_Cactus_Rutina(Personaje_Cactus_Valores,Nube[revisador_nuve],desicion,Montana,Montana_2,sonido_de_roptura_de_ladrillo,sonido_de_recoleccion_de_fruta,Personaje_Cactus_bmp,Personaje_Cactus,revisador_nuve);
                for(contador_secundario=0;contador_secundario<DOS;contador_secundario++){
                    Enemigo_Pez_Valores_Numero_[contador_secundario]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[contador_secundario],Personaje_Cactus_Valores,desicion,Enemigo_Pez,Enemigo_Pez_bmp);
                }
                if(Personaje_Cactus_Valores.medidor_de_altura>16){
                    Enemigo_Murcielago_Valores[0]=Enemigo_Murcielago_Rutina(Enemigo_Murcielago_Valores[0],Personaje_Cactus_Valores,Enemigo_Murcielago_bmp,Enemigo_Murcielago);
                }
                if(Personaje_Cactus_Valores.medidor_de_altura<0){
                    Nave_Espacial=Aliado_Nave_Espacial_Rutina(Nave_Espacial,Personaje_Cactus_Valores,Aliado_Nave_Espacial_Parte_1,Aliado_Nave_Espacial_Parte_1_bmp,Aliado_Nave_Espacial_Parte_2,Aliado_Nave_Espacial_Parte_2_bmp,Aliado_Nave_Espacial_Parte_3,Aliado_Nave_Espacial_Parte_3_bmp);
                }
                if(Personaje_Cactus_Valores.medidor_de_altura<16){
                    for(contador_secundario=0;contador_secundario<TRES;contador_secundario++){
                        Nube[contador_secundario]=Nube_rutina(Nube[contador_secundario],Nube_Parte_1,Nube_Parte_1_bmp,Nube_Parte_2,Nube_Parte_2_bmp,Nube_Parte_3,Nube_Parte_3_bmp);
                    }
                }
                if(Personaje_Cactus_Valores.Posicion_Y<285 && Personaje_Cactus_Valores.medidor_de_altura>-1){
                    Personaje_Cactus_Valores.medidor_de_altura--;
                    Personaje_Cactus_Valores=Ascenso_Montana(Personaje_Cactus_Valores,Montana);
                    Personaje_Cactus_Valores.Posicion_Y +=15;
                    Enemigo_Murcielago_Valores[0].Posicion_Y +=15;
                    for(contador_secundario=0;contador_secundario<DOS;contador_secundario++){
                        Enemigo_Pez_Valores_Numero_[contador_secundario].Posicion_Y +=15;
                    }
                    for(contador_secundario=0;contador_secundario<TRES;contador_secundario++){
                            Nube[contador_secundario].Posicion_Y_Parte_1 +=15;
                            Nube[contador_secundario].Posicion_Y_Parte_2 +=15;
                            Nube[contador_secundario].Posicion_Y_Parte_3 +=15;
                    }
                    Nave_Espacial.Posicion_Y_Parte_1 +=15;
                    Nave_Espacial.Posicion_Y_Parte_2 +=15;
                    Nave_Espacial.Posicion_Y_Parte_3 +=15;
                }
                Dibujar_Montana(Ladrillo_Amarillo,Ladrillo_Azul,Fruta);
                textout_centre(buffer, font,"______",20, 32, 0x3BFF14);
                textout_centre(buffer, font,"______",20, 20, 0x3BFF14);
                textprintf_centre(buffer, font,20, 30, 0x3BFF14,"|%d0|",puntaje);
                Pantalla();
                for(contador_secundario=0;contador_secundario<DOS;contador_secundario++){
                    if(Enemigo_Pez_Valores_Numero_[contador_secundario].indicador_de_perdida==1){
                        control_de_reinicio=1;
                    }
                }
                if(Personaje_Cactus_Valores.Posicion_Y>600 || Enemigo_Murcielago_Valores[0].indicador_de_perdida==1){
                    control_de_reinicio=1;
                }
                if(Nave_Espacial.ganar==1){
                    control_de_reinicio=2;
                }
                if(control_de_reinicio>0){
                    stop_sample(sonido_ciclo);
                    Cambio_de_pantalla(control_de_reinicio,puntaje,Ranking,sonido_de_ganar,sonido_de_perdida,sonido_ciclo,sonido_de_menu_secundario);
                    Personaje_Cactus_Valores.medidor_de_altura=MAX_ALTURA_nivel_1-36;
                    puntaje=0;
                    for(contador_secundario=0;contador_secundario<DOS;contador_secundario++){
                        Enemigo_Pez_Valores_Numero_[contador_secundario].Posicion_X=pez[contador_secundario].x;
                        Enemigo_Pez_Valores_Numero_[contador_secundario].Posicion_Y=pez[contador_secundario].y;
                        Enemigo_Pez_Valores_Numero_[contador_secundario].indicador_de_perdida=0;
                    }
                    Nave_Espacial.Posicion_X_Parte_1=alien.x;
                    Nave_Espacial.Posicion_X_Parte_2=alien.x+20;
                    Nave_Espacial.Posicion_X_Parte_3=alien.x+40;
                    Nave_Espacial.Posicion_Y_Parte_1=alien.y;
                    Nave_Espacial.Posicion_Y_Parte_2=alien.y;
                    Nave_Espacial.Posicion_Y_Parte_3=alien.y;
                    Nave_Espacial.ganar=0;
                    Enemigo_Murcielago_Valores[0].Posicion_X=ave[0].x;
                    Enemigo_Murcielago_Valores[0].Posicion_Y=ave[0].y;
                    Enemigo_Murcielago_Valores[0].indicador_de_perdida=0;
                    for(contador_secundario=0;contador_secundario<TRES;contador_secundario++){
                        Nube[contador_secundario].Posicion_X_Parte_1=nube[contador_secundario].x;
                        Nube[contador_secundario].Posicion_X_Parte_2=nube[contador_secundario].x+20;
                        Nube[contador_secundario].Posicion_X_Parte_3=nube[contador_secundario].x+40;
                        Nube[contador_secundario].Posicion_Y_Parte_1=nube[contador_secundario].y;
                        Nube[contador_secundario].Posicion_Y_Parte_2=nube[contador_secundario].y;
                        Nube[contador_secundario].Posicion_Y_Parte_3=nube[contador_secundario].y;
                    }
                    Personaje_Cactus_Valores.Posicion_X=personaje.x;
                    Personaje_Cactus_Valores.Posicion_Y=personaje.y;
                    Personaje_Cactus_Valores.bloque_inferior=0;
                    control_de_reinicio=0;
                    for(contador_i=0;contador_i<MAX_ALTURA_nivel_1;contador_i++){
                        for(contador_j=0;contador_j<MAX_ANCHURA;contador_j++){
                            Montana[contador_i][contador_j]=Montana_de_Respaldo[contador_i][contador_j];
                        }
                    }
                    stop_sample(sonido_de_perdida);
                    stop_sample(sonido_de_ganar);
                    play_sample(sonido_ciclo,200,0,1000,3);
                    Personaje_Cactus_Valores=Ascenso_Montana(Personaje_Cactus_Valores,Montana);
                }
                clear(buffer);
            }
            break;
        }
        case 2:{
            play_sample(sonido_ciclo,200,0,1000,3);
            Personaje_Cactus_Valores.medidor_de_altura=MAX_ALTURA_nivel_2-36;
            Replicador_de_Mapa_2(Mapa_en_Texto,desicion,Montana_2,Montana_de_Respaldo_2);
            Personaje_Cactus_Valores=Ascenso_Montana_2(Personaje_Cactus_Valores,Montana_2);

            while(!key[KEY_ESC]){
                if(contador<5000){
                    contador++;
                }
                if(contador==5000){
                    contador=0;
                    puntaje--;
                }
                if(Personaje_Cactus_Valores.puntos>0){
                    puntaje=puntaje+Personaje_Cactus_Valores.puntos;
                    Personaje_Cactus_Valores.puntos=0;
                }
                revisador_nuve=Revisar_subido_nuve(Personaje_Cactus_Valores,Nube);
                Personaje_Cactus_Valores=Personaje_Cactus_Rutina(Personaje_Cactus_Valores,Nube[revisador_nuve],desicion,Montana,Montana_2,sonido_de_roptura_de_ladrillo,sonido_de_recoleccion_de_fruta,Personaje_Cactus_bmp,Personaje_Cactus,revisador_nuve);
                if(Personaje_Cactus_Valores.medidor_de_altura>37){
                    Enemigo_Pez_Valores_Numero_[8]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[8],Personaje_Cactus_Valores,desicion,Enemigo_Pez,Enemigo_Pez_bmp);
                }
                if(Personaje_Cactus_Valores.medidor_de_altura>17){
                    Nube[1]=Nube_rutina(Nube[1],Nube_Parte_1,Nube_Parte_1_bmp,Nube_Parte_2,Nube_Parte_2_bmp,Nube_Parte_3,Nube_Parte_3_bmp);
                }
                if(Personaje_Cactus_Valores.medidor_de_altura<36 && Personaje_Cactus_Valores.medidor_de_altura>3){
                    Nube[0]=Nube_rutina(Nube[0],Nube_Parte_1,Nube_Parte_1_bmp,Nube_Parte_2,Nube_Parte_2_bmp,Nube_Parte_3,Nube_Parte_3_bmp);
                }
                if(Personaje_Cactus_Valores.medidor_de_altura<46 && Personaje_Cactus_Valores.medidor_de_altura>41){
                    for(contador_secundario=0;contador_secundario<DOS;contador_secundario++){
                        Enemigo_Murcielago_Valores[contador_secundario]=Enemigo_Murcielago_Rutina(Enemigo_Murcielago_Valores[contador_secundario],Personaje_Cactus_Valores,Enemigo_Murcielago_bmp,Enemigo_Murcielago);
                    }
                }
                if(Personaje_Cactus_Valores.medidor_de_altura>26){
                    for(contador_secundario=6;contador_secundario<OCHO;contador_secundario++){
                        Enemigo_Pez_Valores_Numero_[contador_secundario]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[contador_secundario],Personaje_Cactus_Valores,desicion,Enemigo_Pez,Enemigo_Pez_bmp);
                    }
                }
                if(Personaje_Cactus_Valores.medidor_de_altura>20){
                    for(contador_secundario=3;contador_secundario<SEIS;contador_secundario++){
                        Enemigo_Pez_Valores_Numero_[contador_secundario]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[contador_secundario],Personaje_Cactus_Valores,desicion,Enemigo_Pez,Enemigo_Pez_bmp);
                    }
                }
                if(Personaje_Cactus_Valores.medidor_de_altura>10){
                    for(contador_secundario=1;contador_secundario<TRES;contador_secundario++){
                        Enemigo_Pez_Valores_Numero_[contador_secundario]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[contador_secundario],Personaje_Cactus_Valores,desicion,Enemigo_Pez,Enemigo_Pez_bmp);
                    }
                }
                if(Personaje_Cactus_Valores.medidor_de_altura<37 && Personaje_Cactus_Valores.medidor_de_altura>4){
                    Enemigo_Pez_Valores_Numero_[0]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[0],Personaje_Cactus_Valores,desicion,Enemigo_Pez,Enemigo_Pez_bmp);
                }
                if(Personaje_Cactus_Valores.medidor_de_altura<3){
                    Nave_Espacial=Aliado_Nave_Espacial_Rutina(Nave_Espacial,Personaje_Cactus_Valores,Aliado_Nave_Espacial_Parte_1,Aliado_Nave_Espacial_Parte_1_bmp,Aliado_Nave_Espacial_Parte_2,Aliado_Nave_Espacial_Parte_2_bmp,Aliado_Nave_Espacial_Parte_3,Aliado_Nave_Espacial_Parte_3_bmp);
                    printf("alien_y=%d\n",Nave_Espacial.Posicion_Y_Parte_1);
                }
                if(Personaje_Cactus_Valores.Posicion_Y<285 && Personaje_Cactus_Valores.medidor_de_altura>-1){
                    Personaje_Cactus_Valores.medidor_de_altura--;
                    Personaje_Cactus_Valores=Ascenso_Montana_2(Personaje_Cactus_Valores,Montana_2);
                    Personaje_Cactus_Valores.Posicion_Y=Personaje_Cactus_Valores.Posicion_Y+15;
                    for(contador_secundario=0;contador_secundario<DOS;contador_secundario++){
                        Nube[contador_secundario].Posicion_Y_Parte_1 +=15;
                        Nube[contador_secundario].Posicion_Y_Parte_2 +=15;
                        Nube[contador_secundario].Posicion_Y_Parte_3 +=15;
                        Enemigo_Murcielago_Valores[contador_secundario].Posicion_Y +=15;
                    }
                    for(contador_secundario=0;contador_secundario<NUEVE;contador_secundario++){
                        Enemigo_Pez_Valores_Numero_[contador_secundario].Posicion_Y=Enemigo_Pez_Valores_Numero_[contador_secundario].Posicion_Y+15;
                    }
                    Nave_Espacial.Posicion_Y_Parte_1 +=15;
                    Nave_Espacial.Posicion_Y_Parte_2 +=15;
                    Nave_Espacial.Posicion_Y_Parte_3 +=15;
                }
                Dibujar_Montana(Ladrillo_Amarillo,Ladrillo_Azul,Fruta);
                textout_centre(buffer, font,"______",20, 32, 0x3BFF14);
                textout_centre(buffer, font,"______",20, 20, 0x3BFF14);
                textprintf_centre(buffer, font,20, 30, 0x3BFF14,"|%d0|",puntaje);

                Pantalla();
                for(contador_secundario=0;contador_secundario<NUEVE;contador_secundario++){
                    if(Enemigo_Pez_Valores_Numero_[contador_secundario].indicador_de_perdida==1){
                        control_de_reinicio=1;
                    }
                }
                for(contador_secundario=0;contador_secundario<DOS;contador_secundario++){
                    if(Personaje_Cactus_Valores.Posicion_Y>600 || Enemigo_Murcielago_Valores[contador_secundario].indicador_de_perdida==1){
                        control_de_reinicio=1;
                    }
                }
                if(Nave_Espacial.ganar==1){
                    control_de_reinicio=2;
                }
                if(control_de_reinicio>0){
                    stop_sample(sonido_ciclo);
                    Personaje_Cactus_Valores.medidor_de_altura=MAX_ALTURA_nivel_2-36;
                    Cambio_de_pantalla(control_de_reinicio,puntaje,Ranking,sonido_de_ganar,sonido_de_perdida,sonido_ciclo,sonido_de_menu_secundario);
                    puntaje=0;

                    for(contador_secundario=0;contador_secundario<NUEVE;contador_secundario++){
                        Enemigo_Pez_Valores_Numero_[contador_secundario].Posicion_X=pez[contador_secundario].x;
                        Enemigo_Pez_Valores_Numero_[contador_secundario].Posicion_Y=pez[contador_secundario].y;
                        Enemigo_Pez_Valores_Numero_[contador_secundario].indicador_de_perdida=0;
                    }
                    Nave_Espacial.Posicion_X_Parte_1=alien.x;
                    Nave_Espacial.Posicion_X_Parte_2=alien.x+20;
                    Nave_Espacial.Posicion_X_Parte_3=alien.x+40;
                    Nave_Espacial.Posicion_Y_Parte_1=alien.y;
                    Nave_Espacial.Posicion_Y_Parte_2=alien.y;
                    Nave_Espacial.Posicion_Y_Parte_3=alien.y;
                    Nave_Espacial.ganar=0;
                    for(contador_secundario=0;contador_secundario<DOS;contador_secundario++){
                        Enemigo_Murcielago_Valores[contador_secundario].Posicion_X=ave[contador_secundario].x;
                        Enemigo_Murcielago_Valores[contador_secundario].Posicion_Y=ave[contador_secundario].y;
                        Enemigo_Murcielago_Valores[contador_secundario].indicador_de_perdida=0;
                    }
                    for(contador_secundario=0;contador_secundario<DOS;contador_secundario++){
                        Nube[contador_secundario].Posicion_X_Parte_1=nube[contador_secundario].x;
                        Nube[contador_secundario].Posicion_X_Parte_2=nube[contador_secundario].x+20;
                        Nube[contador_secundario].Posicion_X_Parte_3=nube[contador_secundario].x+40;
                        Nube[contador_secundario].Posicion_Y_Parte_1=nube[contador_secundario].y;
                        Nube[contador_secundario].Posicion_Y_Parte_2=nube[contador_secundario].y;
                        Nube[contador_secundario].Posicion_Y_Parte_3=nube[contador_secundario].y;
                    }
                    Personaje_Cactus_Valores.Posicion_X=personaje.x;
                    Personaje_Cactus_Valores.Posicion_Y=personaje.y;
                    Personaje_Cactus_Valores.bloque_inferior=0;
                    Personaje_Cactus_Valores.indicador_de_perdida=0;
                    control_de_reinicio=0;
                    for(contador_i=0;contador_i<MAX_ALTURA_nivel_2;contador_i++){
                        for(contador_j=0;contador_j<MAX_ANCHURA;contador_j++){
                            Montana_2[contador_i][contador_j]=Montana_de_Respaldo_2[contador_i][contador_j];
                        }
                    }
                    play_sample(sonido_ciclo,200,0,1000,3);
                    Personaje_Cactus_Valores=Ascenso_Montana_2(Personaje_Cactus_Valores,Montana_2);
                }
                clear(buffer);
            }
            break;
        }
    }
    return 0;
}
END_OF_MAIN();

void Encontrar_enemigos(char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA],int desicion,char Montana_2[MAX_ALTURA_nivel_2][MAX_ANCHURA]){
int contador_i,contador_j,contador_pez=0,contador_ave=0,contador_nube=0,redefinidor=0;
    switch(desicion){
        case 1:{
                for(contador_i=0;contador_i<MAX_ALTURA_nivel_1;contador_i++){
        for(contador_j=0;contador_j<MAX_ANCHURA;contador_j++){
            if(Montana[contador_i][contador_j]=='}'){
                pez[contador_pez].x=20*contador_j;
                pez[contador_pez].y=15*contador_i;
                contador_pez++;
            }
            if(Montana[contador_i][contador_j]=='{'){
                ave[contador_ave].x=20*contador_j;
                ave[contador_ave].y=15*contador_i;
                contador_ave++;
            }
            if(Montana[contador_i][contador_j]=='K'){
                alien.x=20*contador_j;
                alien.y=15*contador_i;
            }
            if(Montana[contador_i][contador_j]=='N'){
                nube[contador_nube].x=20*contador_j;
                nube[contador_nube].y=15*contador_i;
                contador_nube++;
            }
            if(Montana[contador_i][contador_j]=='U'){
                personaje.x=20*contador_j;
                personaje.y=15*contador_i;
            }
        }
    }
            redefinidor=MAX_ALTURA_nivel_1-36;
            redefinidor=redefinidor*15;
            break;
        }
        case 2:{
            for(contador_i=0;contador_i<MAX_ALTURA_nivel_2;contador_i++){
        for(contador_j=0;contador_j<MAX_ANCHURA;contador_j++){
            if(Montana_2[contador_i][contador_j]=='P'){
                pez[contador_pez].x=20*contador_j;
                pez[contador_pez].y=15*contador_i;
                contador_pez++;
            }
            if(Montana_2[contador_i][contador_j]=='A'){
                ave[contador_ave].x=20*contador_j;
                ave[contador_ave].y=15*contador_i;
                contador_ave++;
            }
            if(Montana_2[contador_i][contador_j]=='K'){
                alien.x=20*contador_j;
                alien.y=15*contador_i;
            }
            if(Montana_2[contador_i][contador_j]=='+'){
                nube[contador_nube].x=20*contador_j;
                nube[contador_nube].y=15*contador_i;
                contador_nube++;
            }
            if(Montana_2[contador_i][contador_j]=='Q'){
                personaje.x=20*contador_j;
                personaje.y=15*contador_i;
            }
        }
    }
            redefinidor=MAX_ALTURA_nivel_2-36;
            redefinidor=redefinidor*15;
        break;
        }
    }
    for(contador_pez=0;contador_pez<NUEVE;contador_pez++){
        pez[contador_pez].y -=redefinidor;
    }
    for(contador_ave=0;contador_ave<DOS;contador_ave++){
        ave[contador_ave].y -=redefinidor;
    }
    alien.y -=redefinidor;
    for(contador_nube=0;contador_nube<TRES;contador_nube++){
        nube[contador_nube].y -=redefinidor;;
    }
    personaje.y -=redefinidor;
}
