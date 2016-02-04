#include"contraheader.h"
int inside(int x, int y, int x1, int x2, int y1, int y2){
    if(x>x1 && x<x2 && y>y1 && y<y2)
        return 1;
    else return 0;
}

int met(int x1,int y1,int x2, int y2, int w1, int w2,int h1, int h2){
    int wa=x1+w1;
    int ha=y1+h1;
    int wb=x2+w2;
    int hb=y2+h2;
    return(inside(x1,y1,x2,wb,y2,hb)|| inside(x1,ha,x2,wb,y2,hb) ||  inside(wa,ha,x2,wb,y2,hb) ||  inside(wa,y1,x2,wb,y2,hb));
}

void updatehero(){
    tarma.animate();
    if(tarma.crouch)    tarma.height=35;
    else    tarma.height=70;
    if(tarma.jump==false){
        if(!collided(tarma.x+tarma.width/2,tarma.y+tarma.height+5)){
            tarma.jump=true;
            tarma.jumpfactor=-1;
        }
    }
    if(tarma.jump)  {
        tarma.lasty=tarma.y;
        tarma.y    -=  tarma.jumpfactor/5;
        if(tarma.y<20){
            tarma.y=20;
        }
        tarma.jumpfactor--;
    }
    if(tarma.jumpfactor<0){
        if(collided(tarma.x+tarma.width/2,tarma.y+tarma.height))
        {
            tarma.jump=false;
            lastjump=mils;
            while(collided(tarma.x+tarma.width/2,tarma.y+tarma.height))
                tarma.y-=2;
        }
    }
    if(tarma.facing==LEFT){
        if(collided(tarma.x,tarma.y+tarma.height)){
            tarma.x=tarma.lastx;
    }
    }
    if(tarma.facing==RIGHT){
        if(collided(tarma.x+tarma.width,tarma.y+tarma.height)){
            tarma.x=tarma.lastx;
    }
    }
    for(int i=0;i<20;i++){
         if(bulldogs[i].alive){
                if(met(tarma.x,tarma.y,bulldogs[i].x,bulldogs[i].y,tarma.width,bulldogs[i].width,tarma.height,bulldogs[i].height)){
                        tarma.x=tarma.lastx;

               }
        }
        if(i>=MAXBOMBERS)   continue;
        if(bombman[i].alive){
                if(met(tarma.x,tarma.y,bombman[i].x,bombman[i].y,tarma.width,bombman[i].width,tarma.height,bombman[i].height)){
                        tarma.x=tarma.lastx;

               }
        }

    }


    if(tarma.y>(mapheight*mapblockheight-tarma.height-50) ){
        resetplayer();
        if(gameover)    return;
    }

    if(tarma.x<5)  tarma.x=5;

    mapxoff=tarma.x+tarma.width/2-WIDTH/2+10;
    mapyoff=tarma.y+tarma.height/2-HEIGHT/2+10;
    if(mapxoff<0)   mapxoff=0;
    if(mapxoff>mapwidth*mapblockwidth-WIDTH)    mapxoff=mapwidth*mapblockwidth-WIDTH;
    if(mapyoff<0)   mapyoff=0;
    if(mapyoff>mapheight*mapblockheight-HEIGHT)    mapyoff=mapheight*mapblockheight-HEIGHT;
    MapDrawBG(buffer,mapxoff,mapyoff,0,0,WIDTH-1,HEIGHT-1);
    MapDrawFG(buffer,mapxoff,mapyoff,0,0,WIDTH-1,HEIGHT-1,0);

    tarma.draw();
}

void resetplayer(){
    tarma.lives--;
    tarma.jump=false;
    if(tarma.lives<0) {gameover=1;     return;}
    tarma.hitpoints=10;
    tarma.type2=TARMADYING;
    tarma.totalframes=TARMAMAX[TARMADYING];
    tarma.curframe=0;
    tarma.bombs=20;
    inputflag=0;
    lastinput=counter;
    tarma.x =checkpointx;
    tarma.y=checkpointy;


}



