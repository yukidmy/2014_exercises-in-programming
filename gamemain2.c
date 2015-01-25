/* gamemain2.c */
#include <stdio.h>
#include <ncurses.h>
#include <gameio.h>
#include <scenario.h>
#include <screen.h>
#include <walls.h>
#include <enemy.h>
#include <myenemy.h>
#include <movingobjectmanager.h>
#include <gameover.h>
#include <goal.h>
#include <item.h>
#ifdef DEBUG
#include <log.h>
#endif

#define OBJNUM 3
#define MOBJNUM 15
#define EVNUM 15
#define LASTBUTTLE 10
#define LIFE 5

object* objp[OBJNUM];
movingobject* mobjp[MOBJNUM];
event* ev[EVNUM];
static vector2 mypos;   // プレイヤーの現在地
int isfire;
int time = 0;
int score = 0;
int score_plus = 0;
int speedlevel = 17; 
int playerlevel = 0;
int buttle = 0;

static vector2 pos = {SCREENWIDTH/2-1, SCREENHEIGHT-3};

void onestepb(movingobject* mobj){   // mobj(bullet)を動かす
  vec2add(&(mobj->pos), &(mobj->vel));
}

void dispb(movingobject* mobj){   // bufferにmobj(bullet)を書き込み
  putobject(*(mobj->obj), mobj->id, mobj->pos.x, mobj->pos.y);
}

void dispm(movingobject* mobj){   // bufferにmobj(me)を書き込み
  putobject(*(mobj->obj), mobj->id, mobj->pos.x, mobj->pos.y);
}

int bomba(movingobject* mobj){  // bullet用
  return 1;
}

void addlife(int num){
  mobjp[0]->flag += num;
  if(mobjp[0]->flag  > 5){
    mobjp[0]->flag = 5;
  }
}

void scoreup(int num){
  score_plus += num;
}

int bombme(movingobject* mobj){  // me用
  mobj->flag -= 1;
  if(mobj->flag == 0){
    return 1;
  }else{
    return 0;
  }
}

void initobjects(void){   // objpの初期設定
  objp[0] = newobject(1, 1, "x");
  objp[1] = newobject(3, 2, " ^ =x=");
  objp[2] = newobject(7, 4, "   ^     ( )   (   ) (_____)");
}

void initmovingobjects(void){   // mobjpの初期設定
  mobjp[0] = newmovingobject(&objp[1], NULL, dispm, bombme, "me");
  mobjp[0]->flag = LIFE;
  mobjp[0]->id = PLAYER;
  mobjp[1] = newmovingobject(&objp[0], onestepb, dispb, bomba, "bullet");
  /* ここから敵さん ※ mobjp[n] なら time==n-2 で */
  mobjp[2] = newenemy();
  /* ここからオリジナルの敵さん */
  mobjp[3] = newenemy2();
  mobjp[4] = newenemy09();
  mobjp[5] = superunk();
  mobjp[6] = newenemyh();
  mobjp[7] = superunk2();
  mobjp[8] = momoenemy();
  mobjp[9] = superunk3();
  mobjp[10] = newmovingobject(&objp[2], onestepb, dispb, bomba, "unkbullet");
  mobjp[11] = newenemy26();
  mobjp[12] = newenemy37();
}

void setevents(void){   // evの初期設定
  int i;
  ev[0] = newevent(0, makevector2(8,8), 
		   makevector2(0,0.1), mobjp[2], "enemy1-1");
  ev[1] = newevent(0, makevector2(28,13), 
		   makevector2(0,0.1), mobjp[2], "enemy1-2");
  ev[2] = newevent(1, makevector2(5,10), 
		   makevector2(0,0.1), mobjp[3], "wey");     // 14 小山内遥香
  ev[3] = newevent(2, makevector2(3,3), 
		   makevector2(0,0.1), mobjp[4], "taso");    // 09 漆原理乃
  ev[4] = newevent(3, makevector2(18,3), 
		   makevector2(0,0.1), mobjp[5], "unk");     // 10 大島榛名
  ev[5] = newevent(4, makevector2(25,3), 
		   makevector2(0,0.1), mobjp[6], "hiraga");  // 32 平賀郁子 
  ev[6] = newevent(5, makevector2(30,3), 
		   makevector2(0,0.1), mobjp[7], "unk2");    // 10 大島榛名
  ev[7] = newevent(6, makevector2(3,10), 
		   makevector2(0,0.1), mobjp[8], "momo");    // 07 岩見桃子
  ev[8] = newevent(7, makevector2(17,3), 
		   makevector2(0,0.1), mobjp[9], "unk3");    // 10 大島榛名
  ev[9] = newevent(8, makevector2(2,3), 
		   makevector2(1,0.1), mobjp[11], "pyon");   // 26 張嘉瑩
  ev[10] = newevent(9, makevector2(3,3), 
		    makevector2(0,0), mobjp[12], "enemy37"); // 自分の
  for(i=0;i<EVNUM;i++){
    addevent(ev[i]);
  }
  resetmark();
}

