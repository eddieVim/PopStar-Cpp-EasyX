#pragma once
#include <iostream>
#include"GlobalDefine.h"
#include<graphics.h>

using namespace std;

class GameMenu
{
public:
	GameMenu(Account &p);//��ʼ����Դ
	~GameMenu(void);//�ͷ���Դ
	void menu();//��Ϸ���˵�
	int loginA();//��½����
	int loginB();//ע�����
	int findPwd();//�һ��������
	void set();//���ý���
	void rankList();//���а�
	void explain();//˵��
	int catchMouse(Point &point);//�����Ϣ��ȡ
	void TextBox();//�ı���
	void clear();//�������

private:
	IMAGE menuImage,loginAImage,findPwdImage1,findPwdImage2,loginBImage,setImage,setImage1,rankListImage,explainImage,bsA,bsB;
	string loginAName,loginAPwd,loginBName,loginBPwd,loginBPwdCon,question,answer;
};