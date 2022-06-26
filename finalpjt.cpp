// sb6.h ��� ������ ���Խ�Ų��.
#include <sb7.h>
#include <vmath.h>
#include <shader.h>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Model.h"

// sb6::application�� ��ӹ޴´�.
class my_application : public sb7::application
{
public:
	// ���̴� �������Ѵ�.
	GLuint compile_shader(const char* vs_filename, const char* fs_filename)
	{
		// ���ؽ� ���̴��� �����ϰ� �������Ѵ�.
		GLuint vertex_shader = sb7::shader::load(vs_filename, GL_VERTEX_SHADER);

		// �����׸�Ʈ ���̴��� �����ϰ� �������Ѵ�.
		GLuint fragment_shader = sb7::shader::load(fs_filename, GL_FRAGMENT_SHADER);

		// ���α׷��� �����ϰ� ���̴��� Attach��Ű�� ��ũ�Ѵ�.
		GLuint program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		// ���� ���α׷��� ���̴��� �����ϹǷ� ���̴��� �����Ѵ�.
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}
	GLuint compile_shader_screen(void)
	{
		// ���ؽ� ���̴��� �����ϰ� �������Ѵ�.
		GLuint vertex_shader = sb7::shader::load("screen_filtering_vs.glsl", GL_VERTEX_SHADER);

		// �����׸�Ʈ ���̴��� �����ϰ� �������Ѵ�.
		GLuint fragment_shader = sb7::shader::load("screen_filtering_fs.glsl", GL_FRAGMENT_SHADER);

		// ���α׷��� �����ϰ� ���̴��� Attach��Ű�� ��ũ�Ѵ�.
		GLuint program = glCreateProgram();
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
		// ���̴� ���α׷� ������ �� ����
		shader_programs[0] = compile_shader("basic_texturing_vs.glsl", "basic_texturing_fs.glsl");
		shader_programs[1] = compile_shader("multiple_lights_vs.glsl", "multiple_lights_fs.glsl");
		shader_programs[2] = compile_shader("simple_color_vs.glsl", "simple_color_fs.glsl");
		shader_program_screen = compile_shader_screen();

		// VAO, VBO, EBO, texture ����
		glGenVertexArrays(3, VAOs);
		glGenBuffers(3, VBOs);
		glGenBuffers(2, EBOs);
		glGenTextures(3, textures);

		stbi_set_flip_vertically_on_load(true);

		// ù ��° ��ü ���� : �ٴ� --------------------------------------------------
		glBindVertexArray(VAOs[0]);
		// �ٴ� ������ ��ġ�� �÷�, �ؽ�ó ��ǥ�� �����Ѵ�.
		float floor_s = 3.0f, floor_t = 3.0f;
		GLfloat floor_vertices[] = {
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, floor_s, floor_t,  // ���� ���
			-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, floor_t,  // ���� ���
			-1.0f, 0.0f, 30.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // ���� �ϴ�
			1.0f, 0.0f, 30.0f, 1.0f, 1.0f, 0.0f, floor_s, 0.0f,   // ���� �ϴ�
			-1.0f, 2.0f, 7.0f, 1.0f, 0.0f, 0.0f, floor_s, floor_t, // 1-1���� ������ ��
			1.0f, 2.0f, 7.0f, 0.0f, 1.0f, 0.0f, 0.0f, floor_t, // 1-1���� ���� ��
			1.0f, 0.0f, 7.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 1-1���� ���� �Ʒ�
			-1.0f, 0.0f, 7.0f, 1.0f, 1.0f, 0.0f, floor_s, 0.0f, // 1-1���� ������ �Ʒ�
			-1.0f, 10.0f, 7.0f, 1.0f, 0.0f, 0.0f, floor_s, floor_t, // 1-2���� ������ ��
			1.0f, 10.0f, 7.0f, 0.0f, 1.0f, 0.0f, 0.0f, floor_t, // 1-2���� ���� ��
			1.0f, 3.0f, 7.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 1-2���� ���� �Ʒ�
			-1.0f, 3.0f, 7.0f, 1.0f, 1.0f, 0.0f, floor_s, 0.0f, // 1-2���� ������ �Ʒ�
			-1.0f, 6.0f, 14.0f, 1.0f, 0.0f, 0.0f, floor_s, floor_t, // 2-1���� ������ ��
			1.0f, 6.0f, 14.0f, 0.0f, 1.0f, 0.0f, 0.0f, floor_t, // 2-1���� ���� ��
			1.0f, 0.0f, 14.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 2-1���� ���� �Ʒ�
			-1.0f, 0.0f, 14.0f, 1.0f, 1.0f, 0.0f, floor_s, 0.0f, // 2-1���� ������ �Ʒ�
			-1.0f, 10.0f, 14.0f, 1.0f, 0.0f, 0.0f, floor_s, floor_t, // 2-2���� ������ ��
			1.0f, 10.0f, 14.0f, 0.0f, 1.0f, 0.0f, 0.0f, floor_t, // 2-2���� ���� ��
			1.0f, 7.0f, 14.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 2-2���� ���� �Ʒ�
			-1.0f, 7.0f, 14.0f, 1.0f, 1.0f, 0.0f, floor_s, 0.0f, // 2-2���� ������ �Ʒ�
			-1.0f, 4.0f, 21.0f, 1.0f, 0.0f, 0.0f, floor_s, floor_t, // 3-1���� ������ ��
			1.0f, 4.0f, 21.0f, 0.0f, 1.0f, 0.0f, 0.0f, floor_t, // 3-1���� ���� ��
			1.0f, 0.0f, 21.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 3-1���� ���� �Ʒ�
			-1.0f, 0.0f, 21.0f, 1.0f, 1.0f, 0.0f, floor_s, 0.0f, // 3-1���� ������ �Ʒ�
			-1.0f, 10.0f, 21.0f, 1.0f, 0.0f, 0.0f, floor_s, floor_t, // 3-2���� ������ ��
			1.0f, 10.0f, 21.0f, 0.0f, 1.0f, 0.0f, 0.0f, floor_t, // 3-2���� ���� ��
			1.0f, 5.0f, 21.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 3-2���� ���� �Ʒ�
			-1.0f, 5.0f, 21.0f, 1.0f, 1.0f, 0.0f, floor_s, 0.0f, // 3-2���� ������ �Ʒ�
			-1.0f, 6.0f, 28.0f, 1.0f, 0.0f, 0.0f, floor_s, floor_t, // 4-1���� ������ ��
			1.0f, 6.0f, 28.0f, 0.0f, 1.0f, 0.0f, 0.0f, floor_t, // 4-1���� ���� ��
			1.0f, 0.0f, 28.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 4-1���� ���� �Ʒ�
			-1.0f, 0.0f, 28.0f, 1.0f, 1.0f, 0.0f, floor_s, 0.0f, // 4-1���� ������ �Ʒ�
			-1.0f, 10.0f, 28.0f, 1.0f, 0.0f, 0.0f, floor_s, floor_t, // 4-2���� ������ ��
			1.0f, 10.0f, 28.0f, 0.0f, 1.0f, 0.0f, 0.0f, floor_t, // 4-2���� ���� ��
			1.0f, 7.0f, 28.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 4-2���� ���� �Ʒ�
			-1.0f, 7.0f, 28.0f, 1.0f, 1.0f, 0.0f, floor_s, 0.0f, // 4-2���� ������ �Ʒ�
		};

		// �ﰢ������ �׸� �ε����� �����Ѵ�.
		GLuint floor_indices[] = {
			0, 1, 2,	// ù��° �ﰢ��
			0, 2, 3,		// �ι�° �ﰢ��
			4, 5, 6,
			4, 6, 7,
			8, 9, 10,
			8, 10, 11,
			12, 13, 14,
			12, 14, 15,
			16, 17, 18,
			16, 18, 19,
			20, 21, 22,
			20, 22, 23,
			24, 25, 26,
			24, 26, 27,
			28, 29, 30,
			28, 30, 31,
			32, 33, 34,
			32, 34, 35
		};

		// VBO�� �����Ͽ� vertices ������ ����
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(floor_vertices), floor_vertices, GL_STATIC_DRAW);

