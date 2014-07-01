#include "Window.h"

Window::Window(void){
	root = NULL;
	win = NULL;
	sceneManager = NULL;
	cam = NULL;
	view = NULL;
}

void Window::start(void){
	root = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");

	Ogre::RenderSystem *rs = root->getRenderSystemByName("Direct3D9 Rendering Subsystem");
	root->setRenderSystem(rs);

	std::vector<std::string> res = load("ogre.cfg");
	for(size_t i = 0; i < res.size(); ++i){
		std::string *s = separate(res[i]);
		rs->setConfigOption(s[0], s[1]);
	}

	win = root->initialise(true, "Crossed Times");

	sceneManager = root->createSceneManager(Ogre::ST_GENERIC, "Menu");
	cam = sceneManager->createCamera("Camera");
	view = win->addViewport(cam);
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

Window::~Window(void){
	delete view;
	delete cam;
	delete sceneManager;
	delete win;
	delete root->getRenderSystem();
	delete root;
}
