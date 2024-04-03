#include "camera.h"
#include "Vector3.h"

camera::camera() {
	pos = Vector3(0.0, 0.0, 0.0);
	up = Vector3(0.0, 0.0, 0.0);
	pitch = 0;
	roll = 0;
	yaw = 0;
}
camera::~camera()
{
}
void camera::update(float dt)
{
	float cosR, cosP, cosY; //temp values for sin/cos from
	float sinR, sinP, sinY;
	// Roll, Pitch and Yall are variables stored by the camera
	// handle rotation
	// Only want to calculate these values once, when rotation changes, not every frame.
	cosY = cosf(yaw * 3.1415 / 180);
	cosP = cosf(pitch * 3.1415 / 180);
	cosR = cosf(roll * 3.1415 / 180);
	sinY = sinf(yaw * 3.1415 / 180);
	sinP = sinf(pitch * 3.1415 / 180);
	sinR = sinf(roll * 3.1415 / 180);

	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;
	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	right = forward.cross(up);
	right.normalise();
}

void camera::mforward(float dt) {
	pos.x += forward.x * speed * dt;
	pos.y += forward.y * speed * dt;
	pos.z += forward.z * speed * dt;
}

void camera::mback(float dt) {
	pos.x -= forward.x * speed * dt;
	pos.y -= forward.y * speed * dt;
	pos.z -= forward.z * speed * dt;
}

void camera::mdown(float dt)
{
	pos.x -= up.x * speed * dt;
	pos.y -= up.y * speed * dt;
	pos.z -= up.z * speed * dt;
}

void camera::mup(float dt)
{
	pos.x += up.x * speed * dt;
	pos.y += up.y * speed * dt;
	pos.z += up.z * speed * dt;
}

void camera::mleft(float dt)
{
	pos.x -= right.x * speed * dt;
	pos.y -= right.y * speed * dt;
	pos.z -= right.z * speed * dt;
}

void camera::mright(float dt)
{
	pos.x += right.x * speed * dt;
	pos.y += right.y * speed * dt;
	pos.z += right.z * speed * dt;
}

void camera::rleft(float dt)
{
	roll += rotate * dt*30;
}

void camera::rright(float dt)
{
	roll -= rotate * dt * 30;
}

void camera::reset(float)
{
	pitch = 0;
	roll = 0;
	yaw = 0;
}


bool camera::mousecheck(float dt, float x, float y)
{
	bool movement = false;

	if (x != 0) {
		yaw += dt * rotate * x;
			movement = true;
	}
	if (y != 0) {
		pitch += dt * rotate * y;
		movement = true;
	}
	return movement;
}

Vector3 camera::getpos()
{
	return pos;
}

Vector3 camera::getlook()
{
	return pos+forward;
}

Vector3 camera::getup()
{
	return up;
}

void camera::setpos(float x1, float y1, float z1 , float x2, float y2, float z2, float x3, float y3, float z3)
{
	pos.x = x1;
	pos.y = y1;
	pos.z = z1;
	forward.x = x2;
	forward.y = y2;
	forward.z = z2;
	up.x = x3;
	up.y = y3;
	up.z = z3;
}
