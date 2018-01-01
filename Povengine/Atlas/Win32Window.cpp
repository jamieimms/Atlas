#include <Windows.h>
#include <Windowsx.h>
#include <cmath>
#include "Win32Window.h"
#include "AtlasManager.h"
#include "../AtlasAPI/AtlasAPIHelper.h"

using namespace Atlas;

std::string Win32Window::MAIN_WINDOW_CLASS_NAME = "AtlasWin32ApplicationClassName";

Win32Window::Win32Window(AtlasManager* parent)
	:Window(parent)
{
	// Init
	_hInstance = 0;
	_hWnd = 0;
}

Win32Window::~Win32Window() {
}

/// <summary>
///
/// </summary>
void Win32Window::setWindowVariables(HINSTANCE hInstance, int nCmdShow)
{
	_hInstance = hInstance;
	_nCmdShow = nCmdShow;
}

/// <summary>
/// Creates a new window with the given title.
/// </summary>
bool Win32Window::createWindow(std::string& title, unsigned int width, unsigned int height)
{
	if (!initialiseWindow()) {
		return false;
	}

	// Create window
	_width = width;
	_height = height;

	RECT rc = { 0, 0, _width, _height };
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

/// <summary>
/// Implements the interface to show a message box
/// </summary>
bool Win32Window::showMessageBox(AtlasMessageTypeEnum type, std::string title, std::string message, AtlasMessageButtonsEnum buttons)
{
	unsigned int button;
	switch (buttons)
	{
	case AtlasMessageButtonsEnum::AB_OKCancel:
		button = MB_OKCANCEL;
		break;
	//case AtlasMessageButtonsEnum::AB_YesNoCancel:
	//	button = MB_YESNOCANCEL;
	//	break;
	case AtlasMessageButtonsEnum::AB_YesNo:
		button = MB_YESNO;
		break;
	default:
		button = MB_OK;
	}

	switch (type)
	{
	case AtlasMessageTypeEnum::AMT_Error:
		button |= MB_ICONERROR;
		break;
	case AtlasMessageTypeEnum::AMT_Warning:
		button |= MB_ICONWARNING;
		break;
	case AtlasMessageTypeEnum::AMT_Information:
		button |= MB_ICONINFORMATION;
		break;
	}

	int result = MessageBox(_hWnd, message.c_str(), title.c_str(),  button);

	if (result == IDOK || result == IDYES) {
		return true;
	}

	return false;
}

/// <summary>
/// Enables or disables mouse capture inside the window
/// </summary>
void Win32Window::setCaptureMouse(bool enable)
{
	static HWND _prevCap;
	Window::setCaptureMouse(enable);

	int result = ShowCursor(!enable);
	if (enable) {
		_prevCap = SetCapture(_hWnd);
	}
	else {
		ReleaseCapture();
	}
}

/// <summary>
/// Set up and register the window class
/// </summary>
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
		char buf[256];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, error, 0, buf, 256, 0);
		MessageBox(NULL, buf, "Error", MB_OK);
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
	_parent->GetInput()->HandleKeyPress(wParam, true);
	return 0;
}

//
//
LRESULT Win32Window::wmKeyUpHandler(WPARAM wParam, LPARAM lParam)
{
	_parent->GetInput()->HandleKeyPress(wParam, false);

	return 0;
}

LRESULT Win32Window::wmCharHandler(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT Win32Window::wmMouseMoveHandler(WPARAM wParam, LPARAM lParam)
{
	if (_mouseCaptured) {
		int mx = GET_X_LPARAM(lParam);
		int my = GET_Y_LPARAM(lParam);

		POINT p;
		p.x = _width / 2;
		p.y = _height / 2;

		if (mx != (_width / 2) || my != (_height / 2)) {
			_parent->GetInput()->HandleMouseInput(mx, my);

			ClientToScreen(_hWnd, &p);
			SetCursorPos(p.x, p.y);
		}
	}

	return 0;
}

LRESULT Win32Window::wmSizeHandler(WPARAM wParam, LPARAM lParam)
{
	auto height = HIWORD(lParam);
	auto width = LOWORD(lParam);

	_parent->windowSizeChanged(width, height);

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
	int mx = GET_X_LPARAM(lParam);
	int my = GET_Y_LPARAM(lParam);

	_parent->GetInput()->HandleMouseClick(mx, my, true);

	return 0;
}

LRESULT Win32Window::wmRButtonDownHandler(WPARAM wParam, LPARAM lParam)
{
	int mx = GET_X_LPARAM(lParam);
	int my = GET_Y_LPARAM(lParam);

	_parent->GetInput()->HandleMouseClick(mx, my, true);

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


LRESULT CALLBACK Win32Window::staticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Win32Window *window;

	if (message == WM_NCCREATE) {
		// If we're receiving this message then it's the first, so here is where we should set our
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