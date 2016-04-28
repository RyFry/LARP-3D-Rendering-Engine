#include "GUIManager.hpp"


void GUIManager::_setup_resources()
{
	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
   (CEGUI::System::getSingleton().getResourceProvider());


  /***
  ** NEED TO CHANGE THE RESOURCE PATH IN CASE OF DIFFERENT FOLDER NAME 
  ***/
  rp->setResourceGroupDirectory("schemes", "../cs354r-final-game-project/assets/schemes/");
	rp->setResourceGroupDirectory("imagesets", "../cs354r-final-game-project/assets/imagesets/");
	rp->setResourceGroupDirectory("fonts", "../cs354r-final-game-project/assets/fonts/");
	rp->setResourceGroupDirectory("layouts", "../cs354r-final-game-project/assets/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "../cs354r-final-game-project/assets/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts", "../cs354r-final-game-project/assets/lua_scripts/");

	/* Setups all the resources */
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
}


GUIManager::GUIManager()
{
	this->_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();
	this->_wmgr =  &CEGUI::WindowManager::getSingleton();

	this->_setup_resources();

	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
}