void updateenemy(int& spawn){
         int difficulty=2+tarma.x*10/(mapblockwidth*mapwidth);
       if(spawn==1){
            int n,i;

            n=difficulty+rand()%difficulty;
            for(i=0;i<20 && n>0 ;i++){
                if(!(bulldogs[i].alive)){
                    bulldogs[i].alive=1;
                    bulldogs[i].totalframes=11;
                    bulldogs[i].x=mapxoff+WIDTH+rand()%1200;
                    bulldogs[i].y=SCREEN_H/2;
                    bulldogs[i].curframe=0;
                    bulldogs[i].hitpoints=2;
                    bulldogs[i].jump=false;

                    if((bulldogs[i].x+bulldogs[i].width/2)<(tarma.x+tarma.width/2)){
                        bulldogs[i].velx=rand()%3;
                        bulldogs[i].facing=RIGHT;
                        bulldogs[i].type2=REBELRIGHT;
                        bulldogs[i].curframe=0;
                    }
                    else {
                           bulldogs[i].velx=-(rand()%3);
                                bulldogs[i].facing=LEFT;
                                bulldogs[i].type2=REBELLEFT;
                                bulldogs[i].curframe=0;
                    }
                 n--;

                }
        }
    spawn=0;
    }
        for(int i=0;i<20;i++){
            if(bulldogs[i].alive && bulldogs[i].hitpoints>0){


                 if(bulldogs[i].jump==false){
                    if(!collided(bulldogs[i].x+bulldogs[i].width/2,bulldogs[i].y+bulldogs[i].height+5)){
                    bulldogs[i].jump=true;
                    bulldogs[i].jumpfactor = -1;
                    }
                 }
                if(bulldogs[i].jump==false){
                      for(int j=0;j<25;j++){
                          if(pistols[j].alive){
                                int dist=pistols[j].x-bulldogs[i].x;
                                if(((dist>50 && dist<80) || (dist<-50 && dist>-80)) && pistols[j].y>bulldogs[i].y && pistols[j].y<bulldogs[i].y+ bulldogs[i].width){
                                    bulldogs[i].jump=(rand()%(40/difficulty))?false:true;
                                    bulldogs[i].jumpfactor=24;
                                }
                          }
                      }
                  }

                if(bulldogs[i].jump)  {
                    bulldogs[i].y    -=  bulldogs[i].jumpfactor/3;
                    bulldogs[i].jumpfactor--;
                }
                if(bulldogs[i].jumpfactor<0){
                    if(collided(bulldogs[i].x+bulldogs[i].width/2,bulldogs[i].y+bulldogs[i].height))
                {
                    bulldogs[i].jump=false;
                    while(collided(bulldogs[i].x+bulldogs[i].width/2,bulldogs[i].y+bulldogs[i].height))
                        bulldogs[i].y -= 2;
                }
                }
                bulldogs[i].lastx=bulldogs[i].x;
                bulldogs[i].animate();
                if(bulldogs[i].jump)    bulldogs[i].x=bulldogs[i].lastx;

                if((counter-bulldogs[i].lastcount)>bulldogs[i].firedelay){
                        if((bulldogs[i].x-mapxoff) >0 && (bulldogs[i].x-mapxoff)<(640-bulldogs[i].width)){

                            fireathero(i);
                            bulldogs[i].lastcount=counter;
                        }
                }
                if(bulldogs[i].facing==LEFT){
                    if(collided(bulldogs[i].x,bulldogs[i].y+bulldogs[i].height/2)){
                        bulldogs[i].x=bulldogs[i].lastx;

                    }
                }
                if(bulldogs[i].facing==RIGHT){
                    if(collided(bulldogs[i].x+bulldogs[i].width,bulldogs[i].y+bulldogs[i].height/2)){
                        bulldogs[i].x=bulldogs[i].lastx;
                    }
                }
               if(!collided(bulldogs[i].x+bulldogs[i].width/2,bulldogs[i].y+bulldogs[i].height) ){
                   bulldogs[i].x=bulldogs[i].lastx;
               }
               if(met(tarma.x,tarma.y,bulldogs[i].x,bulldogs[i].y,tarma.width,bulldogs[i].width,tarma.height,bulldogs[i].height)){
                        bulldogs[i].x=bulldogs[i].lastx;
               }
               //bulldogs[i].velx=0;
               if((bulldogs[i].x+bulldogs[i].width/2)<(tarma.x+tarma.width/2)){
                   bulldogs[i].velx=rand()%3;
                   bulldogs[i].facing=RIGHT;
                   bulldogs[i].type2=REBELRIGHT;
               }
                else    {
                    bulldogs[i].velx=-(rand()%3);
                    bulldogs[i].facing=LEFT;
                   bulldogs[i].type2=REBELLEFT;
               }
                //bulldogs[i].type2=REBELLEFT;
                //bulldogs[i].facing=LEFT;


                if(bulldogs[i].x+bulldogs[i].width<mapxoff)
                    bulldogs[i].alive=0;
                if(bulldogs[i].y>mapheight*mapblockheight-bulldogs[i].height-50 || bulldogs[i].y<10)
                    bulldogs[i].alive=0;
                if(bulldogs[i].alive &&     (bulldogs[i].x+bulldogs[i].width-mapxoff)>0 && (bulldogs[i].x-mapxoff<WIDTH))
                    bulldogs[i].draw();
            }
        }

}

