/*
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <stdio.h>

#include "Shader_Loader.h"

using namespace Core;

GLuint program;

void renderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);//clear red

	using namespace Core;

	GLuint program;

	glutSwapBuffers();
}


void Init()
{

	glEnable(GL_DEPTH_TEST);

	//load and compile shaders
	Core::Shader_Loader shaderLoader;
	program = shaderLoader.CreateProgram("Shaders\\Vertex_Shader.glsl",
		"Shaders\\Fragment_Shader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("OpenGL First Window");

	glEnable(GL_DEPTH_TEST);

	// register callbacks
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
*/


//Install-Package nupengl.core






#include<QGLViewer/qglviewer.h>
#include<QGLViewer/manipulatedCameraFrame.h>
#include<qapplication.h>
#include<cmath>
#include<iostream>
#include<QKeyEvent>

class Viewer : public QGLViewer
{
protected:
	virtual void draw();
	virtual void init();
	virtual void animate();
	virtual QString helpString() const;
	void keyPressEvent(QKeyEvent * e);
private:
	float paletka_x;
	float paletka_y;
	float paletka_sx;
	float paletka_sy;

	float kwadrat_x;
	float kwadrat_y;
	float kwadrat_sx;
	float kwadrat_sy;

	float kwadrat_vel_x;
	float kwadrat_vel_y;

	int punkty;
};

void Viewer::keyPressEvent(QKeyEvent * e)
{
	if (e->key() == Qt::Key_Left)
	{
		paletka_x -= 0.05;
		paletka_x = std::max(paletka_x, -1.0f);
		std::cerr << "left" << std::endl;
	}
	else if (e->key() == Qt::Key_Right)
	{
		paletka_x += 0.05;
		paletka_x = std::min(paletka_x, 1 - paletka_sx);
		std::cerr << "right" << std::endl;
	}
	else
		QGLViewer::keyPressEvent(e);

	updateGL();
}


void Viewer::init()
{
	restoreFromFile();
	setBackgroundColor(QColor(255, 255, 0));
	help();

	paletka_x = -1.0;
	paletka_y = -1.0;
	paletka_sx = 0.3;
	paletka_sy = 0.1;

	kwadrat_sx = 0.05;
	kwadrat_sy = 0.05;
	kwadrat_x = 0;
	kwadrat_y = 1 - kwadrat_sy;

	kwadrat_vel_x = -0.005;
	kwadrat_vel_y = -0.02;

	punkty = 0;
}

void Viewer::draw()
{
	if (not animationIsStarted()) {
		drawText(5, 15, "Press enter to start! ");
	}
	drawText(5, 30, "Points: " + QString::number(punkty));
	glBegin(GL_QUADS);
	glColor3f(1, 0.3, 0.5);
	glNormal3f(0, 0, 1);
	glVertex3f(paletka_x, paletka_y, 0);
	glVertex3f(paletka_x + paletka_sx, paletka_y, 0);
	glVertex3f(paletka_x + paletka_sx, paletka_y + paletka_sy, 0);
	glVertex3f(paletka_x, paletka_y + paletka_sy, 0);

	glColor3f(0, 0.5, 0.5);
	glVertex3f(kwadrat_x, kwadrat_y, 0);
	glVertex3f(kwadrat_x + kwadrat_sx, kwadrat_y, 0);
	glVertex3f(kwadrat_x + kwadrat_sx, kwadrat_y + kwadrat_sy, 0);
	glVertex3f(kwadrat_x, kwadrat_y + kwadrat_sy, 0);
	glEnd();
}

void Viewer::animate()
{
	kwadrat_x += kwadrat_vel_x;
	kwadrat_y += kwadrat_vel_y;

	// odbijamy pileczke od scian pudeleczka
	if (kwadrat_x < -1.0 or kwadrat_x >(1 - kwadrat_sx)) kwadrat_vel_x *= -1;
	if (kwadrat_y > (1 - kwadrat_sy)) kwadrat_vel_y *= -1;

	// odbijamy pileczke:
	if (
		(kwadrat_y             < (-1.0 + paletka_sy))
		and ((kwadrat_x + kwadrat_sx) >       paletka_x)
		and (kwadrat_x             < (paletka_x + paletka_sx))
		and (kwadrat_y             > -1.0)
		) kwadrat_vel_y *= -1;


	if (kwadrat_y < -1.0)
	{ // stracilismy pi³kê
		punkty -= 1;
		stopAnimation();
		kwadrat_y = 1 - kwadrat_sy;
	}
}

QString Viewer::helpString() const
{
	QString text("<h2>P a l e t k a</h2>");
	text += "TUTAJ TRZEBA NAPISAC POMOC<br><br><br>. ";
	return text;
}

int main(int argc, char** argv)
{
	QApplication application(argc, argv);
	Viewer v;
	v.show();
	return application.exec();
}