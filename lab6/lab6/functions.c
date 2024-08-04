#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

char * mystrrev(char * str)
{
    if (str == NULL || *str == 0)
    {
        return str;
    }
    int i = strlen(str) - 1, j = 0;
    char temp;
    while (i > j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i--;
        j++;
    }
    return str;
}

char * myitoa(int input, int base)
{
    char * result = calloc (1, sizeof (char));
    int i = 0;
    int value = abs(input);
    for(; value > 0; i++, value /= base)
    {
        result[i] = "0123456789abcdef"[value % base];
        result = realloc(result, i + 2);
    }
    if (input < 0)
    {
        result = realloc(result, i + 3);
        result[i] = '-';
        i++;
    }
    result[i] = '\0';
    //printf("myitoa %s\n", result);
    result = mystrrev(result);
    //printf("strrev %s\n", result);
    return result;
}

List * list_new()
{
    return (List *) calloc(1, sizeof (List));
}

void list_delete(List * list)
{
    Item * ptr = list->head, * ptr_prev;
    while (ptr != NULL)
    {
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    free(list);
}

void delHead(List * list)
{
    Item * ptr = list->head, * ptr_prev;
    while (ptr->data != '\0' && ptr != NULL)
    {
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    for (int i = 0; i < 2; i++)
    {
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    list->head = ptr;
}

void list_print(const List * list)
{
    Item * ptr = list->head;
    printf("\"");
    while (ptr != NULL)
    {
        printf("%c", ptr->data);
        ptr = ptr->next;
    }
    printf("\"\n");
}

int list_push_back(List * list, char symbol)
{
    Item * ptr = (Item *) malloc(sizeof (Item));
    if (ptr == NULL)
    {
        return -1;
    }
    ptr->data = symbol;
    ptr->next = NULL;
    if (list->head == NULL)
    {
        list->head = ptr;
        list->tail = ptr;
    }
    else
    {
        list->tail->next = ptr;
        list->tail = ptr;
    }
    return 0;
}

/*int list_insert(List * list, int data)
{
    Item * ptr = list->head, * ptr_prev = NULL;
    while (ptr != NULL && (ptr->data < data))
    {
        ptr_prev = ptr;
        ptr = ptr->next;
    }
    Item * new = (Item *) malloc(sizeof (Item));
    if (new == NULL)
    {
        return -1;
    }
    new->data = data;
    new->next = ptr;
    if (ptr_prev != NULL)
    {
        ptr_prev->next = new;
    }
    else
    {
        list->head = new;
    }
    if (ptr == NULL)
    {
        list->tail = new;
    }
    return 0;
}*/

/*void list_remove(List * list, char symbol)
{
    Item * ptr = list->head, * ptr_prev = NULL;
    while (ptr != NULL && ptr->data != symbol)
    {
        ptr_prev = ptr;
        ptr = ptr->next;
    }
    if (ptr == NULL)
    {
        return;
    }
    if (ptr == list->head)
    {
        list->head = ptr->next;
    }
    if (ptr == list->tail)
    {
        list->tail = ptr_prev;
    }
    if (ptr_prev != NULL)
    {
        ptr_prev->next = ptr->next;
    }
    free(ptr);
}*/

void noExtraSpaces(List * list)
{
    int count = 0;
    {
        Item * ptr = list->head;
        while (ptr != NULL)
        {
            if (ptr->data == '\t')
            {
                ptr->data = ' ';
            }
            ptr = ptr->next;
        }
        free(ptr);
    }
    Item * ptr = list->head;
    while (ptr != NULL)
    {
        if (ptr->data == ' ' && ptr->next != NULL && ptr->next->data == ' ')
        {
            count++;
        }
        ptr = ptr->next;
    }
    free(ptr);
    for (int i = 0; i < count; i++)
    {
        Item * ptr = list->head, * ptr_prev = NULL;
        while (ptr != NULL)
        {
            if (ptr->data == ' ' && ptr_prev != NULL && ptr_prev->data == ' ')
            {
                ptr_prev->next = ptr->next;
                break;
            }
            ptr_prev = ptr;
            ptr = ptr->next;
        }
        if (ptr == NULL)
        {
            return;
        }
        if (ptr == list->head)
        {
            list->head = ptr->next;
        }
        if (ptr == list->tail)
        {
            list->tail = ptr_prev;
        }
        free(ptr);
    }
    //Item * tail = list->tail;
    if (list->head != NULL && list->head->data == ' ')
    {
        list->head = list->head->next;
    }
//    if (tail != head && tail->data == ' ')
//    {
//        Item * ptr = list->head;
//        Item * ptr_prev = NULL;
//        while (ptr != NULL)
//        {
//            ptr_prev = ptr;
//            ptr = ptr->next;
//        }
//        list->tail = ptr_prev;
//    }
//    free(head);
//    free(ptr);
}

int findLetters(const char * input, int size)
{
    if ((input[0] < 48 || input[0] > 57) && input[0] != '-')
    {
        return 1;
    }
    for (int i = 1; i < size; i++)
    {
        if ((input[i] < 48 || input[i] > 57) && input[i] != '\0')
        {
            return 1;
        }
    }
    return 0;
}

void decToHex(List * list)
{
    Item * ptr = list->head;
    Item * last = list->head;
    list_push_back(list, '\0');
    char **arr_hex = malloc(1 * sizeof (char *));
    int hex_num = 0;
    while (ptr != NULL)
    {
        int dec = 0;
        int dec_len = 0;
        while (ptr != NULL && ptr->data != ' ')
        {
            dec_len++;
            ptr = ptr->next;
        }
        char * str_dec = NULL;
        if (dec_len > 0)
        {
            str_dec = malloc(dec_len + 1);
            if (str_dec == NULL)
            {
                printf("Out of memory\n");
                exit(EXIT_FAILURE);
            }
        }
        ptr = last;
        int n = 0;
        while (ptr != NULL && ptr->data != ' ')
        {
            str_dec[n] = ptr->data;
            //printf("\"%c\"\n", ptr->data);
            ptr = ptr->next;
            n++;
        }
        if (ptr != NULL && ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        last = ptr;
        char * str_hex = NULL;
        if (str_dec != NULL)
        {
            str_dec[n] = '\0';
            //printf("str_dec %s\n", str_dec);
            if (findLetters(str_dec, n) == 0)
            {

                dec = atoi(str_dec);
                str_hex = myitoa(dec, 16);
                //printf("dec %d\n", dec);
                if (dec != 0)
                {
                    str_hex = realloc(str_hex, strlen(str_hex) + 3);
                    memmove(str_hex + 2, str_hex, strlen(str_hex) + 1);
                    str_hex[0] = '0';
                    str_hex[1] = 'x';
                    str_hex[strlen(str_hex)] = '\0';
                }
                else
                {
                    str_hex = realloc(str_hex, 4);
                    str_hex[0] = '0';
                    str_hex[1] = 'x';
                    str_hex[2] = '0';
                    str_hex[3] = '\0';
                }
            }
            else
            {
                //printf("str %s\n", str_dec);
                str_hex = realloc(str_hex, strlen(str_dec) + 1);
                strcpy(str_hex, str_dec);
            }
        }
        hex_num++;
        arr_hex = realloc(arr_hex, hex_num * sizeof (char *));
        arr_hex[hex_num - 1] = str_hex;
        //printf("%s\n", str_hex);
        free(str_dec);
    }
    for (int n = 0; n < hex_num; n++)
    {
        list_push_back(list, ' ');
        int j = 0;
        while (arr_hex[n][j] != '\0')
        {
            list_push_back(list, arr_hex[n][j]);
            j++;
        }
        free(arr_hex[n]);
    }
    free(arr_hex);
}
