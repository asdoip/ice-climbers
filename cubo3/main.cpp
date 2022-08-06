#include <stdio.h>
#include <allegro.h>
#include <time.h>

#define MAX_ALTURA  66
#define MAX_ANCHURA  34
#define ALTURA_REAL  36

BITMAP *buffer;                  /*espacios en el mapa*/
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

struct _entidad_nave{   /*structuras*/
int Direccion_Nave,Posicion_X_Parte_1,Posicion_Y_Parte_1,Posicion_X_Parte_2,Posicion_Y_Parte_2,Posicion_X_Parte_3,Posicion_Y_Parte_3;
};
struct _entidad{
int Direccion,Posicion_X,Posicion_Y,m,u;
};
struct _Reinicio{
    _entidad Personaje_Cactus_Valores;
    _entidad Enemigo_Pez_Valores_Numero_1;
    _entidad Enemigo_Pez_Valores_Numero_2;
    _entidad Enemigo_Murcielago_Valores;
    _entidad_nave Nave_Espacial;
};

int Control_de_Reinicio=0;

char Montana[MAX_ALTURA][MAX_ANCHURA];
char Montana_de_Respaldo[MAX_ALTURA][MAX_ANCHURA];
char Montana_Real[ALTURA_REAL][MAX_ANCHURA];

void Retardamiento(int Retraso);

void Dibujar_Montana();        /*dibujadores*/
_entidad Ascenso_Montana(_entidad Personaje_Cactus_Valores);
void Replicador_de_Mapa();
void Pantalla();
void Dibujar_Personaje_Cactus(_entidad Personaje_Cactus_Valores);
void Dibujar_Enemigo_Murcielago(_entidad Enemigo_Murcielago_Valores);
void Dibujar_Aliado_Nave_Espacial(_entidad_nave Nave_Espacial);
void Dibujar_Enemigo_Pez(_entidad Enemigo_Pez_Valores_Numero_1);
void Redibujador(_entidad Personaje_Cactus_Valores);
void Dibujar_Nube(_entidad_nave Nube);
_Reinicio Todas_las_Posiciones(_entidad Personaje_Cactus_Valores,_entidad Enemigo_Pez_Valores_Numero_1,_entidad Enemigo_Pez_Valores_Numero_2,_entidad Enemigo_Murcielago_Valores,_entidad_nave Nave_Espacial);

void Perdida();             /*Pantallas*/
void Ganancia();

_entidad Enemigo_Pez_Rutina(_entidad Enemigo_Pez_Valores_Numero_1,_entidad Personaje_Cactus_Valores); /*movimiento*/
_entidad Enemigo_Murcielago_Rutina(_entidad Enemigo_Murcielago_Valores,_entidad Personaje_Cactus_Valores);
_entidad_nave Aliado_Nave_Espacial_Rutina(_entidad_nave Nave_Espacial,_entidad Personaje_Cactus_Valores);
_entidad Personaje_Cactus_Rutina(_entidad Personaje_Cactus_Valores,_entidad_nave Nube);
_entidad_nave Nube_rutina(_entidad_nave Nube);

FILE *Mapa_en_Texto = fopen("./mapas/mapa12.txt","r+t");

