#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mylib.h"

void _quit(char *command, FILE *file, Matrix src_matrix, Matrix res_matrix)
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
            if (src_matrix.matrix != NULL)
                freeMatrix(src_matrix);
            if (res_matrix.matrix != NULL)
                freeMatrix(res_matrix);
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

Matrix _newmatrix()
{
    drawEverything();
    new_matrix.used_now = 1;
    Matrix matrix;
    printf("Enter number of rows: ");
    scanf("%d", &matrix.rows);
    if (matrix.rows == 0)
    {
        new_matrix.used_now = 0;
        return matrix;
    }
    printf("Enter number of columns: ");
    scanf("%d", &matrix.columns);
    if (matrix.columns == 0)
    {
        new_matrix.used_now = 0;
        return matrix;
    }
    matrix.matrix = malloc(matrix.rows * sizeof (int*));
    for (int i = 0; i < matrix.rows; i++)
    {
        matrix.matrix[i] = malloc(matrix.columns * sizeof (int));
    }
    for (int row = 0; row < matrix.rows; row++)
    {
        printf("Enter row %d: ", row + 1);
        for (int column = 0; column < matrix.columns; column++)
        {
            scanf("%d", &matrix.matrix[row][column]);
        }
    }
    scanf("%*c");
    printf("Done\n");
    printf("Press enter to continue . . .");
    getchar();
    return matrix;
}

Matrix _loadmatrix(FILE *file)
{
    if (file == NULL)
    {
        printf("No files are opened\n");
        printf("Press enter to continue . . .");
        getchar();
        Matrix null_matrix;
        null_matrix.rows = 0;
        return null_matrix;
    }
    fseek(file, 0, SEEK_SET);
    Matrix matrix;
    fscanf(file, "%d", &matrix.rows);
    fscanf(file, "%d", &matrix.columns);
    matrix.matrix = malloc(matrix.rows * sizeof (int*));
    for (int i = 0; i < matrix.rows; i++)
    {
        matrix.matrix[i] = malloc(matrix.columns * sizeof (int));
    }
    for (int row = 0; row < matrix.rows; row++)
    {
        for (int column = 0; column < matrix.columns; column++)
        {
            fscanf(file, "%d", &matrix.matrix[row][column]);
        }
    }
    printf("Done\n");
    printf("Press enter to continue . . .");
    getchar();
    return matrix;
}

Matrix _genmatrix()
{
    srand(time(NULL));
    Matrix matrix;
    matrix.rows = 2 + rand()%(10 - 2 + 1);
    matrix.columns = 2 + rand()%(10 - 2 + 1);
    matrix.matrix = malloc(matrix.rows * sizeof (int*));
    for (int i = 0; i < matrix.rows; i++)
    {
        matrix.matrix[i] = malloc(matrix.columns * sizeof (int));
    }
    for (int row = 0; row < matrix.rows; row++)
    {
        for (int column = 0; column < matrix.columns; column++)
        {
            matrix.matrix[row][column] = -100 + rand()%199;
        }
    }

    printf("Done\n");
    printf("Press enter to continue . . .");
    getchar();
    return matrix;
}

