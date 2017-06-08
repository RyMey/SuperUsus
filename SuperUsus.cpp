#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <conio.h>
using namespace std;
float ySuperP = 11;

struct peluru {
    float x=-12;
    float y=-6;
};

peluru pels[12];

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

bool tembak(float pos) {
    int nextPel = -1;
    for (int i=0;i<12;i++) {
        if (pels[i].y == -6) {
            nextPel = i;
            break;
        }
    }

    if (nextPel <= -1){
        return false;
    }

    pels[nextPel].y += 1;
    pels[nextPel].x = pos;
    return true;
}

void renderPeluru() {
    Sleep(50);
    for (int i=0;i<12;i++) {
        if (pels[i].y > -6 && pels[i].y < 12) {
            glPushMatrix();
                glTranslatef(pels[i].x,pels[i].y,1);
                glColor3ub(162,94,154);
                circle(0.5);
            glPopMatrix();
            pels[i].y += 1.5;
        }else{
            pels[i].y = -6;
        }
    }
}

void gerakSuper(float x,float y){
    glPushMatrix();
        glTranslatef(x,y,1);
        SuperUsus();
    glPopMatrix();
}
