#pragma once


#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/CEGUI.h>
#include <iostream>
#include <vector>

#include "LarpPrerequisites.hpp"

#include "Camera.hpp"
#include "ConfigurationLoader.hpp"
#include "Model.hpp"
#include "PhysicsMeshColliderBuilder.hpp"
#include "PhysicsPlayerController.hpp"
#include "PhysicsWorld.hpp"
#include "SceneGraph.hpp"
#include "Shader.hpp"


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
		GUIManager(Larp::SceneGraphPtr g);

		/**
     * Destructor
     */
		~GUIManager();

		// void set_GUI(string GUI_name);

		bool _GUI_rendering;

		bool get_rendering_state();

	  void show_main();

	private:

		Larp::SceneGraphPtr _graph;

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
		void setup_resources();

		/**
		* Setups up the main menu for use
		*/
		void setup_main_menu();

		void add_light(const CEGUI::EventArgs&);

		/**
		* Will handle adding lights to the scene 
		*/
		void add_point_light(const CEGUI::EventArgs&);

		void add_spot_light(const CEGUI::EventArgs&);

		void add_directional_light(const CEGUI::EventArgs&);

		void hide_GUI();

		void show_GUI();

};