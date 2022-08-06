#include <stdio.h>
#include <allegro.h>
#include <time.h>

#define MAX_ALTURA  114
#define MAX_ANCHURA  132
#define ALTURA_REAL  114

struct _entidad_nave{   /*structuras*/
int Direccion_Nave,Posicion_X_Parte_1,Posicion_Y_Parte_1,Posicion_X_Parte_2,Posicion_Y_Parte_2,Posicion_X_Parte_3,Posicion_Y_Parte_3;
};
struct _entidad{
int Direccion,Posicion_X,Posicion_Y,m;
};
struct _Reinicio{
    _entidad Personaje_Cactus_Valores;
    _entidad Enemigo_Pez_Valores_Numero_1;
    _entidad Enemigo_Pez_Valores_Numero_2;
    _entidad Enemigo_Murcielago_Valores;
    _entidad_nave Nave_Espacial;
};

char Montana[MAX_ALTURA][MAX_ANCHURA];
char Montana_de_Respaldo[MAX_ALTURA][MAX_ANCHURA];
char Montana_Real[ALTURA_REAL][MAX_ANCHURA];

_entidad Personaje_Cactus_Rutina(_entidad Personaje_Cactus_Valores);
void Dibujar_Personaje_Cactus(_entidad Personaje_Cactus_Valores);

void Dibujar_Montana();        /*dibujadores*/
void Pantalla();
void Replicador_de_Mapa();
void borrar(_entidad Personaje_Cactus_Valores);

BITMAP *buffer;
BITMAP *Prueva;
BITMAP *Ladrillo_Verde;
BITMAP *Hielo_Subterraneo;
BITMAP *Cactus_bmp;
BITMAP *Cactus;

FILE *Mapa_en_Texto = fopen("./mapas/mapa1.txt","r+t");

int main(){                     /*funcion principal*/
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,660,570,0,0);
    buffer=create_bitmap(660,570);

    Prueva=load_bitmap("./bmp/prueva.bmp",NULL);
    Ladrillo_Verde=load_bitmap("./bmp/Ladrillo2.bmp",NULL);
    Hielo_Subterraneo=load_bitmap("./bmp/Hileo.bmp",NULL);
    Cactus_bmp=load_bitmap("./bmp/cactus2.bmp",NULL);
    Cactus=create_bitmap(20,25);

    _entidad Personaje_Cactus_Valores; /*catus*/
    Personaje_Cactus_Valores.Direccion=0;
    Personaje_Cactus_Valores.Posicion_X=300;
    Personaje_Cactus_Valores.Posicion_Y=505;
    Personaje_Cactus_Valores.m=29;

    Replicador_de_Mapa();

    while(!key[KEY_ESC]){      /*ciclo sin fin*/
        Dibujar_Montana();
        Personaje_Cactus_Valores=Personaje_Cactus_Rutina(Personaje_Cactus_Valores);
        Pantalla();
        clear(buffer);
    }
    return 0;
}
END_OF_MAIN();


