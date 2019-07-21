#include <stdio.h>
#include <graphics.h>
#include <time.h>

#define BLOCK_COUNT     5
#define BLOCK_WIDTH     5
#define BLOCK_HEIGHT    5
#define UNIT_SIZE       20

int score = 0;
int rank = 0;

int NextIndex = -1;

int color[BLOCK_COUNT] = {
	GREEN, CYAN, MAGENTA, BROWN, YELLOW
};

int visit[30][15]; //访问数组

int block[BLOCK_COUNT*4][BLOCK_HEIGHT][BLOCK_WIDTH] = {
	// | 型方块
	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,1,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,1,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	 // L 型方块
	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,1,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,1,0,
	 0,1,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,1,0,
	 0,1,0,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	//丁字形
	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,1,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,1,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,1,0,
	 0,0,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,1,0,
	 0,0,1,0,0,
	 0,0,0,0,0},
	//田型
	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,1,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,1,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,1,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,1,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	// Z  型方块
	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,0,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,1,0,
	 0,0,1,1,0,
	 0,0,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,0,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,1,0,
	 0,0,1,1,0,
	 0,0,1,0,0,
	 0,0,0,0,0}
};

// 欢迎界面
void Welcome(){
	//初始化画布
	initgraph(550,660);

	//设置窗口标题
	HWND window = GetHWnd();
	SetWindowText(window,_T("俄罗斯方块    Rock"));

	setfont(40, 0, _T("微软雅黑"));
	setcolor(WHITE);
	outtextxy(205, 200, _T("俄罗斯方块"));

	setfont(22, 0, _T("楷体"));
	outtextxy(175, 300, _T("编程， 从俄罗斯方块开始！"));

	Sleep(3000);
}

//初始化游戏场景
void initGameScene(){

	char str[15];
	//清除屏幕
	cleardevice();

	rectangle(27, 27, 336, 635);
	rectangle(29, 29, 334, 633);
	rectangle(370, 50, 515, 195);

	setfont(24, 0, _T("楷体"));
	setcolor(LIGHTGRAY);
	outtextxy(405, 215, _T("下一个"));

	setcolor(RED);
	outtextxy(405, 280, _T("分数"));
	sprintf(str,"%d",score);
	outtextxy(415, 310, str);

	outtextxy(405, 375, _T("等级"));
	sprintf(str,"%d",rank);
	outtextxy(425, 405, str);

	//操作说明
	setcolor(LIGHTBLUE);
	outtextxy(390, 475, _T("操作说明"));
	outtextxy(390, 500, _T("↑: 旋转"));
	outtextxy(390, 525, _T("↓: 下降"));
	outtextxy(390, 550, _T("←: 左移"));
	outtextxy(390, 575, _T("→: 右移"));
	outtextxy(390, 600, _T("空格 : 暂停"));

}
void clearBlock(){
	setcolor(BLACK);
	setfont(23,0,_T("楷体"));
	for(int i = 0; i < BLOCK_HEIGHT; i++){
		for(int j = 0; j < BLOCK_WIDTH; j++){
			int x = 391 + j * UNIT_SIZE;
			int y = 71 + i * UNIT_SIZE;
			outtextxy(x, y, "■");
		}
	}
}

//在右上角区域绘制下一个方块
void drawBlock(){
	setcolor(color[NextIndex]);
	setfont(23,0,_T("楷体"));

	for(int i = 0; i < BLOCK_HEIGHT; i++){
		for(int j = 0; j < BLOCK_WIDTH; j++){
			// "■"
			if(block[NextIndex*4][i][j] == 1){
				int x = 391 + j * UNIT_SIZE;
				int y = 71 + i * UNIT_SIZE;
				outtextxy(x, y, "■");
			}
		}
	}
}

void nextblock(){
	clearBlock();   //清除右上角区域的方块
	// 随机选择一种方块
	srand(time(NULL));  // 利用时间返回值产生一个随机种子

	NextIndex = rand() % BLOCK_COUNT;

	drawBlock();

}

int main(void){

	Welcome();
	
	initGameScene();
	//产生新方块
	nextblock();

	//初始化访问数组
	memset(visit, 0, sizeof(visit));


	system("pause");
	closegraph();
	return 0 ;
}

