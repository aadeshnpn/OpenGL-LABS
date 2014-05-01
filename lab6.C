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
//]
void idle(void);
void display(void);
void keyboard(unsigned char key,int x,int y);
int window_id;
int win_width = 800, win_height = 600;
// the locally define location of our triangle
static float v0_local[3], v1_local[3], v2_local[3];

// the actual location of our triangle
static float v0[3], v1[3], v2[3]; 

GLfloat light_pos[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat red_diffuse_material[] = { 0.8, 0.2, 0.2, 1.0 }; // red matte
GLfloat red_specular_material[] = { 0.8, 0.2, 0.2, 1.0 }; // red shine
GLfloat shininess[] = { 50.0 };
//vec3 eye; // The (regularly updated) vector coordinates of the eye location 
//vec3 up; 
//vec3 center;
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
v0_local[0] = -10;
v0_local[1] = 0;
v1_local[0] = 10;
v1_local[1] = 0;
v2_local[0] = 0;
v2_local[1] = 10;
v0_local[2] = -2.0;
v1_local[2] = -2.0;
v2_local[2] = -2.0;
glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
glutInit(&argc, argv);
glutInitWindowPosition(100, 100);
glutInitWindowSize(win_width, win_height);
window_id = glutCreateWindow(argv[0]);
//glGetString(GL_VERSION)
printf("%sn", glGetString(GL_VERSION));
glutDisplayFunc(display);
glutKeyboardFunc(keyboard);
glutIdleFunc(idle);
glutMainLoop();
return 0;
}
void display(void)
{
glClearColor(0, 0, 0, 1.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
int width = glutGet(GLUT_WINDOW_WIDTH);
int height = glutGet(GLUT_WINDOW_HEIGHT);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum( -width/2.0, width/2.0, -height/2.0, height/2.0, -1.0, -200.0 );
//glOrtho(0, width, 0, height, -1, 1);
//gluPerspective( field_of_view, aspect, near, far ); //field of view (in degrees) in the Y (up) direction, 
//the aspect ratio (width over height), the near plane, and the far plane.
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
gluPerspective(45,float(width)/float(height),1,100); //Default for solid GLU objects
//gluLookAt(0,0,0,0,0,-1,0,1,0);
glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
glEnable(GL_LIGHT0);
glEnable(GL_LIGHTING);
glViewport(0, 0, width, height);
glEnable(GL_DEPTH_TEST);
//eye=(0, 0, 0);
//center = (0, 0, -1);
//up = (0, 1, 0);
//gluLookAt( eyeX, eyeY, eyeZ,
//               centerX, centerY, centerZ,
//               upX, upY, upZ ); 
//
//gluLookAt(0,0,0,0,0,-100,0,1,0); //For viewing traingles

// Draw Code can go here
//
//glutWireTorus(innerRadius, outerRadius, nsides, rings)
glColor3f(1.0, 0.0, 0.0); // makes the current color red
glPushMatrix(); // pushes the current matrix stack down and makes a copy on top
glMaterialfv(GL_FRONT, GL_DIFFUSE, red_diffuse_material);
glMaterialfv(GL_FRONT, GL_SPECULAR, red_specular_material);
glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
glTranslatef(-5, 20, -100); // multiplies the top of stack with trans matri
glutSolidTorus(20, 30, 20, 20); // creates a wire cone using current matrix
//glutSolidSphere(30,20,20);
//glutWireSphere (blue): translate=(20, -20, -200);
//glutWireTorus (green): translate=(-20,-40,-150), rotate1=(23.6, 0,1,0), rotate2=(68, 1,0,0);
glPopMatrix();
/*glBegin(GL_TRIANGLES);
	glColor3f(0.0, 1.0, 0.0);
	//glVertex3f(100, 100,0); // first line
	//glVertex3f(100, 200,0);
	//glVertex3f(200,200,0);
	//glVertex3f(200,100,0); // second line
	glVertex3f(v0[0], v0[1],v0[2]); // first line
	glVertex3f(v0[1], v1[1],v2[1]);  // first line
	glVertex3f(v0[2], v1[2],v2[2]); 
	//glVertex3f(v2[0], v2[1],v2[2]); // first line
	//glVertex3f(v2[0], v2[1],v2[2]);
	//glVertex3f(v0[0], v0[1],v0[2]);
glEnd();*/
//
// Draw code should be completed by this point
//
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

	float translation[3];
	translation[0] = cos(ang) * radius;
	translation[1] = sin(ang) * radius;
	translation[2] = sin(ang) * sin(ang);

	// translate the locally defined vertices with our translation vector
	v0[0] = v0_local[0] + translation[0];
	v0[1] = v0_local[1] + translation[1];
	v0[2] = v0_local[2] + translation[2];
	
	v1[0] = v1_local[0] + translation[0];
	v1[1] = v1_local[1] + translation[1];
	v1[2] = v1_local[2] + translation[2];
	
	v2[0] = v2_local[0] + translation[0];
	v2[1] = v2_local[1] + translation[1];
	v2[2] = v2_local[2] + translation[2];

	// now, update the angle with some small increment
	ang += 0.0005;
	if (ang >= 2*M_PI) ang = 0.0;
		glutPostRedisplay();
	}

