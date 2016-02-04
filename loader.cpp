#include"contraheader.h"

int loadplayer(){
    int x=10, y=10;
    int alive=1;
    int lives=100,    type1=HERO,    type2=TARMACELEBRATING,  hitpoints=10, width=50,    height=70;
    int xdel=10,ydel=0,    totalframe=TARMAMAX[type2];
    int velx=0,vely=0;
    tarma.setcharacter(x,y,lives,type1,type2,width,height, totalframe,velx, vely,xdel,ydel,hitpoints,alive);
    for(int i=0;i<6;i++){
        if(i!=TARMALEFT){
            BITMAP* temp = load_bitmap(TARMABMP[i],NULL);
            if(temp==NULL)   {return 0;}
            int j=0;
            for(j=0;j<TARMAMAX[i];j++)
//                tarma.heroimg[i][j]=grabframe(temp,TARMAWIDTH,TARMAHEIGHT[i],0,0,19,j);
                 tarma.heroimg[i][j]=grabframe(temp,TARMAWIDTH,TARMAHEIGHT[i],0,0,19,j);

            destroy_bitmap(temp);
        }

    }
    for(int i=0;i<TARMAMAX[TARMALEFT];i++)    {
        BITMAP* temp=create_bitmap(width,height);
        clear_to_color(temp,makecol(255,0,255));
        draw_sprite_h_flip(temp,tarma.heroimg[TARMARIGHT][i],0,0);
        tarma.heroimg[TARMALEFT][i]=temp;
    }
    return 1;
}

int loadenemy(){
    int x=10, y=10;
    int n;
    int alive=0;
    int lives=0,    type1=ENEMY,    type2=REBELRIGHT,  hitpoints=2, width=50,    height=70;
    int xdel=5,ydel=0,    totalframe=11;
    int velx=0,vely=0;
    for(n=0;n<20;n++)
        bulldogs[n].setcharacter(x,y,lives,type1,type2,width,height, totalframe,velx, vely,xdel,ydel,hitpoints,alive);
    for(int i=2;i<5;i++){
        if(i==REBELLEFT || i==REBELDYING){
            BITMAP* temp=load_bitmap(REBELBMP[i],NULL);
            if(temp==NULL)    {return 0;}
            int j=0;
            for(j=0;j<REBELMAX[i];j++)
                enemypics.enemyimg[i][j]=grabframe(temp,width,height,0,0,19,j);
            destroy_bitmap(temp);
        }

    }
    for(int i=0;i<REBELMAX[REBELRIGHT];i++)    {
        BITMAP* temp=create_bitmap(width,height);
        clear_to_color(temp,makecol(255,0,255));
        draw_sprite_h_flip(temp,enemypics.enemyimg[REBELLEFT][i],0,0);
        enemypics.enemyimg[REBELRIGHT][i]=temp;
    }
    return 1;
}

int loadpistol( ){
    int x=0,y=0,alive=0;
    int type=PISTOL;
    int direction=FIRELEFT;
    int damagept=1;
    int speed=5;
    int width=15,height=15;
    for(int i=0;i<50;i++)
            pistols[i].setbullet(x,y,type,direction,speed,width,height,damagept,alive);

    bulletpics.bullets[PISTOL]=load_bitmap("pistolbullet.bmp",NULL);
    bulletpics.bullets[GUN]=load_bitmap("gunbullet.bmp",NULL);
    bulletpics.bullets[ROCKET]=load_bitmap("rocket.bmp",NULL);
    bulletpics.bullets[BOMB]=load_bitmap("bomb.bmp",NULL);
    return 1;
}


int loadbomber(){
    int x=10, y=10;
    int alive=0;
    int lives=0,    type1=ENEMY,    type2=ENEMY,  hitpoints=2, width=50,    height=70;
    int n;
    int xdel=5,ydel=0,    totalframe=14;
    int velx=0,vely=0;
    for(n=0;n<MAXBOMBERS;n++)
        bombman[n].setcharacter(x,y,lives,type1,type2,width,height, totalframe,velx, vely,xdel,ydel,hitpoints,alive);
        BITMAP* temp=load_bitmap("rebelbomber.bmp",NULL);
            if(temp==NULL)    {return 0;}
            int j=0;
            for(j=0;j<totalframe;j++)
                bomberpics.bomber[j]=grabframe(temp,width,height,0,0,14,j);
            destroy_bitmap(temp);
    return 1;
}

int loadbomb( ){
    int x=0,y=0,alive=0;
    int type=BOMB;
    int direction=FIRELEFT;
    int damagept=5;
    int speed=2;
    int width=20,height=15;
    for(int i=0;i<20;i++)
            bomb[i].setbullet(x,y,type,direction,speed,width,height,damagept,alive);


    return 1;
}
