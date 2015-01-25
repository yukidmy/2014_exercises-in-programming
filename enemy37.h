/* enemy37.h */
#ifndef _ENEMY37_H_
#define _ENEMY37_H_

#include <movingobjectmanager.h>

// gamemain.c の関数等で必要なもの
#define MOBJNUM 15
extern movingobject* mobjp[MOBJNUM];
void onestepb(movingobject* mobj);
void dispb(movingobject* mobj);

// gamemain.c で呼び出す関数
extern movingobject* newenemy37(void);

#endif
