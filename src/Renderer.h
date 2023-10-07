#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Block.h"
#include "texture.h"

namespace Renderer {


	extern GLuint VBO, VAO, EBO;
	extern bool hasInitialised;

	void initialise();

	namespace block {

		void render(Block::object b);
	}
}

#endif // !RENDERER_H

