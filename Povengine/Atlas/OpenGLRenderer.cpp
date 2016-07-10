#include "OpenGLRenderer.h"
#include <gl/GL.h>
#include <gl/GLU.h>

using namespace Atlas;

OpenGLRenderer::OpenGLRenderer() {

}

OpenGLRenderer::~OpenGLRenderer()
{
#ifdef WIN32

	wglMakeCurrent(_deviceContext, NULL);
	wglDeleteContext(_renderContext);

#endif
#ifdef __linux__

	// Linux deinit code goes here

#endif
}

bool OpenGLRenderer::Initialise(unsigned int width, unsigned int height, HWND hwnd)
{
#ifdef WIN32
	_deviceContext = GetDC(hwnd);
	/*      Pixel format index
	*/
	int nPixelFormat;


	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),          //size of structure
		1,                                      //default version
		PFD_DRAW_TO_WINDOW |                    //window drawing support
		PFD_SUPPORT_OPENGL |                    //opengl support
		PFD_DOUBLEBUFFER,                       //double buffering support
		PFD_TYPE_RGBA,                          //RGBA color mode
		32,                                     //32 bit color mode
		0, 0, 0, 0, 0, 0,                       //ignore color bits
		0,                                      //no alpha buffer
		0,                                      //ignore shift bit
		0,                                      //no accumulation buffer
		0, 0, 0, 0,                             //ignore accumulation bits
		16,                                     //16 bit z-buffer size
		0,                                      //no stencil buffer
		0,                                      //no aux buffer
		PFD_MAIN_PLANE,                         //main drawing plane
		0,                                      //reserved
		0, 0, 0 };                              //layer masks ignored

												/*      Choose best matching format*/
	nPixelFormat = ChoosePixelFormat(_deviceContext, &pfd);

	/*      Set the pixel format to the device context*/
	SetPixelFormat(_deviceContext, nPixelFormat, &pfd);

	_renderContext = wglCreateContext(_deviceContext);

	if (wglMakeCurrent(_deviceContext, _renderContext) == FALSE) {
		return false;
	}

#endif
#ifdef __linux__

	// Linux init code goes here
#endif

	return true;
}

void OpenGLRenderer::beginRender()
{
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.5f, 0.125f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glFlush();
}

void OpenGLRenderer::endRender()
{
	SwapBuffers(_deviceContext);
}