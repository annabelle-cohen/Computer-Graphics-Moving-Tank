#include "glut.h"
#include <math.h>
#include <time.h>
#include <stdio.h>

const double PI = 3.14;
const int W = 600, H = 600;

//rocket params
double mouse_x = -0.6, mouse_y = 0.28;
bool throw_rocket = false;
double vx, vy;// initial rocket speed
double bx0 = mouse_x, by0 = mouse_y; //current barrel position
double bx = bx0, by = by0;
double a = -0.0005; //gravity
double t = 0;//time counetr
double tx0;
double ty0;
double explosionX, explosionY;
bool isexplosion = false;


double angle = 0;
int direction = 1;

void init()
{

	srand(time(0)); // seed or init random numbers generator
	
	glClearColor(0.0, 0.0, 0.4, 0);// color of window background

	// define main axes (left,right,bottom,top,near far)
	glOrtho(-1, 1, -1, 1, -1, 1);
	//glPointSize(2);
}

void DrawWheel()
{
	double alpha, teta = PI / 36;
	double x, y;

	glColor3d(1, 1, 1);
	// outer circle (tyre)
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);  
	for (alpha = 0; alpha < 2 * PI; alpha += teta)
	{
		x = cos(alpha);
		y = sin(alpha);

		glVertex2d(x, y);
	}
	glEnd();

	// inner lines
	glLineWidth(1);

	glColor3d(1,1,1);
	teta = PI / 8;
	glBegin(GL_LINES);
	for (alpha = 0; alpha < 2 * PI; alpha += teta)
	{
		x = cos(alpha);
		y = sin(alpha);

		glVertex2d(x, y);
		glVertex2d(0, 0);
	}
	glEnd();

}

