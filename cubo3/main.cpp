#include <stdio.h>
#include <allegro.h>
#include <time.h>

#define MAXAL  38
#define MAXANC  37

BITMAP *buffer;  /*espacios en el mapa*/
BITMAP *me3;
BITMAP *me2;
BITMAP *cacbmp;
BITMAP *cactus;
BITMAP *pez2;
BITMAP *pezbmp;
BITMAP *aave;
BITMAP *avebmp;
BITMAP *nave1;
BITMAP *nave1bmp;
BITMAP *nave2;
BITMAP *nave2bmp;
BITMAP *nave3;
BITMAP *nave3bmp;
BITMAP *palabra;

struct _ju{         /*structuras*/
int dir,x,y;
};
struct _jux{
int dir,x1,y1,x2,y2,x3,y3;
};
struct _max{
    _ju pez;
    _ju ave;
    _ju j;
    _jux ovni;
};

int c=0;       /*controlador de cerrado*/

void dibujar_mot(_ju p);        /*dibujadores*/
void pantalla();
void imagina_cactus(_ju p);
void diave(_ju a);
void dinave1(_jux n);
void dipez(_ju pp);
_max estado(_ju p,_ju pp,_ju a,_jux n);

void per();             /*Pantallas*/
void win();

_ju pez(_ju pp,_ju p); /*movimiento*/
_ju ave(_ju a,_ju p);
_jux ovni(_jux n,_ju p);
_ju j(_ju p);

char mot[MAXAL][MAXANC]{                /*mapa*/
"O                               O",
"                                 ",
"                                 ",
"                                 ",
"YYYYYYYYYXXXXXXXXXXXXXXXYYYYYYYYY",
"YYYYYYYY                 YYYYYYYY",
"YYYYYYYY                 YYYYYYYY",
"YYYYYYYY                 YYYYYYYY",
"YYYYYYYYXXXXXXXXXXXXXXXXXYYYYYYYY",
"YYYYYYY                   YYYYYYY",
"YYYYYYY                   YYYYYYY",
"YYYYYYY                   YYYYYYY",
"YYYYYYYXXXXXXXXXXXXXXXXXXXYYYYYYY",
"YYYYYY                     YYYYYY",
"YYYYYY                     YYYYYY",
"YYYYYY                     YYYYYY",
"YYYYYYXXXXXXXXXXXXXXXXXXXXXYYYYYY",
"YYYYY                       YYYYY",
"YYYYY                       YYYYY",
"YYYYY                       YYYYY",
"YYYYYXXXXXXXXXXXXXXXXXXXXXXXYYYYY",
"YYYY                         YYYY",
"YYYY                         YYYY",
"YYYY                         YYYY",
"YYYYXXXXXXXXXXXXXXXXXXXXXXXXXYYYY",
"YYY                           YYY",
"YYY                           YYY",
"YYY                           YYY",
"YYYXXXXXXXXXXXXXXXXXXXXXXXXXXXYYY",
"YY                             YY",
"YY                             YY",
"YY                             YY",
"YYXXXXXXXXXXXXXXXXXXXXXXXXXXXXXYY",
"Y                               Y",
"Y                               Y",
"Y                               Y",
"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
};

void dibujar_mot(_ju p){        /*dibujadores*/
    int r,c;
    for(c=0;c<MAXAL;c++){
        for(r=0;r<MAXANC;r++){
            if(mot[c][r]=='X'){
                draw_sprite(buffer, me3, r*20, c*15);
                if(p.x/20 == r && (p.y-15)/15 == c){
                    mot[c][r] = ' ';
                }
            }
            if(mot[c][r]=='Y'){
                draw_sprite(buffer, me2, r*20, c*15);
            }
        }
    }
}
void pantalla(){
    blit(buffer, screen, 0,0,0,0,660,570);
}
void imagina_cactus(_ju p){
    blit(cacbmp,cactus, p.dir*20,0,0,0,20,15);
    draw_sprite(buffer,cactus,p.x,p.y);
}
void diave(_ju a){
    blit(avebmp,aave, 0*20,0,0,0,20,15);
    draw_sprite(buffer,aave,a.x,a.y);
}
void dinave1(_jux n){
    blit(nave1bmp,nave1, 0*20,0,0,0,20,15);
    draw_sprite(buffer,nave1,n.x1,n.y1);
    blit(nave2bmp,nave2, 1*20,0,0,0,20,15);
    draw_sprite(buffer,nave2,n.x2,n.y2);
    blit(nave3bmp,nave3, 2*20,0,0,0,20,15);
    draw_sprite(buffer,nave3,n.x3,n.y3);
}
void dipez(_ju pp){
    blit(pezbmp,pez2, pp.dir*20,0,0,0,20,15);
    draw_sprite(buffer,pez2,pp.x,pp.y);
}

