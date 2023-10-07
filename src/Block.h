#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Block {
	struct object {
		object(glm::vec3 p) {
			position = p;
		}
		glm::vec3 position;
	};
}

#endif // !BLOCK_H
