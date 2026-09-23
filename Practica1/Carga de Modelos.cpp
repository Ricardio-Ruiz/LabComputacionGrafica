//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//Practica #6 											  Ruiz Vargas Ricardo
//Fecha de entrega: 27 de septiembre de 2026 				        316226068
//
//


// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 2.0f ) );             //posicion, al colocar ( 0.0f, 0.0f, 0.0f ), nos "mete" dentro del modelo
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;



int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Practica 6 - Ricardo_Ruiz_Vargas", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shader/modelLoading.vs", "Shader/modelLoading.frag" );
    
    // Load models
    Model dog((char*)"Models/Perro/RedDog.obj");                    //Carga de ruta y nombre del objeto
    //Model kolog1((char*)"Models/Kolog1FBX/korok.fbx");
    //Model kologOBJ((char*)"Models/Kolog1OBJ/kolog1-obj.obj");         //fbx cambiado a obj
    //Model kologFBX((char*)"Models/Kolog1FBX/kolog1-fbx.fbx");         //fbx cambiando las rutas para que inccluya las texturas
    //Model metroid((char*)"Models/Metroid/metroid.obj");
    //Model zinnia((char*)"Models/Zinnia/zinnia.obj");
    //Model majora((char*)"Models/Majora/majora.obj");
    Model laptop((char*)"Models/MacBook_blend/MacBookPro_blend.fbx");
    //Model mouse((char*)"Models/scene_101724/scene.obj");
    Model lentes((char*)"Models/glasses/LentesdeLeer.fbx");


    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
  

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 model(1);
        model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        dog.Draw(shader);                   //Aqui ya se carga el modelo 

        /*model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.5f)); 
        model = glm::scale(model, glm::vec3(1.5f,0.8f,2.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        dog.Draw(shader);                   //perro chato

        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -4.0f));
        model = glm::scale(model, glm::vec3(9.5f, 13.0f, 0.8f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        dog.Draw(shader);*/                 //perro gigante


        //Cargando modelos propios
        //////unsigned int texturaCuerpo, texturaHoja;

        //model = glm::translate(model, glm::vec3(-1.0f, -0.44f, -0.2f)); 
        //model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.18f));
        //model = glm::rotate(model,glm::radians(-2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //kologOBJ.Draw(shader);                  //Kolog OBJ

        //model = glm::translate(model, glm::vec3(4.9f, 5.9f, 0.2f));
        //model = glm::scale(model, glm::vec3(0.18f, 0.25f, 0.27f));
        //model = glm::rotate(model, glm::radians(-7.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //kologFBX.Draw(shader);                  //Kolog FBX

        //model = glm::translate(model, glm::vec3(-18.0f, 4.0f, -1.8f));
        //model = glm::scale(model, glm::vec3(9.25f, 9.25f, 4.0f));
        //model = glm::rotate(model, glm::radians(-18.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //metroid.Draw(shader);                   //Metroid

        //////model = glm::rotate(model, glm::radians(40.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //model = glm::translate(model, glm::vec3(-3.7f, -2.4f, -1.7f)); 
        //model = glm::scale(model, glm::vec3(3.0f, 2.0f, 2.5f));
        //model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //zinnia.Draw(shader);                    //Zinnia

        //model = glm::rotate(model, glm::radians(92.0f), glm::vec3(+1.0f, 0.0f, 0.0f));
        //model = glm::translate(model, glm::vec3(1.92f, 0.4f, -0.8f));
        //model = glm::scale(model, glm::vec3(0.14f, 0.13f, 0.15f)); 
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //majora.Draw(shader);                    //Majora



        //PRACTICA
        //model = glm::rotate(model, glm::radians(92.0f), glm::vec3(+1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(1.92f, 0.4f, -0.8f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        laptop.Draw(shader);                    //Laptop

        //model = glm::rotate(model, glm::radians(92.0f), glm::vec3(+1.0f, 0.0f, 0.0f));
        ///*model = glm::translate(model, glm::vec3(-1.92f, 0.4f, -0.8f));
        //model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f)); 
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //mouse.Draw(shader);   */                 //mouse

        //model = glm::rotate(model, glm::radians(92.0f), glm::vec3(+1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(-13.92f, -3.4f, 5.8f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f)); 
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lentes.Draw(shader);                    //lentes


        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

   
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

 

 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

