#version 330 core
//Comentado porque ahora se va a usar otra varriable
//in vec3 ourColor;

out vec4 color;

//Esta es la nueva variable que recibe el color desde ahora glUniform3f 
uniform vec3 colorCubo;

void main()
{
	//color = vec4(ourColor, 1.0f);

	//ahora se le asignaría el color del uniform en lugar del color de los vértices
	color = vec4(colorCubo, 1.0f);
}