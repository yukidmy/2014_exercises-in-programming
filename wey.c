/* enemy2.c */

/*
dispa2でremovemoしてるので、movingobjectmanager.cでの消し方に気をつけてね
 */
#include<wey.h>
#include<movingobject.h>
#include<object.h>

static object* objp[3];
void removemo(int num);

static void onesteppm2(movingobject* mobj){
  //mobj->pos.x = mobj->pos.x +mobj->vel.x;
  if(((mobj->cnt)/30)%2){
    mobj->pos.x = mobj->pos.x -mobj->vel.x;
    //mobj->pos.y = mobj->pos.x +mobj->vel.y;
  }else{
    mobj->pos.x = mobj->pos.x +mobj->vel.x;
    mobj->pos.y = mobj->pos.x -mobj->vel.y;
  }
  mobj->cnt = (mobj->cnt +1)%48;
}

void dispa2(movingobject* mobj){
  int l = (mobj->cnt/30)%2;
  if(mobj->flag){
    putobject((mobj->obj)[2], mobj->id, mobj->pos.x, mobj->pos.y);
    if(!((mobj->cnt)%100)){
      removemo(mobj->id);
    }
  }
  else if(l == 0){
    putobject((mobj->obj)[0], mobj->id, mobj->pos.x, mobj->pos.y);
  }
  else{
    putobject((mobj->obj)[1], mobj->id, mobj->pos.x, mobj->pos.y);
  }
}

static int bomba2(movingobject* mobj){
  return 1;
}

movingobject* newenemy2(void){
  objp[0] = newobject(7,1,"\\(^o^)/");
  objp[1] = newobject(7,1,"/(^o^)\\");
  objp[2] = newobject(7,1," (._.) ");
  
  return newmovingobject(&objp[0], onesteppm2, dispa2, bomba2, "enemy");
}
