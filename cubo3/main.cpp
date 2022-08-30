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

int main(){
    int Contador_secundario=1,desicion=0,Control_de_Reinicio=0,Puntaje=0,contador=0,contador_i,contador_j;                     /*funcion principal*/
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
        textout_centre(buffer, font,"presione l para iniciar el nivel 2",300, 220, 0x3BFF14);
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
    }
    if(key[KEY_L]){
        Mapa_en_Texto = fopen("./mapas/mapa2.txt","r+t");
        desicion=2;
    }
    stop_sample(sonido_de_menu);
    play_sample(sonido_de_menu_secundario,200,0,1000,0);

    _entidad Personaje_Cactus_Valores; /*catus*/

    Personaje_Cactus_Valores.Direccion=0;
    Personaje_Cactus_Valores.Posicion_X=0;
    Personaje_Cactus_Valores.Posicion_Y=0;
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

    for(Contador_secundario=0;Contador_secundario<NUEVE;Contador_secundario++){
    Enemigo_Pez_Valores_Numero_[Contador_secundario].Direccion=0;
    Enemigo_Pez_Valores_Numero_[Contador_secundario].Posicion_X=500;
    Enemigo_Pez_Valores_Numero_[Contador_secundario].medidor_de_altura=0;
    Enemigo_Pez_Valores_Numero_[Contador_secundario].indicador_de_perdida=0;
    }

    Enemigo_Pez_Valores_Numero_[0].Posicion_Y=105;
    Enemigo_Pez_Valores_Numero_[1].Posicion_Y=210;

    struct _entidad Enemigo_Murcielago_Valores[DOS];

    for(Contador_secundario=0;Contador_secundario<DOS;Contador_secundario++){
    Enemigo_Murcielago_Valores[Contador_secundario].Direccion=0;
    Enemigo_Murcielago_Valores[Contador_secundario].Posicion_X=300;
    Enemigo_Murcielago_Valores[Contador_secundario].Posicion_Y=100;
    Enemigo_Murcielago_Valores[Contador_secundario].medidor_de_altura=0;
    Enemigo_Murcielago_Valores[Contador_secundario].indicador_de_perdida=0;
    }

    _entidad_nave Nave_Espacial;    /*ovni*/
    Nave_Espacial.Direccion_Nave=0;
    Nave_Espacial.Posicion_X_Parte_1=260;
    Nave_Espacial.Posicion_X_Parte_2=280;
    Nave_Espacial.Posicion_X_Parte_3=300;
    Nave_Espacial.Posicion_Y_Parte_1=15;
    Nave_Espacial.Posicion_Y_Parte_2=15;
    Nave_Espacial.Posicion_Y_Parte_3=15;
    Nave_Espacial.ganar=0;

     struct _entidad_nave Nube[TRES];

    Nube[0].contador=0;
    Nube[1].contador=1;
    Nube[2].contador=0;


    Nube[0].Posicion_X_Parte_1=140;
    Nube[0].Posicion_X_Parte_2=160;
    Nube[0].Posicion_X_Parte_3=180;
    Nube[1].Posicion_X_Parte_1=240;
    Nube[1].Posicion_X_Parte_2=260;
    Nube[1].Posicion_X_Parte_3=280;
    Nube[2].Posicion_X_Parte_1=340;
    Nube[2].Posicion_X_Parte_2=360;
    Nube[2].Posicion_X_Parte_3=380;

    switch(desicion){
    case 1:
    {
    play_sample(sonido_ciclo,200,0,1000,3);
    Nube[0].Posicion_Y_Parte_1=150;
    Nube[0].Posicion_Y_Parte_2=150;
    Nube[0].Posicion_Y_Parte_3=150;
    Nube[1].Posicion_Y_Parte_1=105;
    Nube[1].Posicion_Y_Parte_2=105;
    Nube[1].Posicion_Y_Parte_3=105;
    Nube[2].Posicion_Y_Parte_1=0;
    Nube[2].Posicion_Y_Parte_2=0;
    Nube[2].Posicion_Y_Parte_3=0;
    Personaje_Cactus_Valores.medidor_de_altura=MAX_ALTURA_nivel_1-36;
    Replicador_de_Mapa(Mapa_en_Texto,desicion,Montana,Montana_de_Respaldo);
    Personaje_Cactus_Valores=Ascenso_Montana(Personaje_Cactus_Valores,Montana);
    while(!key[KEY_ESC]){
        if(contador<2000){
            contador++;
        }
        if(contador==2000){
            contador=0;
            Puntaje--;
        }
        if(Personaje_Cactus_Valores.puntos>0){
            Puntaje=Puntaje+Personaje_Cactus_Valores.puntos;
            Personaje_Cactus_Valores.puntos=0;
        }
        for(Contador_secundario=0;Contador_secundario<TRES;Contador_secundario++){
        Personaje_Cactus_Valores=Personaje_Cactus_Rutina(Personaje_Cactus_Valores,Nube[Contador_secundario],desicion,Montana,Montana_2,sonido_de_roptura_de_ladrillo,sonido_de_recoleccion_de_fruta);
        }
        for(Contador_secundario=0;Contador_secundario<DOS;Contador_secundario++){
        Enemigo_Pez_Valores_Numero_[Contador_secundario]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[Contador_secundario],Personaje_Cactus_Valores,desicion);
        }
        if(Personaje_Cactus_Valores.medidor_de_altura>16){
        Enemigo_Murcielago_Valores[0]=Enemigo_Murcielago_Rutina(Enemigo_Murcielago_Valores[0],Personaje_Cactus_Valores);
        }
        if(Personaje_Cactus_Valores.medidor_de_altura<3){
        Nave_Espacial=Aliado_Nave_Espacial_Rutina(Nave_Espacial,Personaje_Cactus_Valores);
        }
        if(Personaje_Cactus_Valores.medidor_de_altura<16){
        Nube[0]=Nube_rutina(Nube[0]);
        Nube[1]=Nube_rutina(Nube[1]);
        if(Personaje_Cactus_Valores.medidor_de_altura<14){
        Nube[2]=Nube_rutina(Nube[2]);
        }
        }
        if(Personaje_Cactus_Valores.Posicion_Y<285 && Personaje_Cactus_Valores.medidor_de_altura>-1){
        Personaje_Cactus_Valores.medidor_de_altura--;
        Personaje_Cactus_Valores=Ascenso_Montana(Personaje_Cactus_Valores,Montana);
        Personaje_Cactus_Valores.Posicion_Y=Personaje_Cactus_Valores.Posicion_Y+15;
        Enemigo_Murcielago_Valores[0].Posicion_Y=Enemigo_Murcielago_Valores[0].Posicion_Y+15;
        for(Contador_secundario=0;Contador_secundario<DOS;Contador_secundario++){
        Enemigo_Pez_Valores_Numero_[Contador_secundario].Posicion_Y=Enemigo_Pez_Valores_Numero_[Contador_secundario].Posicion_Y+15;
        }
        for(Contador_secundario=0;Contador_secundario<DOS;Contador_secundario++){
        if(Personaje_Cactus_Valores.medidor_de_altura<16){
        Nube[Contador_secundario].Posicion_Y_Parte_1 +=15;
        Nube[Contador_secundario].Posicion_Y_Parte_2 +=15;
        Nube[Contador_secundario].Posicion_Y_Parte_3 +=15;
        }
        }
        if(Personaje_Cactus_Valores.medidor_de_altura<14){
        Nube[2].Posicion_Y_Parte_1 +=15;
        Nube[2].Posicion_Y_Parte_2 +=15;
        Nube[2].Posicion_Y_Parte_3 +=15;
        }
        }
        Dibujar_Montana();
        textout_centre(buffer, font,"______",20, 32, 0x3BFF14);
        textout_centre(buffer, font,"______",20, 20, 0x3BFF14);
        textprintf_centre(buffer, font,20, 30, 0x3BFF14,"|%d0|",Puntaje);
        Pantalla();
        for(Contador_secundario=0;Contador_secundario<DOS;Contador_secundario++){
        if(Enemigo_Pez_Valores_Numero_[Contador_secundario].indicador_de_perdida==1){
        Control_de_Reinicio=1;
        }
        }
        if(Personaje_Cactus_Valores.Posicion_Y>600 || Enemigo_Murcielago_Valores[0].indicador_de_perdida==1){
            Control_de_Reinicio=1;
        }
        if(Nave_Espacial.ganar==1){
            Control_de_Reinicio=2;
        }
           if(Control_de_Reinicio>0){
            stop_sample(sonido_ciclo);
            Todas_las_Posiciones(Control_de_Reinicio,Puntaje,Ranking,sonido_de_ganar,sonido_de_perdida,sonido_ciclo,sonido_de_menu_secundario);
            Personaje_Cactus_Valores.indicador_de_perdida=0;
            Enemigo_Murcielago_Valores[0].indicador_de_perdida=0;
                        Control_de_Reinicio=0;
            Personaje_Cactus_Valores.Posicion_X=100;
            Personaje_Cactus_Valores.Posicion_Y=495;
            Personaje_Cactus_Valores.medidor_de_altura=MAX_ALTURA_nivel_1-36;
            for(Contador_secundario=0;Contador_secundario<DOS;Contador_secundario++){
                Enemigo_Pez_Valores_Numero_[Contador_secundario].Posicion_X=300;
                Enemigo_Pez_Valores_Numero_[Contador_secundario].Posicion_Y=Contador_secundario*105;
                Enemigo_Pez_Valores_Numero_[Contador_secundario].indicador_de_perdida=0;
            }
                Enemigo_Pez_Valores_Numero_[0].Posicion_Y=300;
            Personaje_Cactus_Valores.medidor_de_altura=MAX_ALTURA_nivel_1-36;
            Enemigo_Murcielago_Valores[0].Posicion_X=300;
            Enemigo_Murcielago_Valores[0].Posicion_Y=100;
            Nave_Espacial.Posicion_X_Parte_1=140;
            Nave_Espacial.Posicion_X_Parte_2=160;
            Nave_Espacial.Posicion_X_Parte_3=180;
            Nave_Espacial.Posicion_Y_Parte_1=15;
            Nave_Espacial.Posicion_Y_Parte_2=15;
            Nave_Espacial.Posicion_Y_Parte_3=15;
            Nube[0].Posicion_Y_Parte_1=150;
            Nube[0].Posicion_Y_Parte_2=150;
            Nube[0].Posicion_Y_Parte_3=150;
            Nube[1].Posicion_Y_Parte_1=105;
            Nube[1].Posicion_Y_Parte_2=105;
            Nube[1].Posicion_Y_Parte_3=105;
            Nube[2].Posicion_Y_Parte_1=0;
            Nube[2].Posicion_Y_Parte_2=0;
            Nube[2].Posicion_Y_Parte_3=0;
            Puntaje=0;
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
    Nube[0].Posicion_Y_Parte_1=105;
    Nube[0].Posicion_Y_Parte_2=105;
    Nube[0].Posicion_Y_Parte_3=105;
    Nube[0].Posicion_X_Parte_1=140;
    Nube[0].Posicion_X_Parte_2=160;
    Nube[0].Posicion_X_Parte_3=180;
    Nube[1].Posicion_Y_Parte_1=-150;
    Nube[1].Posicion_Y_Parte_2=-150;
    Nube[1].Posicion_Y_Parte_3=-150;
    Nube[1].Posicion_X_Parte_1=320;
    Nube[1].Posicion_X_Parte_2=340;
    Nube[1].Posicion_X_Parte_3=360;
    Enemigo_Murcielago_Valores[0].Posicion_Y=260;
    Enemigo_Murcielago_Valores[0].Posicion_X=120;
    Enemigo_Murcielago_Valores[1].Posicion_Y=300;
    Enemigo_Murcielago_Valores[1].Posicion_X=105;
    Enemigo_Pez_Valores_Numero_[0].Posicion_Y=390;
    Enemigo_Pez_Valores_Numero_[0].Posicion_X=400;
    Enemigo_Pez_Valores_Numero_[1].Posicion_Y=210;
    Enemigo_Pez_Valores_Numero_[1].Posicion_X=420;
    Enemigo_Pez_Valores_Numero_[2].Posicion_Y=210;
    Enemigo_Pez_Valores_Numero_[2].Posicion_X=600;
    Enemigo_Pez_Valores_Numero_[3].Posicion_Y=135;
    Enemigo_Pez_Valores_Numero_[3].Posicion_X=100;
    Enemigo_Pez_Valores_Numero_[4].Posicion_Y=135;
    Enemigo_Pez_Valores_Numero_[4].Posicion_X=200;
    Enemigo_Pez_Valores_Numero_[5].Posicion_Y=135;
    Enemigo_Pez_Valores_Numero_[5].Posicion_X=400;
    Enemigo_Pez_Valores_Numero_[6].Posicion_Y=30;
    Enemigo_Pez_Valores_Numero_[6].Posicion_X=200;
    Enemigo_Pez_Valores_Numero_[7].Posicion_Y=30;
    Enemigo_Pez_Valores_Numero_[7].Posicion_X=440;
    Enemigo_Pez_Valores_Numero_[8].Posicion_Y=-105;
    Enemigo_Pez_Valores_Numero_[8].Posicion_X=340;

    Personaje_Cactus_Valores.medidor_de_altura=MAX_ALTURA_nivel_2-36;
    Replicador_de_Mapa_2(Mapa_en_Texto,desicion,Montana_2,Montana_de_Respaldo_2);
    Personaje_Cactus_Valores=Ascenso_Montana_2(Personaje_Cactus_Valores,Montana_2);
    while(!key[KEY_ESC]){
        if(contador<5000){
            contador++;
        }
        if(contador==5000){
            contador=0;
            Puntaje--;
        }
        if(Personaje_Cactus_Valores.puntos>0){
            Puntaje=Puntaje+Personaje_Cactus_Valores.puntos;
            Personaje_Cactus_Valores.puntos=0;
        }
        for(Contador_secundario=0;Contador_secundario<TRES;Contador_secundario++){
        Personaje_Cactus_Valores=Personaje_Cactus_Rutina(Personaje_Cactus_Valores,Nube[Contador_secundario],desicion,Montana,Montana_2,sonido_de_roptura_de_ladrillo,sonido_de_recoleccion_de_fruta);
        }
        if(Personaje_Cactus_Valores.medidor_de_altura>37){
            Enemigo_Pez_Valores_Numero_[0]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[0],Personaje_Cactus_Valores,desicion);
        }
        if(Personaje_Cactus_Valores.medidor_de_altura>17){
        Nube[0]=Nube_rutina(Nube[0]);
        }
        if(Personaje_Cactus_Valores.medidor_de_altura<36 && Personaje_Cactus_Valores.medidor_de_altura>3){
        Nube[1]=Nube_rutina(Nube[1]);
        }
        if(Personaje_Cactus_Valores.medidor_de_altura<46 && Personaje_Cactus_Valores.medidor_de_altura>41){
        for(Contador_secundario=0;Contador_secundario<DOS;Contador_secundario++){
        Enemigo_Murcielago_Valores[Contador_secundario]=Enemigo_Murcielago_Rutina(Enemigo_Murcielago_Valores[Contador_secundario],Personaje_Cactus_Valores);
        }
        }
        if(Personaje_Cactus_Valores.medidor_de_altura>26){
        for(Contador_secundario=1;Contador_secundario<TRES;Contador_secundario++){
        Enemigo_Pez_Valores_Numero_[Contador_secundario]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[Contador_secundario],Personaje_Cactus_Valores,desicion);
        }
        }
        if(Personaje_Cactus_Valores.medidor_de_altura>20){
        for(Contador_secundario=3;Contador_secundario<SEIS;Contador_secundario++){
        Enemigo_Pez_Valores_Numero_[Contador_secundario]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[Contador_secundario],Personaje_Cactus_Valores,desicion);
        }
        }
        if(Personaje_Cactus_Valores.medidor_de_altura>10){
        for(Contador_secundario=6;Contador_secundario<OCHO;Contador_secundario++){
        Enemigo_Pez_Valores_Numero_[Contador_secundario]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[Contador_secundario],Personaje_Cactus_Valores,desicion);
        }
        }
        if(Personaje_Cactus_Valores.medidor_de_altura<37 && Personaje_Cactus_Valores.medidor_de_altura>4){
        Enemigo_Pez_Valores_Numero_[8]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[8],Personaje_Cactus_Valores,desicion);
        }
        if(Personaje_Cactus_Valores.medidor_de_altura<3){
        Nave_Espacial=Aliado_Nave_Espacial_Rutina(Nave_Espacial,Personaje_Cactus_Valores);
        }
        if(Personaje_Cactus_Valores.Posicion_Y<285 && Personaje_Cactus_Valores.medidor_de_altura>-1){
        Personaje_Cactus_Valores.medidor_de_altura--;
        Personaje_Cactus_Valores=Ascenso_Montana_2(Personaje_Cactus_Valores,Montana_2);
        Personaje_Cactus_Valores.Posicion_Y=Personaje_Cactus_Valores.Posicion_Y+15;
        for(Contador_secundario=0;Contador_secundario<DOS;Contador_secundario++){
        Nube[Contador_secundario].Posicion_Y_Parte_1 +=15;
        Nube[Contador_secundario].Posicion_Y_Parte_2 +=15;
        Nube[Contador_secundario].Posicion_Y_Parte_3 +=15;
        Enemigo_Murcielago_Valores[Contador_secundario].Posicion_Y +=15;
        }
        for(Contador_secundario=0;Contador_secundario<NUEVE;Contador_secundario++){
        Enemigo_Pez_Valores_Numero_[Contador_secundario].Posicion_Y=Enemigo_Pez_Valores_Numero_[Contador_secundario].Posicion_Y+15;
        }
        }
        Dibujar_Montana();
        textout_centre(buffer, font,"______",20, 32, 0x3BFF14);
        textout_centre(buffer, font,"______",20, 20, 0x3BFF14);
        textprintf_centre(buffer, font,20, 30, 0x3BFF14,"|%d0|",Puntaje);

        Pantalla();
        for(Contador_secundario=0;Contador_secundario<NUEVE;Contador_secundario++){
        if(Enemigo_Pez_Valores_Numero_[Contador_secundario].indicador_de_perdida==1){
        Control_de_Reinicio=1;
        }
        }
        for(Contador_secundario=0;Contador_secundario<DOS;Contador_secundario++){
        if(Personaje_Cactus_Valores.Posicion_Y>600 || Enemigo_Murcielago_Valores[Contador_secundario].indicador_de_perdida==1){
            Control_de_Reinicio=1;
        }
        }
        if(Nave_Espacial.ganar==1){
            Control_de_Reinicio=2;
        }
            if(Control_de_Reinicio>0){
                    stop_sample(sonido_ciclo);
            Todas_las_Posiciones(Control_de_Reinicio,Puntaje,Ranking,sonido_de_ganar,sonido_de_perdida,sonido_ciclo,sonido_de_menu_secundario);
    Nube[0].Posicion_Y_Parte_1=105;
    Nube[0].Posicion_Y_Parte_2=105;
    Nube[0].Posicion_Y_Parte_3=105;
    Nube[0].Posicion_X_Parte_1=140;
    Nube[0].Posicion_X_Parte_2=160;
    Nube[0].Posicion_X_Parte_3=180;
    Nube[1].Posicion_Y_Parte_1=-150;
    Nube[1].Posicion_Y_Parte_2=-150;
    Nube[1].Posicion_Y_Parte_3=-150;
    Nube[1].Posicion_X_Parte_1=320;
    Nube[1].Posicion_X_Parte_2=340;
    Nube[1].Posicion_X_Parte_3=360;
    Enemigo_Murcielago_Valores[0].Posicion_Y=260;
    Enemigo_Murcielago_Valores[0].Posicion_X=120;
    Enemigo_Murcielago_Valores[1].Posicion_Y=300;
    Enemigo_Murcielago_Valores[1].Posicion_X=105;
    Enemigo_Pez_Valores_Numero_[0].Posicion_Y=390;
    Enemigo_Pez_Valores_Numero_[0].Posicion_X=400;
    Enemigo_Pez_Valores_Numero_[1].Posicion_Y=210;
    Enemigo_Pez_Valores_Numero_[1].Posicion_X=420;
    Enemigo_Pez_Valores_Numero_[2].Posicion_Y=210;
    Enemigo_Pez_Valores_Numero_[2].Posicion_X=600;
    Enemigo_Pez_Valores_Numero_[3].Posicion_Y=135;
    Enemigo_Pez_Valores_Numero_[3].Posicion_X=100;
    Enemigo_Pez_Valores_Numero_[4].Posicion_Y=135;
    Enemigo_Pez_Valores_Numero_[4].Posicion_X=200;
    Enemigo_Pez_Valores_Numero_[5].Posicion_Y=135;
    Enemigo_Pez_Valores_Numero_[5].Posicion_X=400;
    Enemigo_Pez_Valores_Numero_[6].Posicion_Y=30;
    Enemigo_Pez_Valores_Numero_[6].Posicion_X=200;
    Enemigo_Pez_Valores_Numero_[7].Posicion_Y=30;
    Enemigo_Pez_Valores_Numero_[7].Posicion_X=440;
    Enemigo_Pez_Valores_Numero_[8].Posicion_Y=-105;
    Enemigo_Pez_Valores_Numero_[8].Posicion_X=340;
    Personaje_Cactus_Valores.Posicion_X=100;
    Personaje_Cactus_Valores.Posicion_Y=495;
    Puntaje=0;
            Control_de_Reinicio=0;
            for(Contador_secundario=0;Contador_secundario<DOS;Contador_secundario++){
                Enemigo_Murcielago_Valores[Contador_secundario].indicador_de_perdida=0;
            }
            for(Contador_secundario=0;Contador_secundario<NUEVE;Contador_secundario++){
                Enemigo_Pez_Valores_Numero_[Contador_secundario].indicador_de_perdida=0;
            }
            Personaje_Cactus_Valores.medidor_de_altura=MAX_ALTURA_nivel_2-36;
            Personaje_Cactus_Valores.indicador_de_perdida=0;
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
