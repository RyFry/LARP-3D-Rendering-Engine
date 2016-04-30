#include "GUIManager.hpp"




GUIManager::GUIManager()
{
	this->_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();
	this->_wmgr =  &CEGUI::WindowManager::getSingleton();

	// this->_renderer->setupExtraStates();
	// this->_renderer->enableExtraStateSettings(true);

	this->_setup_resources();
	this->_setup_main_menu();
}

GUIManager::~GUIManager()
{

}

void GUIManager::_setup_resources()
{
	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
   (CEGUI::System::getSingleton().getResourceProvider());


  rp->setResourceGroupDirectory("schemes", "assets/schemes/");
	rp->setResourceGroupDirectory("imagesets", "assets/imagesets/");
	rp->setResourceGroupDirectory("fonts", "assets/fonts/");
	rp->setResourceGroupDirectory("layouts", "assets/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "assets/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts", "assets/lua_scripts/");

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

void GUIManager::_setup_main_menu()
{
	CEGUI::Window* mainSheet = this->_wmgr->createWindow("DefaultWindow", "CEGUIDemo/mainSheet");

	CEGUI::Window* addLight = this->_wmgr->createWindow("TaharezLook/Button", "Game/addLight");
	CEGUI::Window* lightMenu = this->_wmgr->createWindow("TaharezLook/Menubar", "lightMenu");

	CEGUI::Window* pointLight = this->_wmgr->createWindow("TaharezLook/MenuItem", "point");
	CEGUI::Window* spotLight = this->_wmgr->createWindow("TaharezLook/MenuItem", "spot");




	pointLight->setText("Point Light");
	spotLight->setText("Spotlight");

  lightMenu->setPosition(CEGUI::UVector2(CEGUI::UDim(0.4f,0),CEGUI::UDim(0.4f,0)));
  lightMenu->setSize(CEGUI::USize(CEGUI::UDim(0.15,0), CEGUI::UDim(0.05,0)));

  addLight->setText("Add Light...");
  addLight->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05f,0),CEGUI::UDim(0.2f,0)));
  addLight->setSize(CEGUI::USize(CEGUI::UDim(0.10,0), CEGUI::UDim(0.05,0)));

  pointLight->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::_add_point_light, this));
  addLight->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::_add_light, this));

  lightMenu->addChild(pointLight);
  lightMenu->addChild(spotLight);


  mainSheet->addChild(addLight);
  // popupMenu->addChild(start);

  this->_sheets.push_back(mainSheet);
  this->_sheets.push_back(lightMenu);

  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mainSheet);
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
}

bool GUIManager::_get_rendering_state()
{
	return this->_GUI_rendering;
}

void GUIManager::_add_light(const CEGUI::EventArgs&)
{
		this->_sheets.at(MAIN)->addChild(this->_sheets.at(ADDLIGHT));
}

void GUIManager::_add_point_light(const CEGUI::EventArgs&)
{

	// CEGUI::Window* = static_cast<CEGUI::WindowEventArgs *> CEGUI::EventArgs;
	this->_sheets.at(MAIN)->removeChild("lightMenu");

	this->_hide_GUI();

}

void GUIManager::_hide_GUI()
{
	this->_sheets.at(MAIN)->hide();
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
	this->_GUI_rendering = false;
}

