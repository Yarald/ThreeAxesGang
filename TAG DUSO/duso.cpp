#include <Windows.h>
#include <locale.h>
#include <cstdio>
#include <cstdlib>
#include <conio.h>

#ifndef TRUE
#define TRUE
#endif // !TRUE


int main(int argc, char *args [])
{
	setlocale(LC_ALL, "rus");
	HANDLE Port = CreateFile("\\\\.\\COM3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	DWORD numbytes, numbytes_ok;
	char command;
	char com[10];

	numbytes = sizeof(command);

	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout = 5;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 0;

	SetCommTimeouts(Port, &CommTimeOuts);

	if (Port != INVALID_HANDLE_VALUE)
	{
		while (TRUE)
		{
			command = _getch();
			if (command == 'x')
			{
				ExitProcess(1);
			}

			com[0] = command;
			WriteFile(Port, com, numbytes, &numbytes_ok, NULL);
		}
	}
	else
	{
		MessageBox(NULL, "Cannot open COM3 port for usage.", "Error", MB_OK);
		ExitProcess(1);
	}

	PurgeComm(Port, PURGE_RXCLEAR);
	PurgeComm(Port, PURGE_TXCLEAR);

	CloseHandle(Port);

	return (0);
}