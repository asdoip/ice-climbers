#include <stdio.h>
#include <allegro.h>
#include <time.h>

#define MAX_ALTURA_nivel_1 69
#define MAX_ANCHURA  34
#define MAX_ALTURA_nivel_2 82
#define ALTURA_REAL  36
#define DOS 2
#define TRES 3
#define NUEVE 9
#define SEIS 6
#define OCHO 8
#define CINCO 5
#define CUATRO 4

struct _entidad_nave{   /*structuras*/
int Direccion_Nave,Posicion_X_Parte_1,Posicion_Y_Parte_1,Posicion_X_Parte_2,Posicion_Y_Parte_2,Posicion_X_Parte_3,Posicion_Y_Parte_3,m,ganar;
};
struct _entidad{
int Direccion,Posicion_X,Posicion_Y,m,u,b,imp,c,t,l,cont,r,f,perdida,Punt;
};
struct ranking{
    char Nombre[TRES];
    int Puntaj;
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

char Montana_Real[ALTURA_REAL][MAX_ANCHURA];


void Dibujar_Montana();        /*dibujadores*/
_entidad Ascenso_Montana(_entidad Personaje_Cactus_Valores,char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA]);
void Replicador_de_Mapa(FILE *Mapa_en_Texto,int desicion,char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA],char Montana_de_Respaldo[MAX_ALTURA_nivel_1][MAX_ANCHURA]);
void Dibujar_Montana_2(char Montana[MAX_ALTURA_nivel_2][MAX_ANCHURA]);        /*dibujadores*/
_entidad Ascenso_Montana_2(_entidad Personaje_Cactus_Valores,char Montana[MAX_ALTURA_nivel_2][MAX_ANCHURA]);
void Replicador_de_Mapa_2(FILE *Mapa_en_Texto,int desicion,char Montana[MAX_ALTURA_nivel_2][MAX_ANCHURA],char Montana_de_Respaldo[MAX_ALTURA_nivel_2][MAX_ANCHURA]);
void Pantalla();
void Dibujar_Personaje_Cactus(_entidad Personaje_Cactus_Valores);
void Dibujar_Enemigo_Murcielago(_entidad Enemigo_Murcielago_Valores);
void Dibujar_Aliado_Nave_Espacial(_entidad_nave Nave_Espacial);
void Dibujar_Enemigo_Pez(_entidad Enemigo_Pez_Valores_Numero_);
void Redibujador(_entidad Personaje_Cactus_Valores,char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA]);
void Redibujador_2(_entidad Personaje_Cactus_Valores, char Montana_2[MAX_ALTURA_nivel_2][MAX_ANCHURA]);
void Dibujar_Nube(_entidad_nave Nube);
_entidad Sprite_Personaje(_entidad Personaje_Cactus_valores);
void Todas_las_Posiciones(int Control_de_Reinicio,int Puntaje,FILE *Ranking,SAMPLE *W,SAMPLE *F,SAMPLE *ciclo,SAMPLE *MENU);


_entidad Enemigo_Pez_Rutina(_entidad Enemigo_Pez_Valores_Numero_1,_entidad Personaje_Cactus_Valores,int desicion); /*movimiento*/
_entidad Enemigo_Murcielago_Rutina(_entidad Enemigo_Murcielago_Valores,_entidad Personaje_Cactus_Valores);
_entidad_nave Aliado_Nave_Espacial_Rutina(_entidad_nave Nave_Espacial,_entidad Personaje_Cactus_Valores);
_entidad Personaje_Cactus_Rutina(_entidad Personaje_Cactus_Valores,_entidad_nave Nube[TRES],int desicion,char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA],SAMPLE *LADRILLO,SAMPLE *FRUTA);
_entidad_nave Nube_rutina(_entidad_nave Nube);

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


