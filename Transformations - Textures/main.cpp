#include "pch.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <GL/glut.h>
#include "imageloader.h"

using namespace std;
//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}
GLuint _textureId; //The id of the texture

void initRendering() {
	glOrtho(0.0f, 1200.0, 600.0, 0.0, 0.0, 1.f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	Image* image = loadBMP("clouds.bmp");
	_textureId = loadTexture(image);
	delete image;
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void coloring(float colors[3]) {
	float   r = colors[0] / 255, g = colors[1] / 255, b = colors[2] / 255;
	glColor3f(r, g, b);
}

float _dir_x = 0.0f;
float _dir_y = 0.0f;
float angle = 0.0f;
int cnt = 0;
void DrawBoat() {

	float color1[3] = { 235,172,79 };
	float color2[3] = { 222,233,244 };
	float color3[3] = { 175,196,225 };
	float color4[3] = { 98,91,105 };
	float color5[3] = { 76,77,96 };

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glRotatef(_angle, 1.0f, 0.0f, 0.0f);

	glTranslatef(_dir_x, 0.0f, 0.0f);
	glTranslatef(0.0f, _dir_y, 0.0f);

	glBegin(GL_QUADS);
	coloring(color4);
	glVertex3f(-0.56, 0.33, -5);
	glVertex3f(-0.56, 0.36, -5);
	glVertex3f(-0.625, 0.36, -5);
	glVertex3f(-0.625, 0.33, -5);
	glEnd();

	glBegin(GL_QUADS);
	coloring(color4);
	glVertex3f(-0.585, 0.33, -5);
	glVertex3f(-0.585, 0.30, -5);
	glVertex3f(-0.6, 0.30, -5);
	glVertex3f(-0.6, 0.33, -5);
	glEnd();

	glBegin(GL_TRIANGLES);
	coloring(color5);
	glVertex3f(-0.15, 0.3, -5);
	glVertex3f(0.2, 0.3, -5);
	glVertex3f(0.0, 0.39, -5);
	glEnd();

	glBegin(GL_QUADS);
	coloring(color1);
	glVertex3f(0.25, 0.3, -5);
	glVertex3f(0.2, 0.3, -5);
	glVertex3f(0.0, 0.39, -5);
	glVertex3f(0.03, 0.40, -5);
	glEnd();

	glBegin(GL_QUADS);
	coloring(color4);
	glVertex3f(0.27, 0.33, -5);
	glVertex3f(0.27, 0.30, -5);
	glVertex3f(0.3, 0.30, -5);
	glVertex3f(0.3, 0.33, -5);
	glEnd();

	glBegin(GL_QUADS);
	coloring(color4);
	glVertex3f(0.4, 0.33, -5);
	glVertex3f(0.4, 0.30, -5);
	glVertex3f(0.37, 0.30, -5);
	glVertex3f(0.37, 0.33, -5);
	glEnd();

	glBegin(GL_QUADS);
	coloring(color4);
	glVertex3f(0.47, 0.33, -5);
	glVertex3f(0.47, 0.30, -5);
	glVertex3f(0.5, 0.30, -5);
	glVertex3f(0.5, 0.33, -5);
	glEnd();

	glBegin(GL_QUADS);
	coloring(color3);
	glVertex3f(0.75, 0.25, -5);
	glVertex3f(-.75, 0.25, -5);
	glVertex3f(-0.75, 0.3, -5);
	glVertex3f(0.75, 0.3, -5);
	glEnd();

	glBegin(GL_QUADS);
	coloring(color2);
	glVertex3f(0.75, 0.25, -5);
	glVertex3f(-.75, 0.25, -5);
	glVertex3f(-0.5, 0.05, -5);
	glVertex3f(0.5, 0.05, -5);
	glEnd();

	glBegin(GL_QUADS);
	coloring(color1);
	glVertex3f(0.45, 0.0, -5);
	glVertex3f(-.45, 0.0, -5);
	glVertex3f(-0.5, 0.05, -5);
	glVertex3f(0.5, 0.05, -5);
	glEnd();

	glPopMatrix();
	if (cnt==0) angle += 0.1f;
	if (angle > 15) {
		angle = -15;
	}
}

void MoveBoat_rl(int dir_x) {
	_dir_x += dir_x * 0.1;
}

void MoveBoat_ud(int dir_y) {
	_dir_y += dir_y * 0.1;
}

float _x = 1.0f;
void DrawWave(float colors[3], float wave_length, float amplitude, float inc, float height) {
	float k, x, y;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(_x, 0.0f, 0.0f);

	glBegin(GL_TRIANGLE_STRIP);
	coloring(colors);
	for (x = -50; x <= 50; x += inc) {
		k = 2 * 3.14 / wave_length;
		y = amplitude * sin(k * (x)) - height;
		glVertex3f(x, y - 35, -5);
		glVertex3f(x, y, -5);
	}
	glEnd();
	glPopMatrix();
}

void update(int value) {
	_x += 0.06f;
	if (_x > 20) {
		_x -= 20;
	}
	glutPostRedisplay();
	glutTimerFunc(60, update, 0);
}


void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glTranslatef(-5.0f, -2.0f, -6.0f);

	GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat directedLightPos[] = { -0.0f, 15.0f, 20.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0); glVertex2d( 0.0, 0.0);
	glTexCoord2d(1.0, 0.0); glVertex2d(10.0, 0.0);
	glTexCoord2d(1.0, 1.0); glVertex2d(10.0, 5.0);
	glTexCoord2d(0.0, 1.0); glVertex2d( 0.0, 5.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

  DrawBoat();
	float first_wave[3] = { 35, 137, 218 };
	float second_wave[3] = { 15, 94, 156 };
	float third_wave[3] = { 153, 217, 234 };
	float fourth_wave[3] = { 69, 122, 211 };
	DrawWave(fourth_wave, 3, 0.15, 0.15, 0.22);
	DrawWave(third_wave, 2.25, 0.07, 0.01, 0.1);
	DrawWave(second_wave, 4, 0.05, 0.1, 0.03);
	DrawWave(first_wave, 4.5, 0.1, 0.05, -0.19);
	glutSwapBuffers(); //Send the 3D scene to the screen
}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case '\x1B': //Escape key
		exit(0); //Exit the program
		break;
	case '\x34': //4 numpad
	case 'a': //a keypad		
		MoveBoat_rl(-1); //Left
		cout << "left";
		break;
	case 'd': //d keypad
	case '\x36': //6 numpad
		MoveBoat_rl(1);//Right
		cout << "right";
		break;
	case '\x32': //2 numpad
	case 's': //s keypad		
		MoveBoat_ud(-1); //Down
		cout << "down";
		break;
	case 'w': //w keypad
	case '\x38': //8 numpad
		MoveBoat_ud(1);//Up
		cout << "up";
		break;
	}
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 600);
	glutCreateWindow("Dynamic Waves");
	initRendering();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutMainLoop();
	return 0;
}
