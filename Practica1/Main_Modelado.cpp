//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//Práctica #4 											  Ruiz Vargas Ricardo
//Fecha de entrega: 12 de septiembre de 2026 				        316226068
//
//

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
float rot2 = 0.0f;
float rot3 = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4 - Ricardo_Ruiz_Vargas", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {
		//-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front	ROJO
		//0.5f, -0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		//0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		//0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		//-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		//-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		//
	 //   -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back	VERDE
		// 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		// 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		// 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	 //   -0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	 //   -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		//
		// 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,//DERECHA AZUL
		// 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		// 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		// 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		// 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		// 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,1.0f,
  //    
		//-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,//IZQUIERDA ANMARILLO
		//-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		//-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		//-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		//-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		//-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		//
		//-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,//ABAJO CIAN
		//0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		//0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		//0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		//-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
		//-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		//
		//-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,//ARRIBA ROSA
		//0.5f,  0.5f, -0.5f,  1.0f, 0.2f,0.5f,
		//0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		//0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		//-0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
		//-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,



		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front	ROJO
		0.5f, -0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,

		-0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back	VERDE
		 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		-0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		-0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,//DERECHA AZUL
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,//IZQUIERDA ANMARILLO
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,//ABAJO CIAN
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,//ARRIBA ROSA
		0.5f,  0.5f, -0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClearColor(0.702f, 0.702f, 0.702f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle 
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::rotate(view, glm::radians(rot2), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, glm::radians(rot3), glm::vec3(0.0f, 0.0f, 1.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		// Obtener la locación del color
		GLint colorLoc = glGetUniformLocation(ourShader.Program, "colorCubo");

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);
	
		//// Tabla
	 //   model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(3.0f, 0.1f, 2.0f));				//Ancho, grosor y profundidad 
		//model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));			//pocisión en ejes x, y, z
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		////glBindVertexArray(0);


		//// Pata 1
		//model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.2f, 1.5f, 0.2f));				//Ancho, grosor y profundidad 
		//model = glm::translate(model, glm::vec3(6.5f, -0.46f, 4.0f));			//pocisión en ejes x, y, z
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);
	

		//// Pata 2
		//model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.2f, 1.5f, 0.2f));				
		//model = glm::translate(model, glm::vec3(6.5f, -0.46f, -4.0f));			
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);


		//// Pata 3
		//model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.2f, 1.5f, 0.2f));
		//model = glm::translate(model, glm::vec3(-6.0f, -0.46f, 4.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);


		//// Pata 4
		//model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.2f, 1.5f, 0.2f));
		//model = glm::translate(model, glm::vec3(-6.0f, -0.46f, -4.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		

		// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
		// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
		//FORMAR CUERPO - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		// Cuerpo
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 0.9f, 1.5f));
		model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.0f));
		//view = glm::rotate(view, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.9961f, 0.9294f, 0.4824f);									// <--- Aquí se asigna directamente el color
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Oreja 1 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 1.0f, 0.15f));
		model = glm::translate(model, glm::vec3(-1.0f, 0.8f, 3.2f));
		model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, -1.0f, 0.0f));		//Interesante  / / / / / / / / / / / / /
		//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));		//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Oreja 2
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 1.0f, 0.15f));
		model = glm::translate(model, glm::vec3(1.0f, 0.8f, 3.2f));
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));		//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Patas - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		model = glm::mat4(1.0f);											//Derecha delante
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
		model = glm::translate(model, glm::vec3(-1.0f, -0.5f, 1.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.9961f, 0.9294f, 0.4824f);									//amarillo
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);											//Izquierda delante
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
		model = glm::translate(model, glm::vec3(1.0f, -0.5f, 1.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);											//Derecha atras
		model = glm::scale(model, glm::vec3(0.37f, 0.5f, 0.32f));
		model = glm::translate(model, glm::vec3(-0.83f, -0.5f, -1.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);											//Izquierda atras
		model = glm::scale(model, glm::vec3(0.37f, 0.5f, 0.32f));
		model = glm::translate(model, glm::vec3(0.83f, -0.5f, -1.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cola - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		model = glm::mat4(1.0f);											//Base
		model = glm::scale(model, glm::vec3(0.2f, 0.58f, 0.15f));
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -5.5f));
		//model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));		//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.7804f, 0.5961f, 0.0f);										//marron
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);											//Medio
		model = glm::scale(model, glm::vec3(0.49f, 0.3f, 0.15f));
		model = glm::translate(model, glm::vec3(0.3f, 3.4f, -5.5f));
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));		//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.9961f, 0.9294f, 0.4824f);									//amarillo
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);											//Punta
		model = glm::scale(model, glm::vec3(0.75f, 0.45f, 0.15f));
		model = glm::translate(model, glm::vec3(0.7f, 3.1f, -5.6f));
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));		//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		
		// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
		// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
		//FORMAS EXTRA - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		// Manchas
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0003f, 0.4f, 0.2f));
		model = glm::translate(model, glm::vec3(0.000f, 1.32f, -0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.7414f, 0.5647f, 0.0431f);									// color
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0003f, 0.4f, 0.2f));
		model = glm::translate(model, glm::vec3(0.000f, 1.32f, -2.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		// Ojos
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.175f, 0.1f));
		model = glm::translate(model, glm::vec3(-1.3f, 2.5f, 7.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.1373f, 0.1373f, 0.1373f);									// color
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.175f, 0.1f));
		model = glm::translate(model, glm::vec3(1.3f, 2.5f, 7.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//------------------------------------------------------------
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		model = glm::translate(model, glm::vec3(-3.3f, 9.5f, 7.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 1.0f, 1.0f, 0.9922f);									// color
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		model = glm::translate(model, glm::vec3(3.3f, 9.5f, 7.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Nariz
		//model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.1f, 0.07f, 0.2f));
		//model = glm::translate(model, glm::vec3(0.000f, 4.2f, 3.6f));
		//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3f(colorLoc, 0.1373f, 0.1373f, 0.1373f);									// color
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.04f, 0.2f));
		model = glm::translate(model, glm::vec3(0.000f, 7.4f, 3.6f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.1373f, 0.1373f, 0.1373f);									// color
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cachetes
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.1f));
		model = glm::translate(model, glm::vec3(-1.7f, 1.0f, 7.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 1.0f, 0.4353f, 0.0f);											// color
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.1f));
		model = glm::translate(model, glm::vec3(1.7f, 1.0f, 7.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Boca
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.15f, 0.2f));
		model = glm::translate(model, glm::vec3(0.000f, 1.0f, 3.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.7882f, 0.298f, 0.5255f);									// color
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.2f));
		model = glm::translate(model, glm::vec3(0.000f, 1.9f, 3.4f));  //1.9 , antes 1.8
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.22f, 0.09f, 0.2f));
		model = glm::translate(model, glm::vec3(0.19f, 1.32f, 3.42f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.9451f, 0.7333f, 0.8353f);									// color
		glDrawArrays(GL_TRIANGLES, 0, 36);

		
		// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
		// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
		//COLORES EXTRA - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		// 
		// Quise probar aplicando los colores de la nueva forma pero así como lo hice, agregando un nuevo 
		// objeto, cambiandole el color y colocarlo casi junto al objeto original  para darle esa
		// "sombra". Pero la vrdad es mejor solo cambiar en los vertices los colores, porque así solo
		// me estoy llenando de objetos,mientras que al cambiar el color de las caras del objeto pues
		// se ahorrarían recursos y bastante código.
		// 
		// Aunque se aclara, no son sombras reales, solo son caras de los mismos bloques con un color
		// mas oscuro para dar el efecto. Principalmente hecho para tener un poco mas de contraste 
		// entre las diferentes piezas del Pikachu
		// 
		// 
		// 
		// Cuerpo sombra
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 0.9f, 1.5f));
		model = glm::translate(model, glm::vec3(0.0f, 0.2999f, 0.0f));
		//view = glm::rotate(view, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.9216f, 0.8627f, 0.4431f);									//Sombra abajo
		glDrawArrays(GL_TRIANGLES, 24, 30);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 0.9f, 1.5f));
		model = glm::translate(model, glm::vec3(0.0001f, 0.3f, 0.0f));
		//view = glm::rotate(view, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.9647, 0.8941f, 0.3608f);									//Sombra lado
		glDrawArrays(GL_TRIANGLES, 12, 18);

		// Oreja PUNTAS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2502f, 1.0f, 0.15f));
		model = glm::translate(model, glm::vec3(-0.999f, 0.8f, 3.2f));
		model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, -1.0f, 0.0f));		//
		//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));		//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 12, 18);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2502f, 1.0f, 0.15f));
		model = glm::translate(model, glm::vec3(0.999f, 0.8f, 3.2f));
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));		//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 12, 18);
		//---------------------------------------------------------------
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.252f, 0.15f, 0.152f));
		model = glm::translate(model, glm::vec3(-0.995f, 8.5f, 3.16f));
		model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, -1.0f, 0.0f));		//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.1373f, 0.1373f, 0.1373f);									//negro
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.252f, 0.15f, 0.152f));
		model = glm::translate(model, glm::vec3(0.995f, 8.5f, 3.16f));
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));		//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Patas - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		model = glm::mat4(1.0f);											//Derecha delante
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
		model = glm::translate(model, glm::vec3(-1.0f, -0.5001f, 1.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.9216f, 0.8627f, 0.4431f);									//Sombra abajo
		glDrawArrays(GL_TRIANGLES, 24,30);

		model = glm::mat4(1.0f);											//Izquierda delante
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
		model = glm::translate(model, glm::vec3(1.0f, -0.5001f, 1.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 24, 30);

		model = glm::mat4(1.0f);											//Derecha atras
		model = glm::scale(model, glm::vec3(0.37f, 0.5f, 0.32f));
		model = glm::translate(model, glm::vec3(-0.83f, -0.5001f, -1.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 24, 30);

		model = glm::mat4(1.0f);											//Izquierda atras
		model = glm::scale(model, glm::vec3(0.37f, 0.5f, 0.32f));
		model = glm::translate(model, glm::vec3(0.83f, -0.5001f, -1.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 24, 30);
		//------------------------------------------------------------------
		model = glm::mat4(1.0f);											//Derecha delante
		model = glm::scale(model, glm::vec3(0.302f, 0.5f, 0.3f));
		model = glm::translate(model, glm::vec3(-0.996f, -0.5f, 1.3001f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.9647, 0.8941f, 0.3608f);									//Sombra lado
		glDrawArrays(GL_TRIANGLES, 6, 18);

		model = glm::mat4(1.0f);											//Izquierda delante
		model = glm::scale(model, glm::vec3(0.302f, 0.5f, 0.3f));
		model = glm::translate(model, glm::vec3(0.9962f, -0.5f, 1.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 12, 18);

		model = glm::mat4(1.0f);											//Derecha atras
		model = glm::scale(model, glm::vec3(0.372f, 0.5f, 0.32f));
		model = glm::translate(model, glm::vec3(-0.826f, -0.5f, -1.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 12, 18);

		model = glm::mat4(1.0f);											//Izquierda atras
		model = glm::scale(model, glm::vec3(0.372f, 0.5f, 0.32f));
		model = glm::translate(model, glm::vec3(0.8262f, -0.5f, -1.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 12, 18);

		//Cola - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		model = glm::mat4(1.0f);											//Base
		model = glm::scale(model, glm::vec3(0.2003f, 0.58f, 0.15f));
		model = glm::translate(model, glm::vec3(0.000f, 0.9990f, -5.5f));
		//model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));		//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.7414f, 0.5647f, 0.0431f);									//marron
		glDrawArrays(GL_TRIANGLES, 12, 18);

		model = glm::mat4(1.0f);											//Medio
		model = glm::scale(model, glm::vec3(0.4903f, 0.3f, 0.15f));
		model = glm::translate(model, glm::vec3(0.300f, 3.3999f, -5.5f));
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));		//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(colorLoc, 0.9647, 0.8941f, 0.3608f);									//amarillo
		glDrawArrays(GL_TRIANGLES, 12, 18);

		model = glm::mat4(1.0f);											//Punta
		model = glm::scale(model, glm::vec3(0.7507f, 0.45f, 0.15f));
		model = glm::translate(model, glm::vec3(0.6997f, 3.0999f, -5.61f));
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));		//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 12, 18);

		

		glBindVertexArray(0);

				

		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);				// Se cierra ventana
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.008f;											//Mov vista a izquierda
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.008f;											//Mov vista a derecha
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY += 0.008f;											//Mov vista a abajo												
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY -= 0.008f;											//Mov vista a arriba
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.008f;											//Mov vista hacia adelante (fondo)
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.008f;											//Mov vista hacia atras (a cámara)
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.4f;											//Rota hacia la derecha
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.4f;											//Rota hacia la izquierda
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 rot2 += 0.4f;											//Rota hacia la arriba
	 if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		 rot2 -= 0.4f;											//Rota hacia la abajo
	 if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		 rot3 += 0.4f;											//Rota contrareloj
	 if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		 rot3 -= 0.4f;											//Rota reloj
 }