Matrix _adddel(const Matrix src_matrix)
{
    if (src_matrix.matrix == NULL)
    {
        printf("Source matrix is empty\n");
        printf("Press enter to continue . . .");
        getchar();
        Matrix null_matrix;
        null_matrix.matrix = NULL;
        null_matrix.rows = 0;
        null_matrix.columns = 0;
        return null_matrix;
    }
    add_del.used_now = 1;
    int choice;
    do
    {
        drawEverything();
        printf("Select choice\n");
        printf("0: _escape\n");
        printf("1: Insert row\n");
        printf("2: Insert column\n");
        printf("3: Delete row\n");
        printf("4: Delete column\n");
        printf("5: Move elements inside rows\n");
        printf(">");
        scanf("%d", &choice);
        scanf("%*c");
        if (choice == 0)
        {
            add_del.used_now = 0;
            Matrix null_matrix;
            null_matrix.matrix = NULL;
            null_matrix.rows = 0;
            null_matrix.columns = 0;
            return null_matrix;
        }
        else if (choice < 0 || choice > 5)
        {
            printf("Please try again\n");
            printf("Press enter to continue . . .");
            getchar();
        }
    }
    while (choice < 0 || choice > 5);
    Matrix res_matrix;
    if (choice == 1)
    {
        int *row = malloc(src_matrix.columns * sizeof (int));
        drawEverything();
        printf("Enter row (row length = %d): ", src_matrix.columns);
        for (int i = 0; i < src_matrix.columns; i++)
        {
            scanf("%d", &row[i]);
        }
        int index;
        do
        {
            drawEverything();
            printf("Enter row index to insert (must be between 1 and %d): ", src_matrix.rows + 1);
            scanf("%d", &index);
            scanf("%*c");
            if (index == 0)
            {
                free(row);
                add_del.used_now = 0;
                return src_matrix;
            }
            else if (index < 0 || index > src_matrix.rows + 1)
            {
                printf("Please try again\n");
                printf("Press enter to continue . . .");
                getchar();
            }
        }
        while (index < 0 || index > src_matrix.rows + 1);
        res_matrix = insertByRow(src_matrix, row, index - 1);
        free(row);
    }
    else if (choice == 2)
    {
        int *column = malloc(src_matrix.rows * sizeof (int));
        drawEverything();
        printf("Enter column (column length = %d): ", src_matrix.rows);
        for (int i = 0; i < src_matrix.rows; i++)
        {
            scanf("%d", &column[i]);
        }
        int index;
        do
        {
            drawEverything();
            printf("Enter column index to insert (must be between 1 and %d): ", src_matrix.columns + 1);
            scanf("%d", &index);
            scanf("%*c");
            if (index == 0)
            {
                free(column);
                add_del.used_now = 0;
                return src_matrix;
            }
            else if (index < 0 || index > src_matrix.columns + 1)
            {
                printf("Please try again\n");
                printf("Press enter to continue . . .");
                getchar();
            }
        }
        while (index < 0 || index > src_matrix.columns + 1);
        res_matrix = insertByColumn(src_matrix, column, index - 1);
        free(column);
    }
    else if (choice == 3)
    {
        drawEverything();
        int index;
        do
        {
            drawEverything();
            printf("Enter row index to delete (must be between 1 and %d): ", src_matrix.rows);
            scanf("%d", &index);
            scanf("%*c");
            if (index == 0)
            {
                add_del.used_now = 0;
                return src_matrix;
            }
            else if (index < 0 || index > src_matrix.rows)
            {
                printf("Please try again\n");
                printf("Press enter to continue . . .");
                getchar();
            }
        }
        while (index < 0 || index > src_matrix.rows);
        res_matrix = delByRow(src_matrix, index - 1);
    }
    else if (choice == 4)
    {
        drawEverything();
        int index;
        do
        {
            drawEverything();
            printf("Enter column index to delete (must be between 1 and %d): ", src_matrix.columns);
            scanf("%d", &index);
            scanf("%*c");
            if (index == 0)
            {
                add_del.used_now = 0;
                return src_matrix;
            }
            else if (index < 0 || index > src_matrix.columns)
            {
                printf("Please try again\n");
                printf("Press enter to continue . . .");
                getchar();
            }
        }
        while (index < 0 || index > src_matrix.columns);
        res_matrix = delByColumn(src_matrix, index - 1);
    }
    else
    {
        drawEverything();
        int N;
        drawEverything();
        printf("Enter N: ");
        scanf("%d", &N);
        scanf("%*c");
        if (N == 0)
        {
            add_del.used_now = 0;
            return src_matrix;
        }
        res_matrix = moveByN(src_matrix, N);
    }
    add_del.used_now = 0;
    printf("Done\n");
    printf("Press enter to continue . . .");
    getchar();
    return res_matrix;
}

