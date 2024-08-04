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
        printf("|----------------------------|-----------------------------------|--------------------------------------|\n");
        printf("|    Navigation commands     |    File commands                  |    Voter list and sort commands      |\n");
        printf("|----------------------------|-----------------------------------|--------------------------------------|\n");
        printf("|   _pin: Pin command list   |_fcreate: Create new file          |   _newlist: Create new voter list    |\n");
        printf("| _unpin: Unpin command list |                                   |  _loadlist: Load voter list from file|\n");
        printf("|_escape: Break entering data|  _fopen: Open file                |  _sortlist: Sort list by...          |\n");
        printf("|_timing: Start timing test  |                                   |  _showlist: Show current voter list  |\n");
        printf("|  _quit: Close the program  | _fclose: Close file               | _writelist: Write list to file       |\n");
        printf("|                            |                                   |_adddellist: Add voter to list        |\n");
        printf("|----------------------------|-----------------------------------|--------------------------------------|\n");
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

void drawVoterMenu()
{
    if (new_voter_list.used_now == 1)
    {
        printf("== Creating new voter list ==\n\n");
    }
    if (sort_voter_list.used_now == 1)
    {
        printf("== Sorting voter list ==\n\n");
    }
    if (add_del_voter_list.used_now == 1)
    {
        printf("== Adding / deleting voters ==\n\n");
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
    drawVoterMenu();
}

void executeCommand()
{
    static FILE *current_file = NULL;
    static Voter *voter_list = NULL;
    static int list_len = 0;
    char *command;
    int check;
    static int sorted = 0;

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
        else if (strcmp(command, "_timing") == 0)
        {
            _timing();
            check = 1;
        }
        else if (strcmp(command, "_quit") == 0)
        {
            _quit(command, current_file, voter_list, list_len);
            check = 1;
        }
        else if (strcmp(command, "_newlist") == 0)
        {
            if (voter_list != NULL)
                freeVoterList(voter_list, list_len);
            voter_list = _newlist(&list_len);
            drawEverything();
            if (list_len != 1)
                printf("Added %d voters\n", list_len);
            else
                printf("Added %d voter\n", list_len);
            printf("Press enter to continue . . .");
            getchar();
            check = 1;
        }
        else if (strcmp(command, "_loadlist") == 0)
        {
            if (voter_list != NULL)
                freeVoterList(voter_list, list_len);
            voter_list = _loadlist(current_file, &list_len);
            check = 1;
        }
        else if (strcmp(command, "_sortlist") == 0)
        {
            voter_list = _sortlist(voter_list, &list_len, &sorted);
            check = 1;
        }
        else if (strcmp(command, "_showlist") == 0)
        {
            printVoterList(voter_list, list_len);
            check = 1;
        }
        else if (strcmp(command, "_writelist") == 0)
        {
            _writelist(current_file, voter_list, list_len);
            check = 1;
        }
        else if (strcmp(command, "_adddellist") == 0)
        {
            voter_list = _adddellist(voter_list, &list_len, &sorted);
            check = 1;
        }
        else if (strcmp(command, "_genlist") == 0)
        {
            if (voter_list != NULL)
                freeVoterList(voter_list, list_len);
            voter_list = _genlist(&list_len);
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
