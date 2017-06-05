#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <conio.h>
using namespace std;
float yVirus = 11;

void Virus(float size){
    glColor3ub(255,0,0);
    circle(size);
}

bool tembakVirus(float position){
    if(yVirus<12){
        glPushMatrix();
            glTranslatef(position,yVirus,1);
            circle(0.5);
        glPopMatrix();

        yVirus +=1.5;
        Sleep(50);
        return true;
    }else{
        yVirus=-11;
        return false;
    }
}

void addVirus(float x){
    glPushMatrix();
            glTranslatef(x,yVirus+1.5,1);
            Virus(1.5);
    glPopMatrix();
    yVirus--;
}