int main(){                     /*funcion principal*/
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,660,570,0,0);
    buffer= create_bitmap(660,570);
    Ladrillo_Amarillo=load_bitmap("./bmp/me3.bmp",NULL);
    Ladrillo_Azul=load_bitmap("./bmp/me2.bmp",NULL);
    Personaje_Cactus_bmp=load_bitmap("./bmp/cactus.bmp",NULL);
    Personaje_Cactus=create_bitmap(20,15);
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
    Personaje_Cactus_Valores.Posicion_Y=465;
    Personaje_Cactus_Valores.m=29;

    _entidad Enemigo_Pez_Valores_Numero_1;     /*pez*/
    Enemigo_Pez_Valores_Numero_1.Direccion=0;
    Enemigo_Pez_Valores_Numero_1.Posicion_X=300;
    Enemigo_Pez_Valores_Numero_1.Posicion_Y=105;
    Enemigo_Pez_Valores_Numero_1.m=0;

    _entidad Enemigo_Pez_Valores_Numero_2;     /*pez2*/

     Enemigo_Pez_Valores_Numero_2=Enemigo_Pez_Valores_Numero_1;

     Enemigo_Pez_Valores_Numero_2.Posicion_Y=210;

    _entidad Enemigo_Murcielago_Valores;     /*ave*/
    Enemigo_Murcielago_Valores.Direccion=0;
    Enemigo_Murcielago_Valores.Posicion_X=300;
    Enemigo_Murcielago_Valores.Posicion_Y=100;
    Enemigo_Murcielago_Valores.m=0;

    _entidad_nave Nave_Espacial;    /*ovni*/
    Nave_Espacial.Direccion_Nave=0;
    Nave_Espacial.Posicion_X_Parte_1=140;
    Nave_Espacial.Posicion_X_Parte_2=160;
    Nave_Espacial.Posicion_X_Parte_3=180;
    Nave_Espacial.Posicion_Y_Parte_1=15;
    Nave_Espacial.Posicion_Y_Parte_2=15;
    Nave_Espacial.Posicion_Y_Parte_3=15;

    _entidad_nave Nube;    /*ovni*/
    Nube=Nave_Espacial;
    Nube.Posicion_X_Parte_1=180;
    Nube.Posicion_X_Parte_2=200;
    Nube.Posicion_X_Parte_3=220;


    _Reinicio Archivador;
    Replicador_de_Mapa();
    Personaje_Cactus_Valores=Ascenso_Montana(Personaje_Cactus_Valores);
    while(!key[KEY_ESC]){      /*ciclo sin fin*/
        Personaje_Cactus_Valores=Personaje_Cactus_Rutina(Personaje_Cactus_Valores,Nube);
        Enemigo_Pez_Valores_Numero_1=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_1,Personaje_Cactus_Valores);
        Enemigo_Pez_Valores_Numero_2=Enemigo_Pez_Rutina(Enemigo_Pez_Valores_Numero_2,Personaje_Cactus_Valores);
        Enemigo_Murcielago_Valores=Enemigo_Murcielago_Rutina(Enemigo_Murcielago_Valores,Personaje_Cactus_Valores);
        if(Personaje_Cactus_Valores.m<12){
        switch (Personaje_Cactus_Valores.m){
            case 11:
                    {
                        Nube.Posicion_Y_Parte_1=225;
                        Nube.Posicion_Y_Parte_2=225;
                        Nube.Posicion_Y_Parte_3=225;
                        break;
                    }
            case 10:
                    {
                        Nube.Posicion_Y_Parte_1=240;
                        Nube.Posicion_Y_Parte_2=240;
                        Nube.Posicion_Y_Parte_3=240;
                        break;
                    }
            case 9:
                    {
                        Nube.Posicion_Y_Parte_1=255;
                        Nube.Posicion_Y_Parte_2=255;
                        Nube.Posicion_Y_Parte_3=255;
                        break;
                    }
            case 8:
                    {
                        Nube.Posicion_Y_Parte_1=270;
                        Nube.Posicion_Y_Parte_2=270;
                        Nube.Posicion_Y_Parte_3=270;
                        break;
                    }
            case 7:
                    {
                        Nube.Posicion_Y_Parte_1=285;
                        Nube.Posicion_Y_Parte_2=285;
                        Nube.Posicion_Y_Parte_3=285;
                        break;
                    }
            case 6:
                    {
                        Nube.Posicion_Y_Parte_1=300;
                        Nube.Posicion_Y_Parte_2=300;
                        Nube.Posicion_Y_Parte_3=300;
                        break;
                    }
            case 5:
                    {
                        Nube.Posicion_Y_Parte_1=315;
                        Nube.Posicion_Y_Parte_2=315;
                        Nube.Posicion_Y_Parte_3=315;
                        break;
                    }
            case 4:
                    {
                        Nube.Posicion_Y_Parte_1=330;
                        Nube.Posicion_Y_Parte_2=330;
                        Nube.Posicion_Y_Parte_3=330;
                        break;
                    }
            case 3:
                    {
                        Nube.Posicion_Y_Parte_1=345;
                        Nube.Posicion_Y_Parte_2=345;
                        Nube.Posicion_Y_Parte_3=345;
                        break;
                    }
            case 2:
                    {
                        Nube.Posicion_Y_Parte_1=360;
                        Nube.Posicion_Y_Parte_2=360;
                        Nube.Posicion_Y_Parte_3=360;
                        break;
                    }
            case 1:
                    {
                        Nube.Posicion_Y_Parte_1=375;
                        Nube.Posicion_Y_Parte_2=375;
                        Nube.Posicion_Y_Parte_3=375;
                        break;
                    }
            case 0:
                    {
                        Nube.Posicion_Y_Parte_1=390;
                        Nube.Posicion_Y_Parte_2=390;
                        Nube.Posicion_Y_Parte_3=390;
                        break;
                    }
            case -1:
                    {
                        Nube.Posicion_Y_Parte_1=405;
                        Nube.Posicion_Y_Parte_2=405;
                        Nube.Posicion_Y_Parte_3=405;
                        break;
                    }
        }
        Nube=Nube_rutina(Nube);
        }
        if(Personaje_Cactus_Valores.m==-2){
        Nave_Espacial=Aliado_Nave_Espacial_Rutina(Nave_Espacial,Personaje_Cactus_Valores);
        }
        if(Personaje_Cactus_Valores.Posicion_Y<300 && Personaje_Cactus_Valores.m>-1){
        Personaje_Cactus_Valores.m--;
        Personaje_Cactus_Valores.Posicion_Y=Personaje_Cactus_Valores.Posicion_Y+15;
        Enemigo_Murcielago_Valores.Posicion_Y=Enemigo_Murcielago_Valores.Posicion_Y+15;
        Enemigo_Pez_Valores_Numero_2.Posicion_Y=Enemigo_Pez_Valores_Numero_2.Posicion_Y+15;
        Enemigo_Pez_Valores_Numero_1.Posicion_Y=Enemigo_Pez_Valores_Numero_1.Posicion_Y+15;
        Personaje_Cactus_Valores=Ascenso_Montana(Personaje_Cactus_Valores);
        }
        Dibujar_Montana();
        Pantalla();
        if(Personaje_Cactus_Valores.Posicion_Y>660){
            Perdida();
        }
        if(Control_de_Reinicio>0){
            Archivador=Todas_las_Posiciones(Personaje_Cactus_Valores,Enemigo_Pez_Valores_Numero_1,Enemigo_Pez_Valores_Numero_2,Enemigo_Murcielago_Valores,Nave_Espacial);
            Personaje_Cactus_Valores.Posicion_X=Archivador.Personaje_Cactus_Valores.Posicion_X;
            Personaje_Cactus_Valores.Posicion_Y=Archivador.Personaje_Cactus_Valores.Posicion_Y;
            Personaje_Cactus_Valores.m=Archivador.Personaje_Cactus_Valores.m;
            Enemigo_Pez_Valores_Numero_1.Posicion_X=Archivador.Enemigo_Pez_Valores_Numero_1.Posicion_X;
            Enemigo_Pez_Valores_Numero_1.Posicion_Y=Archivador.Enemigo_Pez_Valores_Numero_1.Posicion_Y;
            Enemigo_Pez_Valores_Numero_2.Posicion_Y=Archivador.Enemigo_Pez_Valores_Numero_2.Posicion_Y;
            Enemigo_Pez_Valores_Numero_2.Posicion_X=Archivador.Enemigo_Pez_Valores_Numero_2.Posicion_X;
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

_entidad Ascenso_Montana(_entidad Personaje_Cactus_Valores){
    int i=0,j=0,z,f,u;
    z=ALTURA_REAL-1;
    f=MAX_ANCHURA-1;
    for(i=z;i>0;i--){
        for(j=0;j<MAX_ANCHURA;j++){
            u=i+Personaje_Cactus_Valores.m;
            Montana_Real[i][j]=Montana[u][j];
        }
    }
    return Personaje_Cactus_Valores;
    }

void Dibujar_Montana(){        /*dibujadores*/
    int i,j;
    for(i=0;i<ALTURA_REAL;i++){
        for(j=0;j<MAX_ANCHURA;j++){
            if(Montana_Real[i][j]=='X'){
                draw_sprite(buffer, Ladrillo_Amarillo, j*20, i*15);
            }
            if(Montana_Real[i][j]=='Y'){
                draw_sprite(buffer, Ladrillo_Azul, j*20, i*15);
            }
            if(Montana_Real[i][j]=='F'){
                draw_sprite(buffer, Fruta, j*20, i*15);
            }
        }
    }
}

void Replicador_de_Mapa(){
char Intermediario;
int i=0,j=0;
while(!feof(Mapa_en_Texto)){
    fscanf(Mapa_en_Texto,"%c",&Intermediario);
    if(Intermediario=='\n'){
     i++;
     j=0;
    }
    if(Intermediario!='\n'){
    Montana[i][j]=Intermediario;
    j++;
    }
}
    for(int i=0;i<MAX_ALTURA;i++){
        for(int j=0;j<MAX_ANCHURA;j++){
            Montana_de_Respaldo[i][j]=Montana[i][j];
        }
    }
}

void Pantalla(){
    blit(buffer, screen, 0,0,0,0,660,570);
}
void Dibujar_Personaje_Cactus(_entidad Personaje_Cactus_Valores){
    blit(Personaje_Cactus_bmp,Personaje_Cactus, Personaje_Cactus_Valores.Direccion*20,0,0,0,20,15);
    draw_sprite(buffer,Personaje_Cactus,Personaje_Cactus_Valores.Posicion_X,Personaje_Cactus_Valores.Posicion_Y);
}
void Dibujar_Enemigo_Murcielago(_entidad Enemigo_Murcielago_Valores){
    blit(Enemigo_Murcielago_bmp,Enemigo_Murcielago, 0*20,0,0,0,20,15);
    draw_sprite(buffer,Enemigo_Murcielago,Enemigo_Murcielago_Valores.Posicion_X,Enemigo_Murcielago_Valores.Posicion_Y);
}
void Dibujar_Aliado_Nave_Espacial(_entidad_nave Nave_Espacial){
    blit(Aliado_Nave_Espacial_Parte_1_bmp,Aliado_Nave_Espacial_Parte_1, 0*20,0,0,0,20,15);
    draw_sprite(buffer,Aliado_Nave_Espacial_Parte_1,Nave_Espacial.Posicion_X_Parte_1,Nave_Espacial.Posicion_Y_Parte_1);
    blit(Aliado_Nave_Espacial_Parte_2_bmp,Aliado_Nave_Espacial_Parte_2, 1*20,0,0,0,20,15);
    draw_sprite(buffer,Aliado_Nave_Espacial_Parte_2,Nave_Espacial.Posicion_X_Parte_2,Nave_Espacial.Posicion_Y_Parte_2);
    blit(Aliado_Nave_Espacial_Parte_3_bmp,Aliado_Nave_Espacial_Parte_3, 2*20,0,0,0,20,15);
    draw_sprite(buffer,Aliado_Nave_Espacial_Parte_3,Nave_Espacial.Posicion_X_Parte_3,Nave_Espacial.Posicion_Y_Parte_3);
}
void Dibujar_Enemigo_Pez(_entidad Enemigo_Pez_Valores_Numero_1){
    blit(Enemigo_Pez_bmp,Enemigo_Pez, Enemigo_Pez_Valores_Numero_1.Direccion*20,0,0,0,20,15);
    draw_sprite(buffer,Enemigo_Pez,Enemigo_Pez_Valores_Numero_1.Posicion_X,Enemigo_Pez_Valores_Numero_1.Posicion_Y);
}
void Dibujar_Nube(_entidad_nave Nube){
    blit(Nube_Parte_1_bmp,Nube_Parte_1, 0*20,0,0,0,20,15);
    draw_sprite(buffer,Nube_Parte_1,Nube.Posicion_X_Parte_1,Nube.Posicion_Y_Parte_1);
    blit(Nube_Parte_2_bmp,Nube_Parte_2, 1*20,0,0,0,20,15);
    draw_sprite(buffer,Nube_Parte_2,Nube.Posicion_X_Parte_2,Nube.Posicion_Y_Parte_2);
    blit(Nube_Parte_3_bmp,Nube_Parte_3, 2*20,0,0,0,20,15);
    draw_sprite(buffer,Nube_Parte_3,Nube.Posicion_X_Parte_3,Nube.Posicion_Y_Parte_3);
}

void Perdida(){     /*ganar, perder*/
    Control_de_Reinicio=1;
}
void Ganancia(){
    Control_de_Reinicio=2;
}
void Retardamiento(int Retraso){
    int Contador;
    for(Contador=0;Contador<Retraso;Contador++){
    rest(8);
    }
}
_Reinicio Todas_las_Posiciones(_entidad Personaje_Cactus_Valores,_entidad Enemigo_Pez_Valores_Numero_1,_entidad Enemigo_Pez_Valores_Numero_2,_entidad Enemigo_Murcielago_Valores,_entidad_nave Nave_Espacial){
    _Reinicio Archivador;
    if(Control_de_Reinicio==1){
    while(!key[KEY_R]){
    clear_to_color(buffer,0x000000);
    textout_centre(buffer, font,"perdiste, presione r para reiniciar",300, 100, 0x3BFF14);
    textout_centre(buffer, font,"presione ESC para salir",300, 130, 0x3BFF14);
    blit(buffer,screen,0,0,0,0,660,700);
    if(key[KEY_ESC]){
        break;
    }
    }
    }
    if(Control_de_Reinicio==2){
    while(!key[KEY_R]){
    clear_to_color(buffer,0x000000);
    textout_centre(buffer, font,"Ganaste, presione r para reiniciar",300, 100, 0x3BFF14);
    textout_centre(buffer, font,"presione ESC para salir",300, 130, 0x3BFF14);
    blit(buffer,screen,0,0,0,0,660,700);
    if(key[KEY_ESC]){
        break;
    }
    }
}
            Archivador.Personaje_Cactus_Valores.Posicion_X=100;
            Archivador.Personaje_Cactus_Valores.Posicion_Y=495;
            Archivador.Personaje_Cactus_Valores.m=29;
            Archivador.Enemigo_Pez_Valores_Numero_1.Posicion_X=300;
            Archivador.Enemigo_Pez_Valores_Numero_1.Posicion_Y=105;
            Archivador.Enemigo_Pez_Valores_Numero_2.Posicion_Y=210;
            Archivador.Enemigo_Pez_Valores_Numero_2.Posicion_X=300;
            Archivador.Enemigo_Murcielago_Valores.Posicion_X=300;
            Archivador.Enemigo_Murcielago_Valores.Posicion_Y=100;
            Archivador.Nave_Espacial.Posicion_X_Parte_1=140;
            Archivador.Nave_Espacial.Posicion_X_Parte_2=160;
            Archivador.Nave_Espacial.Posicion_X_Parte_3=180;
            Archivador.Nave_Espacial.Posicion_Y_Parte_1=15;
            Archivador.Nave_Espacial.Posicion_Y_Parte_2=15;
            Archivador.Nave_Espacial.Posicion_Y_Parte_3=15;
        return Archivador;
}
void Redibujador(_entidad Personaje_Cactus_Valores){
    int i,j,z,u;
    z=ALTURA_REAL-1;
    for(i=z;i>0;i--){
        for(j=0;j<MAX_ANCHURA;j++){
            u=i+Personaje_Cactus_Valores.m;
            Montana[u][j]=Montana_Real[i][j];
        }
    }
}
_entidad Personaje_Cactus_Rutina(_entidad Personaje_Cactus_Valores,_entidad_nave Nube){        /*Rutinas*/
        if(Personaje_Cactus_Valores.u<4){
        Personaje_Cactus_Valores.u++;
        }
        if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][Personaje_Cactus_Valores.Posicion_X/20] != 'X' || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][Personaje_Cactus_Valores.Posicion_X/20] !='Y'){
            Personaje_Cactus_Valores.Direccion=1;
            Personaje_Cactus_Valores.Posicion_Y +=15;
        }
        if(Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][Personaje_Cactus_Valores.Posicion_X/20] == 'X' || Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][Personaje_Cactus_Valores.Posicion_X/20] =='Y' || Personaje_Cactus_Valores.Posicion_Y==Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_1==Personaje_Cactus_Valores.Posicion_X || Personaje_Cactus_Valores.Posicion_Y==Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_2==Personaje_Cactus_Valores.Posicion_X || Personaje_Cactus_Valores.Posicion_Y==Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_3==Personaje_Cactus_Valores.Posicion_X){
            Personaje_Cactus_Valores.Posicion_Y -=15;
            if(Personaje_Cactus_Valores.Posicion_Y+15==Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_1==Personaje_Cactus_Valores.Posicion_X && Personaje_Cactus_Valores.u==4){
                if(Nube.Direccion_Nave==1){
                    Personaje_Cactus_Valores.Posicion_X=Personaje_Cactus_Valores.Posicion_X+20;
                }
                if(Nube.Direccion_Nave==0){
                    Personaje_Cactus_Valores.Posicion_X=Personaje_Cactus_Valores.Posicion_X-20;
                }
                Personaje_Cactus_Valores.u=0;
            }
            if(Personaje_Cactus_Valores.Posicion_Y+15==Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_2==Personaje_Cactus_Valores.Posicion_X && Personaje_Cactus_Valores.u==4){
                if(Nube.Direccion_Nave==1){
                    Personaje_Cactus_Valores.Posicion_X=Personaje_Cactus_Valores.Posicion_X+20;
                }
                if(Nube.Direccion_Nave==0){
                    Personaje_Cactus_Valores.Posicion_X=Personaje_Cactus_Valores.Posicion_X-20;
                }
                Personaje_Cactus_Valores.u=0;
            }
            if(Personaje_Cactus_Valores.Posicion_Y+15==Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_3==Personaje_Cactus_Valores.Posicion_X && Personaje_Cactus_Valores.u==4){
                if(Nube.Direccion_Nave==1){
                    Personaje_Cactus_Valores.Posicion_X=Personaje_Cactus_Valores.Posicion_X+20;
                }
                if(Nube.Direccion_Nave==0){
                    Personaje_Cactus_Valores.Posicion_X=Personaje_Cactus_Valores.Posicion_X-20;
                }
                Personaje_Cactus_Valores.u=0;
            }
        if(key[KEY_RIGHT]) Personaje_Cactus_Valores.Direccion=3;
        if(key[KEY_LEFT]) Personaje_Cactus_Valores.Direccion=7;
        if(key[KEY_UP]) Personaje_Cactus_Valores.Direccion=0;
        if(key[KEY_UP] && key[KEY_RIGHT]) Personaje_Cactus_Valores.Direccion=4;
        if(key[KEY_UP] && key[KEY_LEFT]) Personaje_Cactus_Valores.Direccion=6;
        switch(Personaje_Cactus_Valores.Direccion){
        case 4:{
            if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][(Personaje_Cactus_Valores.Posicion_X+20)/20] != 'Y' && Personaje_Cactus_Valores.u==4){
            if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-45)/15][Personaje_Cactus_Valores.Posicion_X/20] == 'X'){
            Personaje_Cactus_Valores.Posicion_Y -=30;
            if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][(Personaje_Cactus_Valores.Posicion_X+20)/20]=='X'){
                Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][(Personaje_Cactus_Valores.Posicion_X+20)/20] =' ';
            }
            Redibujador(Personaje_Cactus_Valores);
            }
            else{
            Personaje_Cactus_Valores.Posicion_Y -=60;
            }
            Personaje_Cactus_Valores.Posicion_X +=20;
            Personaje_Cactus_Valores.u=0;
        }
                    break;
        }
        case 6:{
            if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'Y' && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20] != 'Y' && Personaje_Cactus_Valores.u==4){
            if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-45)/15][Personaje_Cactus_Valores.Posicion_X/20] == 'X'){
            Personaje_Cactus_Valores.Posicion_Y -=30;
            if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][(Personaje_Cactus_Valores.Posicion_X-20)/20]=='X'){
                Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] =' ';
            }
            Redibujador(Personaje_Cactus_Valores);
            }
            else{
            Personaje_Cactus_Valores.Posicion_Y -=60;
            }
            Personaje_Cactus_Valores.Posicion_X -=20;
            Personaje_Cactus_Valores.u=0;
        }
                    break;
        }
        case 0:{
            if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20] != 'Y' && Personaje_Cactus_Valores.u==4){
            if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-45)/15][Personaje_Cactus_Valores.Posicion_X/20] == 'X'){
            Personaje_Cactus_Valores.Posicion_Y -=30;
            if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20]=='X'){
                Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20] =' ';
            }
            Redibujador(Personaje_Cactus_Valores);
            }
            else{
            Personaje_Cactus_Valores.Posicion_Y -=60;
            }
            Personaje_Cactus_Valores.u=0;
            }
            break;
        }
        case 3:{
            if(Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X+20)/20] != 'Y' && Personaje_Cactus_Valores.u==4){
            Personaje_Cactus_Valores.Posicion_X +=20;
            Personaje_Cactus_Valores.u=0;
            break;
            }
        }
        case 7:{
            if(Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'Y' && Personaje_Cactus_Valores.u==4){
            Personaje_Cactus_Valores.Posicion_X -=20;
            Personaje_Cactus_Valores.u=0;
            break;
            }
        }
        }
        if(Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][Personaje_Cactus_Valores.Posicion_X/20]=='F'){
            Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][Personaje_Cactus_Valores.Posicion_X/20]=' ';
        }
        }
        Dibujar_Personaje_Cactus(Personaje_Cactus_Valores);
        return Personaje_Cactus_Valores;
        }

