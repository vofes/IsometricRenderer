#include <iostream>
#include "stb_image/stb_image.h"
#include "Window.h"
#include "Sprite.h"
#include "World.h"
#include "matrix4/matrix4.h"

int main()
{
	// Window
	Window::CreateWindow();

	// data

	std::vector<Vertex> vertexData;
	std::vector<unsigned int> indexData;

	World world;
	world.GetVertices(&vertexData, &indexData);

	// Vertex array
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnable(GL_DEPTH_TEST);

	// 1 - source alpha = destination alpha
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Vertex buffer
	// Generate 1 buffer and giving us back an id
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	// Selecting buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(Vertex), &vertexData[0], GL_STATIC_DRAW);
	

	// Vertex layout in buffer
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	unsigned int stride = 0;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)stride); // vec3: position
	stride += sizeof(Vector3);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)stride); // vec2: uv
	stride += sizeof(Vector2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)stride); // vec4: color
	stride += sizeof(Vector4);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)stride); // float: textureID
	stride += sizeof(float);

	// Index buffer
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(unsigned int), &indexData[0], GL_STATIC_DRAW);

	// Shaders
	const char* vertexSrc = R"(
	#version 150 core
	in vec3 position; 
	in vec2 uv;
	in vec4 color;
	in float textureID;

	uniform mat4 u_MVP;

	out vec2 v_uv;
	out vec4 v_color;
	out float v_textureID;

	void main()
	{
		gl_Position = u_MVP * vec4(position.x, position.y, position.z, 1.0f);
		v_uv = uv;
		v_color = color;
		v_textureID = textureID;
	})";

	const char* fragmentSrc = R"(
	#version 150 core
	out vec4 colorOut;
	in vec2 v_uv;
	in vec4 v_color;
	in float v_textureID;

	uniform sampler2D u_texture;

	void main()
	{
		vec4 texColor = texture(u_texture, v_uv);
		colorOut = texColor * v_color;
		if (colorOut.a == 0.0)
			discard;
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
	if (location == -1) return -1;
	glUniform1i(location, slot);

	location = glGetUniformLocation(shader, "u_MVP");
	if (location == -1) return -1;
	Matrix4 proj = Matrix4::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -100.0f, 100.0f);
	glUniformMatrix4fv(location, 1, GL_FALSE, proj.getData());

	// Loop
	while (!glfwWindowShouldClose(Window::m_ID))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(Window::m_ID);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// Clean up
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteProgram(shader);
	glDeleteTextures(1, &texture);

	Window::CloseWindow();

	return 0;
}