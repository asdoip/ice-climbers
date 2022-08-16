#include <stdio.h>
#include <allegro.h>
#include <time.h>

#define MAX_ALTURA  70
#define MAX_ANCHURA  34
#define ALTURA_REAL  36
#define DOS 2
#define TRES 3

struct _entidad_nave{   /*structuras*/
int Direccion_Nave,Posicion_X_Parte_1,Posicion_Y_Parte_1,Posicion_X_Parte_2,Posicion_Y_Parte_2,Posicion_X_Parte_3,Posicion_Y_Parte_3,m;
};
struct _entidad{
int Direccion,Posicion_X,Posicion_Y,m,u,b,imp,c,t,l,cont,r,f;
};
struct _Reinicio{
    _entidad Personaje_Cactus_Valores;
    _entidad Enemigo_Murcielago_Valores;
    _entidad_nave Nave_Espacial;
};

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
void Dibujar_Enemigo_Pez(_entidad Enemigo_Pez_Valores_Numero_);
void Redibujador(_entidad Personaje_Cactus_Valores);
void Dibujar_Nube(_entidad_nave Nube);
_entidad Sprite_Personaje(_entidad Personaje_Cactus_valores);
_Reinicio Todas_las_Posiciones(_entidad Personaje_Cactus_Valores,_entidad Enemigo_Murcielago_Valores,_entidad_nave Nave_Espacial);

void Perdida();             /*Pantallas*/
void Ganancia();

_entidad Enemigo_Pez_Rutina(_entidad Enemigo_Pez_Valores_Numero_1,_entidad Personaje_Cactus_Valores); /*movimiento*/
_entidad Enemigo_Murcielago_Rutina(_entidad Enemigo_Murcielago_Valores,_entidad Personaje_Cactus_Valores);
_entidad_nave Aliado_Nave_Espacial_Rutina(_entidad_nave Nave_Espacial,_entidad Personaje_Cactus_Valores);
_entidad Personaje_Cactus_Rutina(_entidad Personaje_Cactus_Valores,_entidad_nave Nube[TRES]);
_entidad_nave Nube_rutina(_entidad_nave Nube);

FILE *Mapa_en_Texto = fopen("./mapas/mapa12.txt","r+t");

