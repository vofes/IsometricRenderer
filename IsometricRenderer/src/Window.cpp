#include "Window.h"

GLFWwindow* Window::m_ID;

void Window::CreateWindow()
{
	/* Initialize the library */
	if (!glfwInit())
		return;

	/* Specify version of OpenGL */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	Window::m_ID = glfwCreateWindow(640 * 2, 360 * 2, "Isometric Renderer", NULL, NULL);
	if (!Window::m_ID)
	{
		glfwTerminate();
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(Window::m_ID);

	/* fps limitation to V-SYNC*/
	glfwSwapInterval(1);

	// Needs to be after context is created!!!
	GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cout << "Error: \n" << glewGetErrorString(err) << std::endl;

	// Printing out OpenGL version
	std::cout << glGetString(GL_VERSION) << std::endl;
}

void Window::CloseWindow()
{
	glfwTerminate();
}