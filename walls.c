/* walls.c */
#include <string.h>
#include <walls.h>
#include <screen.h>
#include <movingobjectmanager.h>

#define WALLLOOP 40
#define UNITS 9
#define UNITLINES  7

static int count = 0;

static char walldata[UNITS*UNITLINES][WIDTH+1] = {
  // 0
  "OOOOO                             OOOOOO",
  "OOOOOO       O          O        OOOOOOO",
  "OOOOOO      OOO        OOO       OOOOOOO",
  "OOOOOO     OOOO       OOOOO      OOOOOOO",
  "OOOOOO      OOO       OOOO      OOOOOOOO",
  "OOOOOOO      OO        O       OOOOOOOOO",
  "OOOOOOOO                      OOOOOOOOOO",
  /*   ,    |    ,    |    ,    |    ,    */
  // 1
  "OOOOOOOOOO                  OOOOOOOOOOOO",
  "OOOOOOOOO                  OOOOOOOOOOOOO",
  "OOOOOOO                   OOOOOOOOOOOOOO",
  "OOOO                     OOOOOOOOOOOOOOO",
  "OOO                     OOOOOOOOOOOOOOOO",
  "OOO                   OOOOOOOOOOOOOOOOOO",
  "OO                   OOOOOOOOOOOOOOOOOOO",
  /*   ,    |    ,    |    ,    |    ,    */
  // 2
  "OO                    OOOOOOOOOOOOOOOOOO",
  "OOO                   OOOOOOOOOOOOOOOOOO",
  "OOO                    OOOOOOOOOOOOOOOOO",
  "OOOO                     OOOOOOOOOOOOOOO",
  "OOOOOOO                    OOOOOOOOOOOOO",
  "OOOOOOOOO                    OOOOOOOOOOO",
  "OOOOOOOOOOO                   OOOOOOOOOO",
  /*   ,    |    ,    |    ,    |    ,    */
  // 3
  "OOOOOOOOOOOOOO                 OOOOOOOOO",
  "OOOOOOOOOOOOOOOO                OOOOOOOO",
  "OOOOOOOOOOOOOOOOOO               OOOOOOO",
  "OOOOOOOOOOOOOOOOOOOO              OOOOOO",
  "OOOOOOOOOOOOOOOOOOOOO               OOOO",
  "OOOOOOOOOOOOOOOOOOOOOO               OOO",
  "OOOOOOOOOOOOOOOOOOOOOOO               OO",
  /*   ,    |    ,    |    ,    |    ,    */
  // 4
  "OOOOOOOOOOOOOOOOOOOOO                 OO",
  "OOOOOOOOOOOOOOOOOOOO                 OOO",
  "OOOOOOOOOOOOOOOOOOO                 OOOO",
  "OOOOOOOOOOOOOOOOO                  OOOOO",
  "OOOOOOOOOOOOOO                    OOOOOO",
  "OOOOOOOOOOOO                    OOOOOOOO",
  "OOOOOOOOO                      OOOOOOOOO",
  /*   ,    |    ,    |    ,    |    ,    */
  // 5
  "OOOOOOO            OOOOO        OOOOOOOO",   
  "OOOOOO          OOOOOOOOOO        OOOOOO",
  "OOOOOO         OOOOOOOOOOOO        OOOOO",
  "OOOOOO         OOOOOOOOOOOO          OOO",   
  "OOOOOOO        OOOOOOOOOOO          OOOO",   
  "OOOOOOO         OOOOOOOOO         OOOOOO",   
  "OOOOOOOO          OOOOO          OOOOOOO",   
  /*   ,    |    ,    |    ,    |    ,    */
  // 6
  "OOOOOO                            OOOOOO",   
  "OOOOO       OO            OO       OOOOO",   
  "OOOO       OOO     OO     OOO       OOOO",   
  "OOOO        O     OOOO     O        OOOO",   
  "OOOOO              OO              OOOOO",   
  "OOOOO                              OOOOO",   
  "OOOOO                              OOOOO",   
  /*   ,    |    ,    |    ,    |    ,    */
  // 7
  "OOOOO                              OOOOO",   
  "OOOOO                              OOOOO",   
  "OOOOO      O                O      OOOOO",   
  "OOOOO      O    OO    OO    O      OOOOO",   
  "OOOOO       O   O      O   O       OOOOO",   
  "OOOOOO                            OOOOOO",   
  "OOOOOOO                          OOOOOOO",     
  /*   ,    |    ,    |    ,    |    ,    */
  // 8 (buttle用)
  "                                        ",   
  "                                        ",   
  "                                        ",   
  "                                        ",
  "                                        ",
  "                                        ",
  "                                        ",
};

static char collisioncheckdata[UNITS*UNITLINES][WIDTH];

static int wallorder[WALLLOOP] = {
  0,1,2,3,4, 5,6,7,6,7, 0,1,2,3,4, 5,6,7,6,7,
  0,1,2,1,2, 7,6,7,6,7, 0,3,4,3,4, 5,5,5,0,5,
};

void initwalls(void){
  int i,j;
  for(i=0; i<UNITS*UNITLINES; i++){
    for(j=0; j<WIDTH; j++){
      if(walldata[i][j] ==' '){ 
        collisioncheckdata[i][j] = NONOBJ;  //non object
      }else{ 
        collisioncheckdata[i][j] = WALL;  //wall
      }
    }
  }
}

void scrollwall(void){
  count++;
}

vector2 safepos(vector2* mypos, object* obj){
  vector2 ret = {mypos->x, mypos->y};
  int flag = 1;
  while(checkcollision(ret, obj) != NONOBJ){
    if((ret.x < 40)&&flag){
      ret.x += 1;
    }else{
      flag = 0;
      ret.x -= 1;
    }
  }
  *mypos = ret;
}

void putbuttlewalls(int lines){
  int lline;
  int i, j;
  for (i=lines; i>0; i--){
    lline = ((count+i) % UNITLINES); 
    for(j=0; j<WIDTH; j++){
      putdata(j, lines-i, walldata[8*UNITLINES+lline][j],
              collisioncheckdata[8*UNITLINES+lline][j]);
    }
  }
  for(j=0; j<WIDTH; j++){
    putdata(j, 0, '+', BORDER);
    putdata(j, lines-1, '+', BORDER);
  }            
  for(j=0; j<lines; j++){
    putdata(0, j, '+', BORDER);
    putdata(WIDTH-1, j, '+', BORDER);
  }            
}

void putwalls(int lines){
  int unit, lline;
  int i, j;
  for (i=lines; i>0; i--){
    unit = ((count+i) / UNITLINES) % WALLLOOP; 
    lline = ((count+i) % UNITLINES); 
    for(j=0; j<WIDTH; j++){
      putdata(j, lines-i, walldata[wallorder[unit]*UNITLINES+lline][j],
              collisioncheckdata[wallorder[unit]*UNITLINES+lline][j]);
    }
  }
  for(j=0; j<WIDTH; j++){
    putdata(j, 0, '+', BORDER);
    putdata(j, lines-1, '+', BORDER);
  }            
  for(j=0; j<lines; j++){
    putdata(0, j, '+', BORDER);
    putdata(WIDTH-1, j, '+', BORDER);
  }
}
