#include <stdio.h>
#include <allegro.h>
#include <time.h>

#define MAX_ALTURA_nivel_1 69
#define MAX_ANCHURA  34
#define MAX_ALTURA_nivel_2 82
#define ALTURA_REAL  36
#define ALTURA_REAL_MENOS_UNO 35
#define DOS 2
#define TRES 3
#define NUEVE 9
#define SEIS 6
#define OCHO 8
#define CINCO 5
#define CUATRO 4
#define UNO 1

struct _entidad_nave{   /*structuras*/
    int Direccion_Nave,Posicion_X_Parte_1,Posicion_Y_Parte_1,Posicion_X_Parte_2,Posicion_Y_Parte_2,Posicion_X_Parte_3,Posicion_Y_Parte_3,contador,ganar;
};
struct _entidad{
    int Direccion,Posicion_X,Posicion_Y,medidor_de_altura,contador,contador_secundario,impresion,altura_maxima_de_salto,contador_de_altura,bloque_inferior,contador_terciario,indicador_de_perdida,puntos,estado_y,estado_x;
};
struct ranking{
    char Nombre[TRES];
    int Puntaj;
};
struct posicion{
int x,y;
};
BITMAP *buffer;                  /*espacios en el mapa*/

char Montana_Real[ALTURA_REAL][MAX_ANCHURA];


void Dibujar_Montana(BITMAP *Ladrillo_Amarillo,BITMAP *Ladrillo_Azul,BITMAP *Fruta);        /*dibujadores*/
_entidad Ascenso_Montana(_entidad Personaje_Cactus_Valores,char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA]);
void Replicador_de_Mapa(FILE *Mapa_en_Texto,int desicion,char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA],char Montana_de_Respaldo[MAX_ALTURA_nivel_1][MAX_ANCHURA]);
void Dibujar_Montana_2(char Montana[MAX_ALTURA_nivel_2][MAX_ANCHURA]);        /*dibujadores*/
_entidad Ascenso_Montana_2(_entidad Personaje_Cactus_Valores,char Montana[MAX_ALTURA_nivel_2][MAX_ANCHURA]);
void Replicador_de_Mapa_2(FILE *Mapa_en_Texto,int desicion,char Montana[MAX_ALTURA_nivel_2][MAX_ANCHURA],char Montana_de_Respaldo[MAX_ALTURA_nivel_2][MAX_ANCHURA]);
void Pantalla();
void Dibujar_Personaje_Cactus(_entidad Personaje_Cactus_Valores,BITMAP *Personaje_Cactus_bmp,BITMAP *Personaje_Cactus);
void Dibujar_Enemigo_Murcielago(_entidad Enemigo_Murcielago_Valores,BITMAP *Enemigo_Murcielago_bmp,BITMAP *Enemigo_Murcielago);
void Dibujar_Aliado_Nave_Espacial(_entidad_nave Nave_Espacial,BITMAP *Aliado_Nave_Espacial_Parte_1,BITMAP *Aliado_Nave_Espacial_Parte_1_bmp,BITMAP *Aliado_Nave_Espacial_Parte_2,BITMAP *Aliado_Nave_Espacial_Parte_2_bmp,BITMAP *Aliado_Nave_Espacial_Parte_3,BITMAP *Aliado_Nave_Espacial_Parte_3_bmp);
void Dibujar_Enemigo_Pez(_entidad Enemigo_Pez_Valores_Numero_1,BITMAP *Enemigo_Pez,BITMAP *Enemigo_Pez_bmp);
void Redibujador(_entidad Personaje_Cactus_Valores,char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA]);
void Redibujador_2(_entidad Personaje_Cactus_Valores, char Montana_2[MAX_ALTURA_nivel_2][MAX_ANCHURA]);
void Dibujar_Nube(_entidad_nave Nube,BITMAP *Aliado_Nave_Espacial_Parte_1,BITMAP *Aliado_Nave_Espacial_Parte_1_bmp,BITMAP *Aliado_Nave_Espacial_Parte_2,BITMAP *Aliado_Nave_Espacial_Parte_2_bmp,BITMAP *Aliado_Nave_Espacial_Parte_3,BITMAP *Aliado_Nave_Espacial_Parte_3_bmp);
void Cambio_de_pantalla(int control_de_reinicio,int puntaje,FILE *Ranking,SAMPLE *sonido_de_ganar,SAMPLE *sonido_de_perdida,SAMPLE *sonido_ciclo,SAMPLE *sonido_de_menu_secundario);

int Revisar_subido_nuve(_entidad Personaje_Cactus_Valores , _entidad_nave Nube);

