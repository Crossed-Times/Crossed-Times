#ifndef WINDOW_H
#define WINDOW_H

#include <Ogre.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <CEGUI.h>
#include <RendererModules\Ogre\CEGUIOgreRenderer.h>

class Window{
	public:
		Window(void);
		~Window(void);
		void start(void);
		void run(void);
		std::vector<std::string> load(const char *file);
	private:
		Ogre::Root *root;
		Ogre::RenderWindow *win;
		Ogre::SceneManager *sceneManager;
		Ogre::Camera *cam;
		Ogre::Viewport *view;
		std::string* separate(std::string el);
	protected:
		CEGUI::OgreRenderer *cRenderer;
		void gui(void);
};

#endif
