//Creamos las importaciones necesarias
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader_s.h>
#include <stb_image.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ctime>
#include <sys\timeb.h> 

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 900;

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

    // build and compile our shaders programs
    // ------------------------------------
    Shader ourShader("3.3.shader.vs", "3.3.shader.fs"); // Shader figura normales
    Shader texturaShader("4.1.texture.vs", "4.1.texture.fs"); //Shader para la textura
    Shader transformacionShader("5.1.transform.vs", "5.1.transform.fs");//shader para las transformaciones

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float laberinto[] = {
        // x    y     z     r      g     b      textura
        //primero
        -0.62f, 0.6f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 
        -0.62f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.58f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

        -0.58f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,    
        -0.58f, 0.6f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,0.0f ,    
        -0.62f, 0.6f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f,0.0f,    

        //segundo
        -1.0f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.2f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.2f,  0.24f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

        -1.0f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.2f,  0.24f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,0.0f ,
        -1.0f,  0.24f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f,

         //tercero
        -0.24f, 0.2f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.24f, 0.64f, 0.0f, 0.0, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.2f,  0.64f, 0.0f, 0.0, 0.0f, 1.0f, 1.0f, 1.0f,

        -0.2f, 0.64f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.2f,  0.2f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,0.0f ,
        -0.24f,  0.2f, 0.0f,  0.0f, 0.0f, 1.0f,0.0f,0.0f,

          //cuarto
        -0.24f, 0.6f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.24f, 0.64f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.2f,  0.64f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,

        0.2f, 0.64f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.2f,  0.6f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,0.0f ,
        -0.24f,  0.6f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f,0.0f,

        // quinto
        -0.64f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f,0.0f,0.0f,
        -0.64f, -0.16f, 0.0f, 1.0f, 0.0f, 0.0f,0.0f,1.0f,
        -0.6f, -0.16f, 0.0f, 1.0f, 0.0f, 0.0f,1.0f,1.0f,

        -0.6f, -0.16f, 0.0f, 1.0f, 0.0f, 0.0f,1.0f,1.0f,
        -0.6f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f,1.0f,0.0f,
        -0.64f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f,0.0f,0.0f,

        //sexto
        -0.64f, -0.2f, 0.0f, 0.5154f, 0.0f, 0.5154f,0.0f,0.0f,
        -0.64f, -0.16f, 0.0f,  0.5154f, 0.0f, 0.5154f,0.0f,1.0f,
        0.2f, -0.16f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,1.0f,

        0.2f, -0.16f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,1.0f,
        0.2f, -0.2f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,0.0f,
        -0.64f, -0.2f, 0.0f,  0.5154f, 0.0f, 0.5154f,0.0f,0.0f,

        //septimo
        0.16f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f,0.0f,
        0.16f, 0.22f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f,1.0f,
        0.2f, 0.22f, 0.0f, 0.0f, 0.0f, 1.0f,1.0f,1.0f,

        0.2f, 0.22f, 0.0f, 0.0f, 0.0f, 1.0f,1.0f,1.0f,
        0.2f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f,1.0f,0.0f,
        0.16f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f,0.0f,

        //octavo
        0.16f, 0.18f, 0.0f, 0.0f, 0.3608f, 0.0f,0.0f,0.0f,
        0.16f, 0.22f, 0.0f,0.0f, 0.3608f, 0.0f,0.0f,1.0f,
        1.0f, 0.22f, 0.0f,0.0f, 0.3608f, 0.0f,1.0f,1.0f,

        1.0f, 0.22f, 0.0f, 0.0f, 0.3608f, 0.0f,1.0f,1.0f,
        1.0f, 0.18f, 0.0f, 0.0f, 0.3608f, 0.0f,1.0f,0.0f,
        0.16f, 0.18f, 0.0f, 0.0f, 0.3608f, 0.0f,0.0f,0.0f,

        //noveno
        0.6f, 0.18f, 0.0f, 1.0f, 0.0f, 0.0f,0.0f,0.0f,
        0.6f, 0.6f, 0.0f, 1.0f, 0.0f, 0.0f,0.0f,1.0f,
        0.64f, 0.6f, 0.0f, 1.0f, 0.0f, 0.0f,1.0f,1.0f,

        0.64f, 0.6f, 0.0f, 1.0f, 0.0f, 0.0f,1.0f,1.0f,
        0.64f, 0.18f, 0.0f, 1.0f, 0.0f, 0.0f,1.0f,0.0f,
        0.6f, 0.18f, 0.0f, 1.0f, 0.0f, 0.0f,0.0f,0.0f,

        //decimo
        -0.2f, -0.64f, 0.0f, 0.5154f, 0.0f, 0.5154f,0.0f,0.0f,
        -0.2f, -0.6f, 0.0f,  0.5154f, 0.0f, 0.5154f,0.0f,1.0f,
        0.64f, -0.6f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,1.0f,

        0.64f, -0.6f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,1.0f,
        0.64f, -0.64f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,0.0f,
        -0.2f, -0.64f, 0.0f,  0.5154f, 0.0f, 0.5154f,0.0f,0.0f,

        //once
        0.6f, -0.64f, 0.0f, 0.5154f, 0.0f, 0.5154f,0.0f,0.0f,
        0.6f, -0.2f, 0.0f,  0.5154f, 0.0f, 0.5154f,0.0f,1.0f,
        0.64f, -0.2f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,1.0f,

        0.64f, -0.2f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,1.0f,
        0.64f, -0.64f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,0.0f,
        0.6f, -0.64f, 0.0f,  0.5154f, 0.0f, 0.5154f,0.0f,0.0f,

        //doce
        0.6f, -0.24f, 0.0f, 0.5154f, 0.0f, 0.5154f,0.0f,0.0f,
        0.6f, -0.2f, 0.0f,  0.5154f, 0.0f, 0.5154f,0.0f,1.0f,
        0.64f, -0.2f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,1.0f,

        0.64f, -0.2f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,1.0f,
        0.64f, -0.64f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,0.0f,
        0.6f, -0.64f, 0.0f,  0.5154f, 0.0f, 0.5154f,0.0f,0.0f,

        //trece
        0.96f, 0.18f, 0.0f, 0.5154f, 0.0f, 0.5154f,0.0f,0.0f,
        0.96f, 1.0f, 0.0f,  0.5154f, 0.0f, 0.5154f,0.0f,1.0f,
        1.0f, 1.0f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,1.0f,

        1.0f, 1.0f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,1.0f,
        1.0f, 0.18f, 0.0f,  0.5154f, 0.0f, 0.5154f,1.0f,0.0f,
        0.96f, 0.18f, 0.0f,  0.5154f, 0.0f, 0.5154f,0.0f,0.0f,

        //catorce
        0.96f, -1.0f, 0.0f, 0.5154f, 0.0f, 0.5154f, 0.0f, 0.0f,
        0.96f, -0.2f, 0.0f, 0.5154f, 0.0f, 0.5154f, 0.0f, 1.0f,
        1.0f, -0.2f, 0.0f, 0.5154f, 0.0f, 0.5154f, 1.0f, 1.0f,

        1.0f, -0.2f, 0.0f, 0.5154f, 0.0f, 0.5154f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 0.5154f, 0.0f, 0.5154f, 1.0f, 0.0f,
        0.96f, -1.0f, 0.0f, 0.5154f, 0.0f, 0.5154f, 0.0f, 0.0f,

        //15
        -1.0f, -1.0f, 0.0f, 0.5154f, 0.0f, 0.5154f, 0.0f, 0.0f,
        -1.0f, -0.96f, 0.0f, 0.5154f, 0.0f, 0.5154f, 0.0f, 1.0f,
        1.0f, -0.96f, 0.0f, 0.5154f, 0.0f, 0.5154f, 1.0f, 1.0f,

        1.0f, -0.96f, 0.0f, 0.5154f, 0.0f, 0.5154f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 0.5154f, 0.0f, 0.5154f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.5154f, 0.0f, 0.5154f, 0.0f, 0.0f,

        //16
       -1.0f, -1.0f, 0.0f, 0.5154f, 0.0f, 0.5154f, 0.0f, 0.0f,
       -1.0f, 0.6f, 0.0f, 0.5154f, 0.0f, 0.5154f, 0.0f, 1.0f,
       -0.96f, 0.6f, 0.0f, 0.5154f, 0.0f, 0.5154f, 1.0f, 1.0f,

        -0.96f, 0.6f, 0.0f, 0.5154f, 0.0f, 0.5154f, 1.0f, 1.0f,
        -0.96f, -1.0f, 0.0f, 0.5154f, 0.0f, 0.5154f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.5154f, 0.0f, 0.5154f, 0.0f, 0.0f,

        //17
        -1.0f, 0.96f, 0.0f, 0.5154f, 0.0f, 0.5154f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.5154f, 0.0f, 0.5154f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 0.5154f, 0.0f, 0.5154f, 1.0f, 1.0f,

        1.0f, 1.0f, 0.0f, 0.5154f, 0.0f, 0.5154f, 1.0f, 1.0f,
        1.0f, 0.96f, 0.0f, 0.5154f, 0.0f, 0.5154f, 1.0f, 0.0f,
        -1.0f, 0.96f, 0.0f, 0.5154f, 0.0f, 0.5154f, 0.0f, 0.0f,

        
    };

    float fantasmas[]{
        //x  y  z  r g  b 
        //fantasma1
         0.294f, 0.7505f, 0.0f, 1.0f, 0.5f, 0.0f,
        0.43f, 0.85f, 0.0f, 1.0f, 0.5f, 0.0f, 
        0.434f, 0.699f, 0.0f, 1.0f, 0.5f, 0.0f, 

        //fantasma2
         -0.853f, -0.067f, 0.0f,1.0f, 0.5f, 0.0f,
        -0.751f, 0.0655f, 0.0f,1.0f, 0.5f, 0.0f,
        -0.693f, -0.023f, 0.0f, 1.0f, 0.5f, 0.0f,

        //fantasma3
         0.686f, -0.687f, 0.0f,1.0f, 0.5f, 0.0f,
        0.672f, -0.793f, 0.0f,1.0f, 0.5f, 0.0f,
        0.8f, -0.8f, 0.0f, 1.0f, 0.5f, 0.0f,
    };

    //fruta magica
    float frutaMagica[]{
        0.712f, -0.037f, 0.0f,0.9059f, 0.2980f, 0.2353f,
        0.712f, 0.053f, 0.0f,0.9059f, 0.2980f, 0.2353f,
        0.828f, 0.053f, 0.0f, 0.9059f, 0.2980f, 0.2353f,

         0.828f, 0.053f, 0.0f,0.9059f, 0.2980f, 0.2353f,
        0.828f, -0.037f, 0.0f,0.9059f, 0.2980f, 0.2353f,
        0.712f, -0.037f, 0.0f, 0.9059f, 0.2980f, 0.2353f,
    };

    //pintura original
    //Colores a usar:
    // rojo: 1.0f, 0.0f, 0.0f
    // amarillo: 1.0f, 1.0f, 0.0f
    // azul: 0.0f, 0.2f, 1.0f
    // naranja: 1.0f, 0.5f, 0.0f
    // morado: 0.63f, 0.28f, 0.64f
    // verde: 0.0f, 0.56f, 0.223f
    // negro: 0.0f, 0.0f, 0.0f
    float vertices[]{
        //x,y,z,r,g,b
        0.4544f,   0.1835f,   0.0f, 0.63f, 0.28f, 0.64f,//triangulo figura 1
        0.4850f,  -0.9828f,   0.0f, 0.63f, 0.28f, 0.64f,
       -0.6000f,  -1.0000f,   0.0f, 0.63f, 0.28f, 0.64f,
        0.8505f,   0.7554f,   0.0f, 1.0f, 1.0f, 0.0f,//pac man figura 2
        0.0348f,   0.7554f,   0.0f, 1.0f, 1.0f, 0.0f,
        0.8505f,  -0.4372f,   0.0f, 1.0f, 1.0f, 0.0f,
        0.0348f,  -0.4372f,   0.0f, 1.0f, 1.0f, 0.0f,
       -0.6000f,  -1.0000f,   0.0f, 0.0f, 0.56f, 0.223f,//triangulo figura 3
       -0.8000f,  -1.0000f,   0.0f, 0.0f, 0.56f, 0.223f,
       -0.6703f,  -0.7167f,   0.0f, 0.0f, 0.56f, 0.223f,
       -0.8659f,  -0.8574f,   0.0f, 0.63f, 0.28f, 0.64f,//triangulo figura 4
       -0.8085f,  -0.7267f,   0.0f, 0.63f, 0.28f, 0.64f,
       -0.7191f,  -0.9584f,   0.0f, 0.63f, 0.28f, 0.64f,
       -0.3344f,   0.1285f,   0.0f, 1.0f, 0.5f, 0.0f,//triangulo figura 5
       -0.0396f,   0.3207f,   0.0f, 1.0f, 0.5f, 0.0f,
       -0.4000f,   0.5000f,   0.0f, 1.0f, 0.5f, 0.0f,
       -0.5334f,   0.1666f,   0.0f, 1.0f, 0.5f, 0.0f,//triangulo figura 6
       -0.4263f,   0.5410f,   0.0f, 1.0f, 0.5f, 0.0f,
       -0.4263f,   0.5410f,   0.0f, 1.0f, 0.5f, 0.0f,
       -0.5715f,   0.1513f,   0.0f, 1.0f, 1.0f, 0.0f,//rectangulo figura 7
       -0.4110f,   0.1666f,   0.0f, 1.0f, 1.0f, 0.0f,
       -0.5810f,   0.0616f,   0.0f, 1.0f, 1.0f, 0.0f,
       -0.4053f,   0.0845f,   0.0f, 1.0f, 1.0f, 0.0f,
       -0.4053f,   0.0845f,   0.0f, 1.0f, 0.0f, 0.0f,//rectangulo figura 8
       -0.4015f,   0.3653f,   0.0f, 1.0f, 0.0f, 0.0f,
       -0.3327f,   0.3691f,   0.0f, 1.0f, 0.0f, 0.0f,
       -0.3404f,   0.1246f,   0.0f, 1.0f, 0.0f, 0.0f,
       -0.2125f,   0.5169f,   0.0f, 1.0f, 1.0f, 0.0f,//triangulo figura 9 
       -0.2885f,   0.5573f,   0.0f, 1.0f, 1.0f, 0.0f,
       -0.2579f,   0.3675f,   0.0f, 1.0f, 1.0f, 0.0f,
       -0.1082f,   0.1327f,   0.0f, 0.0f, 0.56f, 0.223f,//rectangulo figura 10
       -0.0618f,   0.4959f,   0.0f, 0.0f, 0.56f, 0.223f,
        0.4482f,   0.1772f,   0.0f, 0.0f, 0.56f, 0.223f,
        0.4482f,   0.5009f,   0.0f, 0.0f, 0.56f, 0.223f,
        0.8129f,   0.2247f,   0.0f, 0.63f, 0.28f, 0.64f,//triangulo figura 11
        0.3283f,   0.2474f,   0.0f, 0.63f, 0.28f, 0.64f,
        0.6991f,   0.9210f,   0.0f, 0.63f, 0.28f, 0.64f,
        0.7426f,  -0.0518f,   0.0f, 0.0f, 0.0f, 0.0f,//triangulo figura 12 (sonrisa PacMan)
        0.6607f,  -0.2414f,   0.0f, 0.0f, 0.0f, 0.0f,
        0.5180f,  -0.4487f,   0.0f, 0.0f, 0.0f, 0.0f,
        0.5031f,   0.1201f,   0.0f, //rectangulo ojo PacMan figura 13
        0.3996f,   0.1194f,   0.0f,
        0.5031f,   0.2594f,   0.0f,
        0.3996f,   0.2594f,   0.0f,
       -0.6502f,   0.7063f,   0.0f, 0.0f, 0.2f, 1.0f,//rectangulo figura 14
       -0.6169f,   0.7742f,   0.0f, 0.0f, 0.2f, 1.0f,
       -0.1583f,   0.4849f,   0.0f, 0.0f, 0.2f, 1.0f,
       -0.1413f,   0.6335f,   0.0f, 0.0f, 0.2f, 1.0f,
       -0.1583f,   0.4849f,   0.0f, 0.0f, 0.2f, 1.0f,//rectangulo figura 15
       -0.1413f,   0.6335f,   0.0f, 0.0f, 0.2f, 1.0f,
        0.0609f,   0.6530f,   0.0f, 0.0f, 0.2f, 1.0f,
        0.0048f,   0.7310f,   0.0f, 0.0f, 0.2f, 1.0f,
        0.0609f,   0.6530f,   0.0f, 0.0f, 0.2f, 1.0f,//rectangulo figura 16
        0.0048f,   0.7310f,   0.0f, 0.0f, 0.2f, 1.0f,
        0.2661f,   1.0000f,   0.0f, 0.0f, 0.2f, 1.0f,
        0.2000f,   1.0000f,   0.0f, 0.0f, 0.2f, 1.0f
    };


    //PACMAN
    float radio = 0.115f;
    float centro_x = -0.8f;
    float centro_y = 0.8f;
    int numSegments = 500;

    std::vector<float> verticesCirculoCentro;
    for (int i = 0; i <= numSegments; i++) {
        float angulo = i * 2.0f * 3.14159f / numSegments;
        float x = (cos(angulo) * radio)  + centro_x;
        float y = (sin(angulo) * radio) + centro_y; // Compensación en y
        verticesCirculoCentro.push_back(x);
        verticesCirculoCentro.push_back(y);
        verticesCirculoCentro.push_back(0.0f);
        verticesCirculoCentro.push_back(1.0f);
        verticesCirculoCentro.push_back(1.0f);
        verticesCirculoCentro.push_back(0.0f);
    }

    //ojo de PACMAN
    radio = 0.0115f;
    centro_x = -0.75f;
    centro_y = 0.85f;

    std::vector<float> verticesCirculoCentro2;
    for (int i = 0; i <= numSegments; i++) {
        float angulo = i * 2.0f * 3.14159f / numSegments;
        float x = (cos(angulo) * radio) + centro_x;
        float y = (sin(angulo) * radio) + centro_y; // Compensación en y
        verticesCirculoCentro2.push_back(x);
        verticesCirculoCentro2.push_back(y);
        verticesCirculoCentro2.push_back(0.0f);
        verticesCirculoCentro2.push_back(0.0f);
        verticesCirculoCentro2.push_back(0.0f);
        verticesCirculoCentro2.push_back(0.0f);
    }

    /*Creamos los buffers, nota yo cree un buffer para cada figura, ya que siento que me da más control para
    lograr que se puedan aplicar mis shaders a una figura específica y así tendría más control de mi programa*/

    // laberinto
    unsigned int laberintoVBO, laberintoVAO;
    glGenVertexArrays(1, &laberintoVAO);
    glGenBuffers(1, &laberintoVBO);
    glBindVertexArray(laberintoVAO);

    glBindBuffer(GL_ARRAY_BUFFER, laberintoVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(laberinto), laberinto, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texturas
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //Creamos la imagen de la textura, aqui solo sera aplicado para el laberinto
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
    unsigned char* data = stbi_load("C:/Users/Djcho/OneDrive/Documentos/ITAM/Semestre_7/GráficasPorComputadora/Proyecto1/Proyect1_2DAnimation/src/ProyectoOpenGL_glfw/Fotos/roca3.jpg", &width, &height, &nrChannels, 0);
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

   
    //buffers de pacman
    unsigned int pacmanVBO, pacmanVAO;
    glGenVertexArrays(1, &pacmanVAO);
    glGenBuffers(1, &pacmanVBO);
    glBindVertexArray(pacmanVAO);

    glBindBuffer(GL_ARRAY_BUFFER, pacmanVBO);
    glBufferData(GL_ARRAY_BUFFER, verticesCirculoCentro.size() * sizeof(float), &verticesCirculoCentro[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //buffers de ojo de pacman
    unsigned int ojoPacmanVBO, ojoPacmanVAO;
    glGenVertexArrays(1, &ojoPacmanVAO);
    glGenBuffers(1, &ojoPacmanVBO);
    glBindVertexArray(ojoPacmanVAO);

    glBindBuffer(GL_ARRAY_BUFFER, ojoPacmanVBO);
    glBufferData(GL_ARRAY_BUFFER, verticesCirculoCentro2.size() * sizeof(float), &verticesCirculoCentro2[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //buffers de fantasmas
    unsigned int fantasmaVBO, fantasmaVAO;
    glGenVertexArrays(1, &fantasmaVAO);
    glGenBuffers(1, &fantasmaVBO);
    glBindVertexArray(fantasmaVAO);

    glBindBuffer(GL_ARRAY_BUFFER, fantasmaVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fantasmas), fantasmas, GL_STATIC_DRAW);

    // Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    
    
    //buffers de la frutaMagica
    unsigned int frutaVBO, frutaVAO;
    glGenVertexArrays(1, &frutaVAO);
    glGenBuffers(1, &frutaVBO);
    glBindVertexArray(frutaVAO);

    glBindBuffer(GL_ARRAY_BUFFER, frutaVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(frutaMagica), frutaMagica, GL_STATIC_DRAW);

    // Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    
    struct timeb start, end;
    unsigned short elapse = 0, t1, t2;
    float animationTime = 0.0f;
    float animationSpeed = 0.01f; // Ajusta la velocidad de la animación según sea necesario
    ftime(&start);
    t1 = start.millitm;


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        //pone el color de la ventana
        glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture, para la textura
        glBindTexture(GL_TEXTURE_2D, texture);

        // render el del laberinto
        texturaShader.use(); //llamamos al shader de las texturas
        glBindVertexArray(laberintoVAO);
        glDrawArrays(GL_TRIANGLES, 0, 17*6);
        glBindVertexArray(0);
        glUseProgram(0);
        ourShader.use(); //llamamos al Shader que nos carga las figuras normal

        //Render pacman
        glBindVertexArray(pacmanVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments + 1);

        //Render ojo pacman
        glBindVertexArray(ojoPacmanVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments + 2);

       //render fantasmas

        ftime(&end);
        t2 = end.millitm;
        elapse = t2 - t1;

        // Si ha pasado un milisegundo, actualiza la animación
        if (elapse > 1) {
            t1 = t2;
            animationTime += animationSpeed * elapse; // Ajusta la velocidad multiplicando por el tiempo transcurrido
        }

        float tiempoTranscurrido = glfwGetTime();

        if (tiempoTranscurrido <= 15.0f) {
            glm::mat4 modeloFantasma = glm::mat4(1.0f);
            float velocidadRotacion = 0.7f;
            float anguloRotacion = glm::radians(tiempoTranscurrido * velocidadRotacion);

            modeloFantasma = glm::rotate(modeloFantasma, anguloRotacion, glm::vec3(0.0f, 0.0f, 1.0f));
            transformacionShader.use();
            unsigned int modelLoc = glGetUniformLocation(transformacionShader.ID, "transform");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modeloFantasma));
            glBindVertexArray(fantasmaVAO);
            glDrawArrays(GL_TRIANGLES, 0, 3 * 3);
        }

        glBindVertexArray(fantasmaVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3 * 3);
        
        //render frutaMagica
        glBindVertexArray(frutaVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
        glDeleteVertexArrays(1, &laberintoVAO);
        glDeleteBuffers(1, &laberintoVBO);
       
        glDeleteVertexArrays(1, &pacmanVAO);
        glDeleteBuffers(1, &pacmanVBO);

        glDeleteVertexArrays(1, &fantasmaVAO);
        glDeleteBuffers(1, &fantasmaVBO);

        glDeleteVertexArrays(1, &frutaVAO);
        glDeleteBuffers(1, &frutaVBO);
        
        /*glDeleteVertexArrays(1, &VAO9);
        glDeleteBuffers(1, &VBO9);*/
        
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
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
