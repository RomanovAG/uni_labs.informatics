#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mylib.h"

char *thisStr(char *input)
{
    char *output = (char*) malloc((strlen(input) + 1) * sizeof (char));
    strcpy(output, input);
    return output;
}

void freeVoterList(Voter *voter_list, int list_len)
{
    for (int i = 0; i < list_len; i++)
    {
        free(voter_list[i].full_name);
    }
    free(voter_list);
}

int search(Voter *voter_list, int list_len, Voter voter, int field)
{
    if (field == 1)
    {
        for (int index = 0; index < list_len; index++)
        {
            if (strcmp(voter_list[index].full_name, voter.full_name) >= 0)
                return index + 1;
        }
    }
    else if (field == 2)
    {
        for (int index = 0; index < list_len; index++)
        {
            if (strcmp(voter_list[index].VSN, voter.VSN) >= 0)
                return index + 1;
        }
    }
    else if (field == 3)
    {
        for (int index = 0; index < list_len; index++)
        {
            if (voter_list[index].age >= voter.age )
                return index + 1;
        }
    }
    return -1;
}

char *moveArr(char *input, int i)
{
    char *moved_input = input;

    while (input[i] != '\0')
    {
        moved_input[i] = moved_input[i + 1];
        i++;
    }
    return moved_input;
}

Voter newVoter()
{
    Voter new_voter;
    char *name = enterName();
    if (strcmp(name, "_escape") == 0)
    {
        new_voter.full_name = (char*) malloc(8);
        strcpy(new_voter.full_name, name);
        free(name);
        return new_voter;
    }
    else
    {
        new_voter.full_name = (char*) malloc(strlen(name) + 1);
        strcpy(new_voter.full_name, name);
        free(name);
    }
    char *vsn = enterVSN();
    if (strcmp(vsn, "_escape") == 0)
    {
        memcpy(new_voter.VSN, vsn, 8);
        free(vsn);
        return new_voter;
    }
    else
    {
        memcpy(new_voter.VSN, vsn, 8);
        free(vsn);
    }
    new_voter.age = enterAge();
    if (new_voter.age == 0)
    {
        return new_voter;
    }
    return new_voter;
}

Voter *insertByIndex(Voter *voter_list, Voter new_voter, int *list_len, int index)
{
    Voter *new_voter_list = malloc((*list_len + 1) * sizeof (Voter));
    for (int i = 0; i < index; i++)
    {
        memcpy(&new_voter_list[i], &voter_list[i], sizeof (Voter));
    }
    new_voter_list[index] = new_voter;
    for (int j = index + 1; j <= *list_len; j++)
    {
        memcpy(&new_voter_list[j], &voter_list[j - 1], sizeof (Voter));
    }
    free(voter_list);
    *list_len = *list_len + 1;
    return new_voter_list;
}

Voter *delFromIndex(Voter *voter_list, int *list_len, int index, int number)
{
    if (index == 0 && number == *list_len)
    {
        return NULL;
    }
    Voter *new_voter_list = malloc((*list_len - number) * sizeof (Voter));
    for (int i = 0; i < index; i++)
    {
        memcpy(&new_voter_list[i], &voter_list[i], sizeof (Voter));
    }
    for (int j = index; j < index + number; j++)
        free(voter_list[j].full_name);
    if (*list_len - number - index == 0)
    {
        free(voter_list);
        *list_len = *list_len - number;
        return new_voter_list;
    }
    for (int j = index; j <= *list_len - number - index + 1; j++)
    {
        memcpy(&new_voter_list[j], &voter_list[j + number], sizeof (Voter));
    }
    free(voter_list);
    *list_len = *list_len - number;
    return new_voter_list;
}

char *noExtraSpaces(char *input)
{
    char *result;
    result = input;
    int i = 0, prev_space = 0, result_len;

    while (input[i] != '\0')
    {
        if (result[i] == '\t')
            result[i] = ' ';
        if (input[i] == ' ')
        {
            if (i == 0 || prev_space == 1)
                result = moveArr(result, i);
            else
            {
                prev_space = 1;
                i++;
            }
        }
        else
        {
            prev_space = 0;
            i++;
        }
    }
    result_len = strlen(result);
    if (result[result_len - 1] == ' ' && result[result_len] == '\0')
        result[result_len - 1] = '\0';
    return result;
}