void init(void){   // 初期設定いろいろ
  initscreen();
  initwalls();
  initmom();
  initobjects();
  initmovingobjects();
  initscenario();
  setevents();
  inititem();
}

void color(void){   // 終了時の表示色を変えたかったけどうまく動かない、エラーは出ない
  start_color();
  // カラー設定
  init_pair(1, COLOR_WHITE, COLOR_BLACK);     //　基本的にはこれ
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_GREEN, COLOR_BLACK);
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(10, COLOR_BLACK, COLOR_BLACK);
  bkgd(COLOR_PAIR(10));			    // 背景は色10
}


void getstate(vector2* ret, int* isfire){   // キー操作 
  *isfire = 0;
  int in = gameioread();
  switch(in){
  case 'f':
  case 'F':
  case KEY_RIGHT:
    pos.x++;
    break;
  case 'b':
  case 'B':
  case KEY_LEFT:
    pos.x--;
    break;
  case 'p':
  case 'P':
    pos.y--;
    break;
  case 'n':
  case 'N':
    pos.y++;
    break;
  case KEY_UP:
    scrollwall();
    if(!buttle){
      score++;
    }
    break;
  case 'u':
  case 'U':
    if(speedlevel > 3){
      speedlevel -= 1;
    }
    break;
  case 'd':
  case 'D':
    if(speedlevel < 17){
      speedlevel += 1;
    }
    break;
  case ' ':
    *isfire = 1;
  } 
  *ret = pos;
}

void show(void){   // 画面出力
  int x,y;
  for(y=0; y<SCREENHEIGHT; y++){
    for(x=0; x<SCREENWIDTH; x++){
      gameioput(x, y, dispbuffer[SCREENWIDTH*y+x]);
    }
  }
  gameiorefresh();
}

void putscores(void){   // score等の表示
  int s = 18 - speedlevel;
  int i;
  gameioput(SCREENWIDTH+3, 1, '0'+(int)mypos.x/10);
  gameioput(SCREENWIDTH+4, 1, '0'+(int)mypos.x%10);
  gameioput(SCREENWIDTH+6, 1, '0'+(int)mypos.y/10);
  gameioput(SCREENWIDTH+7, 1, '0'+(int)mypos.y%10);
  gameioput(SCREENWIDTH+3, 3, 'L');
  gameioput(SCREENWIDTH+4, 3, 'e');
  gameioput(SCREENWIDTH+5, 3, 'v');
  gameioput(SCREENWIDTH+6, 3, 'e');
  gameioput(SCREENWIDTH+7, 3, 'l');
  gameioput(SCREENWIDTH+8, 3, ':');
  gameioput(SCREENWIDTH+9, 3, ' ');
  gameioput(SCREENWIDTH+13, 3, '0'+(playerlevel+1)/10);
  gameioput(SCREENWIDTH+14, 3, '0'+(playerlevel+1)%10);
  gameioput(SCREENWIDTH+3, 4, 'S');
  gameioput(SCREENWIDTH+4, 4, 'c');
  gameioput(SCREENWIDTH+5, 4, 'o');
  gameioput(SCREENWIDTH+6, 4, 'r');
  gameioput(SCREENWIDTH+7, 4, 'e');
  gameioput(SCREENWIDTH+8, 4, ':');
  gameioput(SCREENWIDTH+9, 4, ' ');
  gameioput(SCREENWIDTH+11, 4, '0'+(score+score_plus)/1000);
  gameioput(SCREENWIDTH+12, 4, '0'+((score+score_plus)%1000)/100);
  gameioput(SCREENWIDTH+13, 4, '0'+((score+score_plus)%100)/10);
  gameioput(SCREENWIDTH+14, 4, '0'+(score+score_plus)%10);
  gameioput(SCREENWIDTH+3, 5, 'S');
  gameioput(SCREENWIDTH+4, 5, 'p');
  gameioput(SCREENWIDTH+5, 5, 'e');
  gameioput(SCREENWIDTH+6, 5, 'e');
  gameioput(SCREENWIDTH+7, 5, 'd');
  gameioput(SCREENWIDTH+8, 5, ':');
  gameioput(SCREENWIDTH+9, 5, ' ');
  gameioput(SCREENWIDTH+13, 5, '0'+s/10);
  gameioput(SCREENWIDTH+14, 5, '0'+s%10);
  gameioput(SCREENWIDTH+3, 7, 'L');
  gameioput(SCREENWIDTH+4, 7, 'I');
  gameioput(SCREENWIDTH+5, 7, 'F');
  gameioput(SCREENWIDTH+6, 7, 'E');
  gameioput(SCREENWIDTH+7, 7, ':');
  gameioput(SCREENWIDTH+8, 7, ' ');  
  for(i=0; i<LIFE; i++){
    gameioput(SCREENWIDTH+9+i, 7, ' ');
  }
  for(i=0; i<mobjp[0]->flag; i++){
    gameioput(SCREENWIDTH+9+i, 7, '@');
  }
}

