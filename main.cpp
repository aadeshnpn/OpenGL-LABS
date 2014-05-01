//@author: Aadesh Neupane, Rajesh Twanabase
//@Mini-project: COMP 411 (Computer Graphics)
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
//#include "shaders.h"
//#include "Transform.h"
#include <string>
#include <sstream>
#include "glm.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ; 

int amount;
int w=500,h=500;
vec3 eye;
vec3 up;
const vec3 eyeinit(0.0,0.0,2.0); // Initial eye position, also for resets(0.0,0.0,5.0)
const vec3 upinit(0.0,1.0,0.0); // Initial up position, also for resets(0.0,1.0,0.0);
const int amountinit = 5; //Initial step amount for camera movement, also for resets



static void left(float degrees, vec3& eye, vec3& up);
static void up1(float degrees, vec3& eye, vec3& up);
static mat4 lookAt(vec3 eye, vec3 up);
static mat3 rotate(const float degrees, const vec3& axis) ;
const float pi = 3.14159265 ; // For portability across platforms
class Transform  
{
	public:
		Transform();
		virtual ~Transform();
		static void left(float degrees, vec3& eye, vec3& up);
		static void up1(float degrees, vec3& eye, vec3& up);
		static mat4 lookAt(vec3 eye, vec3 up);
		static mat3 rotate(const float degrees, const vec3& axis) ;
};

mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
  mat3 rotate;

  //float degrees1=degrees;
  //vec3 x_axis(1,0,0);
  //vec3 y_axis(0,1,0);
  /*
  if(axis==x_axis){
  rotate_x[0][0]=1; rotate_x[0][1]=0; rotate_x[0][2]=0; 
  rotate_x[1][0]=0; rotate_x[1][1]= cos(degrees1*pi/180); rotate_x[1][2]=-sin(degrees1*pi/180); 
  rotate_x[2][0]=0; rotate_x[2][1]= sin(degrees1*pi/180); rotate_x[2][2]=cos(degrees1*pi/180); 

  rotate_x= glm::transpose(rotate_x);
  // You will change this return call
  return rotate_x;
  }
  else if(axis==y_axis){
  rotate_x[0][0]=cos(degrees1*pi/180); rotate_x[0][1]=0; rotate_x[0][2]=sin(degrees1*pi/180); 
  rotate_x[1][0]=0; rotate_x[1][1]= 1; rotate_x[1][2]=0; 
  rotate_x[2][0]=-sin(degrees1*pi/180); rotate_x[2][1]= 0; rotate_x[2][2]=cos(degrees1*pi/180); 

  rotate_x= glm::transpose(rotate_x);
  // You will change this return call
  return rotate_x;
  }*/

  mat3 I;
  I[0][0]=1; I[0][1]= 0; I[0][2]=0;  
  I[1][0]=0; I[1][1]= 1; I[1][2]=0;
  I[2][0]=0; I[2][1]= 0; I[2][2]=1;
  
  mat3 A1;
  A1[0][0]=axis.x*axis.x; A1[0][1]= axis.x*axis.y; A1[0][2]=axis.x*axis.z;  
  A1[1][0]=axis.x*axis.y; A1[1][1]= axis.y*axis.y; A1[1][2]=axis.y*axis.z;
  A1[2][0]=axis.x*axis.z; A1[2][1]= axis.y*axis.z; A1[2][2]=axis.z*axis.z;

  mat3 A0;
  A0[0][0]=0; A0[0][1]= -axis.z; A0[0][2]=axis.y;  
  A0[1][0]=axis.z; A0[1][1]= 0; A0[1][2]=-axis.x;
  A0[2][0]=-axis.y; A0[2][1]= axis.x; A0[2][2]=0;

  rotate=cos(degrees*pi/180)*I+(1-cos(degrees*pi/180))*A1+sin(degrees*pi/180)*A0;

  return rotate;

}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
  vec3 axis=-up;
  axis=glm::normalize(axis);
   mat3 rotate_left;
   rotate_left=rotate(degrees, axis);
  //TODO
   mat4 move;
   mat4 rotate;
   
   
   vec4 eye4(eye.x,eye.y,eye.z,1);  

  move[0][0]=1; move[0][1]= 0; move[0][2]=0; move[0][3]=eye.x; 
  move[1][0]=0; move[1][1]= 1; move[1][2]=0; move[1][3]=eye.y;
  move[2][0]=0; move[2][1]= 0; move[2][2]=1; move[2][3]=eye.z; 
  move[3][0]=0; move[3][1]= 0; move[3][2]=0; move[3][3]=1;  
  
   rotate[0][0]=rotate_left[0][0]; rotate[0][1]= rotate_left[0][1]; rotate[0][2]=rotate_left[0][2]; rotate[0][3]=0; 
   rotate[1][0]=rotate_left[1][0]; rotate[1][1]= rotate_left[1][1]; rotate[1][2]=rotate_left[1][2]; rotate[1][3]=0;
   rotate[2][0]=rotate_left[2][0]; rotate[2][1]= rotate_left[2][1]; rotate[2][2]=rotate_left[2][2]; rotate[2][3]=0; 
   rotate[3][0]=0; rotate[3][1]= 0; rotate[3][2]=0; rotate[3][3]=1; 
   
   eye=rotate_left*eye;

   //eye.x=eye4.x;
   //eye.y=eye4.y;
   //eye.z=eye4.z;
   up=rotate_left*up;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up1(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
   vec3 axis=glm::cross(up,eye);
    
   axis=glm::normalize(axis);
   mat3 rotate_up;
   rotate_up=rotate(degrees, axis);

   mat4 rotate;
   mat4 move;
   vec4 eye4(eye.x,eye.y,eye.z,1); 

   rotate[0][0]=rotate_up[0][0]; rotate[0][1]= rotate_up[0][1]; rotate[0][2]=rotate_up[0][2]; rotate[0][3]=0; 
   rotate[1][0]=rotate_up[1][0]; rotate[1][1]= rotate_up[1][1]; rotate[1][2]=rotate_up[1][2]; rotate[1][3]=0;
   rotate[2][0]=rotate_up[2][0]; rotate[2][1]= rotate_up[2][1]; rotate[2][2]=rotate_up[2][2]; rotate[2][3]=0; 
   rotate[3][0]=0; rotate[3][1]= 0; rotate[3][2]=0; rotate[3][3]=1; 
  // for(int i=0;i<3; i++)
   // for(int j=0; j<3;j++)
     // std::cout<<rotate_up[i][j];
  //TODO

  move[0][0]=1; move[0][1]= 0; move[0][2]=0; move[0][3]=eye.x; 
  move[1][0]=0; move[1][1]= 1; move[1][2]=0; move[1][3]=eye.y;
  move[2][0]=0; move[2][1]= 0; move[2][2]=1; move[2][3]=eye.z; 
  move[3][0]=0; move[3][1]= 0; move[3][2]=0; move[3][3]=1; 

   eye=rotate_up*eye;
   up=rotate_up*up;
   //eye.x=eye4.x;
   //eye.y=eye4.y;
   //eye.z=eye4.z;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE
  vec3 w;  
  vec3 u;
  vec3 v;
  vec3 center(0,0,0);

  vec3 eye_normalize = glm::normalize(eye);
  w=eye_normalize;
  
  vec3 temp=glm::cross(up,w);
  temp = glm::normalize(temp);

  u=temp;
  v = glm::cross(w,u);

  mat4 lookat;
  lookat[0][0]=1; lookat[0][1]= 0; lookat[0][2]=0; lookat[0][3]=-eye.x; 
  lookat[1][0]=0; lookat[1][1]= 1; lookat[1][2]=0; lookat[1][3]=-eye.y;
  lookat[2][0]=0; lookat[2][1]= 0; lookat[2][2]=1; lookat[2][3]=-eye.z; 
  lookat[3][0]=0; lookat[3][1]= 0; lookat[3][2]=0; lookat[3][3]=1;  
  
  lookat= glm::transpose(lookat);

  mat4 coordinate_frame;

  coordinate_frame[0][0]=u.x; coordinate_frame[0][1]= u.y; coordinate_frame[0][2]=u.z; coordinate_frame[0][3]=0; 
  coordinate_frame[1][0]=v.x; coordinate_frame[1][1]= v.y; coordinate_frame[1][2]=v.z; coordinate_frame[1][3]=0;
  coordinate_frame[2][0]=w.x; coordinate_frame[2][1]= w.y; coordinate_frame[2][2]=w.z; coordinate_frame[2][3]=0; 
  coordinate_frame[3][0]=0;   coordinate_frame[3][1]= 0;   coordinate_frame[3][2]=0;   coordinate_frame[3][3]=1;  

  coordinate_frame= glm::transpose(coordinate_frame);

  lookat=coordinate_frame*lookat;

  // You will change this return call
  return lookat;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}


