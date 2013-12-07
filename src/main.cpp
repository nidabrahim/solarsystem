
#define GL_GLEXT_PROTOTYPES
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include <boost/bind.hpp>

#include "engine/Engine.hpp"
#include "solar_system.hpp"


int main(int argc, char**argv) {

	Engine engine("solarsystem", 1024, 1024, PRINT_VERSION);

	//SDL_GL_SetSwapInterval(0);

	SolarSystem *system =  new SolarSystem();

	
	engine.registerRenderFunc(
			boost::bind(&SolarSystem::renderFunc, system, _1, _2)
	);


	//engine.toggleDebugCamera();
	engine.run();

}
