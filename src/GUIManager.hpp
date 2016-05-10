#pragma once


#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/CEGUI.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>


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
		/* These enums act as indexs into _sheets vector */
		enum MenuNames
		{
			MAIN,
			ADDLIGHT,
			LIGHTLIST,
			LIGHTEDIT,
			AMBINT,
			DIFINT,
			SPECINT,
			POSINT,
			DIRINT
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

		GLFWwindow* _off_screen;

		/**
		* CEGUI renderer that is required when using OpenGL3
		*/ 
		CEGUI::OpenGL3Renderer* _renderer;

		/*
		* WindowManager that will manage all the GUI windows
		*/
		CEGUI::WindowManager*   _wmgr;

		/*
		* Vector that holds all the GUI sheets
			*/
	    std::vector<CEGUI::Window*> _sheets;

	    /* 
	    * Vector that will contain all the windows that represent lights in the light menu
	    */
	    std::vector<CEGUI::Window*> _light_list;

	    std::vector<CEGUI::Window*> _light_edit;

	    /* 
	    * CEGUI window times will be tied to a Pointlightptr
	    */
	    std::map<std::string, Larp::PointLightPtr> _point_map;

	    std::map<std::string, Larp::SpotLightPtr> _spot_map;

	    std::map<std::string, Larp::DirectionalLightPtr> _direct_map;

  		float _yPos = 0.0f;

		/*
		* Setups all the resource groups that CEGUI requires.
		*/
		void setup_resources();

		/**
		* Setups up all the menus for use
		*/
		void setup_menus();

		void populate_light_list(CEGUI::Window* lightList);

		void add_light(const CEGUI::EventArgs&);

		/**
		* Adds a point light to the scene 
		*/
		void add_point_light(const CEGUI::EventArgs&);

		void add_spot_light(const CEGUI::EventArgs&);

		void add_directional_light(const CEGUI::EventArgs&);

		/**
		* Closes the window
		*/
		void quit(const CEGUI::EventArgs&);

		void push_test(const CEGUI::EventArgs&);

		void spinner_switch(const CEGUI::EventArgs&);


		/*This will popluate the spinners for the current editing light */
		void populate_spinners(const char* name);

		/**
		* Hides the current GUI sheet and mouse
		*/ 
		void hide_GUI();

		/**
		* Shows the current GUI sheet and mouse
		*/ 
		void show_GUI();

};