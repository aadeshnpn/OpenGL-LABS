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
int main( int argc, char *argv[] )
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
glutInit(&argc, argv);
glutInitWindowPosition(100, 100);
glutInitWindowSize(win_width, win_height);
window_id = glutCreateWindow(argv[0]);
//glGetString(GL_VERSION)
printf("%sn", glGetString(GL_VERSION));
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
int height = glutGet(GLUT_WINDOW_HEIGHT);
glViewport(0, 0, width, height);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0, width, 0, height, -1, 1);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glEnable(GL_DEPTH_TEST);
glDisable(GL_LIGHTING);
//
// Draw Code can go here
//
glBegin(GL_LINES);
glColor3f(1.0, 0.0, 0.0);
glVertex2f(100, 100); // first line
glVertex2f(300, 300);
glVertex2f(150,10); // second line
glVertex2f(10,150);
glEnd();
//
// Draw code should be completed by this point
//
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
