/* enemy26.c */
/*1420526 張嘉瑩
敵が敵(弾)をうちます。それに当たると死にます。
newevent()の三番目の引数をmakevector2(1,?)とかにして、スピードは各自で調節してください。
調節すれば、画面から出さないことも可能です。*/
#include<enemy26.h>
#include<movingobject.h>
#include<object.h>
#include<movingobjectmanager.h>

static object* objp[3];
static movingobject* mobjpp[1];

static void onesteppm26(movingobject* mobj){
   if(((mobj->cnt)/6)%4){
    mobj->pos.y = mobj->pos.y + mobj->vel.y;}
  else{
    mobj->pos.y = mobj->pos.y - mobj->vel.y;
    }

  if((mobj->cnt)<24){
    mobj->pos.x = mobj->pos.x + mobj->vel.x;}
   else{
     mobj->pos.x = mobj->pos.x - mobj->vel.x;}

  mobj->cnt = (mobj->cnt+1)%48;
}

static void dispa26(movingobject* mobj){
  vector2 tmpv;
  int l = (mobj->cnt/12)%2;
  putobject((mobj->obj)[l], mobj->id, mobj->pos.x, mobj->pos.y);
  mobjpp[0] = newmovingobject(&objp[2], onestepb, dispb, bomba, "enemybullet");
  if((mobj->cnt)%37==1){
    tmpv = mobj->pos;
    tmpv.x +=2;
    tmpv.y +=5;
    addmo(mobjpp[0], tmpv, makevector2(0,0.1));}
}

static int bomba26(movingobject* mobj){
  return 1;
}

movingobject* newenemy26(void){
  objp[0] = newobject(7,5,"  ___   /o-o\\ /|---|\\ \\___/   | |  ");
  objp[1] = newobject(7,5,"  ___   /x-x\\ /|---|\\ \\___/   | |  ");
  objp[2] = newobject(1,1,"*");
  return newmovingobject(&objp[0], onesteppm26, dispa26, bomba26, "enemy26");
}
