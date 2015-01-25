/* bidlist.c */
#include <bidlist.h>
#include <stdio.h>
#include <stdlib.h>

bidlist* newbidlist(void){   // bidlistの初期値設定
  bidlist* ret = (bidlist*)malloc(sizeof(bidlist));
  ret->head = NULL;
  ret->tail = NULL;
  ret->mark = NULL;
  ret->count = 0;
  return ret;
}

int bidlistadd(bidlist* blist, void* data){   // blistに新しい要素を付け加える
  bidnode* newnode = (bidnode*)malloc(sizeof(bidnode));
  newnode->data = data; 
  newnode->prev = blist->tail; 
  newnode->next = NULL;
  if(blist->tail != NULL){
    blist->tail->next = newnode;
  }    
  blist->tail = newnode;
  if(blist->head == NULL){
    blist->head = newnode;
  }
  blist->count++;
  return blist->count;   // blistの最新の要素数を返す
}

int bidlistremove(bidlist* blist, bidnode* node){   // blistから要素を取り除く
  bidnode* prev = node->prev;
  bidnode* next = node->next;
  if(blist->mark == node){
    blist->mark = node->next;
  }
  if(next != NULL){
    next->prev = prev;
  }else{
    blist->tail = prev;
  }
  if(prev != NULL){
    prev->next = next;
  }else{
    blist->head = next;
  }
  free(node);
  blist->count--;
  return blist->count;   // blistの最新の要素数を返す
}

int bidlistcount(bidlist* blist){   // bidlistの要素数を返す
  return blist->count;
}

bidnode* bidlistget(bidlist* blist, int num){   // blistのnum番目の要素を返す
  int i;
  bidnode* point = blist->head;
  for(i=0; i<num; i++){
    point = point->next;
  }
  return point;
}

void bidlistreset(bidlist* blist){   // blistのmarkにheadを代入
  blist->mark = blist->head;
}

bidnode* bidlistnext(bidlist* blist){   // blistのmarkを一つ後ろにする
  bidnode* ret = blist->mark;
  if(ret != NULL){
    blist->mark = blist->mark->next;
  }
  return ret;
}

bidnode* bidlistsetmark(bidlist* blist, bidnode* node){  // blistのmarkをnodeに
  blist->mark = node;
  return node;
}
