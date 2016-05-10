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


	CEGUI::Window* lightList = this->_wmgr->createWindow("TaharezLook/ScrollablePane", "lightList");






	CEGUI::Window* pushTest1 = this->_wmgr->createWindow("TaharezLook/Button", "txt");
	CEGUI::Window* pushTest2 = this->_wmgr->createWindow("TaharezLook/Button", "txt2");

	/* Light edit is the menu used for modifing properties of the lights */
	CEGUI::Window* lightEdit = this->_wmgr->createWindow("TaharezLook/ScrollablePane", "lightEdit");

	CEGUI::Window* name = this->_wmgr->createWindow("TaharezLook/Label", "name");

	name->setSize(CEGUI::USize(CEGUI::UDim(0.2,0), CEGUI::UDim(0.1,0)));
	name->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(0.0f,0)));



	/* Is a child of Light Edit (It will be used to switch between ambient, specular, and diffuse intensity sliders) */
	CEGUI::Window* ambientIntensity = this->_wmgr->createWindow("TaharezLook/ScrollablePane", "ambientIntensity");

	/* Ambient RGB for the light */
	CEGUI::Spinner* redSpinnerAmbient   = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "redAmb"));
	CEGUI::Spinner* greenSpinnerAmbient = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "greenAmb"));
	CEGUI::Spinner* blueSpinnerAmbient  = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "blueAmb"));

	ambientIntensity->setSize(CEGUI::USize(CEGUI::UDim(0.75f,0), CEGUI::UDim(0.1f,0)));
	ambientIntensity->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1f,0),CEGUI::UDim(0.1f,0)));



	redSpinnerAmbient->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	redSpinnerAmbient->setMinimumValue(0.0f);
	redSpinnerAmbient->setMaximumValue(255.0f);
	redSpinnerAmbient->setStepSize(10.0f);
	redSpinnerAmbient->setCurrentValue(10.0f);
	redSpinnerAmbient->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(0.0f,0)));

	greenSpinnerAmbient->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	greenSpinnerAmbient->setMinimumValue(0.0f);
	greenSpinnerAmbient->setMaximumValue(255.0f);
	greenSpinnerAmbient->setStepSize(10.0f);
	greenSpinnerAmbient->setCurrentValue(10.0f);
	greenSpinnerAmbient->setPosition(CEGUI::UVector2(CEGUI::UDim(0.15f,0),CEGUI::UDim(0.0f,0)));

	blueSpinnerAmbient->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	blueSpinnerAmbient->setMinimumValue(0.0f);
	blueSpinnerAmbient->setMaximumValue(255.0f);
	blueSpinnerAmbient->setStepSize(10.0f);
	blueSpinnerAmbient->setCurrentValue(10.0f);
	blueSpinnerAmbient->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30f,0),CEGUI::UDim(0.0f,0)));


	ambientIntensity->addChild(redSpinnerAmbient);
	ambientIntensity->addChild(greenSpinnerAmbient);
	ambientIntensity->addChild(blueSpinnerAmbient);




	/* Is a child of Light Edit (It will be used to switch between ambient, specular, and diffuse intensity sliders) */
	CEGUI::Window* diffuseIntensity = this->_wmgr->createWindow("TaharezLook/ScrollablePane", "diffusetIntensity");

	diffuseIntensity->setSize(CEGUI::USize(CEGUI::UDim(0.75f,0), CEGUI::UDim(0.1f,0)));
	diffuseIntensity->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1f,0),CEGUI::UDim(0.1f,0)));


	/* Ambient RGB for the light */
	CEGUI::Spinner* redSpinnerDiffuse   = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "redDif"));
	CEGUI::Spinner* greenSpinnerDiffuse = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "greenDif"));
	CEGUI::Spinner* blueSpinnerDiffuse  = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "blueDif"));

	redSpinnerDiffuse->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	redSpinnerDiffuse->setMinimumValue(0.0f);
	redSpinnerDiffuse->setMaximumValue(255.0f);
	redSpinnerDiffuse->setStepSize(10.0f);
	redSpinnerDiffuse->setCurrentValue(10.0f);
	redSpinnerDiffuse->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(0.0f,0)));

	greenSpinnerDiffuse->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	greenSpinnerDiffuse->setMinimumValue(0.0f);
	greenSpinnerDiffuse->setMaximumValue(255.0f);
	greenSpinnerDiffuse->setStepSize(10.0f);
	greenSpinnerDiffuse->setCurrentValue(10.0f);
	greenSpinnerDiffuse->setPosition(CEGUI::UVector2(CEGUI::UDim(0.15f,0),CEGUI::UDim(0.0f,0)));

	blueSpinnerDiffuse->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	blueSpinnerDiffuse->setMinimumValue(0.0f);
	blueSpinnerDiffuse->setMaximumValue(255.0f);
	blueSpinnerDiffuse->setStepSize(10.0f);
	blueSpinnerDiffuse->setCurrentValue(10.0f);
	blueSpinnerDiffuse->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30f,0),CEGUI::UDim(0.0f,0)));


	diffuseIntensity->addChild(redSpinnerDiffuse);
	diffuseIntensity->addChild(greenSpinnerDiffuse);
	diffuseIntensity->addChild(blueSpinnerDiffuse);


	/* Is a child of Light Edit (It will be used to switch between ambient, specular, and diffuse intensity sliders) */
	CEGUI::Window* specularIntensity = this->_wmgr->createWindow("TaharezLook/ScrollablePane", "specularIntensity");

	specularIntensity->setSize(CEGUI::USize(CEGUI::UDim(0.75f,0), CEGUI::UDim(0.1f,0)));
	specularIntensity->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1f,0),CEGUI::UDim(0.1f,0)));


	/* Ambient RGB for the light */
	CEGUI::Spinner* redSpinnerSpecular   = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "redSpec"));
	CEGUI::Spinner* greenSpinnerSpecular = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "greenSpec"));
	CEGUI::Spinner* blueSpinnerSpecular  = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "blueSpec"));

	redSpinnerSpecular->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	redSpinnerSpecular->setMinimumValue(0.0f);
	redSpinnerSpecular->setMaximumValue(255.0f);
	redSpinnerSpecular->setStepSize(10.0f);
	redSpinnerSpecular->setCurrentValue(10.0f);
	redSpinnerSpecular->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(0.0f,0)));

	greenSpinnerSpecular->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	greenSpinnerSpecular->setMinimumValue(0.0f);
	greenSpinnerSpecular->setMaximumValue(255.0f);
	greenSpinnerSpecular->setStepSize(10.0f);
	greenSpinnerSpecular->setCurrentValue(10.0f);
	greenSpinnerSpecular->setPosition(CEGUI::UVector2(CEGUI::UDim(0.15f,0),CEGUI::UDim(0.0f,0)));

	blueSpinnerSpecular->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	blueSpinnerSpecular->setMinimumValue(0.0f);
	blueSpinnerSpecular->setMaximumValue(255.0f);
	blueSpinnerSpecular->setStepSize(10.0f);
	blueSpinnerSpecular->setCurrentValue(10.0f);
	blueSpinnerSpecular->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30f,0),CEGUI::UDim(0.0f,0)));


	specularIntensity->addChild(redSpinnerSpecular);
	specularIntensity->addChild(greenSpinnerSpecular);
	specularIntensity->addChild(blueSpinnerSpecular);


	/*Position spinners */
	CEGUI::Window* positionSheet = this->_wmgr->createWindow("TaharezLook/ScrollablePane", "positionSheet");

	positionSheet->setSize(CEGUI::USize(CEGUI::UDim(0.75f,0), CEGUI::UDim(0.1f,0)));
	positionSheet->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1f,0),CEGUI::UDim(0.1f,0)));


	/* Ambient RGB for the light */
	CEGUI::Spinner* xPos   = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "xPos"));
	CEGUI::Spinner* yPos = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "yPos"));
	CEGUI::Spinner* zPos  = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "zPos"));

	xPos->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	xPos->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(0.0f,0)));

	yPos->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	yPos->setPosition(CEGUI::UVector2(CEGUI::UDim(0.15f,0),CEGUI::UDim(0.0f,0)));

	zPos->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	zPos->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30f,0),CEGUI::UDim(0.0f,0)));


	positionSheet->addChild(xPos);
	positionSheet->addChild(yPos);
	positionSheet->addChild(zPos);



	/* Setup the buttons that will be used to change between ambient, diffuse, and specular intensity spinners */
	CEGUI::Window* ambSwitch = this->_wmgr->createWindow("TaharezLook/Button", "ambSwitch");
	CEGUI::Window* difSwitch = this->_wmgr->createWindow("TaharezLook/Button", "difSwitch");
	CEGUI::Window* specSwitch = this->_wmgr->createWindow("TaharezLook/Button", "specSwitch");
	CEGUI::Window* positionSwitch = this->_wmgr->createWindow("TaharezLook/Button", "posSwitch");


	ambSwitch->setText("Ambient");
	ambSwitch->setSize(CEGUI::USize(CEGUI::UDim(0.1,0), CEGUI::UDim(0.05,0)));
	ambSwitch->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1f,0),CEGUI::UDim(0.3f,0)));

	difSwitch->setText("Diffuse");
	difSwitch->setSize(CEGUI::USize(CEGUI::UDim(0.1,0), CEGUI::UDim(0.05,0)));
	difSwitch->setPosition(CEGUI::UVector2(CEGUI::UDim(0.21f,0),CEGUI::UDim(0.3f,0)));

	specSwitch->setText("Specular");
	specSwitch->setSize(CEGUI::USize(CEGUI::UDim(0.1,0), CEGUI::UDim(0.05,0)));
	specSwitch->setPosition(CEGUI::UVector2(CEGUI::UDim(0.32f,0),CEGUI::UDim(0.3f,0)));

	positionSwitch->setText("Position");
	positionSwitch->setSize(CEGUI::USize(CEGUI::UDim(0.1,0), CEGUI::UDim(0.05,0)));
	positionSwitch->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1f,0),CEGUI::UDim(0.4f,0)));





	
	/* This are the sheets for the spinners for different intensities */
	lightEdit->addChild(ambientIntensity);
	lightEdit->addChild(diffuseIntensity);
	lightEdit->addChild(specularIntensity);
	lightEdit->addChild(positionSheet);


	lightEdit->addChild(ambSwitch);
	lightEdit->addChild(difSwitch);
	lightEdit->addChild(specSwitch);
	lightEdit->addChild(positionSwitch);
	lightEdit->addChild(name);


	this->_light_edit.push_back(name);

	this->_light_edit.push_back(redSpinnerAmbient);
	this->_light_edit.push_back(greenSpinnerAmbient);
	this->_light_edit.push_back(blueSpinnerAmbient);

	this->_light_edit.push_back(redSpinnerDiffuse);
	this->_light_edit.push_back(greenSpinnerDiffuse);
	this->_light_edit.push_back(blueSpinnerDiffuse);

	this->_light_edit.push_back(redSpinnerSpecular);
	this->_light_edit.push_back(greenSpinnerSpecular);
	this->_light_edit.push_back(blueSpinnerSpecular);




	/* These three will always be last */
	this->_light_edit.push_back(ambSwitch);
	this->_light_edit.push_back(difSwitch);
	this->_light_edit.push_back(specSwitch);
	this->_light_edit.push_back(positionSwitch);


	lightEdit->setSize(CEGUI::USize(CEGUI::UDim(0.75,0), CEGUI::UDim(0.45,0)));
	lightEdit->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5,0),CEGUI::UDim(0.3f,0)));

	lightList->setSize(CEGUI::USize(CEGUI::UDim(0.75,0), CEGUI::UDim(0.45,0)));
	lightList->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35f,0),CEGUI::UDim(0.4f,0)));

	pushTest1->setText("Hi thar");
	pushTest1->setSize(CEGUI::USize(CEGUI::UDim(0.1,0), CEGUI::UDim(0.05,0)));
	pushTest2->setText("Das Kampfer");
	pushTest2->setSize(CEGUI::USize(CEGUI::UDim(0.1,0), CEGUI::UDim(0.05,0)));
	pushTest2->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(0.05f,0)));

	lightList->addChild(pushTest1);
	lightList->addChild(pushTest2);




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
  pushTest1->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::push_test, this));
  pushTest2->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::push_test, this));

  ambSwitch->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::spinner_switch, this));
  difSwitch->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::spinner_switch, this));
  specSwitch->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::spinner_switch, this));
  positionSwitch->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::spinner_switch, this));

  
  quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::quit, this));

  lightMenu->addChild(pointLight);
  lightMenu->addChild(spotLight);
  lightMenu->addChild(directionalLight);

  this->populate_light_list(lightList);

  mainSheet->addChild(addLight);
  mainSheet->addChild(quit);
  mainSheet->addChild(lightList);

  this->_sheets.push_back(mainSheet);
  this->_sheets.push_back(lightMenu);
  this->_sheets.push_back(lightList);
  this->_sheets.push_back(lightEdit);
  this->_sheets.push_back(ambientIntensity);
  this->_sheets.push_back(diffuseIntensity);	
  this->_sheets.push_back(specularIntensity);
  this->_sheets.push_back(positionSheet);

  this->_light_list.push_back(pushTest1);
  this->_light_list.push_back(pushTest2);


  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mainSheet);
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
}

