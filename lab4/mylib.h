#ifndef MYLIB_H
#define MYLIB_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Voter
{
    char *full_name;
    char VSN[8]; //Voting Station Number
    int age;
} Voter;

struct MenuParts
{
    int used_now;
} cmd_list, new_voter_list, sort_voter_list, add_del_voter_list, f_open, f_create, current_file;

char *current_file_name;



//sort
int comparName(const void *a, const void *b);
int comparVSN(const void *a, const void *b);
int comparAge(const void *a, const void *b);
int comparInt(const void *a, const void *b);

void combSort(void *base, size_t nmemb, size_t size, int (*compar) (const void *, const void *));
void shellSort(void *base, size_t nmemb, size_t size, int (*compar) (const void *, const void *));
void selectionSort(void *base, size_t nmemb, size_t size, int (*compar) (const void *, const void *));

//menu
void drawGreeting();
void drawCommandList();
void drawFileMenu();
void drawEverything();
void executeCommand();

//commands
void _quit(char *command, FILE *file, Voter *voter_list, int list_len);
void _pin();
void _unpin();
void _timing();
void _escape();

Voter *_newlist(int *list_len);
Voter *_loadlist(FILE *file, int *list_len);
Voter *_sortlist(Voter *voter_list, int *list_len, int *sorted);
void _writelist(FILE *file, Voter *voterlist, int voter_num);
Voter *_adddellist(Voter *voter_list, int *list_len, int *sorted);
Voter *_genlist(int *list_len);

FILE *_fopen(FILE *previous_file);
FILE *_fcreate(FILE *previous_file);
FILE *_fclose(FILE *file);

//functions
void freeVoterList(Voter *voter_list, int list_len);
int search(Voter *voter_list, int list_len, Voter voter, int field);
Voter newVoter();
char *thisStr(char *input);
Voter *insertByIndex(Voter *voter_list, Voter new_voter, int *list_len, int index);
Voter *delFromIndex(Voter *voter_list, int *list_len, int index, int number);
char *enterName();
char *enterVSN();
int enterAge();
void printVoterList(Voter *voter_list, int list_len);
char *getStr();

#endif