void updatebullets(){
    int i,j;
    for(i=0;i<50;i++){
        if(pistols[i].alive){
            pistols[i].x=pistols[i].x+pistols[i].velx;
            pistols[i].y=pistols[i].y+pistols[i].vely;


            if(pistols[i].x<(mapxoff-WIDTH) || pistols[i].x>mapxoff+WIDTH || pistols[i].y<mapyoff || pistols[i].y>mapyoff+HEIGHT){
                    pistols[i].alive=0;
                    continue;
            }
            else   if( pistols[i].x-mapxoff>0 && pistols[i].x-mapxoff<WIDTH) pistols[i].draw();






    for(j=0;j<20;j++){
        if(bulldogs[j].alive &&i<25 && bulldogs[j].hitpoints>0){


                    if(met(pistols[i].x,pistols[i].y,bulldogs[j].x,bulldogs[j].y,pistols[i].width,bulldogs[j].width,pistols[i].height,bulldogs[j].height)){
                        pistols[i].alive=0;
                        scores+=100;
                        bulldogs[j].hitpoints--;
                        if((bulldogs[j].hitpoints)<=0){
                            bulldogs[j].type2=REBELDYING;
                            bulldogs[j].totalframes=REBELMAX[REBELDYING];
                            bulldogs[j].curframe=0;
                            bulldogs[j].velx=0;
                            bulldogs[j].jump=false;
                    }
                    break;
                }
        }
        if(j>=MAXBOMBERS)    continue;
                   if(bombman[j].alive &&i<25 && bombman[j].hitpoints>0){


                    if(met(pistols[i].x,pistols[i].y,bombman[j].x,bombman[j].y,bombman[i].width,bombman[j].width,bombman[i].height,bombman[j].height)){
                        pistols[i].alive=0;
                        scores+=500;
                        bombman[j].hitpoints--;
                        if((bombman[j].hitpoints)<=0){
                            bombman[j].type2=REBELDYING;
                            bombman[j].totalframes=REBELMAX[REBELDYING];
                            bombman[j].curframe=0;
                            bombman[j].velx=0;
                            bombman[j].jump=false;
                    }
                    break;
                }

            }
        }

        if(!pistols[i].alive)   continue;

        if(i>25 && inputflag){
            if(met(pistols[i].x,pistols[i].y,tarma.x,tarma.y,pistols[i].width,tarma.width,pistols[i].height,tarma.height)){
                scores-=100;
                tarma.hitpoints--;
                if(!tarma.hitpoints)
                    resetplayer();
                pistols[i].alive=0;
        }
    }

        }
    }
}

