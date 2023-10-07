#include "Renderer.h"


float cubeVerticies[] = {
    // Positions            // Tex coords
    // front
    -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, // 0
    -0.5f, 0.5f, 0.5f,      0.0f, 1.0f, // 1
    0.5f, 0.5f, 0.5f,       1.0f, 1.0f, // 2
    0.5f, -0.5f, 0.5f,      1.0f, 0.0f, // 3
    // back
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, // 4
    -0.5f, 0.5f, -0.5f,     1.0f, 1.0f, // 5
    0.5f, 0.5f, -0.5f,      0.0f, 1.0f, // 6
    0.5f, -0.5f, -0.5f,     0.0f, 0.0f,  // 7
    // top
    0.5f, 0.5f, 0.5f,       0.0f, 0.0f, // 8 (2)
    -0.5f, 0.5f, 0.5f,      1.0f, 0.0f, // 9 (1)
    // bottom
    0.5f, -0.5f, -0.5f,     1.0f, 1.0f,  // 10 (7)
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f // 11 (4)
};


unsigned int cubeIndicies[] = {
    // front face
    0, 1, 2,
    2, 3, 0,
    // back face
    4, 5, 6,
    6, 7, 4,
    // left face
    4, 5, 1,
    1, 0, 4,
    // right face
    7, 6, 2,
    2, 3, 7,
    // top face
    9, 5, 6,
    6, 8, 9,
    // bottom face
    0, 11, 10,
    10, 3, 0
};

Texture grassTop(GL_TEXTURE_2D, RESOURCES_PATH "grass_top.jpg");
Texture dirt(GL_TEXTURE_2D, RESOURCES_PATH "dirt.png", 4);

namespace Renderer {

    GLuint VBO, VAO, EBO;
    bool hasInitialised = false;

    void initialise() {

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerticies), cubeVerticies, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndicies), cubeIndicies, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Textures

        grassTop.Load();
        dirt.Load();
    }

    void block::render(Block::object b) {
        // for each side of cube
        for (int i = 0; i <= 6; i++) {
            if (i == 5) {
                grassTop.BindTexture(GL_TEXTURE0);
            }
            else {
                dirt.BindTexture(GL_TEXTURE0);
            }
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6 * i, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }
}
