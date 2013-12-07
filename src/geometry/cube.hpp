#ifndef CUBE_LBT1GNQA

#define CUBE_LBT1GNQA

#define GL_GLEXT_PROTOTYPES
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>


class Cube {
	public:
		Cube();
		~Cube();

	protected:
		void draw();

		GLuint *buffers;

		GLuint vertex_count;
		GLfloat *vertices;

		GLuint normal_count;
		GLfloat *normals;

};

#endif /* end of include guard: CUBE_LBT1GNQA */