_entidad Enemigo_Pez_Rutina(_entidad Enemigo_Pez_Valores_Numero_1,_entidad Personaje_Cactus_Valores,int desicion,BITMAP *Enemigo_Pez,BITMAP *Enemigo_Pez_bmp); /*movimiento*/
_entidad Enemigo_Murcielago_Rutina(_entidad Enemigo_Murcielago_Valores,_entidad Personaje_Cactus_Valores,BITMAP *Enemigo_Murcielago_bmp,BITMAP *Enemigo_Murcielago);
_entidad_nave Aliado_Nave_Espacial_Rutina(_entidad_nave Nave_Espacial,_entidad Personaje_Cactus_Valores,BITMAP *Aliado_Nave_Espacial_Parte_1,BITMAP *Aliado_Nave_Espacial_Parte_1_bmp,BITMAP *Aliado_Nave_Espacial_Parte_2,BITMAP *Aliado_Nave_Espacial_Parte_2_bmp,BITMAP *Aliado_Nave_Espacial_Parte_3,BITMAP *Aliado_Nave_Espacial_Parte_3_bmp);
_entidad Personaje_Cactus_Rutina(_entidad Personaje_Cactus_Valores,_entidad_nave Nube,int desicion,char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA],SAMPLE *sonido_de_ruptura_de_ladrillo,SAMPLE *sonido_de_recoleccion_de_fruta,BITMAP *Personaje_Cactus_bmp,BITMAP *Personaje_Cactus,int revisador_nuve);
_entidad_nave Nube_rutina(_entidad_nave Nube,BITMAP *Nube_Parte_1,BITMAP *Nube_Parte_1_bmp,BITMAP *Nube_Parte_2,BITMAP *Nube_Parte_2_bmp,BITMAP *Nube_Parte_3,BITMAP *Nube_Parte_3_bmp);


void Pantalla(){
    blit(buffer, screen, 0,0,0,0,660,570);
}
void Dibujar_Personaje_Cactus(_entidad Personaje_Cactus_Valores,BITMAP *Personaje_Cactus_bmp,BITMAP *Personaje_Cactus){
    blit(Personaje_Cactus_bmp,Personaje_Cactus, Personaje_Cactus_Valores.impresion*20,0,0,0,20,30);
    draw_sprite(buffer,Personaje_Cactus,Personaje_Cactus_Valores.Posicion_X,Personaje_Cactus_Valores.Posicion_Y);
}
void Dibujar_Enemigo_Murcielago(_entidad Enemigo_Murcielago_Valores,BITMAP *Enemigo_Murcielago_bmp,BITMAP *Enemigo_Murcielago){
    blit(Enemigo_Murcielago_bmp,Enemigo_Murcielago, 0*20,0,0,0,20,15);
    draw_sprite(buffer,Enemigo_Murcielago,Enemigo_Murcielago_Valores.Posicion_X,Enemigo_Murcielago_Valores.Posicion_Y);
}
void Dibujar_Aliado_Nave_Espacial(_entidad_nave Nave_Espacial,BITMAP *Aliado_Nave_Espacial_Parte_1,BITMAP *Aliado_Nave_Espacial_Parte_1_bmp,BITMAP *Aliado_Nave_Espacial_Parte_2,BITMAP *Aliado_Nave_Espacial_Parte_2_bmp,BITMAP *Aliado_Nave_Espacial_Parte_3,BITMAP *Aliado_Nave_Espacial_Parte_3_bmp){
    blit(Aliado_Nave_Espacial_Parte_1_bmp,Aliado_Nave_Espacial_Parte_1, 0*20,0,0,0,20,15);
    draw_sprite(buffer,Aliado_Nave_Espacial_Parte_1,Nave_Espacial.Posicion_X_Parte_1,Nave_Espacial.Posicion_Y_Parte_1);
    blit(Aliado_Nave_Espacial_Parte_2_bmp,Aliado_Nave_Espacial_Parte_2, 1*20,0,0,0,20,15);
    draw_sprite(buffer,Aliado_Nave_Espacial_Parte_2,Nave_Espacial.Posicion_X_Parte_2,Nave_Espacial.Posicion_Y_Parte_2);
    blit(Aliado_Nave_Espacial_Parte_3_bmp,Aliado_Nave_Espacial_Parte_3, 2*20,0,0,0,20,15);
    draw_sprite(buffer,Aliado_Nave_Espacial_Parte_3,Nave_Espacial.Posicion_X_Parte_3,Nave_Espacial.Posicion_Y_Parte_3);
}
void Dibujar_Enemigo_Pez(_entidad Enemigo_Pez_Valores_Numero_1,BITMAP *Enemigo_Pez,BITMAP *Enemigo_Pez_bmp){
    blit(Enemigo_Pez_bmp,Enemigo_Pez, Enemigo_Pez_Valores_Numero_1.Direccion*20,0,0,0,20,15);
    draw_sprite(buffer,Enemigo_Pez,Enemigo_Pez_Valores_Numero_1.Posicion_X,Enemigo_Pez_Valores_Numero_1.Posicion_Y);
}
void Dibujar_Nube(_entidad_nave Nube,BITMAP *Nube_Parte_1,BITMAP *Nube_Parte_1_bmp,BITMAP *Nube_Parte_2,BITMAP *Nube_Parte_2_bmp,BITMAP *Nube_Parte_3,BITMAP *Nube_Parte_3_bmp){
    blit(Nube_Parte_1_bmp,Nube_Parte_1, 0*20,0,0,0,20,15);
    draw_sprite(buffer,Nube_Parte_1,Nube.Posicion_X_Parte_1,Nube.Posicion_Y_Parte_1);
    blit(Nube_Parte_2_bmp,Nube_Parte_2, 1*20,0,0,0,20,15);
    draw_sprite(buffer,Nube_Parte_2,Nube.Posicion_X_Parte_2,Nube.Posicion_Y_Parte_2);
    blit(Nube_Parte_3_bmp,Nube_Parte_3, 2*20,0,0,0,20,15);
    draw_sprite(buffer,Nube_Parte_3,Nube.Posicion_X_Parte_3,Nube.Posicion_Y_Parte_3);

}


