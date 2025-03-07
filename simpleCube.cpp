// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "shader.hpp"
#include "texture.hpp"

void dessinerRepere(unsigned int echelle = 10)
{
  glPushMatrix();
  glScalef(echelle,echelle,echelle);
  glBegin(GL_LINES);
  glColor3ub(0,0,255);
  glVertex2i(0,0);
  glVertex2i(1,0);
  glColor3ub(0,255,0);
  glVertex2i(0,0);
  glVertex2i(0,1);
  glEnd();
  glPopMatrix();
}

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 05 - Textured Cube", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
  /*
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
               */
  //glm::mat4 View = glm::lookAt(glm::vec3(3,3,3), glm::vec3(-0.5,0.5,-0.5), glm::vec3(0,1,0));
  glm::mat4 View = glm::lookAt(glm::vec3(2,2,2), glm::vec3(-0.5,0.5,-0.5), glm::vec3(0,1,0));
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	// Load the texture using any two methods
	//GLuint Texture = loadBMP_custom("uvtemplate.bmp");
	GLuint Texture = loadDDS("minecraftMap.DDS");

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");


static const GLfloat g_vertex_buffer_data[] = {
   0.0f, 0.0f, 0.0f, // Front face
  -1.0f, 0.0f, 0.0f,
   0.0f, 1.0f, 0.0f,
  -1.0f, 1.0f, 0.0f,
   0.0f, 1.0f, 0.0f,
  -1.0f, 0.0f, 0.0f,

  0.0f, 0.0f,-1.0f, // Right face
  0.0f, 0.0f, 0.0f,
  0.0f, 1.0f,-1.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 1.0f,-1.0f,
  0.0f, 0.0f, 0.0f,

  0.0f, 0.0f, -1.0f, // Back face
 -1.0f, 0.0f, -1.0f,
  0.0f, 1.0f, -1.0f,
 -1.0f, 1.0f, -1.0f,
  0.0f, 1.0f, -1.0f,
 -1.0f, 0.0f, -1.0f,

 -1.0f, 0.0f,-1.0f, // Left face
 -1.0f, 0.0f, 0.0f,
 -1.0f, 1.0f,-1.0f,
 -1.0f, 1.0f, 0.0f,
 -1.0f, 1.0f,-1.0f,
 -1.0f, 0.0f, 0.0f,

 0.0f, 1.0f,  0.0f, // Top face
-1.0f, 1.0f,  0.0f,
 0.0f, 1.0f, -1.0f,
-1.0f, 1.0f, -1.0f,
 0.0f, 1.0f, -1.0f,
-1.0f, 1.0f,  0.0f,


 0.0f, 0.0f,  0.0f, // Bottom face
-1.0f, 0.0f,  0.0f,
 0.0f, 0.0f, -1.0f,
-1.0f, 0.0f, -1.0f,
 0.0f, 0.0f, -1.0f,
-1.0f, 0.0f,  0.0f
};

/*
// Two UV coordinatesfor each vertex. They were created with Blender.
static const GLfloat g_uv_buffer_data[] = {
  0.0f, 0.0f,
 -1.0f, 0.0f,
  0.0f, 1.0f,
  0.0f, 1.0f,
 -1.0f, 0.0f,
 -1.0f, 1.0f,
};




*/


std::map<std::string, std::vector<float>> blocksList;

//add some items to the map
blocksList["grass"] = {32.0f, 5.0f};
blocksList["dirt"] = {31.0f, 5.0f};
blocksList["stone"] = {30.0f, 5.0f};
blocksList["sand"] = {29.0f, 5.0f};

std::cout << blocksList["sand"][1] << std::endl;

// Two UV coordinatesfor each vertex. They were created with Blender.
const float texItemSize = 16;
const float grassXDecal = 3.0f/16.0f;
const float grassYDecal = 0;

const float grassTopXDecal = 15.0f/16.0f;
const float grassTopYDecal = 11.0f/16.0f;
static const GLfloat g_uv_buffer_data[] = {
  1.0f/texItemSize+grassXDecal, 1.0f/texItemSize+grassYDecal,
  0.0f+grassXDecal, 1.0f/texItemSize+grassYDecal,
  1.0f/texItemSize+grassXDecal, 0.0f+grassYDecal,

  0.0f+grassXDecal, 0.0f+grassYDecal,
  1.0f/texItemSize+grassXDecal, 0.0f+grassYDecal,
  0.0f+grassXDecal, 1.0f/texItemSize+grassYDecal,


  1.0f/texItemSize+grassXDecal, 1.0f/texItemSize+grassYDecal,
  0.0f+grassXDecal, 1.0f/texItemSize+grassYDecal,
  1.0f/texItemSize+grassXDecal, 0.0f+grassYDecal,

  0.0f+grassXDecal, 0.0f+grassYDecal,
  1.0f/texItemSize+grassXDecal, 0.0f+grassYDecal,
  0.0f+grassXDecal, 1.0f/texItemSize+grassYDecal,


  1.0f/texItemSize+grassXDecal, 1.0f/texItemSize+grassYDecal,
  0.0f+grassXDecal, 1.0f/texItemSize+grassYDecal,
  1.0f/texItemSize+grassXDecal, 0.0f+grassYDecal,

  0.0f+grassXDecal, 0.0f+grassYDecal,
  1.0f/texItemSize+grassXDecal, 0.0f+grassYDecal,
  0.0f+grassXDecal, 1.0f/texItemSize+grassYDecal,


  1.0f/texItemSize+grassXDecal, 1.0f/texItemSize+grassYDecal,
  0.0f+grassXDecal, 1.0f/texItemSize+grassYDecal,
  1.0f/texItemSize+grassXDecal, 0.0f+grassYDecal,

  0.0f+grassXDecal, 0.0f+grassYDecal,
  1.0f/texItemSize+grassXDecal, 0.0f+grassYDecal,
  0.0f+grassXDecal, 1.0f/texItemSize+grassYDecal,


  1.0f/texItemSize+grassTopXDecal, 1.0f/texItemSize+grassTopYDecal,
  0.0f+grassTopXDecal, 1.0f/texItemSize+grassTopYDecal,
  1.0f/texItemSize+grassTopXDecal, 0.0f+grassTopYDecal,

  0.0f+grassTopXDecal, 0.0f+grassTopYDecal,
  1.0f/texItemSize+grassTopXDecal, 0.0f+grassTopYDecal,
  0.0f+grassTopXDecal, 1.0f/texItemSize+grassTopYDecal,
};


	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	do{

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
  // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
       dessinerRepere();

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
