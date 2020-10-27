#include "Vector2D.h"

Vector2D::Vector2D() {
	x = y = 0;
}

Vector2D::Vector2D(int x, int y) {
	this->x = x, this->y = y;
}

Vector2D::Vector2D(int pos[2]) {
	x = pos[0], y = pos[2];
}

Vector2D::~Vector2D(){}

void Vector2D::SetVector(int x, int y) {
	this->x = x, this->y = y;
}

void Vector2D::SetVector(int pos[2]) {
	x = pos[0], y = pos[1];
}

Vector2D Vector2D::Addition(Vector2D v) {
	Vector2D vec;
	vec.x = this->x + v.x;
	vec.y = this->y + v.y;
	return vec;
}

Vector2D Vector2D::ScalarMultiplication(int x) {
	Vector2D vec;
	vec.x = this->x * x;
	vec.y = this->y * x;
	return vec;
}

bool Vector2D::IsZero() {
	if (this->x == this->y == 0)
		return true;
	return false;
}

Vector2D operator + (Vector2D v1, Vector2D v2) {
	return v1.Addition(v2);
}

Vector2D operator * (int x, Vector2D v) {
	return v.ScalarMultiplication(x);
}