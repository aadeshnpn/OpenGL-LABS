#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#define GL3_PROTOTYPES 1

void idle(void);
void display(void);
void keyboard(unsigned char key,int x,int y);
int window_id;
int win_width = 600, win_height = 600;
// the locally define location of our triangle
static float v0_local[2], v1_local[2], v2_local[2];

// the actual location of our triangle
static float v0[2], v1[2], v2[2]; 

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
v0_local[0] = -10;
v0_local[1] = 0;
v1_local[0] = 10;
v1_local[1] = 0;
v2_local[0] = 0;
v2_local[1] = 10;
glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
glutInit(&argc,argv);
glutInitWindowPosition(100, 100);
glutInitWindowSize(win_width, win_height);
window_id = glutCreateWindow(argv[0]);
//glGetString(GL_VERSION)
printf("%s\n", glGetString(GL_VERSION));
glutDisplayFunc(display);
glutKeyboardFunc(keyboard);
glutIdleFunc(idle);
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
glOrtho(0, width, 0, height, -400, 400);
//glOrtho(-width,width,-height,height,-400,400);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glEnable(GL_DEPTH_TEST);
glDisable(GL_LIGHTING);
printf("The values are %g\t%g\t%g\n",v0[0],v0[1],v0[2]);
glBegin(GL_TRIANGLES);
	glColor3f(0.0, 1.0, 0.0);
	//glVertex3f(100, 100,0); // first line
	//glVertex3f(100, 200,0);
	//glVertex3f(200,200,0);
	//glVertex3f(200,100,0); // second line
	glVertex3f(v0[0], v1[0],v2[0]); // first line
	glVertex3f(v0[1], v1[1],v2[1]);  // first line
	glVertex3f(v0[2], v1[2],v2[2]); 
	//glVertex3f(v2[0], v2[1],v2[2]); // first line
	//glVertex3f(v2[0], v2[1],v2[2]);
	//glVertex3f(v0[0], v0[1],v0[2]);
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

void idle(void){
	static float ang = 0.0;
	float radius = 100.0;
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	float translation[2];
	translation[0] = width/2.0 + cos(ang) * radius;
	translation[1] = height/2.0 + sin(ang) * radius;

	// translate the locally defined vertices with our translation vector
	v0[0] = v0_local[0] + translation[0];
	v0[1] = v0_local[1] + translation[1];

	v1[0] = v1_local[0] + translation[0];
	v1[1] = v1_local[1] + translation[1];

	v2[0] = v2_local[0] + translation[0];
	v2[1] = v2_local[1] + translation[1];

	// now, update the angle with some small increment
	ang += 0.0005;
	if (ang >= 2*M_PI) ang = 0.0;
		glutPostRedisplay();
	}

