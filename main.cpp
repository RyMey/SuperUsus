#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
float x=0;
bool play = false;
bool gameOver = false;
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE); // close program on ESC key
}

void processNormalKeys(GLFWwindow* window, int key, int scancode, int action,int mods) {
	if(key==GLFW_KEY_ENTER && action == GLFW_PRESS){
            play = true;
            gameOver = false;
    }else if(key==GLFW_KEY_UP && action == GLFW_PRESS) {

	}else if(key==GLFW_KEY_LEFT && action == GLFW_PRESS) {
		if(x-1<-10)
			gameOver = true;
		else
			x-=1;
	}else if(key==GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		if(x+1>10)
			gameOver = true;
		else
			x+=1;
	}
}

void setup_viewport(GLFWwindow* window)
{
   float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, 1000.f, -1000.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void grid(){
	glBegin(GL_LINES);
	for(int i=0;i<=20;i++){
		if(-10+i==0)
			glColor3ub(192,192,192);
		else
			glColor3ub(128,128,128);
		glVertex2f(-10+i,10);
		glVertex2f(-10+i,-10);
	}
	glEnd();

	glBegin(GL_LINES);
	for(int i=0;i<=20;i++){
		if(-10+i==0)
			glColor3ub(192,192,192);
		else
			glColor3ub(128,128,128);
		glVertex2f(10,-10+i);
		glVertex2f(-10,-10+i);
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

void bgMenu(){
    glColor3ub(255,230,0);
    rectangle(600,600);
}

void bgGameOver(){
    glColor3ub(255,0,0);
    rectangle(600,600);
}

void display()
{
    if(gameOver){
        bgGameOver();
        x=0;
    }else if(!play){
        bgMenu();
        x=0;
    }else{
        glColor3ub(0,0,255);
        glPushMatrix();
            glTranslatef(x,-8,1);
            circle(1.0);
        glPopMatrix();
    }
}

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit()) exit(EXIT_FAILURE);

    window = glfwCreateWindow(600, 600, "Game Mini", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    glfwSetKeyCallback(window,processNormalKeys);

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
