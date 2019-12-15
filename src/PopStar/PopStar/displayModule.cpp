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
	settextcolor(color);//设置字体颜色
	settextstyle(TEXT_HEIGHT,TEXT_WIDTH,"Consolas");//字体style
	setbkmode(TRANSPARENT);//设置字体背景颜色为透明
}


DisplayModule::~DisplayModule(void)
{
}


void DisplayModule::textBox(int x,int y,int width,int height,string name){//用于显示字符串
	if(width!=0&&height!=0) settextstyle(height,width,"Consolas");
	outtextxy(x,y,name.c_str());
}

void DisplayModule::textBox(int x,int y,int width,int height,string name,string content){//用于拼接字符串显示字符串
	if(width!=0&&height!=0) settextstyle(height,width,"Consolas");
	string str = name+content;
	outtextxy(x,y,str.c_str());
}

void DisplayModule::textBox(int x,int y,int width,int height,string name,int content){//用于显示字符串 并拼接int类型
	if(width!=0&&height!=0) settextstyle(height,width,"Consolas");
	stringstream ss;
	ss<<content;
	string strss = ss.str();
	string str = name+strss;
	outtextxy(x,y,str.c_str());
}

void DisplayModule::textBox(int x,int y,int width,int height,char ch){//用于显示字符串 并拼接char类型
	if(width!=0&&height!=0) settextstyle(height,width,"Consolas");
	stringstream ss;
	ss<<ch;
	outtextxy(x,y,ss.str().c_str());
}