/* walls.h */

#ifndef _GAME_WALLS_H_
#define _GAME_WALLS_H_

#include <movingobjectmanager.h>

#define WIDTH 40

void initwalls(void);
void putbuttlewalls(int lines);
void putwalls(int lines);
void scrollwall(void);
vector2 safepos(vector2* mypos, object* obj);

#endif
