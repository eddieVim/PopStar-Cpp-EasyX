#include "displayModule.h"
#include<graphics.h>
#include<iostream>
#include<string>
#include <sstream>

using namespace std;



DisplayModule::DisplayModule(void)
{
	this->uFormat = DT_CENTER|DT_INTERNAL;
	COLORREF color=RGB(255,255,255);
	settextcolor(color);//����������ɫ
	settextstyle(TEXT_HEIGHT,TEXT_WIDTH,"Consolas");//����style
	setbkmode(TRANSPARENT);//�������屳����ɫΪ͸��
}


DisplayModule::~DisplayModule(void)
{
}


void DisplayModule::textBox(int x,int y,int width,int height,string name){//������ʾ�ַ���
	if(width!=0&&height!=0) settextstyle(height,width,"Consolas");
	outtextxy(x,y,name.c_str());
}

void DisplayModule::textBox(int x,int y,int width,int height,string name,string content){//����ƴ���ַ�����ʾ�ַ���
	if(width!=0&&height!=0) settextstyle(height,width,"Consolas");
	string str = name+content;
	outtextxy(x,y,str.c_str());
}

void DisplayModule::textBox(int x,int y,int width,int height,string name,int content){//������ʾ�ַ��� ��ƴ��int����
	if(width!=0&&height!=0) settextstyle(height,width,"Consolas");
	stringstream ss;
	ss<<content;
	string strss = ss.str();
	string str = name+strss;
	outtextxy(x,y,str.c_str());
}

void DisplayModule::textBox(int x,int y,int width,int height,char ch){//������ʾ�ַ��� ��ƴ��char����
	if(width!=0&&height!=0) settextstyle(height,width,"Consolas");
	stringstream ss;
	ss<<ch;
	outtextxy(x,y,ss.str().c_str());
}