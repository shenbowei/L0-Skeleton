#pragma once
#include <Windows.h>//����gl.h����
#include <osgGA/GUIEventHandler>

class KeyboardEventHandle : public osgGA::GUIEventHandler
{
public:
	KeyboardEventHandle(){};
	~KeyboardEventHandle(){};

	bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
};