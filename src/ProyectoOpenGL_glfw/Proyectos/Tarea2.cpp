#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <shader_m.h>
#include <shader_s.h>
#include <stb_image.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tarea 2", NULL, NULL);
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

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("4.1.texture.vs", "4.1.texture.fs");

    //Para examen se usa esta parte 
    /*float vertices[] = {
        // positions          // colors           // texture coords
         0.5,  0.5, 0.0,  1.0, 0.0, 0.0,  4.0, 4.0,  // top right
         0.5, -0.5, 0.0,  0.0, 1.0, 0.0,  4.0, 0.0,  // bottom right
        -0.5, -0.5, 0.0,  0.0, 0.0, 1.0,  0.0, 0.0,  // bottom left
        -0.5,  0.5, 0.0,  1.0, 1.0, 0.0,  0.0, 4.0    //top left
    };*/

    float vertices[] = {
        // positions                // colors           // texture coords
        -0.9687f, -0.3437f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        -0.2187f, -0.7187f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
         0.3750f,  0.0625f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.1718f,  0.3843f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left
        -0.3750f, -0.0312f, 0.0f,  
        -0.3750f, -0.4156f, 0.0f,
         0.1250f, -0.4156f, 0.0f,
         0.1250f, -0.0312f, 0.0f,//
        -1.0000f, -0.7812f, 0.0f,
        -1.0000f, -0.9156f, 0.0f,
        -0.4375f, -0.7812f, 0.0f,
        -0.4375f, -0.9156f, 0.0f,//
         0.4375f,  0.0343f, 0.0f,
         1.0000f,  0.0343f, 0.0f,
         0.4375f, -0.9406f, 0.0f,
         1.0000f, -0.9406f, 0.0f,//
         0.4375f,  0.0343f, 0.0f,
         0.6562f,  0.0343f, 0.0f,
         0.4375f, -0.4312f, 0.0f,
         0.6562f, -0.4312f, 0.0f//
        -0.0937f,  0.9531f, 0.0f,
         0.4718f,  0.6406f, 0.0f,
        -0.5000f,  0.2937f, 0.0f,
        -0.1250f, -0.0625f, 0.0f,//
         0.6875f,  0.6250f, 0.0f,
         0.6875f, -0.6837f, 0.0f,
        -0.5000f, -0.6387f, 0.0f,
        -0.5000f,  0.6250f, 0.0f,//
        // 0.8281f es el maximo y ; -0.1562f es el minimo
        -0.8531f,  0.8281f, 0.0f, 
        -0.7906f,  0.8281f, 0.0f,
        -0.8531f, -0.1562f, 0.0f,
        -0.7906f, -0.1562f, 0.0f,//
        -0.7750f,  0.8281f, 0.0f,
        -0.7156f,  0.8281f, 0.0f,
        -0.7750f, -0.1562f, 0.0f,
        -0.7156f, -0.1562f, 0.0f,//
        -0.6875f,  0.8281f, 0.0f,
        -0.6250f,  0.8281f, 0.0f,
        -0.6875f, -0.1562f, 0.0f,
        -0.6250f, -0.1562f, 0.0f,//
        -0.5968f,  0.8281f, 0.0f,
        -0.5406f,  0.8281f, 0.0f,
        -0.5968f, -0.1562f, 0.0f,
        -0.5406f, -0.1562f, 0.0f,//
        -0.5281f,  0.8281f, 0.0f,
        -0.4656f,  0.8281f, 0.0f,
        -0.5281f, -0.1562f, 0.0f,
        -0.4656f, -0.1562f, 0.0f,//
        -0.4375f,  0.8281f, 0.0f,
        -0.3750f,  0.8281f, 0.0f,
        -0.4375f, -0.1562f, 0.0f,
        -0.3750f, -0.1562f, 0.0f,//
        -0.3437f,  0.8281f, 0.0f,
        -0.2875f,  0.8281f, 0.0f,
        -0.3437f, -0.1562f, 0.0f,
        -0.2875f, -0.1562f, 0.0f,//
        -0.2718f,  0.8281f, 0.0f,
        -0.2031f,  0.8281f, 0.0f,
        -0.2718f, -0.1562f, 0.0f,
        -0.2031f, -0.1562f, 0.0f//
    };

    /*
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };*/
    unsigned int indices[] = {
        0, 1, 2,    //R1: first triangle
        0, 2, 3,    //R1: second triangle
        4, 5, 6,    //R2: first triangle
        4, 6, 7,    //R2: second triangle
        8, 9, 10,   //R3: first triangle
        9, 10, 11,  //R3: second triangle
        12,13,14,   //R4: first triangle
        13,14,15,   //R4: second triangle
        16,17,18,   //R5: first triangle
        17,18,19,   //R5: second triangle
        20,21,22,   //R6: first triangle
        21,22,23,   //R6: second triangle
        24,25,26,   //R7: first triangle
        24,26,27,   //R7: second triangle
        28,29,30,   //R8: first triangle
        29,30,31,   //R8: second triangle
        32,33,34,   //R9: first triangle
        32,34,35,   //R9: second triangle
        36,37,38,   //R10: first triangle
        36,38,39,   //R10: second triangle
        40,41,42,   //R11: first triangle
        40,42,43,   //R11: second triangle
        44,45,46,   //R12: first triangle
        44,46,47,   //R12: second triangle
        48,49,50,   //R13: first triangle
        48,50,51,   //R13: second triangle
        52,53,54,   //R14: first triangle
        52,54,55,   //R14: second triangle
        56,57,58,   //R15: first triangle
        56,58,59    //R15: second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    stbi_set_flip_vertically_on_load(true); 
    unsigned char* data = stbi_load("C:/Users/Djcho/OneDrive/Documentos/roca3.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}