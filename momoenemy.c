/*momoenemy.c


g1420507　岩見桃子


 */
#include<enemy.h>
#include<movingobject.h>
#include<object.h>
#include<screen.h>
static object* objp[6];

static void onesteppm(movingobject* mobj){

  /*case 3は平和なメンディーくん（ぴょんぴょん）
   case 2は怒ったメンディーくん（突進してくる）
   case 1は逃げるメンディーくん（上に逃げてく）*/
  
  switch(mobj->flag){

  case 3:
    if(((mobj->cnt)/12)%2){
      mobj->pos.y = mobj->pos.y + 0.4;
      mobj->pos.x = mobj->pos.x + 0.2;
    }else{
      mobj->pos.y = mobj->pos.y - 0.4;
      mobj->pos.x = mobj->pos.x + 0.2;
    }
    break;

  case 2:
    if(((mobj->cnt)/12)%2){
      mobj->pos.y = mobj->pos.y + 0.5;
      mobj->pos.x = mobj->pos.x + 0.2;
    }else{
      mobj->pos.y = mobj->pos.y + 0.5;
      mobj->pos.x = mobj->pos.x - 0.2;
    }
    break;

  case 1: 
  if(((mobj->cnt)/6)%4){
    mobj->pos.y = mobj->pos.y - 0.1;
    mobj->pos.x = mobj->pos.x + 0.2;
  }else{
    mobj->pos.y = mobj->pos.y - 0.1;
    mobj->pos.x = mobj->pos.x - 0.2;
  }
  break;

  }
  mobj->cnt = (mobj->cnt +1)%48;
}


static void dispa(movingobject* mobj){
  int l = (mobj->cnt/12)%2;
  
  switch(mobj->flag){
  case 3:
    putobject((mobj->obj)[l], mobj->id, mobj->pos.x, mobj->pos.y);
    break;
  case 2:
    putobject((mobj->obj)[l+2], mobj->id, mobj->pos.x, mobj->pos.y);
    break;
  case 1:
    putobject((mobj->obj)[l+4], mobj->id, mobj->pos.x, mobj->pos.y);
  }
}

static int bomba(movingobject* mobj){
  mobj->flag -= 1;
  if(mobj->flag == 0){
    return 0;
  }else{
    return 1;
  }
}

movingobject* momoenemy(void){
  movingobject* ret;
  objp[0] = newobject(7,7,"HELLO! @@@@@@@|~~ ~~|| ^ ^ ||  [  ||  O  ||_____|");
  objp[1] = newobject(7,7,"       @@@@@@@|~~ ~~|| ^ ^ ||  [  ||  -  ||_____|");
  objp[2] = newobject(7,7,"OKOTTA!@@@@@@@|~~ ~~|| @ @ ||  [  ||  A  ||_____|");
  objp[3] = newobject(7,7,"       @@@@@@@|~~ ~~|| @ @ ||  [  ||  O  ||_____|");
  objp[4] = newobject(3,4,"@@@|_|-O-/ \\");
  objp[5] = newobject(3,4,"@@@|_|-O-/ \\");
  ret =  newmovingobject(&objp[0], onesteppm, dispa, bomba, "momoenemy");
  ret -> flag = 3;
  return ret;
}
