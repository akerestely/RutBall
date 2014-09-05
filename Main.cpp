#include <Windows.h>
#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "CameraSpectator.h"
#include "Tools.h"
#include "vector"
#include<map>
#include "Map.h"
CCamera cam;
std::map<int,Node> nodes;
Map brasovMap;
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix
   
   glTranslatef(0.0f, -1.5f, -7.0f);  // Move right and into the screen 
   //glTranslatef(-88.4f, -54.5f, 16.8f);
   //glRotatef(-85,1,0,0);
   cam.Render();
   glRotatef(180, 0, 1, 0); 
   brasovMap.Draw();
   glRotatef(-180, 0, 1, 0);
   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

void timer(int value) 
{
   glutPostRedisplay();
   glutTimerFunc(15, timer, 0);
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

float stepZ=0.5;
void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
	  case 'w':cam.RotateX(-5);break;
	  case 's':cam.RotateX(5);break;
	  case 'a':cam.RotateY(-5);break;
	  case 'd':cam.RotateY(5);break;
	  case 27: stepZ=1.5;break;
   }
}
/*void keyboardUp (unsigned char key, int x, int y)
{
 switch (key) {
	  case 27: stepZ=0.5;break;
   }
}
*/
void handleSpecialKeypress(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:  cam.MoveX(-0.3);  break;
	case GLUT_KEY_RIGHT: cam.MoveX(0.3); break;
	case GLUT_KEY_UP:    cam.MoveZ(-stepZ);  break;
	case GLUT_KEY_DOWN:  cam.MoveZ(stepZ); break; 
	}
}
int main(int argc, char** argv) {

	if (!Tools::ReadNodesFromXML("Map.xml", nodes))
	{
		return 0;
	}
	brasovMap = Map(nodes);
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow("Test");          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                       // Our own OpenGL initialization
   glutKeyboardFunc(keyboard);
   //glutKeyboardUpFunc(keyboardUp);
   glutSpecialFunc(handleSpecialKeypress);
   glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}