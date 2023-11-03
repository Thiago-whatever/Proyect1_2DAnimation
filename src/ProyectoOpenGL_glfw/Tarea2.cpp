#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>//operaciones de entrada y salida en c++

//prototipo de una funcion (como la firma)
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//funcion que se pone en el ciclo de renderizacion, captura eventos que llegan a la ventana
//Ejemplo: mouse, teclado
void processInput(GLFWwindow* window);

// settings; tamano de la ventana
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//los shaders
//recibe el in (vec3) y ese vector lo coloca en la variable glPosition con z=0
//le retorna al fragmen el vec4
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//la salida del vertex le pone al fragment
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//version mayor a 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//para que no ejecute nada por debajo del 3.3

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tarea 2", NULL, NULL);
    if (window == NULL)
    {
        //operacion parecida el printf pero en c++
        std::cout << "Failed to create GLFW window" << std::endl;//ejemplo de entrada y salida
        glfwTerminate();
        return -1;
    }
    //definir la ventana actual
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//se avisa que se invoca el visor

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//solicito creación de (lo compilo)
    if (!success)//en caso de error
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//lo creo
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//le asocio un codigo a ese objeto
    //es el mismo codigo pero cambia la entrada (distintas partes de la imagen)
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();//creo un programa
    glAttachShader(shaderProgram, vertexShader);//le asocio a mi programa los dos shaders
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);//hago un link (definirle un lugar específico en la RAM cuando compila codigo)
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {//verifico que no hay errores de link
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //borro el objeto no el codigo
    glDeleteShader(vertexShader);//luego los borro: libero el apuntador (del heap) porque ya estan en el programa
    glDeleteShader(fragmentShader);//y ya no necesito los apuntadores

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    //coordenadas del triangulo
    /*/float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };*/

    float vertices[] = {
        -0.9687f, -0.3437f, 0.0f,   
        -0.2187f, -0.7187f, 0.0f,  
         0.3750f,  0.0625f, 0.0f,  
        -0.1718f,  0.3843f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        0, 2, 3    // second triangle
    };

    unsigned int VBO, VAO;
    //defino como le voy a mandar los datos
    glGenVertexArrays(1, &VAO);//defino un arreglo con los atributos que le voy a mandar a la RAM
    glGenBuffers(1, &VBO);//defino los datos crudos
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //le aviso que desde la posicion 0 hasta la tres en mi arreglo de vertices es un vertice, ...
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    //Activa el gl blend
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_ONE, GL_ONE);//para que el triangulo se viera clarito
    //glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);// para que el triangulo se viera oscuro

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {//75 veces por segundo se va a hacer este ciclo
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);//va a tratar de dibujar el triangulo con el programa
        //se pinta en paralelo
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);//va preparando el siguiente buffer para que cuando se vuelva a reenderizar
        //se ponga de inmediato, (actualizacion del marco), un buffer pintando y otro construyendo la siguiente
        //ventana. 
        glfwPollEvents();//quedate a la espera de eventos
    }

    //Desactiva el glBlend
    //glDisable(GL_BLEND);

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
//captura la tecla escape, cuando la presiono cierra la ventana
//se llama solamente cuando ocurre el evento
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

//cuerpo de la funcion
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
//Ventana asociada a un visor. El visor se ajusta a cuando las cosas se achican o agrandan
//No es que se ajuste a la ventana, se ajusta al visor. El visor se ajusta al tamano de la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}