#include "GUIManager.hpp"




GUIManager::GUIManager(Larp::SceneGraphPtr g, GLFWwindow* window):
_graph(g), _window(window)
{
	this->_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();
	this->_wmgr =  &CEGUI::WindowManager::getSingleton();
	// this->_renderer->setupExtraStates();
	// this->_renderer->enableExtraStateSettings(true);

	this->setup_resources();
	this->setup_menus();
}

GUIManager::~GUIManager()
{

}

void GUIManager::setup_resources()
{
	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
   (CEGUI::System::getSingleton().getResourceProvider());


  rp->setResourceGroupDirectory("schemes", "assets/CEGUI/schemes/");
	rp->setResourceGroupDirectory("imagesets", "assets/CEGUI/imagesets/");
	rp->setResourceGroupDirectory("fonts", "assets/CEGUI/fonts/");
	rp->setResourceGroupDirectory("layouts", "assets/CEGUI/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "assets/CEGUI/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts", "assets/CEGUI/lua_scripts/");

	/* Setups all the resources */
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

	/* Using the TahrezLook since it is prebuilt. May change for custom gui */
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	CEGUI::FontManager::getSingleton().createFromFile( "DejaVuSans-10.font" );


}

void GUIManager::setup_menus()
{
	/* Main menu sheet */
	CEGUI::Window* mainSheet = this->_wmgr->createWindow("DefaultWindow", "mainSheet");

	/* The Add light button and the menu bar that holds all the add light buttons */
	CEGUI::Window* addLight = this->_wmgr->createWindow("TaharezLook/Button", "addLight");
	CEGUI::Window* lightMenu = this->_wmgr->createWindow("TaharezLook/Menubar", "lightMenu");

	/* All the add light buttons */
	CEGUI::Window* pointLight = this->_wmgr->createWindow("TaharezLook/MenuItem", "point");
	CEGUI::Window* spotLight = this->_wmgr->createWindow("TaharezLook/MenuItem", "spot");
	CEGUI::Window* directionalLight = this->_wmgr->createWindow("TaharezLook/MenuItem", "directional");

	/* This is the quit button*/
	CEGUI::Window* quit = this->_wmgr->createWindow("TaharezLook/Button", "quit");

	CEGUI::MultiColumnList* test = static_cast<CEGUI::MultiColumnList *>(this->_wmgr->createWindow("TaharezLook/MultiColumnList", "list"));


	// CEGUI::ListboxTextItem* testItem = new CEGUI::ListboxTextItem("My dickkkk", 25);
	// // testItem->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");


	// test->setPosition(CEGUI::UVector2(CEGUI::UDim(0.4f,0),CEGUI::UDim(0.4f,0)));
	// test->setSize(CEGUI::USize(CEGUI::UDim(0.25,0), CEGUI::UDim(0.15,0)));
	// test->setSelectionMode(CEGUI::MultiColumnList::SelectionMode::RowMultiple);
	// test->addColumn("Column1", 0, CEGUI::UDim(0.15,0));
	// test->addRow(testItem, 0, 0);

	CEGUI::MultiLineEditbox* test2 = static_cast<CEGUI::MultiLineEditbox*>(this->_wmgr->createWindow("TaharezLook/MultiLineEditbox", "test2"));
	test2->setText("Something sometihnf dick");
	test2->setReadOnly(false);
	test2->setWordWrapping(true);

	pointLight->setText("Point Light");
	spotLight->setText("Spotlight");
	directionalLight->setText("Directional Light");


  lightMenu->setPosition(CEGUI::UVector2(CEGUI::UDim(0.4f,0),CEGUI::UDim(0.4f,0)));
  lightMenu->setSize(CEGUI::USize(CEGUI::UDim(0.25,0), CEGUI::UDim(0.05,0)));

  addLight->setText("Add Light...");
  addLight->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05f,0),CEGUI::UDim(0.2f,0)));
  addLight->setSize(CEGUI::USize(CEGUI::UDim(0.10,0), CEGUI::UDim(0.05,0)));


  quit->setText("Quit");
  quit->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05f,0),CEGUI::UDim(0.6f,0)));
  quit->setSize(CEGUI::USize(CEGUI::UDim(0.10,0), CEGUI::UDim(0.05,0)));

  addLight->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::add_light, this));
  pointLight->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::add_point_light, this));
  spotLight->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::add_spot_light, this));
  directionalLight->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::add_directional_light, this));

  quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::quit, this));

  lightMenu->addChild(pointLight);
  lightMenu->addChild(spotLight);
  lightMenu->addChild(directionalLight);



  mainSheet->addChild(addLight);
  mainSheet->addChild(quit);
  mainSheet->addChild(test2);

  this->_sheets.push_back(mainSheet);
  this->_sheets.push_back(lightMenu);

  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mainSheet);
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
}

bool GUIManager::get_rendering_state()
{
	return this->_GUI_rendering;
}

void GUIManager::add_light(const CEGUI::EventArgs&)
{
		this->_sheets.at(MAIN)->addChild(this->_sheets.at(ADDLIGHT));
}

void GUIManager::add_point_light(const CEGUI::EventArgs&)
{

	this->_sheets.at(MAIN)->removeChild("lightMenu");
	this->hide_GUI();
	Larp::PointLightPtr point_light = this->_graph->create_point_light();

	point_light->set_ambient_intensity(0.0f, 1.0f, 0.0f);
  point_light->set_position(0.0f, 2.0f, 0.0f);

}

void GUIManager::add_spot_light(const CEGUI::EventArgs&)
{

	this->_sheets.at(MAIN)->removeChild("lightMenu");
	this->hide_GUI();

	Larp::SpotLightPtr spot_light = this->_graph->create_spot_light();

	spot_light->set_ambient_intensity(0.0f, 1.0f, 0.0f);
 	spot_light->set_position(0.0f, 2.0f, 0.0f);

}

void GUIManager::add_directional_light(const CEGUI::EventArgs&)
{

	this->_sheets.at(MAIN)->removeChild("lightMenu");
	this->hide_GUI();

	Larp::DirectionalLightPtr directional_light = this->_graph->create_directional_light();

	// directional_light->set_ambient_intensity(0.0f, 1.0f, 0.0f);
 // 	directional_light->set_position(0.0f, 2.0f, 0.0f);

}

void GUIManager::quit(const CEGUI::EventArgs&)
{
	glfwSetWindowShouldClose(this->_window, GL_TRUE);
}

void GUIManager::hide_GUI()
{
	this->_sheets.at(MAIN)->hide();
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
	this->_GUI_rendering = false;
}

void GUIManager::show_GUI()
{
		this->_sheets.at(MAIN)->show();
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
		this->_GUI_rendering = true;
}

void GUIManager::show_main()
{
	if(_GUI_rendering)
		this->hide_GUI();
	else
		this->show_GUI();

}