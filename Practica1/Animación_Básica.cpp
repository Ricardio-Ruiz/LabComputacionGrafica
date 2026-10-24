//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//Practica #10 											  Ruiz Vargas Ricardo
//Fecha de entrega: 23 de octubre de 2026 							316226068
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

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void Animation();
void Animation2();

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
bool active;										// <-- Determina cuando se activa o desactiva la animación

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
float rotBall = 0;									//rotacion pelota
bool AnimBall = false;								// <-- Determina cuando se activa o desactiva la animación


//Previo10 - - - - - - - - - - - - - - - - - - - 
//variables para el rebote solicitado
float posY = 1.0f;				//altura inicial (se ajustaria según la altura de la nariz del perro)		<---
bool subiendo = true;			//controlar dirección
// - - - - - - - - - - - - - - - - - - - - - - - 

//Practica10 - - - - - - - - - - - - - - - - - - - 
float rotDog = 0;									//rotacion perro
bool AnimDog = false;								// <-- Determina cuando se activa o desactiva la animación
float posY2 = 0.0f;				//altura inicial (se ajustaria según la altura de la nariz del perro)		<---
float saltoDog = 0.0f;				//para la rotacion del perro en su salto									<---
bool subiendo2 = true;			//controlar dirección

float movelightRot = 0.0f;
// - - - - - - - - - - - - - - - - - - - - - - - 



// Deltatime										//definicion del Intervalo de tiempo
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
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 10 - Ricardo_Ruiz_Vargas", nullptr, nullptr);

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
	Model Dog((char*)"Models/RedDog.obj");
	Model Piso((char*)"Models/piso.obj");
	Model Ball((char*)"Models/ball.obj");



	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
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
		GLfloat currentFrame = glfwGetTime();				//calcula el fram actual (como en la practica anterior con la vela)
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;							//se calcula el tiempo transcurrido y se utiliza para determinar la 
															//velocidad en la que transcurrecn las animaciones

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		Animation();				//función que contiene la animacion
		//Animation2();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
		// OpenGL options
		glEnable(GL_DEPTH_TEST);

		
		
		
	

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


		// Point light 1									//Porceso por el cual pasa la luz
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


		model = glm::mat4(1);							// |/ Para que coincida la caida de la pelota con la cabeza
		model = glm::rotate(model, glm::radians(rotDog - 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));	//pivotr
		model = glm::translate(model, glm::vec3(1.5f, posY2, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//
		model = glm::rotate(model, glm::radians(saltoDog), glm::vec3(-1.0f, 0.0f, 0.0f));		//Para que haga el salto con inclinacion
		//
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Dog.Draw(lightingShader);


		model = glm::mat4(1);
		model = glm::rotate(model, glm::radians(rotBall), glm::vec3(0.0f, -1.0f, 0.0f));			//parte de rotación de la pelota, como en practicas anteiores
		//model = glm::rotate(model, glm::radians(movelightRot), glm::vec3(0.0f, 0.0f, 1.0f));	//pivote
		//model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		//
		model = glm::translate(model, glm::vec3(1.3, posY, 0.0f));								//para mover en eje Y con posY
		//
		//model = glm::rotate(model, glm::radians(rotBall), glm::vec3(0.0f, 1.0f, 0.0f));			//parte de rotación de la pelota, como en practicas anteiores
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));						//se envia al shader
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

	if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_Y])
	{
		pointLightPositions[0].y += 0.01f;
	}

	if (keys[GLFW_KEY_H])
	{
		pointLightPositions[0].y -= 0.01f;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z -= 0.1f;
	}
	if (keys[GLFW_KEY_J])
	{
		pointLightPositions[0].z += 0.01f;
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

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;				//cambia el booleano
		if (active)
		{
			Light1 = glm::vec3(1.0f, 1.0f, 0.0f);
			
		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente 
		}
	}
	if (keys[GLFW_KEY_N])
	{
		AnimBall = !AnimBall;			//cambia el booleano
		AnimDog = !AnimDog;
		
	}
}


