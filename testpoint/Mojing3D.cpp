// Mojing3D.cpp : 定义控制台应用程序的入口点。
//


#include "Mojing3DHelper.h"
//#include "MojingMath.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

struct TestItem
{
	float topLeft[3];
	float topRight[3];
	float bottomLeft[3];
	float light[3];
	bool hasIntersection;
	float intersection[2];
	char name[64];
};

TestItem tests[] =
{
	// 垂直x轴平面
	// Z轴负方向
	{
		{ 5.0f, 1.0f, -1.0f },
		{ 5.0f, 1.0f, 1.0f },
		{ 5.0f, -1.0f, -1.0f },
		{ 0.0f, 0.0f, -1.0f },
		false,
		{ 0.5f, 0.5f },
		"垂直x轴矩形, 视线和平面平行"
	},
	// 交点在平面内
	{
		{ 5.0f, 1.0f, -1.0f },
		{ 5.0f, 1.0f, 1.0f },
		{ 5.0f, -1.0f, -1.0f },
		{ 5.0f, 0.4f, -0.4f },
		true,
		{ 0.3f, 0.3f },
		"垂直x轴矩形, 交点在平面内"
	},
	// 垂直y轴平面
	// Z轴负方向
	{
		{ 1.0f, 5.0f, -1.0f },
		{ 1.0f, 5.0f, 1.0f },
		{ -1.0f, 5.0f, -1.0f },
		{ 0.0f, 0.0f, -1.0f },
		false,
		{ 0.5f, 0.5f },
		"垂直y轴矩形, 视线和平面平行"
	},
	// 交点在平面内
	{
		{ 0.0f, 1.0f, 10.0f },
		{ 10.0f, 1.0f, 10.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 6.85f, 1.0f, 4.0f },
		true,
		{ 0.685f, 0.6f },
		"垂直y轴矩形, 交点在平面内"
	},
	// 垂直Z轴平面
	// Z轴负方向
	{
		{ -1.0f, 1.0f, -5.0f },
		{ 1.0f, 1.0f, -5.0f },
		{ -1.0f, -1.0f, -5.0f },
		{0.0f, 0.0f, -1.0f },
		true,
		{0.5f, 0.5f},
		"垂直z轴矩形, 视线和平面垂直"
	},
	// 第一象限
	{
		{ -1.0f, 1.0f, -5.0f },
		{ 1.0f, 1.0f, -5.0f },
		{ -1.0f, -1.0f, -5.0f },
		{ 0.5f, 0.5f, -5.0f },
		true,
		{ 0.75f, 0.25f },
		"垂直z轴矩形, 视线在第一象限"
	},
	// 第二象限
	{
		{ -1.0f, 1.0f, -5.0f },
		{ 1.0f, 1.0f, -5.0f },
		{ -1.0f, -1.0f, -5.0f },
		{ -0.95f, 0.5f, -5.0f },
		true,
		{ 0.025f, 0.25f },
		"垂直z轴矩形, 视线在第二象限"
	},
	// 第三象限
	{
		{ -1.0f, 1.0f, -5.0f },
		{ 1.0f, 1.0f, -5.0f },
		{ -1.0f, -1.0f, -5.0f },
		{ -0.95f, -0.8f, -5.0f },
		true,
		{ 0.025f, 0.9f },
		"垂直z轴矩形, 视线在第三象限"
	},
	// 第四象限
	{
		{ -1.0f, 1.0f, -5.0f },
		{ 1.0f, 1.0f, -5.0f },
		{ -1.0f, -1.0f, -5.0f },
		{ 0.9f, -0.4f, -5.0f },
		true,
		{ 0.95f, 0.7f },
		"垂直z轴矩形, 视线在第四象限"
	},
	// 外上
	{
		{ -1.0f, 1.0f, -5.0f },
		{ 1.0f, 1.0f, -5.0f },
		{ -1.0f, -1.0f, -5.0f },
		{ 0.9f, 1.01f, -5.0f },
		false,
		{ 0.0f, 0.0f },
		"垂直z轴矩形, 视线在矩形上方"
	},
	// 外下
	{
		{ -1.0f, 1.0f, -5.0f },
		{ 1.0f, 1.0f, -5.0f },
		{ -1.0f, -1.0f, -5.0f },
		{ 0.9f, -1.01f, -5.0f },
		false,
		{ 0.0f, 0.0f },
		"垂直z轴矩形, 视线在矩形下方"
	},
	// 外左
	{
		{ -1.0f, 1.0f, -5.0f },
		{ 1.0f, 1.0f, -5.0f },
		{ -1.0f, -1.0f, -5.0f },
		{ -1.01f, -0.5f, -5.0f },
		false,
		{ 0.0f, 0.0f },
		"垂直z轴矩形, 视线在矩形左方"
	},
	// 外右
	{
		{ -1.0f, 1.0f, -5.0f },
		{ 1.0f, 1.0f, -5.0f },
		{ -1.0f, -1.0f, -5.0f },
		{ 1.01f, 0.01f, -5.0f },
		false,
		{ 0.0f, 0.0f },
		"垂直z轴矩形, 视线在矩形右方"
	},
	// 矩形在视线的反方向
	{
		{ -1.0f, 1.0f, -5.0f },
		{ 1.0f, 1.0f, -5.0f },
		{ -1.0f, -1.0f, -5.0f },
		{ 0.5f, 0.5f, 5.0f },
		false,
		{ 0.75f, 0.25f },
		"垂直z轴矩形, 平面在视线反向"
	},
	// 平行四边形
	{
		{ 4.0f, 3.0f, -5.0f },
		{ 14.0f, 3.0f, -5.0f },
		{ 0.0f, 0.0f, -5.0f },
		{ 5.0f, 2.0f, -5.0f },
		true,
		{ 0.2333333f, 0.3333333f },
		"垂直z轴平行四边形"
	}
};

int main(int argc, char* argv[])
{
	srand(time(NULL));

	Point2f position;
	for (int i = 0; i < sizeof(tests) / sizeof(TestItem); i++)
	{
		//Baofeng::Mojing::Matrix4f m = Baofeng::Mojing::Matrix4f::RotationX(rand()) * Baofeng::Mojing::Matrix4f::RotationY(rand()) * Baofeng::Mojing::Matrix4f::RotationZ(rand());
		//Baofeng::Mojing::Vector3f topLeft(tests[i].topLeft);
		//topLeft = m.Transform(topLeft);

		Plane plane(Point3f(tests[i].topLeft), Point3f(tests[i].topRight), Point3f(tests[i].bottomLeft));
		if (tests[i].hasIntersection == plane.Intersection(Vector3f(tests[i].light), position))
		{
			if (tests[i].hasIntersection)
			{
				if ((fabsf(tests[i].intersection[0] - position.x) < 1e-5) && (fabsf(tests[i].intersection[1] - position.y) < 1e-5))
					printf("Test %02d [%s] passed\r\n", i, tests[i].name);
				else
					printf("Test %02d [%s] failed. Result is: (%f, %f) <> (%f, %f)\r\n", i, tests[i].name, position.x, position.y, tests[i].intersection[0], tests[i].intersection[1]);
			}
			else
				printf("Test %02d [%s] passed\r\n", i, tests[i].name);
		}
		else
		{
			printf("Test %02d [%s] failed. Judge if in RECT wrong.\r\n", i, tests[i].name);
		}
	}
	getchar();
	return 0;
}

