#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "emulator.h"

int main()
{
    LampList_T lampList;
    char userInput_function;
    int userInput_curX, userInput_curY;
    int switchAll_ON_OFF = 1; //if 0 - turn the lights off. if 1 - turn the lights on.
    //Initialize the main set of lamps.
    lampList_constructor(&lampList);
    //Initialize the default console size.
    system(CONSOLE_SIZE);
    //Draw the console
    drawAboutMenu();
    drawAllBorders();
    drawLampList(&lampList);
    //Get the user input and do the main algorithm
    prStr_CrdClr(2,2, STANDART_COLOR, "DUSO - TAG team");
    userInput_curX = 4;
    userInput_curY = 3;
    prStr_CrdClr(2,3, STANDART_COLOR, ">>");
    setCoord(userInput_curX, userInput_curY);
    while(tolower((userInput_function = getchar())) != 'x')
    {
        userInput_curY++;
        //Take only the first character.
        while(getchar() != '\n') continue;
        //Start of the if-else conditions ladder.
        if(tolower(userInput_function) == '1') {
            if(switchAll_ON_OFF == 1) {
                prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Switching on all lamps...");
                userInput_curY++;
                lampList_turnOnAll(&lampList);
                switchAll_ON_OFF = 0;
            }
            else if (switchAll_ON_OFF == 0) {
                prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Switching off all lamps...");
                userInput_curY++;
                lampList_turnOffAll(&lampList);
                switchAll_ON_OFF = 1;
            }
            else {
                system("cls");
                prStr_CrdClr(0,0,STANDART_COLOR, "Fatal error in the \"userInput_function == '1'\" function");
                userInput_curX = 0;
                userInput_curY = 1;
            }
        }
        else if (tolower(userInput_function) == '2') {
            int userInput_lampID;
            drawAboutMenu_TurnOnOffOne();
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Switching on/off n-th lamp");
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "What lamp to switch:");
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, ">>");
            userInput_curX+=2;
            //get the user input
            setCoord(userInput_curX, userInput_curY);
            userInput_curX-=2;
            char ch;
            while(scanf("%d", &userInput_lampID) != 1 || userInput_lampID < 1 || userInput_lampID > 8) {
                while((ch = getchar()) != '\n') continue; //read only the first symbol.
                clearWorkspace(userInput_curX, userInput_curY, COMMAND_WINDOW_X_END - 1, userInput_curY + 3);
                setCoord(userInput_curX, userInput_curY);
            }
            userInput_curY++;
            lampList_turnOnOffOne(&lampList, userInput_lampID);
            //In the end - redraw 'about' menu.
            drawAboutMenu();
        }
        else if (tolower(userInput_function) == '3') {
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Switching the brightness for n-th lamp");
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Done by AndrienkoF & RomaniykS");
            userInput_curY++;
        }
        else if (tolower(userInput_function) == '4') {
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Switching the color for n-th lamp");
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Done by BorzychV & LemeshkoB");
            userInput_curY++;
        }
        else {
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Wrong input. Look at the list below.");
            userInput_curY++;
        }
        //End of the user Input.
        prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Press [enter] to continue...");
        while(getchar() != '\n') continue;
        //Clear the workspace. Redraw lampList.
        clearWorkspace(USER_INPUT_X, USER_INPUT_Y, COMMAND_WINDOW_X_END - 1, COMMAND_WINDOW_Y_END - 1);
        drawAboutMenu();
        drawAllBorders();
        drawLampList(&lampList);
        //Set userInput (x,y) by default. Print '>' again.
        userInput_curX = 4;
        userInput_curY = 3;
        prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, ">>");
    }
    //Clear the screen, when user wants to exit the program.
    system("cls");
    return (0);
}
