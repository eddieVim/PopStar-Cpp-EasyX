#include <iostream>
#include<graphics.h>
#include<string>
#include"GlobalDefine.h"
#include "displayModule.h"


using namespace std;


class GameLogic{
public:
	GameLogic(void);
	GameLogic(Account &accountID);//�����û�����ȡ�������
	~GameLogic(void);
	//��ȡ����
	int getScore();
	//��Ϸ��ѭ������ǿ��װ��ʹ�ô�������
	int mainLogic();

private:
	void starArrInit(int arr[][COUNT_X],int seed);//���������ʼ��
	void starDisplay(int starArr[][COUNT_X]);//����ͼƬ����ʾ
	void sameArrReset(bool arr[][COUNT_X]);//��ʱ��������
	void sameArrPrint(bool arr[][COUNT_X]);//����̨�鿴�ж����

	
	//�ж������ ��洢���������Ϣ
	int catchMouse(Point &point);
	//����������ɫ��ķ��飬sameArr[][COUNT_X]����¼��ͬ���ǵ�λ��
	bool judgeTheSame(Point &point,int starArr[][COUNT_X],bool sameArr[][COUNT_X]);
	//��ʾ������ɫ��ķ�����Χ�ķ���
	void displayBox(bool flag,bool sameArr[][COUNT_X]);
	//���ط��������������ǣ�
	int pop(int starArr[][COUNT_X],bool sameArr[][COUNT_X]);
	//�ж���Ϸ�Ƿ����
	bool gameOver(int starArr[][COUNT_X]);
	//"��������"
	void falldown();
	//�޸����յķ�������ʽ2000��-ʣ�����*5,����ֵΪ�ж��Ƿ�ͨ��
	bool passLevel(int starArr[][COUNT_X]);//�����ж�
	void maxScoreAlter();//�޸ķ���
	int gameOverDisplay(bool);//��Ϸ������Ĵ���

private:
	int score;
	int level;
	int seed;
	string userName;
};

