//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//Practica #12 											  Ruiz Vargas Ricardo
//Fecha de entrega: 06 de noviembre de 2026 						316226068
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

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"


	//	Necesarioa para laa lectur/escritur de archivos en C++
#include <fstream>


// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void Animation();

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
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,2.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};


glm::vec3 Light1 = glm::vec3(0);
//Anim
float rotBall = 0.0f;
float rotDog = 0.0f;
int dogAnim = 0;
//float FLegs = 0.0f;
//float RLegs = 0.0f;
	
	//patas:
float FR_Leg = 0.0f;	//delantera derecha
float FL_Leg = 0.0f;	//			izquierda
float BR_Leg = 0.0f;	//trasera derecha
float BL_Leg = 0.0f;	//			izquierda

float head = 0.0f;		//cabeza - - - - -

float tail = 0.0f;

float body = 0.0f;

float bodyDead = 0.0f;



//KeyFrames /*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+				
// <--- Para manejar las posiciones independientemente por frame
float dogPosX , dogPosY , dogPosZ  ;

// /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+ VARIAVBLES ***
#define MAX_FRAMES 20					// <--- Numero maximo de keyfframes que se van a usar !!!
int i_max_steps = 150;
int i_curr_steps = 0;
typedef struct _frame {
	
	float rotDog;
	float rotDogInc;
	float dogPosX;
	float dogPosY;
	float dogPosZ;
	float incX;
	float incY;
	float incZ;

	float head;		//cabeza anim - - - - -
	float headInc;	//estructura para el incremento - - - - -
		//patas:
	float FR_Leg;	//
	float FR_LegInc;
	float FL_Leg;	//
	float FL_LegInc;
	float BR_Leg;	//
	float BR_LegInc;
	float BL_Leg;	//
	float BL_LegInc;

	float tail;     //cola anim
	float tailInc;

	float body;		//cuerpo anim
	float bodyInc;

	float bodyDead;
	float bodyDeadInc;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;		//	introducir datos
bool play = false;
int playIndex = 0;		//	en que punto de la animaçion se encuentra

// /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+ GUARDA FRAME ***
void saveFrame(void)	//	funcion que guarda toda la informacion 
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].dogPosX = dogPosX;
	KeyFrame[FrameIndex].dogPosY = dogPosY;
	KeyFrame[FrameIndex].dogPosZ = dogPosZ;

	KeyFrame[FrameIndex].rotDog = rotDog;

	KeyFrame[FrameIndex].head = head;		//para guardarlo en el frame - - - - -
		//patas:
	KeyFrame[FrameIndex].FR_Leg = FR_Leg;	
	KeyFrame[FrameIndex].FL_Leg = FL_Leg;
	KeyFrame[FrameIndex].BR_Leg = BR_Leg;
	KeyFrame[FrameIndex].BL_Leg = BL_Leg;

	KeyFrame[FrameIndex].tail = tail;

	KeyFrame[FrameIndex].body = body;

	KeyFrame[FrameIndex].bodyDead = bodyDead;

	FrameIndex++;
}

// /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+ RESETEO ***
void resetElements(void)	//	Regresa a la posicion inicial
{
	dogPosX = KeyFrame[0].dogPosX;
	dogPosY = KeyFrame[0].dogPosY;
	dogPosZ = KeyFrame[0].dogPosZ;

	rotDog = KeyFrame[0].rotDog;

	head = KeyFrame[0].head;		// inicializarlo para cuando inicia la animacion - - - - -
		//patas
	FR_Leg = KeyFrame[0].FR_Leg;	
	FL_Leg = KeyFrame[0].FL_Leg;
	BR_Leg = KeyFrame[0].BR_Leg;
	BL_Leg = KeyFrame[0].BL_Leg;

	tail = KeyFrame[0].tail;

	body = KeyFrame[0].body;

	bodyDead = KeyFrame[0].bodyDead;

}

