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

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "CAMBIAR NOMBREEEE", NULL, NULL);
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

		// CABEZA - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		//Primer segmento
		//	poscición				color
		-0.28f, 0.7f,  0.0f,	0.96f,0.6f,0.643f,  
		-0.01f, 0.66f, 0.0f,    0.96f,0.6f,0.643f,
		-0.143f,0.458f,0.0f,    0.96f,0.6f,0.643f,
		-0.27f, 0.45f, 0.0f,    0.96f,0.6f,0.643f,
		-0.29f, 0.28f, 0.0f,    0.96f,0.6f,0.643f,
		-0.41f, 0.11f, 0.0f,    0.96f,0.6f,0.643f,
		-0.65f, 0.16f, 0.0f,    0.96f,0.6f,0.643f,
		-0.48f, 0.52f, 0.0f,    0.96f,0.6f,0.643f,		//0-7

		//Swgundo swgmento
		-0.01f, 0.66f,  0.0f,    0.96f,0.6f,0.643f,
		0.14f,  0.44f,  0.0f,    0.96f,0.6f,0.643f,
		-0.02f, 0.38f,  0.0f,    0.96f,0.6f,0.643f,
		-0.143f,0.458f, 0.0f,    0.96f,0.6f,0.643f,		//8-11

		//Tercer segmento
		-0.29f, 0.28f,  0.0f,    0.96f,0.6f,0.643f,
		-0.22f, 0.218f, 0.0f,    0.96f,0.6f,0.643f,
		-0.35f, 0.056f, 0.0f,    0.96f,0.6f,0.643f,
		-0.41f, 0.11f,  0.0f,    0.96f,0.6f,0.643f,		//12-15

		//Cuarto segmento
		0.14f,   0.44f,  0.0f,    0.866f,0.403f,0.427f,
		0.078f,  0.21f,  0.0f,    0.866f,0.403f,0.427f,
		-0.158f, 0.01f,  0.0f,    0.866f,0.403f,0.427f,
		-0.305f, -0.07f, 0.0f,    0.866f,0.403f,0.427f,
		-0.35f,  0.056f, 0.0f,    0.866f,0.403f,0.427f,
		-0.22f,  0.218f, 0.0f,    0.866f,0.403f,0.427f,
		-0.08f,  0.222f, 0.0f,    0.866f,0.403f,0.427f,
		-0.02f,  0.38f,  0.0f,    0.866f,0.403f,0.427f,	//16-23

		//Quinto segmento
		-0.65f, 0.16f,   0.0f,    0.529f,0.756f,0.764f,
		-0.41f, 0.11f,   0.0f,    0.529f,0.756f,0.764f,
		-0.585f,-0.135f, 0.0f,    0.529f,0.756f,0.764f,
		-0.739f,-0.098f, 0.0f,    0.529f,0.756f,0.764f,	//24-27

		//Sexto segmento
		-0.41f,  0.11f,  0.0f,    0.529f,0.756f,0.764f,
		-0.35f,  0.056f, 0.0f,    0.529f,0.756f,0.764f,
		-0.56f, -0.162f, 0.0f,    0.529f,0.756f,0.764f,
		-0.585f,-0.135f, 0.0f,    0.529f,0.756f,0.764f,	//28-31

		//Septimo segmento
		-0.35f,  0.056f, 0.0f,    0.325f,0.549f,0.576f,
		-0.305f,-0.07f,  0.0f,    0.325f,0.549f,0.576f,
		-0.56f, -0.162f, 0.0f,    0.325f,0.549f,0.576f,	//32-34

		//Octavo segmento
		-0.739f, -0.098f, 0.0f,    0.529f,0.756f,0.764f,
		-0.585f, -0.135f, 0.0f,    0.529f,0.756f,0.764f,
		-0.56f,  -0.162f, 0.0f,    0.529f,0.756f,0.764f,
		-0.72f,  -0.12f,  0.0f,    0.529f,0.756f,0.764f,//35-38

		// CUERPO - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		// Segmento 9
		0.078f, 0.21f,	0.0f,    0.96f,0.6f,0.643f,
		0.34f,  0.2f,   0.0f,    0.96f,0.6f,0.643f,
		0.14f,  0.157f, 0.0f,    0.96f,0.6f,0.643f,		//39-41
		0.14f,  0.157f, 0.0f,    0.866f,0.403f,0.427f,		
		-0.028f,0.12f,	0.0f,    0.866f,0.403f,0.427f,
		0.078f, 0.21f,	0.0f,    0.866f,0.403f,0.427f,	//Sombra 42-44
		
		// Segmento 10
		0.34f,  0.2f,	0.0f,    0.96f,0.6f,0.643f,
		0.46f,  0.08f,	0.0f,    0.96f,0.6f,0.643f,
		0.07f, -0.37f,	0.0f,    0.96f,0.6f,0.643f,
		0.12f, -0.09f,	0.0f,    0.96f,0.6f,0.643f,
		0.065f,-0.01f,  0.0f,    0.96f,0.6f,0.643f,
		0.14f,  0.157f, 0.0f,    0.96f,0.6f,0.643f, 	//45-50
		0.14f,  0.157f, 0.0f,    0.866f,0.403f,0.427f,
		0.065f,-0.01f,  0.0f,    0.866f,0.403f,0.427f,
		-0.028f,0.12f,  0.0f,    0.866f,0.403f,0.427f,	//51-53
		
		// Segmento 11
		0.065f, -0.01f, 0.0f,    0.529f,0.756f,0.764f,
		0.12f,  -0.09f, 0.0f,    0.529f,0.756f,0.764f,
		0.07f,  -0.37f, 0.0f,    0.529f,0.756f,0.764f,		
		0.02f,  -0.12f, 0.0f,    0.325f,0.549f,0.576f,	//54-57
		-0.028f, 0.12f, 0.0f,    0.325f, 0.549f, 0.576f,
		0.065f, -0.01f, 0.0f,	 0.325f, 0.549f, 0.576f,
		0.02f,  -0.12f, 0.0f,    0.325f, 0.549f, 0.576f,//Sombra 58-60
		
		// Segmento 12
		-0.028f, 0.12f, 0.0f,    0.529f,0.756f,0.764f,
		0.07f,  -0.37f, 0.0f,    0.529f,0.756f,0.764f,
		-0.085f,-0.34f, 0.0f,    0.529f,0.756f,0.764f,
		0.03f,  -0.3f,  0.0f,    0.529f,0.756f,0.764f,
		-0.33f, -0.1f,  0.0f,    0.529f,0.756f,0.764f,
		-0.32f, -0.079f,0.0f,    0.529f,0.756f,0.764f,		
		-0.158f, 0.01f, 0.0f,    0.325f,0.549f,0.576f,	//61-67
		-0.33f, -0.1f,  0.0f,    0.325f, 0.549f, 0.576f,
		0.03f,  -0.3f,  0.0f,	 0.325f, 0.549f, 0.576f,
		-0.085f,-0.34f, 0.0f,	 0.325f, 0.549f, 0.576f, 
		-0.4f,  -0.275f,0.0f,    0.325f, 0.549f, 0.576f,//Luz 68-71
		
		// Segmento 13
		-0.4f,  -0.275f, 0.0f,   0.325f,0.549f,0.576f,
		0.07f,  -0.37f,  0.0f,   0.325f,0.549f,0.576f,
		0.158f, -0.545f, 0.0f,   0.325f,0.549f,0.576f,
		-0.145f,-0.462f, 0.0f,   0.325f,0.549f,0.576f,	//72-75
		
		// Segmento 14
		0.46f,   0.08f,  0.0f,   0.866f,0.403f,0.427f,
		0.49f,  -0.02f,  0.0f,   0.866f,0.403f,0.427f,
		0.24f,  -0.46f,  0.0f,   0.866f,0.403f,0.427f,
		0.158f, -0.545f, 0.0f,   0.866f,0.403f,0.427f,
		0.07f,  -0.37f,  0.0f,   0.866f,0.403f,0.427f,	//76-80
		 
		// COLA PATAS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		// Segmento 15
		0.44f, 0.8f,   0.0f,    0.529f,0.756f,0.764f,
		0.52f, 0.78f,  0.0f,    0.529f,0.756f,0.764f,
		0.42f, 0.28f,  0.0f,    0.529f,0.756f,0.764f,		
		0.21f, 0.208f, 0.0f,    0.325f,0.549f,0.576f,	//81-84
		0.42f, 0.28f,  0.0f,    0.325f, 0.549f, 0.576f,
		0.394f,0.149f, 0.0f,	0.325f, 0.549f, 0.576f,
		0.34f, 0.202f, 0.0f,	0.325f, 0.549f, 0.576f,
		0.21f, 0.208f, 0.0f,    0.325f, 0.549f, 0.576f,	//Sombra 85-88

		// Segmento 16
		0.52f,  0.78f,  0.0f,   0.325f,0.549f,0.576f,
		0.55f,  0.74f,  0.0f,	0.325f,0.549f,0.576f,
		0.49f, -0.02f,  0.0f,	0.325f,0.549f,0.576f,
		0.46f,  0.08f,  0.0f,	0.325f,0.549f,0.576f,
		0.394f, 0.149f, 0.0f,   0.325f,0.549f,0.576f,	//89-93

		// Segmento 17
		0.58f,  0.02f, 0.0f,    0.529f,0.756f,0.764f,
		0.775f,-0.08f, 0.0f,    0.529f,0.756f,0.764f,
		0.57f, -0.23f, 0.0f,    0.529f,0.756f,0.764f,		
		0.3f,  -0.1f,  0.0f,    0.325f,0.549f,0.576f,	//94-97

		// Segmento 18
		0.3f,  -0.1f,  0.0f,    0.529f,0.756f,0.764f,
		0.57f, -0.23f, 0.0f,    0.529f,0.756f,0.764f,
		0.45f, -0.69f, 0.0f,    0.529f,0.756f,0.764f,		
		0.22f, -0.58f, 0.0f,    0.325f,0.549f,0.576f,	//98-101

		// Segmento 19
		0.775f, -0.08f, 0.0f,   0.325f,0.549f,0.576f,
		0.785f, -0.18f, 0.0f,   0.325f,0.549f,0.576f,
		0.48f,  -0.76f, 0.0f,	0.325f,0.549f,0.576f,
		0.45f,  -0.69f, 0.0f,	0.325f,0.549f,0.576f,
		0.57f,  -0.23f, 0.0f,   0.325f,0.549f,0.576f,	//102-106

		// Segmento 20
		0.22f, -0.58f, 0.0f,	0.325f,0.549f,0.576f,
		0.45f, -0.69f, 0.0f,	0.325f,0.549f,0.576f,
		0.48f, -0.76f, 0.0f,	0.325f,0.549f,0.576f,
		0.255f,-0.65f, 0.0f,    0.325f,0.549f,0.576f,	//107-110

		// Segmento 21
		-0.32f, -0.079f, 0.0f,  0.529f,0.756f,0.764f,
		-0.4f,  -0.275f, 0.0f,  0.529f,0.756f,0.764f,
		-0.3f,  -0.35f,  0.0f,  0.529f,0.756f,0.764f,
		-0.31f, -0.44f,  0.0f,  0.529f,0.756f,0.764f,
		-0.465f,-0.36f,  0.0f,  0.529f,0.756f,0.764f,		
		-0.435f,-0.12f,  0.0f,  0.325f,0.549f,0.576f,	//111-116

		// Segmento 22
		-0.3f, -0.35f, 0.0f,	0.325f,0.549f,0.576f,
		-0.23f,-0.4f,  0.0f,	0.325f,0.549f,0.576f,
		-0.27f,-0.46f, 0.0f,	0.325f,0.549f,0.576f,
		-0.31f,-0.44f, 0.0f,    0.325f,0.549f,0.576f,	//117-120

		// OJO - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		// Segmento 23
		-0.143f, 0.458f, 0.0f,	  1.0f,1.0f,1.0f,
		-0.02f,  0.38f,  0.0f,    1.0f,1.0f,1.0f,
		-0.08f,  0.222f, 0.0f,    1.0f,1.0f,1.0f,			
		-0.22f,  0.218f, 0.0f,    1.0f,1.0f,1.0f,		
		-0.29f,  0.28f,  0.0f,    1.0f,1.0f,1.0f,
		-0.27f,  0.45f,  0.0f,    1.0f,1.0f,1.0f,		//121-126

		// Segmento 24
		-1.8f,  0.36f, 0.0f,	  0.0f,0.0f,0.0f,
		-1.5f,  0.35f, 0.0f,      0.0f,0.0f,0.0f,
		-1.4f,  0.32f, 0.0f,      0.0f,0.0f,0.0f,
		-1.7f,  0.3f,  0.0f,      0.0f,0.0f,0.0f,
		-1.9f,  0.34f, 0.0f,      0.0f,0.0f,0.0f,		//127-131
				   	
		// CABEZA / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
		//Primer segmento
		//	poscición				color
		-0.28f, 0.7f,  0.0f,	0.0f,0.0f,0.0f,  
		-0.01f, 0.66f, 0.0f,    0.0f,0.0f,0.0f,
		-0.143f,0.458f,0.0f,    0.0f,0.0f,0.0f,
		-0.27f, 0.45f, 0.0f,    0.0f,0.0f,0.0f,
		-0.29f, 0.28f, 0.0f,    0.0f,0.0f,0.0f,
		-0.41f, 0.11f, 0.0f,    0.0f,0.0f,0.0f,
		-0.65f, 0.16f, 0.0f,    0.0f,0.0f,0.0f,
		-0.48f, 0.52f, 0.0f,    0.0f,0.0f,0.0f,		//132-139
		//Swgundo swgmento
		-0.01f, 0.66f,  0.0f,    0.0f,0.0f,0.0f,
		0.14f,  0.44f,  0.0f,    0.0f,0.0f,0.0f,
		-0.02f, 0.38f,  0.0f,    0.0f,0.0f,0.0f,
		-0.143f,0.458f, 0.0f,    0.0f,0.0f,0.0f,		//140-143
		//Tercer segmento
		-0.29f, 0.28f,  0.0f,    0.0f,0.0f,0.0f,
		-0.22f, 0.218f, 0.0f,    0.0f,0.0f,0.0f,
		-0.35f, 0.056f, 0.0f,    0.0f,0.0f,0.0f,
		-0.41f, 0.11f,  0.0f,    0.0f,0.0f,0.0f,		//144-147
		//Cuarto segmento
		0.14f,   0.44f,  0.0f,    0.0f,0.0f,0.0f,
		0.078f,  0.21f,  0.0f,    0.0f,0.0f,0.0f,
		-0.158f, 0.01f,  0.0f,    0.0f,0.0f,0.0f,
		-0.305f, -0.07f, 0.0f,    0.0f,0.0f,0.0f,
		-0.35f,  0.056f, 0.0f,    0.0f,0.0f,0.0f,
		-0.22f,  0.218f, 0.0f,    0.0f,0.0f,0.0f,
		-0.08f,  0.222f, 0.0f,    0.0f,0.0f,0.0f,
		-0.02f,  0.38f,  0.0f,    0.0f,0.0f,0.0f,	//148-155
		//Quinto segmento
		-0.65f, 0.16f,   0.0f,    0.529f,0.756f,0.764f,
		-0.41f, 0.11f,   0.0f,    0.529f,0.756f,0.764f,
		-0.585f,-0.135f, 0.0f,    0.529f,0.756f,0.764f,
		-0.739f,-0.098f, 0.0f,    0.529f,0.756f,0.764f,	//155-158588888888
		//Sexto segmento
		-0.41f,  0.11f,  0.0f,    0.529f,0.756f,0.764f,
		-0.35f,  0.056f, 0.0f,    0.529f,0.756f,0.764f,
		-0.56f, -0.162f, 0.0f,    0.529f,0.756f,0.764f,
		-0.585f,-0.135f, 0.0f,    0.529f,0.756f,0.764f,	//159-162
		//Septimo segmento
		-0.35f,  0.056f, 0.0f,    0.325f,0.549f,0.576f,
		-0.305f,-0.07f,  0.0f,    0.325f,0.549f,0.576f,
		-0.56f, -0.162f, 0.0f,    0.325f,0.549f,0.576f,	//163-165
		//Octavo segmento
		-0.739f, -0.098f, 0.0f,    0.529f,0.756f,0.764f,
		-0.585f, -0.135f, 0.0f,    0.529f,0.756f,0.764f,
		-0.56f,  -0.162f, 0.0f,    0.529f,0.756f,0.764f,
		-0.72f,  -0.12f,  0.0f,    0.529f,0.756f,0.764f,//166-169
		// CUERPO / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
		// Segmento 9
		0.078f, 0.21f,	0.0f,    0.96f,0.6f,0.643f,
		0.34f,  0.2f,   0.0f,    0.96f,0.6f,0.643f,
		-0.028f,0.12f,	0.0f,    0.866f,0.403f,0.427f,	//170-172
		// Segmento 10
		0.34f,  0.2f,	0.0f,    0.96f,0.6f,0.643f,
		0.46f,  0.08f,	0.0f,    0.96f,0.6f,0.643f,
		0.07f, -0.37f,	0.0f,    0.96f,0.6f,0.643f,
		0.12f, -0.09f,	0.0f,    0.96f,0.6f,0.643f,
		-0.028f,0.12f,  0.0f,    0.866f,0.403f,0.427f,	//173-177
		// Segmento 11
		0.12f,  -0.09f, 0.0f,    0.529f,0.756f,0.764f,
		0.07f,  -0.37f, 0.0f,    0.529f,0.756f,0.764f,		
		-0.028f, 0.12f, 0.0f,    0.325f, 0.549f, 0.576f,//178-180
		// Segmento 12
		-0.028f, 0.12f, 0.0f,    0.529f,0.756f,0.764f,
		0.07f,  -0.37f, 0.0f,    0.529f,0.756f,0.764f,
		-0.32f, -0.079f,0.0f,    0.529f,0.756f,0.764f,		
		-0.158f, 0.01f, 0.0f,    0.325f,0.549f,0.576f,	
		-0.4f,  -0.275f,0.0f,    0.325f, 0.549f, 0.576f,//181-185
		// Segmento 13vavadfvavasvcasvasvasvavva
		-0.4f,  -0.275f, 0.0f,   0.325f,0.549f,0.576f,
		0.07f,  -0.37f,  0.0f,   0.325f,0.549f,0.576f,
		0.158f, -0.545f, 0.0f,   0.325f,0.549f,0.576f,
		-0.145f,-0.462f, 0.0f,   0.325f,0.549f,0.576f,	//72-75
		// Segmento 14
		0.46f,   0.08f,  0.0f,   0.866f,0.403f,0.427f,
		0.49f,  -0.02f,  0.0f,   0.866f,0.403f,0.427f,
		0.24f,  -0.46f,  0.0f,   0.866f,0.403f,0.427f,
		0.158f, -0.545f, 0.0f,   0.866f,0.403f,0.427f,
		0.07f,  -0.37f,  0.0f,   0.866f,0.403f,0.427f,	//76-80
		// COLA PATAS / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
		// Segmento 15
		0.44f, 0.8f,   0.0f,    0.529f,0.756f,0.764f,
		0.52f, 0.78f,  0.0f,    0.529f,0.756f,0.764f,
		0.42f, 0.28f,  0.0f,    0.529f,0.756f,0.764f,		
		0.21f, 0.208f, 0.0f,    0.325f,0.549f,0.576f,	//81-84
		0.42f, 0.28f,  0.0f,    0.325f, 0.549f, 0.576f,
		0.394f,0.149f, 0.0f,	0.325f, 0.549f, 0.576f,
		0.34f, 0.202f, 0.0f,	0.325f, 0.549f, 0.576f,
		0.21f, 0.208f, 0.0f,    0.325f, 0.549f, 0.576f,	//Sombra 85-88
		// Segmento 16
		0.52f,  0.78f,  0.0f,   0.325f,0.549f,0.576f,
		0.55f,  0.74f,  0.0f,	0.325f,0.549f,0.576f,
		0.49f, -0.02f,  0.0f,	0.325f,0.549f,0.576f,
		0.46f,  0.08f,  0.0f,	0.325f,0.549f,0.576f,
		0.394f, 0.149f, 0.0f,   0.325f,0.549f,0.576f,	//89-93
		// Segmento 17
		0.58f,  0.02f, 0.0f,    0.529f,0.756f,0.764f,
		0.775f,-0.08f, 0.0f,    0.529f,0.756f,0.764f,
		0.57f, -0.23f, 0.0f,    0.529f,0.756f,0.764f,		
		0.3f,  -0.1f,  0.0f,    0.325f,0.549f,0.576f,	//94-97
		// Segmento 18
		0.3f,  -0.1f,  0.0f,    0.529f,0.756f,0.764f,
		0.57f, -0.23f, 0.0f,    0.529f,0.756f,0.764f,
		0.45f, -0.69f, 0.0f,    0.529f,0.756f,0.764f,		
		0.22f, -0.58f, 0.0f,    0.325f,0.549f,0.576f,	//98-101
		// Segmento 19
		0.775f, -0.08f, 0.0f,   0.325f,0.549f,0.576f,
		0.785f, -0.18f, 0.0f,   0.325f,0.549f,0.576f,
		0.48f,  -0.76f, 0.0f,	0.325f,0.549f,0.576f,
		0.45f,  -0.69f, 0.0f,	0.325f,0.549f,0.576f,
		0.57f,  -0.23f, 0.0f,   0.325f,0.549f,0.576f,	//102-10
		// Segmento 20
		0.22f, -0.58f, 0.0f,	0.325f,0.549f,0.576f,
		0.45f, -0.69f, 0.0f,	0.325f,0.549f,0.576f,
		0.48f, -0.76f, 0.0f,	0.325f,0.549f,0.576f,
		0.255f,-0.65f, 0.0f,    0.325f,0.549f,0.576f,	//107-11
		// Segmento 21
		-0.32f, -0.079f, 0.0f,  0.529f,0.756f,0.764f,
		-0.4f,  -0.275f, 0.0f,  0.529f,0.756f,0.764f,
		-0.3f,  -0.35f,  0.0f,  0.529f,0.756f,0.764f,
		-0.31f, -0.44f,  0.0f,  0.529f,0.756f,0.764f,
		-0.465f,-0.36f,  0.0f,  0.529f,0.756f,0.764f,		
		-0.435f,-0.12f,  0.0f,  0.325f,0.549f,0.576f,	//111-116
		// Segmento 22
		-0.3f, -0.35f, 0.0f,	0.325f,0.549f,0.576f,
		-0.23f,-0.4f,  0.0f,	0.325f,0.549f,0.576f,
		-0.27f,-0.46f, 0.0f,	0.325f,0.549f,0.576f,
		-0.31f,-0.44f, 0.0f,    0.325f,0.549f,0.576f,	//117-120
		// OJO / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
		// Segmento 23
		-0.143f, 0.458f, 0.0f,	  1.0f,1.0f,1.0f,
		-0.02f,  0.38f,  0.0f,    1.0f,1.0f,1.0f,
		-0.08f,  0.222f, 0.0f,    1.0f,1.0f,1.0f,			
		-0.22f,  0.218f, 0.0f,    1.0f,1.0f,1.0f,		
		-0.29f,  0.28f,  0.0f,    1.0f,1.0f,1.0f,
		-0.27f,  0.45f,  0.0f,    1.0f,1.0f,1.0f,		//121-126
		// Segmento 24
		-1.8f,  0.36f, 0.0f,	  0.0f,0.0f,0.0f,
		-1.5f,  0.35f, 0.0f,      0.0f,0.0f,0.0f,
		-1.4f,  0.32f, 0.0f,      0.0f,0.0f,0.0f,
		-1.7f,  0.3f,  0.0f,      0.0f,0.0f,0.0f,
		-1.9f,  0.34f, 0.0f,      0.0f,0.0f,0.0f,		//127-131
		

	};
	unsigned int indices[] = {  // note that we start from 0!
		//2,3,0,
		//3,2,1,// second Triangle
		//0,1,3,
		
		//Seccion 1
		0,1,2,
		0,2,3,	
		0,3,7,	
		3,4,7,	
		4,5,7,	
		5,6,7,		//18
		//Seccion 2
		8,9,10,
		8,10,11,	//24
		//Sección 3
		12,13,14,
		14,15,12,	//30
		//Sección 4
		16,17,23,
		23,22,17,
		17,22,18,
		18,22,21,
		20,21,18,
		18,19,20,	//48
		//Sección 5
		24,25,26,
		27,24,26,	//54
		//Sección 6
		28,29,30,
		31,28,30,	//60
		//Sección 7
		32,33,34,	//63
		//Sección 8
		35,36,37,
		38,35,37,	//69

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
        glDrawArrays(GL_POINTS,0,150);		//dibuja cada punto
        
        //glDrawArrays(GL_LINES,0,50);		//dibuja unión de 2 vertices

		// ----- ----- ----- ----- ----- LINEAS ----- ----- ----- ----- -----
		// CABEZA - - - - - - - - - -
        //Primer segmento 
		glDrawArrays(GL_LINE_LOOP,0,8);		//dibuja todo el cuadrado

		//Segundo segmento
		glDrawArrays(GL_LINE_LOOP, 8, 4);		

		//Terfcer segmento
		glDrawArrays(GL_LINE_LOOP, 12, 4);		

		//Cuarto segmento
		glDrawArrays(GL_LINE_LOOP, 16, 8);		

		//Quinto segmento
		glDrawArrays(GL_LINE_LOOP, 24, 4);

		//Sexto segmento
		glDrawArrays(GL_LINE_LOOP, 28, 4);

		//Septimo segmento
		glDrawArrays(GL_LINE_LOOP, 32, 3);

		//Octavo segmento
		glDrawArrays(GL_LINE_LOOP, 35, 4);

		// CUERPO - - - - - - - - - -
		//Segmento 9
		glDrawArrays(GL_LINE_LOOP, 39, 3);
		glDrawArrays(GL_LINE_LOOP, 42, 3);

		//Segmento 10
		glDrawArrays(GL_LINE_LOOP, 45, 6);
		glDrawArrays(GL_LINE_LOOP, 51, 3);

		//Segmento 11
		glDrawArrays(GL_LINE_LOOP, 54, 4);
		glDrawArrays(GL_LINE_LOOP, 58, 3);

		//Segmento 12
		glDrawArrays(GL_LINE_LOOP, 61, 7);
		glDrawArrays(GL_LINE_LOOP, 68, 4);

		//Segmento 13
		glDrawArrays(GL_LINE_LOOP, 72, 4);

		//Segmento 14
		glDrawArrays(GL_LINE_LOOP, 76, 5);

		// COLA PATAS - - - - - - - - - -
		//Segmento 15
		glDrawArrays(GL_LINE_LOOP, 81, 4);
		glDrawArrays(GL_LINE_LOOP, 85, 4);

		//Segmento 16
		glDrawArrays(GL_LINE_LOOP, 89, 5);

		//Segmento 17
		glDrawArrays(GL_LINE_LOOP, 94, 4);

		//Segmento 18
		glDrawArrays(GL_LINE_LOOP, 98, 4);

		//Segmento 19
		glDrawArrays(GL_LINE_LOOP, 102, 5);

		//Segmento 20
		glDrawArrays(GL_LINE_LOOP, 107, 4);

		//Segmento 21
		glDrawArrays(GL_LINE_LOOP, 111, 6);

		//Segmento 22
		glDrawArrays(GL_LINE_LOOP, 117, 4);

		// OJO - - - - - - - - - -
		//Segmento 23
		glDrawArrays(GL_LINE_LOOP, 121, 6);

		//Segmento 24
		glDrawArrays(GL_LINE_LOOP, 127, 5);

		//glDrawArrays(GL_LINE_LOOP, 0, 3);		//dibuja todo el cuadrado triangulo      


		// ----- ----- ----- ----- ----- COLOR ----- ----- ----- ----- -----
		// CABEZA - - - - - - - - - -
		//glDrawArrays(GL_TRIANGLES,0,8);								//dibuja triangulos
		//glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, 0);		//dibujando triangulos tomando vertice de inicio independientemente
		
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawArrays(GL_TRIANGLES, 3, 3);
		//glDrawArrays(GL_TRIANGLES, 5, 3);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
		
		//(void*) convierte el número de bytes al tipo depuntero que ve glDrawElements y openGl
		//El 4to parametro, es donde inicia la sección:  posición * tamaño de unsigned int
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(unsigned int)));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(unsigned int)));

		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(48 * sizeof(unsigned int)));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(54 * sizeof(unsigned int)));

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(60 * sizeof(unsigned int)));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(63 * sizeof(unsigned int)));
		
		//glDrawArrays(GL_TRIANGLES, 0, 4);
		//glDrawArrays(GL_TRIANGLES, 0, 3);  // 0-1-2
		//glDrawArrays(GL_TRIANGLES, 2, 3);  // 2-3-4 (reutiliza patrón)
		//glDrawArrays(GL_TRIANGLES, 4, 3);  // 4-5-6
		//glDrawArrays(GL_TRIANGLES, 5, 3);  // 5-6-7

		
						// ----- ----- ----- ----- ----- LINEAS NEGRAS ----- ----- ----- ----- -----
		// CABEZA - - - - - - - - - -
        //Primer segmento 
		glDrawArrays(GL_LINE_LOOP,132,8);		
		//Segundo segmento
		glDrawArrays(GL_LINE_LOOP, 140, 4);		
		//Terfcer segmento
		glDrawArrays(GL_LINE_LOOP, 144, 4);		
		//Cuarto segmento
		glDrawArrays(GL_LINE_LOOP, 148, 8);

		
		//glDrawArrays(GL_TRIANGLES,1,8);		
		//glDrawArrays(GL_TRIANGLES,0,3);
		//glDrawArrays(GL_TRIANGLES,0,3);
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