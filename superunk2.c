/* superunk2.c */
#include<superunk2.h>
#include<movingobject.h>
#include<object.h>
#include<vector2.h>
#include<movingobjectmanager.h>
#include<bidlist.h>
#include<object.h>


static object* objp[2];
vector2 tmpv;

static void onesteppm(movingobject* mobj){
  if(((mobj->cnt)/6)%4 == 0){
    mobj->pos.x = mobj->pos.x -mobj->vel.x -1;
    mobj->pos.y = mobj->pos.y +mobj->vel.y ;
  }else{
    mobj->pos.x = mobj->pos.x +mobj->vel.x +0.2;
    mobj->pos.y = mobj->pos.y +mobj->vel.y;
  }

  mobj->cnt = (mobj->cnt +1)%48;

  if(((mobj->cnt)/6)%4 == 1){

    tmpv = mobj->pos;
    tmpv.x +=3;
    tmpv.y +=4;
    /* addmo(mobjp[0], tmpv, makevector2(0,1));*/
  }

}

static void dispa(movingobject* mobj){
  int l = (mobj->cnt/12)%2;
  putobject((mobj->obj)[l], mobj->id, mobj->pos.x, mobj->pos.y);
}

static int bomb(movingobject* mobj){
  return 1;
}

movingobject* superunk2(void){
  objp[0] = newobject(7,4,"   ^     ( )   (:_:) (_____)");
  objp[1] = newobject(7,4,"   ^     ( )   (*_*) (_____)");
  return newmovingobject(&objp[0], onesteppm, dispa, bomb, "superunk2");
}
