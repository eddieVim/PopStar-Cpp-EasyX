#pragma once
#include<iostream>
#include<graphics.h>
#include"ConstDefinition.h"
#include"GlobalDefine.h"



class Star{
public:
	Star();
	virtual ~Star(void);
	void display(int x,int y,int color);
	void preload();
private:
	int color;
	IMAGE starImage[11];
};

