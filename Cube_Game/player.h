#include "libs.h"

class Player {
public:
	unsigned int VBO, VAO, EBO;

	Player(float vertices[], size_t vertexSize, unsigned int indices[], size_t indexSize) {

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);

	}

	glm::vec3 rotationAxis = glm::vec3(0.f, 1.f, 0.f);
	glm::mat4 transform = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f);
	float moveSpeed = 0.007f;
	float strafeSpeed = 0.005f;
	float acc = 1.01f;
	float full = moveSpeed;

	float rotateDeg = 50.f;

	float bottomBound = -1.0f;  // = -0.95f
	float topBound = 1.7f;   
	float leftBound = -1.0f;
	float rightBound = 1.0f + 0.02f;


	void draw(Shader& shader) {
		unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void moveRight() {
		if (position.x + strafeSpeed < 0.95f) {
			position.x += strafeSpeed;
			transform = glm::mat4(1.0f);
			transform = glm::translate(transform, position);
		}
		std::cout << position.x << "\n";
	}

	void moveLeft() {
		if (position.x - strafeSpeed > -0.95f) {
			position.x -= strafeSpeed;
			transform = glm::mat4(1.0f);
			transform = glm::translate(transform, position);
		}
		std::cout << position.x << "\n";
	}

	void moveUp() {
		if (position.y + full < topBound) {  
			position.y += full;
			full *= acc;
			if (full > 1.1f) full = 1.1f;
			transform = glm::mat4(1.0f);
			transform = glm::translate(transform, position);
		}
		std::cout << position.y << "\n";
	}

	void moveDown() {
		if (position.y - full > 0.01f) {
			position.y -= full;
			full /= acc;
			if (full < moveSpeed) full = moveSpeed;
			transform = glm::mat4(1.0f);
			transform = glm::translate(transform, position);
		}
		std::cout << position.y << "\n";
	}

	void dealloc() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

};

