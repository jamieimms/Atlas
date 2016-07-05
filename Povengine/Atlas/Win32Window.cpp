#include <Windows.h>
#include "Win32Window.h"

using namespace Atlas;

std::wstring Win32Window::MAIN_WINDOW_CLASS_NAME = L"AtlasWin32ApplicationClassName";

Win32Window::Win32Window()
{

	// Init
	_hInstance = 0;
	_hWnd = 0;
}

Win32Window::~Win32Window() {

}

void Win32Window::setWindowVariables(HINSTANCE hInstance, int nCmdShow)
{
	_hInstance = hInstance;
	_nCmdShow = nCmdShow;
}

// createWindow
// Creates a new window with the given title.
bool Win32Window::createWindow(std::wstring title)
{
	if (!initialiseWindow()) {
		return false;
	}

	// Create window

	RECT rc = { 0, 0, 800, 600 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	_hWnd = CreateWindow(MAIN_WINDOW_CLASS_NAME.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, _hInstance,
		this);
	if (!_hWnd) {
		return false;
	}

	ShowWindow(_hWnd, _nCmdShow);

	return true;
}

bool Win32Window::initialiseWindow()
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Win32Window::staticWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = MAIN_WINDOW_CLASS_NAME.c_str();
	// wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
	wcex.hIconSm = 0;
	if (!RegisterClassEx(&wcex)) {
		DWORD error = GetLastError();
		wchar_t buf[256];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, error, 0, buf, 256, 0);
		MessageBox(NULL, buf, L"Error", MB_OK);
		return false;
	}

	return true;
}


LRESULT Win32Window::wmPaintHandler(WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(_hWnd, &ps);
	EndPaint(_hWnd, &ps);

	return 0;
}

LRESULT Win32Window::wmCommandHandler(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT Win32Window::wmKeyDownHandler(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

//
//
LRESULT Win32Window::wmKeyUpHandler(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT Win32Window::wmCharHandler(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT Win32Window::wmMouseMoveHandler(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT Win32Window::wmSizeHandler(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT Win32Window::wmMoveHandler(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT Win32Window::wmInputHandler(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT Win32Window::wmLButtonDownHandler(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT Win32Window::wmRButtonDownHandler(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
LRESULT Win32Window::wmLButtonUpHandler(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
LRESULT Win32Window::wmRButtonUpHandler(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

HWND Win32Window::getWindowHandle()
{
	return _hWnd;
}


// MessageLoop
// Static method of the Window class, will be used for our application message loop.
int Win32Window::messageLoop()
{
	// Main message loop
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}


LRESULT CALLBACK Win32Window::staticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Win32Window *window;

	if (message == WM_NCCREATE) {
		// If we're receiving this message then it's the first, so here is where we should set oour
		// user data so we can call the correct instance version of the wndproc.  We've stored the calling
		// Window in the lParam of the create window.
		window = (Win32Window *)((LPCREATESTRUCT)lParam)->lpCreateParams;

		SetWindowLongPtr(hWnd, GWLP_USERDATA, (long)window);

	}
	else {
		// otherwise, call the instance version
		window = (Win32Window *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}

	if (window) {
		return window->wndProc(hWnd, message, wParam, lParam);
	}
	else {
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK Win32Window::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		return wmCommandHandler(wParam, lParam);
	case WM_PAINT:
		return wmPaintHandler(wParam, lParam);
	case WM_SIZE:
		return wmSizeHandler(wParam, lParam);
	case WM_MOVE:
		return wmMoveHandler(wParam, lParam);

		// Input related messages
	case WM_INPUT:
		return wmInputHandler(wParam, lParam);
	case WM_KEYDOWN:
		return wmKeyDownHandler(wParam, lParam);
	case WM_KEYUP:
		return wmKeyUpHandler(wParam, lParam);
	case WM_CHAR:
		return wmCharHandler(wParam, lParam);
	case WM_MOUSEMOVE:
		return wmMouseMoveHandler(wParam, lParam);
	case WM_LBUTTONDOWN:
		return wmLButtonDownHandler(wParam, lParam);
	case WM_RBUTTONDOWN:
		return wmRButtonDownHandler(wParam, lParam);
	case WM_LBUTTONUP:
		return wmLButtonUpHandler(wParam, lParam);
	case WM_RBUTTONUP:
		return wmRButtonUpHandler(wParam, lParam);

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}