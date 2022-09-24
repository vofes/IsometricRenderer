#include <iostream>
#include "stb_image/stb_image.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main()
{
	// Window

	/* Initialize the library */
	if (!glfwInit())
		return false;

	/* Specify version of OpenGL */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(480, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* fps limitation to V-SYNC*/
	glfwSwapInterval(1);

	// Needs to be after context is created!!!
	GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cout << "Error: \n" << glewGetErrorString(err) << std::endl;

	// Printing out OpenGL version
	std::cout << glGetString(GL_VERSION) << std::endl;



	// data
	float positions[] = {
		// position: xyz	uv: xy
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 0
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 1
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // 2
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // 3
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Vertex array
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertex buffer
	// Generate 1 buffer and giving us back an id
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	// Selecting buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), positions, GL_STATIC_DRAW);

	// Vertex layout in buffer
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0); // binds vertex buffer to vertex array
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void*)(sizeof(float) * 3)); // binds vertex buffer to vertex array

	// Index buffer
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// Shaders
	const char* vertexSrc = R"(
	#version 150 core
	in vec3 position;
	in vec2 uv;
	out vec2 v_uv;
	void main()
	{
		gl_Position = vec4(position.x, position.y, position.z, 1.0f);
		v_uv = uv;
	})";

	const char* fragmentSrc = R"(
	#version 150 core
	out vec4 colorOut;
	in vec2 v_uv;

	uniform sampler2D u_texture;

	void main()
	{
		vec4 texColor = texture(u_texture, v_uv);
		colorOut = texColor;
	})";

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertexSrc, nullptr);
	glCompileShader(vs);

	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragmentSrc, nullptr);
	glCompileShader(fs);

	unsigned int shader = glCreateProgram();
	glAttachShader(shader, vs);
	glAttachShader(shader, fs);
	glLinkProgram(shader);
	glValidateProgram(shader);
	glUseProgram(shader);

	glDeleteShader(vs);
	glDeleteShader(fs);

	// Texture
	int imageWidth, imageHeight, BPP;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* imageBuffer = stbi_load("res/grass.png", &imageWidth, &imageHeight, &BPP, 4);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer);

	if (imageBuffer)
		stbi_image_free(imageBuffer);
	unsigned int slot = 0;
	glActiveTexture(GL_TEXTURE0 + slot);

	// Uniform
	int location = glGetUniformLocation(shader, "u_texture");
	if (location == -1)
		return -1;
	glUniform1i(location, slot);

	// Loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// Clean up
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteProgram(shader);
	glDeleteTextures(1, &texture);

	glfwTerminate();

	return 0;
}