#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <conio.h>
using namespace std;
float ySuperUsus = 11;
float xSuperUsus=0; //untuk gerakan/posisi x milik super usus
float minTembakan = -9;
float rSuper=1.5;
int nyawa = 3;
struct Peluru {
    float x=-12;
    float y=minTembakan;
};

Peluru pels[12];

void createSuperUsus(){
    glColor3ub(255,255,255);
    glEnable(GL_TEXTURE_2D);
        glBindTexture (GL_TEXTURE_2D, 6);
            glBegin(GL_POLYGON);
                glTexCoord2f(0, 0);
                glVertex3f(-rSuper, -ySuperUsus, 0);
                glTexCoord2f(1, 0);
                glVertex3f(rSuper, -ySuperUsus, 0);
                glTexCoord2f(1, 1);
                glVertex3f(rSuper, -ySuperUsus+4, 0);
                glTexCoord2f(0, 1);
                glVertex3f(-rSuper,-ySuperUsus+4, 0);
            glEnd();
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

float getXSuper(){
    return xSuperUsus;
}

float getRSuper(){
    return rSuper;
}

bool tembak(float pos) {
    int nextPel = -1;
    for (int i=0;i<12;i++) {
        if (pels[i].y == minTembakan) {
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
    for (int i=0;i<12;i++) {
        if (pels[i].y > minTembakan && pels[i].y < 12) {
            glPushMatrix();
                glTranslatef(pels[i].x,pels[i].y,1);
                glColor3ub(162,94,154);
                circle(0.4);
            glPopMatrix();
            pels[i].y += 1.5;
        }else{
            pels[i].y = minTembakan;
        }
    }
}

void setNyawa(int n){
    nyawa = n;
}

int getNyawa(){
    return nyawa;
}

void gerakSuper(float x){
    glPushMatrix();
        glTranslatef(x,-1,1);
        createSuperUsus();
    glPopMatrix();
}
