#include"contraheader.h"

void checkinputs(){
    int laststate=tarma.type2;
     int speed=2;
    tarma.crouch=false;
    //tarma.animdir=0;
    /*if(keypressed())
        tarma.animdir=1;
    else
        tarma.animdir=0;
     */
    if(tarma.jump==true)    speed=3;
    if(key[KEY_UP]){
        tarma.type2=TARMASHOWINGUP;
        tarma.totalframes=TARMAMAX[tarma.type2];
        tarma.firedirection=FIREUP;

    }
    if(key[KEY_LEFT]){
        tarma.facing=LEFT;
        tarma.type2=TARMALEFT;
        tarma.firedirection=FIRELEFT;
        tarma.totalframes=TARMAMAX[tarma.type2];
        tarma.lastx=tarma.x;
        tarma.x -= speed;
    }
     if(key[KEY_RIGHT]){
        tarma.facing=RIGHT;
        tarma.type2=TARMARIGHT;
        tarma.firedirection=FIRERIGHT;
        tarma.lastx=tarma.x;
        tarma.totalframes=TARMAMAX[tarma.type2];
        tarma.x += speed;
    }
    if(key[KEY_DOWN]){
        if(tarma.jump==false){
            tarma.crouch=true;
            tarma.type2=TARMACROUCHING;
            //tarma.y+=30;
            tarma.totalframes=TARMAMAX[tarma.type2];
            tarma.firedirection=(tarma.facing==LEFT)?FIRELEFT:FIRERIGHT;
        }
    }

    if(key[KEY_LEFT] && key[KEY_UP]){
        tarma.facing=LEFT;
        tarma.type2=TARMASHOWINGUP;
        tarma.firedirection=FIRELEFTUP;
        tarma.lastx=tarma.x;
        tarma.totalframes=TARMAMAX[tarma.type2];
        tarma.x -= speed/2;
    }
    if(key[KEY_RIGHT] && key[KEY_UP]){
        tarma.facing=RIGHT;
        tarma.type2=TARMASHOWINGUP;
        tarma.firedirection=FIRERIGHTUP;
        tarma.lastx=tarma.x;
        tarma.totalframes=TARMAMAX[tarma .type2];
        tarma.x += speed/2;
    }
    if(key[KEY_S] && mils-lastjump>2){
        if(tarma.jump==false && tarma.crouch==false){
            checkpointx=tarma.x;
            checkpointy=tarma.y;
            tarma.jump=true;
            tarma.jumpfactor=40;
            tarma.crouch=false;
            tarma.totalframes=TARMAMAX[tarma.type2];

        }
    }
    if(key[KEY_A]){
        if(tarma.bullettype==PISTOL){
            if(pistolcount>PISTOLDELAY){
            pistolcount=0;
            firebullet(tarma.bullettype);
            }
        }
        if(tarma.bullettype==GUN){
            if(guncount>GUNDELAY){
            guncount=0;
            firebullet(tarma.bullettype);
            }
        }

    }
    if(key[KEY_D]){
        if(bombcount>BOMBDELAY && tarma.bombs>0){
            bombcount=0;
            firebomb();
            tarma.bombs--;
        }
    }
    guncount++;
    pistolcount++;
    bombcount++;
    rocketcount++;
    if(laststate != tarma.type2){
        tarma.curframe=0;
        if(laststate==TARMACROUCHING)   tarma.y-=35;
        if(tarma.type2!=TARMACELEBRATING)
        tarma.animdir=0;
    }
    else    {tarma.animdir=1;
                if(laststate==TARMACROUCHING) tarma.crouch=true;
                }
}


