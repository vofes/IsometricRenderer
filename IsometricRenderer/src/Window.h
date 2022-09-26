#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
public:
	static GLFWwindow* m_ID;
	static void CreateWindow();
	static void CloseWindow();
private:
};