void Cambio_de_pantalla(int Control_de_Reinicio,int puntaje,FILE *Ranking,SAMPLE *sonido_de_ganar,SAMPLE *sonido_de_perdida,SAMPLE *sonido_ciclo,SAMPLE *sonido_de_menu_secundario){
    int contador_p=0,contador=0,contador_u=0,contador_i=0,contador_j=0,contador_i_mas_uno=0,aux=0,auxl[TRES];
    char In=0;
    if(Control_de_Reinicio==1){
        stop_sample(sonido_ciclo);
        play_sample(sonido_de_perdida,200,0,1000,0);
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
        play_sample(sonido_de_ganar,200,0,1000,0);
        clear_to_color(buffer,0x000000);
        ranking _uno;
        char ran[SEIS][TRES];
        char Nran[SEIS];
        rewind(Ranking);
        while(!feof(Ranking)){
            fscanf(Ranking,"%c",&In);
            if(In=='\n'){
                contador_i++;
                contador_j=0;
            }
            if(In!='\n'){
                if(contador_j==4){
                    Nran[contador_i]=In;
                }
                else{
                    ran[contador_i][contador_j]=In;
                }
                contador_j++;
            }
        }
        _uno.Puntaj=puntaje;
        for(contador=0;contador<TRES;contador++){
        _uno.Nombre[0]=65;
        }
        while(contador_p<3){
            if(contador_u<70){
                contador_u++;
            }
            clear_to_color(buffer,0x000000);
            textout_centre(buffer, font,"Inserte su Alias",300, 80, 0x3BFF14);
            textout_centre(buffer, font,"_ _ _",300, 232, 0x3BFF14);
            textprintf_centre(buffer, font,300, 230, 0x3BFF14,"%c %c %c",_uno.Nombre[0],_uno.Nombre[1],_uno.Nombre[2]);
            blit(buffer,screen,0,0,0,0,660,700);
            if(key[KEY_RIGHT] && contador_u==70){
                _uno.Nombre[contador]++;
                contador_u=0;
                play_sample(sonido_de_menu_secundario,50,0,1000,0);
            }
            if(key[KEY_LEFT] && contador_u==70){
                _uno.Nombre[contador]--;
                contador_u=0;
                play_sample(sonido_de_menu_secundario,50,0,1000,0);
            }
            if(key[KEY_ENTER] && contador_u==70){
                contador_p++;
                contador++;
                contador_u=0;
                play_sample(sonido_de_menu_secundario,200,0,1000,0);
            }
        }
        for(contador=0;contador<TRES;contador++){
            ran[5][contador]=_uno.Nombre[contador];
        }
        Nran[5]=_uno.Puntaj;
        for(contador=0;contador<NUEVE;contador++){
            for(contador_i=0;contador_i<CINCO;contador_i++){
                contador_i_mas_uno=contador_i+1;
                if(Nran[contador_i]<Nran[contador_i_mas_uno]){
                    aux=Nran[contador_i_mas_uno];
                    Nran[contador_i_mas_uno]=Nran[contador_i];
                    Nran[contador_i]=aux;
                    for(contador_j=0;contador_j<TRES;contador_j++){
                        auxl[contador_j]=ran[contador_i_mas_uno][contador_j];
                        ran[contador_i_mas_uno][contador_j]=ran[contador_i][contador_j];
                        ran[contador_i][contador_j]=auxl[contador_j];
                    }
                }
            }
        }
        while(!key[KEY_C]){
            clear_to_color(buffer,0x000000);
            textout_centre(buffer, font,"Ranking",330, 60, 0x3BFF14);
            textprintf_centre(buffer, font,300, 90, 0x3BFF14,"1.- %c %c %c...........................................%d0 p",ran[0][0],ran[0][1],ran[0][2],Nran[0]);
            textprintf_centre(buffer, font,300, 100, 0x3BFF14,"2.- %c %c %c...........................................%d0 p",ran[1][0],ran[1][1],ran[1][2],Nran[1]);
            textprintf_centre(buffer, font,300, 110, 0x3BFF14,"3.- %c %c %c...........................................%d0 p",ran[2][0],ran[2][1],ran[2][2],Nran[2]);
            textprintf_centre(buffer, font,300, 120, 0x3BFF14,"4.- %c %c %c...........................................%d0 p",ran[3][0],ran[3][1],ran[3][2],Nran[3]);
            textprintf_centre(buffer, font,300, 130, 0x3BFF14,"5.- %c %c %c...........................................%d0 p",ran[4][0],ran[4][1],ran[4][2],Nran[4]);
            textout_centre(buffer, font,"Presione C para continuar",300,500, 0x3BFF14);
            blit(buffer,screen,0,0,0,0,660,700);
        }
        rewind(Ranking);
        for(contador_i=0;contador_i<SEIS;contador_i++){
            for(contador_j=0;contador_j<SEIS;contador_j++){
                if(contador_j==5){
                    In='\n';
                }
                if(contador_j==4){
                    In=Nran[contador_i];
                }
                if(contador_j<4){
                    In=ran[contador_i][contador_j];
                }
                fputc(In,Ranking);
            }
        }
        while(!key[KEY_R]){
            clear_to_color(buffer,0x000000);
            textout_centre(buffer, font,"Ganaste, presione r para reiniciar",300, 100, 0x3BFF14);
            textout_centre(buffer, font,"presione ESC para salir",300, 130, 0x3BFF14);
            blit(buffer,screen,0,0,0,0,660,700);
            stop_sample(sonido_de_ganar);
            if(key[KEY_ESC]){
                break;
            }
        }
    }
}