_entidad Ascenso_Montana(_entidad Personaje_Cactus_Valores){
    int i=0,j=0,f,z,u;
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
            if(Montana_Real[i][j]=='P'){
                draw_sprite(buffer, Ladrillo_Azul, j*20, i*15);
            }
            if(Montana_Real[i][j]=='C'){
                draw_sprite(buffer, Ladrillo_Azul, j*20, i*15);
            }
            if(Montana_Real[i][j]=='Z'){
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

_entidad Sprite_Personaje(_entidad Personaje_Cactus_valores){

}

void Pantalla(){
    blit(buffer, screen, 0,0,0,0,660,570);
}
void Dibujar_Personaje_Cactus(_entidad Personaje_Cactus_Valores){
    blit(Personaje_Cactus_bmp,Personaje_Cactus, Personaje_Cactus_Valores.imp*20,0,0,0,20,30);
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

_Reinicio Todas_las_Posiciones(_entidad Personaje_Cactus_Valores,_entidad Enemigo_Murcielago_Valores,_entidad_nave Nave_Espacial){
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
            Archivador.Personaje_Cactus_Valores.m=33;
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
    if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20] == 'X'){
        Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20] =' ';
    }
    if((Personaje_Cactus_Valores.Posicion_Y+30)==Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_1==Personaje_Cactus_Valores.Posicion_X || (Personaje_Cactus_Valores.Posicion_Y+30)==Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_2==Personaje_Cactus_Valores.Posicion_X || (Personaje_Cactus_Valores.Posicion_Y+30)==Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_3==Personaje_Cactus_Valores.Posicion_X){
        Personaje_Cactus_Valores.l=2;
        if(Nube.m==0 && Nube.Posicion_Y_Parte_1==(Personaje_Cactus_Valores.Posicion_Y+30)){
            if(Nube.Direccion_Nave==1 && Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X+20)/20]!='Z'){
                Personaje_Cactus_Valores.Posicion_X +=20;
            }
            if(Nube.Direccion_Nave==0 && Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X-20)/20]!='Z'){
                Personaje_Cactus_Valores.Posicion_X -=20;
            }
        }
    }
    if(Personaje_Cactus_Valores.l==2){
        Personaje_Cactus_Valores.t=0;
    }
    if(Personaje_Cactus_Valores.l==2 && Personaje_Cactus_Valores.Posicion_X!=Nube.Posicion_X_Parte_1 && Personaje_Cactus_Valores.Posicion_X!=Nube.Posicion_X_Parte_2 && Personaje_Cactus_Valores.Posicion_X!=Nube.Posicion_X_Parte_3 && (Personaje_Cactus_Valores.Posicion_Y+30)==Nube.Posicion_Y_Parte_1){
        Personaje_Cactus_Valores.l=0;
    }
    if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='X' && Personaje_Cactus_Valores.t>=60 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='X' && Personaje_Cactus_Valores.t==-105 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='X' && Personaje_Cactus_Valores.t<0){
        Personaje_Cactus_Valores.t=0;
    }
    if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Y' && Personaje_Cactus_Valores.t>=60 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Y' && Personaje_Cactus_Valores.t==45 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Y' && Personaje_Cactus_Valores.t<0){
        Personaje_Cactus_Valores.t=0;
    }
    if(Personaje_Cactus_Valores.f<2){
        Personaje_Cactus_Valores.f++;
    }
    if(Personaje_Cactus_Valores.f==2){
        if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20] !='C' && Personaje_Cactus_Valores.t < Personaje_Cactus_Valores.c && Personaje_Cactus_Valores.l==1 && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20] !='X'){
            Personaje_Cactus_Valores.Posicion_Y--;
            Personaje_Cactus_Valores.t++;
        }
        if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]!='Y' && Personaje_Cactus_Valores.l==0 && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]!='X' && Personaje_Cactus_Valores.l==0 && (Personaje_Cactus_Valores.Posicion_Y+30)!=Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_1!=Personaje_Cactus_Valores.Posicion_X && (Personaje_Cactus_Valores.Posicion_Y+30)!=Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_2!=Personaje_Cactus_Valores.Posicion_X && (Personaje_Cactus_Valores.Posicion_Y+30)!=Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_3!=Personaje_Cactus_Valores.Posicion_X){
            Personaje_Cactus_Valores.Posicion_Y++;
            Personaje_Cactus_Valores.t--;
        }
        Personaje_Cactus_Valores.f=0;
    }
    if(Personaje_Cactus_Valores.c==Personaje_Cactus_Valores.t && Personaje_Cactus_Valores.l==1 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20]=='X' && Personaje_Cactus_Valores.l==1 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20]=='C' && Personaje_Cactus_Valores.l==1){
        Personaje_Cactus_Valores.l=0;
    }
    if(Personaje_Cactus_Valores.u<50){
        Personaje_Cactus_Valores.u++;
    }
    Personaje_Cactus_Valores.Direccion=0;
    if(Personaje_Cactus_Valores.u==50){
        if(key[KEY_RIGHT]) Personaje_Cactus_Valores.Direccion=3;
        if(key[KEY_LEFT]) Personaje_Cactus_Valores.Direccion=7;
        if(Personaje_Cactus_Valores.Direccion==0 || Personaje_Cactus_Valores.Direccion==3 || Personaje_Cactus_Valores.Direccion==7){
            Personaje_Cactus_Valores.u=0;
        }
        if(Personaje_Cactus_Valores.b<2){
            Personaje_Cactus_Valores.b++;
        }
        if(Personaje_Cactus_Valores.b==2){
            if(key[KEY_UP])Personaje_Cactus_Valores.Direccion=1;
            Personaje_Cactus_Valores.b=0;
        }
    }

    switch(Personaje_Cactus_Valores.Direccion){
        case 1:{
            if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='X' || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Y' || Personaje_Cactus_Valores.l==2 && (Personaje_Cactus_Valores.Posicion_Y+30)==Nube.Posicion_Y_Parte_1){
                Personaje_Cactus_Valores.l=1;
                Personaje_Cactus_Valores.c=60;
                Redibujador(Personaje_Cactus_Valores);
            }
            break;
        }
        case 3:{
            if(Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X+20)/20] != 'Z' && Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X+20)/20] != 'X' && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][(Personaje_Cactus_Valores.Posicion_X+20)/20] != 'X'){
                Personaje_Cactus_Valores.Posicion_X +=20;
            break;
            }
        }
        case 7:{
            if(Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'Z' && Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'X' && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'X'){
                Personaje_Cactus_Valores.Posicion_X -=20;
            break;
            }
        }
    }
    if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][Personaje_Cactus_Valores.Posicion_X/20]=='F'){
        Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][Personaje_Cactus_Valores.Posicion_X/20]=' ';
    }
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
        if(Enemigo_Pez_Valores_Numero_1.m==20){
            Enemigo_Pez_Valores_Numero_1.m=0;
        }
