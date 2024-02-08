#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

/*
	Main Program
	---
	Generates an orange rectangle in a window
*/
int main()
{
	/*
		Initialize and configure GLFW
	*/
	glfwInit();

	// Specify OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*
		Initialize and configure GLAD
	*/

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*
		Build and compile shaders and shader program
	*/
	Shader ourShader("/root/opengl_workshop/src/00_getting_started/01_hello_triangle/01_vertex.glsl", "/root/opengl_workshop/src/00_getting_started/01_hello_triangle/01_fragment.glsl");

	/*
		Vertices for rectangle to be drawn
	*/
	float vertices[] = {
        // positions         // colors
       -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // bottom right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom left
        0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f  // top
	};

	/*
		Create buffer objects and add vertex data
	*/

	// Make OpenGL array buffer
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	// Add vertex data to vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    // Color attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

	// Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO
	glBindVertexArray(0);

	// Set fill mode to fill/wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Use GL_FILL for fill or GL_LINE for wireframe

	/*
		Render loop
		---
		Renders images repeatedly
	*/
	while (!glfwWindowShouldClose(window))
	{
		// Process IO inputs
		processInput(window);

		// Renders objects
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // background
		glClear(GL_COLOR_BUFFER_BIT);

		// Activate shader program
		ourShader.use();

        // Draw triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Poll events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// De-allocated resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// Delete/clean all GLFW resources
	glfwTerminate();
	return 0;
}

/*
	Resize viewport when window is resized.
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*
	Process inputs
*/
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
