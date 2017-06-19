#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <conio.h>
using namespace std;
float yVirus = 11;
int maksVirus = 4;
int score = 0;

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

bool isVirusKenaPeluru(float x, float y){
    bool aw = false; //virus ketembak
    float batasAtas=(x+2),batasBawah=(x-2);
    if((x+2)<(x-2)){
        batasAtas = (x+2);
        batasBawah = (x-2);
    }

    for(int i=0;i<12;i++){
        if(y-2<=pels[i].y && batasBawah<=pels[i].x && pels[i].x<=batasAtas){
            pels[i].y = minTembakan;
            score++;
            aw = true;
            mciSendString("play sounds/aw.wav",NULL,NULL,NULL);
        }
    }

    return aw;
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

void inisiateVirus(){
    maksVirus = 4;
    for(int i=0;i<8;i++){
        virus[i].x = (rand()%12)-6;
        virus[i].y = (rand()%12)+11;
    }
}

void renderVirus(int score) {
    if(maksVirus<8)
        maksVirus = 4 + (score/20);
    for (int i=0;i<maksVirus;i++) {
        if (virus[i].y > -12 && virus[i].y < 12 && isVirusNotCrossSuper(virus[i].x,virus[i].y) && !isVirusKenaPeluru(virus[i].x,virus[i].y)) {
            glPushMatrix();
                glTranslated(virus[i].x,virus[i].y,1);
                createVirus(i+8);
            glPopMatrix();
            virus[i].y -= 0.05 *(score/30) + 0.15;;
        }else{
            if(!isVirusNotCrossSuper(virus[i].x,virus[i].y) || virus[i].y<=-12){
                setNyawa(getNyawa()-1);
                mciSendString("play sounds/aduh.wav",NULL,NULL,NULL);
            }

            virus[i].y = (rand()%4)+11;
            virus[i].x = (rand()%12)-6;
        }
    }
}



