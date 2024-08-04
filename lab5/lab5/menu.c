#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

void drawGreeting()
{
//    system("clear");
    system("cls");
    printf("== Welcome to the program for working with voter data ==\n");
    printf("Tip: type \"_pin\" or \"_unpin\" to pin/unpin command list\n\n");
}

void drawCommandList()
{
    if (cmd_list.used_now == 1)
    {
        printf("|----------------------------|-------------------------|-------------------------------------|\n");
        printf("|    Navigation commands     |      File commands      |           Matrix commands           |\n");
        printf("|----------------------------|-------------------------|-------------------------------------|\n");
        printf("|   _pin: Pin command list   |_fcreate: Create new file|  _newmatrix: Create new matrix      |\n");
        printf("|                            |                         | _loadmatrix: Load matrix from file  |\n");
        printf("| _unpin: Unpin command list |                         |  _genmatrix: Generate matrix        |\n");
        printf("|                            |  _fopen: Open file      |     _adddel: Operations with matrix |\n");
        printf("|_escape: Break entering data|                         | _showmatrix: Show matrix            |\n");
        printf("|                            |                         | _showmatrix: Show matrix            |\n");
        printf("|  _quit: Close the program  | _fclose: Close file     |_writematrix: Write matrix to file   |\n");
        printf("|----------------------------|-------------------------|   _restosrc: Copy result to source  |\n");
        printf("|----------------------------|-------------------------|-------------------------------------|\n");
        printf("\n");
    }
}

void drawCurrentFile()
{
    if (current_file.used_now == 1)
    {
        printf("Current file: \"%s\"\n\n", current_file_name);
    }
}

void drawMatrixMenu()
{
    if (new_matrix.used_now == 1)
    {
        printf("== Creating matrix ==\n\n");
    }
    if (add_del.used_now == 1)
    {
        printf("== Adding / deleting rows / columns ==\n\n");
    }
}

void drawFileMenu()
{
    if (f_open.used_now == 1)
    {
        printf("== Opening file ==\n\n");
    }
    if (f_create.used_now == 1)
    {
        printf("== Creating file ==\n\n");
    }
}

void drawEverything()
{
//    system("clear");
    system("cls");
    printf("== Program is working ==\n\n");
    drawCommandList();
    drawCurrentFile();
    drawFileMenu();
    drawMatrixMenu();
}

void executeCommand()
{
    static FILE *current_file = NULL;
    static Matrix src_matrix;
    static Matrix res_matrix;
    char *command;
    int check;
    do
    {
        printf(">");
        command = getStr();
        if (strcmp(command, "_pin") == 0)
        {
            _pin();
            check = 1;
        }
        else if (strcmp(command, "_unpin") == 0)
        {
            _unpin();
            check = 1;
        }
        else if (strcmp(command, "_quit") == 0)
        {
            _quit(command, current_file, src_matrix, res_matrix);
            check = 1;
        }
        else if (strcmp(command, "_newmatrix") == 0)
        {
            if (src_matrix.matrix != NULL)
                freeMatrix(src_matrix);
            if (res_matrix.matrix != NULL)
                freeMatrix(res_matrix);
            src_matrix = _newmatrix();
            check = 1;
        }
        else if (strcmp(command, "_loadmatrix") == 0)
        {
            if (src_matrix.matrix != NULL)
                freeMatrix(src_matrix);
            if (res_matrix.matrix != NULL)
                freeMatrix(res_matrix);
            src_matrix = _loadmatrix(current_file);
            check = 1;
        }
        else if (strcmp(command, "_genmatrix") == 0)
        {
            if (src_matrix.matrix != NULL)
                freeMatrix(src_matrix);
            if (res_matrix.matrix != NULL)
                freeMatrix(res_matrix);
            src_matrix = _genmatrix();
            check = 1;
        }
        else if (strcmp(command, "_adddel") == 0)
        {
            if (res_matrix.matrix != NULL)
                freeMatrix(res_matrix);
            res_matrix = _adddel(src_matrix);
            check = 1;
        }
        else if (strcmp(command, "_showmatrix") == 0)
        {
            _showmatrix(src_matrix, res_matrix);
            check = 1;
        }
        else if (strcmp(command, "_writematrix") == 0)
        {
            _writematrix(current_file, src_matrix, res_matrix);
            check = 1;
        }
        else if (strcmp(command, "_restosrc") == 0)
        {
            if (src_matrix.matrix != NULL)
                freeMatrix(src_matrix);
            src_matrix = _restosrc(res_matrix);
            //freeMatrix(res_matrix);
            check = 1;
        }
        else if (strcmp(command, "_fopen") == 0)
        {
            current_file = _fopen(current_file);
            check = 1;
        }
        else if (strcmp(command, "_fcreate") == 0)
        {
            current_file = _fcreate(current_file);
            check = 1;
        }
        else if (strcmp(command, "_fclose") == 0)
        {
            current_file = _fclose(current_file);
            check = 1;
        }
        else
        {
            drawEverything();
            printf("Error: \"%s\" is not a command\n", command);
            check = 0;
        }
        if (check == 1)
            drawEverything();
        free(command);
    }
    while (check == 0);
}
