/* item.c */
#include <stdlib.h>
#include <bidlist.h>
#include <item.h>
#include <walls.h>
#include <screen.h>
#include <random.h>
#include <movingobjectmanager.h>

#define ITEMNUM 2

#define MAXITEM 5
#define MAXOBJCNT 250

const unsigned char ITEM0 = 250;
const unsigned char ITEM1 = 249;

static object* objp[ITEMNUM];
static movingobject* mobjp[ITEMNUM];

static bidlist* itemlist;
static bidnode* nodes[MAXITEM];
static int count = 0;

void onestepi(movingobject* mobj){
  if((mobj->cnt/3)%4){
    vec2add(&(mobj->pos), &(mobj->vel));
  }
  mobj->cnt = (mobj->cnt +1)%12;
}

int bombi(movingobject* mobj){
  if(mobj->id == ITEM0){
    addlife(1);
  }else if(mobj->id == ITEM1){
    scoreup(10);
  }
  return 1;
}

void dispi(movingobject* mobj){   
  putobject(*(mobj->obj), mobj->id, mobj->pos.x, mobj->pos.y);
}

void initi(void){
  objp[0] = newobject(1, 1, "@");   // 回復
  objp[1] = newobject(1, 1, "S");   // スコアアップ
}

void initmovingi(void){
  mobjp[0] = newmovingobject(&objp[0], onestepi, dispi, bombi, "i0");
  mobjp[1] = newmovingobject(&objp[1], onestepi, dispi, bombi, "i1");
}

void initilist(void){
  itemlist = newbidlist();
}

void inititem(void){
  initilist();
  initi();
  initmovingi();
}

/* ここまで準備 */

void additem(vector2 pos, vector2 vel, int inum){
  movingobject* tmp;
  int id;
  if(count < MAXITEM){
    inum = inum%2;
    tmp = (movingobject*)malloc(sizeof(movingobject));
    *tmp = *mobjp[inum];
    tmp->pos = pos;
    tmp->vel = vel;
    if(inum == 0){
      tmp->id = ITEM0;
    }else if(inum == 1){
      tmp->id = ITEM1;
    }
    bidlistadd(itemlist, tmp);
    count++;
  }
} 

void removeitem(int n){
  count--;
  deletemovingobject(nodes[n]->data);
  bidlistremove(itemlist, nodes[n]);
}

void putitem(void){  // 描写等
  movingobject* mobj;
  bidnode* node;
  int num = 0;
  int id;
  bidlistreset(itemlist);  
  while((node = bidlistnext(itemlist))){
    nodes[num] = node;
    mobj = (movingobject*)(node->data);
    id = checkcollision(mobj->pos, mobj->currentobj);
    if(id != NONOBJ){     // 衝突判定
      if(id == PLAYER){   // プレイヤーに当たったら
	if(mobj->bomb(mobj)){   // 処理して
	  removeitem(num);      // 取り除く
	  continue;
	}
      }else if(id == BORDER){  // はじまで行ったら 
	removeitem(num);       // 取り除く
	continue;
      }else{              // 壁とかに当たったら
	safepos(&mobj->pos, mobj->currentobj);   // 移動する
	mobj->vel.x  = -(mobj->vel.x);
      }                                   
    }
    mobj->onestep(mobj);     // 動かして
    putmovingobject(mobj);   // 書き込み
    num++;
  }
}

void item(void){
  int num = randomnum(2);
  vector2 pos = makevector2(randomnum(30)+5, 1);
  vector2 vel = makevector2(0.05*randomnum(5), 0.05*(randomnum(5)+1));
  additem(pos, vel, num);
  putitem();   // 衝突判定と処理
}