		// VBO�� ����� �� ���ؽ� �Ӽ����� ����
		// ��ġ �Ӽ� (location = 0)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// �÷� �Ӽ� (location = 1)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// �ؽ�ó ��ǥ �Ӽ� (location = 2)
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// EBO�� �����ϰ� indices ������ ����
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floor_indices), floor_indices, GL_STATIC_DRAW);

		// VBO �� ���ؽ� �Ӽ��� �� ������ VBO�� VAO�� unbind�Ѵ�.
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// �ؽ�ó ��ü ����� ���ε�			
		glBindTexture(GL_TEXTURE_2D, textures[0]);

		// �ؽ�ó �̹��� �ε��ϱ�
		int width, height, nrChannels;
		unsigned char *data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		stbi_image_free(data);

		// �ؽ�ó ���ø�/���͸� ����
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// �� ��° ��ü ���� : �ڽ� --------------------------------------------------
		//glBindVertexArray(VAOs[1]);
		//// �ڽ� ������ ��ġ�� �÷�, �ؽ�ó ��ǥ�� �����Ѵ�.
		//float box_s = 1.0f, box_t = 1.0f;
		//GLfloat box_vertices[] = {
		//	// �޸�
		//	-0.25f, 0.5f, -0.25f, 1.0f, 0.0f, 0.0f,		box_s, box_t,	0.0f, 0.0f, -1.0f,
		//	0.25f, 0.0f, -0.25f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
		//	-0.25f, 0.0f, -0.25f, 1.0f, 0.0f, 0.0f,		box_s, 0.0f,	0.0f, 0.0f, -1.0f,

		//	0.25f, 0.0f, -0.25f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
		//	-0.25f, 0.5f, -0.25f, 1.0f, 0.0f, 0.0f,		box_s, box_t,	0.0f, 0.0f, -1.0f,
		//	0.25f, 0.5f, -0.25f, 1.0f, 0.0f, 0.0f,		0.0f, box_t,	0.0f, 0.0f, -1.0f,
		//	// ������
		//	0.25f, 0.0f, -0.25f, 0.0f, 1.0f, 0.0f,		box_s, 0.0f,	1.0f, 0.0f, 0.0f,
		//	0.25f, 0.5f, -0.25f, 0.0f, 1.0f, 0.0f,		box_s, box_t,	1.0f, 0.0f, 0.0f,
		//	0.25f, 0.0f, 0.25f, 0.0f, 1.0f, 0.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,

		//	0.25f, 0.0f, 0.25f, 0.0f, 1.0f, 0.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		//	0.25f, 0.5f, -0.25f, 0.0f, 1.0f, 0.0f,		box_s, box_t,	1.0f, 0.0f, 0.0f,
		//	0.25f, 0.5f, 0.25f, 0.0f, 1.0f, 0.0f,		0.0f, box_t,	1.0f, 0.0f, 0.0f,
		//	// ����
		//	0.25f, 0.0f, 0.25f, 0.0f, 0.0f, 1.0f,		box_s, 0.0f,	0.0f, 0.0f, 1.0f,
		//	0.25f, 0.5f, 0.25f, 0.0f, 0.0f, 1.0f,		box_s, box_t,	0.0f, 0.0f, 1.0f,
		//	-0.25f, 0.0f, 0.25f, 0.0f, 0.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,

		//	-0.25f, 0.0f, 0.25f, 0.0f, 0.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		//	0.25f, 0.5f, 0.25f, 0.0f, 0.0f, 1.0f,		box_s, box_t,	0.0f, 0.0f, 1.0f,
		//	-0.25f, 0.5f, 0.25f, 0.0f, 0.0f, 1.0f,		0.0f, box_t,	0.0f, 0.0f, 1.0f,
		//	// ������
		//	-0.25f, 0.0f, 0.25f, 1.0f, 0.0f, 1.0f,		box_s, 0.0f,	-1.0f, 0.0f, 0.0f,
		//	-0.25f, 0.5f, 0.25f, 1.0f, 0.0f, 1.0f,		box_s, box_t,	-1.0f, 0.0f, 0.0f,
		//	-0.25f, 0.0f, -0.25f, 1.0f, 0.0f, 1.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,

		//	-0.25f, 0.0f, -0.25f, 1.0f, 0.0f, 1.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
		//	-0.25f, 0.5f, 0.25f, 1.0f, 0.0f, 1.0f,		box_s, box_t,	-1.0f, 0.0f, 0.0f,
		//	-0.25f, 0.5f, -0.25f, 1.0f, 0.0f, 1.0f,		0.0f, box_t,	-1.0f, 0.0f, 0.0f,
		//	// �ٴڸ�
		//	-0.25f, 0.0f, 0.25f, 1.0f, 1.0f, 0.0f,		box_s, 0.0f,	0.0f, -1.0f, 0.0f,
		//	0.25f, 0.0f, -0.25f, 1.0f, 1.0f, 0.0f,		0.0f, box_t,	0.0f, -1.0f, 0.0f,
		//	0.25f, 0.0f, 0.25f, 1.0f, 1.0f, 0.0f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,

		//	0.25f, 0.0f, -0.25f, 1.0f, 1.0f, 0.0f,		0.0f, box_t,	0.0f, -1.0f, 0.0f,
		//	-0.25f, 0.0f, 0.25f, 1.0f, 1.0f, 0.0f,		box_s, 0.0,		0.0f, -1.0f, 0.0f,
		//	-0.25f, 0.0f, -0.25f, 1.0f, 1.0f, 0.0f,		box_s, box_t,	0.0f, -1.0f, 0.0f,
		//	// ����
		//	-0.25f, 0.5f, -0.25f, 0.0f, 1.0f, 1.0f,		0.0f, box_t,	0.0f, 1.0f, 0.0f,
		//	0.25f, 0.5f, 0.25f, 0.0f, 1.0f, 1.0f,		box_s, 0.0f,	0.0f, 1.0f, 0.0f,
		//	0.25f, 0.5f, -0.25f, 0.0f, 1.0f, 1.0f,		box_s, box_t,	0.0f, 1.0f, 0.0f,

		//	0.25f, 0.5f, 0.25f, 0.0f, 1.0f, 1.0f,		box_s, 0.0f,	0.0f, 1.0f, 0.0f,
		//	-0.25f, 0.5f, -0.25f, 0.0f, 1.0f, 1.0f,		0.0f, box_t,	0.0f, 1.0f, 0.0f,
		//	-0.25f, 0.5f, 0.25f, 0.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f
		//};
		//
		//boxPositions.push_back(vmath::vec3(0.0f, 0.0f, 0.0f));
		//boxPositions.push_back(vmath::vec3(2.0f, 5.0f, -15.0f));
		//boxPositions.push_back(vmath::vec3(-1.5f, -2.2f, -2.5f));
		//boxPositions.push_back(vmath::vec3(-3.8f, -2.0f, -12.3f));
		//boxPositions.push_back(vmath::vec3(2.4f, -0.4f, -3.5f));
		//boxPositions.push_back(vmath::vec3(-1.7f, 3.0f, -7.5f));
		//boxPositions.push_back(vmath::vec3(1.3f, -2.0f, -2.5f));
		//boxPositions.push_back(vmath::vec3(1.5f, 2.0f, -2.5f));
		//boxPositions.push_back(vmath::vec3(1.5f, 0.2f, -1.5f));
		//boxPositions.push_back(vmath::vec3(-1.3f, 1.0f, -1.5f));


		//// VBO�� �����Ͽ� vertices ������ ����
		//glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(box_vertices), box_vertices, GL_STATIC_DRAW);

		//// VBO�� ����� �� ���ؽ� �Ӽ����� ����
		//// ��ġ �Ӽ� (location = 0)
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);
		//// �÷� �Ӽ� (location = 1)
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(1);
		//// �ؽ�ó ��ǥ �Ӽ� (location = 2)
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
		//glEnableVertexAttribArray(2);
		//// ��� �Ӽ� (location = 3)
		//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
		//glEnableVertexAttribArray(3);

		//// VBO �� ���ؽ� �Ӽ��� �� ������ VBO�� VAO�� unbind�Ѵ�.
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindVertexArray(0);

		//// Diffuse Map �̹��� �ε� �� ����
		//glBindTexture(GL_TEXTURE_2D, textures[1]);

		//width, height, nrChannels;
		//data = stbi_load("container2.png", &width, &height, &nrChannels, 0);

		//if (data) {
		//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//	glGenerateMipmap(GL_TEXTURE_2D);
		//}
		//stbi_image_free(data);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//// Specular Map �̹��� �ε� �� ����
		//glBindTexture(GL_TEXTURE_2D, textures[2]);

		//width, height, nrChannels;
		//data = stbi_load("container2_specular.png", &width, &height, &nrChannels, 0);

		//if (data) {
		//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//	glGenerateMipmap(GL_TEXTURE_2D);
		//}
		//stbi_image_free(data);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//  �� ��° ��ü ���� : �Ƕ�̵� --------------------------------------------------
		glBindVertexArray(VAOs[2]);
		// �Ƕ�̵� ������ ��ġ�� �÷�, �ؽ�ó ��ǥ�� �����Ѵ�.
		//GLfloat pyramid_vertices[] = {
		//	1.0f, 0.0f, -1.0f,    // ���� ���
		//	-1.0f, 0.0f, -1.0f,   // ���� ���
		//	-1.0f, 0.0f, 1.0f,    // ���� �ϴ�
		//	1.0f, 0.0f, 1.0f,     // ���� �ϴ�
		//	0.0f, 1.0f, 0.0f,      // ��� ������
		//	0.0f, -1.0f, 0.0f,      // �ϴ� ������
		//};

		//// �ﰢ������ �׸� �ε����� �����Ѵ�.
		//GLuint pyramid_indices[] = {
		//	4, 0, 1,
		//	4, 1, 2,
		//	4, 2, 3,
		//	4, 3, 0,

		//	5, 1, 0,
		//	5, 2, 1,
		//	5, 3, 2,
		//	5, 0, 3,
		//};

		//// VBO�� �����Ͽ� vertices ������ ����
		//glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid_vertices), pyramid_vertices, GL_STATIC_DRAW);

		//// VBO�� ����� �� ���ؽ� �Ӽ����� ����
		//// ��ġ �Ӽ� (location = 0)
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);

		//// EBO�� �����ϰ� indices ������ ����
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pyramid_indices), pyramid_indices, GL_STATIC_DRAW);

		// VBO �� ���ؽ� �Ӽ��� �� ������ VBO�� VAO�� unbind�Ѵ�.
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//�𵨸�
		objModel.init();
		//objModel.defaultDiffuse = vmath::vec3(0.2f, 0.1f, 0.2f);
		objModel.loadOBJ("squid_girl.obj");
		
		glEnable(GL_MULTISAMPLE);

		//  Post-processing�� ��ũ�� ���� --------------------------------------------------
		GLfloat screenVertices[] = {
			//NDC xy��ǥ //�ؽ�ó UV
			-1.0f, 1.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 1.0f, 0.0f,

			-1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f
		};

		glGenVertexArrays(1, &VAO_screen);
		glGenBuffers(1, &VBO_screen);
		glBindVertexArray(VAO_screen);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_screen);

		glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), screenVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// framebuffer ���� --------------------------------------------------
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		// color buffer �ؽ�ó ���� �� ����
		glGenTextures(1, &FBO_texture);
		glBindTexture(GL_TEXTURE_2D, FBO_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.windowWidth, info.windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBO_texture, 0);
		// depth&stencil buffer�� ���� Render Buffer Object ���� �� ����
		GLuint RBO;
		glGenRenderbuffers(1, &RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, info.windowWidth, info.windowHeight);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
		// Framebuffer�� ���������� ����� ������ Ȯ��
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			glfwTerminate();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	// ���ø����̼� ���� �� ȣ��ȴ�.
	virtual void shutdown()
	{
		glDeleteTextures(3, textures);
		glDeleteBuffers(2, EBOs);
		glDeleteBuffers(3, VBOs);
		glDeleteVertexArrays(3, VAOs);
		glDeleteProgram(shader_programs[0]);
		glDeleteProgram(shader_programs[1]);
	}

	// ������ virtual �Լ��� �ۼ��ؼ� �������̵��Ѵ�.
	virtual void render(double currentTime)
	{
		t++;
		//currentTime = 1.46;
		//const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 0.0f, 1.0f };
		const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, black);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glViewport(0, 0, info.windowWidth, info.windowHeight);
		GLint uniform_transform1 = glGetUniformLocation(shader_programs[0], "transform");
		GLint uniform_transform2 = glGetUniformLocation(shader_programs[1], "transform");
		float speed = 0.05f - t*0.001f;
		float footX = 0.0f;
		footY = footY + speed;
		footZ = footZ+0.02f;
		vmath::vec3 foot(footX, footY, footZ);
		// ī�޶� ��Ʈ���� ���
		float distance = 2.f;
		if (footZ >= 44.0f || footY >= 14.0f || footY <= 0.0f) {
			t = 0;
			footY = 4.0f;
			footZ = 0.0f;
		}
		if (10.6f >= footZ && footZ >= 10.4f) {
			if (4.0f < footY || footY < 2.7f) {
				t = 0;
				footY = 4.0f;
				footZ = 0.0f;
			}
		}
		if (21.1f >= footZ && footZ >= 20.9f) {
			if (10.0f < footY || footY < 8.7f) {
				t = 0;
				footY = 4.0f;
				footZ = 0.0f;
			}
		}
		if (31.6f >= footZ && footZ >= 31.4f) {
			if (7.0f < footY || footY < 5.7f) {
				t = 0;
				footY = 4.0f;
				footZ = 0.0f;
			}
		}
		if (42.1f >= footZ && footZ >= 41.9f) {
			if (10.0f < footY || footY < 8.7f) {
				t = 0;
				footY = 4.0f;
				footZ = 0.0f;
			}
		}
		//vmath::vec3 eye((float)cos(currentTime*0.3f)*distance, 1.0, (float)sin(currentTime*0.3f)*distance);
		vmath::vec3 eye(footX-2.0f, footY+2.0f, footZ-distance);
		//vmath::vec3 center(0.0, 0.0, 0.0);
		vmath::vec3 up(0.0, 1.0, 0.0);
		vmath::mat4 lookAt = vmath::lookat(eye, vmath::vec3(footX, footY, footZ+1.0f), up);
		float fov = 50.f;// (float)cos(currentTime)*20.f + 50.0f;
		vmath::mat4 projM = vmath::perspective(fov, (float)info.windowWidth / (float)info.windowHeight, 0.1f, 1000.0f);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glEnable(GL_DEPTH_TEST);
		// FBO�� ����� ���۵��� ���� �����, ���� �׽��� Ȱ��ȭ
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// �ٴ� �׸��� ---------------------------------------
		
		glUseProgram(shader_programs[0]);
		glUniformMatrix4fv(glGetUniformLocation(shader_programs[0], "transform"), 1, GL_FALSE, projM*lookAt*vmath::scale(1.5f));
		glUniform1i(glGetUniformLocation(shader_programs[0], "texture1"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glBindVertexArray(VAOs[0]);
		glDrawElements(GL_TRIANGLES, 56, GL_UNSIGNED_INT, 0);


		// ������ ���� ---------------------------------------
		vmath::vec3 pointLightPos[] = { vmath::vec3((float)sin(currentTime*0.5f), 0.25f, (float)cos(currentTime*0.5f) * 0.7f),
										vmath::vec3(0.25f, (float)sin(currentTime*1.f), (float)cos(currentTime*1.f) * 0.7f), 
										vmath::vec3((float)cos(currentTime * 1.5f)*0.7f, (float)sin(currentTime * 1.5f) * 0.7f, 0.25f) };
		vmath::vec3 pointLightColors[] = { vmath::vec3(0.f, 1.f, 0.f),
											vmath::vec3(0.f, 1.f, 0.f),
											vmath::vec3(0.f, 1.f, 0.f) };
		vmath::vec3 lightColor(1.0f, 1.0f, 1.0f);
		vmath::vec3 viewPos = foot;
		float angle = currentTime * 100;

		// �ڽ� �׸��� ---------------------------------------
		/*vmath::mat4 transM = vmath::translate(vmath::vec3((float)sin(currentTime*0.5f), 0.0f, (float)cos(currentTime*0.5f) * 0.7f));
		float angle = currentTime * 100;
		vmath::mat4 rotateM = vmath::rotate(angle, 0.0f, 1.0f, 0.0f);

		glUseProgram(shader_programs[1]);

		glUniformMatrix4fv(glGetUniformLocation(shader_programs[1], "projection"), 1, GL_FALSE, projM);
		glUniformMatrix4fv(glGetUniformLocation(shader_programs[1], "view"), 1, GL_FALSE, lookAt);

		glUniform3fv(glGetUniformLocation(shader_programs[1], "viewPos"), 1, viewPos);

		float shininess = 32.f;
		glUniform1f(glGetUniformLocation(shader_programs[1], "material.shininess"), shininess);
		glUniform1i(glGetUniformLocation(shader_programs[1], "material.diffuse"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glUniform1i(glGetUniformLocation(shader_programs[1], "material.specular"), 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[2]);

		glUniform3f(glGetUniformLocation(shader_programs[1], "dirLight.direction"), -1.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(shader_programs[1], "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(shader_programs[1], "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(shader_programs[1], "dirLight.specular"), 0.5f, 0.5f, 0.5f);

		glUniform3fv(glGetUniformLocation(shader_programs[1], "pointLights[0].position"), 1, pointLightPos[0]);
		glUniform3fv(glGetUniformLocation(shader_programs[1], "pointLights[0].ambient"), 1, pointLightColors[0] * 0.05f);
		glUniform3fv(glGetUniformLocation(shader_programs[1], "pointLights[0].diffuse"), 1, pointLightColors[0]);
		glUniform3fv(glGetUniformLocation(shader_programs[1], "pointLights[0].specular"), 1, pointLightColors[0]);
		glUniform1f(glGetUniformLocation(shader_programs[1], "pointLights[0].c1"), 0.09f);
		glUniform1f(glGetUniformLocation(shader_programs[1], "pointLights[0].c2"), 0.032f);
		glUniform3fv(glGetUniformLocation(shader_programs[1], "pointLights[1].position"), 1, pointLightPos[1]);
		glUniform3fv(glGetUniformLocation(shader_programs[1], "pointLights[1].ambient"), 1, pointLightColors[1] * 0.05f);
		glUniform3fv(glGetUniformLocation(shader_programs[1], "pointLights[1].diffuse"), 1, pointLightColors[1]);
		glUniform3fv(glGetUniformLocation(shader_programs[1], "pointLights[1].specular"), 1, pointLightColors[1]);
		glUniform1f(glGetUniformLocation(shader_programs[1], "pointLights[1].c1"), 0.09f);
		glUniform1f(glGetUniformLocation(shader_programs[1], "pointLights[1].c2"), 0.032f);
		glUniform3fv(glGetUniformLocation(shader_programs[1], "pointLights[2].position"), 1, pointLightPos[2]);
		glUniform3fv(glGetUniformLocation(shader_programs[1], "pointLights[2].ambient"), 1, pointLightColors[2] * 0.05f);
		glUniform3fv(glGetUniformLocation(shader_programs[1], "pointLights[2].diffuse"), 1, pointLightColors[2]);
		glUniform3fv(glGetUniformLocation(shader_programs[1], "pointLights[2].specular"), 1, pointLightColors[2]);
		glUniform1f(glGetUniformLocation(shader_programs[1], "pointLights[2].c1"), 0.09f);
		glUniform1f(glGetUniformLocation(shader_programs[1], "pointLights[2].c2"), 0.032f);

		glUniform3fv(glGetUniformLocation(shader_programs[1], "spotLight.position"), 1, eye);
		glUniform3fv(glGetUniformLocation(shader_programs[1], "spotLight.direction"), 1, center - eye);
		glUniform1f(glGetUniformLocation(shader_programs[1], "spotLight.cutOff"), (float)cos(vmath::radians(12.5)));
		glUniform1f(glGetUniformLocation(shader_programs[1], "spotLight.outerCutOff"), (float)cos(vmath::radians(15.5)));
		glUniform1f(glGetUniformLocation(shader_programs[1], "spotLight.c1"), 0.09f);
		glUniform1f(glGetUniformLocation(shader_programs[1], "spotLight.c2"), 0.032f);
		glUniform3f(glGetUniformLocation(shader_programs[1], "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(shader_programs[1], "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(shader_programs[1], "spotLight.specular"), 1.0f, 1.0f, 1.0f);

		glBindVertexArray(VAOs[1]);

		for (int i = 0; i < boxPositions.size(); i++)
		{
			float angle = 20.f * i;
			vmath::mat4 model = vmath::translate(boxPositions[i]) *
				vmath::rotate(angle, 1.0f, 0.3f, 0.5f) *
				vmath::scale(1.0f);
			glUniformMatrix4fv(glGetUniformLocation(shader_programs[1], "model"), 1, GL_FALSE, model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}*/



		// �Ƕ�̵� �׸��� ---------------------------------------
		glUseProgram(shader_programs[2]);

		glUniformMatrix4fv(glGetUniformLocation(shader_programs[2], "projection"), 1, GL_FALSE, projM);
		glUniformMatrix4fv(glGetUniformLocation(shader_programs[2], "view"), 1, GL_FALSE, lookAt);
		glUniform3fv(glGetUniformLocation(shader_programs[2], "viewPos"), 1, eye);

		glUniform3f(glGetUniformLocation(shader_programs[2], "dirLight.direction"), -1.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(shader_programs[2], "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(shader_programs[2], "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(shader_programs[2], "dirLight.specular"), 0.5f, 0.5f, 0.5f);

		glUniform3fv(glGetUniformLocation(shader_programs[2], "pointLights[0].position"), 1, pointLightPos[0]);
		glUniform3f(glGetUniformLocation(shader_programs[2], "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(shader_programs[2], "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(shader_programs[2], "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(shader_programs[2], "pointLights[0].c1"), 0.09f);
		glUniform1f(glGetUniformLocation(shader_programs[2], "pointLights[0].c2"), 0.032f);
		glUniform3fv(glGetUniformLocation(shader_programs[2], "pointLights[1].position"), 1, pointLightPos[1]);
		glUniform3f(glGetUniformLocation(shader_programs[2], "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(shader_programs[2], "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(shader_programs[2], "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(shader_programs[2], "pointLights[1].c1"), 0.09f);
		glUniform1f(glGetUniformLocation(shader_programs[2], "pointLights[1].c2"), 0.032f);
		

		glUniform3fv(glGetUniformLocation(shader_programs[2], "spotLight.position"), 1, eye);
		glUniform3fv(glGetUniformLocation(shader_programs[2], "spotLight.direction"), 1, foot - eye);
		glUniform1f(glGetUniformLocation(shader_programs[2], "spotLight.cutOff"), (float)cos(vmath::radians(12.5)));
		glUniform1f(glGetUniformLocation(shader_programs[2], "spotLight.outerCutOff"), (float)cos(vmath::radians(15.5)));
		glUniform1f(glGetUniformLocation(shader_programs[2], "spotLight.c1"), 0.09f);
		glUniform1f(glGetUniformLocation(shader_programs[2], "spotLight.c2"), 0.032f);
		glUniform3f(glGetUniformLocation(shader_programs[2], "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(shader_programs[2], "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(shader_programs[2], "spotLight.specular"), 1.0f, 1.0f, 1.0f);

		vmath::mat4 model =  vmath::translate(footX, footY, footZ) *
			vmath::rotate(180.f, 0.0f, 1.0f, 0.0f) *
			vmath::scale(0.15f);
		glUniformMatrix4fv(glGetUniformLocation(shader_programs[2], "model"), 1, GL_FALSE, model);
		objModel.draw(shader_programs[2]);
		glBindVertexArray(VAOs[2]);

		for (int i = 0; i < 3; i++)
		{
			glUniform3fv(glGetUniformLocation(shader_programs[2], "color"), 1, pointLightColors[i]);
			//float scaleFactor = 0.01f;
			//vmath::mat4 transform = vmath::translate(pointLightPos[i])*
			//						vmath::rotate(angle*0.5f, 0.0f, 1.0f, 0.0f)*
			//						vmath::scale(scaleFactor, scaleFactor, scaleFactor);
			//glUniformMatrix4fv(glGetUniformLocation(shader_programs[2], "model"), 1, GL_FALSE, transform);
			//glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);
		// ���۵��� �� �����
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// FBO Texture�� ���̴� ���α׷��� ����
		glUseProgram(shader_program_screen);
		glUniform1i(glGetUniformLocation(shader_program_screen, "screenTexture"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, FBO_texture);
		glBindVertexArray(VAO_screen);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		

	}
	virtual void onKey(int key, int action) {
		if (action == GLFW_PRESS) {
			switch (key) {
				case ' ':
					t = 0;
					break;
				default:
					break;
			}
		}
	}
	void onResize(int w, int h)
	{
		sb7::application::onResize(w, h);
	}

private:
	GLuint shader_programs[3];
	GLuint shader_program_screen;
	GLuint VAOs[3], VBOs[3], EBOs[2];
	GLuint FBO, FBO_texture;
	GLuint VAO_screen, VBO_screen;
	GLuint textures[3];
	Model objModel;
	std::vector<vmath::vec3> boxPositions;
	int t = 0;
	float footY = 4.0f;
	float footZ = 0.0f;
};

// DECLARE_MAIN�� �ϳ����� �ν��Ͻ�
DECLARE_MAIN(my_application)