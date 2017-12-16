#include "Window.h"


using namespace Atlas;

Window::Window(AtlasManager* parent)
	: _parent(parent), _mouseCaptured(false)
{

}

Window::~Window() 
{

}

void Window::setCaptureMouse(bool enable) 
{
	_mouseCaptured = enable; 
}

