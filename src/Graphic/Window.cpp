#include "Window.h"

Window::Window(void){
	root = NULL;
	win = NULL;
	sceneManager = NULL;
	cRenderer = NULL;
	cam = NULL;
	view = NULL;
}

void Window::start(void){
	root = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");

	// gestion des parametres de l'affichage de la fenetre
	std::vector<std::string> res = load("ogre.cfg");
	Ogre::RenderSystem *rs = root->getRenderSystemByName(res[0]);
	root->setRenderSystem(rs);
	for(size_t i = 1; i < res.size(); ++i){
		std::string *s = separate(res[i]);
		rs->setConfigOption(s[0], s[1]);
	}

	Ogre::ConfigFile configFile;
	configFile.load("resources.cfg");
	Ogre::ConfigFile::SectionIterator seci = configFile.getSectionIterator();
	Ogre::String secName, typeName, archName;
	std::cout << "===========================>TEST<============================" << std::endl;
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	while (seci.hasMoreElements()){
	    secName = seci.peekNextKey();
	    Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
	    Ogre::ConfigFile::SettingsMultiMap::iterator i;
	    for (i = settings->begin(); i != settings->end(); ++i)
	    {
	        typeName = i->first;
	        archName = i->second;
	        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
	            archName, typeName, secName);
	        std::cout << archName << "  !!  " << typeName <<  "  !!  " << secName <<std::endl;
	    }
	}
	win = root->initialise(true, "Crossed Times");
	gui();


	//Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();





	sceneManager = root->createSceneManager("DefaultSceneManager", "Mon Scene Manager");
	sceneManager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

	cam = sceneManager->createCamera("Camera");
	cam->setPosition(Ogre::Vector3(0,0,100));
	cam->lookAt(Ogre::Vector3(0,0,0));
	cam->setNearClipDistance(1);

	view = win->addViewport(cam);
	view->setBackgroundColour(Ogre::ColourValue(0,0,0));
	cam->setAspectRatio(Ogre::Real(view->getActualWidth()) / Ogre::Real(view->getActualHeight()));
}

std::vector<std::string> Window::load(const char *file){
	std::ifstream f(file, std::ios::in);
	std::vector<std::string> str;
	if(!file){
		std::cout << "File " << file << " not loaded" << std::endl;
		return str;
	}

	std::string s;
	while(std::getline(f, s)){
		str.push_back(s);
	}
	f.close();

	return str;
}

std::string* Window::separate(std::string el){
	std::string *str = new std::string[2];
	str[0] = "";
	str[1] = "";
	size_t i = 0;
	bool cont = true;
	while(el.c_str()[i] != '=' && cont){
		str[0] += el.c_str()[i];
		++i;
	}
	for(++i; i < el.size(); ++i){
		str[1] += el.c_str()[i];
	}

	return str;
}


void Window::run(void){
 	root->startRendering();
}

void Window::gui(void){
	try{
		cRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
		for(size_t i = 0; i < Ogre::ResourceGroupManager::getSingleton().getResourceGroups().size(); ++i)
			std::cout << "[GUI]" << Ogre::ResourceGroupManager::getSingleton().getResourceGroups()[i] << std::endl;

		CEGUI::System::getSingleton().
		CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
	}catch(CEGUI::Exception &e){
		fprintf(stderr, "[Gui] An exception has occurred: %s\n",
		            e.getMessage().c_str());
	}
	std::cout << "[GUI] Done" << std::endl;
	//CEGUI::SchemeManager::getSingleton().create("OgreTray.scheme");


	//Ogre::TextureManager::getSingleton().setDefaultNumMipmaps();

}

Window::~Window(void){
	delete view;
	delete cam;
	CEGUI::OgreRenderer::destroySystem();
	delete sceneManager;
	delete win;
	delete root->getRenderSystem();
	delete root;
}
