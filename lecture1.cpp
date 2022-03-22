//배경색 칠하기//////////////////////////////////////////
// sb6.h 헤더 파일을 포함시킨다.
#include <sb6.h>
#include <vmath.h>

// sb6::application을 상속받는다.
class my_application : public sb6::application
{
public:
	GLuint compile_shaders(void) {
		GLuint vertex_shader;

		GLuint fragment_shader;

		GLuint program;

		static const GLchar * vertex_shader_source[] =
		{
			"#version 430 core														\n"
			"																		\n"
			"void main(void)														\n"
			"{																		\n"
			"	const vec4 vertices[12] = vec4[12](vec4(0.0, 0.0, 0.5, 1.0),			\n"
			"									 vec4(-0.50, 0.5, 0.5, 1.0),		\n"
			"									 vec4(0.0, 0.5, 0.5, 1.0),			\n"
			"									 vec4(0.0, 0.0, 0.5, 1.0),			\n"
			"									 vec4(0.5, 0.5, 0.5, 1.0),			\n"
			"									 vec4(0.5, 0.0, 0.5, 1.0),			\n"
			"									 vec4(0.0, 0.0, 0.5, 1.0),			\n"
			"									 vec4(0.5, -0.5, 0.5, 1.0),		\n"
			"									 vec4(0.0, -0.5, 0.5, 1.0),		\n"
			"									 vec4(0.0, 0.0, 0.5, 1.0),			\n"
			"									 vec4(-0.5, -0.5, 0.5, 1.0),		\n"
			"									 vec4(-0.5, 0.0, 0.5, 1.0));		\n"
			"	gl_Position = vertices[gl_VertexID];								\n"
			"																		\n"
			"}																		\n"
		};

		static const GLchar * fragment_shader_source[] =
		{
			"#version 430 core								\n"
			"												\n"
			"out vec4 color;								\n"
			"												\n"
			"void main(void)								\n"
			"{												\n"
			"												\n"
			"	color = vec4(0.0, 0.8, 1.0, 1.0);			\n"
			"}												\n"
		};

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(vertex_shader);
		glCompileShader(fragment_shader);
		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		return program;
	}
	virtual void startup() {
		rendering_program = compile_shaders();
		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);
	}
	virtual void shutdown() {
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program);
	}
	// 렌더링 virtual 함수를 작성해서 오버라이딩한다.
	virtual void render(double currentTime)
	{
		const GLfloat red[] = { (float)sin(currentTime)*0.5f + 0.5f, (float)cos(currentTime)*0.5f + 0.5f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, red);
		glUseProgram(rendering_program);

		glDrawArrays(GL_TRIANGLES, 0, 12);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
	}

private:
	GLuint rendering_program;
	GLuint vertex_array_object;
};

// DECLARE_MAIN의 하나뿐인 인스턴스
DECLARE_MAIN(my_application)
