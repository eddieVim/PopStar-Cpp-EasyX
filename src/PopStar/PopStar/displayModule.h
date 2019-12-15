#pragma once
#include<graphics.h>
#include<iostream>
#include "GlobalDefine.h"
#include<string>

using namespace std;


class DisplayModule
{
public:
	DisplayModule(void);
	~DisplayModule(void);
	void textBox(int x,int y,int width,int height,string name);
	void textBox(int x,int y,int width,int height,string name,string content);
	void textBox(int x,int y,int width,int height,string name,int content);
	void textBox(int x,int y,int width,int height,char ch);
private:
	IMAGE buttonImage;
	UINT uFormat;
};

