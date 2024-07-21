#ifndef CAMERA_H
#define CAMERA_H

#include "Imports.h"
class Camera {

public:

	float min_zoom,max_zoom;
	sf::View view;

	Camera();
};



#endif