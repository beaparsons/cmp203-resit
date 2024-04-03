#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input* in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	// Other OpenGL / render setting should be applied here.
	wood = SOIL_load_OGL_texture(
		"gfx/wood.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT);

	closet = SOIL_load_OGL_texture(
		"gfx/locker.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT);

	walls = SOIL_load_OGL_texture(
		"gfx/walls.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT);

	door = SOIL_load_OGL_texture(
		"gfx/steel.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT);

	floor = SOIL_load_OGL_texture(
		"gfx/floor.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT);

	wardrobe = SOIL_load_OGL_texture(
		"gfx/drobe.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT);

	sky = SOIL_load_OGL_texture(
		"gfx/skybox.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT);

	target = SOIL_load_OGL_texture(
		"gfx/target.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT);

	// Initialise scene variables
	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(width / 2, height / 2);
	model.load("models/teapot.obj", "gfx/grass.png");
}

void Scene::handleInput(float dt)
{
	//c.handleinput(input, dt);
	// Handle user input
	if (cmode) {
		if (input->isKeyDown('w')) {
			c.mforward(dt);
		}
		if (input->isKeyDown('s')) {
			c.mback(dt);
		}
		if (input->isKeyDown(' ')) {
			c.mup(dt);
		}
		if (input->isKeyDown('f')) {
			c.mdown(dt);
		}
		if (input->isKeyDown('d')) {
			c.mright(dt);
		}
		if (input->isKeyDown('a')) {
			c.mleft(dt);
		}
		if (input->isKeyDown('q')) {
			c.rleft(dt);
		}
		if (input->isKeyDown('e')) {
			c.rright(dt);
		}
	}

	if (input->isKeyDown('1')) {
		input->setKeyUp('1');
		cmode = !cmode;
	}
	if (input->isKeyDown('2')) {
		input->setKeyUp('2');
		lightcolour = !lightcolour;
	}

	bool mousemovement = c.mousecheck(dt, (width / 2) - input->getMouseX(), (height / 2) - input->getMouseY());
	if (mousemovement) {
		glutWarpPointer(width / 2, height / 2);
	}
}

void Scene::update(float dt)
{
	// update scene related variables.
	c.update(dt);
	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the position to either the moving or stationary camera
	if (cmode) {
		gluLookAt(c.getpos().x, c.getpos().y, c.getpos().z, c.getlook().x, c.getlook().y, c.getlook().z, c.getup().x, c.getup().y, c.getup().z);
	}
	else {
		gluLookAt(3, 0.5f, 3, 0, 1, 0, 0, -1, 0);
	}
	//light setup
	GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_diff2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat Light_Position[] = { 0.0f, 0.5f, 0.0f, 1.0f };
	GLfloat Light_Ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat LA2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Spot_Direction[] = { 0.0f, 1.0f, 0.0f };
	GLfloat Spot_Direction2[] = { 0.0f, -1.0f, 0.0f };
	//light changing colours
	if (lightcolour) {
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse);
	}
	else {
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_diff2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_diff2);
	}
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Spot_Direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 75.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0f);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LA2);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Position);

	glLightfv(GL_LIGHT2, GL_POSITION, Light_Position);
	glLightfv(GL_LIGHT2, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Spot_Direction2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 75.0f);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1.0f);
	glEnable(GL_LIGHT2);

	// Render geometry/scene here -------------------------------------
	glPushMatrix();
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT1);
	glTranslatef(c.getpos().x, c.getpos().y, c.getpos().z);
	skybox();
	glDisable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);

	glPopMatrix();
	//creates room
	room();
	glPushMatrix();
	//translates and loades model
	glTranslatef(15.0, 0.0, 15.0);
	glRotatef(180, 1, 0, 0);
	glScalef(0.1, 0.1, 0.1);
	model.render();
	glPopMatrix();
	glPushMatrix();
	//translates the lockers and renders them
	glTranslatef(-3.0, 0.0, 1.5);
	locker();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0, 0.0, -3.5);
	glRotatef(180, 0, 1, 0);
	locker();
	glPopMatrix();
	glPushMatrix();
	//translates and renders benches
	glTranslatef(0.0, 0.0, 2.0);
	bench();
	glTranslatef(-1.5, 0.0, 0.0);
	glRotatef(-90, 0, 1, 0);
	bench();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.0, 0.0, -4.0);
	bench();
	glPopMatrix();
	//renders the wardrobe
	drobe();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);

	//glass door
	glColor4f(0.9f, 0.9f, 1.0f, 0.5);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.0f, 2.5f, -2.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-4.0f, 2.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.0f, 0.0f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-4.0f, 0.0f, -2.5f);

	glEnd();
	glDisable(GL_BLEND);
	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();

	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}
