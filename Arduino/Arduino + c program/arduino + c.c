#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <strings.h>

int main(void)
{
    HANDLE hComm;
    char lpBuffer[2];
    DWORD dNoOfBytesToWrite = sizeof(lpBuffer);
    DWORD dNoOfBytesWritten = 0;
    hComm = CreateFile("\\\\.\\COM3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if(hComm == INVALID_HANDLE_VALUE)
    {
        printf("Error in opening serial port");
        CloseHandle(hComm);
        exit(1);
    }
    else
    {
        printf("Opening serial port successful");
    }
    while(strcmp(lpBuffer, "q") != 0)
    {
       gets(lpBuffer);
       WriteFile(hComm, lpBuffer, dNoOfBytesToWrite, &dNoOfBytesWritten, NULL);
    }
    CloseHandle(hComm);
    return (0);
}