_entidad Enemigo_Pez_Rutina(_entidad Enemigo_Pez_Valores_Numero_1,_entidad Personaje_Cactus_Valores,int desicion,BITMAP *Enemigo_Pez,BITMAP *Enemigo_Pez_bmp){    /*movimiento*/
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
            Enemigo_Pez_Valores_Numero_1.medidor_de_altura++;
            if(Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X+20)/20] == 'X' && Enemigo_Pez_Valores_Numero_1.Direccion==1 && Enemigo_Pez_Valores_Numero_1.medidor_de_altura == 30 || Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X+20)/20] == 'Y' && Enemigo_Pez_Valores_Numero_1.Direccion==1 && Enemigo_Pez_Valores_Numero_1.medidor_de_altura==30 || Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X+20)/20] == 'Z' && Enemigo_Pez_Valores_Numero_1.Direccion==1 && Enemigo_Pez_Valores_Numero_1.medidor_de_altura==30){
                Enemigo_Pez_Valores_Numero_1.Posicion_X +=5;
            }
            if(Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X-20)/20] == 'X' && Enemigo_Pez_Valores_Numero_1.Direccion==0 && Enemigo_Pez_Valores_Numero_1.medidor_de_altura == 30 || Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X-20)/20]== 'Y' && Enemigo_Pez_Valores_Numero_1.Direccion==0 && Enemigo_Pez_Valores_Numero_1.medidor_de_altura ==30 || Montana_Real[(Enemigo_Pez_Valores_Numero_1.Posicion_Y+15)/15][(Enemigo_Pez_Valores_Numero_1.Posicion_X-20)/20]== 'Z' && Enemigo_Pez_Valores_Numero_1.Direccion==0 && Enemigo_Pez_Valores_Numero_1.medidor_de_altura==30){
                Enemigo_Pez_Valores_Numero_1.Posicion_X -=5;
            }
        }
        if(Enemigo_Pez_Valores_Numero_1.medidor_de_altura==30){
            Enemigo_Pez_Valores_Numero_1.medidor_de_altura=0;
        }
        Dibujar_Enemigo_Pez(Enemigo_Pez_Valores_Numero_1,Enemigo_Pez,Enemigo_Pez_bmp);
        if(Enemigo_Pez_Valores_Numero_1.Posicion_Y == (Personaje_Cactus_Valores.Posicion_Y+15) && Enemigo_Pez_Valores_Numero_1.Posicion_X == Personaje_Cactus_Valores.Posicion_X){
            Enemigo_Pez_Valores_Numero_1.indicador_de_perdida=1;
        }
    }
    return Enemigo_Pez_Valores_Numero_1;
};