_entidad Enemigo_Pez_Rutina(_entidad Enemigo_Pez_Valores_Numero_1,_entidad Personaje_Cactus_Valores){    /*movimiento*/
        if(Enemigo_Pez_Valores_Numero_1.Posicion_Y>660){}
        else{
        if(Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][Enemigo_Pez_Valores_Numero_1.Posicion_X/20] != 'X' || Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][Enemigo_Pez_Valores_Numero_1.Posicion_X/20] !='Y'){
            Enemigo_Pez_Valores_Numero_1.Posicion_Y +=15;
        }
        if(Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][Enemigo_Pez_Valores_Numero_1.Posicion_X/20] == 'X' || Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][Enemigo_Pez_Valores_Numero_1.Posicion_X/20] =='Y'){
            Enemigo_Pez_Valores_Numero_1.Posicion_Y -=15;
    if(Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X+20)/20] != 'X' || Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X+20)/20] == 'Y'){
        Enemigo_Pez_Valores_Numero_1.Direccion=0;
    }
    if(Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X-20)/20] != 'X' || Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X-20)/20] == 'Y'){
        Enemigo_Pez_Valores_Numero_1.Direccion=1;
    }
    Enemigo_Pez_Valores_Numero_1.m++;
    if(Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X+20)/20] == 'X' && Enemigo_Pez_Valores_Numero_1.Direccion==1 && Enemigo_Pez_Valores_Numero_1.m == 10|| Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X+20)/20] == 'Y' && Enemigo_Pez_Valores_Numero_1.Direccion==1 && Enemigo_Pez_Valores_Numero_1.m==10){
            Enemigo_Pez_Valores_Numero_1.Posicion_X +=5;
        }
        if(Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X-20)/20] == 'X' && Enemigo_Pez_Valores_Numero_1.Direccion==0 && Enemigo_Pez_Valores_Numero_1.m == 10 || Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X-20)/20]== 'Y' && Enemigo_Pez_Valores_Numero_1.Direccion==0 && Enemigo_Pez_Valores_Numero_1.m == 10){
            Enemigo_Pez_Valores_Numero_1.Posicion_X -=5;
        }
        }
        if(Enemigo_Pez_Valores_Numero_1.m==10){
            Enemigo_Pez_Valores_Numero_1.m=0;
        }
