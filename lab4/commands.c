#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mylib.h"

void _quit(char *command, FILE *file, Voter *voter_list, int list_len)
{
    char *answer = NULL;
    do
    {
        drawEverything();
        printf("Are you sure you want to close the program? (y/n)\n");
        printf(">");
        answer = getStr();
        if (strcmp(answer, "y") == 0)
        {
            //            system("clear");
            system("cls");
            freeVoterList(voter_list, list_len);
            free(command);
            free(answer);
            if (file != NULL)
            {
                free(current_file_name);
                fclose(file);
            }
            exit(0);
        }
        else if (strcmp(answer, "n") == 0)
        {
            free(answer);
            break;
        }
        free(answer);
    }
    while (1);
}

void _pin()
{
    cmd_list.used_now = 1;
}

void _unpin()
{
    cmd_list.used_now = 0;
}

void _timing()
{
    int arr_len;
    int MAX;
    clock_t comb = 0, shell = 0, selection = 0;

    drawEverything();
    printf("== Timing ==\n\n");
    printf("Enter array length: ");
    scanf("%d", &arr_len);
    printf("Enter max value: ");
    scanf("%d", &MAX);
    for (int i = 0; i < 10; i++)
    {
        int *arr1 = malloc(arr_len * sizeof (int));
        for (int i = 0; i < arr_len; i++)
        {
            arr1[i] = rand() % MAX;
        }
        int *arr2 = malloc(arr_len * sizeof (int));
        memcpy(arr2, arr1, arr_len);
        int *arr3 = malloc(arr_len * sizeof (int));
        memcpy(arr3, arr1, arr_len);


        clock_t start = clock();
        combSort(arr1, arr_len, sizeof (int), comparInt);
        clock_t end = clock();
        comb += end - start;

        start = clock();
        combSort(arr2, arr_len, sizeof (int), comparInt);
        end = clock();
        shell += end - start;

        start = clock();
        combSort(arr3, arr_len, sizeof (int), comparInt);
        end = clock();
        selection += end - start;
        free(arr1);
        free(arr2);
        free(arr3);
    }
    comb /= 10;
    shell /= 10;
    selection /= 10;
    printf("     Comb sort time: %.8Lf\n", (long double) comb / CLOCKS_PER_SEC);
    printf("    Shell sort time: %.8Lf\n", (long double) shell / CLOCKS_PER_SEC);
    printf("Selection sort time: %.8Lf\n", (long double) selection / CLOCKS_PER_SEC);
    printf("Press enter to continue . . .");
    getchar();
    scanf("%*c");
}

Voter *_newlist(int *list_len)
{
    new_voter_list.used_now = 1;
    int i = 0;
    Voter *voter_list = malloc(sizeof (Voter));
    do
    {
        voter_list = realloc(voter_list, (i + 1) * sizeof (Voter));
        Voter new_voter = newVoter();
        if (strcmp(new_voter.full_name, "_escape") == 0 || strcmp(new_voter.VSN, "_escape") == 0 || new_voter.age == 0)
        {
            free(new_voter.full_name);
            new_voter_list.used_now = 0;
            break;
        }
        voter_list[i] = new_voter;
        i++;
    }
    while (1);
    if (i == 0)
    {
        free(voter_list);
        return NULL;
    }
    *list_len = i;
    return voter_list;
}

Voter *_loadlist(FILE *file, int *list_len)
{
    if (file == NULL)
    {
        printf("No files are opened\n");
        printf("Press enter to continue . . .");
        getchar();
        return NULL;
    }
    fseek(file, 0, SEEK_SET);
    int voter_num;
    fscanf(file, "%d", &voter_num);
    Voter *voter_list = malloc(sizeof (Voter) * voter_num);
    for (int i = 0; i < voter_num; i++)
    {
        int name_len;
        fscanf(file, "%d", &name_len);
        voter_list[i].full_name = malloc(name_len * sizeof (char));
        char *name = malloc(name_len);
        fscanf(file, "%s", name);
        memcpy(voter_list[i].full_name, name, name_len - 1);
        voter_list[i].full_name[name_len - 1] = '\0';
        free(name);
        char *vsn = malloc(8 * sizeof (char));
        fscanf(file, "%s", vsn);
        memcpy(voter_list[i].VSN, vsn, 7);
        voter_list[i].VSN[7] = '\0';
        free(vsn);
        fscanf(file, "%d", &voter_list[i].age);
    }
    fseek(file, 0, SEEK_SET);
    *list_len = voter_num;
    printf("Done\n");
    printf("Press enter to continue . . .");
    getchar();
    return voter_list;
}