void per(){     /*ganar, perder*/
    c=1;
}
void win(){
    c=2;
}
_max estado(_ju p,_ju pp,_ju a,_jux n){
    _max m;
    if(c==1){
    while(!key[KEY_R]){
    clear_to_color(buffer,0x000000);
    textout_centre(buffer, font,"perdiste, presione r para reiniciar",300, 100, 0x3BFF14);
    textout_centre(buffer, font,"presione ESC para salir",300, 130, 0x3BFF14);
    blit(buffer,screen,0,0,0,0,660,570);
    if(key[KEY_ESC]){
        break;
    }
    }
    }
    if(c==2){
    while(!key[KEY_R]){
    clear_to_color(buffer,0x000000);
    textout_centre(buffer, font,"Ganaste, presione r para reiniciar",300, 100, 0x3BFF14);
    textout_centre(buffer, font,"presione ESC para salir",300, 130, 0x3BFF14);
    blit(buffer,screen,0,0,0,0,660,570);
    if(key[KEY_ESC]){
        break;
    }
    }
}
            m.j.x=100;
            m.j.y=495;
            m.pez.dir=0;
            m.pez.x=100;
            m.pez.y=375;
            m.ave.x=200;
            m.ave.y=200;
            m.ovni.x1=40;
            m.ovni.x2=60;
            m.ovni.x3=80;
            m.ovni.y1=0;
            m.ovni.y2=0;
            m.ovni.y3=0;
        return m;
}

_ju pez(_ju pp,_ju p){                                                       /*movimiento*/
        if(mot[pp.y/15][pp.x/20] != 'X' || mot[pp.y/15][pp.x/20] !='Y'){
            pp.y +=15;
        }
        if(mot[pp.y/15][pp.x/20] == 'X' || mot[pp.y/15][pp.x/20] =='Y'){
            pp.y -=15;
    if(mot[(pp.y+15)/15][(pp.x+20)/20] != 'X' || mot[pp.y/15][(pp.x+20)/20] == 'Y'){
        pp.dir=0;
        pp.x -=10;
    }
    if(mot[(pp.y+15)/15][(pp.x-20)/20] != 'X' || mot[pp.y/15][(pp.x-20)/20] == 'Y'){
        pp.dir=1;
        pp.x +=10;
    }
    if(mot[(pp.y+15)/15][(pp.x+20)/20] == 'X' && pp.dir==1 || mot[(pp.y+15)/15][(pp.x+20)/20] == 'Y' && pp.dir==1){
            pp.x +=10;
        }
        if(mot[(pp.y+15)/15][(pp.x-20)/20] == 'X' && pp.dir==0 || mot[(pp.y+15)/15][(pp.x-20)/20]== 'Y' && pp.dir==0){
            pp.x -=10;
        }
        }
dipez(pp);
if(pp.y == p.y && pp.x == p.x){
    per();
    }
return pp;
};
_ju ave(_ju a,_ju p){
    if(a.x < p.x && a.y < p.y){
            a.x +=5;
            a.y +=5;
    }
    if(a.x > p.x && a.y > p.y){
            a.x -=5;
            a.y -=5;
    }
    if(a.x > p.x && a.y < p.y){
            a.x -=5;
            a.y +=5;
    }
    if(a.x < p.x && a.y > p.y){
            a.x +=5;
            a.y -=5;
    }
    if(a.x < p.x && a.y==p.y){
            a.x +=5;
    }
    if(a.x > p.x && a.y==p.y){
            a.x -=5;
    }
    if(a.y < p.y && a.x==p.x){
            a.y +=5;
    }
    if(a.y > p.y && a.x==p.x){
            a.y -=5;
    }
diave(a);
if(a.y == p.y && a.x == p.x){
    per();
    }
return a;
}
_jux ovni(_jux n,_ju p){
        if(mot[n.y3/15][(n.x3+20)/20] == 'O'){
            n.dir=0;
        }
        if(mot[n.y1/15][(n.x1-20)/20] == 'O'){
            n.dir=1;
        }
        if(n.dir==1){
            n.x1++;
            n.x2++;
            n.x3++;
        }
        if(n.dir==0){
            n.x1--;
            n.x2--;
            n.x3--;
        }
    dinave1(n);
    if(n.y2 == p.y && n.x2 == p.x){
    win();
    }
    return n;
};
_ju j(_ju p){
        if(mot[(p.y+15)/15][p.x/20] != 'X' || mot[(p.y+15)/15][p.x/20] !='Y'){
            p.dir=1;
            p.y +=15;
        }
        if(mot[p.y/15][p.x/20] == 'X' || mot[p.y/15][p.x/20] =='Y'){
            p.y -=15;
        if(key[KEY_RIGHT]) p.dir=3;
        if(key[KEY_LEFT]) p.dir=7;
        if(key[KEY_UP]) p.dir=0;
        if(key[KEY_UP] && key[KEY_RIGHT]) p.dir=4;
        if(key[KEY_UP] && key[KEY_LEFT]) p.dir=6;
        if(p.dir==4){
            if(mot[(p.y-15)/15][(p.x+20)/20] != 'Y'){
            if(mot[(p.y-45)/15][p.x/20] == 'X'){
            p.y -=30;
            rest(40);
            }
            else{
            p.y -=60;
            rest(40);
            }
            p.x +=20;
        }
        }
        if(p.dir==6){
            if(mot[(p.y-15)/15][(p.x-20)/20] != 'Y' && mot[(p.y-15)/15][p.x/20] != 'Y'){
            if(mot[(p.y-45)/15][p.x/20] == 'X'){
            p.y -=30;
            rest(40);
            }
            else{
            p.y -=60;
            rest(40);
            }
            p.x -=20;
        }
        }
        if(p.dir==0){
            if(mot[(p.y-15)/15][p.x/20] != 'Y'){
            if(mot[(p.y-45)/15][p.x/20] == 'X'){
            p.y -=30;
            rest(40);
            }
            else{
            p.y -=60;
            rest(40);
            }
        }
        }
        if(p.dir==3){
            if(mot[p.y/15][(p.x+20)/20] != 'Y'){
            p.x +=20;
            }
        }
        if(p.dir==7){
            if(mot[p.y/15][(p.x-20)/20] != 'Y'){
            p.x -=20;
            }
        }
        }
        return p;
}