void Dibujar_Montana(){        /*dibujadores*/
    int i,j;
    for(i=0;i<ALTURA_REAL;i++){
        for(j=0;j<MAX_ANCHURA;j++){
            if(Montana[i][j]=='X'){
                draw_sprite(buffer, Ladrillo_Verde, j*5, i*5);
        }
            if(Montana[i][j]=='H'){
                draw_sprite(buffer, Hielo_Subterraneo, j*5, i*5);
        }
    }
}
}
void Pantalla(){
    blit(buffer, screen, 0,0,0,0,660,570);
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
_entidad Personaje_Cactus_Rutina(_entidad Personaje_Cactus_Valores){
    if(Montana[(Personaje_Cactus_Valores.Posicion_Y+5)/5][Personaje_Cactus_Valores.Posicion_X/5] != 'X' || Montana[(Personaje_Cactus_Valores.Posicion_Y+5)/5][Personaje_Cactus_Valores.Posicion_X/5] != 'Z'){
        Personaje_Cactus_Valores.Posicion_Y +=10;
    }
    if(Montana[(Personaje_Cactus_Valores.Posicion_Y+15)/5][Personaje_Cactus_Valores.Posicion_X/5] == 'X' || Montana[(Personaje_Cactus_Valores.Posicion_Y+15)/5][Personaje_Cactus_Valores.Posicion_X/5] == 'Z'){
        Personaje_Cactus_Valores.Posicion_Y -=10;
        if(key[KEY_RIGHT]) Personaje_Cactus_Valores.Direccion=3;
        if(key[KEY_LEFT]) Personaje_Cactus_Valores.Direccion=7;
        if(key[KEY_UP]) Personaje_Cactus_Valores.Direccion=0;
        if(key[KEY_UP] && key[KEY_RIGHT]) Personaje_Cactus_Valores.Direccion=4;
        if(key[KEY_UP] && key[KEY_LEFT]) Personaje_Cactus_Valores.Direccion=6;
        switch(Personaje_Cactus_Valores.Direccion){
            case 3:{
                if(Montana[Personaje_Cactus_Valores.Posicion_Y/5][(Personaje_Cactus_Valores.Posicion_X+5)/5] != 'Z'){
                    Personaje_Cactus_Valores.Posicion_X +=1;
                    break;
                }
            }
            case 7:{
                if(Montana[Personaje_Cactus_Valores.Posicion_Y/5][(Personaje_Cactus_Valores.Posicion_X-5)/5] != 'Z'){
                    Personaje_Cactus_Valores.Posicion_X -=1;
                    break;
                }
            }
            case 0:{
                if(Montana[(Personaje_Cactus_Valores.Posicion_Y-70)/5][Personaje_Cactus_Valores.Posicion_X/5] == 'Z' || Montana[(Personaje_Cactus_Valores.Posicion_Y-70)/5][Personaje_Cactus_Valores.Posicion_X/5] == 'X'){
                    Personaje_Cactus_Valores.Posicion_Y -=60;
                    borrar(Personaje_Cactus_Valores);
                }
                if(Montana[(Personaje_Cactus_Valores.Posicion_Y-65)/5][Personaje_Cactus_Valores.Posicion_X/5] != 'Z' || Montana[(Personaje_Cactus_Valores.Posicion_Y-65)/5][Personaje_Cactus_Valores.Posicion_X/5] != 'X'){
                    Personaje_Cactus_Valores.Posicion_Y -=80;
                }
                break;
            }
            case 4:{
                if(Montana[(Personaje_Cactus_Valores.Posicion_Y-70)/5][(Personaje_Cactus_Valores.Posicion_X+5)/5] == 'Z' || Montana[(Personaje_Cactus_Valores.Posicion_Y-70)/5][(Personaje_Cactus_Valores.Posicion_X+5)/5] == 'X'){
                    Personaje_Cactus_Valores.Posicion_Y -=60;
                    Personaje_Cactus_Valores.Posicion_X +=10;
                    borrar(Personaje_Cactus_Valores);
                }
                if(Montana[(Personaje_Cactus_Valores.Posicion_Y-70)/5][(Personaje_Cactus_Valores.Posicion_X+5)/5] != 'Z' || Montana[(Personaje_Cactus_Valores.Posicion_Y-70)/5][(Personaje_Cactus_Valores.Posicion_X+5)/5] != 'X'){
                    Personaje_Cactus_Valores.Posicion_Y -=80;
                    Personaje_Cactus_Valores.Posicion_X +=10;
                }
                break;
            }
            case 6:{
                if(Montana[(Personaje_Cactus_Valores.Posicion_Y-70)/5][(Personaje_Cactus_Valores.Posicion_X-5)/5] == 'Z' || Montana[(Personaje_Cactus_Valores.Posicion_Y-70)/5][(Personaje_Cactus_Valores.Posicion_X-5)/5] == 'X'){
                    Personaje_Cactus_Valores.Posicion_Y -=60;
                    Personaje_Cactus_Valores.Posicion_X -=10;
                    borrar(Personaje_Cactus_Valores);
                }
                if(Montana[(Personaje_Cactus_Valores.Posicion_Y-70)/5][(Personaje_Cactus_Valores.Posicion_X-5)/5] != 'Z' || Montana[(Personaje_Cactus_Valores.Posicion_Y-70)/5][(Personaje_Cactus_Valores.Posicion_X-5)/5] != 'X'){
                    Personaje_Cactus_Valores.Posicion_Y -=80;
                    Personaje_Cactus_Valores.Posicion_X -=10;
                }
                break;
            }
        }
    }
    Personaje_Cactus_Valores.Direccion=8;
    Dibujar_Personaje_Cactus(Personaje_Cactus_Valores);
    return Personaje_Cactus_Valores;
}

void Dibujar_Personaje_Cactus(_entidad Personaje_Cactus_Valores){
    blit(Cactus_bmp,Cactus, 0,0,0,0,20,25);
    draw_sprite(buffer,Cactus,Personaje_Cactus_Valores.Posicion_X,Personaje_Cactus_Valores.Posicion_Y);
}

void borrar(_entidad Personaje_Cactus_Valores){
            if(Montana[(Personaje_Cactus_Valores.Posicion_Y-10)/5][(Personaje_Cactus_Valores.Posicion_X-10)/5] == 'X'){
                Montana[(Personaje_Cactus_Valores.Posicion_Y-10)/5][Personaje_Cactus_Valores.Posicion_X/5] = ' ';
                Montana[(Personaje_Cactus_Valores.Posicion_Y-10)/5][(Personaje_Cactus_Valores.Posicion_X-5)/5] = ' ';
                Montana[(Personaje_Cactus_Valores.Posicion_Y-10)/5][(Personaje_Cactus_Valores.Posicion_X-10)/5] = ' ';
            }
            if(Montana[(Personaje_Cactus_Valores.Posicion_Y-10)/5][(Personaje_Cactus_Valores.Posicion_X-5)/5] == 'X'){
                Montana[(Personaje_Cactus_Valores.Posicion_Y-10)/5][Personaje_Cactus_Valores.Posicion_X/5] = ' ';
                Montana[(Personaje_Cactus_Valores.Posicion_Y-10)/5][(Personaje_Cactus_Valores.Posicion_X-5)/5] = ' ';
                Montana[(Personaje_Cactus_Valores.Posicion_Y-10)/5][(Personaje_Cactus_Valores.Posicion_X+5)/5] = ' ';
            }
            if(Montana[(Personaje_Cactus_Valores.Posicion_Y-10)/5][Personaje_Cactus_Valores.Posicion_X/5] == 'Z'){
                Montana[(Personaje_Cactus_Valores.Posicion_Y-10)/5][Personaje_Cactus_Valores.Posicion_X/5] = ' ';
                Montana[(Personaje_Cactus_Valores.Posicion_Y-10)/5][(Personaje_Cactus_Valores.Posicion_X+5)/5] = ' ';
                Montana[(Personaje_Cactus_Valores.Posicion_Y-10)/5][(Personaje_Cactus_Valores.Posicion_X+10)/5] = ' ';
            }
}
