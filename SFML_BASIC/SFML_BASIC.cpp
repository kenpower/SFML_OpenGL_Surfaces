//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#include "GL/glu.h"
#include "math.h"  

const float twoPI = 2 * 3.141f;
 
void ParametricCylinder(float t, float phi, float xStart, float xEnd, float r, float returnPoint[3]) {

	returnPoint[0] = xStart*(1 - t) + xEnd*t;//x coord of point on surface
	returnPoint[1] = r*cos(phi);//y coord of point on surface
	returnPoint[2] = r*sin(phi);//z coord of point on surface

}

void DrawCylinder() {
	float dt = 0.2f, dphi = 0.5f;

	float point[3];
	float xStart = -0.5, xEnd = +0.5, radius = 0.2;

	glBegin(GL_QUADS);
	for (float t = 0; t < 1; t += dt) {
		for (float phi = 0; phi < twoPI; phi += dphi) {
			ParametricCylinder(t, phi, xStart, xEnd, radius, point);
			glVertex3fv(point);
			ParametricCylinder(t + dt, phi, xStart, xEnd, radius, point);
			glVertex3fv(point);
			ParametricCylinder(t + dt, phi + dphi, xStart, xEnd, radius, point);
			glVertex3fv(point);
			ParametricCylinder(t, phi + dphi, xStart, xEnd, radius, point);
			glVertex3fv(point);

		}
	}
	glEnd();
}
  

void ParametricSphere(float t, float phi,  float r, float returnPoint[3]) {

	returnPoint[0] = r*cos(t)*cos(phi);//x coord of point on surface
	returnPoint[1] = r*cos(t)*sin(phi);//y coord of point on surface
	returnPoint[2] = r*sin(t);//z coord of point on surface

}

void DrawSphere() {
	float dt = 0.2f, dphi = 0.5f;

	float point[3];
	float radius = 0.2;

	glBegin(GL_QUADS);
	for (float t = 0; t < 1; t += dt) {
		for (float phi = 0; phi < twoPI; phi += dphi) {
			ParametricSphere(t, phi,  radius, point);
			glVertex3fv(point);
			ParametricSphere(t + dt, phi,  radius, point);
			glVertex3fv(point);
			ParametricSphere(t + dt, phi + dphi,  radius, point);
			glVertex3fv(point);
			ParametricSphere(t, phi + dphi, radius, point);
			glVertex3fv(point);

		}
	}
	glEnd();
}

void ParametricTorus(float t, float phi, float minorR, float majorR,float returnPoint[3]) {

	returnPoint[0] = (majorR+minorR*cos(t))*cos(phi);//x coord of point on surface
	returnPoint[1] = (majorR + minorR*cos(t))*sin(phi);//y coord of point on surface
	returnPoint[2] = minorR*sin(t);//z coord of point on surface

}

void DrawTorus() {
	int stepsT = 20, stepsPHI = 10;

	float dt = twoPI / stepsT, dphi = twoPI / stepsPHI;

	float point[3];
	float r = 0.2, R=0.5;

	glBegin(GL_QUADS);
	for (float t = 0; t <= twoPI; t += dt) {
		for (float phi = 0; phi <= twoPI; phi += dphi) {
			ParametricTorus(t, phi, r,R, point);
			glVertex3fv(point);
			ParametricTorus(t + dt, phi, r, R, point);
			glVertex3fv(point);
			ParametricTorus(t + dt, phi + dphi, r, R, point);
			glVertex3fv(point);
			ParametricTorus(t, phi + dphi, r, R, point);
			glVertex3fv(point);

		}
	}
	glEnd();
}

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 


int main() 
{ 
    // Create the main window 
	int width = 1024, height = 1024;
    sf::RenderWindow App(sf::VideoMode(width,height, 32), "SFML OpenGL"); 

    // Create a clock for measuring time elapsed     
    sf::Clock Clock; 
      
    //prepare OpenGL surface for HSR 
    glClearDepth(1.f); 
    glClearColor(0.3f, 0.3f, 0.3f, 0.f); //background colour
    glEnable(GL_DEPTH_TEST); 
    glDepthMask(GL_TRUE); 
	
 



    // Start game loop 
    while (App.isOpen()) 
    { 
        // Process events 
        sf::Event Event; 
        while (App.pollEvent(Event)) 
        { 
            // Close window : exit 
            if (Event.type == sf::Event::Closed) 
                App.close(); 
   
            // Escape key : exit 
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)) 
                App.close(); 
             
    
        } 
           
        //Prepare for drawing 
        // Clear color and depth buffer 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		//// Setup a perspective projection & Camera position 
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//set up a 3D Perspective View volume
		//gluPerspective(90.f, (float)width/height, 1.f, 300.0f);//fov, aspect, zNear, zFar 
        // Apply some transformations 
		//set up a  orthographic projection same size as window
		//this means the vertex coordinates are in pixel space
		//glOrtho(-2,2,-2,2,0,10); // use pixel coordinates




		//glMatrixMode(GL_PROJECTION); // reset projection matrix
		//glLoadIdentity();

		//calculate new prespective and aspect ratio
		gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,1.f,1000.0f);

        glMatrixMode(GL_MODELVIEW); 
        glLoadIdentity(); 
         
		glTranslatef(0,0,-2); //push back 10 units from camera
		//gluLookAt(	0,0,100,// camera position
		//			0,0,0, //look at this point
		//			0,1,0); //camera up

		static float ang=0.0;
		glRotatef(ang,0,0,1); //spin about x-axis
		glRotatef(ang*2,0,1,0);//spin about y-axis
		

		ang+=0.05f;

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		DrawCylinder();
		   
        // Finally, display rendered frame on screen 
        App.display(); 
    } 
   
    return EXIT_SUCCESS; 
}


