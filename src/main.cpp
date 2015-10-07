#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Crawler\Common.h>

GLOBAL const int g_windowWidth  = 654;
GLOBAL const int g_windowHeight = 400;

void glfwHints()
{
	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);
}

int main(int argv, char** argc)
{
	GLFWwindow* window;

	if (!glfwInit())
		return EXIT_FAILURE;

	glfwHints();

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

	/* Initialize the library */
	glewInit();

	float vertices[] = {
	    +0.0f, +0.5f, // first vertex
	    -0.5f, -0.5f, // second vertex
	    +0.5f, -0.5f // third vertex
	};

	GLuint vbo; // vertex buffer object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	const char* vertexShaderText = {
	    "#version 120\n"
	    "\n"
	    "attribute vec2 position"
	    "void main()"
	    "{"
	    "	gl_Position = vec4(position, 0.0, 1.0);"
	    "}"
	};

	const char* fragmentShaderText = {
	    "#version 120\n"
	    "\n"
	    "void main()"
	    "{"
	    "	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
	    "}"
	};

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindAttribLocation(shaderProgram, 0, "position");

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	bool running    = true;
	bool fullscreen = false;

	/* Loop until the user closes or presses escape */
	while (running)
	{
		glClearColor(0.5f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* Draw Things */
		{
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDisableVertexAttribArray(0);
		}

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

			glfwHints();

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
