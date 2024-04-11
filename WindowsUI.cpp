// WindowsUI.cpp : Defines the entry point for the application.

#include "framework.h"
#include "WindowsUI.h"

// This is the current instance of the window
HINSTANCE hInstance; 

// place holder to check if the app is running or not
static bool running = false;
// Callback
LRESULT CALLBACK MainWindowCallback(HWND handleWindow, UINT message, WPARAM wParam, LPARAM lParam);
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

		CS_OWNDC (0x0020): Allocates a unique device context for each window in the class
		CS_VREDRAW (0x0001): Redraws entire window if movement or size adjustment changes height of client area
		CS_HREDRAW (0x0002): Redraws entire window if movement or size adjustment changes width of client area

		Setting properties of the windowClass that I want to use below.
	*/
	windowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	// Bottom property needs this function: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-wndproc
	windowClass.lpfnWndProc = MainWindowCallback;
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = className;

	// Now to register the window class. https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexa
	// Gets the address of windowClass in memory and passes into RegisterClassExA

	if (RegisterClassExA(&windowClass))
	{
		/*
			CreateWindowExA requires:
				- Extended Window Styles: https://learn.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles
				- Class Name (Optional)
				- Window Name (Optional)
				- Window Styles: https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles
				- x-coordinate: Can be set to CW_USEDEFAULT for the default coordinate
				- y-coordinate: Can be set to CW_USEDEFAULT for the default coordinate
				- Width: Can be set to CW_USEDEFAULT for the default coordinate but depends on type of window
				- Height: Can be set to CW_USEDEFAULT for the default coordinate. If Width is set to CW_USEDEFAULT then this is ignored
				- Handle Parent Window Instance (Optional): Can set to 0 if not required 
				- Handle Menu (Optional): Can be set to CW_USEDEFAULT for the default coordinate
				- Handle Window Instance: Passed down from wWinMain function
				- Long Pointer Parameter (Optional): Can be set to NULL / 0
		*/
		HWND handleWindow = CreateWindowExA(0, windowClass.lpszClassName, "Windows UI Name", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);

		if (handleWindow)
		{

		}
	}

	return 0;
}

LRESULT CALLBACK MainWindowCallback(HWND handleWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*
		Callback is where Windows calls us back
			- Handle Window: Passed to us from Windows
			- Message: Windows telling us the value to handle
			- LResult (Long Pointer 64bits): Lets Windows know what to do when certain messages are returned
	*/
	LRESULT result = 0;
	// Switch statement to handle messages like resizing the window
	switch (message)
	{
		default:
			break;
	}
}