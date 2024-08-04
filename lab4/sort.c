#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

int comparName(const void *a, const void *b)
{
    Voter voter1 = *(Voter*) a;
    Voter voter2 = *(Voter*) b;
    return strcmp(voter1.full_name, voter2.full_name);
}

int comparVSN(const void *a, const void *b)
{
    Voter voter1 = *(Voter*) a;
    Voter voter2 = *(Voter*) b;
    return strcmp(voter1.VSN, voter2.VSN);
}

int comparAge(const void *a, const void *b)
{
    return (*(Voter*) a).age - (*(Voter*) b).age;
}

int comparInt(const void *a, const void *b)
{
    return *(int*) a - *(int*) b;
}

void combSort(void *base, size_t nmemb, size_t size, int (*compar) (const void *, const void *))
{
    float factor = 1.247;
    void *temp = malloc(size);
    for (int step = nmemb - 1; step >= 1; step /= factor)
    {
        for(unsigned i = 0; i + step < nmemb; i++)
        {
            if (compar((char*) base + i * size, (char*) base + (i + step) * size) > 0)
            {
                memcpy(temp, (char*) base + i * size, size);
                memcpy((char*) base + i * size, (char*) base + (i + step) * size, size);
                memcpy((char*) base + (i + step) * size, temp, size);
            }
        }
    }
    free(temp);
}

void shellSort(void *base, size_t nmemb, size_t size, int (*compar) (const void *, const void *))
{
    void *temp = malloc(size);
    for (int step = nmemb / 2; step > 0; step /= 2)
    {
        for (unsigned i = step; i < nmemb; i++)
        {
            for (int j = i - step; j >= 0 && compar((char*) base + j * size, (char*) base + (j + step) * size) > 0; j -= step)
            {
                memcpy(temp, (char*) base + j * size, size);
                memcpy((char*) base + j * size, (char*) base + (j + step) * size, size);
                memcpy((char*) base + (j + step) * size, temp, size);
            }
        }
    }
    free(temp);
}

void selectionSort(void *base, size_t nmemb, size_t size, int (*compar) (const void *, const void *))
{
    int k;
    void *x = malloc(size);
    for (unsigned i = 0; i < nmemb; i++)
    {
        memcpy(x, (char*) base + i * size, size);
        k = i;
        for (unsigned j = i + 1; j < nmemb; j++)
        {
            if (compar((char*) base + j * size, x) < 0)
            {
                k = j;
                memcpy(x, (char*) base + j * size, size);
            }
        }
        memmove((char*) base + k * size, (char*) base + i * size, size);
        memcpy((char*) base + i * size, x, size);
    }
    free(x);
}

void selectionSort2(void *base, size_t nmemb, size_t size, int (*compar) (const void *, const void *))
{
    void *temp = malloc(size);
    for (unsigned i = 0; i < nmemb - 1; i++)
    {
        int min_i = i;
        for (unsigned j = i + 1; j < nmemb; j++)
        {
            if (compar((char*) base + j * size, (char*) base + min_i * size) < 0)
            {
                min_i = j;
            }
        }
        memcpy(temp, (char*) base + i * size, size);
        memcpy((char*) base + i * size, (char*) base + (min_i) * size, size);
        memcpy((char*) base + (min_i) * size, temp, size);
    }
    free(temp);
}
