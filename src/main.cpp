#include "core.h"
#include "shader.h"
#include "window.h"
#include "input.h"
#include "buffers.h"


int main()
{
	if (!glfwInit())
	{
		printf("failed to initialize GLFW\n");
		return -1;
	}

	Window *window = new Window(720, 720, 144, "poard", false);
	window->Initialize();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad";
		glfwTerminate();
		return -1;
	}

	Input::Initialize(window->GLwindow);

	std::cout << "opengl version " << glGetString(GL_VERSION) << "\n" << std::endl;



	GLfloat vertices[] = 
	{	//coords				//colors
		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
		0.5f,  -0.5f, 0.0f,		0.0f, 0.5f, 0.5f,
		0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 0.5f, 0.5f,
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	Shader shader = Shader("../res/shader/vertex.glsl", "../res/shader/fragment.glsl");

	Vao vao = Vao();
	vao.Bind();
	Vbo vbo = Vbo(vertices, sizeof(vertices));
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(float) * 6, (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(float) * 6, (void*)(sizeof(float) * 3));
	Ebo ebo = Ebo(indices, sizeof(indices));
	ebo.Bind();


	unsigned int xPosLocation = glGetUniformLocation(shader.id, "uX");
	glUniform1f(xPosLocation, 0.0f);

	glViewport(0, 0, window->height, window->height);

	shader.Activate();
	while (!glfwWindowShouldClose(window->GLwindow))
	{

		glClear(GL_COLOR_BUFFER_BIT);

		vao.Bind();
		ebo.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		if (Input::isKeyDown(GLFW_KEY_E))
			glUniform1f(xPosLocation, 0.5f);

		glfwSwapBuffers(window->GLwindow);
		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	//ebo.Delete();
	shader.Delete();

	window->Destroy();
	glfwTerminate();
	return 0;
}