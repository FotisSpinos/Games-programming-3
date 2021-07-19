#include "pch.h"
#include "ShaderProgram.h"
#include "Log.h"

static GLuint* m_bindedProgram;

ShaderProgram::ShaderProgram(const std::string& vShaderFile, const std::string& fShaderFile)
{
	m_vShader = std::make_shared<Shader>(vShaderFile, VERTEX_SHADER);
	m_fShader = std::make_shared<Shader>(fShaderFile, FRAGMENT_SHADER);
	CHECK_GL_ERROR();
	m_program = glCreateProgram();
	glAttachShader(m_program, m_vShader->Get());
	glAttachShader(m_program, m_fShader->Get());
	Link();
}
ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_program);
}
void ShaderProgram::BindAttribLoc(GLuint loc, const char* name)
{
	glBindAttribLocation(m_program, loc, name);
	CHECK_GL_ERROR();
}
void ShaderProgram::Link()
{
	//link shaders and attribs
	glLinkProgram(m_program);
	CheckForLinkErrors();
	CHECK_GL_ERROR();

	//if they were linked we no longer need them
	m_vShader.reset();
	m_fShader.reset();
}
void ShaderProgram::Use()
{
	if (m_bindedProgram == &m_program)
	{
		//LOG_DEBUG("The Shader Program has already been binded");
		return;
	}

	glUseProgram(m_program);
	m_bindedProgram = &m_program;
}
bool ShaderProgram::CheckForLinkErrors()
{
	GLint isLinked = 0;
	glGetProgramiv(m_program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint length = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);
		char* msg = (char*)malloc(length);
		glGetProgramInfoLog(m_program, length, &length, msg);
		printf("Shader linking error: %s\n", msg);
		free(msg);
		glDeleteProgram(m_program);
		return true;
	}
	return false;
}
