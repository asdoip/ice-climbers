#include <stdio.h>
#include <allegro.h>
#include <time.h>

#define MAXAL  36
#define MAXANC  34
#define dos 2

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
struct _jun{
int r,c;
};

int z=0;       /*controlador de cerrado*/
char mot[MAXAL][MAXANC];

void dibujar_mot();        /*dibujadores*/
void lector();
void pantalla();
void imagina_cactus(_ju p);
void diave(_ju a);
void dinave1(_jux n);
void dipez(_ju pp);
_max estado(_ju p,_ju pp,_ju pp2,_ju a,_jux n);

void per();             /*Pantallas*/
void win();

void re(int nu);

_ju pez(_ju pp,_ju p); /*movimiento*/
_ju ave(_ju a,_ju p);
_jux ovni(_jux n,_ju p);
_ju j(_ju p);

FILE *fl = fopen("mapa1.txt","r+t");

int main(){                     /*funcion principal*/
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,660,540,0,0);
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
    clear(buffer);
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
    pp.x=300;
    pp.y=105;

    _ju pp2;     /*pez2*/
    pp.dir=0;
    pp.x=300;
    pp.y=210;

    _ju a;     /*ave*/
    a.dir=0;
    a.x=300;
    a.y=100;

    _jux n;    /*ovni*/
    n.dir=0;
    n.x1=40;
    n.x2=60;
    n.x3=80;
    n.y1=0;
    n.y2=0;
    n.y3=0;

    _jun esp;
    _max t;
    lector();
    while(!key[KEY_ESC]){      /*ciclo sin fin*/
        p=j(p);
        dibujar_mot();
        imagina_cactus(p);
        pp=pez(pp,p);
        printf("a");
        pp2=pez(pp2,p);
        a=ave(a,p);
        n=ovni(n,p);
        pantalla();
        t=estado(p,pp,pp2,a,n);
        if(z>0){
            p.x=t.j.x;
            p.y=t.j.y;
            pp.x=t.pez.x;
            pp.y=t.pez.y;
            a.x=t.ave.x;
            a.y=t.ave.y;
            n.x1=t.ovni.x1;
            n.x2=t.ovni.x2;
            n.x3=t.ovni.x3;
            n.y1=t.ovni.y1;
            n.y2=t.ovni.y2;
            n.y3=t.ovni.y3;
            z=0;
        }
        clear(buffer);
    }
    return 0;
}
END_OF_MAIN();

void dibujar_mot(){        /*dibujadores*/
    int r,c;
    for(c=0;c<MAXAL;c++){
        for(r=0;r<MAXANC;r++){
            if(mot[c][r]=='X'){
                draw_sprite(buffer, me3, r*20, c*15);
            }
            if(mot[c][r]=='Y'){
                draw_sprite(buffer, me2, r*20, c*15);
            }
        }
    }
}

void lector(){
char a;
int c=0,r=0;
while(!feof(fl)){
    fscanf(fl,"%c",&a);
    if(a=='\n'){
     c++;
     r=0;
    }
    if(a!='\n' && a!='n'){
    mot[c][r]=a;
    r++;
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
    z=1;
}
void win(){
    z=2;
}
void re(int nu){
    int v;
    for(v=0;v<nu;v++){
    rest(8);
    }
}
_max estado(_ju p,_ju pp,_ju pp2,_ju a,_jux n){
    _max t;
    if(z==1){
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
    if(z==2){
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
            t.j.x=100;
            t.j.y=495;
            t.pez.dir=0;
            t.pez.x=100;
            t.pez.y=375;
            t.ave.x=200;
            t.ave.y=200;
            t.ovni.x1=40;
            t.ovni.x2=60;
            t.ovni.x3=80;
            t.ovni.y1=0;
            t.ovni.y2=0;
            t.ovni.y3=0;
        return t;
}


_ju j(_ju p){
        int tres=3;
        re(tres);
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
            re(tres);
            if(mot[(p.y-15)/15][(p.x+20)/20] != 'Y'){
            if(mot[(p.y-45)/15][p.x/20] == 'X'){
            p.y -=30;
            mot[(p.y-15)/15][(p.x+20)/20] = ' ';
            }
            else{
            p.y -=60;
            }
            p.x +=20;
        }
        }
        if(p.dir==6){
            re(tres);
            if(mot[(p.y-15)/15][(p.x-20)/20] != 'Y' && mot[(p.y-15)/15][p.x/20] != 'Y'){
            if(mot[(p.y-45)/15][p.x/20] == 'X'){
            p.y -=30;
            mot[(p.y-15)/15][(p.x-20)/20] = ' ';
            }
            else{
            p.y -=60;
            }
            p.x -=20;
        }
        }
        if(p.dir==0){
            re(tres);
            if(mot[(p.y-15)/15][p.x/20] != 'Y'){
            if(mot[(p.y-45)/15][p.x/20] == 'X'){
            p.y -=30;
            mot[(p.y-15)/15][p.x/20] = ' ';
            }
            else{
            p.y -=60;
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

_ju pez(_ju pp,_ju p){    /*movimiento*/
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
