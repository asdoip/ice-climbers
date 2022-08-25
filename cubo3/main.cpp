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

int main(){
    int h=1,desicion=0,Control_de_Reinicio=0,Puntaje=0,contador=0;                     /*funcion principal*/
    char selector='p';
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,660,570,0,0);
    buffer= create_bitmap(660,570);

    FILE *Mapa_en_Texto;
    FILE *Ranking = fopen("Ranking.txt","r+t");

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
        textout_centre(buffer, font,"presione l para iniciar el nivel 2",300, 160, 0x3BFF14);
        textout_centre(buffer, font,"presione k para iniciar",300, 100, 0x3BFF14);
        textout_centre(buffer, font,"presione ESC para salir",300, 130, 0x3BFF14);
        blit(buffer,screen,0,0,0,0,660,570);
        clear(buffer);
        if(key[KEY_ESC]){
            break;
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
    _entidad Personaje_Cactus_Valores; /*catus*/

    Personaje_Cactus_Valores.Direccion=0;
    Personaje_Cactus_Valores.Posicion_X=0;
    Personaje_Cactus_Valores.Posicion_Y=0;
    Personaje_Cactus_Valores.m=0;
    Personaje_Cactus_Valores.u=0;
    Personaje_Cactus_Valores.b=0;
    Personaje_Cactus_Valores.c=0;
    Personaje_Cactus_Valores.t=0;
    Personaje_Cactus_Valores.l=0;
    Personaje_Cactus_Valores.imp=0;
    Personaje_Cactus_Valores.cont=0;
    Personaje_Cactus_Valores.r=0;
    Personaje_Cactus_Valores.f=0;
    Personaje_Cactus_Valores.perdida=0;
    Personaje_Cactus_Valores.Punt=0;


   struct _entidad Enemigo_Pez_Valores_Numero_[NUEVE];

    for(h=0;h<NUEVE;h++){
    Enemigo_Pez_Valores_Numero_[h].Direccion=0;
    Enemigo_Pez_Valores_Numero_[h].Posicion_X=500;
    Enemigo_Pez_Valores_Numero_[h].m=0;
    Enemigo_Pez_Valores_Numero_[h].perdida=0;
    }

    Enemigo_Pez_Valores_Numero_[0].Posicion_Y=105;
    Enemigo_Pez_Valores_Numero_[1].Posicion_Y=210;

    struct _entidad Enemigo_Murcielago_Valores[DOS];

    for(h=0;h<DOS;h++){
    Enemigo_Murcielago_Valores[h].Direccion=0;
    Enemigo_Murcielago_Valores[h].Posicion_X=300;
    Enemigo_Murcielago_Valores[h].Posicion_Y=100;
    Enemigo_Murcielago_Valores[h].m=0;
    Enemigo_Murcielago_Valores[h].perdida=0;
    }

    _entidad_nave Nave_Espacial;    /*ovni*/
    Nave_Espacial.Direccion_Nave=0;
    Nave_Espacial.Posicion_X_Parte_1=240;
    Nave_Espacial.Posicion_X_Parte_2=260;
    Nave_Espacial.Posicion_X_Parte_3=280;
    Nave_Espacial.Posicion_Y_Parte_1=15;
    Nave_Espacial.Posicion_Y_Parte_2=15;
    Nave_Espacial.Posicion_Y_Parte_3=15;
    Nave_Espacial.ganar=0;

     struct _entidad_nave Nube[TRES];

    Nube[0].m=0;
    Nube[1].m=1;
    Nube[2].m=0;


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
    Nube[0].Posicion_Y_Parte_1=150;
    Nube[0].Posicion_Y_Parte_2=150;
    Nube[0].Posicion_Y_Parte_3=150;
    Nube[1].Posicion_Y_Parte_1=105;
    Nube[1].Posicion_Y_Parte_2=105;
    Nube[1].Posicion_Y_Parte_3=105;
    Nube[2].Posicion_Y_Parte_1=0;
    Nube[2].Posicion_Y_Parte_2=0;
    Nube[2].Posicion_Y_Parte_3=0;
    Personaje_Cactus_Valores.m=MAX_ALTURA_nivel_1-36;
    Replicador_de_Mapa(Mapa_en_Texto,desicion,Montana,Montana_de_Respaldo);
    Personaje_Cactus_Valores=Ascenso_Montana(Personaje_Cactus_Valores,Montana);
    while(!key[KEY_ESC]){
        if(contador<1000){
            contador++;
        }
        if(contador==1000){
            contador=0;
            Puntaje--;
        }
        if(Personaje_Cactus_Valores.Punt>0){
            Puntaje=Puntaje+Personaje_Cactus_Valores.Punt;
            Personaje_Cactus_Valores.Punt=0;
        }
        for(h=0;h<TRES;h++){
        Personaje_Cactus_Valores=Personaje_Cactus_Rutina(Personaje_Cactus_Valores,Nube[h],desicion,Montana);
        }
        for(h=0;h<DOS;h++){
        Enemigo_Pez_Valores_Numero_[h]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[h],Personaje_Cactus_Valores,desicion);
        }
        if(Personaje_Cactus_Valores.m>16){
        Enemigo_Murcielago_Valores[0]=Enemigo_Murcielago_Rutina(Enemigo_Murcielago_Valores[0],Personaje_Cactus_Valores);
        }
        if(Personaje_Cactus_Valores.m<3){
        Nave_Espacial=Aliado_Nave_Espacial_Rutina(Nave_Espacial,Personaje_Cactus_Valores);
        }
        if(Personaje_Cactus_Valores.m<16){
        Nube[0]=Nube_rutina(Nube[0]);
        Nube[1]=Nube_rutina(Nube[1]);
        if(Personaje_Cactus_Valores.m<14){
        Nube[2]=Nube_rutina(Nube[2]);
        }
        }
        if(Personaje_Cactus_Valores.Posicion_Y<285 && Personaje_Cactus_Valores.m>-1){
        Personaje_Cactus_Valores.m--;
        Personaje_Cactus_Valores=Ascenso_Montana(Personaje_Cactus_Valores,Montana);
        Personaje_Cactus_Valores.Posicion_Y=Personaje_Cactus_Valores.Posicion_Y+15;
        Enemigo_Murcielago_Valores[0].Posicion_Y=Enemigo_Murcielago_Valores[0].Posicion_Y+15;
        for(h=0;h<DOS;h++){
        Enemigo_Pez_Valores_Numero_[h].Posicion_Y=Enemigo_Pez_Valores_Numero_[h].Posicion_Y+15;
        }
        for(h=0;h<DOS;h++){
        if(Personaje_Cactus_Valores.m<16){
        Nube[h].Posicion_Y_Parte_1 +=15;
        Nube[h].Posicion_Y_Parte_2 +=15;
        Nube[h].Posicion_Y_Parte_3 +=15;
        }
        }
        if(Personaje_Cactus_Valores.m<14){
        Nube[2].Posicion_Y_Parte_1 +=15;
        Nube[2].Posicion_Y_Parte_2 +=15;
        Nube[2].Posicion_Y_Parte_3 +=15;
        }
        }
        Dibujar_Montana();
        textout_centre(buffer, font,"______",20, 32, 0x3BFF14);
        textout_centre(buffer, font,"______",20, 20, 0x3BFF14);
        textprintf_centre(buffer, font,20, 30, 0x3BFF14,"|%d|",Puntaje);
        Pantalla();
        for(h=0;h<DOS;h++){
        if(Enemigo_Pez_Valores_Numero_[h].perdida==1){
        Control_de_Reinicio=1;
        }
        }
        if(Personaje_Cactus_Valores.Posicion_Y>600 || Enemigo_Murcielago_Valores[0].perdida==1){
            Control_de_Reinicio=1;
        }
        if(Nave_Espacial.ganar==1){
            Control_de_Reinicio=2;
        }
           if(Control_de_Reinicio>0){
            Todas_las_Posiciones(Control_de_Reinicio,Puntaje,Ranking);
            Personaje_Cactus_Valores.perdida=0;
            Enemigo_Murcielago_Valores[0].perdida=0;
                        Control_de_Reinicio=0;
            Personaje_Cactus_Valores.Posicion_X=100;
            Personaje_Cactus_Valores.Posicion_Y=495;
            Personaje_Cactus_Valores.m=MAX_ALTURA_nivel_1-36;
            for(h=0;h<DOS;h++){
                Enemigo_Pez_Valores_Numero_[h].Posicion_X=300;
                Enemigo_Pez_Valores_Numero_[h].Posicion_Y=h*105;
                Enemigo_Pez_Valores_Numero_[h].perdida=0;
            }
                Enemigo_Pez_Valores_Numero_[0].Posicion_Y=300;
            Personaje_Cactus_Valores.m=MAX_ALTURA_nivel_1-36;
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
        for(int i=0;i<MAX_ALTURA_nivel_1;i++){
        for(int j=0;j<MAX_ANCHURA;j++){
            Montana[i][j]=Montana_de_Respaldo[i][j];
        }
        }
            Personaje_Cactus_Valores=Ascenso_Montana(Personaje_Cactus_Valores,Montana);
        }
        clear(buffer);
        }
    break;
    }
    case 2:{
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

    Personaje_Cactus_Valores.m=MAX_ALTURA_nivel_2-36;
    Replicador_de_Mapa_2(Mapa_en_Texto,desicion,Montana_2,Montana_de_Respaldo_2);
    Personaje_Cactus_Valores=Ascenso_Montana_2(Personaje_Cactus_Valores,Montana_2);
    while(!key[KEY_ESC]){
        if(contador<1000){
            contador++;
        }
        if(contador==1000){
            contador=0;
            Puntaje--;
        }
        if(Personaje_Cactus_Valores.Punt>0){
            Puntaje=Puntaje+Personaje_Cactus_Valores.Punt;
            Personaje_Cactus_Valores.Punt=0;
        }
        for(h=0;h<DOS;h++){
        Personaje_Cactus_Valores=Personaje_Cactus_Rutina_2(Personaje_Cactus_Valores,Nube[h],desicion,Montana_2);
        }
        if(Personaje_Cactus_Valores.m>37){
            Enemigo_Pez_Valores_Numero_[0]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[0],Personaje_Cactus_Valores,desicion);
        }
        if(Personaje_Cactus_Valores.m>17){
        Nube[0]=Nube_rutina(Nube[0]);
        }
        if(Personaje_Cactus_Valores.m<36 && Personaje_Cactus_Valores.m>3){
        Nube[1]=Nube_rutina(Nube[1]);
        }
        if(Personaje_Cactus_Valores.m<46 && Personaje_Cactus_Valores.m>41){
        for(h=0;h<DOS;h++){
        Enemigo_Murcielago_Valores[h]=Enemigo_Murcielago_Rutina(Enemigo_Murcielago_Valores[h],Personaje_Cactus_Valores);
        }
        }
        if(Personaje_Cactus_Valores.m>26){
        for(h=1;h<TRES;h++){
        Enemigo_Pez_Valores_Numero_[h]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[h],Personaje_Cactus_Valores,desicion);
        }
        }
        if(Personaje_Cactus_Valores.m>20){
        for(h=3;h<SEIS;h++){
        Enemigo_Pez_Valores_Numero_[h]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[h],Personaje_Cactus_Valores,desicion);
        }
        }
        if(Personaje_Cactus_Valores.m>10){
        for(h=6;h<OCHO;h++){
        Enemigo_Pez_Valores_Numero_[h]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[h],Personaje_Cactus_Valores,desicion);
        }
        }
        if(Personaje_Cactus_Valores.m<37 && Personaje_Cactus_Valores.m>4){
        Enemigo_Pez_Valores_Numero_[8]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[8],Personaje_Cactus_Valores,desicion);
        }
        if(Personaje_Cactus_Valores.m<3){
        Nave_Espacial=Aliado_Nave_Espacial_Rutina(Nave_Espacial,Personaje_Cactus_Valores);
        }
        if(Personaje_Cactus_Valores.Posicion_Y<285 && Personaje_Cactus_Valores.m>-1){
        Personaje_Cactus_Valores.m--;
        Personaje_Cactus_Valores=Ascenso_Montana_2(Personaje_Cactus_Valores,Montana_2);
        Personaje_Cactus_Valores.Posicion_Y=Personaje_Cactus_Valores.Posicion_Y+15;
        for(h=0;h<DOS;h++){
        Nube[h].Posicion_Y_Parte_1 +=15;
        Nube[h].Posicion_Y_Parte_2 +=15;
        Nube[h].Posicion_Y_Parte_3 +=15;
        Enemigo_Murcielago_Valores[h].Posicion_Y +=15;
        }
        for(h=0;h<NUEVE;h++){
        Enemigo_Pez_Valores_Numero_[h].Posicion_Y=Enemigo_Pez_Valores_Numero_[h].Posicion_Y+15;
        }
        }
        Dibujar_Montana();
        textout_centre(buffer, font,"______",20, 32, 0x3BFF14);
        textout_centre(buffer, font,"______",20, 20, 0x3BFF14);
        textprintf_centre(buffer, font,20, 30, 0x3BFF14,"|%d|",Puntaje);

        Pantalla();
        for(h=0;h<NUEVE;h++){
        if(Enemigo_Pez_Valores_Numero_[h].perdida==1){
        Control_de_Reinicio=1;
        }
        }
        for(h=0;h<DOS;h++){
        if(Personaje_Cactus_Valores.Posicion_Y>600 || Enemigo_Murcielago_Valores[h].perdida==1){
            Control_de_Reinicio=1;
        }
        }
        if(Nave_Espacial.ganar==1){
            Control_de_Reinicio=2;
        }
            if(Control_de_Reinicio>0){
            Todas_las_Posiciones(Control_de_Reinicio,Puntaje,Ranking);
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
            for(h=0;h<DOS;h++){
                Enemigo_Murcielago_Valores[h].perdida=0;
            }
            for(h=0;h<NUEVE;h++){
                Enemigo_Pez_Valores_Numero_[h].perdida=0;
            }
            Personaje_Cactus_Valores.m=MAX_ALTURA_nivel_2-36;
            Personaje_Cactus_Valores.perdida=0;
        for(int i=0;i<MAX_ALTURA_nivel_2;i++){
        for(int j=0;j<MAX_ANCHURA;j++){
            Montana_2[i][j]=Montana_de_Respaldo_2[i][j];
        }
        }
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
