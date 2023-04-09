/*
glPushMatrix() 이 함수가 불리기 전의 변환 좌표를 저장해 놓는다.
glPopMatrix() 를 사용해 glPushMatrix() 이전의 좌표 상태를 다시 호출한다.
*/

#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define		PI	3.1415926

int			Width = 800;
int			Height = 800;

float		sun_radius = 50.0;
float		earth_radius = 10.0;
float		moon_radius = 5.0;
float		earthRotation = 0.0, moonRotation = 0.0;
float		earthTransforms = 200.0, moonTransforms = 30.0;

float		earth_rotation_speed = 0.005;
float		moon_rotation_speed = 0.05;


void init(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0*Width/2.0, Width/2.0, -1.0*Height/2.0, Height/2.0);
}

//	행성 그리기
void Draw_Circle(float c_radius) {
	float	delta;
	int		num = 36;

	delta = 2 * PI / num;
	glBegin(GL_POLYGON);
	for (int i = 0; i < num; i++)
		glVertex2f(c_radius*cos(delta*i), c_radius*sin(delta*i));
	glEnd();
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); // Set display-window color to black.

	earthRotation += earth_rotation_speed;	
	moonRotation += moon_rotation_speed;

	/***********코드 작성하기 ***************/
	// 태양 : 빨간색의 구 
	glColor3f(1.0, 0.0, 0.0);
	Draw_Circle(sun_radius);
	


	// 지구 : 파란색의 구
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();	//	태양의 변환 좌표를 저장해 놓음
		glRotatef(earthRotation, 0.0, 0.0, 1.0); // 태양 기준에서 earthRotation 만큼 z축 기준으로 회전 
		glTranslatef(earthTransforms, 0.0, 0.0); // 태양의 좌표에서 x축만 +200 이동
		Draw_Circle(earth_radius);	//	지구를 그린다
	

	// 달   : 노랑색의 구 
		glPushMatrix();	//	지구의 변환 좌표를 저장해 놓음 
			glColor3f(1.0, 1.0, 0.0);
			glRotatef(moonRotation, 0.0, 0.0, 1.0);	// 지구 기준으로 달이 moonRotation 만큼 z축 기준으로 회전 
			glTranslatef(moonTransforms, 0.0, 0.0); // 지구의 좌표에서 x축만 +30 이동
			Draw_Circle(moon_radius);	//	달을 그린다.
		glPopMatrix();	//	지구 변환 좌표로 복구
	glPopMatrix();	//	태양의 변환 좌표로 복구
	glPopMatrix();	//	태양 전의 변환 좌표로 복구 

	glFlush();
	glutSwapBuffers();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("태양계 태양-지구-달");
	init();
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);
	glutMainLoop();
}

