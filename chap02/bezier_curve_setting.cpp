#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)
#include <math.h>
#define		Window_Width	800
#define		Window_Height	800

int			point[100][2];
int			num = 0;
int			curveDgree = 0; // 차수
float partialTime; // 시간
int	curvePointNum = 100; // 0~1 사이의 거리를 curvePointNum로 나눔
float sumX, sumY;

float factorial(int n) {
	if (n <= 1) { return 1; }
	else return n * factorial(n - 1);
}

// 조합 계산 
float binomial(int n, int k) {
	float binomialValue;
	
	if (n >= 1 && k <= n) {
		binomialValue = factorial(n) / (factorial(k) * factorial(n - k));
	}
	else binomialValue = 1.0;

	return binomialValue;
}


float bernstein(int n, int k, float time) {
	float	bernsteinValue;

	if (0.0 <= time && time <= 1.0) {
		bernsteinValue = binomial(n, k) * pow(1.0 - time, n - k) * pow(time, k);
	}
	else bernsteinValue = 1.0;
	return bernsteinValue;
}

void Draw_Bezier_Curve(void) {
	//*********** Bezier_Curve ***********//
	glColor3f(1.0, 1.0, 0.0);

	curveDgree = num - 1;
	partialTime = 1.0 / curvePointNum;

	glBegin(GL_LINES);
	for (float time = partialTime; time <= 1.0; time += partialTime) {

		sumX = sumY = 0.0;

		for (int i = 0; i <= curveDgree; i++) {

			sumX += bernstein(curveDgree, i, time) * point[i][0];
			sumY += bernstein(curveDgree, i, time) * point[i][1];
		}

	
		glVertex2f(sumX, sumY);
		
	}
	
	glEnd();
}
void Draw_Control_Points(void) {

	glPointSize(5.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (int k = 0; k < num; k++) {
		glVertex2f(point[k][0], point[k][1]);
	}
	glEnd();

}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glColor3f(1.0, 0.0, 0.0);

	if (num >= 1)
		Draw_Control_Points();
	if (num >= 2)
		Draw_Bezier_Curve();

	glFlush();
	glutSwapBuffers();
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	glLoadIdentity();
	gluOrtho2D(0, Window_Width, 0, Window_Height);
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		point[num][0] = x;
		point[num][1] = Window_Height - y;
		num++;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		num = 0;
	}
	glutPostRedisplay();
	RenderScene();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("Bezier Curve");
	init();
	glutDisplayFunc(RenderScene);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}