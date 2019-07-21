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

int visit[30][15]; //��������

int block[BLOCK_COUNT*4][BLOCK_HEIGHT][BLOCK_WIDTH] = {
	// | �ͷ���
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

	 // L �ͷ���
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

	//������
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
	//����
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

	// Z  �ͷ���
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

// ��ӭ����
void Welcome(){
	//��ʼ������
	initgraph(550,660);

	//���ô��ڱ���
	HWND window = GetHWnd();
	SetWindowText(window,_T("����˹����    Rock"));

	setfont(40, 0, _T("΢���ź�"));
	setcolor(WHITE);
	outtextxy(205, 200, _T("����˹����"));

	setfont(22, 0, _T("����"));
	outtextxy(175, 300, _T("��̣� �Ӷ���˹���鿪ʼ��"));

	Sleep(3000);
}

//��ʼ����Ϸ����
void initGameScene(){

	char str[15];
	//�����Ļ
	cleardevice();

	rectangle(27, 27, 336, 635);
	rectangle(29, 29, 334, 633);
	rectangle(370, 50, 515, 195);

	setfont(24, 0, _T("����"));
	setcolor(LIGHTGRAY);
	outtextxy(405, 215, _T("��һ��"));

	setcolor(RED);
	outtextxy(405, 280, _T("����"));
	sprintf(str,"%d",score);
	outtextxy(415, 310, str);

	outtextxy(405, 375, _T("�ȼ�"));
	sprintf(str,"%d",rank);
	outtextxy(425, 405, str);

	//����˵��
	setcolor(LIGHTBLUE);
	outtextxy(390, 475, _T("����˵��"));
	outtextxy(390, 500, _T("��: ��ת"));
	outtextxy(390, 525, _T("��: �½�"));
	outtextxy(390, 550, _T("��: ����"));
	outtextxy(390, 575, _T("��: ����"));
	outtextxy(390, 600, _T("�ո� : ��ͣ"));

}
void clearBlock(){
	setcolor(BLACK);
	setfont(23,0,_T("����"));
	for(int i = 0; i < BLOCK_HEIGHT; i++){
		for(int j = 0; j < BLOCK_WIDTH; j++){
			int x = 391 + j * UNIT_SIZE;
			int y = 71 + i * UNIT_SIZE;
			outtextxy(x, y, "��");
		}
	}
}

//�����Ͻ����������һ������
void drawBlock(){
	setcolor(color[NextIndex]);
	setfont(23,0,_T("����"));

	for(int i = 0; i < BLOCK_HEIGHT; i++){
		for(int j = 0; j < BLOCK_WIDTH; j++){
			// "��"
			if(block[NextIndex*4][i][j] == 1){
				int x = 391 + j * UNIT_SIZE;
				int y = 71 + i * UNIT_SIZE;
				outtextxy(x, y, "��");
			}
		}
	}
}

void nextblock(){
	clearBlock();   //������Ͻ�����ķ���
	// ���ѡ��һ�ַ���
	srand(time(NULL));  // ����ʱ�䷵��ֵ����һ���������

	NextIndex = rand() % BLOCK_COUNT;

	drawBlock();

}

int main(void){

	Welcome();
	
	initGameScene();
	//�����·���
	nextblock();

	//��ʼ����������
	memset(visit, 0, sizeof(visit));


	system("pause");
	closegraph();
	return 0 ;
}

