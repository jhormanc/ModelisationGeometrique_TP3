#include "GL/glut.h"    

#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>
#include <glm\glm\glm.hpp>

#define WIDTH  480
#define HEIGHT 480

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1
#define PI 3.14159

#define KEY_ESC 27

GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 }; // Black Color
GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 }; // White Color
GLfloat qaRed[] = { 1.0, 0.0, 0.0, 1.0 }; // Red Color
GLfloat qaGreen[] = { 1.0, 0.0, 0.0, 1.0 }; // Green Color
GLfloat qaBlue[] = { 0.0, 0.0, 1.0, 1.0 }; // Blue Color

// Set lighting intensity and color
GLfloat qaAmbientLight[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat qaDiffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat emitLight[] = { 0.9, 0.9, 0.9, 0.01 };
GLfloat Noemit[] = { 0.0, 0.0, 0.0, 1.0 };

// Light source position
GLfloat qaLightPosition[] = { 0, 0, 0, 1 }; // Positional Light
GLfloat qaLightDirection[] = { 1, 1, 1, 0 }; // Directional Light

const int nb_teapots = 4;
const float teta = 50.;
float rotation_y = 0.;
bool lighting = true;
bool move = false;

// Méthodes
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
GLvoid window_idle();

int main(int argc, char **argv) 
{  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // définition et création de la fenêtre graphique
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Primitives graphiques");

  // initialisation de OpenGL et de la scène
  initGL();  
  init_scene();

  // choix des procédures de callback pour 
  // le tracé graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fenêtre
  glutReshapeFunc(&window_reshape);
  // la gestion des événements clavier
  glutKeyboardFunc(&window_key);
  glutIdleFunc(&window_idle);
  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();  

  return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque

GLvoid initGL()
{
	glClearColor(RED, GREEN, BLUE, ALPHA);
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

	/* enable lighting */
	glEnable(GL_LIGHTING);
	/* enable lights (note: uses default values) */
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	// Set lighting intensity and color
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);
	glLightfv(GL_LIGHT2, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT2, GL_POSITION, qaLightPosition);
	glLightfv(GL_LIGHT2, GL_SPECULAR, qaSpecularLight);
	glLightfv(GL_LIGHT3, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT3, GL_POSITION, qaLightPosition);
	glLightfv(GL_LIGHT3, GL_SPECULAR, qaSpecularLight);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.02f);

	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.5f);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.f);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.03f);

	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 2.f);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.f);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.04f);
}

void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre
GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //  | GL_DEPTH_BUFFER_BIT

	render_scene();

	// trace la scène graphique qui vient juste d'être définie
	glFlush();
	glutSwapBuffers();
}

// fonction de call-back pour le redimensionnement de la fenêtre
GLvoid window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 15.0);

  // toutes les transformations suivantes s´appliquent au modèle de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier
GLvoid window_key(unsigned char key, int x, int y) 
{  
	switch (key) 
	{
	case KEY_ESC:
		exit(1);
		break;
	case 'l':
		lighting = !lighting;
		if (lighting)
			glEnable(GL_LIGHTING);
		else
			glDisable(GL_LIGHTING);
		break;
	case 'm':
		move = !move;
		break;
	default:
		printf("La touche %d n´est pas active.\n", key);
		break;
	}
}

GLvoid window_idle() 
{  
	if (move)
		rotation_y += 0.4;

	if (rotation_y > 360.)
		rotation_y = 0.;

	glutPostRedisplay();
}


void render_scene()
{
	const int nb = nb_teapots + 1;
	float angle = 0.;
	float y = 0., x = 0.;
	float eps_y;

	glMatrixMode(GL_MODELVIEW);

	// Description de la scene
	glLoadIdentity();

	// Preserve modelview matrix
	glPushMatrix();

	glTranslatef(2., -8., 0.);
	glRotatef(20., 0., 0., 1.);
	for (int i = nb; i > 1; i--)
	{
		angle = (float)((nb - i) * teta);
		y = (float)(i + i / 1.9);

		glRotatef(angle, 0., 1., 0.);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, new GLfloat[] { (float)(i / (float)nb), (float)(1. - i / (float)nb), 0., 1. });
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[] { (float)(i / (float)nb), (float)(1. - i / (float)nb), 0., 1. });
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.);
		glutSolidTeapot(i);
		glTranslatef(0., y, 0.);
	}

	// Return to previous modelview matrix
	glPopMatrix();

	angle = 0.;
	y = 0.;

	glPushMatrix();
	glTranslatef(2., -8., 0.);
	glRotatef(20., 0., 0., 1.);

	for (int i = nb; i > 1; i--)
	{
		eps_y = 2.8 + (i - 2) * 0.2;
		angle += (float)((nb - i) * teta);
		x = (float)(i + 2 * i / (float)(nb - 1.));

		glPushMatrix();

		glTranslatef(0., y + eps_y, 0.);
		glRotatef(angle + rotation_y, 0., 1., 0.);
		glTranslatef(x, 0., 0.);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLight);   
		glutSolidSphere((i - 1.) / (float)(nb + 2.), 25, 25);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);
		
		glPopMatrix();

		glPushMatrix();

		glTranslatef(0., y + eps_y, 0.);
		glRotatef(angle + rotation_y, 0., 1., 0.);
		glTranslatef(x, 0., 0.);

		switch (i)
		{
		case 5:
			glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
			break;
		case 4:
			glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition);
			break;
		case 3:
			glLightfv(GL_LIGHT2, GL_POSITION, qaLightPosition);
			break;
		case 2:
			glLightfv(GL_LIGHT3, GL_POSITION, qaLightPosition);
			break;
		default:
			break;
		}

		y += (float)(i + i / 2.5);
		glPopMatrix();
	}

	glPopMatrix();
 }