Voter *_sortlist(Voter *voter_list, int *list_len, int *sorted)
{
    if (voter_list == NULL)
    {
        printf("List is empty\n");
        printf("Press enter to continue . . .");
        getchar();
        return NULL;
    }
    sort_voter_list.used_now = 1;
    int field = -1;
    int sort = -1;
    do
    {
        drawEverything();
        printf("Choose field of the structure to sort by\n");
        printf("0: _escape\n");
        printf("1: Full name\n");
        printf("2: Voting station number\n");
        printf("3: Age\n");
        printf(">");
        scanf("%d", &field);
        if (field == 0)
            return 0;
        else if (field < 0 || field > 3)
        {
            printf("Please try again\n");
            printf("Press enter to continue . . .");
            getchar();
        }
    }
    while (field < 0 || field > 3);
    do
    {
        drawEverything();
        printf("Select sort\n");
        printf("0: _escape\n");
        printf("1: Comb sort\n");
        printf("2: Shell sort\n");
        printf("3: Selection sort\n");
        printf(">");
        scanf("%d", &sort);
        if (sort == 0)
            return voter_list;
        else if (sort < 0 || sort > 3)
        {
            printf("Please try again\n");
            printf("Press enter to continue . . .");
            getchar();
        }
    }
    while (sort < 0 || sort > 3);
    if (field == 1 && sort == 1)
    {
        combSort(voter_list, *list_len, sizeof (Voter), comparName);
    }
    else if (field == 1 && sort == 2)
    {
        shellSort(voter_list, *list_len, sizeof (Voter), comparName);
    }
    else if (field == 1 && sort == 3)
    {
        selectionSort(voter_list, *list_len, sizeof (Voter), comparName);
    }
    else if (field == 2 && sort == 1)
    {
        combSort(voter_list, *list_len, sizeof (Voter), comparVSN);
    }
    else if (field == 2 && sort == 2)
    {
        shellSort(voter_list, *list_len, sizeof (Voter), comparVSN);
    }
    else if (field == 2 && sort == 3)
    {
        selectionSort(voter_list, *list_len, sizeof (Voter), comparVSN);
    }
    else if (field == 3 && sort == 1)
    {
        combSort(voter_list, *list_len, sizeof (Voter), comparAge);
    }
    else if (field == 3 && sort == 2)
    {
        shellSort(voter_list, *list_len, sizeof (Voter), comparAge);
    }
    else if (field == 3 && sort == 3)
    {
        selectionSort(voter_list, *list_len, sizeof (Voter), comparAge);
    }
    scanf("%*c");
    printf("Done\n");
    printf("Press enter to continue . . .");
    getchar();
    sort_voter_list.used_now = 0;
    *sorted = field;
    return voter_list;
}

void _writelist(FILE *file, Voter *voter_list, int voter_num)
{
    if (file == NULL)
    {
        printf("No files are opened\n");
        printf("Press enter to continue . . .");
        getchar();
        return;
    }
    if (voter_list == NULL)
    {
        printf("List is empty\n");
        printf("Press enter to continue . . .");
        getchar();
        return;
    }
    fseek(file, 0, SEEK_SET);
    fprintf(file, "%d\n", voter_num);
    for (int i = 0; i < voter_num; i++)
    {
        fprintf(file, "%d\n", strlen(voter_list[i].full_name) + 1);
        fprintf(file, "%s\n", voter_list[i].full_name);
        fprintf(file, "%s\n", voter_list[i].VSN);
        fprintf(file, "%d\n", voter_list[i].age);
    }
    fseek(file, 0, SEEK_SET);
    printf("Done\n");
    printf("Press enter to continue . . .");
    getchar();
    return;
}

