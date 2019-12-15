#include <iostream>
#include<graphics.h>
#include<string>
#include"GlobalDefine.h"
#include "displayModule.h"


using namespace std;


class GameLogic{
public:
	GameLogic(void);
	GameLogic(Account &accountID);//根据用户名获取随机种子
	~GameLogic(void);
	//获取分数
	int getScore();
	//游戏主循环，加强封装，使得代码更简洁
	int mainLogic();

private:
	void starArrInit(int arr[][COUNT_X],int seed);//星星数组初始化
	void starDisplay(int starArr[][COUNT_X]);//星星图片的显示
	void sameArrReset(bool arr[][COUNT_X]);//临时数组重置
	void sameArrPrint(bool arr[][COUNT_X]);//控制台查看判断情况

	
	//判断鼠标点击 与存储鼠标点击的信息
	int catchMouse(Point &point);
	//搜索相邻颜色点的方块，sameArr[][COUNT_X]，记录相同星星的位置
	bool judgeTheSame(Point &point,int starArr[][COUNT_X],bool sameArr[][COUNT_X]);
	//显示相邻颜色点的方块周围的方块
	void displayBox(bool flag,bool sameArr[][COUNT_X]);
	//返回分数，并消灭星星，
	int pop(int starArr[][COUNT_X],bool sameArr[][COUNT_X]);
	//判断游戏是否结束
	bool gameOver(int starArr[][COUNT_X]);
	//"星星下落"
	void falldown();
	//修改最终的分数，公式2000分-剩余个数*5,返回值为判断是否通关
	bool passLevel(int starArr[][COUNT_X]);//过关判断
	void maxScoreAlter();//修改分数
	int gameOverDisplay(bool);//游戏结束后的处理

private:
	int score;
	int level;
	int seed;
	string userName;
};

