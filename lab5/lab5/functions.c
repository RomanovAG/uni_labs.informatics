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

void freeMatrix(Matrix matrix)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        free(matrix.matrix[i]);
    }
    free(matrix.matrix);
    matrix.matrix = NULL;
    matrix.rows = 0;
    matrix.columns = 0;
}

int digits(int input)
{
    int digits = 0;
    if (input == 0)
        return 1;
    while (abs(input) > 0)
    {
        input /= 10;
        digits++;
    }
    return digits;
}

int abs(int input)
{
    if (input < 0)
        return input * -1;
    else
        return input;
}

int findMax(Matrix matrix)
{
    int max_value = 0;
    for (int row = 0; row < matrix.rows; row++)
    {
        for (int column = 0; column < matrix.columns; column++)
        {
            if (abs(matrix.matrix[row][column]) > abs(max_value))
                max_value = matrix.matrix[row][column];
        }
    }
    return max_value;
}

int findBelowZero(Matrix matrix)
{
    for (int row = 0; row < matrix.rows; row++)
    {
        for (int column = 0; column < matrix.columns; column++)
        {
            if (matrix.matrix[row][column] < 0)
                return -1;
        }
    }
    return 1;
}

Matrix insertByRow(const Matrix src_matrix, int *row, int index)
{
    Matrix res_matrix;
    res_matrix.rows = src_matrix.rows + 1;
    res_matrix.columns = src_matrix.columns;
    res_matrix.matrix = malloc((src_matrix.rows + 1) * sizeof (int*));
    for (int i = 0; i < res_matrix.rows; i++)
    {
        res_matrix.matrix[i] = malloc(res_matrix.columns * sizeof (int));
    }
    for (int row = 0; row < index; row++)
    {
        for (int column = 0; column < res_matrix.columns; column++)
        {
            memcpy(&res_matrix.matrix[row][column], &src_matrix.matrix[row][column], sizeof (int));
        }
    }
    for (int column = 0; column < res_matrix.columns; column++)
    {
        memcpy(&res_matrix.matrix[index][column], &row[column], sizeof (int));
    }
    for (int row = index + 1; row < res_matrix.rows; row++)
    {
        for (int column = 0; column < res_matrix.columns; column++)
        {
            memcpy(&res_matrix.matrix[row][column], &src_matrix.matrix[row - 1][column], sizeof (int));
        }
    }
    return res_matrix;
}

Matrix insertByColumn(const Matrix src_matrix, int *column, int index)
{
    Matrix res_matrix;
    res_matrix.rows = src_matrix.rows;
    res_matrix.columns = src_matrix.columns + 1;
    res_matrix.matrix = malloc(src_matrix.rows * sizeof (int*));
    for (int i = 0; i < res_matrix.rows; i++)
    {
        res_matrix.matrix[i] = malloc((res_matrix.columns + 1) * sizeof (int));
    }
    for (int row = 0; row < res_matrix.rows; row++)
    {
        for (int column = 0; column < index; column++)
        {
            memcpy(&res_matrix.matrix[row][column], &src_matrix.matrix[row][column], sizeof (int));
        }
        memcpy(&res_matrix.matrix[row][index], &column[row], sizeof (int));
        for (int column = index + 1; column < res_matrix.columns; column++)
        {
            memcpy(&res_matrix.matrix[row][column], &src_matrix.matrix[row][column - 1], sizeof (int));
        }
    }
    return res_matrix;
}

Matrix delByRow(const Matrix src_matrix, int index)
{
    Matrix res_matrix;
    res_matrix.rows = src_matrix.rows - 1;
    res_matrix.columns = src_matrix.columns;
    res_matrix.matrix = malloc((src_matrix.rows - 1) * sizeof (int*));
    for (int i = 0; i < res_matrix.rows; i++)
    {
        res_matrix.matrix[i] = malloc(res_matrix.columns * sizeof (int));
    }
    for (int row = 0; row < index; row++)
    {
        for (int column = 0; column < res_matrix.columns; column++)
        {
            memcpy(&res_matrix.matrix[row][column], &src_matrix.matrix[row][column], sizeof (int));
        }
    }
    for (int row = index; row < res_matrix.rows; row++)
    {
        for (int column = 0; column < res_matrix.columns; column++)
        {
            memcpy(&res_matrix.matrix[row][column], &src_matrix.matrix[row + 1][column], sizeof (int));
        }
    }
    return res_matrix;
}

Matrix delByColumn(const Matrix src_matrix, int index)
{
    Matrix res_matrix;
    res_matrix.rows = src_matrix.rows;
    res_matrix.columns = src_matrix.columns - 1;
    res_matrix.matrix = malloc(src_matrix.rows * sizeof (int*));
    for (int i = 0; i < res_matrix.rows; i++)
    {
        res_matrix.matrix[i] = malloc((res_matrix.columns - 1) * sizeof (int));
    }
    for (int row = 0; row < res_matrix.rows; row++)
    {
        for (int column = 0; column < index; column++)
        {
            memcpy(&res_matrix.matrix[row][column], &src_matrix.matrix[row][column], sizeof (int));
        }
        for (int column = index; column < res_matrix.columns; column++)
        {
            memcpy(&res_matrix.matrix[row][column], &src_matrix.matrix[row][column + 1], sizeof (int));
        }
    }
    return res_matrix;
}

Matrix moveByN(const Matrix src_matrix, int N)
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
        int i = 0;
        for (int column = 0; column < src_matrix.columns; column++)
        {
            if (column + N < src_matrix.columns)
            {
                memcpy(&res_matrix.matrix[row][column], &src_matrix.matrix[row][column + N], sizeof (int));
            }
            else
            {
                memcpy(&res_matrix.matrix[row][column], &src_matrix.matrix[row][i], sizeof (int));
                i++;
            }
        }
    }
    return res_matrix;
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
