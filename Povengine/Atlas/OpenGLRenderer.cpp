#ifdef _WIN32
#include <Windows.h>
#endif
#include "OpenGLRenderer.h"
#define GLEW_STATIC
#include "glew.h"
#include <gl/GL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace Atlas;

OpenGLRenderer::OpenGLRenderer() {
	_rendererType = AtlasRendererEnum::OpenGL;
	_wireframe = false;
}

OpenGLRenderer::~OpenGLRenderer()
{
	Destroy();
}

void OpenGLRenderer::Destroy()
{
	_initialised = false;

#ifdef _WIN32

	wglMakeCurrent((HDC)_deviceContext, NULL);
	wglDeleteContext(_renderContext);

#endif
#ifdef __linux__

	// Linux deinit code goes here

#endif
}

bool OpenGLRenderer::Initialise(unsigned int width, unsigned int height, void* context)
{
	_width = width;
	_height = height;

	_initialised = false;

#ifdef _WIN32

	_deviceContext = context;
	_renderContext = wglCreateContext((HDC)_deviceContext);

	if (wglMakeCurrent((HDC)_deviceContext, _renderContext) == FALSE) {
		return false;
	}

#endif
#ifdef __linux__

	// Linux init code goes here
#endif

	auto result = glewInit();

	_useVer45 = glewIsSupported("GL_VERSION_4_5");

	glViewport(0, 0, width, height);
	_proj = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);

	_initialised = true;
	return true;
}


void OpenGLRenderer::Resize(unsigned int width, unsigned int height)
{
	_width = width;
	_height = height;

#ifdef _WIN32
	glViewport(0, 0, _width, _height);

	_proj = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);

#endif
#ifdef __linux__
#endif

}


void OpenGLRenderer::beginRender()
{
#ifdef _WIN32

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glFlush();

	glPolygonMode(GL_FRONT_AND_BACK, _wireframe ? GL_LINE : GL_FILL);

#endif
#ifdef __linux__


#endif
}

void OpenGLRenderer::endRender()
{
#ifdef _WIN32

	SwapBuffers((HDC)_deviceContext);

#endif
#ifdef __linux__


#endif
}