#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>

#define PI		3.1415926
#define n_gon	13

float	radius = 0.5;
double	delta_theta;

void draw_axis(void) {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(100.0, 0.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 100.0);
	glEnd();
}

void draw_polygon(void) {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(50.0, 50.0);
	glVertex2f(100.0, 50.0);
	glVertex2f(100.0, 100.0);
	glVertex2f(50.0, 100.0);
	glEnd();
}

// 효율적이지 않은 방법..
void draw_Ngon1(void) {
	
	glColor3f(1.0, 1.0, 0.0); 

	delta_theta = 2 * PI / 17.0;
	glBegin(GL_POLYGON);
		glVertex2f(radius * cos(delta_theta * 0), radius * sin(delta_theta * 0));
		glVertex2f(radius * cos(delta_theta * 1), radius * sin(delta_theta * 1));
		glVertex2f(radius * cos(delta_theta * 2), radius * sin(delta_theta * 2));
		glVertex2f(radius * cos(delta_theta * 3), radius * sin(delta_theta * 3));
		glVertex2f(radius * cos(delta_theta * 4), radius * sin(delta_theta * 4));
		glVertex2f(radius * cos(delta_theta * 5), radius * sin(delta_theta * 5));
		glVertex2f(radius * cos(delta_theta * 6), radius * sin(delta_theta * 6));
		glVertex2f(radius * cos(delta_theta * 7), radius * sin(delta_theta * 7));
		glVertex2f(radius * cos(delta_theta * 8), radius * sin(delta_theta * 8));
		glVertex2f(radius * cos(delta_theta * 9), radius * sin(delta_theta * 9));
		glVertex2f(radius * cos(delta_theta * 10), radius * sin(delta_theta * 10));
		glVertex2f(radius * cos(delta_theta * 11), radius * sin(delta_theta * 11));
		glVertex2f(radius * cos(delta_theta * 12), radius * sin(delta_theta * 12));
		glVertex2f(radius * cos(delta_theta * 13), radius * sin(delta_theta * 13));
		glVertex2f(radius * cos(delta_theta * 14), radius * sin(delta_theta * 14));
		glVertex2f(radius * cos(delta_theta * 15), radius * sin(delta_theta * 15));
		glVertex2f(radius * cos(delta_theta * 16), radius * sin(delta_theta * 16));
	glEnd();
}

/*
x = r * cos
y = r * sin
전체 한바퀴 도는 것 360도 -> 2 * PI
한 각의 크기 = 2 * PI / n_gon
*/

void draw_Ngon2(void) {
	int i;
	glColor3f(1.0, 1.0, 0.0);
	delta_theta = 2 * PI / n_gon;

	glBegin(GL_POLYGON); 
	//glBegin(GL_POINTS); 점으로 그림 
	//glBegin(GL_LINE_LOOP); // 내부를 채우지 않음 
	//glBegin(GL_LINES);
		for (i = 0; i < n_gon; i++) 
			glVertex2f(radius * cos(delta_theta * i), radius * sin(delta_theta * i));
		
	glEnd();
}




void RenderScene(void) {
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	
	draw_polygon();
	//draw_Ngon1();
	draw_Ngon2();
	draw_axis();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(50, 150);
	glutInitWindowSize(500, 500);
	glutCreateWindow("N-Gononal Polygon");
	glutDisplayFunc(RenderScene); // glut 이벤트 등록 함수
	// gluOrtho2D(left, right, bottom, top); 카메라 위치 조정하는 함수  => z축은 고정
	// glOrtho( left, right, bottom, top ); => Z축도 바뀌는 것

	
	glutMainLoop();
	return 0;
}

// 17각형의 위치와 크기를 변경하여, 그 원을 포함하는 결과를 얻기 위해서는 어떤 작업이 필요할까요?
// 임의의 n_각형을 만들기 위해서는 어떤 작업이 필요할까요?
// 주어진 점들로부터 다양한 모양을 나타나게 하기 위해서는 키보드의 키를 입력받아 선택할 수 있도록 하면 좋겠지요?
//       (17개의 점, 8개의 선분, 5개의 삼각형, 4개의 사각형, 내부 채움 없는 LINE_LOOP)