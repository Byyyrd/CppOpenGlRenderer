#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"OpenGl.h"

#define check(x) if(x != 0){return -1;}

void mouse_callback(GLFWwindow * window, double xpos, double ypos);
void scroll_callback(GLFWwindow * window, double xpos, double ypos);

OpenGl gl;

int main() {
	gl = OpenGl();
	GLFWwindow* window;
	check(gl.createWindow(800, 600, window));
	
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	gl.start(window);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	gl.mouse_callback(window, xpos, ypos);
}
void scroll_callback(GLFWwindow* window, double xpos, double ypos) {
	gl.scroll_callback(window, xpos, ypos);
}
