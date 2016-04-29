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
	CEGUI::Window* mainSheet = _wmgr->createWindow("DefaultWindow", "CEGUIDemo/mainSheet");


	CEGUI::Window* start = _wmgr->createWindow("TaharezLook/Button", "Game/mainTitle");


	start->setText("Start");
	start->setSize(CEGUI::USize(CEGUI::UDim(0.15,0), CEGUI::UDim(0.05,0)));
  start->setPosition(CEGUI::UVector2(CEGUI::UDim(0.4f,0),CEGUI::UDim(0.4f,0)));

  start->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::_start, this));

  mainSheet->addChild(start);

  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mainSheet);
   CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
}

void GUIManager::_start(const CEGUI::EventArgs&)
{
	std::cout << "I'm working!" << std::endl;
}