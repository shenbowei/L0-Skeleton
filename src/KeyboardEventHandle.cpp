#include "KeyboardEventHandle.h"
#include "GlobalFunction.h"

#include <osgDB/ReadFile>
#include <iostream>


bool KeyboardEventHandle::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::KEYDOWN:
		cout<<"KEYDOWN"<<endl;
		if(ea.getKey() == 'h' || ea.getKey() == 'H')
		{
			GlobalFunction::geode_skletonPoint->setNodeMask( !GlobalFunction::geode_skletonPoint->getNodeMask() );
			cout<<"getKey() == 'h'"<<endl;
		}
		break;

	default:
		break;
	}

	return false;
}