// /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+  /*-+ INTERPOLACION ***
void interpolation(void)	//	interpolacion de tiempo entre frames
{
	// |/ que tan fluido será la anim.
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].dogPosX - KeyFrame[playIndex].dogPosX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].dogPosY - KeyFrame[playIndex].dogPosY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].dogPosZ - KeyFrame[playIndex].dogPosZ) / i_max_steps;

	KeyFrame[playIndex].rotDogInc = (KeyFrame[playIndex + 1].rotDog - KeyFrame[playIndex].rotDog) / i_max_steps;

	KeyFrame[playIndex].headInc = (KeyFrame[playIndex + 1].head - KeyFrame[playIndex].head) / i_max_steps;	// su interpolacion - - - - -
		//patas:
	KeyFrame[playIndex].FR_LegInc = (KeyFrame[playIndex + 1].FR_Leg - KeyFrame[playIndex].FR_Leg) / i_max_steps;	//patas
	KeyFrame[playIndex].FL_LegInc = (KeyFrame[playIndex + 1].FL_Leg - KeyFrame[playIndex].FL_Leg) / i_max_steps;
	KeyFrame[playIndex].BR_LegInc = (KeyFrame[playIndex + 1].BR_Leg - KeyFrame[playIndex].BR_Leg) / i_max_steps;
	KeyFrame[playIndex].BL_LegInc = (KeyFrame[playIndex + 1].BL_Leg - KeyFrame[playIndex].BL_Leg) / i_max_steps;

	KeyFrame[playIndex].tailInc = (KeyFrame[playIndex + 1].tail - KeyFrame[playIndex].tail) / i_max_steps;

	KeyFrame[playIndex].bodyInc = (KeyFrame[playIndex + 1].body - KeyFrame[playIndex].body) / i_max_steps;

	KeyFrame[playIndex].bodyDeadInc = (KeyFrame[playIndex + 1].bodyDead - KeyFrame[playIndex].bodyDead) / i_max_steps;


}
// /*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+


//Para guardar los frames en un txt /-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+				
void saveFramesToFile() {														//Para guardar en el archivo ***
	std::ofstream file("animacion_perro.txt");
	if (file.is_open())	{ 
		file << FrameIndex << "\n"; //guard la cantidad total de frames registrados
		for (int i = 0; i < FrameIndex; i++) {
					//escribe las variables por cada frame en una sola line
			file << KeyFrame[i].dogPosX << " " << KeyFrame[i].dogPosY << " " << KeyFrame[i].dogPosZ << " "
				<< KeyFrame[i].rotDog << " " << KeyFrame[i].body << " " << KeyFrame[i].bodyDead << " "
				<< KeyFrame[i].head << " " << KeyFrame[i].tail << " "
				<< KeyFrame[i].FR_Leg << " " << KeyFrame[i].FL_Leg << " "
				<< KeyFrame[i].BR_Leg << " " << KeyFrame[i].BL_Leg << "\n";
		}
		file.close();
		printf("Animacion guardada en animacion_perro.txt con %d frames :D \n", FrameIndex);
	}
}
// aaa!!!
void loadFramesFromFile() {														//Para cargaar el archivo ***
	std::ifstream file("animacion_perro.txt");
	if (file.is_open()) {
		file >> FrameIndex; // Lee la cantidad de frames para saber el límite
		for (int i = 0; i < FrameIndex; i++) {
					// Lee los datos exactamente en el mismo orden que se guardaron
			file >> KeyFrame[i].dogPosX >> KeyFrame[i].dogPosY >> KeyFrame[i].dogPosZ
				>> KeyFrame[i].rotDog >> KeyFrame[i].body >> KeyFrame[i].bodyDead
				>> KeyFrame[i].head >> KeyFrame[i].tail
				>> KeyFrame[i].FR_Leg >> KeyFrame[i].FL_Leg
				>> KeyFrame[i].BR_Leg >> KeyFrame[i].BL_Leg;
		}
		file.close();
		resetElements(); // Actualiza el perro a la pose del Frame 0
		printf("Animacion cargada exitosamente jjaja B) \n");
	}
	else {
		printf("No se encontro el archivo animacion_perro.txt wtf :,( \n");
	}
}
// /*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+/*-+







// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	//GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Animacion por Keyframes", nullptr, nullptr);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 12 - Ricardo_Ruiz_Vargas", nullptr, nullptr);

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
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
	
	
	//models
	Model DogBody((char*)"Models/perro-animacion/DogBody.obj");				//cuerpo
	Model HeadDog((char*)"Models/perro-animacion/HeadDog.obj");				//cabeza
	Model DogTail((char*)"Models/perro-animacion/TailDog.obj");				//cola
	Model F_RightLeg((char*)"Models/perro-animacion/F_RightLegDog.obj");	//delantera derecha
	Model F_LeftLeg((char*)"Models/perro-animacion/F_LeftLegDog.obj");		//delantera izquierda
	Model B_RightLeg((char*)"Models/perro-animacion/B_RightLegDog.obj");	//trasera derecha
	Model B_LeftLeg((char*)"Models/perro-animacion/B_LeftLegDog.obj");		//trasera izquierda
	Model Piso((char*)"Models/perro-animacion/piso.obj");
	Model Ball((char*)"Models/perro-animacion/ball.obj");


	//KeyFrames								<--- inicializa el sistema de keyframes - - - - - - - - - - - - - - - - - -
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].dogPosX = 0;
		KeyFrame[i].dogPosY = 0;
		KeyFrame[i].dogPosZ = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotDog = 0;
		KeyFrame[i].rotDogInc = 0;
		
		KeyFrame[i].head = 0;				// - - - - -
		KeyFrame[i].headInc = 0;			// - - - - -
			//patas:
		KeyFrame[i].FR_Leg = 0;			//
		KeyFrame[i].FR_LegInc = 0;
		KeyFrame[i].FL_Leg = 0;			//
		KeyFrame[i].FL_LegInc = 0;
		KeyFrame[i].BR_Leg = 0;			//
		KeyFrame[i].BR_LegInc = 0;
		KeyFrame[i].BL_Leg = 0;			//
		KeyFrame[i].BL_LegInc = 0;

		KeyFrame[i].tail = 0;
		KeyFrame[i].tailInc = 0;

		KeyFrame[i].body = 0;
		KeyFrame[i].bodyInc = 0;

		KeyFrame[i].bodyDead = 0;
		KeyFrame[i].bodyDeadInc = 0;

	}


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	
	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

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
		Animation();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
		// OpenGL options
		glEnable(GL_DEPTH_TEST);

		
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		
	

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

        glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"),0.6f,0.6f,0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"),0.3f, 0.3f, 0.3f);


		// Point light 1
	    glm::vec3 lightColor;
		lightColor.x= abs(sin(glfwGetTime() *Light1.x));
		lightColor.y= abs(sin(glfwGetTime() *Light1.y));
		lightColor.z= sin(glfwGetTime() *Light1.z);

		
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x,lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x,lightColor.y,lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"),0.075f);


		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));
		

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);

	
		// MODELOS / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
		// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
		//Carga de modelo 
        view = camera.GetViewMatrix();	
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);

		//Body - - - - - - - - - - - - - - - - - - - - - - - - - - - -
														// |/ para que se dibujen en la posicion de cada frame
		modelTemp = model = glm::translate(model, glm::vec3(dogPosX, dogPosY, dogPosZ));
		modelTemp = model = glm::rotate(model, glm::radians(rotDog), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTemp = model = glm::rotate(model, glm::radians(body), glm::vec3(1.0f, 0.0f, 0.0f));		// <-- Pa inclinar cuerpo
		modelTemp = model = glm::rotate(model, glm::radians(bodyDead), glm::vec3(0.0f, 0.0f, 1.0f));	// <-- Pa hacer de muerto
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DogBody.Draw(lightingShader);
		
		//Head  - - - - - - - - - - - - - - - - - - - - - - - - - - -
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.0f, 0.093f, 0.208f));
		model = glm::rotate(model, glm::radians(head), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		HeadDog.Draw(lightingShader);
		
		//Tail  - - - - - - - - - - - - - - - - - - - - - - - - - - -
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.0f, 0.026f, -0.288f));
		model = glm::rotate(model, glm::radians(tail), glm::vec3(0.0f, 0.0f, -1.0f)); 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		DogTail.Draw(lightingShader);
		
		//Front Left Leg  - - - - - - - - - - - - - - - - - - - - - -
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.112f, -0.044f, 0.074f));
		model = glm::rotate(model, glm::radians(FL_Leg), glm::vec3(-1.0f, 0.0f, 0.0f)); //cambiar cada variable nueva para cada pata de forma indivisual
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		F_LeftLeg.Draw(lightingShader);
		
		//Front Right Leg  - - - - - - - - - - - - - - - - - - - - - 
		model = modelTemp; 
		model = glm::translate(model, glm::vec3(-0.111f, -0.055f, 0.074f));
		model = glm::rotate(model, glm::radians(FR_Leg), glm::vec3(-1.0f, 0.0f, 0.0f));	//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		F_RightLeg.Draw(lightingShader);
		
		//Back Left Leg  - - - - - - - - - - - - - - - - - - - - - - - - - 
		model = modelTemp; 
		model = glm::translate(model, glm::vec3(0.082f, -0.046, -0.218)); 
		model = glm::rotate(model, glm::radians(BL_Leg), glm::vec3(-1.0f, 0.0f, 0.0f));	//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		B_LeftLeg.Draw(lightingShader);
		
		//Back Right Leg  - - - - - - - - - - - - - - - - - - - - - - - - -
		model = modelTemp; 
		model = glm::translate(model, glm::vec3(-0.083f, -0.057f, -0.231f));
		model = glm::rotate(model, glm::radians(BR_Leg), glm::vec3(-1.0f, 0.0f, 0.0f));	//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		B_RightLeg.Draw(lightingShader); 


		model = glm::mat4(1);
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		model = glm::rotate(model, glm::radians(rotBall), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	    Ball.Draw(lightingShader); 
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);
	

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		
		model = glm::mat4(1);
		model = glm::translate(model, pointLightPositions[0]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		glBindVertexArray(0);

		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	
	

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	//Dog Controls ////////////////////////////////////////////////////////////////////
	if (keys[GLFW_KEY_R])					//gira ANTIHORARIO
	{
			rotDog += 1.0f;
	}

	if (keys[GLFW_KEY_Y])					//gira HORARIO
	{
			rotDog -= 1.0f;
	}
			
	if (keys[GLFW_KEY_G])					//para ADELANTE
	{
		dogPosZ += 0.01;
	}

	if (keys[GLFW_KEY_T])					//para ATRAS
	{
		dogPosZ -= 0.01;
	}

	if (keys[GLFW_KEY_F])					//para IZQUIERDA
	{
		dogPosX -= 0.01;
	}

	if (keys[GLFW_KEY_H])					//para DERECHA
	{
		dogPosX += 0.01;
	}

	// Agregando nuievos controles - - - - -
	if (keys[GLFW_KEY_1])					//para CABEZA - - - - -
	{	head += 1.0;		}
	if (keys[GLFW_KEY_2])					// ''
	{	head -= 1.0;		}

	//Delantera Derecha 
	if (keys[GLFW_KEY_0])
	{	FR_Leg += 1.0f;		}
	if (keys[GLFW_KEY_P])
	{	FR_Leg -= 1.0f;		}

	//delantera Izquierda 
	if (keys[GLFW_KEY_7])
	{	FL_Leg += 1.0f;		}
	if (keys[GLFW_KEY_U])
	{	FL_Leg -= 1.0f;		}

	//rtasera Derecha 
	if (keys[GLFW_KEY_9])
	{	BR_Leg += 1.0f;		}
	if (keys[GLFW_KEY_O])
	{	BR_Leg -= 1.0f;		}

	//Trasera Izquierda
	if (keys[GLFW_KEY_8])
	{	BL_Leg += 1.0f;		}
	if (keys[GLFW_KEY_I])
	{	BL_Leg -= 1.0f;		}

	// Cola
	if (keys[GLFW_KEY_3])
	{	tail += 1.0f;		}
	if (keys[GLFW_KEY_4])
	{	tail -= 1.0f;		}

	// Cuerpo (Sentarse)
	if (keys[GLFW_KEY_5])
	{	body += 1.0f;		}
	if (keys[GLFW_KEY_6])
	{	body -= 1.0f;		}
	// Altura del cuerpo (Eje Y)
	if (keys[GLFW_KEY_E])		//subir el cuerpo
	{	dogPosY += 0.01f;	}
	if (keys[GLFW_KEY_Q])		//bajar el cuerpo
	{	dogPosY -= 0.01f;	}

	// Cuerpo (Muertito)
	if (keys[GLFW_KEY_J])
	{	bodyDead += 1.0f;	}
	if (keys[GLFW_KEY_M])
	{	bodyDead -= 1.0f;	}

		//Para guardar y cargar el archivo de animacion
	if (keys[GLFW_KEY_F1])							//F1 guarda anim
	{	saveFramesToFile();		}

	if (keys[GLFW_KEY_F2])							//F2 carga la anim
	{	loadFramesFromFile();	}



	// Camera controls ////////////////////////////////////////////////////////////////
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


	if (keys[GLFW_KEY_X])//--->LUZ DERECHA 
	{
		pointLightPositions[0].x += 0.01f;
	}
	if (keys[GLFW_KEY_Z])//--->LUZ IZQUIERDA 
	{
		pointLightPositions[0].x -= 0.01f;
	}
	if (keys[GLFW_KEY_N])//--->LUZ ARRIBA
	{
		pointLightPositions[0].y += 0.01f;
	}
	if (keys[GLFW_KEY_B])//--->LUZ ABAJO
	{
		pointLightPositions[0].y -= 0.01f;
	}
	if (keys[GLFW_KEY_C])//--->LUZ ATRAS
	{
		pointLightPositions[0].z -= 0.01f;
	}
	if (keys[GLFW_KEY_V])//--->LUZ ADELANTE
	{
		pointLightPositions[0].z += 0.01f;
	}
}


