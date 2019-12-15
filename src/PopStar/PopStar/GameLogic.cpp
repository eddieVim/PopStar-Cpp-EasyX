#include "GameLogic.h"
#include <iostream>
#include<graphics.h>
#include<queue>
#include"star.h"
#include <conio.h>
#include<fstream>



int direction[4][2] = {{0,-1},{0,1},{-1,0},{1,0}};//搜索方向

IMAGE bgImage,gameOverImage,passLevelImage,BoxImage[2];//用于存储图片

Star *star;//用于星星显示

Point point;//存储鼠标点击的点

DisplayModule *module;//用于显示字符串等模块

Account *ppAccount;//存储用户信息

int starArr[COUNT_Y][COUNT_X];//界面星星所用的数组

bool sameArr[COUNT_Y][COUNT_X];//标记相同星星所用的数组

LPCTSTR boxPImgFile[2] = {
	"Image\\box.jpg",
	"Image\\box1.jpg"
};//透明边框的路径

GameLogic::GameLogic(Account &accountID)
{	
	ppAccount = &accountID;
	this->seed = accountID.name[0]*100+accountID.name[1]*10+accountID.name[2];
	this->userName = accountID.name;
	this->score = 0;
	this->level = 1;
	

	initgraph(WINDOW_X,WINDOW_Y,NOMINIMIZE);
	setcolor(RED);
	loadimage(&bgImage,"Image\\GameBG.jpg",WINDOW_X,WINDOW_Y);
	loadimage(&gameOverImage,"Image\\gameOver.jpg",600,600);
	loadimage(&passLevelImage,"Image\\passLevel.jpg",300,300);
	loadimage(&BoxImage[0],boxPImgFile[0],STAR_X,STAR_Y);
	loadimage(&BoxImage[1],boxPImgFile[1],STAR_X,STAR_Y);
	
	star = new Star;
	module = new DisplayModule;
}


GameLogic::~GameLogic(void)
{
	delete star;
	delete module;
}

void GameLogic::starDisplay(int starArr[][COUNT_X]){
	//初始化Star对象，Star类用于界面显示
	
	
	BeginBatchDraw();

	putimage(0,0,&bgImage);//背景刷新

	module->textBox(0,0,15,30,"用户：",this->userName);
	module->textBox(0,30,15,30,"分数：",this->score);
	module->textBox((WINDOW_X-7*TEXT_WIDTH)/2,0,15,30,"level：",this->level);//(WINDOW_X-7*TEXT_WIDTH)/2
	module->textBox((WINDOW_X-7*TEXT_WIDTH)/2,30,15,30,"晋级需要分数：",1000+2000*(this->level-1));
	
	for(int i = 0;i < COUNT_Y;++i){
		for(int j = 0;j < COUNT_X;++j){
			star->display(j*STAR_X,i*STAR_Y+TOP_MARGIN,starArr[i][j]);
		}
	}

	FlushBatchDraw();
}

void GameLogic::sameArrReset(bool arr[][COUNT_X]){
	for(int i = 0;i < COUNT_Y;++i){
		for(int j = 0;j < COUNT_X;++j){
			arr[i][j] =  false;
		}
	}
}

void GameLogic::sameArrPrint(bool arr[][COUNT_X]){
	for(int i = 0;i < COUNT_Y;++i){
		for(int j = 0;j < COUNT_X;++j){
			cout<<arr[i][j]<<"\t";
		}
		cout<<endl;
	}
}

void GameLogic::starArrInit(int arr[][COUNT_X],int seed){
	for(int i =0;i < COUNT_Y;++i){
		srand(seed+=this->level);
		for(int j = 0;j < COUNT_X;++j){
			int color = 0;
			while(color == 0) color = rand()%6;
			arr[i][j] = color;
		}
	}
}
//point为存坐标点的结构体
int GameLogic::catchMouse(Point &point){
	if (MouseHit()){
		MOUSEMSG msg = GetMouseMsg();
		switch (msg.uMsg){
		case WM_LBUTTONDOWN://左键按下
			//保存坐标
			point.x = msg.x;
			point.y = msg.y;
			cout<<"按下左键；X："<<point.x<<"Y:"<<point.y<<endl;
			return 1;
		case WM_LBUTTONDBLCLK://双击
			//保存坐标
			point.x = msg.x;
			point.y = msg.y;
			cout<<"双击；X："<<point.x<<"Y:"<<point.y<<endl;
			return 2;
		default:
			point.x = -1;
			point.y = -1;
		}
	}
	//没有点击
	return 0;
}


