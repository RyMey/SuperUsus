#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <conio.h>
using namespace std;
float ySuper = -6;
float ySuperP = 11;

void SuperUsus(){
    glColor3ub(255,255,255);
    glEnable(GL_TEXTURE_2D);
    glBindTexture (GL_TEXTURE_2D, 6);
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-1.75, -ySuperP, 0);
            glTexCoord2f(1, 0);
            glVertex3f(1.75, -ySuperP, 0);
            glTexCoord2f(1, 1);
            glVertex3f(1.75, -ySuperP+5, 0);
            glTexCoord2f(0, 1);
            glVertex3f(-1.75,-ySuperP+5, 0);
        glEnd();
    glEnd();
}

bool tembakSuper(float position){
    if(ySuper<12){
        glPushMatrix();
            glTranslatef(position,ySuper,1);
            glColor3ub(162,94,154);
            circle(0.5);
        glPopMatrix();

        ySuper +=1.5;
        Sleep(50);
        return true;
    }else{
        ySuper=-6;
        return false;
    }
}

void gerakSuper(float x,float y){
    glPushMatrix();
        glTranslatef(x,y,1);
        SuperUsus();
    glPopMatrix();
}