void firebullet(int type){
    int i;
    if(type==PISTOL){
        for(i=0;i<25;i++)
                  if(!pistols[i].alive)
                        break;
        if(i<25){
            switch(tarma.firedirection){
                //case    FIRERIGHT:
                case   0:
                    pistols[i].x=tarma.x+tarma.width;
                    pistols[i].y=tarma.y+10;
                    pistols[i].alive=1;
                    pistols[i].direction=FIRERIGHT;
                    pistols[i].velx=pistols[i].speed;
                    pistols[i].vely=0;
                    break;
                //case    FIRERIGHTUP:
                 case  1 :
                    pistols[i].x=tarma.x+tarma.width;
                    pistols[i].y=tarma.y-20;
                    pistols[i].alive=1;
                    pistols[i].direction=FIRERIGHTUP;
                    pistols[i].velx= pistols[i].speed;
                    pistols[i].vely= -pistols[i].speed;
                    break;
                //case    FIREUP:
                case   2:
                    pistols[i].x=tarma.x+tarma.width/2;
                    pistols[i].y=tarma.y-20;
                    pistols[i].alive=1;
                    pistols[i].direction=FIREUP;
                    pistols[i].velx=0;
                    pistols[i].vely=-pistols[i].speed;
                    break;
                //case    FIRELEFT:
                 case   4:
                    pistols[i].x=tarma.x-20;
                    pistols[i].y=tarma.y+10;
                    //if(tarma.crouch)    pistols[i].y-=40;
                    pistols[i].alive=1;
                    pistols[i].direction=FIRELEFT;
                    pistols[i].velx=-pistols[i].speed;
                    pistols[i].vely=0;
                    break;
                //case    FIRELEFTUP:
                 case   3:
                    pistols[i].x=tarma.x-20;
                    pistols[i].y=tarma.y-20;
                    pistols[i].alive=1;
                    pistols[i].direction=FIRELEFTUP;
                    pistols[i].velx=-pistols[i].speed;
                    pistols[i].vely=-pistols[i].speed;
                    break;
            }
        }
    }
}

void fireathero(int n){
    int i;



            for(i=25;i<50;i++)
                  if(!pistols[i].alive)
                        break;
        if(i<50){
            switch(bulldogs[n].facing){
                case   2:
                //case    RIGHT:
                    pistols[i].x=bulldogs[n].x+bulldogs[n].width;
                    pistols[i].y=bulldogs[n].y+10;
                    pistols[i].alive=1;
                    pistols[i].direction=FIRERIGHT;
                    pistols[i].velx=pistols[i].speed;
                    pistols[i].vely=0;
                    break;
                case   1:
                //case    FIRELEFT:
                    pistols[i].x=bulldogs[n].x-20;

                    pistols[i].y=bulldogs[n].y+10;

                    pistols[i].alive=1;
                    pistols[i].direction=FIRELEFT;
                    pistols[i].velx=-pistols[i].speed;
                    pistols[i].vely=0;
                    break;
                            }
        }
}
void firebomb(){
    int i;
        for(i=0;i<10;i++){
            if(!bomb[i].alive)
                break;
        }
        if(i<10){
            bomb[i].jump=true;
            bomb[i].jumpfactor=40;
            switch(tarma.facing){
                case   2:
                //case    RIGHT:
                    bomb[i].x=tarma.x+tarma.width+20;
                    bomb[i].y=tarma.y+10;
                    bomb[i].alive=1;
                    bomb[i].direction=FIRERIGHT;
                    bomb[i].velx=bomb[i].speed;
                    bomb[i].vely=0;
                    break;
                case   1:
                //case    FIRELEFT:
                    bomb[i].x=tarma.x-25;

                    bomb[i].y=tarma.y+10;

                    bomb[i].alive=1;
                    bomb[i].direction=FIRELEFT;
                    bomb[i].velx=-bomb[i].speed;
                    bomb[i].vely=0;
                    break;
                            }
        }
}




void firebombathero(int n){
    int i;

            for(i=10;i<20;i++)
                  if(!bomb[i].alive)
                        break;
        if(i<20){
            bomb[i].jumpfactor=40;
            bomb[i].jump=true;
            switch(bombman[n].facing){
                case   2:
                //case    RIGHT:
                    bomb[i].x=bombman[n].x+bombman[n].width+20;
                    bomb[i].y=bombman[n].y+10;
                    bomb[i].alive=1;
                    bomb[i].direction=FIRERIGHT;
                    bomb[i].velx=bomb[i].speed;
                    bomb[i].vely=0;
                    break;
                case   1:
                //case    FIRELEFT:
                    bomb[i].x=bombman[n].x-25;

                    bomb[i].y=bombman[n].y+10;

                    bomb[i].alive=1;
                    bomb[i].direction=FIRELEFT;
                    bomb[i].velx=-bomb[i].speed;
                    bomb[i].vely=0;
                    break;
                            }
        }
}

