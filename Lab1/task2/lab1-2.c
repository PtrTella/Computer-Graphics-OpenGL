// Lab 1-1.
// This is the same as the first simple example in the course book,
// but with a few error checks.
// Remember to copy your file to a new on appropriate places during the lab so you keep old results.
// Note that the files "lab1-1.frag", "lab1-1.vert" are required.

#include "GL_utilities.h"
#include "MicroGlut.h"
#include "math.h"
// uses framework OpenGL
// uses framework Cocoa

// Globals
// Data would normally be read from files
GLfloat vertices[] =
{
	-0.6f,-0.5f,0.0f,
	-0.3f,0.7f,0.0f,
	0.5f,-0.5f,0.0f
};

GLfloat myMatrix[] = {    1.0f, 0.0f, 0.0f, 0.5f,

                        0.0f, 1.0f, 0.0f, 0.0f,

                        0.0f, 0.0f, 1.0f, 0.0f,

                        0.0f, 0.0f, 0.0f, 1.0f };

GLfloat myMatrixDUO[] = { 	cos(1), -sin(1), 0.0f, 0.0f,
                       		sin(1), cos(1),  0.0f, 0.0f,
                       		0.0f,         0.0f,          1.0f, 0.0f,
                       		0.0f,         0.0f,          0.0f, 1.0f };

// vertex array object
unsigned int vertexArrayObjID;

void init(void)
{
	// vertex buffer object, used for uploading the geometry
	unsigned int vertexBufferObjID;
	// Reference to shader program
	GLuint program;

	dumpInfo();

	// GL inits
	glClearColor(0.2,0.2,0.2,0);
	glDisable(GL_DEPTH_TEST);
	printError("GL inits");

	// Load and compile shader
	program = loadShaders("lab1-2.vert", "lab1-2.frag");
	printError("init shader");
	
	// Upload geometry to the GPU:
	
	// Allocate and activate Vertex Array Object
	glGenVertexArrays(1, &vertexArrayObjID);
	glBindVertexArray(vertexArrayObjID);
	// Allocate Vertex Buffer Objects
	glGenBuffers(1, &vertexBufferObjID);
	
	// VBO for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));

	//COlor change
	int vertexColorLocation = glGetUniformLocation(program, "in_frag_color");
    glUniform4f(vertexColorLocation, 0.796,0.196,0.204, 1.0); 

	//Matrix application
	glUniformMatrix4fv(glGetUniformLocation(program, "myMatrix"), 1, GL_TRUE, myMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "myMatrixDUO"), 1, GL_TRUE, myMatrixDUO);
	
	// End of upload of geometry
	
	printError("init arrays");
}


void display(void)
{
	printError("pre display");

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vertexArrayObjID);	// Select VAO
	glDrawArrays(GL_TRIANGLES, 0, 3);	// draw object

	printError("display");
	
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 2);
	glutInitWindowSize(600, 600);
	glutCreateWindow ("GL3 white triangle example LAB 2");
	glutDisplayFunc(display); 
	init ();
	glutMainLoop();
	return 0;
}