void Scene::skybox() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, sky);
	glBegin(GL_QUADS);
	//front
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.5f, 0.25f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	//right
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f, 0.25f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	//left
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.25f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	//back
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.75f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.25f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	//top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.25f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f, 0.25f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	//bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.25f, 0.75f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.5f, 0.75f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glEnd();
}

//contsructs the walls and floors of the scene
void Scene::planeXZ(float x, float y, float z, float TMX, float TMY)
{
	glTexCoord2f(x / 10 / TMX, (z + 1) / 10 / TMY);
	glVertex3f((x / 10), y, (z / 10) + 0.1);
	glTexCoord2f((x + 1) / 10 / TMX, (z + 1) / 10 / TMY);
	glVertex3f((x / 10) + 0.1, y, (z / 10) + 0.1);
	glTexCoord2f((x + 1) / 10 / TMX, z / 10 / TMY);
	glVertex3f((x / 10) + 0.1, y, (z / 10));
	glTexCoord2f(x / 10 / TMX, z / 10 / TMY);
	glVertex3f((x / 10), y, (z / 10));
}

void Scene::planeXY(float x, float y, float z, float TMX, float TMY)
{
	glTexCoord2f(x / 10 / TMX, (y + 1) / 10 / TMY);
	glVertex3f(x / 10, y / 10 + 0.1, z);
	glTexCoord2f((x + 1) / 10 / TMX, (y + 1) / 10 / TMY);
	glVertex3f(x / 10 + 0.1, y / 10 + 0.1, z);
	glTexCoord2f((x + 1) / 10 / TMX, y / 10 / TMY);
	glVertex3f((x / 10) + 0.1, y / 10, z);
	glTexCoord2f(x / 10 / TMX, y / 10 / TMY);

	glVertex3f((x / 10), y / 10, z);
}

void Scene::planeYZ(float x, float y, float z, float TMX, float TMY)
{
	glTexCoord2f(z / 10 / TMX, (y + 1) / 10 / TMY);
	glVertex3f(x, (y / 10) + 0.1, z / 10);
	glTexCoord2f((z + 1) / 10 / TMX, (y + 1) / 10 / TMY);
	glVertex3f(x, y / 10 + 0.1, (z / 10) + 0.1);
	glTexCoord2f((z + 1) / 10 / TMX, y / 10 / TMY);
	glVertex3f(x, y / 10, (z / 10) + 0.1);
	glTexCoord2f(z / 10 / TMX, y / 10 / TMY);

	glVertex3f(x, y / 10, (z / 10));
}

