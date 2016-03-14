#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>


#include "emulator.h"

void run() 
{
	LampList_T lampList;
    char userInput_function;
    int userInput_curX, userInput_curY;
    //if 0 - turn the lights off. if 1 - turn the lights on.
    int switchAll_ON_OFF = 1;
    //Initialize the main set of lamps.
    lampList_constructor(&lampList);
    //Initialize the default console size.
    system(CONSOLE_SIZE);
    //Draw the console
    drawAboutMenu();
    drawAllBorders();
    drawLampList(&lampList);
    //Get the user input and do the main algorithm
    prStr_CrdClr(2,2, STANDART_COLOR, "DUSO - ThreeAxesGang");
    userInput_curX = 4;
    userInput_curY = 3;
    prStr_CrdClr(2,3, STANDART_COLOR, ">>");
    setCoord(userInput_curX, userInput_curY);
    while(tolower((userInput_function = getchar())) != 'x') {
        userInput_curY++;
        //Take only the first character.
        while(getchar() != '\n') continue;
        //Turn all lamps on/off
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
        //turn one lamp on/off
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
        //change brightness for all lamps
        else if (tolower(userInput_function) == '3') {
            int userInput_brght;
            drawAboutMenu_ChangeBrght();
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Switching brightness - all lamps");
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "What brightness:");
            userInput_curY++;
            //get the user input - id
            setCoord(userInput_curX, userInput_curY);
            char ch;
            while(scanf("%d", &userInput_brght) != 1 || userInput_brght > 1 || userInput_brght < 0) {
                while((ch = getchar()) != '\n') continue; //read only first symbol
                clearWorkspace(userInput_curX, userInput_curY, COMMAND_WINDOW_X_END - 1, userInput_curY + 3);
                setCoord(userInput_curX, userInput_curY);
            }
            userInput_curY++;
            lampList_changeBrightnessAll(&lampList, userInput_brght);
            drawAboutMenu();
        }
        //change brightness for one lamp
        else if (tolower(userInput_function) == '4') {
            int userInput_brght;
            int userInput_id;
            drawAboutMenu_ChangeBrghtOne();
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Switching brightness - one lamps");
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Lamp id:");
            userInput_curY++;
            //get the user input - lamp id
            setCoord(userInput_curX, userInput_curY);
            char ch;
            while(scanf("%d", &userInput_id) != 1 || userInput_id > 8 || userInput_id < 1) {
                while((ch = getchar()) != '\n') continue; //read only first symbol
                clearWorkspace(userInput_curX, userInput_curY, COMMAND_WINDOW_X_END - 1, userInput_curY + 3);
                setCoord(userInput_curX, userInput_curY);
            }
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Lamp brightness:");
            userInput_curY++;
            //get the user input - brightness
            setCoord(userInput_curX, userInput_curY);
            char ch2;
            while(scanf("%d", &userInput_brght) != 1 || userInput_brght > 1 || userInput_brght < 0) {
                while((ch2 = getchar()) != '\n') continue; //read only first symbol
                clearWorkspace(userInput_curX, userInput_curY, COMMAND_WINDOW_X_END - 1, userInput_curY + 3);
                setCoord(userInput_curX, userInput_curY);
            }
            userInput_curY++;
            lampList_changeBrightnessOne(&lampList, userInput_brght, userInput_id - 1);
            drawAboutMenu();
        }
        //change color for one lamp
        else if (tolower(userInput_function) == '5')  {
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Switching the color for n-th lamp...");
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Done by BorzychV & LemeshkoB");
            userInput_curY++;
        }
        //New year mode
         else if (tolower(userInput_function) == '6')  {
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Enabling New Year mode...");
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Done by BorzychV & LemeshkoB");
            userInput_curY++;
        }
        //wrong input
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
}

//Set cursor position on (x,y) coordinate.
void setCoord(int x, int y)
{
    COORD myCoord = { x, y };
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, myCoord);
}

//Set the color for printing out data.
void setColor(int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color);
}

//Print the borders with the certain color.
void drawBorders(int xStart, int yStart, int xEnd, int yEnd)
{
    int i;
    for (i = xStart; i < xEnd; i++)
        prStr_CrdClr(i, yStart, BORDER_COLOR, " ");
    for(i = xStart; i < xEnd; i++)
        prStr_CrdClr(i, yEnd - 1, BORDER_COLOR, " ");
    for (i = yStart; i < yEnd; i++)
        prStr_CrdClr(xStart, i, BORDER_COLOR, " ");
    for(i = yStart; i < yEnd; i++)
        prStr_CrdClr(xEnd - 1, i, BORDER_COLOR, " ");
}

