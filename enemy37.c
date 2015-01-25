/* enemy37.c */
#include <enemy37.h>
#include <screen.h>

/**********************************************************/
/*   敵も弾を撃ちます  　                                   */
/*   弾を３回当てると死にます                                */
/*   倒すまで消えません                                     */
/*   gamemain2.cとこれにenemy37.cを読み込んで使ってください   */
/*                                     1420537  山田優輝   */
/**********************************************************/

#define ENEMYNUM 2

static object* objp[ENEMYNUM];

static int positionx[13] = {2, 6, 10, 14, 18, 26, 30, 
			    26, 22, 18, 14, 6, 2};
static int positiony[5] = {3, 5, 2, 5, 8};
static int posx = 0;
static int posy = 0;

static void onestep37(movingobject* mobj){   // enemy37を動かす
  if(mobj->cnt == 5){   // 横移動
    mobj->pos.x = positionx[posx];
    posx = (posx+1)%13;
  }
  if(mobj->cnt == 15){   // 縦移動
    mobj->pos.y = positiony[posy];
    posy = (posy+1)%5;
  }
  mobj->cnt = (mobj->cnt + 1)%20;
}

static void disp37(movingobject* mobj){   // bufferにenemy37を書き込み
  int l = (mobj->cnt/12)%2;  // 表示を変化させる
  putobject((mobj->obj)[l], mobj->id, mobj->pos.x, mobj->pos.y);
  putdata(mobj->pos.x + 3, mobj->pos.y + 3,'0'+ mobj->flag, NONOBJ);
  if(mobj->cnt == 10){   // 弾を出す
    vector2 tmpv;
    tmpv = mobj->pos;
    tmpv.x += 3;
    tmpv.y += 6;
    addmo(mobjp[1], tmpv, makevector2(0,1));
  }
}

static int bomb37(movingobject* mobj){
  mobj->flag -= 1;
  if(mobj->flag == 0){
    return 1;
  }else{
    return 0;
  }
}

movingobject* newenemy37(void){
  movingobject* ret;
  objp[0] = newobject(7,3,"( O O )(  <  )(  A  )");
  objp[1] = newobject(7,3,"( O O )(  <  )(  -  )");
  ret = newmovingobject(&objp[0], onestep37, disp37, bomb37, "enemy37");
  ret->flag = 3;
  return ret;
}
