#include<iostream>

//#define GLEW_STATIC

//Bibliotecas
#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"


//Creación de la ventana
void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 800;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primiti vas en 2D", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	//++++++++++++++++++++++++++++++++++++++++++++++\/ \/ \/
	//se cargan los archivos nuevos de vertices y fragmentos
	
	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		//poscición				color
		//0.5f,  0.5f, 0.0f,    1.0f,0.0f,0.0f,  // top right
		//0.5f, -0.5f, 0.0f,    1.0f,1.0f,0.0f,  // bottom right
		//-0.5f, -0.5f, 0.0f,   1.0f,0.0f,1.0f,  // bottom left
		//-0.5f,  0.5f, 0.0f,   1.0f,1.0f,0.0f, // top left 

		//0.9f,  0.8f, 0.0f,    0.486f,0.733f,0.0f,  // top right
		//0.4f, -0.76f, 0.0f,    1.0f,0.733f,0.0f,  // bottom right
		//-0.7f, -0.2f, 0.0f,   0.0f,0.631f,0.945f,  // bottom left
		//-0.2f,  0.5f, 0.0f,   0.964f,0.325f,0.078f, // top left 

		//0.9f,  0.8f, 0.0f,    0.486f,0.733f,0.0f,  // top right
		//0.4f, -0.6f, 0.0f,    1.0f,0.733f,0.0f,  // bottom right
		//-0.4f, -0.8f, 0.0f,   0.0f,0.631f,0.945f,  // bottom left
		//-0.7f,  0.8f, 0.0f,   0.964f,0.325f,0.078f, // top left 

		//0.5f,  0.6f, 0.0f,    0.486f,0.733f,0.0f,  // top right
		//0.4f, -0.7f, 0.0f,    1.0f,0.733f,0.0f,  // bottom right
		//-0.5f, -0.4f, 0.0f,   0.0f,0.631f,0.945f,  // bottom left
		//-0.5f,  0.7f, 0.0f,   0.964f,0.325f,0.078f, // top left 

		//Primer segmento
		-0.28f,  0.7f, 0.0f,    0.96f,0.6f,0.643f,  
		-0.01f,  0.66f, 0.0f,    0.96f,0.6f,0.643f,
		-0.143f,  0.458f, 0.0f,    0.96f,0.6f,0.643f,
		-0.27f,  0.45f, 0.0f,    0.96f,0.6f,0.643f,
		-0.29f,  0.28f, 0.0f,    0.96f,0.6f,0.643f,
		-0.43f,  0.11f, 0.0f,    0.96f,0.6f,0.643f,
		-0.65f,  0.16f, 0.0f,    0.96f,0.6f,0.643f,
		-0.48f,  0.52f, 0.0f,    0.96f,0.6f,0.643f,		//0-7

		//Swgundo swgmento
		-0.01f,  0.66f, 0.0f,    0.96f,0.6f,0.643f,
		0.14f,  0.44f, 0.0f,    0.96f,0.6f,0.643f,
		-0.02f,  0.38f, 0.0f,    0.96f,0.6f,0.643f,
		-0.143f,  0.458f, 0.0f,    0.96f,0.6f,0.643f,	//8-11

		//Tercer segmento
		-0.29f,  0.28f, 0.0f,    0.96f,0.6f,0.643f,
		-0.22f,  0.218f, 0.0f,    0.96f,0.6f,0.643f,
		-0.35f,  0.056f, 0.0f,    0.96f,0.6f,0.643f,
		-0.43f,  0.11f, 0.0f,    0.96f,0.6f,0.643f,		//12-15

		//0.5f,  0.5f, 0.0f,    0.96f,0.6f,0.643f,
		//0.5f,  0.5f, 0.0f,    0.96f,0.6f,0.643f,
		//0.5f,  0.5f, 0.0f,    0.96f,0.6f,0.643f,
		//0.5f,  0.5f, 0.0f,    0.96f,0.6f,0.643f,
		//0.5f,  0.5f, 0.0f,    0.96f,0.6f,0.643f,
		//0.5f,  0.5f, 0.0f,    0.96f,0.6f,0.643f,
		//0.5f,  0.5f, 0.0f,    0.96f,0.6f,0.643f,
		//0.5f,  0.5f, 0.0f,    0.96f,0.6f,0.643f,

	};
	unsigned int indices[] = {  // note that we start from 0!
		//2,3,0,
		3,2,1,// second Triangle
		0,1,3,
		
	};


	
	//cargando info de los verticces a los buffer para poderlos enlazar y luego envíar al shader

	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

		
	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	//sección donde ya se dibuja

	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        glPointSize(5);
        glDrawArrays(GL_POINTS,0,50);		//dibuja cada punto
        
        //glDrawArrays(GL_LINES,0,50);		//dibuja unión de 2 vertices

        //Primer segmento
		glDrawArrays(GL_LINE_LOOP,0,8);		//dibuja todo el cuadrado

		//Segundo segmento
		glDrawArrays(GL_LINE_LOOP, 8, 4);		//dibuja todo el cuadrado

		//Terfcer segmento
		glDrawArrays(GL_LINE_LOOP, 12, 4);		//dibuja todo el cuadrado


		//glDrawArrays(GL_LINE_LOOP, 0, 3);		//dibuja todo el cuadrado triangulo      

        //glDrawArrays(GL_TRIANGLES,0,3);		//dibuja triangulos
        //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0);		//dibujando triangulos tomando vertice de inicio independientemente

        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}