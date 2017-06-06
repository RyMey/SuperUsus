#include <string>
using namespace std;
void renderBitmapString(string str,int font){
    int len;
    glRasterPos2i(0,0);

    glDisable(GL_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    for(int i=0,len = str.size();i<len;i++){
        if(font==0)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,(int)str[i]);
        else if(font==1)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)str[i]);
        else if(font==2)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,(int)str[i]);
        else if(font==3)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,(int)str[i]);
        else if(font==4)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(int)str[i]);
    }
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE);
}

void tekstur(){
    load_bmp("texture/bg_menu.bmp", 0);
    load_bmp("texture/bg_gameOver.bmp", 1);
    load_bmp("texture/bg_rectPlay.bmp", 2);
    load_bmp("texture/bg_nyawa1.bmp", 3);
    load_bmp("texture/bg_nyawa2.bmp", 4);
    load_bmp("texture/bg_nyawa3.bmp", 5);
    load_bmp("texture/ic_su.bmp", 6);
    load_bmp("texture/bg_play.bmp", 7);
}

double getDigit(int no){
    double a=0;
    while(no>0)
    {
        no=no/10;
        a++;
    }
    return a;
}

void circle(float size){
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

void rectangle(float p, float l){
    float x0 = 0-(p/2.0);
    float y0 = 0-(l/2.0);
    float xend = 0+(p/2.0);
    float yend = 0+(l/2.0);

    glBegin(GL_POLYGON);
	glVertex2f(x0, y0);
    glVertex2f(xend, y0);
    glVertex2f(xend,yend);
    glVertex2f(x0,yend);
    glEnd();
}