_entidad Enemigo_Murcielago_Rutina(_entidad Enemigo_Murcielago_Valores,_entidad Personaje_Cactus_Valores,BITMAP *Enemigo_Murcielago_bmp,BITMAP *Enemigo_Murcielago){
    if(Enemigo_Murcielago_Valores.Posicion_Y>660){}
    else{
        Enemigo_Murcielago_Valores.medidor_de_altura++;
        if(Enemigo_Murcielago_Valores.Posicion_X > Personaje_Cactus_Valores.Posicion_X && Enemigo_Murcielago_Valores.medidor_de_altura==150){
            Enemigo_Murcielago_Valores.Posicion_X -=5;
            if(Enemigo_Murcielago_Valores.Posicion_Y > Personaje_Cactus_Valores.Posicion_Y){
                Enemigo_Murcielago_Valores.Posicion_Y -=5;
            }
            if(Enemigo_Murcielago_Valores.Posicion_Y < Personaje_Cactus_Valores.Posicion_Y){
                Enemigo_Murcielago_Valores.Posicion_Y +=5;
            }
        }
        if(Enemigo_Murcielago_Valores.Posicion_X < Personaje_Cactus_Valores.Posicion_X && Enemigo_Murcielago_Valores.medidor_de_altura==150){
            Enemigo_Murcielago_Valores.Posicion_X +=5;
            if(Enemigo_Murcielago_Valores.Posicion_Y < Personaje_Cactus_Valores.Posicion_Y){
                Enemigo_Murcielago_Valores.Posicion_Y +=5;
            }
            if(Enemigo_Murcielago_Valores.Posicion_Y > Personaje_Cactus_Valores.Posicion_Y){
                Enemigo_Murcielago_Valores.Posicion_Y -=5;
            }
        }
        if(Enemigo_Murcielago_Valores.Posicion_X==Personaje_Cactus_Valores.Posicion_X && Enemigo_Murcielago_Valores.medidor_de_altura==150){
            if(Enemigo_Murcielago_Valores.Posicion_Y < Personaje_Cactus_Valores.Posicion_Y){
                Enemigo_Murcielago_Valores.Posicion_Y +=5;
            }
            if(Enemigo_Murcielago_Valores.Posicion_Y > Personaje_Cactus_Valores.Posicion_Y){
                Enemigo_Murcielago_Valores.Posicion_Y -=5;
            }
        }
        if(Enemigo_Murcielago_Valores.Posicion_Y==Personaje_Cactus_Valores.Posicion_Y && Enemigo_Murcielago_Valores.medidor_de_altura==150){
            if(Enemigo_Murcielago_Valores.Posicion_X > Personaje_Cactus_Valores.Posicion_X){
                Enemigo_Murcielago_Valores.Posicion_X -=5;
            }
            if(Enemigo_Murcielago_Valores.Posicion_X < Personaje_Cactus_Valores.Posicion_X){
                Enemigo_Murcielago_Valores.Posicion_X +=5;
            }
        }
        if(Enemigo_Murcielago_Valores.medidor_de_altura==150){
            Enemigo_Murcielago_Valores.medidor_de_altura=0;
        }
        Dibujar_Enemigo_Murcielago(Enemigo_Murcielago_Valores,Enemigo_Murcielago_bmp,Enemigo_Murcielago);
        if(Enemigo_Murcielago_Valores.Posicion_Y == Personaje_Cactus_Valores.Posicion_Y && Enemigo_Murcielago_Valores.Posicion_X == Personaje_Cactus_Valores.Posicion_X){
            Enemigo_Murcielago_Valores.indicador_de_perdida=1;
        }
    }
    return Enemigo_Murcielago_Valores;
};

_entidad_nave Aliado_Nave_Espacial_Rutina(_entidad_nave Nave_Espacial,_entidad Personaje_Cactus_Valores,BITMAP *Aliado_Nave_Espacial_Parte_1,BITMAP *Aliado_Nave_Espacial_Parte_1_bmp,BITMAP *Aliado_Nave_Espacial_Parte_2,BITMAP *Aliado_Nave_Espacial_Parte_2_bmp,BITMAP *Aliado_Nave_Espacial_Parte_3,BITMAP *Aliado_Nave_Espacial_Parte_3_bmp){
    if(Montana_Real[Nave_Espacial.Posicion_Y_Parte_3/15][(Nave_Espacial.Posicion_X_Parte_3+20)/20] == 'O'){
        Nave_Espacial.Direccion_Nave=0;
    }
    if(Montana_Real[Nave_Espacial.Posicion_Y_Parte_1/15][(Nave_Espacial.Posicion_X_Parte_1-20)/20] == 'O'){
        Nave_Espacial.Direccion_Nave=1;
    }
    if(Nave_Espacial.contador<120){
        Nave_Espacial.contador++;
    }
    if(Nave_Espacial.contador==120){
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
        Nave_Espacial.contador=0;
    }
    Dibujar_Aliado_Nave_Espacial(Nave_Espacial,Aliado_Nave_Espacial_Parte_1,Aliado_Nave_Espacial_Parte_1_bmp,Aliado_Nave_Espacial_Parte_2,Aliado_Nave_Espacial_Parte_2_bmp,Aliado_Nave_Espacial_Parte_3,Aliado_Nave_Espacial_Parte_3_bmp);
    if(Nave_Espacial.Posicion_Y_Parte_2 == Personaje_Cactus_Valores.Posicion_Y && Nave_Espacial.Posicion_X_Parte_2 == Personaje_Cactus_Valores.Posicion_X){
        Nave_Espacial.ganar=1;
    }
    return Nave_Espacial;
};

_entidad_nave Nube_rutina(_entidad_nave Nube,BITMAP *Nube_Parte_1,BITMAP *Nube_Parte_1_bmp,BITMAP *Nube_Parte_2,BITMAP *Nube_Parte_2_bmp,BITMAP *Nube_Parte_3,BITMAP *Nube_Parte_3_bmp){
    if(Nube.contador<180){
        Nube.contador++;
    }
    if(Nube.contador==180){
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
        Nube.contador=0;
    }
    Dibujar_Nube(Nube,Nube_Parte_1,Nube_Parte_1_bmp,Nube_Parte_2,Nube_Parte_2_bmp,Nube_Parte_3,Nube_Parte_3_bmp);
    return Nube;
}



