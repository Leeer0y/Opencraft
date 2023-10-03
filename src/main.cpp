#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "settings.h"

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

#include <vector>

#include "shader.h"
#include "texture.h"
#include "camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Settings
Settings settings;

// Camera
Camera cam(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f));

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(settings.g_scrWidth, settings.g_scrHeight, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // Shader init
    Shader ourShader(RESOURCES_PATH "baseCube.vert", RESOURCES_PATH "baseCube.frag");

    //glUseProgram(shaderProgram);


        // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    // cube verticies
    /*
    glm::vec3 cubeVerticies[] = {
        // front
        glm::vec3(-0.5, -0.5, 0.5), // 0
        glm::vec3(-0.5, 0.5, 0.5), // 1
        glm::vec3(0.5, 0.5, 0.5), // 2
        glm::vec3(0.5, -0.5, 0.5), // 3
        // back
        glm::vec3(-0.5, -0.5, -0.5), // 4
        glm::vec3(-0.5, 0.5, -0.5), // 5
        glm::vec3(0.5, 0.5, -0.5), // 6
        glm::vec3(0.5, -0.5, -0.5) // 7
    }; */

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


    unsigned int indicies[] = {
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

    // Buffers

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerticies), cubeVerticies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Textures
    Texture grassTop(GL_TEXTURE_2D, RESOURCES_PATH "grass_top.jpg");
    Texture dirt(GL_TEXTURE_2D, RESOURCES_PATH "dirt.png", 4);
    grassTop.Load();
    dirt.Load();


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // Rendering here
        glClearColor(0.1f, 0.1f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        // Create transformations
        cam.SetProjection(&ourShader, settings.g_fov, settings.g_scrWidth / settings.g_scrHeight, 0.1f, 100.0f);
        cam.CalculateViewMatrix(&ourShader);

        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        ourShader.setMat4("model", model);



        // render container
        
        // for each side of cube
        for (int i = 0; i <= 6; i++) {
            if (i == 5) {
                grassTop.BindTexture(GL_TEXTURE0);
            }
            else {
                dirt.BindTexture(GL_TEXTURE0);
            }
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6*i, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    float cameraSpeed = static_cast<float>(2.5 * deltaTime);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.SetPosition(cam.GetPosition() + cameraSpeed * cam.GetFront());
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.SetPosition(cam.GetPosition() - cameraSpeed * cam.GetFront());
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.SetPosition(cam.GetPosition() - (glm::normalize(glm::cross(cam.GetFront(), cam.GetUp())) * cameraSpeed));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.SetPosition(cam.GetPosition() + (glm::normalize(glm::cross(cam.GetFront(), cam.GetUp())) * cameraSpeed));

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    settings.g_scrWidth = width;
    settings.g_scrHeight = height;
}