#include "pch.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <GL/glut.h>

using namespace std;

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.50196078431f, 0.62352941176f, 1.0f, 1.0);
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 1.0, 6.0);
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
	/*
	// Set the camera
	gluLookAt(0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f);
	*/
	glRotatef(5.0f, 1.0f, 0.0f, 0.0f);

	glTranslatef(_dir_x, 0.0f, 0.0f);
	glTranslatef(0.0f,_dir_y, 0.0f);

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
	/*
	if (cnt==0) angle += 0.1f;
	if (angle > 1) {
		angle = 0;
		cnt = 1;
	}
	//cout << angle<<endl;
	*/
}

void MoveBoat_rl(int dir_x) {
	_dir_x += dir_x * 0.1;
}

void MoveBoat_ud(int dir_y) {
	_dir_y += dir_y * 0.1;
}

const float PI = 3.14159265359;
void DrawCircle2(float cx, float cy, float r, float deformation_angle) {
	// deformation_angle represents angle of each line in our 
	// line loop where is the perfect number is 1 to draw a circle
	// smaller than 1 represents an arc, bigger than 1 represents a ploygon with n angle between each two lines
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float color7[3] = { 242,116,11 };
	coloring(color7);
	glBegin(GL_POLYGON);
	double angle, x, y;
	for (int i = 0; i <= 360; i++) {
		//get the current angle
		angle = deformation_angle * 2 * PI * i / 360;
		//calculate the x component 
		x = cx + r * cos(angle);
		//calculate the y component
		y = cy + r * sin(angle);
		//output vertex
		glVertex3d(x, y, -5);
	}
	glEnd(); //End coordinates
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
/*
float _angle = 0.0f;

void renderScene(void) {


	// Set the camera
	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glRotatef(_angle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(-2.0f, -2.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0);
	glVertex3f(0.0f, 2.0f, 0.0);
	glEnd();

	_angle += 0.1f;


}
*/

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//DrawCircle2(2.56, 1.45, 0.4, 1);
	DrawBoat();
	float first_wave[3] = { 35, 137, 218 };
	float second_wave[3] = { 15, 94, 156 };
	float third_wave[3] = { 153, 217, 234 };
	float fourth_wave[3] = { 69, 122, 211 };
	DrawWave(fourth_wave, 3, 0.15, 0.15, 0.22);
	DrawWave(third_wave, 2.25, 0.07, 0.01, 0.1);
	DrawWave(second_wave, 4, 0.05, 0.1, 0.03);
	DrawWave(first_wave, 4.5, 0.1, 0.05, -0.19);
	//renderScene();
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
	//glutIdleFunc(DrawBoat);
	glutMainLoop();
	return 0;
}
