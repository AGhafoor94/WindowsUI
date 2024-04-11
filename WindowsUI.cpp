// WindowsUI.cpp : Defines the entry point for the application.

#include "framework.h"
#include "WindowsUI.h"

// This is the current instance of the window
HINSTANCE hInstance; 

// place holder to check if the app is running or not
static bool running = false;

/*
	Main function that runs
	Function returns int. Can pass status codes to another program
	https://learn.microsoft.com/en-us/windows/win32/learnwin32/winmain--the-application-entry-point
*/

int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPWSTR lpCommandLine, int nCommandShow) 
{
	const char* className = "Windows UI App";

	// Initialise structure for window.
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexa
	WNDCLASSEXA windowClass = {};
	/*
		https://learn.microsoft.com/en-us/windows/win32/winmsg/window-class-styles

		CS_OWNDC: Allocates a unique device context for each window in the class
		CS_VREDRAW: Redraws entire window if movement or size adjustment changes height of client area
		CS_HREDRAW: Redraws entire window if movement or size adjustment changes width of client area

		Setting properties of the windowClass that I want to use below.
	*/
	windowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	windowClass.lpfnWndProc = {};
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = className;

	return 0;
}