//使用广度优先搜索算法（BFS），找到相邻方块的点
bool  GameLogic::judgeTheSame(Point &point,int starArr[][COUNT_X],bool sameArr[][COUNT_X]){
	if(point.y < TOP_MARGIN) return 0;//点击到不是星星区域的时候
	int y = (point.y-TOP_MARGIN)/STAR_Y;//星星在数组中的位置 行
	int x = point.x/STAR_X;//星星在数组中的位置 列
	int color = starArr[y][x];//星星颜色
	if(color==0) return 0;//无星星时，直接返回
	int count = 1;//相同的颜色星星个数

	//存储鼠标点的队列
	queue<Point> q;

	Point xy;
	xy.x = x;
	xy.y = y;
	
	sameArr[y][x] = true;
	q.push(xy);

	while(!q.empty()){
		Point ab = q.front();
		q.pop();
		int a = ab.x;
		int b = ab.y;
		for(int i = 0;i < 4;++i){
			
			int aa = a+direction[i][0];
			int bb = b+direction[i][1];
			if(aa<0||bb<0||aa>=COUNT_X||bb>=COUNT_Y)continue;
			//判断该点是否颜色相同且是否重复了
			if(starArr[bb][aa]==color && sameArr[bb][aa] == false){
				sameArr[bb][aa] = true;
				count++;

				Point temp;
				temp.x = aa;
				temp.y = bb;
				q.push(temp);
			}
			
		}
	}
	return count>=2?true:false;
}

//显示方框
void GameLogic::displayBox(bool flag,bool sameArr[][COUNT_X]){
	//if(!flag) return;
	for(int i = 0;i < COUNT_Y;++i){
		for(int j = 0;j < COUNT_X;++j){
			if(sameArr[i][j] == true){
				BeginBatchDraw();
				putimage(j*STAR_X,i*STAR_Y+TOP_MARGIN,&BoxImage[1],NOTSRCERASE);
				putimage(j*STAR_X,i*STAR_Y+TOP_MARGIN,&BoxImage[0],SRCINVERT);
				EndBatchDraw();
			}
		}
	}
}

//消除星星并返回分数 = 消除星星个数的平方*5
int GameLogic::pop(int starArr[][COUNT_X],bool sameArr[][COUNT_X]){
	int count = 0;

	//找出相同的方块个数并消除方块
	for(int i = 0;i < COUNT_Y;++i){
		for(int j = 0;j < COUNT_X;++j){
			if(sameArr[i][j] == true){
				starArr[i][j] = 0;
				count++;
			}
		}
	}

	//方块下落
	for(int i = 0;i < COUNT_Y;++i){
		for(int j = 0;j < COUNT_X;++j){
			if(starArr[i][j] == 0){
				int k = i;
				for(; k > 0; --k){
					starArr[k][j] = starArr[k-1][j];
					if(starArr[k-1][j] == 0) break;
				}
				if(k == 0) starArr[0][j] = 0;
			}
		}
	}

	//方块左移
	for(int i = COUNT_X;i >= 0;--i){
		if(starArr[COUNT_Y-1][i] == 0){
			for(int j = 0;j < COUNT_Y;++j){
				for(int k = i;k < COUNT_X-1;++k){
					starArr[j][k] = starArr[j][k+1];
				}
				starArr[j][COUNT_X-1] = 0;
			}
				
		}
	}
		
	
	
	int score = count*count*5;
	this->score += score;
	return score;
}


int GameLogic::getScore(){
	return this->score;
}

//判断游戏是否结束
bool GameLogic::gameOver(int starArr[][COUNT_X]){
	for(int i = 0;i < COUNT_Y;++i){
		for(int j = 0;j < COUNT_X;++j){
			if(starArr[i][j] != 0){
				for(int k = 0;k < 4;++k){
					int a = i+direction[k][0];
					int b = j+direction[k][1];
					if(a<0||b<0||a>=COUNT_Y||b>=COUNT_X) continue;
					if(starArr[a][b] != 0 && starArr[i][j] == starArr[a][b]) return false;
				}
			}
		}
	}
	return true;
}

