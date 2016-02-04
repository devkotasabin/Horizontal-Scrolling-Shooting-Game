#include "contraheader.h"


int collided(int x, int y){
    BLKSTR* blockdata;
    blockdata=MapGetBlock(x/mapblockwidth,y/mapblockheight);
    return blockdata->tl;
}
/*int collided(int x, int y){
    return(y>350)?1:0;
}*/

void timer1(){

    mils++;
    if(!(mils%10))
        counter++;
    framerate=ticks;
    ticks=0;

}
END_OF_FUNCTION(timer1)

BITMAP* grabframe(BITMAP* source, int width, int height, int startx, int starty, int columns, int frame){
    BITMAP* temp=create_bitmap(width, height);
    int x=startx+(frame%columns)*width;
    int y=starty+(frame/columns)*height;
    blit(source, temp, x, y, 0,0,width,height);
    return temp;
}

int initialize(){
    allegro_init();
    install_timer();
    install_keyboard();
    set_color_depth(16);
    set_gfx_mode(MODE,WIDTH,HEIGHT,0,0);
    srand(time(NULL));
    buffer=create_bitmap(SCREEN_W,SCREEN_H);
    clear(buffer);
    if(install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,"")!=0){
        allegro_message("Error initializing sound system");
        return 0;
    }
    welcome=load_bitmap("welcome.bmp",NULL);
     instruction1=load_bitmap("instruction1.bmp",NULL);
     instruction2=load_bitmap("instruction2.bmp",NULL);
      instruction3=load_bitmap("instruction3.bmp",NULL);
       gameoverscreen=load_bitmap("gameover.bmp",NULL);
       if(!welcome || !instruction2 || ! instruction3 || !instruction1 || ! gameoverscreen){
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("WELCOME BMPS MISSING");
        return 0;
       }
    //level1=load_sample("stage1.wav");
    /*if(!level1){
        allegro_message("No sound file");
        return 0;
    }*/
        if(MapLoad("level1.fmp")){
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Can't find level1.fmp");
        return 0;
    }
    LOCK_FUNCTION(timer1);
    LOCK_VARIABLE(ticks);
    LOCK_VARIABLE(framerate);
    LOCK_VARIABLE(counter);
    install_int(timer1,100);
    return 1;
}

volatile int counter,mils;
volatile int ticks;
volatile int framerate;
BITMAP* buffer, *welcome, *instruction1, *instruction2, *instruction3, *gameoverscreen;
SAMPLE* level1;
int scores,gameover;
int mapxoff,mapyoff;


enemybitmaps enemypics ;
bomberbitmaps bomberpics;
bulletbmp bulletpics ;

int lastjump=0;
int inputflag=1,lastinput=0;
int checkpointx,checkpointy;
//int powerup,lastpowerup;

hero tarma;
enemy* bulldogs =new enemy[20];
bullet* pistols = new bullet[50];
bullet* gun = new bullet;
bullet* bomb= new bullet[20];
bullet* rocket=new bullet;
bomber* bombman=new bomber[MAXBOMBERS];

int pistolcount,guncount,bombcount,rocketcount;

/*const int mapheight=20;
const int mapblockheight=32;
const int mapwidth=1500;
const int mapblockwidth=32;
*/
const char* REBELBMP[5]={"","","rebelsoldier.bmp","","rebelsoldierdying.bmp"};
const char* TARMABMP[6]={"tarmadying.bmp","tarmaup.bmp","tarmarunning.bmp","","tarmacelebrating.bmp","tarmacrouching.bmp"};
const int  REBELMAX[5]={12,12,11,11,8};
const int  REBELHEIGHT[5]={70,70,70,70,70};
const int TARMAHEIGHT[6]= {70,70,70,70,70,35};
const int  TARMAMAX[6]={19,10,12,12,4,4};




int main()
{
    if(!initialize())    return 1;
    int spawn, lastspawn=-1,spawnbomb,lastspawnbomb=-1;
    if(!loadplayer()) {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Can't load tarma");
        return 1;
    }
    if(!loadenemy()){
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Can't load bulldogs");
        return 1;
    }
    if(!loadpistol()){
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Can't load pistols");
        return 1;
    }
    if(!loadbomber()){
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Can't load bomber");
        return 1;
    }
    if(!loadbomb()){
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Can't load bomb");
        return 1;
    }

    /*if(!loadgun()){
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Can't load guns");
        return 1;
    }*/
    /*if(!loadboss()){
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Can't load boss");
        return 1;
    }*/
    //int volume=250,pan=128,pitch=1000;
    //play_sample(level1,volume,pan,pitch,TRUE);
    int intro=0,exits=0;
    while(!exits){
         intro=counter;
         while(counter-intro<2)
        blit(welcome,screen,0,0,0,0,WIDTH,HEIGHT);
        intro=counter;
        while(counter-intro<2)
        blit(instruction1,screen,0,0,0,0,WIDTH,HEIGHT);
        intro=counter;
        while(counter-intro<2)
        blit(instruction2,screen,0,0,0,0,WIDTH,HEIGHT);
        intro=counter;

        while(counter-intro<2)
        blit(instruction3,screen,0,0,0,0,WIDTH,HEIGHT);
        intro=counter;
        gameover=0;
        loadplayer();
        loadenemy();
        loadbomber();
        loadpistol();
        loadbomb();

        while(!key[KEY_ESC] && !gameover){
       // clear_bitmap(buffer);

        if(mils-lastinput>2) inputflag=1;
        if(inputflag)   checkinputs();

        updatehero();
        if(gameover==1) break;
        if((tarma.x%(640*2))<5 && lastspawn!=tarma.x/(640*2)){
            spawn=1;
            lastspawn=tarma.x/(640*2);
        }
         if((tarma.x%(640*5))<5 && lastspawnbomb!=tarma.x/(640*5)){
            spawnbomb=1;
            lastspawnbomb=tarma.x/(640*5);
        }


        updateenemy(spawn);
        updatebombers(spawnbomb);
        updatedeaths();
        updatebullets();
        updatebombs();
        displaystats();
        acquire_screen();
        blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
        release_screen();
        ticks++;
        rest(DELAY);
    }
    intro=counter;
    while(counter-intro<2)
        blit(gameoverscreen,screen,0,0,0,0,WIDTH,HEIGHT);
    if(key[KEY_ESC])     exits=1;

    }

     destroy_sample(level1);
     remove_sound();
    remove_int(timer1);
    destroy_bitmap(buffer);
    destroy_bitmap(welcome);
    destroy_bitmap(instruction1);
    destroy_bitmap(instruction2);
    destroy_bitmap(instruction3);
    destroy_bitmap(gameoverscreen);
    delete []bulldogs;
    delete []pistols;
    delete gun;
    delete []bomb;
    delete []bombman;
    delete rocket;
     for(int i=0;i<6;i++)
                for(int j=0;j<TARMAMAX[i];j++)
                    destroy_bitmap(tarma.heroimg[i][j]);
     for(int i=2;i<5;i++)
                for(int j=0;j<REBELMAX[i];j++)
                destroy_bitmap(enemypics.enemyimg[i][j]);
    for(int i=0;i<4;i++)
                destroy_bitmap(bulletpics.bullets[i]);
    for(int i=0;i<14;i++)
        destroy_bitmap(bomberpics.bomber[i]);

    MapFreeMem();
    allegro_exit();
    return 0;
}
END_OF_MAIN()
