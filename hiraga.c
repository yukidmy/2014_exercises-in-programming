/* enemy.c */
#include<hiraga.h>
#include<movingobject.h>
#include<object.h>

static object* objp[3];

static void onesteppm(movingobject* mobj){
  if((((mobj->cnt)/12)%4)%2){
    if((((mobj->cnt)/12)%4)%3){
    mobj->pos.x = mobj->pos.x - 8*mobj->vel.x;
    }
    else{
    mobj->pos.x = mobj->pos.x + 7*mobj->vel.x;

    }
  }
  else{
    if((((mobj->cnt)/12)%4)%4){
      mobj->pos.y = mobj->pos.y -4*mobj->vel.y;
    }
    else{
      mobj->pos.y = mobj->pos.y +5*mobj->vel.y;
    }
  }
  mobj->cnt = (mobj->cnt +1)%48;
}

static void dispa(movingobject* mobj){
  int l = (mobj->cnt/12)%3;
  putobject((mobj->obj)[l], mobj->id, mobj->pos.x, mobj->pos.y);
}

static int bomba(movingobject* mobj){
  return 1;
}

movingobject* newenemyh(void){
  objp[0] = newobject(10,4,"   ____    / ^  ^ \\ |  HHHH  | \\ ____ / ");
  objp[1] = newobject(10,4,"   ____    / +  + \\ |  HHHH  | \\ ____ / ");
  objp[2] = newobject(10,4,"                                        ");
  return newmovingobject(&objp[0], onesteppm, dispa, bomba, "hiraga");
}
/*
     _____
   / .   . \\ 
  |    @    |
   \\_______/  
    | | | |
    | | | |
 |_/  | |  \\_|  
            
            
            
             
*/