//Draw all borders on the console
void drawAllBorders() {
    //Print DUSO
    prStr_CrdClr(CONSOLE_WIDTH / 2 - 2, CONSOLE_HEIGHT -1, STANDART_COLOR, "DUSO");
    //Print all borders
    drawBorders(0,0,CONSOLE_WIDTH, CONSOLE_HEIGHT - 1);
    drawBorders(COMMAND_WINDOW_X_END, 0, COMMAND_WINDOW_X_END, CONSOLE_HEIGHT - 1);
    drawBorders(0, COMMAND_WINDOW_Y_END, COMMAND_WINDOW_X_END, COMMAND_WINDOW_Y_END + 1);
    setCoord(USER_INPUT_X, USER_INPUT_Y);
}

//Print the string on the certain position (x,y) with the certain color.
void prStr_CrdClr(int x, int y, int color, char * line)
{
    setCoord(x,y);
    setColor(color);
    printf("%s", line);
    setColor(STANDART_COLOR);
}

//Print the integer on the certain position (x,y) with the certain color.
void prInt_CrdClr(int x, int y, int color, int number)
{
    setCoord(x,y);
    setColor(color);
    printf("%d", number);
    setColor(STANDART_COLOR);
}

//Clear a workspace from (x1,y1) to (x2, y2)
void clearWorkspace(int x1, int y1, int x2, int y2)
{
    int i, j;
    for(i = x1; i<x2; i++) {
        for(j = y1; j< y2; j++) {
            prStr_CrdClr(i,j, STANDART_COLOR, " ");
        }
    }
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

//Draw a 5x5 lamp on the (x,y) position.
void drawLamp(int x, int y, Lamp_T self)
{
    int i,j;
    if(self.state == OFF) {
        for (i = y; i < y+3; i++)
        {
            for (j = x; j < x+3; j++)
            {
                prStr_CrdClr(j, i, NOCOLOR, " ");
            }
        }
        prStr_CrdClr(x-1, y+1, NOCOLOR, " ");
        prStr_CrdClr(x+1, y-1, NOCOLOR, " ");
        prStr_CrdClr(x+1, y+3, NOCOLOR, " ");
        prStr_CrdClr(x+3, y+1, NOCOLOR, " ");
    }
    else if(self.state == ON) {
        for (i = y; i < y+3; i++) {
            for (j = x; j < x+3; j++) {
                prStr_CrdClr(j, i, self.color - DARK * (1 - self.brght), " ");
            }
        }
        prStr_CrdClr(x-1, y+1, self.color - DARK * (1 - self.brght), " ");
        prStr_CrdClr(x+1, y-1, self.color - DARK * (1 - self.brght), " ");
        prStr_CrdClr(x+1, y+3, self.color - DARK * (1 - self.brght), " ");
        prStr_CrdClr(x+3, y+1, self.color - DARK * (1 - self.brght), " ");
    }
    else {
        printf("FATAL ERROR");
        exit(1);
    }
}

//Draw all lamps + their id`s
void drawLampList(LampList_T * lamp_list)
{
    int x = DRAW_ALL_LAMPS_START_POS_X, y = DRAW_ALL_LAMPS_START_POS_Y;
    int i;
    //Draw 1-4 lamps
    for(i = 0; i < LAMPS_MAX_COUNT / 2; i++) {
        drawLamp(x, y, lamp_list->list[i]);
        x += 7;
    }
    //Draw 5-8 lamps
    x = DRAW_ALL_LAMPS_START_POS_X, y = DRAW_ALL_LAMPS_START_POS_Y;
    y += 8;
    for(i = 0; i < LAMPS_MAX_COUNT / 2; i++) {
        drawLamp(x, y, lamp_list->list[i + 4]);
        x += 7;
    }
    //Draw 1-4 id`s
    x = DRAW_ALL_LAMPS_START_POS_X + 1, y = DRAW_ALL_LAMPS_START_POS_Y + 4;
    for(i = 0; i<LAMPS_MAX_COUNT / 2; i++) {
        prInt_CrdClr(x, y, ID_COLOR, lamp_list->list[i].id);
        x+= 7;
    }
    //Draw 5-8 id`s
    x = DRAW_ALL_LAMPS_START_POS_X + 1, y = DRAW_ALL_LAMPS_START_POS_Y + 4;
    y += 8;
    for(i = 0; i<LAMPS_MAX_COUNT / 2; i++) {
        prInt_CrdClr(x, y, ID_COLOR, lamp_list->list[i+4].id);
        x+= 7;
    }
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

//Draw 'About' menu with help for user.
void drawAboutMenu()
{
    clearWorkspace(USER_INPUT_X, COMMAND_WINDOW_Y_END + 1, COMMAND_WINDOW_X_END - 1, CONSOLE_HEIGHT - 2);
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 2);
    setColor(STANDART_COLOR);
    printf("\"1\"-switch all lamps on/off.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 3);
    printf("\"2\"-switch one lamp on/off.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 4);
    printf("\"3\"-switch brightness for all lamps");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 5);
    printf("\"4\"-switch brightness for one lamp.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 6);
    printf("\"5\"-switch color for all lamps.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 7);
    printf("\"6\"-NEW YEAR mode.");
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

//Draw 'About' menu for on-off function
void drawAboutMenu_TurnOnOffOne()
{
    clearWorkspace(USER_INPUT_X, COMMAND_WINDOW_Y_END + 1, COMMAND_WINDOW_X_END - 1, CONSOLE_HEIGHT - 2);
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 2);
    setColor(STANDART_COLOR);
    printf("\"n\"- to switch on/off n-th lamp.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 3);
    printf("n here is the lamp id.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 5);
    printf("Example: | >4 [enter] |");
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

void drawAboutMenu_ChangeBrght()
{
    clearWorkspace(USER_INPUT_X, COMMAND_WINDOW_Y_END + 1, COMMAND_WINDOW_X_END - 1, CONSOLE_HEIGHT - 2);
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 2);
    setColor(STANDART_COLOR);
    printf("0 for dark color.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 3);
    printf("1 for bright color.");
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

void drawAboutMenu_ChangeBrghtOne()
{
    clearWorkspace(USER_INPUT_X, COMMAND_WINDOW_Y_END + 1, COMMAND_WINDOW_X_END - 1, CONSOLE_HEIGHT - 2);
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 2);
    setColor(STANDART_COLOR);
    printf("First number - id (from 0 to 8).");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 3);
    printf("Second number:");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 4);
    printf("0 - dark color.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 5);
    printf("1 - bright color.");
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

//Initialize the lamp list with default numbers.
void lampList_constructor(LampList_T * lamp_list)
{
    int i;
    for(i = 0; i < LAMPS_MAX_COUNT; i++)
    {
        lamp_list->list[i].id = i + 1;
        lamp_list->list[i].brght = HIGH;
        lamp_list->list[i].color = WHITE;
        lamp_list->list[i].state = OFF;
    }
}

//Turn on all the lamps.
void lampList_turnOnAll(LampList_T * lamp_list) {
    int i;
    for(i = 0; i < LAMPS_MAX_COUNT; i++) {
        lamp_list->list[i].state = ON;
    }
}

//Turn off all the lamps.
void lampList_turnOffAll(LampList_T * lamp_list) {
    int i;
    for(i = 0; i < LAMPS_MAX_COUNT; i++) {
        lamp_list->list[i].state = OFF;
    }
}

//Turn on/off only the one lamp.
void lampList_turnOnOffOne(LampList_T * lamp_list, int id) {
    if(id < 1 || id > LAMPS_MAX_COUNT)
        return;
    if(lamp_list->list[id - 1].state == OFF) {
        lamp_list->list[id - 1].state = ON;
    }
    else {
        lamp_list->list[id - 1].state = OFF;
    }
}

//Change brightness for all lamps at one time.
void lampList_changeBrightnessAll(LampList_T * lamp_list, int id_brightness)
{
    for (int i = 0; i < LAMPS_MAX_COUNT; i++){
        lampList_changeBrightnessOne(lamp_list, id_brightness, i);
    }
}

//Change brightness for a single lamp.
void lampList_changeBrightnessOne(LampList_T * lamp_list, int id_brightness, int id)
{
    lamp_list->list[id].brght=id_brightness;
}
