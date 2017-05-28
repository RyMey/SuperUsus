#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <conio.h>
using namespace std;
float ySuper = -11;

void circleSuper(float size){
    int N = 30;
	float pX,pY;
	glBegin(GL_POLYGON);
	for(int i=0;i<N;i++){
		pX = sin(i*2*3.14/N);
		pY = cos(i*2*3.14/N);
		glVertex2f(pX*size,pY*size);
	}
	glEnd();
}

void SuperUsus(float size){
    circleSuper(size);
}

bool tembakSuper(float position){
    if(ySuper<12){
        glPushMatrix();
            glTranslatef(position,ySuper,1);
            circleSuper(0.5);
        glPopMatrix();

        ySuper +=1.5;
        Sleep(80);
        return true;
    }else{
        ySuper=-11;
        return false;
    }
}

void gerakSuper(float x,float y){
    glPushMatrix();
            glTranslatef(x,y+1.5,1);
            SuperUsus(1.5);
    glPopMatrix();
}
