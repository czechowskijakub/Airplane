#include "libs.h"
#include "player.h"

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {

	int windowHeight = 600;
	int windowWidth = 800;

	glewExperimental = GL_TRUE;
	
	// init glfw
	glfwInit();
	// opengl config; which version // 4.4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	// setting it to core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// window creation
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Cube game", NULL, NULL);
	if (window == NULL) {
		std::cout << "FAILED TO CREATE A GLFW WINDOW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
		return -1;
	}
	
	Shader Quad("vertex_core.glsl", "fragment_core.glsl");

	float player_1[] = {
		// positions          // colors           
		 0.0f, -0.82f, 0.0f,  0.3f, 0.3f, 1.0f,	
		 0.0f, -0.90f, 0.0f,  0.3f, 0.3f, 1.0f,	
		-0.03f,-0.95f, 0.0f,  0.3f, 0.3f, 1.0f,	
		 0.03f,-0.95f, 0.0f,  0.3f, 0.3f, 1.0f,	
		 //0.03f,-0.943f, 0.0f, 0.3f, 0.3f, 1.0f,
		//-0.03f,-0.943f, 0.0f, 0.3f, 0.3f, 1.0f
	};

	unsigned int indices_1[] = {
		0, 1, 2, // first triangle
		0, 1, 3,  // second triangle
	};

	Player Plane(player_1, sizeof(player_1), indices_1, sizeof(indices_1));

	// render loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// Movement logic
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			Plane.moveUp();
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			Plane.moveDown();
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			Plane.moveRight();
			Plane.rotateDeg += 0.75f;
			if (Plane.rotateDeg > 50.f) Plane.rotateDeg = 50.f;
			Plane.transform = glm::rotate(Plane.transform, glm::radians(Plane.rotateDeg), Plane.rotationAxis);
		} else {
			Plane.rotateDeg -= 0.25f;
			if (Plane.rotateDeg < 0) Plane.rotateDeg = 0;
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			Plane.moveLeft();
			Plane.rotateDeg += 1.25f;
			if (Plane.rotateDeg > 50.f) Plane.rotateDeg = 50.f;
			Plane.transform = glm::rotate(Plane.transform, glm::radians(Plane.rotateDeg), Plane.rotationAxis);
		} else {
			Plane.rotateDeg -= 0.25f;
			if (Plane.rotateDeg < 0) Plane.rotateDeg = 0;
		}

		Plane.transform = glm::mat4(1.0f);
		Plane.transform = glm::translate(Plane.transform, Plane.position);
		Plane.transform = glm::rotate(Plane.transform, glm::radians(Plane.rotateDeg), Plane.rotationAxis);

		glClearColor(.8f, .8f, .8f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		Quad.use();
		Plane.draw(Quad);
		glActiveTexture(GL_TEXTURE0);

		glfwSwapBuffers(window);						// swap "drawing" plane with a "display plane"
		glfwPollEvents();								// fetch changes, inputs, events
	}

	Plane.dealloc();
	

	glfwTerminate();
	return 0;
}