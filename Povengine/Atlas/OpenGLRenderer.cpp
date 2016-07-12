#include "OpenGLRenderer.h"
#include <gl/GL.h>
#include <gl/GLU.h>

using namespace Atlas;

OpenGLRenderer::OpenGLRenderer() {
	_rendererType = AtlasRendererEnum::OpenGL;
}

OpenGLRenderer::~OpenGLRenderer()
{
	Destroy();
}

void OpenGLRenderer::Destroy()
{
	_initialised = false;

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
	_width = width;
	_height = height;

	_initialised = false;

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

	_initialised = true;
	return true;
}

void OpenGLRenderer::Resize(unsigned int width, unsigned int height)
{
	_width = width;
	_height = height;

#ifdef WIN32
	glViewport(0, 0, _width, _height);

	/*      Set current Matrix to projection*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //reset projection matrix

					  /*      Time to calculate aspect ratio of
					  our window.
					  */
	//gluPerspective(54.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW); //set modelview matrix
	glLoadIdentity(); //reset modelview matrix

#endif
#ifdef __linux__
#endif

}

void OpenGLRenderer::beginRender()
{
#ifdef WIN32

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.5f, 0.125f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glFlush();

#endif
#ifdef __linux__


#endif
}

void OpenGLRenderer::endRender()
{
#ifdef WIN32

	SwapBuffers(_deviceContext);

#endif
#ifdef __linux__


#endif
}