void _showmatrix(Matrix src_matrix, Matrix res_matrix)
{
    if (src_matrix.matrix == NULL)
    {
        printf("Source matrix is empty\n");
        printf("Press enter to continue . . .");
        getchar();
        return;
    }
    int max_value = findMax(src_matrix);
    printf("\n");
    printf("Source matrix:\n\n");
    for (int row = 0; row < src_matrix.rows; row++)
    {
        for (int column = 0; column < src_matrix.columns; column++)
        {
            if (digits(src_matrix.matrix[row][column]) < digits(max_value))
            {
                for (int i = 0; i < digits(max_value) - digits(src_matrix.matrix[row][column]); i++)
                    printf(" ");
            }
            if (findBelowZero(src_matrix) < 0 && src_matrix.matrix[row][column] >= 0)
                printf(" ");
            printf("%d ", src_matrix.matrix[row][column]);
        }
        printf("\n\n");
    }
    if (res_matrix.matrix == NULL)
    {
        printf("Press enter to continue . . .");
        getchar();
        return;
    }
    else
    {
        int max_value = findMax(res_matrix);
        printf("\n");
        printf("Result matrix:\n\n");
        for (int row = 0; row < res_matrix.rows; row++)
        {
            for (int column = 0; column < res_matrix.columns; column++)
            {
                if (digits(res_matrix.matrix[row][column]) < digits(max_value))
                {
                    for (int i = 0; i < digits(max_value) - digits(res_matrix.matrix[row][column]); i++)
                        printf(" ");
                }
                if (findBelowZero(res_matrix) < 0 && res_matrix.matrix[row][column] >= 0)
                    printf(" ");
                printf("%d ", res_matrix.matrix[row][column]);
            }
            printf("\n\n");
        }
    }
    printf("Press enter to continue . . .");
    getchar();
    return;
}

void _writematrix(FILE *file, Matrix src_matrix, Matrix res_matrix)
{
    if (file == NULL)
    {
        printf("No files are opened\n");
        printf("Press enter to continue . . .");
        getchar();
        return;
    }
    int choice;
    printf("What matrix do you want to write to file?\n");
    printf("1: Source matrix\n");
    printf("2: Result matrix\n");
    printf(">");
    scanf("%d", &choice);
    scanf("%*c");
    if (choice == 1)
    {
        if (src_matrix.rows == 0)
        {
            printf("Matrix is empty\n");
            printf("Press enter to continue . . .");
            getchar();
            return;
        }
        fseek(file, 0, SEEK_SET);
        fprintf(file, "%d\n", src_matrix.rows);
        fprintf(file, "%d\n", src_matrix.columns);
        for (int i = 0; i < src_matrix.rows; i++)
        {
            for (int j = 0; j < src_matrix.columns; j++)
            {
                fprintf(file, "%d ", src_matrix.matrix[i][j]);
            }
            fprintf(file, "\n");
        }
    }
    else if (choice == 2)
    {
        if (res_matrix.rows == 0)
        {
            printf("Matrix is empty\n");
            printf("Press enter to continue . . .");
            getchar();
            return;
        }
        fseek(file, 0, SEEK_SET);
        fprintf(file, "%d\n", res_matrix.rows);
        fprintf(file, "%d\n", res_matrix.columns);
        for (int i = 0; i < res_matrix.rows; i++)
        {
            for (int j = 0; j < res_matrix.columns; j++)
            {
                fprintf(file, "%d ", res_matrix.matrix[i][j]);
            }
            fprintf(file, "\n");
        }
    }
    else
    {
        return;
    }
    printf("Done\n");
    printf("Press enter to continue . . .");
    getchar();
}

Matrix _restosrc(Matrix src_matrix)
{
    Matrix res_matrix;
    res_matrix.rows = src_matrix.rows;
    res_matrix.columns = src_matrix.columns;
    res_matrix.matrix = malloc(src_matrix.rows * sizeof (int*));
    for (int i = 0; i < res_matrix.rows; i++)
    {
        res_matrix.matrix[i] = malloc(res_matrix.columns * sizeof (int));
    }
    for (int row = 0; row < res_matrix.rows; row++)
    {
        for (int column = 0; column < res_matrix.columns; column++)
        {
            memcpy(&res_matrix.matrix[row][column], &src_matrix.matrix[row][column], sizeof (int));
        }
    }
    return res_matrix;
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
            free(file_name);
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