void Todas_las_Posiciones(int Control_de_Reinicio,int Puntaje,FILE *Ranking,SAMPLE *W,SAMPLE *F,SAMPLE *ciclo,SAMPLE *MENU){
    int p=0,h=0,u=0,i=0,j=0,k=0,aux=0,auxl[TRES];
    char In=0;
    if(Control_de_Reinicio==1){
            stop_sample(ciclo);
    play_sample(F,200,0,1000,0);
        while(!key[KEY_R]){
    clear_to_color(buffer,0x000000);
    textout_centre(buffer, font,"perdiste, presione r para reiniciar",300, 80, 0x3BFF14);
    textout_centre(buffer, font,"presione ESC para salir",300, 130, 0x3BFF14);
    blit(buffer,screen,0,0,0,0,660,700);
    if(key[KEY_ESC]){
        break;
    }
    }
    }
    if(Control_de_Reinicio==2){
        play_sample(W,200,0,1000,0);
        clear_to_color(buffer,0x000000);
            ranking _uno;
            char ran[SEIS][CUATRO];
            int Nran[SEIS];
            rewind(Ranking);
            while(!feof(Ranking)){
                fscanf(Ranking,"%c",&In);
                if(In=='\n'){
                    i++;
                    j=0;
                }
                if(In!='\n'){
                    if(j==4){
                        Nran[i]=In;
                    }
                    else{
                    ran[i][j]=In;
                    }
                    j++;
                }
            }
            _uno.Puntaj=Puntaje;
            _uno.Nombre[0]=65;
            _uno.Nombre[1]=65;
            _uno.Nombre[2]=65;
                while(!key[KEY_R] && p<3){
                    if(u<70){
                        u++;
                    }
    clear_to_color(buffer,0x000000);
    textout_centre(buffer, font,"Inserte su Alias",300, 80, 0x3BFF14);
        textout_centre(buffer, font,"_ _ _",300, 232, 0x3BFF14);
            textprintf_centre(buffer, font,300, 230, 0x3BFF14,"%c %c %c",_uno.Nombre[0],_uno.Nombre[1],_uno.Nombre[2]);
                     blit(buffer,screen,0,0,0,0,660,700);
        if(key[KEY_RIGHT] && u==70){
            _uno.Nombre[h]++;
            u=0;
            play_sample(MENU,50,0,1000,0);
        }
        if(key[KEY_LEFT] && u==70){
            _uno.Nombre[h]--;
            u=0;
            play_sample(MENU,50,0,1000,0);
        }
        if(key[KEY_ENTER] && u==70){
            p++;
            h++;
            u=0;
            play_sample(MENU,200,0,1000,0);
        }
    }
for(h=0;h<TRES;h++){
ran[5][h]=_uno.Nombre[h];
}
Nran[5]=_uno.Puntaj;
for(h=0;h<NUEVE;h++){
for(i=0;i<CINCO;i++){
    k=i+1;
    if(Nran[i]<Nran[k]){
        aux=Nran[k];
        Nran[k]=Nran[i];
        Nran[i]=aux;
        for(j=0;j<TRES;j++){
        auxl[j]=ran[k][j];
        ran[k][j]=ran[i][j];
        ran[i][j]=auxl[j];
        }
    }
}
}
while(!key[KEY_C]){
clear_to_color(buffer,0x000000);
textout_centre(buffer, font,"Ranking",330, 60, 0x3BFF14);
textprintf_centre(buffer, font,300, 90, 0x3BFF14,"1.- %c %c %c...........................................%d p",ran[0][0],ran[0][1],ran[0][2],Nran[0]);
textprintf_centre(buffer, font,300, 100, 0x3BFF14,"2.- %c %c %c...........................................%d p",ran[1][0],ran[1][1],ran[1][2],Nran[1]);
textprintf_centre(buffer, font,300, 110, 0x3BFF14,"3.- %c %c %c...........................................%d p",ran[2][0],ran[2][1],ran[2][2],Nran[2]);
textprintf_centre(buffer, font,300, 120, 0x3BFF14,"4.- %c %c %c...........................................%d p",ran[3][0],ran[3][1],ran[3][2],Nran[3]);
textprintf_centre(buffer, font,300, 130, 0x3BFF14,"5.- %c %c %c...........................................%d p",ran[4][0],ran[4][1],ran[4][2],Nran[4]);
textout_centre(buffer, font,"Presione C para continuar",300,500, 0x3BFF14);
blit(buffer,screen,0,0,0,0,660,700);
}
i=0;
j=0;
rewind(Ranking);
for(i=0;i<SEIS;i++){
        for(j=0;j<SEIS;j++){
            if(j==5){
                In='\n';
            }
            if(j==4){
                In=Nran[i];
            }
            if(j<4){
                In=ran[i][j];
            }
            fputc(In,Ranking);
        }
}
        while(!key[KEY_R]){
            clear_to_color(buffer,0x000000);
            textout_centre(buffer, font,"Ganaste, presione r para reiniciar",300, 100, 0x3BFF14);
            textout_centre(buffer, font,"presione ESC para salir",300, 130, 0x3BFF14);
            blit(buffer,screen,0,0,0,0,660,700);
            stop_sample(W);
        if(key[KEY_ESC]){
            break;
        }
    }
}
}