void Animation() {			
	// ANIMACION DE PELOTA - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	if (AnimBall)						//si está activs ls vsriable / es verdadera
	{
		rotBall += 0.4f;
		//printf("%f", rotBall);			//imprime en consola la variable


		//traslacion en  Y - - - - - - - - - - - - - - 
		
		//-->Versión con ifs
		//float alturadLuz = pointLightPositions[0].y;		//Limite superior, altura de la luz <---

		//if (subiendo) {										//si está activs ls vsriable / es verdadera = sube
		//	posY += 0.02f;									//es La VelocidaD de subida
		//	if (posY >= alturadLuz) {
		//		subiendo = false;							//aqui toca la luz, por lo que cambia de direccion
		//	}
		//}
		//else {
		//	posY -= 0.009f;									//es la velocidad de bajada
		//	if (posY <= 1.0f) {								//Limite inferior (nariz perro) <---
		//		subiendo = true;							//vuelve a tocar la nariz, va pa arriba de nuevo
		//	}
		//}
		// - - - - - - - -- - -- - - - - - - - - 
		
		//-->Version son el seno aaa
				//rebote trigonometrico del seno dependiente de la rotación de la pelota
		float alturaNariz = 1.0f;
		float alturadLuz = 1.5f;

		posY = alturaNariz + alturadLuz * abs(sin(glm::radians(rotBall * 1.5f)));
				//^ los límites fisicos (alturaNariz y alturadLuz) la encajan en el escenario
										//^abs - Como la ola del seno baja hasta -1, lapelota atravesaria el piso. El valor abs 
										// convierte todo lo negativo en positivo, por eso al llegar a 0, en lugar de seguiir 
										// bajando, la trayectoria "rebota" y vuelve a subir hacia 1
				
											//^sin - para crear la onda seno que sube y baja de forma limpia

																//^rotBall * 1.5 - son los grados que avanza la pelota (0 a 360)
																// al multiplicarlo por 1.5, es como si se dividiera en 3 partes
																// esto hace que cada 120 grados, lo que obliga a la pelota a estar 
																// en su punto mas bajo exactamente esas tres veces por cada vuelta 

	}
	else
	{
		//rotBall = 0.0f;
	}
	
	// ANIMACION DE PERRO  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	if (AnimDog)						//si está activs ls vsriable / es verdadera
	{
		rotDog += 0.8f;
		//printf("%f", rotBall);			//imprime en consola la variable


		////traslacion en  Y - - - - - - - - - - - - - 
		//		//Limite superior, altura minima de la pélota <---

		//if (subiendo) {										//si está activs ls vsriable / es verdadera = sube
		//	posY += 0.02f;									//es La VelocidaD de subida
		//	if (posY >= 1.0) {
		//		subiendo = false;							//aqui toca la luz, por lo que cambia de direccion
		//	}
		//}
		//else {
		//	posY -= 0.005f;									//es la velocidad de bajada
		//	if (posY <= 0.0f) {								//Limite inferior (piso) <---
		//		subiendo = true;							//vuelve a tocar la nariz, va pa arriba de nuevo
		//	}
		//}
		//// - - - - - - - -- - -- - - - - - - - - 

		//--> salto con coseno para que coincida con el seno de la pelota
		float ondadSalto = abs(cos(glm::radians(rotBall * 1.5f)));
												//^ por eso se tien que sincronizar con rotBall para que 
												// salte justo cuando la pelota cae, gracias al coseno

		posY2 = glm::max(0.0f, ondadSalto - 0.8f) * 3.0f; 
						//^ 0.0f - se queda en 0.0f el 80% del tiempo. solo salta en los picos
						// convierte cualquier valor negativo en 0

								//^ondaSalto - 0.8f - hace que se desplace la curva trigonometrica del cosno 
								// hacia abajo, para que solo la "punta" de la ola, el 20% superior, se tenga 
								// con un valor positivo (de 0.0 a 0.2). Todo lo demás se vuelve negativo para
								// que el perro siga en el suelo plano

													//^5.0 - Al multiplicarla por 5, ese pequeno pico se estira 
													// para alcanzar una altura mayor de 1.0 en el eje Y

		//--> movimiento del perro en el salto
		if (posY2 > 0.0f) {
			saltoDog = -sin(glm::radians(rotBall * 9.0f)) * 40.0f;
								//^-sen y rotBall - para que el perro se eleve mientras la pelota cae
							
												//^3.0 -  El multiplicador captura la pendiente de la onda para 
												// los saltos definidos. Menor valor hace que el perro solo se 
												// mueva poco en el aire; a mayor numero hace que el perro al 
												// brincar, de un cabezazo y se quiera ajustar para caer
															
															//^40.0 multiplicar por 40.0f para limitar la inclinacion 
															// máxima a unos 40 grados pa arriba y pa abajo
		}
		else {
			saltoDog = 0.0f; // Asegura que se mantenga recto al tocar el piso
		}


	}
	else
	{
		//rotDog = 0.0f;
	}
}

/*void Animation2() {
	if (AnimDog)						//si está activs ls vsriable / es verdadera
	{
		rotDog += 1.2f;
		//printf("%f", rotBall);			//imprime en consola la variable


		//traslacion en  Y
				//Limite superior, altura minima de la pélota <---

		if (subiendo2) {										//si está activs ls vsriable / es verdadera = sube
			posY2 += 0.02f;									//es La VelocidaD de subida
			if (posY2 >= 1.0) {
				subiendo2 = false;							//aqui toca la luz, por lo que cambia de direccion
			}
		}
		else {
			posY2 -= 0.005f;									//es la velocidad de bajada
			if (posY2 <= 0.0f) {								//Limite inferior (piso) <---
				subiendo2 = true;							//vuelve a tocar la nariz, va pa arriba de nuevo
			}
		}
		// - - - - - - - -- - -- - - - - - - - - 


	}
	else
	{
		//rotBall = 0.0f;
	}
}*/

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