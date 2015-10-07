#include <iostream>
#include <GLFW/glfw3.h>

#include <Crawler\Common.h>

GLOBAL const int g_windowWidth  = 654;
GLOBAL const int g_windowHeight = 400;

int main(int argv, char** argc)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return EXIT_FAILURE;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(
	    g_windowWidth, g_windowHeight, "Crawler", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	bool running    = true;
	bool fullscreen = false;

	/* Loop until the user closes or presses escape */
	while (running)
	{
		glClearColor(0.5f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Closes window */
		if (glfwWindowShouldClose(window) ||
		    glfwGetKey(window, GLFW_KEY_ESCAPE))
			running = false;

		/* Fullscreen window */
		if (glfwGetKey(window, GLFW_KEY_F11))
		{
			fullscreen = !fullscreen;

			GLFWwindow* newWindow;

			if (fullscreen)
			{
				int modeCount;
				const GLFWvidmode* modes =
				    glfwGetVideoModes(glfwGetPrimaryMonitor(), &modeCount);

				newWindow = glfwCreateWindow(modes[modeCount - 1].width,
				                             modes[modeCount - 1].height,
				                             "Crawler",
				                             glfwGetPrimaryMonitor(),
				                             window);
			}
			else
			{
				newWindow = glfwCreateWindow(
				    g_windowWidth, g_windowHeight, "Crawler", nullptr, window);
			}

			glfwDestroyWindow(window);
			window = newWindow;
			glfwMakeContextCurrent(window);
		}
	}

	/* Destroys the window */
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