Dibujar_Enemigo_Pez(Enemigo_Pez_Valores_Numero_1);
if(Enemigo_Pez_Valores_Numero_1.Posicion_Y == Personaje_Cactus_Valores.Posicion_Y && Enemigo_Pez_Valores_Numero_1.Posicion_X == Personaje_Cactus_Valores.Posicion_X){
    Perdida();
    }
        }
        return Enemigo_Pez_Valores_Numero_1;
};

_entidad Enemigo_Murcielago_Rutina(_entidad Enemigo_Murcielago_Valores,_entidad Personaje_Cactus_Valores){
    if(Enemigo_Murcielago_Valores.Posicion_Y>660){}
    else{
    Enemigo_Murcielago_Valores.m++;
    if(Enemigo_Murcielago_Valores.Posicion_X > Personaje_Cactus_Valores.Posicion_X && Enemigo_Murcielago_Valores.m==30){
            Enemigo_Murcielago_Valores.Posicion_X -=5;
    if(Enemigo_Murcielago_Valores.Posicion_Y > Personaje_Cactus_Valores.Posicion_Y){
            Enemigo_Murcielago_Valores.Posicion_Y -=5;
    }
    if(Enemigo_Murcielago_Valores.Posicion_Y < Personaje_Cactus_Valores.Posicion_Y){
            Enemigo_Murcielago_Valores.Posicion_Y +=5;
    }
    }
if(Enemigo_Murcielago_Valores.Posicion_X < Personaje_Cactus_Valores.Posicion_X && Enemigo_Murcielago_Valores.m==30){
            Enemigo_Murcielago_Valores.Posicion_X +=5;
	if(Enemigo_Murcielago_Valores.Posicion_Y < Personaje_Cactus_Valores.Posicion_Y){
            Enemigo_Murcielago_Valores.Posicion_Y +=5;
    	}
    if(Enemigo_Murcielago_Valores.Posicion_Y > Personaje_Cactus_Valores.Posicion_Y){
            Enemigo_Murcielago_Valores.Posicion_Y -=5;
    }
}
if(Enemigo_Murcielago_Valores.Posicion_X==Personaje_Cactus_Valores.Posicion_X && Enemigo_Murcielago_Valores.m==30){
    if(Enemigo_Murcielago_Valores.Posicion_Y < Personaje_Cactus_Valores.Posicion_Y){
            Enemigo_Murcielago_Valores.Posicion_Y +=5;
    }
    if(Enemigo_Murcielago_Valores.Posicion_Y > Personaje_Cactus_Valores.Posicion_Y){
            Enemigo_Murcielago_Valores.Posicion_Y -=5;
    }
}
if(Enemigo_Murcielago_Valores.Posicion_Y==Personaje_Cactus_Valores.Posicion_Y && Enemigo_Murcielago_Valores.m==30){
    if(Enemigo_Murcielago_Valores.Posicion_X > Personaje_Cactus_Valores.Posicion_X){
            Enemigo_Murcielago_Valores.Posicion_X -=5;
    }
    if(Enemigo_Murcielago_Valores.Posicion_X < Personaje_Cactus_Valores.Posicion_X){
            Enemigo_Murcielago_Valores.Posicion_X +=5;
    }
}
if(Enemigo_Murcielago_Valores.m==30){
    Enemigo_Murcielago_Valores.m=0;
}
Dibujar_Enemigo_Murcielago(Enemigo_Murcielago_Valores);
if(Enemigo_Murcielago_Valores.Posicion_Y == Personaje_Cactus_Valores.Posicion_Y && Enemigo_Murcielago_Valores.Posicion_X == Personaje_Cactus_Valores.Posicion_X){
    Perdida();
    }
    }
return Enemigo_Murcielago_Valores;
};

