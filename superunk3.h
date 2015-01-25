/* superunk3.h */
#ifndef _SUPERUNK3_H_
#define _SUPERUNK3_H_
#include<movingobject.h>
#include <movingobjectmanager.h>
#define MOBJNUM 15


extern movingobject* mobjp[MOBJNUM];
void onestepb(movingobject* mobj);
void dispb(movingobject* mobj);

extern movingobject* superunk3(void);

#endif
