#pragma once
#include <Windows.h>//²»¼Ógl.h±¨´í£¡
#include <osgGA/GUIEventHandler>

class KeyboardEventHandle : public osgGA::GUIEventHandler
{
public:
	KeyboardEventHandle(){};
	~KeyboardEventHandle(){};

	bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
};