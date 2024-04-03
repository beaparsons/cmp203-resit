#pragma once
#include <math.h>
#include "Vector3.h"

class camera
{
public:
	camera();
	~camera();
	float yaw, pitch, roll;
	Vector3 pos;
	Vector3 forward;
	Vector3 up;
	Vector3 right;

	void update(float);
	//gluLookAt(0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	void mforward(float);
	void mback(float);
	void mdown(float);
	void mup(float);
	void mleft(float);
	void mright(float);
	void rleft(float);
	void rright(float);
	void reset(float);
	bool mousecheck(float, float, float);

	Vector3 getpos();
	Vector3 getlook();
	Vector3 getup();

	float speed = 2.0f;
	float rotate = 1.0f;

	void setpos(float,float,float,float,float,float,float,float,float);
};
