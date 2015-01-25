/* superunk.c */
#include<superunk.h>
#include<movingobject.h>
#include<object.h>
#include<screen.h>

static object* objp[2];



static void onesteppm(movingobject* mobj){
    if(((mobj->cnt)/6)%4){
    mobj->pos.x = mobj->pos.x +mobj->vel.x;
    mobj->pos.y = mobj->pos.y +mobj->vel.y;
  }else{
    mobj->pos.x = mobj->pos.x -mobj->vel.x;
    mobj->pos.y = mobj->pos.y -mobj->vel.y;
  }
  mobj->cnt = (mobj->cnt +1)%48;
}


static void dispa(movingobject* mobj){
  int l = (mobj->cnt/12)%2;
  putobject((mobj->obj)[l], mobj->id, mobj->pos.x, mobj->pos.y);
}

static int bomba(movingobject* mobj){
  return 1;
}

movingobject* superunk(void){
  objp[0] = newobject(7,4,"   ^     ( )   (^_^) (_____)");
  objp[1] = newobject(7,4,"   ^     ( )   (~_^) (_____)");
  return newmovingobject(&objp[0], onesteppm, dispa, bomba, "superunk");
}
