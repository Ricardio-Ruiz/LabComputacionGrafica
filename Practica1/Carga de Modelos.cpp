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
Camera camera( glm::vec3( 0.0f, 0.5f, 2.2f ) );             //posicion, al colocar ( 0.0f, 0.0f, 0.0f ), nos "mete" dentro del modelo
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
    Model dog((char*)"Models/Perro/perro.obj");                    //Carga de ruta y nombre del objeto
    //Model kolog1((char*)"Models/Kolog1FBX/korok.fbx");
    //Model kologOBJ((char*)"Models/Kolog1OBJ/kolog1-obj.obj");         //fbx cambiado a obj
    //Model kologFBX((char*)"Models/Kolog1FBX/kolog1-fbx.fbx");         //fbx cambiando las rutas para que inccluya las texturas
    //Model metroid((char*)"Models/Metroid/metroid.obj");
    //Model zinnia((char*)"Models/Zinnia/zinnia.obj");
    //Model majora((char*)"Models/Majora/majora.obj");

    //Practica 6
    Model lentes((char*)"Models/P6/LectureGlasses/lentes/lentes7-chick.fbx");
    Model silla((char*)"Models/P6/Silla/silla3.dae");
    Model mesa((char*)"Models/P6/Mesa/mesaZ.obj");
    Model cafe((char*)"Models/P6/Cafe/cafe.fbx");
    Model raton((char*)"Models/P6/LaptopMouse/raton/scene.gltf");
    Model compu((char*)"Models/P6/LaptopMouse/compu/laptop.glb");
    Model sillon((char*)"Models/P6/sillon/sofa.fbx");
    Model cuarto((char*)"Models/P6/habitacion/cuarto.obj");


    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
  

    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //Para el GLB se supone que se debe de cargar el archivo de textura de forma manual
    // Carga manual de la texxtura de la laptop:
    unsigned int compuTextura;
    glGenTextures(1, &compuTextura);
    glBindTexture(GL_TEXTURE_2D, compuTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int widthL, heightL, nrChannelsL;
    //stbi_set_flip_vertically_on_load(true);      // <--- VOLTEA LA IMAGEN
    unsigned char* dataL = stbi_load("Models/P6/LaptopMouse/compu/Image_0-inception-.jpg", &widthL, &heightL, &nrChannelsL, 0);
//    unsigned char* dataL = stbi_load("Models/P6/LaptopMouse/compu/Image_0GG.jpg", &widthL, &heightL, &nrChannelsL, 0);    //Mi pantalla
    if (dataL) {
        GLenum format;
        if (nrChannelsL == 1) format = GL_RED;
        else if (nrChannelsL == 3) format = GL_RGB;
        else if (nrChannelsL == 4) format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, widthL, heightL, 0, format, GL_UNSIGNED_BYTE, dataL);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Fallo al cargar la textura de la compu" << std::endl;
    }
    stbi_image_free(dataL);
    // Inyección manual a todas las mallas del modelo
    for (unsigned int i = 0; i < compu.meshes.size(); i++) {
        compu.meshes[i].textures.clear();    // <--- ESTA LÍNEA ELIMINA LA TEXTURA NEGRA ROTA POR FIN!!        
        Texture texL;
        texL.id = compuTextura;
        texL.type = "texture_diffuse";
        texL.path = "Models/P6/LaptopMouse/compu/Image_0.jpg";
        compu.meshes[i].textures.push_back(texL);
    }
    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -



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

        //cambio de camara
        //view = glm::translate(view, glm::vec3(0.0f, 0.5f, 0.2f));
        //view = glm::rotate(view, glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 model(1);
        
        // Perros del previo / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
        //model = glm::rotate(model, glm::radians(40.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
        //model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //dog.Draw(shader);                   //Aqui ya se carga el modelo 

        /*model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.5f)); 
        model = glm::scale(model, glm::vec3(1.5f,0.8f,2.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        dog.Draw(shader);                   //perro chato

        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -4.0f));
        model = glm::scale(model, glm::vec3(9.5f, 13.0f, 0.8f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        dog.Draw(shader);*/                 //perro gigante


        //Cargando modelos propios / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
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



        //PRACTICA / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
        
        //model = glm::rotate(model, glm::radians(30.0f), glm::vec3(-1.0f, 0.0f, 0.0f)); 
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        //model = glm::rotate(model, glm::radians(8.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        dog.Draw(shader);                       //perro en OBJ      <---     
        
        //model = glm::mat4(1.0f);                // <--- REINICIO DE MATRIZ
        model = glm::translate(model, glm::vec3(0.0f, 0.62f, -0.22f));
        model = glm::rotate(model, glm::radians(-82.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(1.3f, 1.0f, 1.0f)); 
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //glEnable(GL_BLEND);                                     //Agregar la
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);      //transparencia
        lentes.Draw(shader);                    //lentes en FBX     <---
        //glDisable(GL_BLEND);

        model = glm::translate(model, glm::vec3(0.0f, -0.3f, -1.12f));
        model = glm::rotate(model, glm::radians(-8.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(1.3f, 1.0f, 1.0f)); 
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        silla.Draw(shader);                     //silla en DAE      <---

        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.3f, 1.15f, 1.2f)); 
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        mesa.Draw(shader);                      //mesa en OBJ       <---

        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(-0.01f, -0.022f, -0.006f));
        //model = glm::scale(model, glm::vec3(1.3f, 1.15f, 1.2f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cafe.Draw(shader);                      //cafe en FBX       <---

        model = glm::mat4(1.0f);                // <--- REINICIO DE MATRIZ
        model = glm::translate(model, glm::vec3(-0.32f, 0.38f, 0.3f));
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(15.3f, 15.15f, 15.2f));
        model = glm::scale(model, glm::vec3(0.009f, 0.009f, 0.009f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        raton.Draw(shader);                     //raton en GLtF     <---

        model = glm::mat4(1.0f);                // <--- REINICIO DE MATRIZ
        model = glm::translate(model, glm::vec3(-0.0f, 0.388f, 0.55f));
        model = glm::scale(model, glm::vec3(0.05f, 0.07f, 0.07f));
        model = glm::rotate(model, glm::radians(91.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //Forzamiento del uso de la textura extraída
        // Es el entrelazamiento manual de la textura al modelo
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, compuTextura);
        compu.Draw(shader);                     //compu en GLB      <---

        model = glm::mat4(1.0f);                // <--- REINICIO DE MATRIZ
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.5f));
        model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        sillon.Draw(shader);                    //sofa en FBX       <---

        model = glm::mat4(1.0f);                // <--- REINICIO DE MATRIZ
        model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(-4.0f, 0.25f, 0.3f));
        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //glEnable(GL_BLEND);                                     //Agregar la
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);      //transparencia
        cuarto.Draw(shader);                    //cuarto en OBJ     <---
        //glDisable(GL_BLEND); 

        







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

