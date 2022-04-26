// sb6.h ��� ������ ���Խ�Ų��.
#include <sb7.h>
#include <vmath.h>

// sb6::application�� ��ӹ޴´�.
class my_application : public sb7::application
{
public:
	// ���̴� �������Ѵ�.
	GLuint compile_shaders(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		// ���ؽ� ���̴� �ҽ� �ڵ�
		static const GLchar* vertex_shader_source[] =
		{
			"#version 430 core											\n"
			"															\n"
			"layout(location = 0) in vec3 pos;							\n"
			"layout(location = 1) in vec3 color;						\n"
			"															\n"
			"uniform mat4 rotMat;										\n"
			"															\n"
			"out vec3 vsColor;											\n"
			"															\n"
			"void main(void)											\n"
			"{															\n"
			"	gl_Position = rotMat*vec4(pos.x, pos.y, pos.z, 1.0);	\n"
			"															\n"
			"	vsColor = color;										\n"
			"}															\n"
		};

		// �����׸�Ʈ ���̴� �ҽ� �ڵ�
		static const GLchar* fragment_shader_source[] =
		{
			"#version 430 core						\n"
			"										\n"
			"in vec3 vsColor;						\n"
			"out vec4 fragColor;					\n"
			"										\n"
			"void main(void)						\n"
			"{										\n"
			"	fragColor = vec4(vsColor, 1.0);		\n"
			"}										\n"
		};

		// ���ؽ� ���̴��� �����ϰ� �������Ѵ�.
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		// �����׸�Ʈ ���̴��� �����ϰ� �������Ѵ�.
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		// ���α׷��� �����ϰ� ���̴��� Attach��Ű�� ��ũ�Ѵ�.
		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		// ���� ���α׷��� ���̴��� �����ϹǷ� ���̴��� �����Ѵ�.
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}

	// ���ø����̼� �ʱ�ȭ �����Ѵ�.
	virtual void startup()
	{
		rendering_program = compile_shaders();
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// �ﰢ�� ���� ��ġ�� �÷��� �����Ѵ�.
		GLfloat vertices[] = {
			0.25f, -0.25f, 0.5f, 1.0f, 0.0f, 0.0f,  // ���ؽ� 1
			-0.25f, 0.25f, 0.5f, 0.0f, 1.0f, 0.0f,  // ���ؽ� 2
			0.25f, 0.25f, 0.5f, 0.0f, 0.0f, 1.0f    // ���ؽ� 3
		};

		// VBO�� �����Ͽ� vertices ������ ����
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// VBO�� ����� �� ���ؽ� �Ӽ����� ����
		// ��ġ �Ӽ� (location = 0)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// �÷� �Ӽ� (location = 1)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// VBO �� ���ؽ� �Ӽ��� �� ������ VBO�� VAO�� unbind�Ѵ�.
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	// ���ø����̼� ���� �� ȣ��ȴ�.
	virtual void shutdown()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteProgram(rendering_program);
	}

	// ������ virtual �Լ��� �ۼ��ؼ� �������̵��Ѵ�.
	virtual void render(double currentTime)
	{
		const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 0.0f, 1.0f };
		const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, black);

		// ���������� ������ ���α׷� ��ü�� ����ϵ��� �Ѵ�.
		glUseProgram(rendering_program);

		// z�࿡ ���� ȸ�� ����� �����.
		float angle = currentTime * 50;
		vmath::mat4 rm = vmath::rotate(angle, 0.0f, 0.0f, 1.0f);
		// "rotMat" uniform�� ���� ��ġ�� �����´�.
		GLint rotMatLocation = glGetUniformLocation(rendering_program, "rotMat");
		// "rotMat" uniform���� �����Ѵ�.
		glUniformMatrix4fv(rotMatLocation, 1, GL_FALSE, rm);

		// �̸� ������ VAO�� �׸��� ���� bind�Ѵ�.
		glBindVertexArray(VAO);

		// �ﰢ���� �ϳ� �׸���. 
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

private:
	GLuint rendering_program;
	GLuint VAO;
};

// DECLARE_MAIN�� �ϳ����� �ν��Ͻ�
DECLARE_MAIN(my_application)