_entidad Ascenso_Montana(_entidad Personaje_Cactus_Valores,char Montana[ALTURA_REAL][MAX_ANCHURA]){
    int contador_i=0,contador_j=0,altura_menos_uno,avanse_al_final;
    altura_menos_uno=ALTURA_REAL-1;
    for(contador_i=altura_menos_uno;contador_i>0;contador_i--){
        for(contador_j=0;contador_j<MAX_ANCHURA;contador_j++){
            avanse_al_final=contador_i+Personaje_Cactus_Valores.medidor_de_altura;
            Montana_Real[contador_i][contador_j]=Montana[avanse_al_final][contador_j];
        }
    }
    return Personaje_Cactus_Valores;
}

void Dibujar_Montana(BITMAP *Ladrillo_Amarillo,BITMAP *Ladrillo_Azul,BITMAP *Fruta){        /*dibujadores*/
    int contador_i,contador_j;
    for(contador_i=0;contador_i<ALTURA_REAL;contador_i++){
        for(contador_j=0;contador_j<MAX_ANCHURA;contador_j++){
            if(Montana_Real[contador_i][contador_j]=='X'){
                draw_sprite(buffer, Ladrillo_Amarillo, contador_j*20, contador_i*15);
            }
            if(Montana_Real[contador_i][contador_j]=='Y'){
                draw_sprite(buffer, Ladrillo_Azul, contador_j*20, contador_i*15);
            }
            if(Montana_Real[contador_i][contador_j]=='C'){
                draw_sprite(buffer, Ladrillo_Azul, contador_j*20, contador_i*15);
            }
            if(Montana_Real[contador_i][contador_j]=='Z'){
                draw_sprite(buffer, Ladrillo_Azul, contador_j*20, contador_i*15);
            }
            if(Montana_Real[contador_i][contador_j]=='F'){
                draw_sprite(buffer, Fruta, contador_j*20, contador_i*15);
            }
        }
    }
}

void Replicador_de_Mapa(FILE *Mapa_en_Texto,int desicion,char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA],char Montana_de_Respaldo[MAX_ALTURA_nivel_1][MAX_ANCHURA]){
    char Intermediario;
    int contador_i=0,contador_j=0;
    while(!feof(Mapa_en_Texto)){
        fscanf(Mapa_en_Texto,"%c",&Intermediario);
        if(Intermediario=='\n'){
            contador_i++;
            contador_j=0;
        }
        if(Intermediario!='\n'){
            Montana[contador_i][contador_j]=Intermediario;
            contador_j++;
        }
    }
    for(contador_i=0;contador_i<MAX_ALTURA_nivel_1;contador_i++){
        for(contador_j=0;contador_j<MAX_ANCHURA;contador_j++){
            Montana_de_Respaldo[contador_i][contador_j]=Montana[contador_i][contador_j];
        }
    }
}

void Redibujador(_entidad Personaje_Cactus_Valores,char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA]){
    int contador_i,contador_j,altura_real_menos_uno,avanse_al_final;
    altura_real_menos_uno=ALTURA_REAL-1;
    for(contador_i=altura_real_menos_uno;contador_i>0;contador_i--){
        for(contador_j=0;contador_j<MAX_ANCHURA;contador_j++){
            avanse_al_final=contador_i+Personaje_Cactus_Valores.medidor_de_altura;
            Montana[avanse_al_final][contador_j]=Montana_Real[contador_i][contador_j];
        }
    }
}



