#pragma once

#include "../AtlasUtil/AtlasLog.h"
#include "AtlasRenderer.h"
#include "ShaderManager.h"
#include "Input.h"
#include "Audio.h"
#include "Physics.h"
#include "TextureManager.h"
#include "Fonts.h"
#include "Geometry.h"

namespace Atlas
{
	class Subsystems
	{
	public:
		Subsystems()
			: _renderer(nullptr), _shaderManager(nullptr), _input(nullptr), _audio(nullptr), _phys(nullptr), _texManager(nullptr), _fonts(nullptr), _log(nullptr)
		{}

		AtlasUtil::AtlasLog* _log;

		AtlasRenderer* _renderer;	// The renderer, could be DirectX (win32 only) or OpenGL (win32 and linux), currently we only support OpenGL
		ShaderManager* _shaderManager; // The shader loader
		Input* _input;	// Handles user input
		Audio* _audio;	// Handles audio functions
		Physics* _phys;	// Handles physics calculations
		TextureManager* _texManager; // Handles textures
		Fonts* _fonts; // Handles fonts
		Geometry* _geometry;
	};
}