_entidad_nave Aliado_Nave_Espacial_Rutina(_entidad_nave Nave_Espacial,_entidad Personaje_Cactus_Valores){
        if(Montana_Real[Nave_Espacial.Posicion_Y_Parte_3/15][(Nave_Espacial.Posicion_X_Parte_3+20)/20] == 'O'){
            Nave_Espacial.Direccion_Nave=0;
        }
        if(Montana_Real[Nave_Espacial.Posicion_Y_Parte_1/15][(Nave_Espacial.Posicion_X_Parte_1-20)/20] == 'O'){
            Nave_Espacial.Direccion_Nave=1;
        }
        switch (Nave_Espacial.Direccion_Nave){
        case 1:{
            Nave_Espacial.Posicion_X_Parte_1++;
            Nave_Espacial.Posicion_X_Parte_2++;
            Nave_Espacial.Posicion_X_Parte_3++;
        }
        case 0:{
            Nave_Espacial.Posicion_X_Parte_1--;
            Nave_Espacial.Posicion_X_Parte_2--;
            Nave_Espacial.Posicion_X_Parte_3--;
        }
        }
    Dibujar_Aliado_Nave_Espacial(Nave_Espacial);
    if(Nave_Espacial.Posicion_Y_Parte_2 == Personaje_Cactus_Valores.Posicion_Y && Nave_Espacial.Posicion_X_Parte_2 == Personaje_Cactus_Valores.Posicion_X){
    Ganancia();
    }
    return Nave_Espacial;
};

_entidad_nave Nube_rutina(_entidad_nave Nube){
        if(Montana_Real[Nube.Posicion_Y_Parte_3/15][(Nube.Posicion_X_Parte_3+20)/20] == 'O'){
            Nube.Direccion_Nave=0;
        }
        if(Montana_Real[Nube.Posicion_Y_Parte_1/15][(Nube.Posicion_X_Parte_1-20)/20] == 'O'){
            Nube.Direccion_Nave=1;
        }
        if(Nube.Direccion_Nave==1){
            Nube.Posicion_X_Parte_1 +=20;
            Nube.Posicion_X_Parte_2 +=20;
            Nube.Posicion_X_Parte_3 +=20;
        }
        if(Nube.Direccion_Nave==0){
            Nube.Posicion_X_Parte_1 -=20;
            Nube.Posicion_X_Parte_2 -=20;
            Nube.Posicion_X_Parte_3 -=20;
        }
    Dibujar_Nube(Nube);
    return Nube;
}

