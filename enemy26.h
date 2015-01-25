/* enemy26.h */
#ifndef _ENEMY26_H_
#define _ENEMY26_H_
#include<movingobject.h>

#define MOBJNUM 15

extern movingobject* newenemy26(void);

extern movingobject* mobjp[MOBJNUM];

void onestepb(movingobject* mobj);

void dispb(movingobject* mobj);

int bomba(movingobject* mobj);


#endif
