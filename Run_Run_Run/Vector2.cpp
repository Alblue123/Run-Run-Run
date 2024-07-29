#include "Vector2.hpp"


Vector2::Vector2() {
	this->x = this->y = 0;
}

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

void Vector2::add(Vector2 v) {
	this->x += v.x;
	this->y += v.y;
}

void Vector2::add(float x, float y) {
	this->x += x;
	this->y += y;
}

void Vector2::sub(Vector2 v) {
	this->x -= v.x;
	this->y -= v.y;
}

void Vector2::sub(float x, float y) {
	this->x -= x;
	this->y -= y;
}

void Vector2::mul(float f) {
	this->x *= f;
	this->y *= f;
}

Vector2 Vector2::mul_N(float f) {
	Vector2 ret;
	ret.x = this->x*f;
	ret.y = this->y*f;
	return ret;
}
