#include "OpenGl.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "Shaders.h"
#include "Texture.h"
#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "ObjLoader.h"

int OpenGl::start() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::vector<GLfloat> vertices = {
        // positions          // texture coords
          0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  // top right 0
          0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  // bottom right 1
         -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  // bottom left 2
         -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // top left 3
    };
    std::vector<GLuint> indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
	

	GLFWwindow* window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

    glm::vec3 cameraPos = { 0,0,0 };

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, 600, 600);
    glEnable(GL_DEPTH_TEST);

    Shader shader("VertexShader.vert","FragmentShader.frag");

    ObjData mesh = loadObj("monkey.obj");
    std::vector<GLfloat> tris = mesh.tris;

    VertexArrayObject vao;
   
    BufferObject vbo(GL_ARRAY_BUFFER, tris);
    //BufferObject ebo(GL_ELEMENT_ARRAY_BUFFER, indices);

    GLsizei stride = 5 * sizeof(GLfloat);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader.Use();
    
    Texture texture1("monkeytex.png",0);

    

    shader.setInt("texture1", 0);

    glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::translate(trans, glm::vec3(0.0, 0.0, 10.0));
    trans = glm::rotate(trans, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
    trans = glm::rotate(trans, glm::radians(20.0f), glm::vec3(1.0, 0.0, 0.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    GLuint transformLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    GLuint cameraLoc = glGetUniformLocation(shader.ID, "cameraPos");
    glUniform3f(cameraLoc, 1,GL_FALSE,cameraPos[0]);

    while (!glfwWindowShouldClose(window))
    {

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos.z++;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos.z--;

        glUniform3f(cameraLoc, 1, GL_FALSE, cameraPos[0]);
        //trans = glm::rotate(trans, glm::radians(1.0f), glm::vec3(1.0, 0.5, 0.0));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture1.Use();
        shader.Use();

        vao.Bind();
        //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, tris.size() / 5);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}

