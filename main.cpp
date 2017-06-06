//supersus
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <sstream>
#include <string>
#include "lib/tga.h"
#include "lib/tga.c"
#include "Util.cpp"
#include "SuperUsus.cpp"
using namespace std;
float x=0,xTembak;
bool play = false;
bool gameOver = false;
bool tembak = false;
bool isPrint = false;
int pixelX = 11;
int pixelY = 12;
int weightDisplay = 529;
int heightDisplay = 600;
int num=0;
int score = 0;
int highScore = 0;
stringstream ss,hs;

void processNormalKeys(GLFWwindow* window, int key, int scancode, int action,int mods){
	if(key==GLFW_KEY_ENTER && action == GLFW_PRESS){
            play = true;
            gameOver = false;
            mciSendString("stop sounds/main.mp3",NULL,NULL,NULL);
            mciSendString("stop sounds/over.mp3",NULL,NULL,NULL);
            mciSendString("play sounds/start.mp3",NULL,NULL,NULL);
    }else if(key==GLFW_KEY_UP && action == GLFW_PRESS && !tembak) {
            tembak = true;
            xTembak = x;
            mciSendString("play sounds/peluruSu.wav",NULL,NULL,NULL);
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
    mciSendString("play sounds/main.mp3",NULL,NULL,NULL);

}

void bgGameOver(){
    glColor3ub(255,255,255);
    glEnable(GL_TEXTURE_2D);
    glBindTexture (GL_TEXTURE_2D, 1);
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
    mciSendString("stop sounds/start.mp3",NULL,NULL,NULL);
    mciSendString("play sounds/over.mp3",NULL,NULL,NULL);
    if(num%3!=0){
        glPushMatrix();
            glTranslated(-4.5,-4,0);
            glColor3ub(255,255,255);
            renderBitmapString("Press Enter to Play Again",1);
        glPopMatrix();

        Sleep(750);
    }

    if(!isPrint){
        ss << "Score :  " << score;
        hs << "High Score :  " << highScore;
        isPrint = true;
    }

    glPushMatrix();
            glTranslated(-4.5,-6,0);
            glColor3ub(255,255,255);
            renderBitmapString(ss.str() ,3);
    glPopMatrix();

    glPushMatrix();
            glTranslated(-4.5,-7.5,0);
            glColor3ub(255,255,255);
            renderBitmapString(hs.str(),3);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-3,-11,0);
        glColor3ub(255,50,50);
        renderBitmapString("Press Esc to Exit",1);
    glPopMatrix();
}

void bgRectanglePlay(int i){
    glColor3ub(255,255,255);
    glEnable(GL_TEXTURE_2D);
    if(i==0)
        glBindTexture (GL_TEXTURE_2D, 2);
    else if(i==1)
        glBindTexture (GL_TEXTURE_2D, 3);
    else if(i==2)
        glBindTexture (GL_TEXTURE_2D, 4);
    else if(i==3)
        glBindTexture (GL_TEXTURE_2D, 5);

        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-pixelX, -pixelY, 0);
            glTexCoord2f(1, 0);
            glVertex3f(-pixelX+2.5, -pixelY, 0);
            glTexCoord2f(1, 1);
            glVertex3f(-pixelX+2.5, pixelY, 0);
            glTexCoord2f(0, 1);
            glVertex3f(-pixelX, pixelY, 0);
        glEnd();
    glEnd();
}

void bgGamePlay(){
    glColor3ub(255,255,255);
    glEnable(GL_TEXTURE_2D);
    glBindTexture (GL_TEXTURE_2D, 7);
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

    bgRectanglePlay(0);
    glPushMatrix();
        glTranslatef(2*pixelX-2.5,0,0);
        bgRectanglePlay(3);
    glPopMatrix();
}

void display(){
    tekstur();
    if(gameOver){
        num++;
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
        gerakSuper(x,-1);
    }
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
