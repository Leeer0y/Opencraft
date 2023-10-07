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

#include "Renderer.h"
#include "Block.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// Settings
Settings settings;

// Camera
Camera cam(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f));

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = settings.g_scrWidth / 2;
float lastY = settings.g_scrHeight / 2;

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
    glfwSetCursorPosCallback(window, mouse_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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


    Renderer::initialise();
    Block::object b(glm::vec3(0, 0, 0));

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
        Renderer::block::render(b);



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &Renderer::VAO);
    glDeleteBuffers(1, &Renderer::VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    float cameraSpeed = static_cast<float>(3 * deltaTime);

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

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = ypos - lastY;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch -= yoffset;

    // ensure pitch is within bounds so screen doesnt get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    cam.SetDir(front);
    
}