//修改最终的分数，公式2000分-剩余个数*5,返回值为判断是否通关
bool GameLogic::passLevel(int starArr[][COUNT_X]){
	int count = 0;
	for(int i = 0;i < COUNT_Y;++i){
		for(int j = 0;j < COUNT_X;++j){
			if(starArr[i][j] != 0){
				count++;
			}
		}
	}
	if(count<=10)this->score += 2000 - count*50;
	if(this->score >= 1000+2000*(this->level-1)) {
		level++;
		return true;
	}
	return false;
}

void GameLogic::maxScoreAlter(){
	Account accounts[20];
	//文件读取
	fstream fI("resourse\\AccountMsg.txt", ios::in|ios::binary);
	int i = 0;
	fI.peek();
	while(!fI.eof() && i < 20){
		fI.read((char *)&accounts[i], sizeof(Account));
		i++;
		fI.peek();
	}

	fI.close();

	for(int j = 0;j < i;++j){
		if(this->userName.compare(accounts[j].name)==0){
			accounts[j].score = this->score;
			cout<<"max:"<<accounts[j].score<<endl;
			break;
		}
	}

	fstream fO("resourse\\AccountMsg.txt", ios::out|ios::trunc|ios::binary);


	for(int j = 0;j < i;++j){
		cout<<accounts[j].name<<accounts[j].score<<endl;
		Account *accountID = &accounts[j];
		fO.write((char*)accountID,sizeof(*accountID));
	}

	fO.close();
}

int GameLogic::gameOverDisplay(bool alter){
	if(alter) this->maxScoreAlter();//alter为true时，为需要修改分数的情况，即最高分改变时
	
	//cleardevice();
	
	BeginBatchDraw();
	
	putimage(100,50,&gameOverImage);

	module->textBox(315,215,35,80,"",this->getScore());
	module->textBox(315,350,35,80,"",ppAccount->score);

	EndBatchDraw();

	while(true){
		int click = this->catchMouse(point);//监听鼠标信息
		if(click && point.x >=300 && point.x <= 465 && point.y >= 475 && point.y <= 595){//鼠标有点击的情况进入if语句
			if(point.y >= 475 && point.y <= 510){
				//再来一局
				return -1;
			}else if(point.y >= 520 && point.y <= 555){
				//返回主菜单
				return 1;
			}else if(point.y >= 560 && point.y <= 595){
				//退出游戏
				return 0;
			}
		}
		Sleep(5);//可以大大减少死循环占用的资源，且5ms不会对实际操作造成大的影响（可忽略）
	}
}


int GameLogic::mainLogic(){
	bool passLevel = true;
	bool gameOver = false;
	bool alter = false;
	while(passLevel){
		this->starArrInit(starArr,seed);
		this->starDisplay(starArr);
		gameOver = false;
		while(!gameOver){
			int click = this->catchMouse(point);//监听鼠标信息
			if(click){//鼠标有点击的情况进入if语句
				this->starDisplay(starArr);//星星的显示
				bool box = this->judgeTheSame(point,starArr,sameArr);//若点击的块有2个及以上 为true
				this->sameArrPrint(sameArr);//控制台查看相同数组的情况，不影响前台显示
				if(box) this->displayBox(box,sameArr);//显示方框
				if(click==2 && box) {
					mciSendString("close resourse\\PopMusic.mp3",NULL,0,NULL);
					mciSendString("play resourse\\PopMusic.mp3",NULL,0,NULL);
					this->pop(starArr,sameArr);//若点击的块有2个及以上且双击，消灭星星
					this->starDisplay(starArr);//星星的显示
					gameOver = this->gameOver(starArr);//游戏结束的判断
				}
				this->sameArrReset(sameArr);//用于存放相同元素数组的清空
			}
			Sleep(5);//可以大大减少死循环占用的资源，且5ms不会对实际操作造成大的影响（可忽略）
		}
		passLevel = this->passLevel(starArr);
		if(passLevel){
			//显示成功晋级并且显示分数
			

			BeginBatchDraw();
			putimage(250,200,&passLevelImage);
			EndBatchDraw();

			cout<<"分数："<<this->getScore()<<"晋级成功！"<<endl;
			Sleep(1500);
		}else{
			if(ppAccount->score < this->getScore()){
				ppAccount->score = this->getScore();
				alter = true;
			}
			//显示最后分数和失败退出按钮
			cout<<"分数："<<this->getScore()<<"gameOver！"<<endl;
		}
	}
	//gameover
	return this->gameOverDisplay(alter);
}