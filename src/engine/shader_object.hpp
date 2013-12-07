#ifndef SHADER_OBJECT_Y038QQAX

#define SHADER_OBJECT_Y038QQAX

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

class ShaderObject {
	protected:
		void initialiseVariables(GLuint programID);
		void assignVariables();

		struct {
			GLuint projection;
			GLuint view;
			GLuint cam_pos;
		} global_shader_vars;

		virtual ~ShaderObject() = 0;
};



#endif /* end of include guard: SHADER_OBJECT_Y038QQAX */