int main(){                     /*funcion principal*/
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,660,570,0,0);
    buffer= create_bitmap(660,570);
    me3=load_bitmap("me3.bmp",NULL);
    me2=load_bitmap("me2.bmp",NULL);
    cacbmp=load_bitmap("cactus.bmp",NULL);
    cactus=create_bitmap(20,15);
    pezbmp=load_bitmap("pez2.bmp",NULL);
    pez2=create_bitmap(20,15);
    avebmp=load_bitmap("ave.bmp",NULL);
    aave=create_bitmap(20,15);
    nave1bmp=load_bitmap("nave.bmp",NULL);
    nave1=create_bitmap(20,15);
    nave2bmp=load_bitmap("nave.bmp",NULL);
    nave2=create_bitmap(20,15);
    nave3bmp=load_bitmap("nave.bmp",NULL);
    nave3=create_bitmap(20,15);

    clear_to_color(buffer,0x000000);           /*Pantalla de inicio*/
    while(!key[KEY_K]){
    textout_centre(buffer, font,"presione k para iniciar",300, 100, 0x3BFF14);
    textout_centre(buffer, font,"presione ESC para salir",300, 130, 0x3BFF14);
    blit(buffer,screen,0,0,0,0,660,570);
    if(key[KEY_ESC]){
    return 0;
    }
    }
    _ju p; /*catus*/
    p.dir=0;
    p.x=80;
    p.y=495;

    _ju pp;     /*pez*/
    pp.dir=0;
    pp.x=100;
    pp.y=375;

    _ju a;     /*ave*/
    a.dir=0;
    a.x=200;
    a.y=200;

    _jux n;    /*ovni*/
    n.dir=0;
    n.x1=40;
    n.x2=60;
    n.x3=80;
    n.y1=0;
    n.y2=0;
    n.y3=0;

    _max m;

    while(!key[KEY_ESC]){      /*ciclo sin fin*/
        p=j(p);
        clear(buffer);
        imagina_cactus(p);
        pp=pez(pp,p);
        a=ave(a,p);
        n=ovni(n,p);
        dibujar_mot(p);
        pantalla();
        m=estado(p,pp,a,n);
        if(c>0){
            p.dir=m.j.dir;
            p.x=m.j.x;
            p.y=m.j.y;
            pp.dir=m.pez.dir;
            pp.x=m.pez.x;
            pp.y=m.pez.y;
            a.x=m.ave.x;
            a.y=m.ave.y;
            n.x1=m.ovni.x1;
            n.x2=m.ovni.x2;
            n.x3=m.ovni.x3;
            n.y1=m.ovni.y1;
            n.y2=m.ovni.y2;
            n.y3=m.ovni.y3;
            c=0;
        }
        rest(40);
        clear(cactus);
        }
    return 0;
}
END_OF_MAIN();