void GUIManager::populate_light_list(CEGUI::Window* lightList)
{
	// /* Create buttons for each directional light */
	// CEGUI::Window* temp;
	// std::string tempName;
	// for(uint n = 0; n < LightFactory::_directional_lights.size(); ++n)
	// {
	// 	tempName = "directionalLight" + n;

	// 	/*setups the window button */
	// 	temp = this->_wmgr->createWindow("TaharezLook/Button", tempName);
	// 	temp->setText(tempName);
	// 	temp->setSize(CEGUI::USize(CEGUI::UDim(0.1,0), CEGUI::UDim(0.05,0)));
	// 	temp->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(this->yPos,0)));
	// 	temp->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::push_test, this));

	// 	/*Adds the button to the light list and maps the name of the light to the directional light */
	// 	lightList->addChild(temp);
	// 	this->_light_list.push_back(temp);
	// 	this->_direct_map.emplace(tempName, LightFactor::_directional_lights.at(n));
	// 	this->yPos += 0.05;
	// }

	// /* Create buttons for each point lights */
	// for(n = 0; n < LightFactory::_point_lights.size(); ++n)
	// {
	// 	tempName = "pointLight" + n;

	// 	/*setups the window button */
	// 	temp = this->_wmgr->createWindow("TaharezLook/Button", tempName);
	// 	temp->setText(tempName);
	// 	temp->setSize(CEGUI::USize(CEGUI::UDim(0.1,0), CEGUI::UDim(0.05,0)));
	// 	temp->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(this->yPos,0)));
	// 	temp->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::push_test, this));

	// 	/*Adds the button to the light list and maps the name of the light to the directional light */
	// 	lightList->addChild(temp);
	// 	this->_light_list.push_back(temp);
	// 	this->_point_map.emplace(tempName, LightFactor::_point_lights.at(n));
	// 	this->yPos += 0.05;
	// }
	// /*Create buttons for each spot light */
	// for(n = 0; n < LightFactory::_spot_lights.size(); ++n)
	// {
	// 	tempName = "spotLight" + n;

	// 	/*setups the window button */
	// 	temp = this->_wmgr->createWindow("TaharezLook/Button", tempName);
	// 	temp->setText(tempName);
	// 	temp->setSize(CEGUI::USize(CEGUI::UDim(0.1,0), CEGUI::UDim(0.05,0)));
	// 	temp->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(this->yPos,0)));
	// 	temp->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::push_test, this));

	// 	/*Adds the button to the light list and maps the name of the light to the directional light */
	// 	lightList->addChild(temp);
	// 	this->_light_list.push_back(temp);
	// 	this->_point_map.emplace(tempName, LightFactor::_spot_lights.at(n));
	// 	this->yPos += 0.05;
	// }
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


void GUIManager::spinner_switch(const CEGUI::EventArgs&)
{
	/*Ambient Int */
 	if(this->_light_edit.at(this->_light_edit.size()-4)->isCapturedByThis())
 	{

 		this->_sheets.at(AMBINT)->show();
 		this->_sheets.at(DIFINT)->hide();
 		this->_sheets.at(SPECINT)->hide();
 		this->_sheets.at(POSINT)->hide();

 	}
 	/*Diffuse Int */
 	else if(this->_light_edit.at(this->_light_edit.size()-3)->isCapturedByThis())
 	{
 		this->_sheets.at(AMBINT)->hide();
 		this->_sheets.at(DIFINT)->show();
 		this->_sheets.at(SPECINT)->hide();
 		this->_sheets.at(POSINT)->hide();
 	}
 	/* Specular Int */
 	else if(this->_light_edit.at(this->_light_edit.size()-2)->isCapturedByThis())
 	{
 		this->_sheets.at(AMBINT)->hide();
 		this->_sheets.at(DIFINT)->hide();
 		this->_sheets.at(SPECINT)->show();
 		this->_sheets.at(POSINT)->hide();
 	}
 	/* Position */
 	 else if(this->_light_edit.at(this->_light_edit.size()-1)->isCapturedByThis())
 	{
 		this->_sheets.at(AMBINT)->hide();
 		this->_sheets.at(DIFINT)->hide();
 		this->_sheets.at(SPECINT)->hide();
 		this->_sheets.at(POSINT)->show();

 	}
}
	
void GUIManager::push_test(const CEGUI::EventArgs&)
{
	for(uint i = 0; i < this->_light_list.size(); ++i)
	{
		if(this->_light_list.at(i)->isCapturedByThis())
		{
			this->_sheets.at(MAIN)->addChild(this->_sheets.at(LIGHTEDIT));
			this->_sheets.at(DIFINT)->hide();
			this->_sheets.at(SPECINT)->hide();

			/* 0 will always be the index for the name of the light */
			this->_light_edit.at(0)->setText(this->_light_list.at(i)->getText());
		}
	}
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