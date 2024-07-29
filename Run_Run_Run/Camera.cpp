#include "Camera.hpp"

void Camera::setViewPortOffset(Vector2 Offpos) {
	this->portOffset = Offpos;
}

void Camera::follow(Vector2 pos) {
	centerOn(Lerp(getCenter(), pos, CAMERASMOOTHING));
}

void Camera::centerOn(Vector2 pos) {
	this->portOffset.x = clamp(pos.x - SCREEN_WIDTH/2, 0, LEVEL_WIDTH-SCREEN_WIDTH);
	this->portOffset.y = clamp(pos.y - SCREEN_HEIGHT/2, 0, LEVEL_HEIGHT-SCREEN_HEIGHT);
}

Vector2 Camera::getCenter() {
	Vector2 ret;
	ret.set(portOffset.x + SCREEN_WIDTH/2, portOffset.y + SCREEN_HEIGHT/2);
	return ret;
}

