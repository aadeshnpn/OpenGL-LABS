#include <GL/gl.h>
#include <GL/freeglut.h>

#ifndef __PETESMESH_H__
#define __PETESMESH_H__ 1

class Mesh
{
public:
  Mesh(const int w, const int h);
  ~Mesh();
  
  int numTriangles( void ) const { return m_num_triangles; }

  void initialize( void );
  void render( void );

private:
  GLfloat *m_data;       // contains the data for the vertices of the mesh
  GLfloat *m_color;
  GLuint *m_indices;    // contains the indices of the triangles in the m_data array
  GLint m_width, m_height; // width and height of the mesh

  int m_num_triangles;
  GLint m_indice_count;
  
  GLint m_max_vertices,
    m_max_indices;

  void genTriangleIndices( void );
};

#endif
