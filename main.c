#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

// all variables initialized to 1.0, meaning
// the triangle will initially be white
float red=1.0f, blue=1.0f, green=1.0f;

// angle for rotating triangle
float angle = 0.0f;
float x = 0;
float y = 0;
float z = 0;

float cameraX = 0;
float cameraY = 0;
float cameraZ = 10.0f;

void moveCamera(int key) {
	switch(key) {
		case GLUT_KEY_LEFT :
				cameraX -= 1;
				break;
		case GLUT_KEY_UP :
				cameraZ -= 1;
				break;
		case GLUT_KEY_RIGHT :
				cameraX += 1;
				break;
		case GLUT_KEY_DOWN :
				cameraZ += 1;
				break;
	}
	printf("Camera position: %f, %f, %f\n", cameraX, cameraY, cameraZ);
}

void processNormalKeys(unsigned char key, int x, int y) {
	// printf("GLUT_ACTIVE_ALT: %i\n", GLUT_ACTIVE_ALT);
	// printf("GLUT_ACTIVE_CTRL: %i\n", GLUT_ACTIVE_CTRL);
	// printf("GLUT_ACTIVE_SHIFT : %i\n", GLUT_ACTIVE_SHIFT );
	// printf("key : %c\n", key);
	// printf("keyValue : %i\n", key);
	// printf("mod: %i\n", glutGetModifiers());
	if (key == 27)
		exit(0);
	else if (key=='r') {
		int mod = glutGetModifiers();
		if (mod == GLUT_ACTIVE_ALT)
			red = 0.0;
		else
			red = 1.0;
	} else if (key=='e') {
		int mod = glutGetModifiers();
		printf("E PRESSED mod: %i\n", mod);
		if (mod == GLUT_ACTIVE_CTRL) {
			green = 0.0;
		}
		else
			green = 1.0;
	}
}

void processSpecialKeys(int key, int x, int y) {
	printf("GLUT_ACTIVE_ALT: %i\n", GLUT_ACTIVE_ALT);
	printf("GLUT_ACTIVE_CTRL: %i\n", GLUT_ACTIVE_CTRL);
	printf("GLUT_ACTIVE_SHIFT : %i\n", GLUT_ACTIVE_SHIFT );
	printf("key : %c\n", key);
	printf("keyValue : %i\n", key);
	printf("mod: %i\n", glutGetModifiers());
	switch(key) {
		case GLUT_KEY_F1 :
				red = 1.0;
				green = 0.0;
				blue = 0.0;
				break;
		case GLUT_KEY_F2 :
				red = 0.0;
				green = 1.0;
				blue = 0.0;
				break;
		case GLUT_KEY_F3 :
				red = 0.0;
				green = 0.0;
				blue = 1.0;
				break;
	}
	moveCamera(key);
}

void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the correct perspective.
    printf("RATIO: %f\n", ratio);
	gluPerspective(45, ratio, 1, 200);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
    printf("Resized\n");
}

void renderScene(void) {
	angle+=0.1f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(cameraX, cameraY, cameraZ,
			cameraX, cameraY,  cameraZ -10,
			0.0f, 1.0f,  0.0f);

	//glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glColor3f(red,green,blue);
	//z -= 0.01f;
    glBegin(GL_TRIANGLES);
    glVertex3f(-2 + x, -2 + y, 0 + z);
	glVertex3f(2 + x, 0.0 + y, 0 + z);
	glVertex3f(0.0 + x, 2 + y, 0 + z);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    printf("COUCOU\n");
    // init GLUT and create Window
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");
    // register callbacks
	glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
	// here is the idle func registration
	glutIdleFunc(renderScene);
	// here are the new entries
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// enter GLUT event processing cycle
	glutMainLoop();

    printf("FIN COUCOU\n");
    return(0);
}