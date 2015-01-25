/* scenario.c */
#include <stdio.h>
#include <scenario.h>

static bidlist* scenario;
static int mark;

void initscenario(void){   // scenarioの初期化
  scenario = newbidlist();
  mark = 0;
} 

void addevent(event* ev){   // scenarioにevを追加
  bidlistadd(scenario, ev);
}

void resetmark(void){   // scenario->markにscenario->head を代入
  bidlistreset(scenario); 
  mark = 0;
}

int getcurrentmark(void){   // markを返す
  return mark;
}

void setmark(int pos){   // scenario->markの設定
  int cnt = bidlistcount(scenario);   // scenarioの要素数を取得
  if(pos < cnt){
    mark = pos;
    bidlistsetmark(scenario, bidlistget(scenario, mark));
  }else{
    mark = cnt;
    bidlistsetmark(scenario, scenario->tail); 
  }
}

event* getnextevent(void){   
  event* ret = NULL;
  bidnode* node = bidlistnext(scenario);   // markをnodeに代入して一つ後ろに
  if(node != NULL){
    ret = (event*)(node->data);
  }
  return ret;
}
