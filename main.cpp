//supersus
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include "lib/tga.h"
#include "lib/tga.c"
#include "Util.cpp"
#include "SuperUsus.cpp"
#include "Virus.cpp"
using namespace std;
float x=0,xTembak;
bool play = false;
bool gameOver = false;
bool tembak = false;
int pixelX = 11;
int pixelY = 12;
int weightDisplay = 529;
int heightDisplay = 600;

void processNormalKeys(GLFWwindow* window, int key, int scancode, int action,int mods){
	if(key==GLFW_KEY_ENTER && action == GLFW_PRESS){
            play = true;
            gameOver = false;
    }else if(key==GLFW_KEY_UP && action == GLFW_PRESS && !tembak) {
            tembak = true;
            xTembak = x;
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

void setup_viewport(GLFWwindow* window){
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

void tekstur(){
    load_bmp("texture/bg_start.bmp", 0);
    load_bmp("texture/ic_su_start.bmp", 1);
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

void iconStart(){
    glEnable(GL_TEXTURE_2D);
        glBindTexture (GL_TEXTURE_2D, 1);
            glBegin(GL_POLYGON);
                glTexCoord2f(0, 0);
                glVertex3f(-8, -8, 0);
                glTexCoord2f(1, 0);
                glVertex3f(8, -8, 0);
                glTexCoord2f(1, 1);
                glVertex3f(8, 8, 0);
                glTexCoord2f(0, 1);
                glVertex3f(-8, 8, 0);
            glEnd();
        glEnd();
    glDisable(GL_TEXTURE_2D);

}
void bgMenu(){
    glColor3ub(255,255,255);
    glEnable(GL_TEXTURE_2D);
        glBindTexture (GL_TEXTURE_2D, 0);
            glBegin(GL_POLYGON);
                glTexCoord2f(0, 0);
                glVertex3f(-pixelX, -pixelY, 0);
                glTexCoord2f(1, 0);
                glVertex3f(pixelX, -pixelY, 0);
                glTexCoord2f(1, 1);
                glVertex3f(pixelX, pixelY, 0);
                glTexCoord2f(0, 1);
                glVertex3f(-pixelX, pixelY, 0);
            glEnd();
        glEnd();
    glDisable(GL_TEXTURE_2D);

    iconStart();

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

void display(){
    tekstur();
    if(gameOver){
        bgGameOver();
        x=0;
    }else if(!play){
        bgMenu();
        x=0;
    }else{
        bgGamePlay();
        if(tembak){
          tembak = tembakSuper(xTembak);
        }
        gerakSuper(x,-pixelY);
    }

   // grid();
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
    glfwSetKeyCallback(window, processNormalKeys);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_POINT_SMOOTH);

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
