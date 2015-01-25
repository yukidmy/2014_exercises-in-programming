/* movingobjectmanager.c */
#include <movingobjectmanager.h>
#include <screen.h>
#include <bidlist.h>
#include <stdlib.h>
#ifdef DEBUG
#include <log.h>
#endif

#define MAXOBJCNT 200
void dispa2(movingobject* mobj);

static bidlist* objlist;
static bidnode* nodes[MAXOBJCNT];
static int count = 0;   // objlistのobjectの数 objlest->countと同じ？

void initmom(void){   // objlistの初期値設定 全てNULLもしくは0
  objlist = newbidlist();
}

void addmo(movingobject* mobj, vector2 pos, vector2 vel){  // objlistに要素追加
  movingobject* tmp;
  if(count < MAXOBJCNT){
    tmp = (movingobject*)malloc(sizeof(movingobject));
    *tmp = *mobj;
    tmp->pos = pos;
    tmp->vel = vel;
    bidlistadd(objlist, tmp);
    count++;
  }
} 

/* call just after putmo */
void removemo(int num){   // objlistのnum番目の要素を取り除く
  count--;
  deletemovingobject(nodes[num]->data);
  bidlistremove(objlist, nodes[num]);
}

/* put objects on dispbuffer and checkbuffer */
void putmo(void){   // 衝突判定してobjlistの要素をbufferに書き込み
  movingobject* mobj;
  bidnode* node;
  int num = 0;
  int id;
  bidlistreset(objlist);   // objlist->markにobjlist->head を代入
  while((node = bidlistnext(objlist))){   // objlist全部チェック
    nodes[num] = node;
    mobj = (movingobject*)(node->data);
    mobj->id = num;              // ナンバリングする
    id = checkcollision(mobj->pos, mobj->currentobj);
    if(id == BORDER){   // はしっこまで行ったら終わり
      removemo(num);
    }else if(id < MAXOBJCNT){    // NONBOJでもBORDERでもWALLでもなかったら(衝突)
	if(mobj->bomb(mobj)){    // 消してよければ
	  removemo(num);         // 消す
	}
      if(((movingobject*)(nodes[id]->data))
         ->bomb((movingobject*)(nodes[id]->data))){   // こちらも消してよければ
	//if(((movingobject*)(nodes[id]->data))->display == dispa2){
	//dispa2((movingobject*)(nodes[id]->data));
	//}else{        
	  removemo(id);                                 // 消す
	  //}
      }
    }else{                     // NONOBJかWALLだったら
      putmovingobject(mobj);   // mobjを書き込む(ようやく)
      num++;                   // num++ if文のときは後ろが詰めてくるから必要なし
    }
  }
}

/* put objects on dispbuffer and checkbuffer */   // ?? 違う
void onestepmo(void){   // objlistの要素を動かす
  movingobject* mobj;
  bidnode* node;
  int num = 0;
  bidlistreset(objlist);
  while((node = bidlistnext(objlist))){
    mobj = (node->data);
    mobj->onestep(mobj);
  }
}

int countmo(void){   // 今表示されているmobjの数を返す
  return count+1;    // なぜかcountで返すとうまく動かない
}

