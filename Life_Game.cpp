/*生命游戏规则：
1、生命害怕孤独，如果一个生命周围的生命少于2个，生命就在下一个回合结束时死亡
2、生命讨厌拥挤，如果一个生命周围的生命超过3个，生命就在下一个回合结束时死亡
3、生命会繁殖，如果一个空位置周围有3个生命，它就在回合结束时获得生命
4、如果生命周围有2、3个生命，它在下一个回合结束时保持原样
*/
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <iostream>

IMAGE cell_Live, cell_Death;        // 定义活细胞和无细胞区域的图案
__int8 world[402][402] = { 0 };   // 定义二维世界

void Init();
void SquareWorld();
void RandWorld();
void PaintWorld();
void Evolution();
void FillCell();

int main()
{
	Init();
	while (true)
	{
		PaintWorld();
		Evolution();
	}
	return 0;
}

//初始化
void Init()
{
	initgraph(800, 800);//定义画面大小

	//设计随机种子
	srand((unsigned)time(NULL));
	//定义细胞死活形态
	Resize(&cell_Live, 4, 4);
	Resize(&cell_Death, 4, 4);

	//构建活细胞图案
	SetWorkingImage(&cell_Live);
	setcolor(GREEN);
	setfillstyle(GREEN);
	rectangle(0, 0, 3, 3);

	//构建死细胞图案
	SetWorkingImage(&cell_Death);
	setcolor(DARKGRAY);
	rectangle(1, 1, 2, 2);

	// 恢复对默认窗口的绘图
	SetWorkingImage(NULL);

	// 产生默认的细胞以方形分布的世界
	RandWorld();
	//SquareWorld();
}

//构建边框活细胞
void SquareWorld()
{
	memset(world, 0, 402 * 402 * sizeof(__int8));

	for (int x = 1; x <= 180; x++)
		world[x][1] = world[x][180] = 1;
	for (int y = 1; y <= 180; y++)
		world[1][y] = world[180][y] = 1;
}
void FillCell()
{
	memset(world, 0, 402 * 402 * sizeof(__int8));
	for (int x = 1; x <= 180; x++)
	{
		for (int y = 1; y <= 180; y = y + 2)
		{
			world[x][y] = 1;
		}
	}
}
//随机生成细胞
void RandWorld()
{
	for (int x = 1; x <= 180; x++)
	{
		for (int y = 1; y <= 180; y++)
		{
			world[x][y] = rand() % 2;
		}
	}
}

//绘制世界

void PaintWorld()
{
	for (int x = 1; x <= 180; x++)
	{
		for (int y = 1; y <= 180; y++)
		{
			putimage(16 + x * 4, 56 + y * 4, world[x][y] ? &cell_Live : &cell_Death);
		}
	}
}

// 繁殖更新
void Evolution()
{
	__int8 tmp[402][402] = { 0 }; // 临时数组
	int sum;
	for (int x = 1; x <= 200; x++)
	{
		for (int y = 1; y <= 180; y++)
		{
			// 计算周围活着的细胞数量
			sum = world[x + 1][y] + world[x + 1][y - 1] + world[x][y - 1] + world[x - 1][y - 1]
				+ world[x - 1][y] + world[x - 1][y + 1] + world[x][y + 1] + world[x + 1][y + 1];

			// 计算当前位置的细胞状态
			switch (sum)
			{
			case 3:     tmp[x][y] = 1;              break;
			case 2:     tmp[x][y] = world[x][y];    break;
			default:    tmp[x][y] = 0;              break;
			}
		}
	}

	// 将临时数组恢复为世界
	memcpy(world, tmp, 402 * 402 * sizeof(__int8));
}