void displaystats(){
    textprintf_ex(buffer,font,0,0,15,-1,"CONTRA FORCE:");
    textprintf_ex(buffer,font,0,10,15,-1,"SCORES %d",scores);
    textprintf_ex(buffer,font,0,20,15,-1,"Framerate: %d, counter: %d",framerate,counter);
     textprintf_ex(buffer,font,0,30,15,-1,"xoffset: %d, yoffset: %d",mapxoff, mapyoff);
     textprintf_ex(buffer,font,0,40,15,-1,"lives: %d", tarma.lives);
}

void updatedeaths(){
    int i;
    for(i=0;i<20;i++){
        if(bulldogs[i].alive && bulldogs[i].hitpoints<=0){
            bulldogs[i].type2=REBELDYING;
            bulldogs[i].totalframes=REBELMAX[bulldogs[i].type2];
            bulldogs[i].animate();
            bulldogs[i].draw();
            //textprintf_ex(buffer,font,bulldogs[i].x,bulldogs[i].y-20,15,-1,"%d",i);
            if(bulldogs[i].curframe==bulldogs[i].totalframes-1)
                bulldogs[i].alive=0;
        }
    }
    for(i=0;i<MAXBOMBERS;i++){
        if( bombman[i].alive &&  bombman[i].hitpoints<=0){
             bombman[i].type2=REBELDYING;
             bombman[i].totalframes=REBELMAX[ REBELDYING];
             bombman[i].animate();
             bombman[i].draw();
            //textprintf_ex(buffer,font, bombman[i].x, bombman[i].y-20,15,-1,"%d",i);
            if( bombman[i].curframe== bombman[i].totalframes-1)
                 bombman[i].alive=0;
        }
    }

}

void updatebombers(int& spawn){
         int difficulty=2+tarma.x*10/(mapblockwidth*mapwidth);
       if(spawn==1){
            int n,i;

            n=rand()%difficulty;
            for(i=0;i<MAXBOMBERS && n>0;i++){
                if(!(bombman[i].alive)){
                    bombman[i].alive=1;
                    bombman[i].totalframes=14;
                    bombman[i].x=mapxoff+WIDTH+rand()%1200;
                    bombman[i].y=SCREEN_H/2;
                    bombman[i].curframe=0;
                    bombman[i].hitpoints=2;
                    bombman[i].jump=false;

                    if((bombman[i].x+bombman[i].width/2)<(tarma.x+tarma.width/2)){
                        bombman[i].velx=rand()%3;
                        bombman[i].facing=RIGHT;
                        bombman[i].type2=ENEMY;
                        bombman[i].curframe=0;
                    }
                    else {
                           bombman[i].velx=-(rand()%3);
                                bombman[i].facing=LEFT;
                                bombman[i].type2=ENEMY;
                                bombman[i].curframe=0;
                    }
                 n--;

                }
        }
    spawn=0;
    }
        for(int i=0;i<MAXBOMBERS;i++){
            if(bombman[i].alive && bombman[i].hitpoints>0){


                 if(bombman[i].jump==false){
                    if(!collided(bombman[i].x+bombman[i].width/2,bombman[i].y+bombman[i].height+5)){
                    bombman[i].jump=true;
                    bombman[i].jumpfactor = -1;
                    }
                 }
                if(bombman[i].jump==false){
                      for(int j=0;j<25;j++){
                          if(pistols[j].alive){
                                int dist=pistols[j].x-bombman[i].x;
                                if(((dist>50 && dist<80) || (dist<-50 && dist>-80)) && pistols[j].y>bombman[i].y && pistols[j].y<bombman[i].y+ bombman[i].width){
                                    bombman[i].jump=(rand()%(40/difficulty))?false:true;
                                    bombman[i].jumpfactor=24;
                                }
                          }
                      }
                  }

                if(bombman[i].jump)  {
                    bombman[i].y    -=  bombman[i].jumpfactor/3;
                    bombman[i].jumpfactor--;
                }
                if(bombman[i].jumpfactor<0){
                    if(collided(bombman[i].x+bombman[i].width/2,bombman[i].y+bombman[i].height))
                {
                    bombman[i].jump=false;
                    while(collided(bombman[i].x+bombman[i].width/2,bombman[i].y+bombman[i].height))
                        bombman[i].y -= 2;
                }
                }
                bombman[i].lastx=bombman[i].x;
                bombman[i].animate();
                if(bombman[i].jump)    bombman[i].x=bombman[i].lastx;

                if((counter-bombman[i].lastcount)>bombman[i].firedelay+1){
                        if((bombman[i].x-mapxoff) >0 && (bombman[i].x-mapxoff)<(640-bombman[i].width)){

                            firebombathero(i);
                            bombman[i].lastcount=counter;
                        }
                }
                if(bombman[i].facing==LEFT){
                    if(collided(bombman[i].x,bombman[i].y+bombman[i].height/2)){
                        bombman[i].x=bombman[i].lastx;

                    }
                }
                if(bombman[i].facing==RIGHT){
                    if(collided(bombman[i].x+bombman[i].width,bombman[i].y+bombman[i].height/2)){
                        bombman[i].x=bombman[i].lastx;
                    }
                }
               if(!collided(bombman[i].x+bombman[i].width/2,bombman[i].y+bombman[i].height) ){
                   bombman[i].x=bombman[i].lastx;
               }
               if(met(tarma.x,tarma.y,bombman[i].x,bombman[i].y,tarma.width,bombman[i].width,tarma.height,bombman[i].height)){
                        bombman[i].x=bombman[i].lastx;
               }
               //bombman[i].velx=0;
               if((bombman[i].x+bombman[i].width/2)<(tarma.x+tarma.width/2)){
                   bombman[i].velx=rand()%3;
                   bombman[i].facing=RIGHT;
                   bombman[i].type2=REBELRIGHT;
               }
                else    {
                    bombman[i].velx=-(rand()%3);
                    bombman[i].facing=LEFT;
                   bombman[i].type2=REBELLEFT;
               }
                //bombman[i].type2=REBELLEFT;
                //bombman[i].facing=LEFT;


                if(bombman[i].x+bombman[i].width<mapxoff)
                    bombman[i].alive=0;
                if(bombman[i].y>mapheight*mapblockheight-bombman[i].height-50 || bombman[i].y<10)
                    bombman[i].alive=0;
                if(bombman[i].alive &&     (bombman[i].x+bombman[i].width-mapxoff)>0 && (bombman[i].x-mapxoff<WIDTH))
                    bombman[i].draw();
            }
        }

}

