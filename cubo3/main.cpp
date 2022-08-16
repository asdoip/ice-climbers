#include <stdio.h>
#include <allegro.h>
#include <time.h>
#include "mov.h"

#define MAX_ALTURA  70
#define MAX_ANCHURA  34
#define ALTURA_REAL  36
#define DOS 2
#define TRES 3


int main(){
    int h=1;                     /*funcion principal*/
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,660,570,0,0);
    buffer= create_bitmap(660,570);
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
    while(!key[KEY_K]){
    textout_centre(buffer, font,"presione k para iniciar",300, 100, 0x3BFF14);
    textout_centre(buffer, font,"presione ESC para salir",300, 130, 0x3BFF14);
    blit(buffer,screen,0,0,0,0,660,570);
    clear(buffer);
    if(key[KEY_ESC]){
    return 0;
    }
    }
    _entidad Personaje_Cactus_Valores; /*catus*/
    Personaje_Cactus_Valores.Direccion=0;
    Personaje_Cactus_Valores.Posicion_X=200;
    Personaje_Cactus_Valores.Posicion_Y=495;
    Personaje_Cactus_Valores.m=33;
    Personaje_Cactus_Valores.u=0;
    Personaje_Cactus_Valores.b=0;
    Personaje_Cactus_Valores.c=0;
    Personaje_Cactus_Valores.t=0;
    Personaje_Cactus_Valores.l=2;
    Personaje_Cactus_Valores.imp=0;
    Personaje_Cactus_Valores.cont=0;
    Personaje_Cactus_Valores.r=0;
    Personaje_Cactus_Valores.f=0;


   struct _entidad Enemigo_Pez_Valores_Numero_[DOS];

    for(h=0;h<DOS;h++){
    Enemigo_Pez_Valores_Numero_[h].Direccion=0;
    Enemigo_Pez_Valores_Numero_[h].Posicion_X=500;
    Enemigo_Pez_Valores_Numero_[h].m=0;
    }

    Enemigo_Pez_Valores_Numero_[0].Posicion_Y=105;
    Enemigo_Pez_Valores_Numero_[1].Posicion_Y=210;

    _entidad Enemigo_Murcielago_Valores;     /*ave*/
    Enemigo_Murcielago_Valores.Direccion=0;
    Enemigo_Murcielago_Valores.Posicion_X=300;
    Enemigo_Murcielago_Valores.Posicion_Y=100;
    Enemigo_Murcielago_Valores.m=0;


    _entidad_nave Nave_Espacial;    /*ovni*/
    Nave_Espacial.Direccion_Nave=0;
    Nave_Espacial.Posicion_X_Parte_1=240;
    Nave_Espacial.Posicion_X_Parte_2=260;
    Nave_Espacial.Posicion_X_Parte_3=280;
    Nave_Espacial.Posicion_Y_Parte_1=15;
    Nave_Espacial.Posicion_Y_Parte_2=15;
    Nave_Espacial.Posicion_Y_Parte_3=15;

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

    _Reinicio Archivador;
    Replicador_de_Mapa();
    Personaje_Cactus_Valores=Ascenso_Montana(Personaje_Cactus_Valores);
    while(!key[KEY_ESC]){      /*ciclo sin fin*/
        for(h=0;h<TRES;h++){
        Personaje_Cactus_Valores=Personaje_Cactus_Rutina(Personaje_Cactus_Valores,Nube[h]);
        }
        Dibujar_Personaje_Cactus(Personaje_Cactus_Valores);
     /*   for(h=0;h<DOS;h++){
        Enemigo_Pez_Valores_Numero_[h]=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_[h],Personaje_Cactus_Valores);
        }
        Enemigo_Murcielago_Valores=Enemigo_Murcielago_Rutina(Enemigo_Murcielago_Valores,Personaje_Cactus_Valores); */
        if(Personaje_Cactus_Valores.m<16){
        switch (Personaje_Cactus_Valores.m){
            case 15:
                    {
                        Nube[0].Posicion_Y_Parte_1=165;
                        Nube[0].Posicion_Y_Parte_2=165;
                        Nube[0].Posicion_Y_Parte_3=165;
                        Nube[1].Posicion_Y_Parte_1=120;
                        Nube[1].Posicion_Y_Parte_2=120;
                        Nube[1].Posicion_Y_Parte_3=120;
                        break;
                    }
            case 14:
                    {
                        Nube[0].Posicion_Y_Parte_1=180;
                        Nube[0].Posicion_Y_Parte_2=180;
                        Nube[0].Posicion_Y_Parte_3=180;
                        Nube[1].Posicion_Y_Parte_1=135;
                        Nube[1].Posicion_Y_Parte_2=135;
                        Nube[1].Posicion_Y_Parte_3=135;
                        break;
                    }
            case 13:
                    {
                        Nube[0].Posicion_Y_Parte_1=195;
                        Nube[0].Posicion_Y_Parte_2=195;
                        Nube[0].Posicion_Y_Parte_3=195;
                        Nube[1].Posicion_Y_Parte_1=150;
                        Nube[1].Posicion_Y_Parte_2=150;
                        Nube[1].Posicion_Y_Parte_3=150;
                        Nube[2].Posicion_Y_Parte_1=15;
                        Nube[2].Posicion_Y_Parte_2=15;
                        Nube[2].Posicion_Y_Parte_3=15;
                        break;
                    }
            case 12:
                    {
                        Nube[0].Posicion_Y_Parte_1=210;
                        Nube[0].Posicion_Y_Parte_2=210;
                        Nube[0].Posicion_Y_Parte_3=210;
                        Nube[1].Posicion_Y_Parte_1=165;
                        Nube[1].Posicion_Y_Parte_2=165;
                        Nube[1].Posicion_Y_Parte_3=165;
                        Nube[2].Posicion_Y_Parte_1=30;
                        Nube[2].Posicion_Y_Parte_2=30;
                        Nube[2].Posicion_Y_Parte_3=30;
                        break;
                    }
            case 11:
                    {
                        Nube[0].Posicion_Y_Parte_1=225;
                        Nube[0].Posicion_Y_Parte_2=225;
                        Nube[0].Posicion_Y_Parte_3=225;
                        Nube[1].Posicion_Y_Parte_1=180;
                        Nube[1].Posicion_Y_Parte_2=180;
                        Nube[1].Posicion_Y_Parte_3=180;
                        Nube[2].Posicion_Y_Parte_1=45;
                        Nube[2].Posicion_Y_Parte_2=45;
                        Nube[2].Posicion_Y_Parte_3=45;
                        break;
                    }
            case 10:
                    {
                        Nube[0].Posicion_Y_Parte_1=240;
                        Nube[0].Posicion_Y_Parte_2=240;
                        Nube[0].Posicion_Y_Parte_3=240;
                        Nube[1].Posicion_Y_Parte_1=195;
                        Nube[1].Posicion_Y_Parte_2=195;
                        Nube[1].Posicion_Y_Parte_3=195;
                        Nube[2].Posicion_Y_Parte_1=60;
                        Nube[2].Posicion_Y_Parte_2=60;
                        Nube[2].Posicion_Y_Parte_3=60;
                        break;
                    }
            case 9:
                    {
                        Nube[0].Posicion_Y_Parte_1=255;
                        Nube[0].Posicion_Y_Parte_2=255;
                        Nube[0].Posicion_Y_Parte_3=255;
                        Nube[1].Posicion_Y_Parte_1=210;
                        Nube[1].Posicion_Y_Parte_2=210;
                        Nube[1].Posicion_Y_Parte_3=210;
                        Nube[2].Posicion_Y_Parte_1=75;
                        Nube[2].Posicion_Y_Parte_2=75;
                        Nube[2].Posicion_Y_Parte_3=75;
                        break;
                    }
            case 8:
                    {
                        Nube[0].Posicion_Y_Parte_1=270;
                        Nube[0].Posicion_Y_Parte_2=270;
                        Nube[0].Posicion_Y_Parte_3=270;
                        Nube[1].Posicion_Y_Parte_1=225;
                        Nube[1].Posicion_Y_Parte_2=225;
                        Nube[1].Posicion_Y_Parte_3=225;
                        Nube[2].Posicion_Y_Parte_1=90;
                        Nube[2].Posicion_Y_Parte_2=90;
                        Nube[2].Posicion_Y_Parte_3=90;
                        break;
                    }
            case 7:
                    {
                        Nube[0].Posicion_Y_Parte_1=285;
                        Nube[0].Posicion_Y_Parte_2=285;
                        Nube[0].Posicion_Y_Parte_3=285;
                        Nube[1].Posicion_Y_Parte_1=240;
                        Nube[1].Posicion_Y_Parte_2=240;
                        Nube[1].Posicion_Y_Parte_3=240;
                        Nube[2].Posicion_Y_Parte_1=105;
                        Nube[2].Posicion_Y_Parte_2=105;
                        Nube[2].Posicion_Y_Parte_3=105;
                        break;
                    }
            case 6:
                    {
                        Nube[0].Posicion_Y_Parte_1=300;
                        Nube[0].Posicion_Y_Parte_2=300;
                        Nube[0].Posicion_Y_Parte_3=300;
                        Nube[1].Posicion_Y_Parte_1=255;
                        Nube[1].Posicion_Y_Parte_2=255;
                        Nube[1].Posicion_Y_Parte_3=255;
                        Nube[2].Posicion_Y_Parte_1=120;
                        Nube[2].Posicion_Y_Parte_2=120;
                        Nube[2].Posicion_Y_Parte_3=120;
                        break;
                    }
            case 5:
                    {
                        Nube[0].Posicion_Y_Parte_1=315;
                        Nube[0].Posicion_Y_Parte_2=315;
                        Nube[0].Posicion_Y_Parte_3=315;
                        Nube[1].Posicion_Y_Parte_1=270;
                        Nube[1].Posicion_Y_Parte_2=270;
                        Nube[1].Posicion_Y_Parte_3=270;
                        Nube[2].Posicion_Y_Parte_1=135;
                        Nube[2].Posicion_Y_Parte_2=135;
                        Nube[2].Posicion_Y_Parte_3=135;
                        break;
                    }
            case 4:
                    {
                        Nube[0].Posicion_Y_Parte_1=330;
                        Nube[0].Posicion_Y_Parte_2=330;
                        Nube[0].Posicion_Y_Parte_3=330;
                        Nube[1].Posicion_Y_Parte_1=285;
                        Nube[1].Posicion_Y_Parte_2=285;
                        Nube[1].Posicion_Y_Parte_3=285;
                        Nube[2].Posicion_Y_Parte_1=150;
                        Nube[2].Posicion_Y_Parte_2=150;
                        Nube[2].Posicion_Y_Parte_3=150;
                        break;
                    }
            case 3:
                    {
                        Nube[0].Posicion_Y_Parte_1=345;
                        Nube[0].Posicion_Y_Parte_2=345;
                        Nube[0].Posicion_Y_Parte_3=345;
                        Nube[1].Posicion_Y_Parte_1=300;
                        Nube[1].Posicion_Y_Parte_2=300;
                        Nube[1].Posicion_Y_Parte_3=300;
                        Nube[2].Posicion_Y_Parte_1=165;
                        Nube[2].Posicion_Y_Parte_2=165;
                        Nube[2].Posicion_Y_Parte_3=165;
                        break;
                    }
            case 2:
                    {
                        Nube[0].Posicion_Y_Parte_1=360;
                        Nube[0].Posicion_Y_Parte_2=360;
                        Nube[0].Posicion_Y_Parte_3=360;
                        Nube[1].Posicion_Y_Parte_1=315;
                        Nube[1].Posicion_Y_Parte_2=315;
                        Nube[1].Posicion_Y_Parte_3=315;
                        Nube[2].Posicion_Y_Parte_1=180;
                        Nube[2].Posicion_Y_Parte_2=180;
                        Nube[2].Posicion_Y_Parte_3=180;
                        break;
                    }
            case 1:
                    {
                        Nube[0].Posicion_Y_Parte_1=375;
                        Nube[0].Posicion_Y_Parte_2=375;
                        Nube[0].Posicion_Y_Parte_3=375;
                        Nube[1].Posicion_Y_Parte_1=330;
                        Nube[1].Posicion_Y_Parte_2=330;
                        Nube[1].Posicion_Y_Parte_3=330;
                        Nube[2].Posicion_Y_Parte_1=195;
                        Nube[2].Posicion_Y_Parte_2=195;
                        Nube[2].Posicion_Y_Parte_3=195;
                        break;
                    }
            case 0:
                    {
                        Nube[0].Posicion_Y_Parte_1=390;
                        Nube[0].Posicion_Y_Parte_2=390;
                        Nube[0].Posicion_Y_Parte_3=390;
                        Nube[1].Posicion_Y_Parte_1=345;
                        Nube[1].Posicion_Y_Parte_2=345;
                        Nube[1].Posicion_Y_Parte_3=345;
                        Nube[2].Posicion_Y_Parte_1=210;
                        Nube[2].Posicion_Y_Parte_2=210;
                        Nube[2].Posicion_Y_Parte_3=210;
                        break;
                    }
            case -1:
                    {
                        Nube[0].Posicion_Y_Parte_1=405;
                        Nube[0].Posicion_Y_Parte_2=405;
                        Nube[0].Posicion_Y_Parte_3=405;
                        Nube[1].Posicion_Y_Parte_1=360;
                        Nube[1].Posicion_Y_Parte_2=360;
                        Nube[1].Posicion_Y_Parte_3=360;
                        Nube[2].Posicion_Y_Parte_1=225;
                        Nube[2].Posicion_Y_Parte_2=225;
                        Nube[2].Posicion_Y_Parte_3=225;
                        break;
                    }
        }
        Nube[0]=Nube_rutina(Nube[0]);
        Nube[1]=Nube_rutina(Nube[1]);
        if(Personaje_Cactus_Valores.m<14){
        Nube[2]=Nube_rutina(Nube[2]);
        }
        }
        if(Personaje_Cactus_Valores.m<2){
        Nave_Espacial=Aliado_Nave_Espacial_Rutina(Nave_Espacial,Personaje_Cactus_Valores);
        }
        if(Personaje_Cactus_Valores.Posicion_Y<285 && Personaje_Cactus_Valores.m>-1){
        Personaje_Cactus_Valores.m--;
        Personaje_Cactus_Valores.Posicion_Y=Personaje_Cactus_Valores.Posicion_Y+15;
        Enemigo_Murcielago_Valores.Posicion_Y=Enemigo_Murcielago_Valores.Posicion_Y+15;
        for(h=0;h<DOS;h++){
        Enemigo_Pez_Valores_Numero_[h].Posicion_Y=Enemigo_Pez_Valores_Numero_[h].Posicion_Y+15;
        }
        Personaje_Cactus_Valores=Ascenso_Montana(Personaje_Cactus_Valores);
        }
        Dibujar_Montana();
        Pantalla();
        if(Personaje_Cactus_Valores.Posicion_Y>600){
            Perdida();
        }
           if(Control_de_Reinicio>0){
            Archivador=Todas_las_Posiciones(Personaje_Cactus_Valores,Enemigo_Murcielago_Valores,Nave_Espacial);
            Personaje_Cactus_Valores.Posicion_X=Archivador.Personaje_Cactus_Valores.Posicion_X;
            Personaje_Cactus_Valores.Posicion_Y=Archivador.Personaje_Cactus_Valores.Posicion_Y;
            Personaje_Cactus_Valores.m=Archivador.Personaje_Cactus_Valores.m;
            for(h=2;h<DOS;h++){
                Enemigo_Pez_Valores_Numero_[h].Posicion_X=300;
                Enemigo_Pez_Valores_Numero_[h].Posicion_Y=h*105;
            }
            Enemigo_Murcielago_Valores.Posicion_X=Archivador.Enemigo_Murcielago_Valores.Posicion_X;
            Enemigo_Murcielago_Valores.Posicion_Y=Archivador.Enemigo_Murcielago_Valores.Posicion_Y;
            Nave_Espacial.Posicion_X_Parte_1=Archivador.Nave_Espacial.Posicion_X_Parte_1;
            Nave_Espacial.Posicion_X_Parte_2=Archivador.Nave_Espacial.Posicion_X_Parte_2;
            Nave_Espacial.Posicion_X_Parte_3=Archivador.Nave_Espacial.Posicion_X_Parte_3;
            Nave_Espacial.Posicion_Y_Parte_1=Archivador.Nave_Espacial.Posicion_Y_Parte_1;
            Nave_Espacial.Posicion_Y_Parte_2=Archivador.Nave_Espacial.Posicion_Y_Parte_2;
            Nave_Espacial.Posicion_Y_Parte_3=Archivador.Nave_Espacial.Posicion_Y_Parte_3;
            Control_de_Reinicio=0;
        for(int i=0;i<MAX_ALTURA;i++){
        for(int j=0;j<MAX_ANCHURA;j++){
            Montana[i][j]=Montana_de_Respaldo[i][j];
        }
        }
            Personaje_Cactus_Valores=Ascenso_Montana(Personaje_Cactus_Valores);
        }
        clear(buffer);
    }
    return 0;
}
END_OF_MAIN();

