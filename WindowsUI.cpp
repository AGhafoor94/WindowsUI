// WindowsUI.cpp : Defines the entry point for the application.

#include "framework.h"
#include "WindowsUI.h"

// place holder to check if the app is running or not
static bool running = false;
// Callback
LRESULT CALLBACK MainWindowCallback(HWND handleWindow, UINT message, WPARAM wParam, LPARAM lParam);

HMENU AddMenuItems(HWND handleWindow);
/*
	Main function that runs
	Function returns int. Can pass status codes to another program
	https://learn.microsoft.com/en-us/windows/win32/learnwin32/winmain--the-application-entry-point
*/

int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPWSTR lpCommandLine, int nCommandShow) 
{
	const char* className = "Peace for Palestine";

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
	// 
	windowClass.cbSize = sizeof(windowClass);
	windowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	// Bottom property needs this function: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-wndproc
	windowClass.lpfnWndProc = MainWindowCallback;
	windowClass.hCursor = LoadCursorA(hInstance, IDC_ARROW);
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
		HWND handleWindow = CreateWindowExA(0, windowClass.lpszClassName, "Peace for Palestine", WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);

		if (handleWindow)
		{
			// Get messages when running

			running = true;
			while (running)
			{
				// Create message instance
				MSG message;
				/*
					Retrieves message from calling thread queue.
					https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage

					GetMessage([out] message, handleWindow, wMsgFilterMin, wMsgFilterMax)
					Might be returning a -1 so need to handle that
				*/
				BOOL messageResult = GetMessage(&message, handleWindow, 0, 0);
				if (messageResult > 0)
				{
					// Translate virtual key messages into character messages. Posted so that the next time a thread calls GetMessage or PeekMessage, the message can be read
					TranslateMessage(&message);
					// Dispatches a message to a window procedure, used to dispatch message retreived by GetMessage
					DispatchMessageA(&message);
				}
				else {
					OutputDebugStringA("Log errors here\n");
				}
			}
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

	// HTTPS REST requests: https://learn.microsoft.com/en-us/windows/win32/wininet/http-sessions

	LRESULT result = 0;
	// Switch statement to handle messages like resizing the window
	// https://learn.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues#system-defined-messages
	// Using: https://learn.microsoft.com/en-us/windows/win32/winmsg/window-notifications
	switch (message)
	{
		case WM_ACTIVATEAPP:
			// https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-activateapp
			running = true;
			OutputDebugStringA("WM_ACTIVATEAPP\n");
			break;
		case WM_SIZE:
			// https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-sizing
			OutputDebugStringA("WM_SIZE\n");
			break;
		case WM_CLOSE:
			// https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-close
			OutputDebugStringA("WM_CLOSE\n");
			running = false;
			break;
		case WM_CREATE:
			AddMenuItems(handleWindow);
			break;
		case WM_COMMAND:
			// Handle the menu items
			switch (wParam)
			{
				case 1:
					MessageBoxA(handleWindow, "File has been clicked", "File", 0);
					break;
				case 2:
					MessageBoxA(handleWindow, "Help has been clicked", "Help", 0);
					break;
				default:
					break;
			}
			break;
		case WM_DESTROY:
			// https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-destroy
			OutputDebugStringA("WM_DESTROY\n");
			PostQuitMessage(0);
			running = false;
			break;
		case WM_PAINT:
			{
				// paint the window
				PAINTSTRUCT paint;
				HDC deviceContext = BeginPaint(handleWindow, &paint);
				EndPaint(handleWindow, &paint);
				break;
			}
		default:
			// Handle all other messages
			// DefWindowProc: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-defwindowproca
			result = DefWindowProcA(handleWindow, message, wParam, lParam);
			break;
	}
	return result;
}

HMENU AddMenuItems(HWND handleWindow)
{
	/*
		Creating Menus:
			- Have to create an instance of HMENU
			- Append to the window. 1 is the ID of the menu item. When the message is passed back WM_COMMAND we can find it
			- Set the menu
	*/
	HMENU handleMenu = CreateMenu();
	// Drop down menu

	HMENU fileMenu = CreateMenu();

	AppendMenuA(handleMenu, MF_POPUP,(UINT_PTR) fileMenu, "File");
	AppendMenuA(fileMenu, MF_STRING,1, "Test");
	AppendMenuA(handleMenu, MF_STRING, 2, "Help");

	SetMenu(handleWindow, handleMenu);

	return handleMenu;
}