_entidad Personaje_Cactus_Rutina(_entidad Personaje_Cactus_Valores,_entidad_nave Nube, int desicion,char Montana[MAX_ALTURA_nivel_1][MAX_ANCHURA],char Montana_2[MAX_ALTURA_nivel_2][MAX_ANCHURA],SAMPLE *sonido_de_ruptura_de_ladrillo,SAMPLE *sonido_de_recoleccion_de_fruta,BITMAP *Personaje_Cactus_bmp,BITMAP *Personaje_Cactus,int revisador_nuve){
    if(revisador_nuve>=0 && revisador_nuve<=2){
        Personaje_Cactus_Valores.bloque_inferior=2;
        Personaje_Cactus_Valores.contador_de_altura=0;
        Personaje_Cactus_Valores.estado_y=2;
        if(Nube.contador==2){
            if(Nube.Direccion_Nave==1 && Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X+20)/20]!='Z'){
                Personaje_Cactus_Valores.Posicion_X +=20;
            }
            if(Nube.Direccion_Nave==0 && Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X-20)/20]!='Z'){
                Personaje_Cactus_Valores.Posicion_X -=20;
            }
        }
    }
    if(Personaje_Cactus_Valores.bloque_inferior==2 && (Personaje_Cactus_Valores.Posicion_X>Nube.Posicion_X_Parte_3 || Personaje_Cactus_Valores.Posicion_X<Nube.Posicion_X_Parte_1)){
        Personaje_Cactus_Valores.bloque_inferior=0;
    }
   if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='X' && Personaje_Cactus_Valores.contador_de_altura>=60 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='X' && Personaje_Cactus_Valores.contador_de_altura==-105 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='X' && Personaje_Cactus_Valores.contador_de_altura<0){
        Personaje_Cactus_Valores.contador_de_altura=0;
        Personaje_Cactus_Valores.estado_y=2;
    }
    if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Y' && Personaje_Cactus_Valores.contador_de_altura>60 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Y' && Personaje_Cactus_Valores.contador_de_altura==45 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Y' && Personaje_Cactus_Valores.contador_de_altura<60){
        Personaje_Cactus_Valores.contador_de_altura=0;
        Personaje_Cactus_Valores.estado_y=2;
    }
    if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Z' && Personaje_Cactus_Valores.contador_de_altura>60 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Z' && Personaje_Cactus_Valores.contador_de_altura==45 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Z' && Personaje_Cactus_Valores.contador_de_altura<60){
        Personaje_Cactus_Valores.contador_de_altura=0;
        Personaje_Cactus_Valores.estado_y=2;
    }
    if(Personaje_Cactus_Valores.contador_terciario<6){
        Personaje_Cactus_Valores.contador_terciario++;
    }
    if(Personaje_Cactus_Valores.contador_terciario==6){
        if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20] !='C' && Personaje_Cactus_Valores.contador_de_altura < Personaje_Cactus_Valores.altura_maxima_de_salto && Personaje_Cactus_Valores.bloque_inferior==1 && Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][Personaje_Cactus_Valores.Posicion_X/20] !='X' && Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][Personaje_Cactus_Valores.Posicion_X/20] !='Z'){
            Personaje_Cactus_Valores.Posicion_Y--;
            Personaje_Cactus_Valores.contador_de_altura++;
            Personaje_Cactus_Valores.estado_y=1;
            switch(Personaje_Cactus_Valores.estado_x){
                case 0:{
                    Personaje_Cactus_Valores.impresion=7;
                    break;
                }
                case 1:{
                    Personaje_Cactus_Valores.impresion=1;
                    break;
                }
            }
        }
        if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]!='Y' && Personaje_Cactus_Valores.bloque_inferior==0 && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]!='X' && (Personaje_Cactus_Valores.Posicion_Y+30)!=Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_1!=Personaje_Cactus_Valores.Posicion_X && (Personaje_Cactus_Valores.Posicion_Y+30)!=Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_2!=Personaje_Cactus_Valores.Posicion_X && (Personaje_Cactus_Valores.Posicion_Y+30)!=Nube.Posicion_Y_Parte_1 && Nube.Posicion_X_Parte_3!=Personaje_Cactus_Valores.Posicion_X && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20] !='Z' || (Personaje_Cactus_Valores.Posicion_Y+30)==Nube.Posicion_Y_Parte_1 && Personaje_Cactus_Valores.bloque_inferior==0){
            Personaje_Cactus_Valores.Posicion_Y++;
            Personaje_Cactus_Valores.contador_de_altura--;
            Personaje_Cactus_Valores.estado_y=0;
            switch(Personaje_Cactus_Valores.estado_x){
                case 0:{
                    Personaje_Cactus_Valores.impresion=8;
                    break;
                }
                case 1:{
                    Personaje_Cactus_Valores.impresion=2;
                    break;
                }
            }
        }
        Personaje_Cactus_Valores.contador_terciario=0;
    }
    if(Personaje_Cactus_Valores.altura_maxima_de_salto==Personaje_Cactus_Valores.contador_de_altura && Personaje_Cactus_Valores.bloque_inferior==1 || Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][Personaje_Cactus_Valores.Posicion_X/20]=='X' && Personaje_Cactus_Valores.bloque_inferior==1 || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y-15)/15][Personaje_Cactus_Valores.Posicion_X/20]=='C' && Personaje_Cactus_Valores.bloque_inferior==1 || Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][Personaje_Cactus_Valores.Posicion_X/20]=='Z' && Personaje_Cactus_Valores.bloque_inferior==1){
        Personaje_Cactus_Valores.bloque_inferior=0;
    }
    if(Personaje_Cactus_Valores.contador<80){
        Personaje_Cactus_Valores.contador++;
    }
    Personaje_Cactus_Valores.Direccion=4;
    if(Personaje_Cactus_Valores.contador==80){
        if(key[KEY_RIGHT]){
            Personaje_Cactus_Valores.Direccion=3;
        }
        if(key[KEY_LEFT]){
                Personaje_Cactus_Valores.Direccion=7;
        }
        if(key[KEY_H]){
         Personaje_Cactus_Valores.Posicion_Y++;
        }
        if(Personaje_Cactus_Valores.Direccion==0 || Personaje_Cactus_Valores.Direccion==3 || Personaje_Cactus_Valores.Direccion==7){
            Personaje_Cactus_Valores.contador=0;
        }
            if(key[KEY_UP]){
                    Personaje_Cactus_Valores.Direccion=1;
                    Personaje_Cactus_Valores.contador_secundario=0;
            }
    }
    switch(Personaje_Cactus_Valores.Direccion){
        case 1:{
            if(Personaje_Cactus_Valores.bloque_inferior==2){
                Personaje_Cactus_Valores.Posicion_Y--;
                Personaje_Cactus_Valores.bloque_inferior=1;
                Personaje_Cactus_Valores.altura_maxima_de_salto=59;
            }
            if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='X' || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Y' || Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+30)/15][Personaje_Cactus_Valores.Posicion_X/20]=='Z'){
                Personaje_Cactus_Valores.bloque_inferior=1;
                Personaje_Cactus_Valores.altura_maxima_de_salto=60;
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
                Personaje_Cactus_Valores.estado_x=1;
                switch(Personaje_Cactus_Valores.estado_y){
                    case 0:{
                        Personaje_Cactus_Valores.impresion=2;
                        break;
                    }
                    case 1:{
                        Personaje_Cactus_Valores.impresion=1;
                        break;
                    }
                    case 2:{
                        Personaje_Cactus_Valores.impresion=0;
                        break;
                    }
                }
            }
            break;
        }
        case 7:{
            if(Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'Z' && Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'X' && Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'Y' && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'Z' && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'X' && Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][(Personaje_Cactus_Valores.Posicion_X-20)/20] != 'Y'){
                Personaje_Cactus_Valores.Posicion_X -=20;
                Personaje_Cactus_Valores.estado_x=0;
                switch(Personaje_Cactus_Valores.estado_y){
                    case 0:{
                        Personaje_Cactus_Valores.impresion=8;
                        break;
                    }
                    case 1:{
                        Personaje_Cactus_Valores.impresion=7;
                        break;
                    }
                    case 2:{
                        Personaje_Cactus_Valores.impresion=6;
                        break;
                    }
                }
            }
            break;
        }
    }
    if(Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][Personaje_Cactus_Valores.Posicion_X/20] == 'X'){
        Montana_Real[Personaje_Cactus_Valores.Posicion_Y/15][Personaje_Cactus_Valores.Posicion_X/20] =' ';
        play_sample(sonido_de_ruptura_de_ladrillo,150,0,1000,0);
        Personaje_Cactus_Valores.puntos +=1;
    }
    if(Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][Personaje_Cactus_Valores.Posicion_X/20]=='F'){
        Montana_Real[(Personaje_Cactus_Valores.Posicion_Y+15)/15][Personaje_Cactus_Valores.Posicion_X/20]=' ';
        play_sample(sonido_de_recoleccion_de_fruta,150,0,1000,0);
        Personaje_Cactus_Valores.puntos +=5;
    }
    Dibujar_Personaje_Cactus(Personaje_Cactus_Valores,Personaje_Cactus_bmp,Personaje_Cactus);
    return Personaje_Cactus_Valores;
}



