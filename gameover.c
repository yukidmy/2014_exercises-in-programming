/* gameover.c */
#include <unistd.h>
#include <screen.h>
#include <gameio.h>

void gameover(void){
  int i, j;

  static char goal[8][40]={
    "                                        ",
    "  +       ++++++  ++++++  ++++++  + +   ",
    "  +       +    +  +       +       + +   ",
    "  +       +    +  ++++++  ++++++  + +   ",
    "  +       +    +       +  +             ",
    "  ++++++  ++++++  ++++++  ++++++  + +   ",
    "                                        ",
    "  You can't be a HERO..... That's all.  ",
  };

  gameioclear();
  for(i=0; i<8; i++){
    for(j=0; j<40; j++){
      gameioput(j+10, i+5, goal[i][j]);
    }
  }
  gameiorefresh();
  sleep(3);
}
