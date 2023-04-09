#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>

#define PI		3.1415926
#define Window_Width 500 
#define Window_Height 500

float	radius = 100;
double	delta_theta;
int num = 17;

void draw_axis(void) {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // x축 빨간 선
	glVertex2f(0.0, 0.0);
	glVertex2f(500.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y축 초록색 선 
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 500.0);
	glEnd();
}

void draw_rectangle(void) {
	glColor3f(0.0, 0.0, 1.0); // 파란색 사각형 
	glBegin(GL_LINE_LOOP);
	glVertex2f(50.0, 50.0);
	glVertex2f(100.0, 50.0);
	glVertex2f(100.0, 100.0);
	glVertex2f(50.0, 100.0);
	glEnd();
}



void draw_Ngon(void) {
	int i;
	glColor3f(1.0, 1.0, 0.0); // 노란색 다각형 
	delta_theta = 2 * PI / num;

	glBegin(GL_POLYGON);

	for (i = 0; i < num; i++)
		glVertex2f(radius * cos(delta_theta * i), radius * sin(delta_theta * i));

	glEnd();
}



void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.0, 1.0, 0.0);
	
	// Clipping Window : x는[100, 400], y는 [-200, 300]
	glViewport(0, 0, 500, 500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250, 250, -250, 250);
	//gluOrtho2D와 함께 쓰는 함수가 더 필요할 것 같음 
	draw_Ngon();
	draw_rectangle();
	//draw_Ngon();
	draw_axis();

	glFlush();
}

// keyboard event function
void MyKey(unsigned char key, int x, int y)
{
	// key 종류, 위치
	switch (key) {
	case 'n':
		num += 1; break;
	case 'm':
		num -= 1; break;
	default: break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("Clipping Window(Rectangle)");
	glutKeyboardFunc(MyKey); // keyboard 등록 함수 
	glutDisplayFunc(RenderScene);
	glutMainLoop();
	return 0;
}
// 테두리로만 나타난 사각형을 원 위에 놓이게 하기 위해서는 ?
// 키보드 이벤트 적용
// 범위 설정 