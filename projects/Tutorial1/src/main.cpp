#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
	//Initialize GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Failed to initialize Glad" << std::endl;
		return 1;
	}
	// Create a new GLFW window
	GLFWwindow* window = glfwCreateWindow(300, 300, "100746949", nullptr, nullptr);
	//We want GL commands to be executed for our window, so we make our window's context
	glfwMakeContextCurrent(window);

	//Let glad know what function loader we are using (will cancel gl commands via glfw
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
	{
		std::cout << "Failed to initialize Glad" << std::endl;
		return 2;
	}

	//Display our GP and OpenGL version
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	//Run as png as the window is open
	while (!glfwWindowShouldClose(window))
	{
		//Poll for events from windows (clicks, keypressed, closing, all that
		glfwPollEvents();

		//Clear our screen every frame
		glClearColor(0.4f, 0.2f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Present our image window
		glfwSwapBuffers(window);
	}

	return 0;
}