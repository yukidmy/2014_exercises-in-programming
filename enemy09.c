/* enemy09.c */
#include <screen.h>
#include <enemy09.h>
#include <movingobject.h>
#include <object.h>

/* 1420509 漆原理乃 */
/*弾を当てるごとに猫ちゃん(?)の顔が変わります*/
/*４回当てたら消えます*/

static object* objp[4];
static object* bobjp[1];

static void onesteppm(movingobject* mobj){
  if(((mobj->cnt)/6)%4){/*縦の移動*/
    mobj->pos.y = mobj->pos.y +mobj->vel.y;
  }else{
    mobj->pos.y = mobj->pos.y -mobj->vel.y;
  }

  if(((mobj->cnt)/24)%2){/*横の移動*/
    mobj->pos.x = mobj->pos.x +mobj->vel.x;
  }else{
    mobj->pos.x = mobj->pos.x -mobj->vel.x;
  }
  mobj->cnt = (mobj->cnt +1)%48;
}

static void dispa(movingobject* mobj){
  int l = mobj->flag;
  putobject((mobj->obj)[l], mobj->id, mobj->pos.x, mobj->pos.y);
}

static int bomba(movingobject* mobj){
  (mobj->flag)++;
  if(mobj->flag == 4){ 
    return 1;
  }else{
    return 0;
  }
}

movingobject* newenemy09(void){
  objp[0] = newobject(9,4," _^___^_ | ^   ^ ||___@___| |     | ");
  objp[1] = newobject(9,4," _^___^_ | o   o ||___O___| |     | ");
  objp[2] = newobject(9,4," _^___^_ | >   < ||__---__| |     | ");
  objp[3] = newobject(9,4," _^___^_ | x   x ||__TTT__| |     | ");

  return newmovingobject(&objp[0], onesteppm, dispa, bomba, "enemy");
}
