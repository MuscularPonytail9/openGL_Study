// sb6.h 헤더 파일을 포함시킨다.
#include <sb7.h>
#include <vmath.h>

// sb6::application을 상속받는다.
class my_application : public sb7::application
{
public:
	// 쉐이더 컴파일한다.
	GLuint compile_shaders(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		// 버텍스 쉐이더 소스 코드
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

		// 프래그먼트 쉐이더 소스 코드
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

		// 버텍스 쉐이더를 생성하고 컴파일한다.
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		// 프래그먼트 쉐이더를 생성하고 컴파일한다.
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		// 프로그램을 생성하고 쉐이더를 Attach시키고 링크한다.
		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		// 이제 프로그램이 쉐이더를 소유하므로 쉐이더를 삭제한다.
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}

	// 애플리케이션 초기화 수행한다.
	virtual void startup()
	{
		rendering_program = compile_shaders();
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// 삼각형 세점 위치와 컬러를 정의한다.
		GLfloat vertices[] = {
			0.25f, -0.25f, 0.5f, 1.0f, 0.0f, 0.0f,  // 버텍스 1
			-0.25f, 0.25f, 0.5f, 0.0f, 1.0f, 0.0f,  // 버텍스 2
			0.25f, 0.25f, 0.5f, 0.0f, 0.0f, 1.0f    // 버텍스 3
		};

		// VBO를 생성하여 vertices 값들을 복사
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// VBO를 나누어서 각 버텍스 속성으로 연결
		// 위치 속성 (location = 0)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// 컬러 속성 (location = 1)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// VBO 및 버텍스 속성을 다 했으니 VBO와 VAO를 unbind한다.
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	// 애플리케이션 끝날 때 호출된다.
	virtual void shutdown()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteProgram(rendering_program);
	}

	// 렌더링 virtual 함수를 작성해서 오버라이딩한다.
	virtual void render(double currentTime)
	{
		const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 0.0f, 1.0f };
		const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, black);

		// 렌더링위해 생성한 프로그램 객체를 사용하도록 한다.
		glUseProgram(rendering_program);

		// z축에 대한 회전 행렬을 만든다.
		float angle = currentTime * 50;
		vmath::mat4 rm = vmath::rotate(angle, 0.0f, 0.0f, 1.0f);
		// "rotMat" uniform에 대한 위치를 가져온다.
		GLint rotMatLocation = glGetUniformLocation(rendering_program, "rotMat");
		// "rotMat" uniform으로 전달한다.
		glUniformMatrix4fv(rotMatLocation, 1, GL_FALSE, rm);

		// 미리 설정한 VAO를 그리기 위해 bind한다.
		glBindVertexArray(VAO);

		// 삼각형을 하나 그린다. 
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

private:
	GLuint rendering_program;
	GLuint VAO;
};

// DECLARE_MAIN의 하나뿐인 인스턴스
DECLARE_MAIN(my_application)