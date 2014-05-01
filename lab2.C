#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#define GL3_PROTOTYPES 1
//
// compilation instructions
//
// OS X
//
// g++ -Wall -O3 -o opengl_sample main.cpp -framework GLUT -framework OpenGL -framework Foundation
//
// Linux
//
// g++ hello.C -lglut -lGL
//
void display(void);
void keyboard(unsigned char key,int x,int y);
int window_id;
int win_width = 500, win_height = 500;
int main( int argc, char* argv[] )
{
//
// arguments to main are width and height of window if on console
//
if (argc == 3)
{
win_width = atoi( argv[1] );
win_height = atoi( argv[2] );
}
glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
glutInit(&argc,argv);
glutInitWindowPosition(100, 100);
glutInitWindowSize(win_width, win_height);
window_id = glutCreateWindow(argv[0]);
//glGetString(GL_VERSION)
printf("%s\n", glGetString(GL_VERSION));
glutDisplayFunc(display);
glutKeyboardFunc(keyboard);
glutMainLoop();
return 0;
}
void display(void)
{
glClearColor(1, 1, 1, 1.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
int width = glutGet(GLUT_WINDOW_WIDTH);
int i;
int height = glutGet(GLUT_WINDOW_HEIGHT);
glViewport(0, 0, width, height);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0, width, 0, height, -10, 10);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glEnable(GL_DEPTH_TEST);
glDisable(GL_LIGHTING);
//
// Draw Code can go here
//
/*
glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(100, 100); // first line
	glVertex2f(300, 300);
	glVertex2f(150,10); // second line
	glVertex2f(10,150);
glEnd();
*/
//Making square using traingle strip
/*glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(100, 100); // first line
	glVertex2f(100, 200);
	glVertex2f(200,200);
	glVertex2f(200,100); // second line
	glVertex2f(100,100);
glEnd();*/
/*
glBegin(GL_POINTS);
	GLfloat sizeP=90.0000;
	glColor3f(0.0,1.0,0.0);
	glPointSize(4.0);
	for(i=100;i<200;i++)
		{glPointSize(sizeP);
		glVertex2f(i,150);}
	//glVertex2f(1,150);
glEnd();
* /
/*
glBegin(GL_QUAD_STRIP);
	glColor3f(1.0,0.0,1.0);
	glVertex2f(100, 100); // first line
	glVertex2f(100, 200);
	glVertex2f(200,300);
	glVertex2f(300,400);
	glVertex2f(400,300);
	glVertex2f(300,200);
	glVertex2f(200,100);
	glVertex2f(100,100); // second line
	//glVertex2f(100,100);
glEnd();
*/ 
//
// Draw code should be completed by this point
//

int mesh_width=100;
int mesh_height=100;

float mesh_scale=50.0;
float mesh_trans[2];
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
mesh_trans[0]=-((mesh_width-1)/2.0)*mesh_scale;
mesh_trans[1]=-((mesh_height-1)/2.0)*mesh_scale;
glColor3f(1.0,0.0,0.0);
glBegin(GL_LINES);
float v[3];
int row,col;
for (row=20; row<mesh_height-1; row++)
for (col=20; col<mesh_width-1; col++)
{
v[0] = (col * mesh_scale) + mesh_trans[0]; // X
v[1] = (row * mesh_scale) + mesh_trans[1]; // Y
glVertex2f(v[0], v[1]);

v[0] = (col * mesh_scale) + mesh_trans[0]; // X
v[1] = ((row+1) * mesh_scale) + mesh_trans[1]; // Y
glVertex2f(v[0], v[1]);

v[0] = ((col+1) * mesh_scale) + mesh_trans[0]; // X
v[1] = ((row+1) * mesh_scale) + mesh_trans[1]; // Y
glVertex2f(v[0], v[1]);

// second triangle
v[0] = ((col+1) * mesh_scale) + mesh_trans[0]; // X
v[1] = ((row+1) * mesh_scale) + mesh_trans[1]; // Y
glVertex2f(v[0], v[1]);

v[0] = (col * mesh_scale) + mesh_trans[0]; // X
v[1] = (row * mesh_scale) + mesh_trans[1]; // Y
glVertex2f(v[0], v[1]);

v[0] = ((col+1) * mesh_scale) + mesh_trans[0]; // X
v[1] = (row * mesh_scale) + mesh_trans[1]; // Y
glVertex2f(v[0], v[1]);

}
glEnd();
glutSwapBuffers();
}
void keyboard(unsigned char key,int x,int y)
{
if (key==27) // the escape key
{
glutDestroyWindow(window_id);
exit(0);
}
}
