#include <windows.h>
#include "emulator.h"

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
    for(int i = x1; i<x2; i++) {
        for(int j = y1; j< y2; j++) {
            prStr_CrdClr(i,j, STANDART_COLOR, " ");
        }
    }
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

//Draw a 5x5 lamp on the (x,y) position.
void DrawLamp(int x, int y, Lamp_T self)
{
    if(self.state == OFF) {
        return;
    }
    int i, j;
    for (i = y; i < y+3; i++)
    {
        for (j = x; j < x+3; j++)
        {
            prStr_CrdClr(j, i, self.color, " ");
        }
    }
    prStr_CrdClr(x-1, y+1, self.color, " ");
    prStr_CrdClr(x+1, y-1, self.color, " ");
    prStr_CrdClr(x+1, y+3, self.color, " ");
    prStr_CrdClr(x+3, y+1, self.color, " ");
}

//Draw all lamps + their id`s
void DrawLampList(LampList_T * lamp_list)
{
    int x = DRAW_ALL_LAMPS_START_POS_X, y = DRAW_ALL_LAMPS_START_POS_Y;
    int i;
    //Draw 1-4 lamps
    for(i = 0; i < LAMPS_MAX_COUNT / 2; i++) {
        DrawLamp(x, y, lamp_list->list[i]);
        x += 7;
    }
    //Draw 5-8 lamps
    x = DRAW_ALL_LAMPS_START_POS_X, y = DRAW_ALL_LAMPS_START_POS_Y;
    y += 8;
    for(i = 0; i < LAMPS_MAX_COUNT / 2; i++) {
        DrawLamp(x, y, lamp_list->list[i + 3]);
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
void DrawAboutMenu()
{
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 2);
    setColor(STANDART_COLOR);
    printf("\"1\"-switch all lamps on/off.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 3);
    printf("\"2\"-switch one lamp on/off.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 4);
    printf("\"3\"-switch brightness for one lamp.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 5);
    printf("\"4\"-switch color for one lamp.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 6);
    printf("\"x\"-exit the program.");
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

//Initialize the lamp list with default numbers.
void LampList_constructor(LampList_T * lamp_list)
{
    int i;
    for(i = 0; i < LAMPS_MAX_COUNT; i++)
    {
        lamp_list->list[i].id = i + 1;
        //!!!!!
        lamp_list->list[i].color = RED;
        //!!!!!
        lamp_list->list[i].state = ON;
    }
}