Voter *_adddellist(Voter *voter_list, int *list_len, int *sorted)
{
    if (voter_list == NULL)
    {
        printf("List is empty\n");
        printf("Press enter to continue . . .");
        getchar();
        return NULL;
    }
    add_del_voter_list.used_now = 1;
    int choice;
    do
    {
        drawEverything();
        printf("Select choice\n");
        printf("0: _escape\n");
        printf("1: Insert by index\n");
        printf("2: Insert into sorted array\n");
        printf("3: Delete from index\n");
        printf(">");
        scanf("%d", &choice);
        scanf("%*c");
        if (choice == 0)
        {
            add_del_voter_list.used_now = 0;
            return voter_list;
        }
        else if (choice < 0 || choice > 3)
        {
            printf("Please try again\n");
            printf("Press enter to continue . . .");
            getchar();
        }
    }
    while (choice < 0 || choice > 3);
    if (choice == 1)
    {
        int index;
        Voter new_voter = newVoter();
        if (strcmp(new_voter.full_name, "_escape") == 0 || strcmp(new_voter.VSN, "_escape") == 0 || new_voter.age == 0)
        {
            free(new_voter.full_name);
            add_del_voter_list.used_now = 0;
            return voter_list;
        }
        do
        {
            drawEverything();
            printf("Enter index (must be between 1 and %d): ", *list_len + 1);
            scanf("%d", &index);
            scanf("%*c");
            if (index == 0)
            {
                add_del_voter_list.used_now = 0;
                return voter_list;
            }
            else if (index < 0 || index > *list_len + 1)
            {
                printf("Please try again\n");
                printf("Press enter to continue . . .");
                getchar();
            }
        }
        while (index < 0 || index > *list_len + 1);
        voter_list = insertByIndex(voter_list, new_voter, list_len, index - 1);
        *sorted = 0;
    }
    else if (choice == 2)
    {
        if (*sorted == 0)
        {
            printf("Array is not sorted\n");
            printf("Press enter to continue . . .");
            getchar();
            add_del_voter_list.used_now = 0;
            return voter_list;
        }
        Voter new_voter = newVoter();
        if (strcmp(new_voter.full_name, "_escape") == 0 || strcmp(new_voter.VSN, "_escape") == 0 || new_voter.age == 0)
        {
            free(new_voter.full_name);
            add_del_voter_list.used_now = 0;
            return voter_list;
        }
        int index = search(voter_list, *list_len, new_voter, *sorted);
        voter_list = insertByIndex(voter_list, new_voter, list_len, index - 1);
    }
    else if (choice == 3)
    {
        int index;
        do
        {
            drawEverything();
            printf("Enter index (must be between 1 and %d): ", *list_len);
            scanf("%d", &index);
            scanf("%*c");
            if (index == 0)
            {
                add_del_voter_list.used_now = 0;
                return voter_list;
            }
            else if (index < 0 || index > *list_len)
            {
                printf("Please try again\n");
                printf("Press enter to continue . . .");
                getchar();
            }
        }
        while (index < 0 || index > *list_len);
        int number;
        do
        {
            drawEverything();
            printf("Enter number of voters to delete (you can maximum delete %d voters): ", *list_len - index + 1);
            scanf("%d", &number);
            scanf("%*c");
            if (number == 0)
            {
                add_del_voter_list.used_now = 0;
                return voter_list;
            }
            else if (number < 0 || number > *list_len - index + 1)
            {
                printf("Please try again\n");
                printf("Press enter to continue . . .");
                getchar();
            }
        }
        while (number < 0 || number > *list_len - index + 1);
        voter_list = delFromIndex(voter_list, list_len, index - 1, number);
    }
    printf("Done\n");
    printf("Press enter to continue . . .");
    getchar();
    add_del_voter_list.used_now = 0;
    return voter_list;
}

