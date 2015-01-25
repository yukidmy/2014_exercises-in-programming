/* enemy.c */
#include <enemy.h>
#include <movingobject.h>
#include <object.h>

#define ENEMYNUM 2

static object* objp[ENEMYNUM];

static void onesteppm(movingobject* mobj){   // mobj(enemy)を動かす
  if(((mobj->cnt)/6)%4){
    mobj->pos.y = mobj->pos.y + mobj->vel.y;
    if(mobj->pos.y > 15){
      mobj->pos.y = 5;
    }
  }else{
    mobj->pos.y = mobj->pos.y - mobj->vel.y;
  }
  mobj->cnt = (mobj->cnt + 1)%48;
}

static void dispa(movingobject* mobj){   // bufferにmobj(enemy)を書き込み
  int l = (mobj->cnt/12)%2;
  putobject((mobj->obj)[l], mobj->id, mobj->pos.x, mobj->pos.y);
}

static int bomba(movingobject* mobj){   // bombかどうか判定？ 1を返す
  return 1;
}

movingobject* newenemy(void){   // enemyの初期設定
  objp[0] = newobject(3, 3, " : ::: : ");
  objp[1] = newobject(3, 3, " : :*: : ");
  return newmovingobject(&objp[0], onesteppm, dispa, bomba, "enemy");
}