_entidad Enemigo_Pez_Rutina(_entidad Enemigo_Pez_Valores_Numero_1,_entidad Personaje_Cactus_Valores,int desicion){    /*movimiento*/
        if(Enemigo_Pez_Valores_Numero_1.Posicion_Y>660){}
        else{
        if(Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][Enemigo_Pez_Valores_Numero_1.Posicion_X/20] != 'X' || Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][Enemigo_Pez_Valores_Numero_1.Posicion_X/20] !='Y' || Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][Enemigo_Pez_Valores_Numero_1.Posicion_X/20] !='Z'){
            Enemigo_Pez_Valores_Numero_1.Posicion_Y +=15;
        }
        if(Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][Enemigo_Pez_Valores_Numero_1.Posicion_X/20] == 'X' || Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][Enemigo_Pez_Valores_Numero_1.Posicion_X/20] =='Y' || Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][Enemigo_Pez_Valores_Numero_1.Posicion_X/20] == 'Z'){
            Enemigo_Pez_Valores_Numero_1.Posicion_Y -=15;
    switch(desicion){
        case 1: {
    if(Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X+20)/20] != 'X' || Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X+20)/20] == 'Y' || Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X+20)/20] == 'Z'){
        Enemigo_Pez_Valores_Numero_1.Direccion=0;
    }
    if(Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X-20)/20] != 'X' || Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X-20)/20] == 'Y' || Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X-20)/20] == 'Z'){
        Enemigo_Pez_Valores_Numero_1.Direccion=1;
    }
        }
        case 2: {
    if(Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X+20)/20] == 'Z'){
        Enemigo_Pez_Valores_Numero_1.Direccion=0;
    }
    if(Montana_Real[Enemigo_Pez_Valores_Numero_1.Posicion_Y/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X-20)/20] == 'Z'){
        Enemigo_Pez_Valores_Numero_1.Direccion=1;
    }
        }
    }
    Enemigo_Pez_Valores_Numero_1.m++;
    if(Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X+20)/20] == 'X' && Enemigo_Pez_Valores_Numero_1.Direccion==1 && Enemigo_Pez_Valores_Numero_1.m == 10 || Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X+20)/20] == 'Y' && Enemigo_Pez_Valores_Numero_1.Direccion==1 && Enemigo_Pez_Valores_Numero_1.m==10 || Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X+20)/20] == 'Z' && Enemigo_Pez_Valores_Numero_1.Direccion==1 && Enemigo_Pez_Valores_Numero_1.m==10){
            Enemigo_Pez_Valores_Numero_1.Posicion_X +=5;
        }
        if(Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X-20)/20] == 'X' && Enemigo_Pez_Valores_Numero_1.Direccion==0 && Enemigo_Pez_Valores_Numero_1.m == 10 || Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X-20)/20]== 'Y' && Enemigo_Pez_Valores_Numero_1.Direccion==0 && Enemigo_Pez_Valores_Numero_1.m == 10 || Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X-20)/20]== 'Z' && Enemigo_Pez_Valores_Numero_1.Direccion==0 && Enemigo_Pez_Valores_Numero_1.m == 10){
            Enemigo_Pez_Valores_Numero_1.Posicion_X -=5;
        }
        }
        if(Enemigo_Pez_Valores_Numero_1.m==20){
            Enemigo_Pez_Valores_Numero_1.m=0;
        }
