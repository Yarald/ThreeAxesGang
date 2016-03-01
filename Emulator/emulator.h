#pragma once

#define CONSOLE_SIZE "MODE CON: COLS=78 LINES=23"

#define STANDART_COLOR 007
#define HELP_COLOR 014
#define CONSOLE_WIDTH 78
#define CONSOLE_HEIGHT 22
#define COMMAND_WINDOW_X_END 43
#define COMMAND_WINDOW_Y_END 15
#define BORDER_COLOR 071
#define LAMPS_MAX_COUNT 8

typedef enum LAMP_COLOR{
    WHITE,
    RED,
    GREEN,
    BLUE
} LAMP_COLOR;

typedef enum LAMP_STATE{
    ON,
    OFF
}LAMP_STATE;

typedef struct Lamp {
    int id;
    LAMP_COLOR color;
    LAMP_STATE state;
}Lamp;

void setCoord(int , int );
void setColor(int color);
void prStr_CrdClr(int x, int y, int color, char * line) ;
void lamp_list_constructor(Lamp* lamp_list);
void drawBorders(int xStart, int yStart, int xEnd, int yEnd, int color);

