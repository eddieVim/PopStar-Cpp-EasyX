#include "GameLogic.h"
#include <iostream>
#include<graphics.h>
#include<queue>
#include"star.h"
#include <conio.h>
#include<fstream>



int direction[4][2] = {{0,-1},{0,1},{-1,0},{1,0}};//��������

IMAGE bgImage,gameOverImage,passLevelImage,BoxImage[2];//���ڴ洢ͼƬ

Star *star;//����������ʾ

Point point;//�洢������ĵ�

DisplayModule *module;//������ʾ�ַ�����ģ��

Account *ppAccount;//�洢�û���Ϣ

int starArr[COUNT_Y][COUNT_X];//�����������õ�����

bool sameArr[COUNT_Y][COUNT_X];//�����ͬ�������õ�����

LPCTSTR boxPImgFile[2] = {
	"Image\\box.jpg",
	"Image\\box1.jpg"
};//͸���߿��·��

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
	//��ʼ��Star����Star�����ڽ�����ʾ
	
	
	BeginBatchDraw();

	putimage(0,0,&bgImage);//����ˢ��

	module->textBox(0,0,15,30,"�û���",this->userName);
	module->textBox(0,30,15,30,"������",this->score);
	module->textBox((WINDOW_X-7*TEXT_WIDTH)/2,0,15,30,"level��",this->level);//(WINDOW_X-7*TEXT_WIDTH)/2
	module->textBox((WINDOW_X-7*TEXT_WIDTH)/2,30,15,30,"������Ҫ������",1000+2000*(this->level-1));
	
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
//pointΪ�������Ľṹ��
int GameLogic::catchMouse(Point &point){
	if (MouseHit()){
		MOUSEMSG msg = GetMouseMsg();
		switch (msg.uMsg){
		case WM_LBUTTONDOWN://�������
			//��������
			point.x = msg.x;
			point.y = msg.y;
			cout<<"���������X��"<<point.x<<"Y:"<<point.y<<endl;
			return 1;
		case WM_LBUTTONDBLCLK://˫��
			//��������
			point.x = msg.x;
			point.y = msg.y;
			cout<<"˫����X��"<<point.x<<"Y:"<<point.y<<endl;
			return 2;
		default:
			point.x = -1;
			point.y = -1;
		}
	}
	//û�е��
	return 0;
}


//ʹ�ù�����������㷨��BFS�����ҵ����ڷ���ĵ�
bool  GameLogic::judgeTheSame(Point &point,int starArr[][COUNT_X],bool sameArr[][COUNT_X]){
	if(point.y < TOP_MARGIN) return 0;//������������������ʱ��
	int y = (point.y-TOP_MARGIN)/STAR_Y;//�����������е�λ�� ��
	int x = point.x/STAR_X;//�����������е�λ�� ��
	int color = starArr[y][x];//������ɫ
	if(color==0) return 0;//������ʱ��ֱ�ӷ���
	int count = 1;//��ͬ����ɫ���Ǹ���

	//�洢����Ķ���
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
			//�жϸõ��Ƿ���ɫ��ͬ���Ƿ��ظ���
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

//��ʾ����
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

//�������ǲ����ط��� = �������Ǹ�����ƽ��*5
int GameLogic::pop(int starArr[][COUNT_X],bool sameArr[][COUNT_X]){
	int count = 0;

	//�ҳ���ͬ�ķ����������������
	for(int i = 0;i < COUNT_Y;++i){
		for(int j = 0;j < COUNT_X;++j){
			if(sameArr[i][j] == true){
				starArr[i][j] = 0;
				count++;
			}
		}
	}

	//��������
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

	//��������
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

//�ж���Ϸ�Ƿ����
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

//�޸����յķ�������ʽ2000��-ʣ�����*5,����ֵΪ�ж��Ƿ�ͨ��
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
	//�ļ���ȡ
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
	if(alter) this->maxScoreAlter();//alterΪtrueʱ��Ϊ��Ҫ�޸ķ��������������߷ָı�ʱ
	
	//cleardevice();
	
	BeginBatchDraw();
	
	putimage(100,50,&gameOverImage);

	module->textBox(315,215,35,80,"",this->getScore());
	module->textBox(315,350,35,80,"",ppAccount->score);

	EndBatchDraw();

	while(true){
		int click = this->catchMouse(point);//���������Ϣ
		if(click && point.x >=300 && point.x <= 465 && point.y >= 475 && point.y <= 595){//����е�����������if���
			if(point.y >= 475 && point.y <= 510){
				//����һ��
				return -1;
			}else if(point.y >= 520 && point.y <= 555){
				//�������˵�
				return 1;
			}else if(point.y >= 560 && point.y <= 595){
				//�˳���Ϸ
				return 0;
			}
		}
		Sleep(5);//���Դ�������ѭ��ռ�õ���Դ����5ms�����ʵ�ʲ�����ɴ��Ӱ�죨�ɺ��ԣ�
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
			int click = this->catchMouse(point);//���������Ϣ
			if(click){//����е�����������if���
				this->starDisplay(starArr);//���ǵ���ʾ
				bool box = this->judgeTheSame(point,starArr,sameArr);//������Ŀ���2�������� Ϊtrue
				this->sameArrPrint(sameArr);//����̨�鿴��ͬ������������Ӱ��ǰ̨��ʾ
				if(box) this->displayBox(box,sameArr);//��ʾ����
				if(click==2 && box) {
					mciSendString("close resourse\\PopMusic.mp3",NULL,0,NULL);
					mciSendString("play resourse\\PopMusic.mp3",NULL,0,NULL);
					this->pop(starArr,sameArr);//������Ŀ���2����������˫������������
					this->starDisplay(starArr);//���ǵ���ʾ
					gameOver = this->gameOver(starArr);//��Ϸ�������ж�
				}
				this->sameArrReset(sameArr);//���ڴ����ͬԪ����������
			}
			Sleep(5);//���Դ�������ѭ��ռ�õ���Դ����5ms�����ʵ�ʲ�����ɴ��Ӱ�죨�ɺ��ԣ�
		}
		passLevel = this->passLevel(starArr);
		if(passLevel){
			//��ʾ�ɹ�����������ʾ����
			

			BeginBatchDraw();
			putimage(250,200,&passLevelImage);
			EndBatchDraw();

			cout<<"������"<<this->getScore()<<"�����ɹ���"<<endl;
			Sleep(1500);
		}else{
			if(ppAccount->score < this->getScore()){
				ppAccount->score = this->getScore();
				alter = true;
			}
			//��ʾ��������ʧ���˳���ť
			cout<<"������"<<this->getScore()<<"gameOver��"<<endl;
		}
	}
	//gameover
	return this->gameOverDisplay(alter);
}