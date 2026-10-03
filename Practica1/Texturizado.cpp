//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//Practica #7 											  Ruiz Vargas Ricardo
//Fecha de entrega: 02 de octubre de 2026 							316226068
//
//



#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"
#include "Camera.h"


// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

// Light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

							// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 7 - Ricardo_Ruiz_Vargas", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);


	// Build and compile our shader program
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");				//Los archivos que se agregaron en Shader

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =													//Definición de los vertices del plano a manejar
	{
		// Positions            // Colors              // Texture Coords
		-0.5f, -0.5f, 0.0f,    1.0f, 1.0f,1.0f,		0.31f,0.31f,		//0.0f,0.0f,
		0.5f, -0.5f, 0.0f,	   1.0f, 1.0f,1.0f,		0.55f,0.31f,		//1.0f,0.0f,
		0.5f,  0.5f, 0.0f,     1.0f, 1.0f,1.0f,	    0.55f,0.54f,		//1.0f,1.0f,
		-0.5f,  0.5f, 0.0f,    1.0f, 1.0f,1.0f,		0.31f,0.54f,		//0.0f,1.0f,
		
		// Cara derecha
		0.5f, -0.5f,  0.5f,    1.0f, 1.0f,1.0f,		0.31f,0.55f,		// 4
		0.5f, -0.5f, -0.5f,	   1.0f, 1.0f,1.0f,		0.55f,0.55f,		// 5
		0.5f,  0.5f, -0.5f,    1.0f, 1.0f,1.0f,	    0.55f,0.80f,		// 6
		0.5f,  0.5f,  0.5f,    1.0f, 1.0f,1.0f,		0.31f,0.80f,		// 7

		// cara atras
		 0.5f, -0.5f, -0.5f,   1.0f, 1.0f,1.0f,		0.56f,0.31f,		// 8
		-0.5f, -0.5f, -0.5f,   1.0f, 1.0f,1.0f,		0.80f,0.31f,		// 9
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f,1.0f,	    0.80f,0.54f,		// 10
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,1.0f,		0.56f,0.54f,		// 11

		// cara izquierda
		-0.5f, -0.5f, -0.5f,   1.0f, 1.0f,1.0f,		0.31f,0.05f,		// 12
		-0.5f, -0.5f,  0.5f,   1.0f, 1.0f,1.0f,		0.55f,0.05f,		// 13
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f,1.0f,	    0.55f,0.30f,		// 14
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f,1.0f,		0.31f,0.30f,		// 15

		//cara arriba
		-0.5f, 0.5f,  0.5f,   1.0f, 1.0f,1.0f,		0.06f,0.31f,		// 16
		 0.5f, 0.5f,  0.5f,   1.0f, 1.0f,1.0f,		0.30f,0.31f,		// 17
		 0.5f, 0.5f, -0.5f,   1.0f, 1.0f,1.0f,	    0.30f,0.54f,		// 18
		-0.5f, 0.5f, -0.5f,   1.0f, 1.0f,1.0f,		0.06f,0.54f,		// 19

		//cara abajo
		-0.5f, -0.5f, -0.5f,   1.0f, 1.0f,1.0f,		0.68f,0.67f,		// 20
		 0.5f, -0.5f, -0.5f,   1.0f, 1.0f,1.0f,		0.92f,0.67f,		// 21
		 0.5f, -0.5f,  0.5f,   1.0f, 1.0f,1.0f,	    0.92f,0.91f,		// 22
		-0.5f, -0.5f,  0.5f,   1.0f, 1.0f,1.0f,		0.68f,0.91f,		// 23

	};

	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,3,
		1,2,3,		//6

		4,5,6,
		6,7,4,		//12

		8,9,10,
		10,11,8,	//18

		12,13,14,
		14,15,12,	//24

		16,17,18,
		18,19,16,	//30

		20,21,22,
		22,23,20	//36
	
	};

	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	//---------------------------------------------------------------------------------------------------------------------------
	// Load textures						//Carga de las texturas -------------------------------------------------------------
	GLuint texture1;							//identificador de la textura
	glGenTextures(1, &texture1);				//enlace del identificador la textura con el tipo de elemento (textura)
	glBindTexture(GL_TEXTURE_2D,texture1);
	int textureWidth, textureHeight,nrChannels;
	stbi_set_flip_vertically_on_load(true);		//volteo de la textura (para corregir el volteo de la libreria)
	unsigned char *image;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Diffuse map - - - - - - - - -
	image = stbi_load("images/checker_Tex.png", &textureWidth, &textureHeight, &nrChannels,0);		//Carga de la ruta de la texturA
	glBindTexture(GL_TEXTURE_2D, texture1);		// se vincula ahora si la imagen con el identificador
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);	//RGBA para transparecnia
	glGenerateMipmap(GL_TEXTURE_2D);			//optimizar recursos segun la distancia
	if (image)
	{									//RGBA para transparecnia					  |/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

	//---------------------------------------------------------------------------------------------------------------------------
	//Carga de la textura2 ------------------------------------------------------------------------------------------------------
	GLuint texture2;							//identificador de la textura
	glGenTextures(1, &texture2);				//enlace del identificador la textura con el tipo de elemento (textura)
	glBindTexture(GL_TEXTURE_2D, texture2);
	//int textureWidth, textureHeight, nrChannels;
	//stbi_set_flip_vertically_on_load(true);		//volteo de la textura (para corregir el volteo de la libreria)
	//unsigned char* image;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Diffuse map - - - - - - - - - -
	image = stbi_load("images/SuperMario64-BowserPaint-NOtransparente.jpg", &textureWidth, &textureHeight, &nrChannels, 0);		//Carga de la ruta de la texturA
	glBindTexture(GL_TEXTURE_2D, texture2);		// se vincula ahora si la imagen con el identificador
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);	//RGBA para transparecnia
	glGenerateMipmap(GL_TEXTURE_2D);			//optimizar recursos segun la distancia
	if (image)
	{									//RGBA para transparecnia					  |/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	//---------------------------------------------------------------------------------------------------------------------------
	//Carga de la textura3 ------------------------------------------------------------------------------------------------------
	GLuint texture3;							//identificador de la textura
	glGenTextures(1, &texture3);				//enlace del identificador la textura con el tipo de elemento (textura)
	glBindTexture(GL_TEXTURE_2D, texture3);
	//int textureWidth, textureHeight, nrChannels;
	//stbi_set_flip_vertically_on_load(true);		//volteo de la textura (para corregir el volteo de la libreria)
	//unsigned char* image;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Diffuse map - - - - - - - - - -
	image = stbi_load("images/ZeldaOoT-Castle-flower.png", &textureWidth, &textureHeight, &nrChannels, 0);		//Carga de la ruta de la texturA
	glBindTexture(GL_TEXTURE_2D, texture3);		// se vincula ahora si la imagen con el identificador
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);	//RGBA para transparecnia
	glGenerateMipmap(GL_TEXTURE_2D);			//optimizar recursos segun la distancia
	if (image)
	{									//RGBA para transparecnia					  |/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	//---------------------------------------------------------------------------------------------------------------------------
	//Carga de la textura DADO --------------------------------------------------------------------------------------------------
	GLuint texture5;							//identificador de la textura
	glGenTextures(1, &texture5);				//enlace del identificador la textura con el tipo de elemento (textura)
	glBindTexture(GL_TEXTURE_2D, texture5);
	//int textureWidth, textureHeight, nrChannels;
	//stbi_set_flip_vertically_on_load(true);		//volteo de la textura (para corregir el volteo de la libreria)
	//unsigned char* image;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Diffuse map - - - - - - - - - -
	image = stbi_load("images/dado-colorido.jpg", &textureWidth, &textureHeight, &nrChannels, 0);		//Carga de la ruta de la texturA
	glBindTexture(GL_TEXTURE_2D, texture5);		// se vincula ahora si la imagen con el identificador
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);	//RGBA para transparecnia
	glGenerateMipmap(GL_TEXTURE_2D);			//optimizar recursos segun la distancia
	if (image)
	{									//RGBA para transparecnia					  |/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		// Clear the colorbuffer
		glClearColor(0.5333f, 0.5765f, 0.5765f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lampShader.Use();								//Activar Shader
		//// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 model(1);
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lampShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lampShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lampShader.Program, "projection");

		//Textura 1 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		// Bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);									//No hacen falta
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));		//pero quiero dejarlo
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(VAO);													//para ver la guia de la 
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);					//cual partió la primera
		glBindVertexArray(0);													//carda (frente) del dado


		// Previo - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		//Textura 2 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		//model = glm::mat4(1.0f);					// <--- REINICIO DE MATRIZ
		//model = glm::translate(model, glm::vec3(-1.1f, 0.0f, 0.2f));
		//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		////																		//Redundancia de al usar el canal. "es como
		////glActiveTexture(GL_TEXTURE0);						-->					//decirle a una puerta abierta que se abra."
		//glBindTexture(GL_TEXTURE_2D, texture2);
		////
		////glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));		//se están volviendo a enviar las matrices
		////glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));	//	--> son pa ra la cámara
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));		
		////
		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);

		////Textura 3 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		//model = glm::mat4(1.0f);					// <--- REINICIO DE MATRIZ
		//model = glm::translate(model, glm::vec3(1.1f, 0.0f, 0.2f));
		//model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		////
		//glBindTexture(GL_TEXTURE_2D, texture3);
		////se actualizaa ÚNICAMENTE el uniform 'modelLoc' en el shader para esta nueva posición
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		////
		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);

		////Textura 4 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		//model = glm::mat4(1.0f);					// <--- REINICIO DE MATRIZ
		//model = glm::translate(model, glm::vec3(0.0f, 1.1f, 0.2f));
		//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		////
		//glBindTexture(GL_TEXTURE_2D, texture1);
		////se actualizaa ÚNICAMENTE el uniform 'modelLoc' en el shader para esta nueva posición
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		////
		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);


		// Practica - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		//Lado 1 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - FRENTE
		model = glm::mat4(1.0f);					// <--- REINICIO DE MATRIZ
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f));
		//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//
		glBindTexture(GL_TEXTURE_2D, texture5);
		//se actualizaa ÚNICAMENTE el uniform 'modelLoc' en el shader para esta nueva posición
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//Lado 2 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - DERECHA
		model = glm::mat4(1.0f);					// <--- REINICIO DE MATRIZ
		//model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//
		glBindTexture(GL_TEXTURE_2D, texture5);
		//se actualizaa ÚNICAMENTE el uniform 'modelLoc' en el shader para esta nueva posición
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)));/////////////////
		glBindVertexArray(0);
		
		//Lado 3 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ATRAS
		model = glm::mat4(1.0f);					// <--- REINICIO DE MATRIZ
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.5f));
		//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//
		glBindTexture(GL_TEXTURE_2D, texture5);
		//se actualizaa ÚNICAMENTE el uniform 'modelLoc' en el shader para esta nueva posición
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(unsigned int)));
		glBindVertexArray(0);

		//Lado 4 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - IZQUIERDA
		model = glm::mat4(1.0f);					// <--- REINICIO DE MATRIZ
		//model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//
		glBindTexture(GL_TEXTURE_2D, texture5);
		//se actualizaa ÚNICAMENTE el uniform 'modelLoc' en el shader para esta nueva posición
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(unsigned int)));
		glBindVertexArray(0);

		//Lado 5 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ARRIBA
		model = glm::mat4(1.0f);					// <--- REINICIO DE MATRIZ
		//model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//
		glBindTexture(GL_TEXTURE_2D, texture5);
		//se actualizaa ÚNICAMENTE el uniform 'modelLoc' en el shader para esta nueva posición
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(unsigned int)));
		glBindVertexArray(0);

		//Lado 6 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ABAJO
		model = glm::mat4(1.0f);					// <--- REINICIO DE MATRIZ
		//model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//
		glBindTexture(GL_TEXTURE_2D, texture5);
		//se actualizaa ÚNICAMENTE el uniform 'modelLoc' en el shader para esta nueva posición
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));
		glBindVertexArray(0);



		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}