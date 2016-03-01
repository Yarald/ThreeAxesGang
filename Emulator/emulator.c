#include <windows.h>
#include "emulator.h"

//Set cursor position on (x,y) coordinate.
void setCoord(int x, int y) {
	COORD myCoord = { x, y };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, myCoord);
}

//Set the color for printing out data.
void setColor(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}

//Print the string on the certain position (x,y) with the certain color.
void prStr_CrdClr(int x, int y, int color, char * line) {
    setCoord(x,y);
    setColor(color);
    printf("%s", line);
    setColor(STANDART_COLOR);
}

//Draw a 5x5 lamp on the (x,y) position.
void DrawLamp(int x, int y,int color) {
	int i, j;
	for (i = y; i < y+3; i++) {
		for (j = x; j < x+3; j++) {
            prStr_CrdClr(j, i, color, " ");
        }
	}
	prStr_CrdClr(x-1, y+1, color, " ");
	prStr_CrdClr(x+1, y-1, color, " ");
	prStr_CrdClr(x+1, y+3, color, " ");
	prStr_CrdClr(x+3, y+1, color, " ");
}

void lamp_list_constructor(Lamp *lamp_list){
    int i;
    for(i = 0; i <LAMPS_MAX_COUNT; i++){
        lamp_list[i].id = i + 1;
        lamp_list[i].color = WHITE;
        lamp_list[i].state = OFF;
    }
}

void drawBorders(int xStart, int yStart, int xEnd, int yEnd, int color) {
	int i;
	for (i = xStart; i < xEnd; i++) {
        prStr_CrdClr(i, yStart, color, " ");
        prStr_CrdClr(i, yEnd-1, color, " ");
	}
	for (i = yStart; i < yEnd; i++) {
        prStr_CrdClr(xStart, i, color, " ");
        prStr_CrdClr(xEnd - 1, i, color, " ");
	}
}
