#include "GL/glut.h"    

#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>
#include <time.h>
#include <glm\glm\glm.hpp>

#define WIDTH  800
#define HEIGHT 600

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

const int nb_teapots = 5;
float teta = 50.;
bool solid = true;
float rotation_y = 0.;
float delta_rotation_y = 0.4;
bool lighting = true;
bool move = false;
bool spheres = false;
float tabSphere[nb_teapots][4]; // delta x, y, rotation y et sens de rotation

// Méthodes
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
GLvoid window_idle();
void printCommandes();
float random();
void initTabSpheres();
//float sum(const int i);

int main(int argc, char **argv) 
{ 
	srand(time(NULL));
	printCommandes();
	initTabSpheres();
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  // définition et création de la fenêtre graphique
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(500, 400);
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
	glEnable(GL_LIGHT4);

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
	glLightfv(GL_LIGHT4, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT4, GL_POSITION, qaLightPosition);
	glLightfv(GL_LIGHT4, GL_SPECULAR, qaSpecularLight);

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

	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 2.5f);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.f);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.05f);
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
	case 'L':
		lighting = !lighting;
		if (lighting)
			glEnable(GL_LIGHTING);
		else
			glDisable(GL_LIGHTING);
		break;
	case 'm':
	case 'M':
		move = !move;
		break;
	case 'p':
	case 'P':
		solid = !solid;
		break;
	case 'r':
	case 'R':
		if (spheres)
		{
			initTabSpheres();
			delta_rotation_y = 0.03;
		}
		else
		{
			delta_rotation_y = 0.4;
			move = false;
			rotation_y = 0.;
		}
		break;
	case 'i':
	case 'I':
		if (delta_rotation_y > -3.)
		{
			if (delta_rotation_y > -2.)
				delta_rotation_y -= 0.02;
			else
				delta_rotation_y -= 0.1;
		}
		break;
	case 'o':
	case 'O':
		if (delta_rotation_y < 3.)
		{
			if (delta_rotation_y < 1.)
				delta_rotation_y += 0.02;
			else
				delta_rotation_y += 0.1;
		}
		break;
	case 'k':
	case 'K':
		spheres = !spheres;
		break;
	case 32: // 'Espace'
 		teta += 10.;
		if (teta >= 360.)
			teta = 0.;
		break;
	default:
		printf("La touche %d n´est pas active.\n", key);
		printCommandes();
		break;
	}
}

GLvoid window_idle() 
{  
	if (move)
		rotation_y += delta_rotation_y;

	if (rotation_y > 360.)
		rotation_y = 0.;

	glutPostRedisplay();
}


void render_scene()
{
	const int nb = nb_teapots;
	float angle = 0.;
	float y = 0., x = 0.;
	float eps_y;
	float sens;

	glMatrixMode(GL_MODELVIEW);

	// Description de la scene
	glLoadIdentity();

	glPushMatrix();

	// Teapots - Spheres
	glTranslatef(2., -8., 0.);
	glRotatef(20., 0., 0., 1.);
	for (int i = nb_teapots; i >= 1; i--)
	{
		angle = (float)((nb - i) * teta);
		y = (float)(i + i / 1.9);

		glRotatef(angle, 0., 1., 0.);
		if (lighting)
		{
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, new GLfloat[] { (float)(i / (float)nb), (float)(1. - i / (float)nb), 0., 1. }); // (float)((nb - i) / (float)nb)
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[] { (float)(i / (float)nb), (float)(1. - i / (float)nb), 0., 1. });
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.);
		}
		else
			glColor3f((float)(i / (float)nb), (float)(1. - i / (float)nb), 0.);

		if (spheres)
		{
			if (solid)
				glutSolidSphere(i * 0.8, 50, 50);
			else
				glutWireSphere(i * 0.8, 50, 50);
		}
		else
		{
			if (solid)
				glutSolidTeapot(i);
			else
				glutWireTeapot(i);
		}
		glTranslatef(0., y, 0.);
	}

	glPopMatrix();

	angle = 0.;
	y = 0.;

	glPushMatrix();

	// Lights
	glTranslatef(2., -8., 0.);
	glRotatef(20., 0., 0., 1.);

	for (int i = nb; i >= 1; i--)
	{
		if (spheres)
		{
			x = tabSphere[i - 1][0];
			eps_y = tabSphere[i - 1][1];
			angle = tabSphere[i - 1][2];
			sens = tabSphere[i - 1][3];
		}
		else
		{
			x = (float)(i + i / 1.9);
			eps_y = (float)i * 0.66;
			angle += (float)((nb - i) * teta);
			sens = 1.;
		}

		glPushMatrix();

		// Spheres
		glTranslatef(0., y + eps_y, 0.);
		glRotatef(angle + sens * rotation_y, 0., 1., 0.);
		glTranslatef(x, 0., 0.);

		if (lighting)
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLight);
		else
			glColor3f(1., 1., 1.);

		if (solid)
			glutSolidSphere((float)i / (float)(nb + 3.), 25, 25);
		else
			glutWireSphere((float)i / (float)(nb + 3.), 25, 25);

		if (lighting)
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);
		
		glPopMatrix();


		// Light
		if (lighting)
		{
			glPushMatrix();

			glTranslatef(0., y + eps_y, 0.);
			glRotatef(angle + sens * rotation_y, 0., 1., 0.);
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
			case 1:
				glLightfv(GL_LIGHT4, GL_POSITION, qaLightPosition);
				break;
			default:
				break;
			}
			glPopMatrix();
		}

		y += (float)(i + i / 1.9); 
	}

	glPopMatrix();
 }

void printCommandes()
{
	printf("=== Commandes ===\n\n");
	printf(" L : activer / desactiver le lighting\n");
	printf(" M : activer / desactiver la rotation des spheres\n");
	printf(" I / O : diminuer / augmenter la vitesse de rotation des spheres\n");
	printf(" R : changer de type d'affichage (Solid / Wire)\n");
	printf(" K : changer de type d'objet (teapot / sphere)\n");
	printf(" Espace : augmenter l'angle de rotation des objets de 10 degres\n");
	printf(" R : reset\n");
	printf(" Echap : quitter\n");
}

float random(const float min, const float max)
{
	return (float)(rand() * (max - min) / RAND_MAX + min);
}

void initTabSpheres()
{
	for (int i = nb_teapots; i >= 1; i--)
	{
		tabSphere[i - 1][0] = i * 0.8 + random(0., i) + 2. * (float)i / (float)(nb_teapots + 3.);
		tabSphere[i - 1][1] = random(-0.9, 0.9) * i * 0.8;
		tabSphere[i - 1][2] = random(-1., 1.) * 180.;
		tabSphere[i - 1][3] = random(-1., 1.) >= 0 ? 1. : -1;
	}
}