#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <conio.h>
using namespace std;
float ySuper = -11;

void SuperUsus(float size){
    circle(size);
}

bool tembakSuper(float position){
    if(ySuper<12){
        glPushMatrix();
            glTranslatef(position,ySuper,1);
            circle(0.5);
        glPopMatrix();

        ySuper +=1.5;
        Sleep(50);
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
