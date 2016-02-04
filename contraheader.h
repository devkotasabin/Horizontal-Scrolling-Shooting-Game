#ifndef CONTRAHEADER_H_INCLUDED
#define CONTRAHEADER_H_INCLUDED

#include <allegro.h>
#include "mappyal.h"
#include <ctime>
#include <cstdlib>

#define MODE GFX_AUTODETECT_FULLSCREEN
#define WIDTH 640
#define HEIGHT 480
#define DELAY 10

#define HERO 0
#define ENEMY 1
#define HELPER 2
#define AMMO 3

#define LEFT 1
#define RIGHT 2
#define UP 3

#define FIRERIGHT 0
#define FIRERIGHTUP 1
#define FIREUP 2
#define FIRELEFTUP 3
#define FIRELEFT 4

#define BOMBRADIUS 80

#define PISTOL 0
#define GUN 1
#define ROCKET 2
#define BOMB 3

#define PISTOLDELAY 20
#define GUNDELAY 15
#define ROCKETDELAY 25
#define BOMBDELAY 30

extern const char* TARMABMP[6];

extern const int  TARMAMAX[6];
#define  TARMAWIDTH 50
extern const int TARMAHEIGHT[6];

#define  TARMADYING 0
#define  TARMASHOWINGUP 1
#define  TARMARIGHT 2
#define  TARMALEFT 3
#define  TARMACELEBRATING 4
#define  TARMACROUCHING 5

#define MAXBOMBERS 5

extern const char* REBELBMP[5];

extern const int  REBELMAX[5];
#define  REBELWIDTH 50
extern const int  REBELHEIGHT[5];


#define  REBELSOLDIER 0
#define  REBELUP 1
#define  REBELLEFT 2
#define  REBELRIGHT 3
#define  REBELDYING 4
/*extern const int mapheight;
extern const int mapblockheight;
extern const int mapwidth;
extern const int mapblockwidth;
*/
extern volatile int counter,mils;
extern volatile int ticks;
extern volatile int framerate;
extern BITMAP* buffer, * welcome,* instruction1,* instruction2,* instruction3,* gameoverscreen;;
extern int scores,gameover,lastjump;
extern int mapxoff,mapyoff;
extern SAMPLE* level1;
//extern int powerup,lastpowerup;



class character{
    public:
        int x,y,alive,lives,lastx,lasty;
        int type1,type2;
        int bullettype,bombs;
        int hitpoints;
        int facing;
        int jumpfactor;
        int firedirection;
        bool crouch,jump;
        int width,height;
        int velx,vely;
        int xdelay,ydelay;
        int xcount,ycount;
        int curframe,totalframes,animdir;
        int framecount,framedelay;
        int firedelay,lastcount;

        void setcharacter(int x1,int y1, int lives1, int tp1,int tp2,int width1,int height1,int tfr,int vx,int vy, int xdel, int ydel,int hp,int al){
            x=x1;
            y=y1;
            lastx=0;
            lasty=0;
            alive=al;       lives=lives1;   type1=tp1;  type2=tp2;
            bullettype= PISTOL;
            hitpoints=hp;
            facing=RIGHT;
            jumpfactor=0;
            firedirection=FIRERIGHT;
            crouch=jump=false;
            width=width1;   height=height1;
            velx=vx;     vely=vy;
            xdelay=xdel;   ydelay=ydel;
            xcount=ycount=0;
            curframe=0;
            totalframes=tfr;
            animdir=1;
            framecount=0;
            framedelay=50;
            firedelay=1;
            lastcount=0;
            bombs=20;
        }

        void animate(){

            if(++xcount>xdelay){
                xcount=0;
                x+=velx;
            }
            if(++ycount>ydelay){
                ycount=0;
                y+=vely;
            }
            if(++framecount>framedelay){
                framecount=0;
                if(animdir==1){
                    if(++curframe==totalframes && type2!=TARMADYING && type2!=REBELDYING )
                        curframe=0;
                    else    curframe=totalframes-1;
                }
                else if(animdir==-1){
                    if(--curframe<0)
                        curframe=totalframes-1;
            }
        }
        }
};