Voter *_genlist(int *list_len)
{
    srand(time(NULL));
    drawEverything();
    printf("Enter list length: ");
    scanf("%d", list_len);
    Voter *voter_list = malloc(*list_len * sizeof (Voter));
    for (int i = 0; i < *list_len; i++)
    {
        int name_len = 3 + rand()%15;
        voter_list[i].full_name = malloc(name_len * sizeof (char));
        char *name = malloc(name_len * sizeof (char));
        name[0] = 65 + rand()%(90 - 65 + 1);
        for (int k = 1; k < name_len - 1; k++)
        {
            name[k] = 97 + rand()%(122 - 97 + 1);
        }
        name[name_len - 1] = '\0';
        strcpy(voter_list[i].full_name, name);
        free(name);
        voter_list[i].VSN[3] = '-';
        voter_list[i].VSN[7] = '\0';
        for (int l = 0; l < 3; l++)
        {
            voter_list[i].VSN[l] = 97 + rand()%(122 - 97 + 1);
        }
        for (int l = 4; l < 7; l++)
        {
            voter_list[i].VSN[l] = 48 + rand()%(57 - 48 + 1);
        }
        voter_list[i].age = 18 + rand()%(118 - 18 + 1);
    }
    scanf("%*c");
    printf("Done\n");
    printf("Press enter to continue . . .");
    getchar();
    return voter_list;
}

FILE *_fcreate(FILE *previous_file)
{
    if (previous_file != NULL)
    {
        char *answer = NULL;
        do
        {
            drawEverything();
            printf("This will close opened file. Continue? (y/n)\n");
            printf(">");
            answer = getStr();
            if (strcmp(answer, "y") == 0)
            {
                //system("clear");
                free(answer);
                break;
            }
            else if (strcmp(answer, "n") == 0)
            {
                free(answer);
                return previous_file;
            }
            free(answer);
        }
        while (1);
        fclose(previous_file);
    }
    f_create.used_now = 1;
    FILE *file;
    char *file_name;
    do
    {
        drawEverything();
        printf("Enter file name: ");
        file_name = getStr();
        if (strcmp(file_name, "_escape") == 0)
        {
            f_create.used_now = 0;
            return NULL;
        }
        file = fopen(file_name, "w");
        if (file == NULL)
        {
            perror("Error occured while creating file");
            printf("Please try again or type \"_escape\"\n");
            printf("Press enter to continue . . .");
            getchar();
        }
        else
        {
            if (current_file_name != NULL)
                free(current_file_name);
            current_file_name = thisStr(file_name);
            printf("Created\n");
            printf("Press enter to continue . . .");
            getchar();
            f_create.used_now = 0;
            current_file.used_now = 1;
            free(file_name);
            return file;
        }
        free(file_name);
    }
    while (1);
}

FILE *_fopen(FILE *previous_file)
{
    if (previous_file != NULL)
    {
        char *answer = NULL;
        do
        {
            drawEverything();
            printf("This will close opened file. Continue? (y/n)\n");
            printf(">");
            answer = getStr();
            if (strcmp(answer, "y") == 0)
            {
                system("clear");
                free(answer);
                break;
            }
            else if (strcmp(answer, "n") == 0)
            {
                free(answer);
                return previous_file;
            }
            free(answer);
        }
        while (1);
        fclose(previous_file);
    }
    f_open.used_now = 1;
    FILE *file;
    char *file_name;
    do
    {
        drawEverything();
        printf("Enter file name: ");
        file_name = getStr();
        if (strcmp(file_name, "_escape") == 0)
        {
            free(file_name);
            f_open.used_now = 0;
            return NULL;
        }
        file = fopen(file_name, "r+");
        if (file == NULL)
        {
            perror("Error occured while opening file to read");
            printf("Please try again or type \"_escape\"\n");
            printf("Press enter to continue . . .");
            getchar();
        }
        else
        {
            if (current_file_name != NULL)
                free(current_file_name);
            current_file_name = thisStr(file_name);
            printf("Opened\n");
            printf("Press enter to continue . . .");
            getchar();
            f_open.used_now = 0;
            current_file.used_now = 1;
            free(file_name);
            return file;
        }
        free(file_name);
    }
    while (1);
}

FILE *_fclose(FILE *file)
{
    if (file == NULL)
    {
        printf("No files are opened\n");
        printf("Press enter to continue . . .");
        getchar();
        return NULL;
    }
    free(current_file_name);
    fclose(file);
    current_file.used_now = 0;
    printf("Closed\n");
    printf("Press enter to continue . . .");
    getchar();
    return NULL;

}
