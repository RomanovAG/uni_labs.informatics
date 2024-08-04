#ifndef MYLIB_H
#define MYLIB_H

typedef struct Item
{
    char data;
    struct Item *next;
} Item;

typedef struct List
{
    Item *head;
    Item *tail;
} List;

List *list_new();
void list_delete(List *list);
void delHead(List * list);
void list_print(const List *list);
int list_push_back(List *list, char symbol);
//int list_insert(List *list, int data);
//void list_remove(List *list, char symbol);
void noExtraSpaces(List * list);
void decToHex(List * list);
char* myitoa(int val, int base);

#endif // MYLIB_H
