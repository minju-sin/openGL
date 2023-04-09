#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h> 
#include <math.h> // sin cos함수를 사용하기 위한 헤더파일 
#define PI 3.1415

int num = 17; // 정 17각형을 만들기 때문에 num을 17로 선언
float radius = 100.0; //반지름

// 정17각형그리는 함수 
void DrawPolygon(int n) {
	float x, y; 
	float delta; 

	delta = 2 * PI / n;
	
	glColor3f(1.0, 1.0, 0.0); // 노란색 
	glBegin(GL_POLYGON); // 정 17각형 내부 색칠하기 
	for (int i = 0; i < n; i++) { // 17각형이므로 17번 반복문으로 돌림 

		x = 250.0 + radius * cos(delta * i);
		y = 250.0 + radius * sin(delta * i);
		glVertex2f(x, y);
	}
	glEnd();
}

// 도형을 그리기 위한 좌표계 그리는 함수
void Display(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0); //바탕색 검은색 
	glClear(GL_COLOR_BUFFER_BIT); // 바탕색을 검은색으로 적용 (순서를 바꾸면 안됨)
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); // 행렬을 단위행렬로 초기화 할 떼 사용 -> 원하는 위치에 그림을 그리기 위해 사용
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);

	glColor3f(1.0, 0.0, 0.0); // 빨간색 
	glBegin(GL_LINES); // x축 그리기 
	glVertex2i(0, 250);
	glVertex2i(500, 250);
	glEnd();
	
	glColor3f(0.0, 0.0, 1.0); // 파란색 
	glBegin(GL_LINES); // y축 선 그리기 
	glVertex2i(250, 0);
	glVertex2i(250, 500); 
	glEnd();
	DrawPolygon(num); 
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(400, 400); // 창의 위치 설정
	glutInitWindowSize(500, 500); // 창의 크기 설정 
	glutCreateWindow("정17각형 만들기");
	glutDisplayFunc(Display);
	glutMainLoop();
}
