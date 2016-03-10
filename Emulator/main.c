#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emulator.h"

int main()
{
    system(CONSOLE_SIZE);
    LampList_T lampList;
    char userInput;
    //Initialization of the set of lamps
    LampList_constructor(&lampList);
    //Draw console and the invitation
    prStr_CrdClr(12,2, STANDART_COLOR, "Choose the function.");
    DrawAboutMenu();
    drawAllBorders();
    DrawLampList(&lampList);
    //Get the user input and do the main algorithm
    setCoord(USER_INPUT_X,USER_INPUT_Y);
    while((userInput = getchar())!= 'x')
    {
        clearWorkspace(USER_INPUT_X, USER_INPUT_Y, COMMAND_WINDOW_X_END - 1, COMMAND_WINDOW_Y_END - 1);
        DrawLampList(&lampList);

    }
    system("cls");
    return (0);
}
