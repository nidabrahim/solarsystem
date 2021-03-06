#ifndef TEXTURE_OBJECT_7UDF7LAB

#define TEXTURE_OBJECT_7UDF7LAB

#include <string>
#include <GL/gl.h>
#include <SDL2/SDL.h>

using std::string;

class TextureObject {
	protected:
		GLuint createCubeTexture(
			string x_pos,
			string x_neg,
			string y_pos,
			string y_neg,
			string z_pos,
			string z_neg
		);

		GLuint create1DTexture(
			string path
		);
		
		GLuint createGL1DTexture(); 

		SDL_Surface *loadTextureImage(string path);

		GLuint createGLCubeTexture();
		void cubeTextureParameters();

		void assignCubeTextureImages(
			SDL_Surface *,
			SDL_Surface *,
			SDL_Surface *,
			SDL_Surface *,
			SDL_Surface *,
			SDL_Surface *
		);

		struct tex_info {
			GLenum texture_format;
			GLint n_of_colors;
		};

		tex_info getTextureParams(SDL_Surface *);

		void assign2DImage(SDL_Surface *, GLenum target);

};

#endif /* end of include guard: TEXTURE_OBJECT_7UDF7LAB */
