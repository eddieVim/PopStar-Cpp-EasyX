#pragma once

const int WINDOW_X = 800;//������
const int WINDOW_Y = 700;//����߶�

const int STAR_X = 80;//���ǿ��
const int STAR_Y = 80;//���Ǹ߶�

const int TOP_MARGIN = 60;// �ϱ߾� TOP_MARGIN = WINDOW_Y - STAR_Y*COUNT_Y

const int COUNT_Y = 8;//��������
const int COUNT_X = 10;//��������


const int TEXT_HEIGHT = 45;
const int TEXT_WIDTH = 20;


typedef struct mousePoint{
	int x;
	int y;
}Point;

typedef struct account{
	char name[13];
	char pwd[13];
	char question[13];
	char answer[13];
	int score;
}Account;