#include <stdio.h>
#include <stdlib.h>
#include "emulator.h"

int main()
{
    system(CONSOLE_SIZE);
    Lamp lamp_list[LAMPS_MAX_COUNT];
    lamp_list_constructor(lamp_list);
    int i;
    for(i = 0; i < 8; i++){
        printf("%d ", lamp_list[i].id);
        printf("%d ", lamp_list[i].color);
        printf("%d ", lamp_list[i].state);
        printf("\n");
    }

    return 0;
}



