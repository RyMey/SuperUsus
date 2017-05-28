#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include "SuperUsus.cpp"
using namespace std;
float x=0;
bool play = false;
bool gameOver = false;
bool tembak = false;
int pixelX = 11;
int pixelY = 12;
int weightDisplay = 529;
int heightDisplay = 600;

void processNormalKeys(GLFWwindow* window, int key, int scancode, int action,int mods) {
	if(key==GLFW_KEY_ENTER && action == GLFW_PRESS){
            play = true;
            gameOver = false;
    }else if(key==GLFW_KEY_UP && action == GLFW_PRESS) {
            tembak = true;
	}else if(key==GLFW_KEY_LEFT && action == GLFW_PRESS) {
		if(x-1<=-pixelX+3)
			gameOver = true;
		else
			x-=1;
	}else if(key==GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		if(x+1>=pixelX-3)
			gameOver = true;
		else
			x+=1;
	}else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void setup_viewport(GLFWwindow* window)
{
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-pixelX, pixelX, -pixelY, pixelY, 1000.f, -1000.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void grid(){
    //vertikal
	glBegin(GL_LINES);
	for(int i=0;i<=2*pixelX;i++){
		if(-pixelX+i==0)
			glColor3ub(192,192,192);
		else
			glColor3ub(128,128,128);
		glVertex2f(-pixelX+i,pixelY);
		glVertex2f(-pixelX+i,-pixelY);
	}
	glEnd();

	//horizontal
	glBegin(GL_LINES);
	for(int i=0;i<=2*pixelY;i++){
		if(-pixelY+i==0)
			glColor3ub(192,192,192);
		else
			glColor3ub(128,128,128);
		glVertex2f(pixelX,-pixelY+i);
		glVertex2f(-pixelX,-pixelY+i);
	}
	glEnd();
}

void rectangle(float p, float l){
    float x0 = 0-(p/2.0);
    float y0 = 0-(l/2.0);
    float xend = 0+(p/2.0);
    float yend = 0+(l/2.0);

    glBegin(GL_POLYGON);
	glVertex2f(x0, y0);
    glVertex2f(xend, y0);
    glVertex2f(xend,yend);
    glVertex2f(x0,yend);
    glEnd();
}

void bgMenu(){
    glColor3ub(255,230,0);
    rectangle(weightDisplay,heightDisplay);
}

void bgGameOver(){
    glColor3ub(255,0,0);
    rectangle(weightDisplay,heightDisplay);
}

void bgGamePlay(){
    glColor3b(40,40,40);
    rectangle(weightDisplay,heightDisplay);
    glColor3b(255,255,255);
    glPushMatrix();
        glTranslatef(-9.5,0,1);
        rectangle(3,heightDisplay);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(9.5,0,1);
        rectangle(3,heightDisplay);
    glPopMatrix();
}

void display()
{
    if(gameOver){
        bgGameOver();
        x=0;
    }else if(!play){
        bgMenu();
        x=0;
    }else{
        bgGamePlay();
        glColor3ub(0,0,255);
        gerakSuper(x,-pixelY);
    }

    if(tembak){
      tembak = tembakSuper(x);
    }

    grid();
}

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit()) exit(EXIT_FAILURE);

    window = glfwCreateWindow(weightDisplay, heightDisplay, "Super Usus", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window,processNormalKeys);

    while (!glfwWindowShouldClose(window))
    {
        setup_viewport(window);

        grid();
        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}