//#include <FreeImage.h>
//s#include "UCB/grader.h"


// Constants to set up lighting on the teapot
const GLfloat light_position[] = {0,5,10,1};    // Position of light 0
const GLfloat light_position1[] = {0,5,-10,1};  // Position of light 1
const GLfloat light_specular[] = {0.6,0.3,0,1};    // Specular of light 0
const GLfloat light_specular1[] = {0,0.3,0.6,1};   // Specular of light 1
const GLfloat one[] = {1,1,1,1};                 // Specular on teapot
const GLfloat medium[] = {0.5,0.5,0.5,1};        // Diffuse on teapot
const GLfloat small[] = {0.2,0.2,0.2,1};         // Ambient on teapot
const GLfloat high[] = {100};                      // Shininess of teapot
GLfloat light0[4],light1[4]; 

GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat red_diffuse_material[] = { 0.8, 0.2, 0.2, 1.0 }; // red matte
GLfloat red_specular_material[] = { 0.8, 0.2, 0.2, 1.0 }; // red shine
GLfloat shininess[] = { 50.0 };
// Variables to set uniform params for lighting fragment shader 
GLuint islight; 
GLuint light0posn; 
GLuint light0color; 
GLuint light1posn; 
GLuint light1color; 
GLuint ambient; 
GLuint diffuse; 
GLuint specular; 
//GLuint shininess; 
GLMmodel *objmodel_ptr;

void transformvec (const GLfloat input[4],GLfloat output[4]) {
	GLfloat modelview[16]; // in column major order
	glGetFloatv(GL_MODELVIEW_MATRIX,modelview); 

	for (int i = 0; i < 4; i++) {
		output[i] = 0; 
		for (int j = 0; j < 4; j++) 
			output[i] += modelview[4*j+i] * input[j]; 
	}
}

std::string imgNumber(int num) {
	std::stringstream ss;
	//Return 3-digit number (or more if num > 999, but this case shouldn't be encountered)
	if(num < 10) {
		ss << "00" << num;
	} else if(num < 100) {
		ss << "0" << num;
	} else {
		ss << num;
	}
	return ss.str();
}

void printHelp() {
	std::cout << "\npress 'h' to print this message again.\n" 
		//<< "press '+' or '-' to change the amount of rotation that\n"
		//<< "occurs with each arrow press.\n" 
		//<< "press 'i' to run image grader test cases\n"
		//<< "press 'g' to switch between using glm::lookAt or your own LookAt.\n"     
		<< "press 'r' to reset the transformation (eye and up).\n"
		<< "press ESC to quit.\n";  

}

