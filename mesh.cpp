#include <iostream>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <time.h>
#include <stdlib.h>
#include "mesh.h"

//
// Mesh Definitions
//
Mesh::Mesh(const int w, const int h)
  : m_data(0), m_indices(0), m_width(w), m_height(h),m_color(0)
{
  m_num_triangles = (m_width-1)*(m_height-1)*2;

  float mesh_scale = 10.0;
  float mesh_trans[2];
  mesh_trans[0] = -((m_width-1)/2.0)*mesh_scale;
  mesh_trans[1] = -((m_height-1)/2.0)*mesh_scale;

  // number of vertices in a triangle with storage for X,Y,Z tuple
  m_data = new GLfloat[ m_num_triangles*3*3 ];  
  m_color= new GLfloat[ m_num_triangles*3*3 ];  

  // Each triangle has 3 vertices, and for each one we store an index
  // into the data vertex array, never more than num_triangles * 3.
  // Should change to reflect the drawing type.
  m_indices = new GLuint[ m_num_triangles*3 ];    

  std::cout << "Mesh Dim(" << m_width << " by " << m_height << "), Num Tris: " << m_num_triangles << ", Mesh scale = " << mesh_scale << ", trans = " << mesh_trans[0] << ", " << mesh_trans[1] << std::endl;

  // Generate the coordinates of the vertices
  int idx, n=1;
  int row, col;
  for (row=0; row<m_height; row++)
    for (col=0; col<m_width; col++)
      {
	idx = (m_width*row*3) + col*3;

	m_data[idx] = (col * mesh_scale) + mesh_trans[0];   // X
	m_color[idx]=rand()%2;
	m_data[idx+1] = (row * mesh_scale) + mesh_trans[1]; // Y
	m_color[idx+1]=rand()%2;
	m_data[idx+2] = 0.0;   // Z
	m_color[idx+2]=rand()%2;
	n++;
      }

  genTriangleIndices();
}

void Mesh::genTriangleIndices(void)
{
  //
  // generates the indices of the triangles for drawing all of the
  // triangles as separate triangles
  //
  int row, col;
  int idx_count = 0;
  int idx, idx_over, idx_above, idx_above_over;
  for (row=0; row<m_height-1; row++)
    for (col=0; col<m_width-1; col++)
      {
	idx = (m_width*row) + col;
	idx_over = (m_width*row) + col + 1;
	idx_above = (m_width*(row+1)) + col;
	idx_above_over = (m_width*(row+1)) + col + 1;
	
	m_indices[idx_count++] = idx;
	m_indices[idx_count++] = idx_above;
	m_indices[idx_count++] = idx_above_over;
	
	m_indices[idx_count++] = idx_above_over;
	m_indices[idx_count++] = idx;
	m_indices[idx_count++] = idx_over;
      }
}

void Mesh::initialize( void )
{
  // query the OpenGL driver about the maximum number of vertices
  // recommended for a vertex array and the recommended maximum for
  // number of indices.
  glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &m_max_vertices);
  glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &m_max_indices);

  // may need to tailor this code to take the above two values into
  // account... creating multiple vertex arrays to easily fit into the
  // drivers (and card's) caches.
  std::cout << "Recommended maximum number of vertex array vertices: " << m_max_vertices << std::endl;
  std::cout << "Recommended maximum number of vertex array indices: " << m_max_indices << std::endl;

  // enable the client state for the vertex array and set the pointer
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, m_data);
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, m_color);
}

void Mesh::render( void )
{
  // Render as LINES to see the mesh.  Comment out this line to render as full triangles.
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
  
  // glDrawElements renders primitives from array data with the first
  // arg being the primitive mode (such as points, tris, etc...), and
  // the second arg being the number of "elements" to be rendered.
  // Elements refers to the number of indices to utilize. So, for
  // triangles, this is essentially the number of triangles multiplied
  // by the number of vertices.  For tristrips, the number will be
  // less. The third and fourth arg referring to the type of values in
  // the indice array and the indice array, respectively.

  // Draw the triangles using indices into the data array...
  glColor3f(0.0, 1.0, 0.0);
  glDrawElements(GL_TRIANGLES, m_num_triangles*3, GL_UNSIGNED_INT, m_indices);
}

Mesh::~Mesh()
{
  delete [] m_data;
  delete [] m_indices;
}


void display(void);
void keyboard(unsigned char key,int x,int y);
int window_id;
int win_width = 500, win_height = 500;
int main(int argc, char* argv[]){
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
glOrtho(0, width, 0, height, -1, 1);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glEnable(GL_DEPTH_TEST);
glDisable(GL_LIGHTING);

Mesh m1(width,height);
m1.initialize();
m1.render();
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