Dibujar_Enemigo_Pez(Enemigo_Pez_Valores_Numero_1);
if(Enemigo_Pez_Valores_Numero_1.Posicion_Y == (Personaje_Cactus_Valores.Posicion_Y+15) && Enemigo_Pez_Valores_Numero_1.Posicion_X == Personaje_Cactus_Valores.Posicion_X){
    Enemigo_Pez_Valores_Numero_1.perdida=1;
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
    Enemigo_Murcielago_Valores.perdida=1;
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
    Nave_Espacial.ganar=1;
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



_entidad Ascenso_Montana(_entidad Personaje_Cactus_Valores,char Montana[ALTURA_REAL][MAX_ANCHURA]){
    int i=0,j=0,z,u;
    z=ALTURA_REAL-1;
    for(i=z;i>0;i--){
        for(j=0;j<MAX_ANCHURA;j++){
            u=i+Personaje_Cactus_Valores.m;
            Montana_Real[i][j]=Montana[u][j];
            if(Montana_Real[i][j]=='U' && Personaje_Cactus_Valores.Posicion_X==0 && Personaje_Cactus_Valores.Posicion_Y==0){
                Personaje_Cactus_Valores.Posicion_X=20*j;
                Personaje_Cactus_Valores.Posicion_Y=15*i;
                Personaje_Cactus_Valores.Posicion_Y -=15;
            }
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

void Replicador_de_Mapa(FILE *Mapa_en_Texto,int desicion,char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA],char Montana_de_Respaldo[MAX_ALTURA_nivel_1][MAX_ANCHURA]){
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
    for(i=0;i<MAX_ALTURA_nivel_1;i++){
        for(j=0;j<MAX_ANCHURA;j++){
            Montana_de_Respaldo[i][j]=Montana[i][j];
        }
    }
}

void Redibujador(_entidad Personaje_Cactus_Valores,char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA]){
    int i,j,z,u;
    z=ALTURA_REAL-1;
    for(i=z;i>0;i--){
        for(j=0;j<MAX_ANCHURA;j++){
            u=i+Personaje_Cactus_Valores.m;
            Montana[u][j]=Montana_Real[i][j];
        }
    }
}



_entidad Personaje_Cactus_Rutina(_entidad Personaje_Cactus_Valores,_entidad_nave Nube, int desicion,char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA],char Montana_2[MAX_ALTURA_nivel_2][MAX_ANCHURA],SAMPLE *LADRILLO,SAMPLE *FRUTA){
    if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20] == 'X'){
        Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20] =' ';
        play_sample(LADRILLO,150,0,1000,0);
        Personaje_Cactus_Valores.Punt +=15;
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
    if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Z' && Personaje_Cactus_Valores.t>60 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Z' && Personaje_Cactus_Valores.t==45 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Z' && Personaje_Cactus_Valores.t<60){
    Personaje_Cactus_Valores.t=0;
    }
    if(Personaje_Cactus_Valores.f<4){
        Personaje_Cactus_Valores.f++;
    }
    if(Personaje_Cactus_Valores.f==4){
        if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20] !='C' && Personaje_Cactus_Valores.t < Personaje_Cactus_Valores.c && Personaje_Cactus_Valores.l==1 && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20] !='X' && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20] !='Z'){
            Personaje_Cactus_Valores.Posicion_Y--;
            Personaje_Cactus_Valores.t++;
        }
        if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]!='Y' && Personaje_Cactus_Valores.l==0 && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]!='X' && (Personaje_Cactus_Valores.Posicion_Y+30)!=Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_1!=Personaje_Cactus_Valores.Posicion_X && (Personaje_Cactus_Valores.Posicion_Y+30)!=Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_2!=Personaje_Cactus_Valores.Posicion_X && (Personaje_Cactus_Valores.Posicion_Y+30)!=Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_3!=Personaje_Cactus_Valores.Posicion_X && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20] !='Z' || (Personaje_Cactus_Valores.Posicion_Y+30)==Nube.Posicion_Y_Parte_1 && Personaje_Cactus_Valores.l==0){
            Personaje_Cactus_Valores.Posicion_Y++;
            Personaje_Cactus_Valores.t--;
        }
        Personaje_Cactus_Valores.f=0;
    }
    if(Personaje_Cactus_Valores.c==Personaje_Cactus_Valores.t && Personaje_Cactus_Valores.l==1 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20]=='X' && Personaje_Cactus_Valores.l==1 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20]=='C' && Personaje_Cactus_Valores.l==1 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Z' && Personaje_Cactus_Valores.l==1){
        Personaje_Cactus_Valores.l=0;
    }
    if(Personaje_Cactus_Valores.u<40){
        Personaje_Cactus_Valores.u++;
    }
    Personaje_Cactus_Valores.Direccion=4;
    if(Personaje_Cactus_Valores.u==40){
        if(key[KEY_RIGHT]) Personaje_Cactus_Valores.Direccion=3;
        if(key[KEY_LEFT]) Personaje_Cactus_Valores.Direccion=7;
        if(Personaje_Cactus_Valores.Direccion==0 || Personaje_Cactus_Valores.Direccion==3 || Personaje_Cactus_Valores.Direccion==7){
            Personaje_Cactus_Valores.u=0;
        }
        if(Personaje_Cactus_Valores.b<2){
            Personaje_Cactus_Valores.b++;
        }
        if(Personaje_Cactus_Valores.b==2){
            if(key[KEY_UP]){
                    Personaje_Cactus_Valores.Direccion=1;
            Personaje_Cactus_Valores.b=0;
        }
    }
    }
    switch(Personaje_Cactus_Valores.Direccion){
        case 1:{
            if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='X' || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Y' || Personaje_Cactus_Valores.l==2 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Z' || Personaje_Cactus_Valores.t==0){
                Personaje_Cactus_Valores.l=1;
                Personaje_Cactus_Valores.c=60;
                switch(desicion){
                case 1:{
                    Redibujador(Personaje_Cactus_Valores,Montana);
                    break;
                }
                case 2:{
                    Redibujador_2(Personaje_Cactus_Valores,Montana_2);
                    break;
                }
                }
            }
            break;
        }
        case 3:{
            if(Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X+20)/20] != 'Z' && Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X+20)/20] != 'X' && Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X+20)/20] != 'Y' && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][(Personaje_Cactus_Valores.Posicion_X+20)/20] != 'Z' && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][(Personaje_Cactus_Valores.Posicion_X+20)/20] != 'X' && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][(Personaje_Cactus_Valores.Posicion_X+20)/20] != 'Y'){
                Personaje_Cactus_Valores.Posicion_X +=20;
            break;
            }
        }
        case 7:{
            if(Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'Z' && Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'X' && Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'Y' && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'Z' && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'X' && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'Y'){
                Personaje_Cactus_Valores.Posicion_X -=20;
            break;
            }
        }
    }
    if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][Personaje_Cactus_Valores.Posicion_X/20]=='F'){
        Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][Personaje_Cactus_Valores.Posicion_X/20]=' ';
        play_sample(FRUTA,150,0,1000,0);
        Personaje_Cactus_Valores.Punt +=100;
    }
    Dibujar_Personaje_Cactus(Personaje_Cactus_Valores);
    return Personaje_Cactus_Valores;
}



