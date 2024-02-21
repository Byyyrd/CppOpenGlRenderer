#pragma once

#include <filesystem>
#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class OpenGl
{
private:
	int createWindow(int width, int height, GLFWwindow*& window);
	
public: 
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	int start();
};