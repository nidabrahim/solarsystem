#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <stdexcept>
#include <boost/container/vector.hpp>
#include <boost/lexical_cast.hpp>

#include "shader.hpp"


using std::ifstream;
using std::ios;
using boost::container::vector;
using boost::lexical_cast;


Shader::Shader(string vert_shader_file, string frag_shader_file) {
	GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

	string vert_code = loadShaderFile(vert_shader_file);
	string fragCode = loadShaderFile(frag_shader_file);

	compileShader(vert_shader, vert_code);
	if (!checkShader(vert_shader, vert_shader_file)) {
		throw std::runtime_error("Could not compile vertex shader");
	}

	compileShader(frag_shader, fragCode);
	if (!checkShader(frag_shader, frag_shader_file)) {
		throw std::runtime_error("Could not compile fragment shader");
	}

	program = glCreateProgram();
	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);
	glLinkProgram(program);

	if (!checkProgram(program)) {
		throw std::runtime_error("Could, not create program");
	}
}

Shader::Shader(string vert_shader_file, string frag_shader_file, string geom_shader_file) {
	GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint geom_shader = glCreateShader(GL_GEOMETRY_SHADER_EXT);

	string vert_code = loadShaderFile(vert_shader_file);
	string fragCode = loadShaderFile(frag_shader_file);
	string geomCode = loadShaderFile(geom_shader_file);

	compileShader(vert_shader, vert_code);
	if (!checkShader(vert_shader, vert_shader_file)) {
		throw std::runtime_error("Could not compile vertex shader");
	}

	compileShader(frag_shader, fragCode);
	if (!checkShader(frag_shader, frag_shader_file)) {
		throw std::runtime_error("Could not compile fragment shader");
	}

	compileShader(geom_shader, geomCode);
	if (!checkShader(geom_shader, geom_shader_file)) {
		throw std::runtime_error("Could not compile geometry shader");
	}

	program = glCreateProgram();
	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);
	glAttachShader(program, geom_shader);


	glLinkProgram(program);

	if (!checkProgram(program)) {
		throw std::runtime_error("Could, not create program");
	}
}


void Shader::compileShader(GLuint shaderID, string shaderCode)  {
	char const *sourcePointer = shaderCode.c_str();

	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);
}

/**
 * Check the shader compilation for errors
 */
GLboolean Shader::checkShader(GLuint shaderID, string shader_file) {
	GLint result = GL_FALSE;
	GLint logLength = 0;

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

	// TODO only print when there is a log
	if (logLength > 0) {
		std::cout << "--- " << shader_file  << ": " << std::endl; 
		vector<char> errorMsg(logLength + 1);
		glGetShaderInfoLog(shaderID, logLength, NULL, &errorMsg[0]);
		std::cout << &errorMsg[0] << std::endl;
	}
	return result;
}


GLboolean Shader::checkProgram(GLuint program) {
	GLint result = GL_FALSE;
	GLint logLength = 1000;

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

	vector<char> errorMsg(logLength + 1);
	glGetProgramInfoLog(program, logLength, NULL, &errorMsg[0]);
	std::cout << &errorMsg[0] << std::endl;
	return result;
}

string Shader::loadShaderFile(string file) {
	string shaderCode;

	ifstream codeStream(file, ios::in);
	if (codeStream.is_open()) {
		string line = "";

		while (getline(codeStream, line)) {
			shaderCode += "\n" + line;
		}

		codeStream.close();
	}
	else {
		throw std::invalid_argument("Shader file " + file);
	}

	return shaderCode;
}