_entidad Ascenso_Montana_2(_entidad Personaje_Cactus_Valores,char Montana_2[MAX_ALTURA_nivel_2][MAX_ANCHURA]){
    int i=0,j=0,z,u;
    z=ALTURA_REAL-1;
    for(i=z;i>0;i--){
        for(j=0;j<MAX_ANCHURA;j++){
            u=i+Personaje_Cactus_Valores.m;
            Montana_Real[i][j]=Montana_2[u][j];
            if(Montana_Real[i][j]=='U' && Personaje_Cactus_Valores.Posicion_X==0 && Personaje_Cactus_Valores.Posicion_Y==0){
                Personaje_Cactus_Valores.Posicion_X=20*j;
                Personaje_Cactus_Valores.Posicion_Y=15*i;
                Personaje_Cactus_Valores.Posicion_Y -=15;
            }
        }
    }
    return Personaje_Cactus_Valores;
    }


void Replicador_de_Mapa_2(FILE *Mapa_en_Texto,int desicion,char Montana_2[MAX_ALTURA_nivel_2][MAX_ANCHURA],char Montana_de_Respaldo_2[MAX_ALTURA_nivel_2][MAX_ANCHURA]){
char Intermediario;
int i=0,j=0;
while(!feof(Mapa_en_Texto)){
    fscanf(Mapa_en_Texto,"%c",&Intermediario);
    if(Intermediario=='\n'){
     i++;
     j=0;
    }
    if(Intermediario!='\n'){
    Montana_2[i][j]=Intermediario;
    j++;
    }
}
    for(i=0;i<MAX_ALTURA_nivel_2;i++){
        for(j=0;j<MAX_ANCHURA;j++){
            Montana_de_Respaldo_2[i][j]=Montana_2[i][j];
        }
    }
}

void Redibujador_2(_entidad Personaje_Cactus_Valores,char Montana_2[MAX_ALTURA_nivel_2][MAX_ANCHURA]){
    int i,j,z,u;
    z=ALTURA_REAL-1;
    for(i=z;i>0;i--){
        for(j=0;j<MAX_ANCHURA;j++){
            u=i+Personaje_Cactus_Valores.m;
            Montana_2[u][j]=Montana_Real[i][j];
        }
    }
}
