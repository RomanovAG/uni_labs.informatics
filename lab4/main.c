#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mylib.h"

int main()
{
    cmd_list.used_now = 1;
    drawGreeting();
    drawCommandList();
    while (1)
    {
        executeCommand();
    }
    return 0;
}