void Scene::bench() {

	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, wood);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.0f, 2.0f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.0f, 2.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.25f, 2.0f, 0.05f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.25f, 2.0f, 0.45f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.25f, 2.5f, 0.3f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.25f, 2.5f, 0.2f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 2.0f, 0.05f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 2.0f, 0.45f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 2.5f, 0.3f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, 2.5f, 0.2f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.75f, 2.0f, 0.05f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.75f, 2.0f, 0.45f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.75f, 2.5f, 0.3f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.75f, 2.5f, 0.2f);

	glEnd();
}
void Scene::drobe() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, wardrobe);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 3.5f);
	glTexCoord2f(2.9f, 0.0f);
	glVertex3f(2.5f, 0.5f, 3.5f);
	glTexCoord2f(2.9f, 1.0f);
	glVertex3f(2.5f, 2.5f, 3.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 2.5f, 3.5f);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glBegin(GL_QUADS);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glColor3f(0.45f, 0.35f, 0.25f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.5f, 0.5f, 3.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.5f, 0.5f, 4.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.5f, 2.5f, 4.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.5f, 2.5f, 3.5f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 3.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 4.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 2.5f, 4.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 2.5f, 3.5f);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 3.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.5f, 0.5f, 3.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.5f, 0.5f, 4.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 4.0f);

	glEnd();
}
void Scene::locker() {

	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, closet);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 0.5f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 2.5f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 2.5f, 0.0f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.995f, 0.0f);
	glVertex3f(1.0f, 0.5f, 0.0f);
	glTexCoord2f(0.995f, 0.0f);
	glVertex3f(1.0f, 0.5f, 0.5f);
	glTexCoord2f(0.995f, 1.0f);
	glVertex3f(1.0f, 2.5f, 0.5f);
	glTexCoord2f(0.995f, 1.0f);
	glVertex3f(1.0f, 2.5f, 0.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.005f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glTexCoord2f(0.005f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.5f);
	glTexCoord2f(0.005f, 1.0f);
	glVertex3f(0.0f, 2.5f, 0.5f);
	glTexCoord2f(0.005f, 1.0f);
	glVertex3f(0.0f, 2.5f, 0.0f);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.05f);
	glVertex3f(0.0f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.05f);
	glVertex3f(1.0f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.05f);
	glVertex3f(1.0f, 0.5f, 0.0f);
	glTexCoord2f(0.0f, 0.05f);
	glVertex3f(0.0f, 0.5f, 0.0f);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void Scene::room() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, walls);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, -1.0f);
	for (float x = -20; x < 40; x++) {
		for (float y = 0;y < 25;y++) {
			planeXY(x, y, 4, 1, 2.5);
		}
	}


	glNormal3f(-1.0f, 0.0f, 0.0f);
	for (float z = 20; z < 40; z++) {
		for (float y = 0;y < 25;y++) {
			planeYZ(4, y, z, 1, 2.5);
		}
	}

	glNormal3f(0.0f, 0.0f, -1.0f);
	for (float x = 40; x < 50; x++) {
		for (float y = 0;y < 25;y++) {
			planeXY(x, y, 2, 1, 2.5);
		}
	}

	glNormal3f(-1.0f, 0.0f, 0.0f);
	for (float z = 15; z < 20; z++) {
		for (float y = 0;y < 25;y++) {
			planeYZ(5, y, z, 1, 2.5);
		}
	}

	glNormal3f(-1.0f, 0.0f, 0.0f);
	for (float z = -20; z < -15; z++) {
		for (float y = 0;y < 25;y++) {
			planeYZ(5, y, z, 1, 2.5);
		}
	}

	glNormal3f(0.0f, 0.0f, 1.0f);
	for (float x = 40; x < 50; x++) {
		for (float y = 0;y < 25;y++) {
			planeXY(x, y, -2, 1, 2.5);
		}
	}

	glNormal3f(-1.0f, 0.0f, 0.0f);
	for (float z = -40; z < -20; z++) {
		for (float y = 0;y < 25;y++) {
			planeYZ(4, y, z, 1, 2.5);
		}
	}

	glNormal3f(0.0f, 0.0f, 1.0f);
	for (float x = -40; x < 40; x++) {
		for (float y = 0;y < 25;y++) {
			planeXY(x, y, -4, 1, 2.5);
		}
	}

	glNormal3f(1.0f, 0.0f, 0.0f);
	for (float z = -40; z < -25; z++) {
		for (float y = 0;y < 25;y++) {
			planeYZ(-4, y, z, 1, 2.5);
		}
	}

	glNormal3f(1.0f, 0.0f, 0.0f);
	for (float z = 5; z < 20; z++) {
		for (float y = 0;y < 25;y++) {
			planeYZ(-4, y, z, 1, 2.5);
		}
	}

	glNormal3f(0.0f, 0.0f, -1.0f);
	for (float x = -40; x < -20; x++) {
		for (float y = 0;y < 25;y++) {
			planeXY(x, y, 2, 1, 2.5);
		}
	}

	glNormal3f(1.0f, 0.0f, 0.0f);
	for (float z = 20; z < 40; z++) {
		for (float y = 0;y < 25;y++) {
			planeYZ(-2, y, z, 1, 2.5);
		}
	}

	//small room
	glNormal3f(0.0f, 0.0f, 1.0f);
	for (float x = -80; x < -40; x++) {
		for (float y = 0;y < 25;y++) {
			planeXY(x, y, -4, 1, 2.5);
		}
	}


	glNormal3f(1.0f, 0.0f, 0.0f);
	for (float z = -40; z < 20; z++) {
		for (float y = 0;y < 25;y++) {
			planeYZ(-8, y, z, 1, 2.5);
		}
	}


	glNormal3f(0.0f, 0.0f, -1.0f);
	for (float x = -80; x < -40; x++) {
		for (float y = 0;y < 25;y++) {
			planeXY(x, y, 2, 1, 2.5);
		}
	}

	glEnd();
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, target);
	glRotatef(15, 0, 0, 1);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.25f, 1.25f, -3.99f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.0f, 1.25f, -3.99f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.0f, 0.5f, -3.99f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.25f, 0.5f, -3.99f);


	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, door);
	glBegin(GL_QUADS);

	//steel door
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.0f, 2.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, 2.5f, -1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, -1.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, 1.5f);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, floor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_QUADS);

	//floor
	glNormal3f(0.0f, -1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (float z = -40; z < 40; z++) {

		for (float x = -100; x < 60; x++) {

			planeXZ(x, 2.5f, z, 1, 1);
		}
	}

	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);

	glBegin(GL_QUADS);


	//roof
	glNormal3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.8f, 0.8f, 0.8f);


	for (float z = -40; z < 40; z++) {
		for (float x = -100; x < 60; x++) {
			planeXZ(x, 0.0f, z, 1, 1);
		}
	}

	glEnd();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h)
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame * 1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width / (float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
