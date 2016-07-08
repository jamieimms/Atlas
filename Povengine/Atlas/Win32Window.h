#pragma once
#include <Windows.h>
#include "Window.h"
#include <string>

namespace Atlas
{
	class Win32Window : public Window
	{
	public:
		Win32Window();
		virtual ~Win32Window();

		void setWindowVariables(HINSTANCE hInstance, int nCmdShow);
		bool createWindow(std::wstring title, unsigned int width, unsigned int height);

		virtual LRESULT wmPaintHandler(WPARAM wParam, LPARAM lParam);
		virtual LRESULT wmCommandHandler(WPARAM wParam, LPARAM lParam);
		virtual LRESULT wmKeyDownHandler(WPARAM wParam, LPARAM lParam);
		virtual LRESULT wmKeyUpHandler(WPARAM wParam, LPARAM lParam);
		virtual LRESULT wmCharHandler(WPARAM wParam, LPARAM lParam);
		virtual LRESULT wmMouseMoveHandler(WPARAM wParam, LPARAM lParam);
		virtual LRESULT wmSizeHandler(WPARAM wParam, LPARAM lParam);
		virtual LRESULT wmMoveHandler(WPARAM wParam, LPARAM lParam);

		// Input related messages
		virtual LRESULT wmInputHandler(WPARAM wParam, LPARAM lParam);
		virtual LRESULT wmLButtonDownHandler(WPARAM wParam, LPARAM lParam);
		virtual LRESULT wmRButtonDownHandler(WPARAM wParam, LPARAM lParam);
		virtual LRESULT wmLButtonUpHandler(WPARAM wParam, LPARAM lParam);
		virtual LRESULT wmRButtonUpHandler(WPARAM wParam, LPARAM lParam);

		// Return the handle of this window.
		HWND getWindowHandle();
		HINSTANCE getInstance() { return _hInstance; }

		//int messageLoop();

		static LRESULT CALLBACK staticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		static std::wstring MAIN_WINDOW_CLASS_NAME;

	protected:

		HINSTANCE _hInstance;
		int _nCmdShow;

		HWND _hWnd;

		unsigned int _width;
		unsigned int _height;

	private:

		bool initialiseWindow();

	};
}