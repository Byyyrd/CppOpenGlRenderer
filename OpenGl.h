#pragma once

#include <filesystem>
#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders.h"
#include "Texture.h"
#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "ObjLoader.h"
#include "Camera.h"
class OpenGl
{
private:
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);
public: 
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	int createWindow(int width, int height, GLFWwindow*& window);
	int start(GLFWwindow* window);
};