void DrawGround()
{
	double x, y;

	glColor3d(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	for (x = -1; x <= 1; x += 0.01)
	{
		y = 0.15*sin(8*x);
		glVertex2d(x, y);
	}
	glEnd();

}

void DrawTank()
{
	// first wheel
	glPushMatrix();
	glTranslated(-0.3, 0, 0);
	glRotated(angle*direction , 0, 0, 1); // 
	glScaled(0.09, 0.09, 1);
	DrawWheel();
	glPopMatrix();

	// second wheel
	glPushMatrix();
	glTranslated(-0.1, 0, 0);
	glRotated(angle * direction, 0, 0, 1);
	glScaled(0.09, 0.09, 1);
	DrawWheel();
	glPopMatrix();

	// third wheel
	glPushMatrix();
	glTranslated(0.1, 0, 0);
	glRotated(angle * direction, 0, 0, 1);
	glScaled(0.09, 0.09, 1);
	DrawWheel();
	glPopMatrix();

	// forth wheel
	glPushMatrix();
	glTranslated(0.3, 0, 0);
	glRotated(angle * direction, 0, 0, 1);
	glScaled(0.09, 0.09, 1);
	DrawWheel();
	glPopMatrix();

	// rama tank
	glLineWidth(2);
	glColor3d(1, 1,1);
	glBegin(GL_LINE_STRIP);
	glVertex2d(-0.38, -0.02);
	glVertex2d(-0.456, 0.145);
	glVertex2d(0.456, 0.145);
	glVertex2d(0.38, -0.02);
	glEnd();
	
	glLineWidth(2);
	glColor3d(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2d(-0.4, 0.08);
	glVertex2d(-0.456, 0.145);
	glVertex2d(-0.4, 0.145);
	glVertex2d(-0.4, 0.08);
	glEnd();

	glLineWidth(2);
	glColor3d(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2d(0.4, 0.08);
	glVertex2d(0.456, 0.145);
	glVertex2d(0.4, 0.145);
	glVertex2d(0.4, 0.08);
	glEnd();

	//first start
	glLineWidth(1);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2d(-0.2, 0.145);
	glVertex2d(-0.2, 0.1);
	glEnd();

	glLineWidth(1);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2d(-0.23, 0.145);
	glVertex2d(-0.17, 0.1);
	glEnd();

	glLineWidth(1);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2d(-0.17, 0.145);
	glVertex2d(-0.23, 0.1);
	glEnd();

	//second star
	glLineWidth(1);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2d(0, 0.145);
	glVertex2d(0, 0.1);
	glEnd();

	glLineWidth(1);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2d(-0.03, 0.145);
	glVertex2d(0.03, 0.1);
	glEnd();

	glLineWidth(1);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2d(0.03, 0.145);
	glVertex2d(-0.03, 0.1);
	glEnd();

	//third start
	glLineWidth(1);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2d(0.2, 0.145);
	glVertex2d(0.2, 0.1);
	glEnd();

	glLineWidth(1);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2d(0.23, 0.145);
	glVertex2d(0.17, 0.1);
	glEnd();

	glLineWidth(1);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2d(0.17, 0.145);
	glVertex2d(0.23, 0.1);
	glEnd();


	glLineWidth(1);
	glColor3d(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	glVertex2d(-0.35, 0.145);
	glVertex2d(-0.25, 0.22);
	glVertex2d(0.27, 0.22);
	glVertex2d(0.3, 0.145);
	glEnd();

	glLineWidth(1);
	glColor3d(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	glVertex2d(-0.2, 0.22);
	glVertex2d(-0.1, 0.29);
	glVertex2d(0.2, 0.29);
	glVertex2d(0.24, 0.22);
	glEnd();

	glLineWidth(1);
	glColor3d(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	glVertex2d(-0.2, 0.22);
	glVertex2d(-0.6, 0.28);
	glVertex2d(-0.59, 0.32);
	glVertex2d(-0.16, 0.25);
	glEnd();

	// draw line from ball to mouse
	glBegin(GL_LINES);
	glVertex2d(-0.6, 0.28);
	glVertex2d(mouse_x, mouse_y);
	glEnd();

}

void DrawRocket()
{
	glBegin(GL_POLYGON);
	glColor3d(0.7, 0.1, 0);

	glVertex2d(-0.05, 0.03);
	glVertex2d(0, 0.06);
	glVertex2d(0.05, 0.03);

	glVertex2d(0.1, 0.03);
	glVertex2d(0.045, 0);
	glVertex2d(0.1, -0.03);

	glVertex2d(0, -0.01);
	glVertex2d(-0.1, -0.03);
	glVertex2d(-0.045, 0);
	glVertex2d(-0.1, 0.03);

	glVertex2d(-0.05, 0.03);
	glEnd();

	//inner bumb
	glBegin(GL_POLYGON);
	glColor3d(1, 1, 0);

	glVertex2d(-0.04, 0.02);
	glVertex2d(0, 0.055);
	glVertex2d(0.04, 0.02);

	glVertex2d(0.09, 0.025);
	glVertex2d(0.035, 0);
	glVertex2d(0.09, -0.025);

	glVertex2d(0, -0.009);
	glVertex2d(-0.09, -0.025);
	glVertex2d(-0.035, 0);
	glVertex2d(-0.09, 0.025);
	glVertex2d(-0.04, 0.02);
	glEnd();

}

void display()
{
	double x, y,beta;
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // loads the Identity matrix to the TRASFORMATION Matrix


	

	DrawGround();
	x = -0.04 * angle * PI / 180;
	y = 0.15 * sin(8 * x);
	beta = atan(1.2 * cos(8 * x)); // beta computed in radians
	// we add 0.04 (wheel radius) to the bicycle to let it move on the ground

	tx0 = x;
	ty0 = y+0.04;
	
	glPushMatrix();
	glTranslated(-0.04 * angle * PI / 180,y+0.04,0); // move the rotating wheel
	glRotated(beta * 180 / PI, 0, 0, 1);
	glScaled(0.2*direction, 0.2, 0);
	DrawTank();
	glPopMatrix();
	
	if (throw_rocket) {
		glPushMatrix();
		//glTranslated(tx0, ty0, 0);
		glRotated(beta * 180 / PI, 0, 0, 1);
		glTranslated(bx, by, 0);
		glScaled(0.2 * direction, 0.2, 0);
		DrawRocket();
		glPopMatrix();
	}
	if(isexplosion){
		glPushMatrix();
		glTranslated(tx0, ty0, 0);
		glRotated(beta * 180 / PI, 0, 0, 1);
		glTranslated(bx, by, 0);
		glScaled(0.2 * direction, 0.2, 0);
		DrawRocket();
		glPopMatrix();
	}
	glutSwapBuffers(); // show all
}


void idle()
{
	angle+=(direction*0.06);

	if (throw_rocket)// update rocket params.
	{	
		t += 0.001;

			bx = bx0 + vx * t;
			by = by0 + vy * t + a * t * t;
			double ground_bullet_height = 0.1 * sin(10 * bx);

			if (by <= ground_bullet_height) {
				throw_rocket = false;
				isexplosion = true;
				explosionX = bx;
				explosionY = by;

			}
			if (direction < 0) {
				bx = -bx;
			}

		
		// we add 0.04 (wheel radius) to the bicycle to let it move on the ground

	}
	
	glutPostRedisplay(); // posts message (with request to show the frame ) to main window
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		direction = -direction;
}


void keyboard(unsigned char key, int x, int y)
{
	
	if (key == ' ')
	{
		
		throw_rocket = true;
		t = 0;
		vx = mouse_x - tx0;
		vy = mouse_y - ty0;
		
		
	}
	
}

void passiveMotion(int x, int y)
{	
	mouse_x = 2 * x / (double)W - 1;
	mouse_y = 2 * (H - y) / (double)H - 1;

	if (direction < 0) {
		mouse_x = -mouse_x;
	}
	
	
}
void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // defines BUFFERS: Color buffer (frame buffer)
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Transformations Example");

	glutDisplayFunc(display); // refresh window function
	glutIdleFunc(idle); // kind of timer function

	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(passiveMotion);
	init();

	glutMainLoop();
}