#pragma once


#include "LarpPrerequisites.hpp"
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/CEGUI.h>
#include <iostream>
#include <vector>


class GUIManager
{
	public:
		enum MenuNames
		{
			MAIN,
			ADDLIGHT
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

		bool _GUI_rendering;

		bool _get_rendering_state();

	private:

		/**
		* CEGUI renderer that is required when using OpenGL3
		*/ 
		CEGUI::OpenGL3Renderer* _renderer;

		/*
		* WindowManager that will manage all the GUI windows
		*/
		CEGUI::WindowManager*   _wmgr;

    std::vector<CEGUI::Window*> _sheets;

		/**
		* Setups all the resource groups that CEGUI requires.
		*/
		void _setup_resources();

		/**
		* Setups up the main menu for use
		*/
		void _setup_main_menu();

		void _add_light(const CEGUI::EventArgs&);

		/**
		* Will handle adding lights to the scene 
		*/
		void _add_point_light(const CEGUI::EventArgs&);

		void _hide_GUI();
};