class hero:public character{
    public:
        BITMAP* heroimg[6][20];
        void draw(){
            if(((type2==TARMACROUCHING)|| type2==TARMASHOWINGUP) && facing==LEFT)
                draw_sprite_h_flip(buffer,heroimg[type2][curframe],x-mapxoff,y-mapyoff);
            else    draw_sprite(buffer,heroimg[type2][curframe],x-mapxoff,y-mapyoff);
        }


};

class enemybitmaps{
    private:

    public:
        BITMAP* enemyimg[5][12];


};


extern enemybitmaps enemypics;

class enemy:public character {
    public:

        void draw(){

            draw_sprite(buffer,enemypics.enemyimg[type2][curframe],x-mapxoff,y-mapyoff);
        }
};

class bomberbitmaps{
    public:
        BITMAP* bomber[14];
};
extern bomberbitmaps bomberpics;
class bomber:public character{
    public:
            void draw(){
                if(type2==REBELDYING)    draw_sprite(buffer,enemypics.enemyimg[type2][curframe],x-mapxoff,y-mapyoff);
                else if(facing==LEFT)    draw_sprite_h_flip(buffer,bomberpics.bomber[curframe],x-mapxoff,y-mapyoff);
                else if(facing==RIGHT)    draw_sprite(buffer,bomberpics.bomber[curframe],x-mapxoff,y-mapyoff);
            }
};
class bulletbmp{
    private:

    public:
        BITMAP* bullets[4];




};


extern bulletbmp bulletpics;

class bullet{
    public:
        int x,y,alive;
        int type;
        int direction;
        int damagept;
        int speed;
        bool jump;
        int velx,vely;
        int width,height;
        int xdelay,ydelay;
        int xcount,ycount;
        int firecount, firedelay,jumpfactor;

        void draw(){
            if(direction==FIRERIGHT)draw_sprite(buffer,bulletpics.bullets[type],x-mapxoff,y-mapyoff);
            else    draw_sprite_h_flip(buffer,bulletpics.bullets[type],x-mapxoff,y-mapyoff);
        }
        void setbullet(int x1,int y1,int tp, int dir, int spd, int wid, int ht, int dp,int al){
            x=x1;   y=y1;   type=tp;    direction=dir;  speed= spd; width=wid; height=ht;
            xcount=ycount=0;    xdelay=ydelay=0;
            damagept=dp;    alive=al;   firecount=firedelay=0;
            velx=vely=0;
            jump=false;
            jumpfactor=40;
        }
};
extern int inputflag,lastinput;
extern int checkpointx,checkpointy;

extern hero tarma;
extern enemy* bulldogs;
extern bomber* bombman;
extern bullet* pistols;
extern bullet* gun;
extern bullet* bomb;
extern bullet* rocket;
extern int pistolcount,guncount,bombcount,rocketcount;

int collided(int x, int y);
BITMAP* grabframe(BITMAP* source, int width, int height, int startx, int starty, int columns, int frame);
int initialize();
int loadplayer();
int inside(int x, int y, int x1, int x2, int y1, int y2);
int met(int x1,int y1,int x2, int y2, int w1, int w2,int h1, int h2);
void firebullet(int type);
void checkinputs();
void fireathero(int i);
int initialize();
int collided(int x, int y);
int loadplayer();
int loadenemy();
int loadpistol( );
void updatehero();
void resetplayer();
void updateenemy(int& spawn);
void updatebullets();
void displaystats();
void updatedeaths();
void firebomb();
void firebombathero(int n);
int loadbomber();
int loadbomb( );
void updatebombers(int& spawn);
void updatebombs();

#endif // CONTRAHEADER_H_INCLUDED
