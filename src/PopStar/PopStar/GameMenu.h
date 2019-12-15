#pragma once
#include <iostream>
#include"GlobalDefine.h"
#include<graphics.h>

using namespace std;

class GameMenu
{
public:
	GameMenu(Account &p);//初始化资源
	~GameMenu(void);//释放资源
	void menu();//游戏主菜单
	int loginA();//登陆界面
	int loginB();//注册界面
	int findPwd();//找回密码界面
	void set();//设置界面
	void rankList();//排行榜
	void explain();//说明
	int catchMouse(Point &point);//鼠标信息获取
	void TextBox();//文本框
	void clear();//清空属性

private:
	IMAGE menuImage,loginAImage,findPwdImage1,findPwdImage2,loginBImage,setImage,setImage1,rankListImage,explainImage,bsA,bsB;
	string loginAName,loginAPwd,loginBName,loginBPwd,loginBPwdCon,question,answer;
};