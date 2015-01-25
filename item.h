/* ITEM.h */
#ifndef _ITEM_H_
#define _ITEM_H_

extern const unsigned char ITEM0;
extern const unsigned char ITEM1;

// gamemain2.c より
void addlife(int num);
void scoreup(int num);

// item.c より
void inititem(void);
void item(void);

#endif
