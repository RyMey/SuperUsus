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

