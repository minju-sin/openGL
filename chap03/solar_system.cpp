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

// 행성 반지름
float		sun_radius = 20.0;	// 태양
float		merkury_radius = 7.0;	// 수성
float		venus_radius = 9.0;	// 금성
float		earth_radius = 10.0; // 지구
float		moon_radius = 5.0; // 달
float		mars_radius = 8.0;	// 화성
float		jupiter_radius = 21.0;	// 목성
float		saturn_radius = 17.0;	// 토성
float		uranus_radius = 14.0;	// 천왕성
float		neptune_radius = 14.0;	// 천왕성

// 행성 회전
float		merkuryRotation = 0.0, venusRotation = 0.0, earthRotation = 0.0, moonRotation = 0.0;
float		marsRotation = 0.0, jupiterRotation = 0.0, saturnRotation = 0.0, uranusRotation = 0.0, neptuneRotation = 0.0;

// 행성 거리 
float		merkuryTransforms = 40.0, venusTransforms = 60.0, earthTransforms = 100.0, moonTransforms = 30.0;
float		marsTransforms = 120.0, jupiterTransforms = 200.0, saturnTransforms = 250.0, uranusTransforms = 300.0, neptuneTransforms = 350.0;

// 행성 속도 
float		merkury_rotation_speed = 0.04;
float		venus_rotation_speed = 0.03;
float		earth_rotation_speed = 0.025;
float		moon_rotation_speed = 0.1;
float		mars_rotation_speed = 0.02;
float		jupiter_rotation_speed = 0.01;
float		saturn_rotation_speed = 0.008;
float		uranus_rotation_speed = 0.005;
float		neptune_rotation_speed = 0.003;


void init(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0 * Width / 2.0, Width / 2.0, -1.0 * Height / 2.0, Height / 2.0);
}

//	행성 그리기
void Draw_Circle(float c_radius) {
	float	delta;
	int		num = 36;

	delta = 2 * PI / num;
	glBegin(GL_POLYGON);
	for (int i = 0; i < num; i++)
		glVertex2f(c_radius * cos(delta * i), c_radius * sin(delta * i));
	glEnd();
}
void Solar(float rotation, float transforms, float radius) {
	glRotatef(rotation, 0.0, 0.0, 1.0);	// 기준 좌표에서 rotation 만큼 z축 기준으로 회전
	glTranslatef(transforms, 0.0, 0.0);	// 기준 좌표에서 x축만 trabsforms만큼 이동
	Draw_Circle(radius);
}

// 궤도 그리기 
void Draw_Orbit(float c_radius) {
	float	delta;
	int		num = 36;

	delta = 2 * PI / num;
	glBegin(GL_LINES);
	for (int i = 0; i < num; i++)
		glVertex2f(c_radius * cos(delta * i), c_radius * sin(delta * i));
	glEnd();
}
void Orbit(float transforms) {
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0); // 궤도 색상 흰색
	Draw_Orbit(transforms); // 행성과 태양 사이의 거리 
	// 달은 달과 지구 사이의 거리를 궤도 반지름으로 결정
	glPopMatrix();
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); // Set display-window color to black.

	merkuryRotation += merkury_rotation_speed;
	venusRotation += venus_rotation_speed;
	earthRotation += earth_rotation_speed;
	moonRotation += moon_rotation_speed;
	marsRotation += mars_rotation_speed;
	jupiterRotation += jupiter_rotation_speed;
	saturnRotation += saturn_rotation_speed;
	uranusRotation += uranus_rotation_speed;
	neptuneRotation += neptune_rotation_speed;

	/***********코드 작성하기 ***************/
	// 태양 : 빨간색의 구 
	glColor3f(1.0, 0.0, 0.0);
	Draw_Circle(sun_radius);

	// 수성 : 회색 구
	glPushMatrix(); // 태양의 변환 좌표 저장
	glColor3f(0.5, 0.5, 0.5);
	Solar(merkuryRotation, merkuryTransforms, merkury_radius);
	glPopMatrix(); // 태양 변환 좌표로 복구 
	// 수성 궤도 
	Orbit(merkuryTransforms);

	// 금성 : 금색 구
	glPushMatrix(); // 태양의 변환 좌표 저장
	glColor3f(1.0, 0.7, 0.0);
	Solar(venusRotation, venusTransforms, venus_radius);
	glPopMatrix(); // 태양 변환 좌표로 복구 
	// 금성 궤도
	Orbit(venusTransforms);

	// 지구 궤도 
	Orbit(earthTransforms);
	// 지구 : 하늘색의 구
	glPushMatrix();	//	태양의 변환 좌표를 저장해 놓음
	glColor3f(0.0, 1.0, 1.0);
	Solar(earthRotation, earthTransforms, earth_radius);

	// 달   : 노랑색의 구 
	glPushMatrix();	//	지구의 변환 좌표를 저장해 놓음 
	glColor3f(1.0, 1.0, 0.0);
	Solar(moonRotation, moonTransforms, moon_radius);
	glPopMatrix();	//	지구 변환 좌표로 복구
	// 달 궤도
	Orbit(moonTransforms);
	glPopMatrix();	//	태양의 변환 좌표로 복구
	glPopMatrix();	//	태양 전의 변환 좌표로 복구 

	// 화성 : 다홍색 구 
	glPushMatrix();
	glColor3f(1.0, 0.3, 0.0);
	Solar(marsRotation, marsTransforms, mars_radius);
	glPopMatrix();
	// 화성 궤도
	Orbit(marsTransforms);

	// 목성 : 보라색 구 
	glPushMatrix();
	glColor3f(0.5, 0.4, 1.0);
	Solar(jupiterRotation, jupiterTransforms, jupiter_radius);
	glPopMatrix();
	// 목성 궤도
	Orbit(jupiterTransforms);

	// 토성 : 주황색 구 
	glPushMatrix();
	glColor3f(1.0, 0.4, 0.0);
	Solar(saturnRotation, saturnTransforms, saturn_radius);
	glPopMatrix();
	// 토성 궤도
	Orbit(saturnTransforms);

	// 천왕성 : 파란색 구 
	glPushMatrix();
	glColor3f(0.0, 0.6, 1.0);
	Solar(uranusRotation, uranusTransforms, uranus_radius);
	glPopMatrix();
	// 천왕성 궤도
	Orbit(uranusTransforms);

	// 해왕성 : 남색 구 
	glPushMatrix();
	glColor3f(0.2, 0.0, 0.8);
	Solar(neptuneRotation, neptuneTransforms, neptune_radius);
	glPopMatrix();
	// 해왕성 궤도
	Orbit(neptuneTransforms);
	glFlush();
	glutSwapBuffers();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("태양계 시뮬레이션");
	init();
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);
	glutMainLoop();
}