void putoops(void){
  gameioput(mypos.x-1, mypos.y-1, 'O');
  gameioput(mypos.x, mypos.y-1, 'o');
  gameioput(mypos.x+1, mypos.y-1, 'P');
  gameioput(mypos.x+2, mypos.y-1, 's');
  gameioput(mypos.x+3, mypos.y-1, '!');
  gameioput(mypos.x+4, mypos.y-1, '!');
}

void battle(void){   // たたかう時の表示
  buttle = 1;
  int loopnum = 0;
  vector2 tmpv;
  event* e = getnextevent();   // scenarioのmarkを取得、一つ後ろにずらす
  while(1){
    gameiousleep(30000);
    if(time%speedlevel == 0){
      loopnum++;
      scrollwall();
      while(e != NULL){
      	if(e->time == playerlevel){
       	  addmo(e->mobj, e->pos, e->vel);
       	}
	e = getnextevent();
      }
    }
    getstate(&mypos, &isfire);
    putscores();
    putbuttlewalls(SCREENHEIGHT);
    putmo();
    if(loopnum > 1 && countmo() == 1){   // なんでだろうなぁ
      if(speedlevel > 3){  // スピードアップ
	speedlevel -= 1;
      }
      score++;
      buttle = 0;
      break;
    }
    onestepmo();
    if(isfire){   // spaceキーが押された時の処理 bullet
      tmpv = mypos;
      tmpv.x += 1;   // プレイヤーの真ん中から発射！！！するため
      tmpv.y -= 2;
      addmo(mobjp[1], tmpv, makevector2(0,-1));
    }
    if(checkcollision(mypos, objp[1]) != NONOBJ){  // 自分に弾が当たったら
      if(mobjp[0]->bomb(mobjp[0])){
	break;
      }
    }
    mobjp[0]->pos = mypos;
    dispm(mobjp[0]);
    show();
    time++;
  }
  playerlevel++;
}

void gameloop(void){   // 時間の経過に合わせていろいろ処理
  while(1){
    gameiousleep(30000);
    if(playerlevel == LASTBUTTLE){
      break;
    }
    if(score > 0 && score%100 == 0){
      battle();
      resetmark();
      continue;
    }
    if(time%speedlevel == 0){
      scrollwall();
      score++;
    }
    getstate(&mypos, &isfire);
    putscores();
    putwalls(SCREENHEIGHT);
    if(checkcollision(mypos, objp[1]) != NONOBJ){
      if(!(mobjp[0]->flag -= 1)){
	break;
      }
      safepos(&mypos, objp[1]);
      pos = mypos;
    }
    mobjp[0]->pos = mypos;
    dispm(mobjp[0]);
    item();
    show();
    time++;
  }
}

int main(void){   // main
  gameioinit();
  gameioclear();
  init();
  
  gameloop();

  if(playerlevel == LASTBUTTLE && buttle == 0){   // 最後の画面
    attrset(COLOR_PAIR(7));   // 色変更できない
    goal();
    attrset(0);
  }else{
    attrset(COLOR_PAIR(6));
    gameover();
    attrset(0);
  }

  gameiopost();
  printf("\n\nLevel %d \n",playerlevel+1);
  printf("Score %d\n\n\n",score+score_plus);
  return 0;
}
