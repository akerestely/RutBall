#include <Windows.h>
#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "CameraSpectator.h"
#include "Tools.h"
#include "vector"
#include "Building.h"
CCamera cam;
std::vector<Node> nodes;
void initGL() {

   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_BLEND);
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void display(void)
{
  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	// Render a color-cube consisting of 6 quads with different colors
	glLoadIdentity();                 // Reset the model-view matrix
	glTranslatef(0.f, 10.0f, -7.0f);  // Move right and into the screen
	glRotated(30,1.,0,0);
	cam.Render();
	glTranslatef(0.f, -10, 0);  // Move right and into the screen

	//_____________________

	glBegin(GL_QUADS);        
	 glColor3f(1.0f, 1.0f, 1.0f);     // Green
	  glVertex3f( -100., 0., -100.);
	  glVertex3f(-100.,0.,100.);
	  glVertex3f(100.,0.,100.);
	  glVertex3f( 100.,0.,-100.);

	  glEnd();



//_______________________




   glBindTexture(GL_TEXTURE_2D, texName);
	Building build1=Building(Point(1.35,0.,1.3),2,2);
	build1.Draw();
	//glTranslatef(3.f, 0.0f, 0.0f);
	


	//glTranslatef(3.f, 0.0f, 0.0f);
	glutSwapBuffers();  // Swap the front and qback frame buffers (double buffering)

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
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
	  case 'w':cam.RotateX(-5);break;
	  case 's':cam.RotateX(5);break;
	  case 'a':cam.RotateY(-5);break;
	  case 'd':cam.RotateY(5);break;
   }
}

void handleSpecialKeypress(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:  cam.MoveX(-0.3);  break;
	case GLUT_KEY_RIGHT: cam.MoveX(0.3); break;
	case GLUT_KEY_UP:    cam.MoveZ(-0.2);  break;
	case GLUT_KEY_DOWN:  cam.MoveZ(0.2); break; 
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
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(handleSpecialKeypress);
   glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}