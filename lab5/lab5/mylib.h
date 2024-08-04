#ifndef MYLIB_H
#define MYLIB_H
#include <stdio.h>

typedef struct Matrix
{
    int **matrix;
    int rows;
    int columns;
} Matrix;

struct MenuParts
{
    int used_now;
} cmd_list, new_matrix, add_del, f_open, f_create, current_file;

char *current_file_name;

//menu
void drawGreeting();
void drawCommandList();
void drawEverything();
void executeCommand();

//commands
void _quit(char *command, FILE *file, Matrix src_matrix, Matrix res_matrix);
void _pin();
void _unpin();

Matrix _newmatrix();
Matrix _loadmatrix(FILE *file);
Matrix _genmatrix();
Matrix _adddel(const Matrix src_matrix);
void _showmatrix(Matrix src_matrix, Matrix res_matrix);
void _writematrix(FILE *file, Matrix src_matrix, Matrix res_matrix);

FILE *_fcreate(FILE *previous_file);
FILE *_fopen(FILE *previous_file);
FILE *_fclose(FILE *file);

//functions
char *thisStr(char *input);
void freeMatrix(Matrix matrix);
int digits(int input);
int abs(int input);
int findMax(Matrix matrix);
int findBelowZero(Matrix matrix);

Matrix insertByRow(const Matrix src_matrix, int *row, int index);
Matrix insertByColumn(const Matrix src_matrix, int *column, int index);
Matrix delByRow(const Matrix src_matrix, int index);
Matrix delByColumn(const Matrix src_matrix, int index);
Matrix moveByN(const Matrix src_matrix, int N);

Matrix _restosrc(Matrix res_matrix);
char *getStr();

#endif // MYLIB_H