// Is called whenever a key is pressed/released via GLFW ///////////////////////////
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{

	if (keys[GLFW_KEY_L])					//REPRODUCE LA ANIMACION HECHA POR KEYFRAMES
	{
		if (play == false && (FrameIndex > 1))
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

	}

	if (keys[GLFW_KEY_K])					//GUARDA POSICION DEL FRAME
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}

	}



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

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(0.2f, 0.8f, 1.0f);
			
		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}
	}
	
	
}

// /-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_/-_
void Animation() {

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation - - - - - - - - - - - - - - - - - - - - *
			dogPosX += KeyFrame[playIndex].incX;
			dogPosY += KeyFrame[playIndex].incY;
			dogPosZ += KeyFrame[playIndex].incZ;

			rotDog += KeyFrame[playIndex].rotDogInc;

			head += KeyFrame[playIndex].headInc;		// para que lo dibuje cada frame - - - - -
				//patas:
			FR_Leg += KeyFrame[playIndex].FR_LegInc;
			FL_Leg += KeyFrame[playIndex].FL_LegInc;
			BR_Leg += KeyFrame[playIndex].BR_LegInc;
			BL_Leg += KeyFrame[playIndex].BL_LegInc;

			tail += KeyFrame[playIndex].tailInc;

			body += KeyFrame[playIndex].bodyInc;

			bodyDead += KeyFrame[playIndex].bodyDeadInc;

			i_curr_steps++;
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