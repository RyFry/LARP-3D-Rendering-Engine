#pragma once


#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/CEGUI.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
		GUIManager(Larp::SceneGraphPtr g, GLFWwindow* window);

		/**
     * Destructor
     */
		~GUIManager();

		// void set_GUI(string GUI_name);

		/**
		* Tells the user if the GUI is currently rendering out
		*/
		bool _GUI_rendering;

		/**
		* Returns the GUI's current rendering state 
		*/
		bool get_rendering_state();

		/** 
		* Shows the main menu used for adding different elements to the scene
		*/
	  void show_main();

	private:

		Larp::SceneGraphPtr _graph;

		GLFWwindow* _window;

		/**
		* CEGUI renderer that is required when using OpenGL3
		*/ 
		CEGUI::OpenGL3Renderer* _renderer;

		/*
		* WindowManager that will manage all the GUI windows
		*/
		CEGUI::WindowManager*   _wmgr;

    std::vector<CEGUI::Window*> _sheets;

    std::vector<CEGUI::Window*> _light_list;

    std::map<std::string, Larp::PointLightPtr> _pointMap;

		/**
		* Setups all the resource groups that CEGUI requires.
		*/
		void setup_resources();

		/**
		* Setups up all the menus for use
		*/
		void setup_menus();

		void add_light(const CEGUI::EventArgs&);

		/**
		* Adds a point light to the scene 
		*/
		void add_point_light(const CEGUI::EventArgs&);

		void add_spot_light(const CEGUI::EventArgs&);

		void add_directional_light(const CEGUI::EventArgs&);

		void quit(const CEGUI::EventArgs&);

		void push_test(const CEGUI::EventArgs&);

		/**
		* Hides the current GUI sheet and mouse
		*/ 
		void hide_GUI();

		/**
		* Shows the current GUI sheet and mouse
		*/ 
		void show_GUI();

};