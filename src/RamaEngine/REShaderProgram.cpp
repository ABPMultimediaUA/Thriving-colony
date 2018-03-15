#include "REShaderProgram.h"

REShaderProgram::REShaderProgram(ResourceGLSL* vs, ResourceGLSL* fs){
	vertexShader = new TShader(vs);
	fragmentShader = new TShader(fs);

	pid = glCreateProgram();
	glAttachShader(pid, vertexShader->getShaderID());
	glAttachShader(pid, fragmentShader->getShaderID());
	
	glLinkProgram(pid);

	// Check the program
    GLint Result = GL_FALSE;
    int InfoLogLength;
	glGetProgramiv(pid, GL_LINK_STATUS, &Result);
	glGetProgramiv(pid, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(pid, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << &ProgramErrorMessage[0] << std::endl;
		exit(0);
	}

	rootEntity = new TRoot(pid);
}

REShaderProgram::~REShaderProgram(){
	glDetachShader(pid, vertexShader->getShaderID());
	glDeleteShader(vertexShader->getShaderID());
	glDetachShader(pid, fragmentShader->getShaderID());
	glDeleteShader(fragmentShader->getShaderID());
}
    
TRoot *REShaderProgram::getRootEntity(){
	return rootEntity;
}
    
GLuint REShaderProgram::getShaderProgram(){
	return pid;
}