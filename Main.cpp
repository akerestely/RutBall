#include <Windows.h>
#include <ctime>
#include "iostream"
#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "CameraSpectator.h"
#include "Tools.h"
#include "vector"
#include "Map.h"
#include "Building.h"
#include "Ball.h"

#define SPEED 0.3
#define ROTATION 3

CCamera cam;
Map brasovMap;
Ball *ball;
bool up,down,left,right,rotLeft,rotRight, jump;
int texNr=0;
int lastCheckPointKey;
std::vector<Building> buildings;

void initGL() 
{
 	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	try
	{
		
		brasovMap = Map("Map.xml");
		ball = new Ball(WIDTH / 8, Point(0, 0, 0));
	}
	catch(char* message)
	{
		throw message;
	}
	srand(time(NULL));
	buildings.push_back(Building(Point(35.0,0.,16.0),20,3,16));
   //__________________________2 ______________________
   buildings.push_back(Building(Point(49.0,0.,22.0),15,2,15));
   //_____________________3__________
   buildings.push_back(Building(Point(55.0,0.,10.0),15,3,16));

   buildings.push_back(Building(Point(10.0,0.,-2.0),12,3,10));
   buildings.push_back(Building(Point(-8.0,0.,2.0),10,3,10));
   buildings.push_back(Building(Point(56.0,0.,-82.0),10,3,-10));
   buildings.push_back(Building(Point(64.0,0.,-96.0),12,3,-10));
   buildings.push_back(Building(Point(72.0,0.,-84.0),12,3,-10));
   buildings.push_back(Building(Point(85.0,0.,-81.0),12,3,-14));
   buildings.push_back(Building(Point(98.0,0.,-78.0),12,3,-10));
   buildings.push_back(Building(Point(111.0,0.,-77.0),12,3,-10));
   buildings.push_back(Building(Point(125.0,0.,-78.0),12,3,-10));
   buildings.push_back(Building(Point(139.0,0.,-73.0),12,3,-10));
   buildings.push_back(Building(Point(152.0,0.,-69.0),12,3,-10));
   buildings.push_back(Building(Point(165.0,0.,-70.0),12,3,-10));
   buildings.push_back(Building(Point(178.0,0.,-68.0),12,3,-10));
   buildings.push_back(Building(Point(190.0,0.,-65.0),12,3,-10));
   buildings.push_back(Building(Point(197.0,0.,-49.50),12,3,-10));
   buildings.push_back(Building(Point(178.0,0.,-68.0),12,3,-10));
   buildings.push_back(Building(Point(86.0,0.,-14.0),12,3,10));
   buildings.push_back(Building(Point(100.0,0.,-17.0),12,3,10));
   buildings.push_back(Building(Point(114.0,0.,-20.0),12,3,10));
   buildings.push_back(Building(Point(128.0,0.,-23.0),12,3,10));
   buildings.push_back(Building(Point(142.0,0.,-26.0),12,3,10));
   buildings.push_back(Building(Point(156.0,0.,-29.0),12,3,10));
   buildings.push_back(Building(Point(170.0,0.,-32.0),12,3,10));
   buildings.push_back(Building(Point(184.0,0.,-35.0),12,3,10));
   buildings.push_back(Building(Point(83.0,0.,-32.0),12,3,10));
   buildings.push_back(Building(Point(97.0,0.,-35.0),12,3,10));
   buildings.push_back(Building(Point(111.0,0.,-38.0),12,3,10));
   buildings.push_back(Building(Point(126.0,0.,-41.0),12,3,10));
   buildings.push_back(Building(Point(138.0,0.,-41.0),12,2,10));
   buildings.push_back(Building(Point(152.0,0.,-52.0),12,3,-10));
   buildings.push_back(Building(Point(165.0,0.,-50.0),12,3,-10));
   buildings.push_back(Building(Point(178.0,0.,-51.0),12,2,-10));
   buildings.push_back(Building(Point(81.0,0.,-53.0),12,3,15));
   buildings.push_back(Building(Point(98.0,0.,-53.0),12,3,15));
   buildings.push_back(Building(Point(111.0,0.,-58.0),12,3,-15));
   buildings.push_back(Building(Point(125.0,0.,-58.0),12,3,-10));
   buildings.push_back(Building(Point(139.0,0.,-53.0),12,3,-10));
   buildings.push_back(Building(Point(152.0,0.,-52.0),12,3,-10));
   buildings.push_back(Building(Point(165.0,0.,-50.0),12,3,-10));
   buildings.push_back(Building(Point(178.0,0.,-51.0),12,2,-10));

}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
   
   glLoadIdentity();                 // Reset the model-view matrix

   glTranslatef(0.0f, -1.0f, -10.0f); 
   glRotatef(5.0,1,0,0);

   ball->Draw();
   cam.Render();

   brasovMap.Draw();

	/*Building build1=Building(Point(1.35,0.,1.3),8,2);
	build1.Draw();	
	Building build2=Building(Point(5.2,0.,2.2),8,2);
	build2.Draw();*/
	
   //________________________1 _________________

   //________________________1 _________________

  
   
   for(int i=0;i<buildings.size();i++) {
	   buildings[i].Draw();
   }



    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}
