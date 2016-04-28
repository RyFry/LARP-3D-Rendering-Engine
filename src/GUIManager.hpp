#pragma once


#include "LarpPrerequisites.hpp"
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/CEGUI.h>

class GUIManager
{
	public:
		enum MenuNames
		{
			MAIN,
			OPTIONS
		};


		GUIManager();
		~GUIManager();

		// void set_GUI(string GUI_name);

	private:

		CEGUI::OpenGL3Renderer* _renderer;


};