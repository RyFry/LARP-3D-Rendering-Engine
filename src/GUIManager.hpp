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

	  /**
     * Constructor
     */
		GUIManager();

		/**
     * Destructor
     */
		~GUIManager();

		// void set_GUI(string GUI_name);

	private:

		/**
		* CEGUI renderer that is required when using OpenGL3
		*/ 
		CEGUI::OpenGL3Renderer* _renderer;

		/*
		* WindowManager that will manage all the GUI windows
		*/
		CEGUI::WindowManager*   _wmgr;

		/**
		* Setups all the resource groups that CEGUI requires.
		*/
		void _setup_resources();
};