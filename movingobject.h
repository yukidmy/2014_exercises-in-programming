/* movingobject.h */
#ifndef _MOVINGOBJECT_H_
#define _MOVINGOBJECT_H_
#include <object.h>

typedef struct movingobject{
  vector2 pos;     // {double x; double y} 現在地
  vector2 vel;     // 動く方向
  int flag;        // 何回被弾したら消えるか 不使用あり
  int cnt;         // 表示の変化 きらきらとかぱくぱくとか
  int id;          // 衝突判定用
  void (*onestep)(struct movingobject* obj);   // 動かす用
  void (*display)(struct movingobject* obj);   // 書き込み用
  int (*bomb)(struct movingobject* obj);       // 消すかどうか
  char* name; 
  object** obj;    // {vector2 size; char* shape}
  object* currentobj;
} movingobject;

movingobject* newmovingobject(object** shape, 
                              void(*onestep)(movingobject* obj),
                              void(*display)(movingobject* obj), 
                              int(*bomb)(movingobject* obj), 
                              char* name);
void deletemovingobject(movingobject* mobj);
void setinitposition(movingobject* mobj, vector2 pos);
void putmovingobject(movingobject* mobj); 

#endif