char *getStr()
{
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;

    do
    {
        n = scanf("%80[^\n]", buf);
        if (n < 0)
        {
            if (!res)
            {
                return NULL;
            }
        }
        else if (n > 0)
        {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        }
        else
        {
            scanf("%*c");
        }
    } while (n > 0);
    if (len > 0)
    {
        res[len] = '\0';
    }
    else
    {
        res = calloc(1, sizeof(char));
    }
    return res;
}

char *enterName()
{
    char *name = NULL;
    do
    {
        drawEverything();
        printf("Enter voter full name: ");
        name = getStr();
        if (strcmp(name, "_escape") == 0)
        {
            return name;
        }
        else if (name == NULL)
        {
            printf("Invalid name. Try again\n");
            free(name);
            printf("Press enter to continue . . .");
            getchar();
        }
        else if (strcmp(name, "") == 0 || (name[0]) < 65 || name[0] > 90)
        {
            printf("Invalid name. Please try again\n");
            free(name);
            printf("Press enter to continue . . .");
            getchar();
        }
        else
        {
            return name;
        }
    }
    while (1);
}

char *enterVSN()
{
    char *vsn = NULL;
    int check;
    do
    {
        drawEverything();
        printf("Enter Voting Station Number (VSN): ");
        vsn = getStr();
        check = 1;
        if (strcmp(vsn, "_escape") == 0)
        {
            return vsn;
        }
        if (strlen(vsn) != 7)
        {
            printf("Incorrect data has been entered. Please try again. Input format: AAA-000\n");
            free(vsn);
            printf("Press enter to continue . . .");
            getchar();
            check = 0;
        }
        else if (vsn[3] != '-')
        {
            printf("Incorrect data has been entered. Please try again. Input format: AAA-000\n");
            free(vsn);
            printf("Press enter to continue . . .");
            getchar();
            check = 0;
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                if (((int) vsn[i] < 65 || ((int) vsn[i] > 90 && (int) vsn[i] < 97) || (int) vsn[i] > 122) && check != 0)
                {
                    printf("Incorrect data has been entered. Please try again. Input format: AAA-000\n");
                    free(vsn);
                    printf("Press enter to continue . . .");
                    getchar();
                    check = 0;
                }
            }
            for (int i = 4; i < 7; i++)
            {
                if (((int) vsn[i] < 48 || (int) vsn[i] > 57) && check != 0)
                {
                    printf("Incorrect data has been entered. Please try again. Input format: AAA-000\n");
                    free(vsn);
                    printf("Press enter to continue . . .");
                    getchar();
                    check = 0;
                }
            }
        }
    }
    while (check == 0);
    return vsn;
}

int enterAge()
{
    int age;
    do
    {
        drawEverything();
        printf("Enter voter age (or type \"0\" to escape): ");
        scanf("%d", &age);
        if (age == 0)
            return 0;
        if (age > 118 || age < 18)
        {
            printf("Invalid voter age (must be between 18 and 118). Try again\n");
            printf("Press enter to continue . . .");
            getchar();
        }
    }
    while (age > 118 || age < 18);
    scanf("%*c");
    return age;
}

void printVoterList(Voter *voter_list, int list_len)
{
    drawEverything();
    if (voter_list == NULL || list_len == 0)
    {
        printf("List is empty\n");
        printf("Press enter to continue . . .");
        getchar();
        return;
    }
    for (int i = 0; i < list_len; i++)
    {
        printf("Voter %d\n", i + 1);
        printf("\tFull name: %s\n", voter_list[i].full_name);
        printf("\t      VSN: %s\n", voter_list[i].VSN);
        printf("\t      Age: %d\n", voter_list[i].age);
        printf("\n");
    }
    printf("Total voters: %d\n", list_len);
    printf("Press enter to continue . . .");
    getchar();
}