Dibujar_Enemigo_Pez(Enemigo_Pez_Valores_Numero_1);
if(Enemigo_Pez_Valores_Numero_1.Posicion_Y == (Personaje_Cactus_Valores.Posicion_Y+15) && Enemigo_Pez_Valores_Numero_1.Posicion_X == Personaje_Cactus_Valores.Posicion_X){
    Perdida();
    }
        }
        return Enemigo_Pez_Valores_Numero_1;
};

_entidad Enemigo_Murcielago_Rutina(_entidad Enemigo_Murcielago_Valores,_entidad Personaje_Cactus_Valores){
    if(Enemigo_Murcielago_Valores.Posicion_Y>660){}
    else{
    Enemigo_Murcielago_Valores.m++;
    if(Enemigo_Murcielago_Valores.Posicion_X > Personaje_Cactus_Valores.Posicion_X && Enemigo_Murcielago_Valores.m==110){
            Enemigo_Murcielago_Valores.Posicion_X -=5;
    if(Enemigo_Murcielago_Valores.Posicion_Y > Personaje_Cactus_Valores.Posicion_Y){
            Enemigo_Murcielago_Valores.Posicion_Y -=5;
    }
    if(Enemigo_Murcielago_Valores.Posicion_Y < Personaje_Cactus_Valores.Posicion_Y){
            Enemigo_Murcielago_Valores.Posicion_Y +=5;
    }
    }
if(Enemigo_Murcielago_Valores.Posicion_X < Personaje_Cactus_Valores.Posicion_X && Enemigo_Murcielago_Valores.m==110){
            Enemigo_Murcielago_Valores.Posicion_X +=5;
	if(Enemigo_Murcielago_Valores.Posicion_Y < Personaje_Cactus_Valores.Posicion_Y){
            Enemigo_Murcielago_Valores.Posicion_Y +=5;
    	}
    if(Enemigo_Murcielago_Valores.Posicion_Y > Personaje_Cactus_Valores.Posicion_Y){
            Enemigo_Murcielago_Valores.Posicion_Y -=5;
    }
}
if(Enemigo_Murcielago_Valores.Posicion_X==Personaje_Cactus_Valores.Posicion_X && Enemigo_Murcielago_Valores.m==110){
    if(Enemigo_Murcielago_Valores.Posicion_Y < Personaje_Cactus_Valores.Posicion_Y){
            Enemigo_Murcielago_Valores.Posicion_Y +=5;
    }
    if(Enemigo_Murcielago_Valores.Posicion_Y > Personaje_Cactus_Valores.Posicion_Y){
            Enemigo_Murcielago_Valores.Posicion_Y -=5;
    }
}
if(Enemigo_Murcielago_Valores.Posicion_Y==Personaje_Cactus_Valores.Posicion_Y && Enemigo_Murcielago_Valores.m==110){
    if(Enemigo_Murcielago_Valores.Posicion_X > Personaje_Cactus_Valores.Posicion_X){
            Enemigo_Murcielago_Valores.Posicion_X -=5;
    }
    if(Enemigo_Murcielago_Valores.Posicion_X < Personaje_Cactus_Valores.Posicion_X){
            Enemigo_Murcielago_Valores.Posicion_X +=5;
    }
}
if(Enemigo_Murcielago_Valores.m==110){
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
        if(Nave_Espacial.m<80){
        Nave_Espacial.m++;
        }
        if(Nave_Espacial.m==80){
        if(Nave_Espacial.Direccion_Nave==1){
            Nave_Espacial.Posicion_X_Parte_1 +=20;
            Nave_Espacial.Posicion_X_Parte_2 +=20;
            Nave_Espacial.Posicion_X_Parte_3 +=20;
        }
        if(Nave_Espacial.Direccion_Nave==0){
            Nave_Espacial.Posicion_X_Parte_1 -=20;
            Nave_Espacial.Posicion_X_Parte_2 -=20;
            Nave_Espacial.Posicion_X_Parte_3 -=20;
        }
        Nave_Espacial.m=0;
        }
    Dibujar_Aliado_Nave_Espacial(Nave_Espacial);
    if(Nave_Espacial.Posicion_Y_Parte_2 == Personaje_Cactus_Valores.Posicion_Y && Nave_Espacial.Posicion_X_Parte_2 == Personaje_Cactus_Valores.Posicion_X){
    Ganancia();
    }
    return Nave_Espacial;
};

_entidad_nave Nube_rutina(_entidad_nave Nube){
        if(Nube.m<60){
        Nube.m++;
        }
        if(Nube.m==60){
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
            Nube.m=0;
        }
    Dibujar_Nube(Nube);
    return Nube;
}
