#include "Camera.h"


Camera::Camera()
{	
	min_zoom = 2000.f;
	max_zoom = 5706.23f;

	view = sf::View();
	view.setSize(2000, 1150.f);
	
	
}