_entidad Ascenso_Montana_2(_entidad Personaje_Cactus_Valores,char Montana_2[MAX_ALTURA_nivel_2][MAX_ANCHURA]){
    int contador_i=0,contador_j=0,altura_real_menos_uno,avanse_al_final;
    altura_real_menos_uno=ALTURA_REAL-1;
    for(contador_i=altura_real_menos_uno;contador_i>0;contador_i--){
        for(contador_j=0;contador_j<MAX_ANCHURA;contador_j++){
            avanse_al_final=contador_i+Personaje_Cactus_Valores.medidor_de_altura;
            Montana_Real[contador_i][contador_j]=Montana_2[avanse_al_final][contador_j];
        }
    }
    return Personaje_Cactus_Valores;
}


void Replicador_de_Mapa_2(FILE *Mapa_en_Texto,int desicion,char Montana_2[MAX_ALTURA_nivel_2][MAX_ANCHURA],char Montana_de_Respaldo_2[MAX_ALTURA_nivel_2][MAX_ANCHURA]){
    char Intermediario;
    int contador_i=0,contador_j=0;
    while(!feof(Mapa_en_Texto)){
        fscanf(Mapa_en_Texto,"%c",&Intermediario);
        if(Intermediario=='\n'){
            contador_i++;
            contador_j=0;
        }
        if(Intermediario!='\n'){
            Montana_2[contador_i][contador_j]=Intermediario;
            contador_j++;
        }
    }
    for(contador_i=0;contador_i<MAX_ALTURA_nivel_2;contador_i++){
        for(contador_j=0;contador_j<MAX_ANCHURA;contador_j++){
            Montana_de_Respaldo_2[contador_i][contador_j]=Montana_2[contador_i][contador_j];
        }
    }
}

void Redibujador_2(_entidad Personaje_Cactus_Valores,char Montana_2[MAX_ALTURA_nivel_2][MAX_ANCHURA]){
    int contador_i,contador_j,altura_real_menos_uno,avanse_al_final;
    for(contador_i=ALTURA_REAL_MENOS_UNO;contador_i>0;contador_i--){
        for(contador_j=0;contador_j<MAX_ANCHURA;contador_j++){
            avanse_al_final=contador_i+Personaje_Cactus_Valores.medidor_de_altura;
            Montana_2[avanse_al_final][contador_j]=Montana_Real[contador_i][contador_j];
        }
    }
}

int Revisar_subido_nuve(_entidad Personaje_Cactus_Valores , _entidad_nave Nube[]){
    int contador;
    for(contador=0;contador<TRES;contador++){
        if((Personaje_Cactus_Valores.Posicion_Y+30)==Nube[contador].Posicion_Y_Parte_1 && Personaje_Cactus_Valores.Posicion_X>=Nube[contador].Posicion_X_Parte_1 && Personaje_Cactus_Valores.Posicion_X<=(Nube[contador].Posicion_X_Parte_3+20)){
            return contador;
        }
    }
    return 3;
}
