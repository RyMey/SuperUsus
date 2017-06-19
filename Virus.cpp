#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <conio.h>
using namespace std;
float yVirus = 11;
int maksVirus = 4;

struct Virus{
    float x=(rand()%12)-6;
    float y=(rand()%5)+11;
};

Virus virus[8];

void createVirus(int x){
    glColor3ub(255,255,255);
    glEnable(GL_TEXTURE_2D);
        glBindTexture (GL_TEXTURE_2D, x);
            glBegin(GL_POLYGON);
                glTexCoord2f(0, 0);
                glVertex3f(-2, -2, 0);
                glTexCoord2f(1, 0);
                glVertex3f(2, -2, 0);
                glTexCoord2f(1, 1);
                glVertex3f(2, 2, 0);
                glTexCoord2f(0, 1);
                glVertex3f(-2, 2, 0);
            glEnd();
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

bool isVirusNotCrossSuper(float x, float y){
    float batasAtas=(x+2),batasBawah=(x-2);
    if((x+2)<(x-2)){
        batasAtas = (x+2);
        batasBawah = (x-2);
    }

    if(y-2<=-9 && batasBawah<=getXSuper() && getXSuper()<=batasAtas)
        return false;
    else
        return true;
}

void renderVirus(int score) {
    if(maksVirus<8)
        maksVirus = 4 + (score/20);
    for (int i=0;i<maksVirus;i++) {
        if (virus[i].y > -12 && virus[i].y < 12 && isVirusNotCrossSuper(virus[i].x,virus[i].y)) {
            glPushMatrix();
                glTranslated(virus[i].x,virus[i].y,1);
                createVirus(i+8);
            glPopMatrix();
            virus[i].y -= 0.15 *((score/30) + 0.25);
        }else{
            if(!isVirusNotCrossSuper(virus[i].x,virus[i].y))
                setNyawa(getNyawa()-1);

            virus[i].y = (rand()%4)+11;
            virus[i].x = (rand()%12)-6;
        }
    }
}