void keyboard(unsigned char key,int x,int y) {
	switch(key) {
		//case '+':
		//	amount++;
		//	std::cout << "amount set to " << amount << "\n";
		//	break;
		//case '-':
		//	amount--;
		//	std::cout << "amount set to " << amount << "\n"; 
		//	break;
		/*case 'i':
			if(useGlu) {
				std::cout << "Please disable glm::LookAt by pressing 'g'"
					   << " before running tests\n";
			}
			else if(!allowGrader) {
				std::cout << "Error: no input file specified for grader\n";
			} else {
				std::cout << "Running tests...\n";
				grader.runTests();
				std::cout << "Done! [ESC to quit]\n";
			}
			break;
		case 'g':
			useGlu = !useGlu;
			std::cout << "Using glm::LookAt set to: " 
				<< (useGlu ? " true " : " false ") << "\n"; 
			break;
		*/	
		case 'h':
			printHelp();
			break;
		case 27:  // Escape to quit
			exit(0);
			break;
		case 'r': // reset eye and up vectors 
			eye = eyeinit; 
			up = upinit; 
			amount = amountinit;
			std::cout << "eye and up vectors reset, amount set to " << amountinit << "\n";
			break;                 
	}
	glutPostRedisplay();
}

void specialKey(int key,int x,int y) {
	switch(key) {
		case 100: //left
			Transform::left(amount,eye,up);
			break;
		case 101: //up
			Transform::up1(amount,eye,up);
			break;
		case 102: //right
			Transform::left(-amount,eye,up);
			break;
		case 103: //down
			Transform::up1(-amount,eye,up);
			break;
	}
	glutPostRedisplay();
}


void reshape(int width,int height){
	w = width;
	h = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,w/(float)h,0.1,99);
	glViewport(0,0,w,h);
}

void init() {

	// Set up initial position for eye,up and amount
	// As well as booleans 

	eye = eyeinit; 
	up = upinit; 
	amount = amountinit;
	//useGlu = true;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

}

void display() {
	glClearColor(0,0,1,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	mat4 mv; 
	const vec3 center(0.0,0.0,0.0); 

	//if (useGlu) mv = glm::lookAt(eye,center,up); 
	//else {
		mv = Transform::lookAt(eye,up); 
	//}
	glLoadMatrixf(&mv[0][0]); 

	// Set Light and Material properties for the teapot
	// Lights are transformed by current modelview matrix. 
	// The shader can't do this globally. 
	// So we need to do so manually.  
	transformvec(light_position,light0); 
	transformvec(light_position1,light1); 
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	/*glUniform4fv(light0posn,1,light0); 
	glUniform4fv(light0color,1,light_specular); 
	glUniform4fv(light1posn,1,light1); 
	glUniform4fv(light1color,1,light_specular1); 

	//glUniform4fv(ambient,1,small); 
	//glUniform4fv(diffuse,1,medium); 
	glUniform4fv(ambient,1,small); 
	glUniform4fv(diffuse,1,small); 
	glUniform4fv(specular,1,one); 
	glUniform1fv(shininess,1,high); 
	glUniform1i(islight,true);
	*/
	//glutSolidTeapot(3);
	if (!objmodel_ptr)
	{
	   objmodel_ptr = glmReadOBJ("dragon.obj");
	   if (!objmodel_ptr)
	       exit(0);
	
	   glmUnitize(objmodel_ptr);
	   glmFacetNormals(objmodel_ptr);
	   glmVertexNormals(objmodel_ptr, 90.0);

	}
	
	glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL);

	glutSwapBuffers();
}

int main(int argc,char* argv[]) {
	
	//Initialize GLUT
	//FreeImage_Initialise();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Mini-project: Transformations");
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(specialKey);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutReshapeWindow(w,h);
	
	/*if(argc > 1) {
		allowGrader = true;
		grader.init(argv[1]);
		grader.loadCommands(argv[1]);
		grader.bindDisplayFunc(display);
		grader.bindSpecialFunc(specialKey);
		grader.bindKeyboardFunc(keyboard);
		grader.bindScreenshotFunc(saveScreenshot);
	}
	*/
	printHelp();
	glutMainLoop();	
	//FreeImage_DeInitialise();

	return 0;
}
