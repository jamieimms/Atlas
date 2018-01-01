#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace Atlas
{
	enum AtlasRendererEnum
	{
		Unknown,
		DirectX,
		OpenGL
	};


	class AtlasRenderer
	{
	public:
		AtlasRenderer();
		virtual ~AtlasRenderer();

		virtual bool Initialise(unsigned int width, unsigned int height, void* context) = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;

		glm::mat4 GetProjection() { return _proj; }
		glm::mat4 Get2DProjection() { return _2DProj; }

		virtual void beginRender() = 0;
		virtual void endRender() = 0;
	
		// Getters
		bool IsInitialised() { return _initialised; }
		AtlasRendererEnum GetType() { return _rendererType; }

		void ToggleWireframe(bool newValue) { _wireframe = newValue; }

	protected:

		virtual void Destroy() = 0;

		unsigned int _width;
		unsigned int _height;

		AtlasRendererEnum _rendererType;

		bool _wireframe;

		bool _initialised;

		glm::mat4 _proj;
		glm::mat4 _2DProj;

	};
}