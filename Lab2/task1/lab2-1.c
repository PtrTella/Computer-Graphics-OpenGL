// Lab 1-1.
// This is the same as the first simple example in the course book,
// but with a few error checks.
// Remember to copy your file to a new on appropriate places during the lab so you keep old results.
// Note that the files "lab1-1.frag", "lab1-1.vert" are required.

// Should work as is on Linux and Mac. MS Windows needs GLEW or glee.
// See separate Visual Studio version of my demos.
#ifdef __APPLE__
	#include <OpenGL/gl3.h>
	// Linking hint for Lightweight IDE
	// uses framework Cocoa
#endif
#include "MicroGlut.h"
#include "GL_utilities.h"
#include <math.h>
#include <stdio.h>
#include "../common/LittleOBJLoader.h"
#include "../common/VectorUtils3.h"



GLfloat color[] = 
{
	1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,

	
};

mat4 transform;
//Maek teh madel!
Model *m;


// vertex array object
unsigned int bunnyVertexArrayObjID;
GLfloat t;
GLuint program;

void init(void)
{
	// Load objects for bunny
	
	
	unsigned int bunnyVertexBufferObjID;
	
	unsigned int bunnyIndexBufferObjID;
	
	unsigned int bunnyNormalBufferObjID;

	unsigned int bunnyTexCoordBufferObjID;
	
	//Load teh banny
	m = LoadModel("bunnyplus.obj");
	dumpInfo();

	// GL inits
	glClearColor(0.3,0.3,0.3,0);
	//glDisable(GL_DEPTH_TEST);
	printError("GL inits");

	
	// Load and compile shader
	program = loadShaders("lab2-1.vert", "lab2-1.frag");
	printError("init shader");
	
	// Upload geometry to the GPU:
	
	// Allocate and activate Vertex Array Object
	glGenVertexArrays(1, &bunnyVertexArrayObjID);
	glGenBuffers(1, &bunnyVertexBufferObjID);
	glGenBuffers(1, &bunnyIndexBufferObjID);
	glGenBuffers(1, &bunnyNormalBufferObjID);
	glGenBuffers(1, &bunnyTexCoordBufferObjID);
	glBindVertexArray(bunnyVertexArrayObjID);
	
	
	// VBO for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, bunnyVertexBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, m->numVertices*3*sizeof(GLfloat), m->vertexArray, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));
	
	// VBO for normal data
	glBindBuffer(GL_ARRAY_BUFFER, bunnyNormalBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, m->numVertices*3*sizeof(GLfloat), m->normalArray, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Normal"));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bunnyIndexBufferObjID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->numIndices*sizeof(GLuint), m->indexArray, GL_STATIC_DRAW);
	if(m->texCoordArray != NULL)
	{
		glBindBuffer(GL_ARRAY_BUFFER, bunnyTexCoordBufferObjID);
		glBufferData(GL_ARRAY_BUFFER, m->numVertices*2*sizeof(GLfloat), m->texCoordArray, GL_STATIC_DRAW);
		glVertexAttribPointer(glGetAttribLocation(program, "inTexCoord"), 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(glGetAttribLocation(program, "inTexCoord"));
	}

	
	printError("init arrays");

	

}


void display(void)
{
	printError("pre display");

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(bunnyVertexArrayObjID);    // Select VAO
	glDrawElements(GL_TRIANGLES, m->numIndices, GL_UNSIGNED_INT, 0L);
	
	
	printError("display");
	
	glutSwapBuffers();
}


void onTimer(int value)
{
	
	t = (GLfloat)glutGet(GLUT_ELAPSED_TIME) * M_PI / (2*1000);
	glUniform1f(glGetUniformLocation(program, "uniTime"), t*10);
	transform = Mult(Rx(t), Rz(t));
	glUniformMatrix4fv(glGetUniformLocation(program, "uniTransform"), 1, GL_TRUE, transform.m);
	glutPostRedisplay();	
	glutTimerFunc(20, &onTimer, value); //50 FPS
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 2);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow ("Trippy sandstorm Bunny");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutTimerFunc(20, &onTimer, 0); 
	init ();
	glutMainLoop();
	return 0;
}