void updatebombs(){
    int i,j;
    for(i=0;i<20;i++){
        if(bomb[i].alive){
            int dieatlast=0;
            bomb[i].x=bomb[i].x+bomb[i].velx;
           bomb[i].y-=bomb[i].jumpfactor/10;
           bomb[i].jumpfactor--;

         if(bomb[i].x<(mapxoff-WIDTH) || bomb[i].x>mapxoff+WIDTH || bomb[i].y<mapyoff || bomb[i].y>mapyoff+HEIGHT){
                    bomb[i].alive=0;

            }
            else if(bomb[i].y>mapblockheight*mapheight-30)  bomb[i].alive=0;
            if( bomb[i].x-mapxoff>0 && (bomb[i].x-mapxoff)<(WIDTH-bomb[i].width)) bomb[i].draw();

           if(bomb[i].jumpfactor<0){
        if(collided(bomb[i].x+bomb[i].width/2,bomb[i].y+bomb[i].height))
        {

            bomb[i].jump=false;
                while(collided(bomb[i].x+bomb[i].width/2,bomb[i].y+bomb[i].height))
                bomb[i].y-=2;

                 if(i<10){
                for(int k=0;k<20;k++){
                    if(bulldogs[k].alive && bulldogs[k].hitpoints>0){
                        if(met(bulldogs[k].x,bulldogs[k].y,bomb[i].x-BOMBRADIUS,bomb[i].y-BOMBRADIUS,bulldogs[k].width,BOMBRADIUS*2,bulldogs[k].height,BOMBRADIUS*2)){
                        scores+=500;
                        bulldogs[k].hitpoints-=bomb[i].damagept;
                        if((bulldogs[k].hitpoints)<=0){
                            bulldogs[k].type2=REBELDYING;
                            bulldogs[k].totalframes=REBELMAX[REBELDYING];
                            bulldogs[k].curframe=0;
                            bulldogs[k].velx=0;
                            bulldogs[k].jump=false;
                    }

                }
        }
        if(k>=MAXBOMBERS)    continue;
                   if(bombman[k].alive  && bombman[k].hitpoints>0){
                             if(met(bombman[k].x,bombman[k].y,bomb[i].x-BOMBRADIUS,bomb[i].y-BOMBRADIUS,bombman[k].width,BOMBRADIUS*2,bombman[k].height,BOMBRADIUS*2)){


                        scores+=1000;
                        bombman[k].hitpoints-=bomb[i].damagept;
                        if((bombman[k].hitpoints)<=0){
                            bombman[k].type2=REBELDYING;
                            bombman[k].totalframes=REBELMAX[REBELDYING];
                            bombman[k].curframe=0;
                            bombman[k].velx=0;
                            bombman[k].jump=false;
                    }

                }

            }
        }
        //bomb[i].alive=0;
                 }
                       if(i>=10 && inputflag){
            if(met(tarma.x,tarma.y,bomb[i].x-BOMBRADIUS,bomb[i].y-BOMBRADIUS,tarma.width,BOMBRADIUS*2,tarma.height,BOMBRADIUS*2)){

                tarma.hitpoints-=bomb[i].damagept;
                if(tarma.hitpoints<=0)
                    resetplayer();
                bomb[i].alive=0;
        }
    }
        bomb[i].alive=0;

        }

           }

if(!bomb[i].alive)  continue;
 for(j=0;j<20;j++){
        if(bulldogs[j].alive &&i<10 && bulldogs[j].hitpoints>0){
                if(met(bulldogs[j].x,bulldogs[j].y,bomb[i].x-BOMBRADIUS,bomb[i].y-BOMBRADIUS,bulldogs[j].width,BOMBRADIUS*2,bulldogs[j].height,BOMBRADIUS*2)){


                        dieatlast=1;
                        scores+=500;
                        bulldogs[j].hitpoints-=bomb[i].damagept;
                        if((bulldogs[j].hitpoints)<=0){
                            bulldogs[j].type2=REBELDYING;
                            bulldogs[j].totalframes=REBELMAX[REBELDYING];
                            bulldogs[j].curframe=0;
                            bulldogs[j].velx=0;
                            bulldogs[j].jump=false;
                    }

                }
        }
        if(j>=MAXBOMBERS)    continue;
                   if(bombman[j].alive &&i<10 && bombman[j].hitpoints>0){
                        if(met(bombman[j].x,bombman[j].y,bomb[i].x-BOMBRADIUS,bomb[i].y-BOMBRADIUS,bombman[j].width,BOMBRADIUS*2,bombman[j].height,BOMBRADIUS*2)){


                        dieatlast=1;                        scores+=1000;
                        bombman[j].hitpoints-=bomb[i].damagept;
                        if((bombman[j].hitpoints)<=0){
                            bombman[j].type2=REBELDYING;
                            bombman[j].totalframes=REBELMAX[REBELDYING];
                            bombman[j].curframe=0;
                            bombman[j].velx=0;
                            bombman[j].jump=false;
                    }

                }

            }
        }


    if(dieatlast)   bomb[i].alive=0;
    if(!bomb[i].alive)  continue;


        if(i>=10 && inputflag){
            if(met(tarma.x,tarma.y,bomb[i].x-BOMBRADIUS,bomb[i].y-BOMBRADIUS,tarma.width,BOMBRADIUS*2,tarma.height,BOMBRADIUS*2)){

                tarma.hitpoints-=bomb[i].damagept;
                if(tarma.hitpoints<=0)
                    resetplayer();
                bomb[i].alive=0;
        }
    }

        }
    }
}

/*void updatepowerups(){
    if(counter-lastpowerups>20 && !powerup)
*/
