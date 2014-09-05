#include <Windows.h>
#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "CameraSpectator.h"
#include "Tools.h"
#include "vector"
#include "Ball.h"
CCamera cam;
Ball *ball;

std::vector<Node> nodes;
bool up,down,left,right,rotLeft,rotRight, jump;


void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling   
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	ball=new Ball(1,Point(0,0,0));
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
   
   glLoadIdentity();                 // Reset the model-view matrix

   glTranslatef(0.0f, -1.0f, -10.0f);  // Move right and into the screen 
   glRotatef(30.,1,0,0);

   ball->Draw();
   cam.Render();

   //glRotatef(180, 0, 1, 0); 
   //for (int i = 0; i < nodes.size(); i++)
   //{
	  // nodes[i].Draw();
   //}	
   //glRotatef(-180, 0, 1, 0);

   glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
	// Front
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f( 0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Right
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Back
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// Left
	glColor3f(1.0f,0.0f,0.0f);       // Red
	glVertex3f( 0.0f, 1.0f, 0.0f);
	glColor3f(0.0f,0.0f,1.0f);       // Blue
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glColor3f(0.0f,1.0f,0.0f);       // Green
	glVertex3f(-1.0f,-1.0f, 1.0f);
	glEnd();   // Done drawing the pyramid

    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
  //  glFlush();
}

void timer(int value) 
{
	glutPostRedisplay();
	glutTimerFunc(15, timer, 0);
	if(left)
	{
		cam.MoveX(-0.2); 
		ball->MoveX(-0.2);
	}
	if(right)
	{
		cam.MoveX(0.2); 
		ball->MoveX(0.2);
	}
	if(up)
	{
		cam.MoveZ(-0.2); 
		ball->MoveZ(0.2);
	}
	if(down)
	{
		cam.MoveZ(0.2);
		ball->MoveZ(-0.2);
	}
	if(rotLeft)
	{
		cam.RotateY(5);
		ball->RotateY(-5);
	}
	if(rotRight)
	{
		cam.RotateY(-5);
		ball->RotateY(5);
	}
	if(jump)
		ball->Jump(1);
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
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void keyboardPressed (unsigned char key, int x, int y)
{
	switch (key) 
	{
		//  case 'w':cam.RotateX(-5);break;
		//  case 's':cam.RotateX(5);break;
	case 'a':rotLeft=true; break;
	case 'd':rotRight=true; break;
	case ' ':jump=true; break;
	}
}
void keyboardReleased (unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 'a':rotLeft=false; break;
	case 'd':rotRight=false; break;
	case ' ':jump=false; break;
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
int main(int argc, char** argv) {

	if (!Tools::ReadNodesFromXML("Map.xml", nodes))
	{
		return 0;
	}
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
   return 0;
}