void timer(int value) 
{
	glutPostRedisplay();
	glutTimerFunc(15, timer, 0);
	
	if (jump)
	{
		ball->Jump(jump);
	}
	if (left)
	{
		cam.MoveX(-SPEED); 
		ball->MoveX(-SPEED);
		
	}
	if (right)
	{
		cam.MoveX(SPEED); 
		ball->MoveX(SPEED);
		
	}
	if (up)
	{
		cam.MoveZ(-SPEED); 
		ball->MoveZ(SPEED);
		
	}
	if (down)
	{
		cam.MoveZ(SPEED); 
		ball->MoveZ(-SPEED);
		
	}
	if(rotLeft)
	{
		cam.RotateY(ROTATION);
	}
	if(rotRight)
	{
		cam.RotateY(-ROTATION);
	}
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 300.0f);
}

void keyboardPressed (unsigned char key, int x, int y)
{
	switch (key) 
	{
		//  case 'w':cam.RotateX(-5);break;
		//  case 's':cam.RotateX(5);break;
	case 'a':rotLeft=true; break;
	case 'd':rotRight=true; break;
	//case 'w':cam.RotateX(5);break;
	//case 's':cam.RotateX(-5);break;
	case ' ':jump=true; break;
	case 't':if(texNr==4)
				 texNr=0;
			 else
			     texNr++;
			 break;
	}
}
void keyboardReleased (unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 'a':rotLeft=false; break;
	case 'd':rotRight=false; break;
	}
}

void handleSpecialKeyPressed(int key, int x, int y)
{
	switch (key) 
	{
	case GLUT_KEY_LEFT:left = true; break;
	case GLUT_KEY_RIGHT:right = true; break;
	case GLUT_KEY_UP:up = true; break;
	case GLUT_KEY_DOWN:down = true; break;
	}
}
void handleSpecialKeyReleased(int key, int x, int y) 
{
	switch (key) 
	{
	case GLUT_KEY_LEFT:left = false; break;
	case GLUT_KEY_RIGHT:right = false; break;
	case GLUT_KEY_UP:up = false; break;
	case GLUT_KEY_DOWN:down = false; break;
	}
}
int main(int argc, char** argv) 
{
	try
	{
		glutInit(&argc, argv);            // Initialize GLUT
		glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
		glutInitWindowSize(640, 480);   // Set the window's initial width & height
		glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
		glutCreateWindow("Test");          // Create window with the given title
		glutDisplayFunc(display);       // Register callback handler for window re-paint event
		glutReshapeFunc(reshape);       // Register callback handler for window re-size event
		initGL();                       // Our own OpenGL initialization
		glutKeyboardFunc(keyboardPressed);
   		glutKeyboardUpFunc(keyboardReleased);
  		glutSpecialFunc(handleSpecialKeyPressed);
   		glutSpecialUpFunc(handleSpecialKeyReleased);
		glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
		glutMainLoop();                 // Enter the infinite event-processing loop
	}
	catch(char* message)
	{
		std::cout<<message<<"\n";
	}
	catch(...)
	{
		return -5;
	}
	return 0;
}