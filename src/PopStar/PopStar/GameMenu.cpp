#include "GameMenu.h"
#include "GlobalDefine.h"
#include <iostream>
#include<graphics.h>
#include<conio.h>
#include<sstream>
#include<string>
#include"displayModule.h"
#include <fstream>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

using namespace std;

Point mousePoint;//储存鼠标的坐标

DisplayModule *text;//文本模块对象指针

Account *pAccount;//用户对象指针

bool jump = false,enter = false;//enter用于回车登陆，jump tab跳转

bool sound = true;//声音是否开启

GameMenu::GameMenu(Account &account)
{
	pAccount = &account;//用于main函数接受用户的结构体

	initgraph(WINDOW_X,WINDOW_Y,NOMINIMIZE);
	loadimage(&this->menuImage,"Image\\menu.jpg",WINDOW_X,WINDOW_Y);
	loadimage(&this->loginAImage,"Image\\loginA.jpg",WINDOW_X,WINDOW_Y);
	loadimage(&this->findPwdImage1,"Image\\findPwd1.jpg",WINDOW_X,WINDOW_Y);
	loadimage(&this->findPwdImage2,"Image\\findPwd2.jpg",WINDOW_X,WINDOW_Y);
	loadimage(&this->loginBImage,"Image\\loginB.jpg",WINDOW_X,WINDOW_Y);
	loadimage(&this->rankListImage,"Image\\rankList.jpg",WINDOW_X,WINDOW_Y);
	loadimage(&this->setImage,"Image\\set.jpg",WINDOW_X,WINDOW_Y);
	loadimage(&this->setImage1,"Image\\set1.jpg",WINDOW_X,WINDOW_Y);
	loadimage(&this->explainImage,"Image\\explain.jpg",WINDOW_X,WINDOW_Y);
	loadimage(&this->bsA,"Image\\bsA.jpg",270,45);
	loadimage(&this->bsB,"Image\\bsB.jpg",270,45);

	//播放背景音乐
	mciSendString("open resourse\\canon.mp3 alias bkmusic",NULL,0,NULL);
	mciSendString("play bkmusic repeat",NULL,0,NULL);
	
	//初始化
	text = new DisplayModule;
	
}

GameMenu::~GameMenu(){
	delete text;
}


void GameMenu::menu(){
	int res = 1;
	while(res){
		//加载菜单图像
		putimage(0,0,&this->menuImage);
		int click = this->catchMouse(mousePoint);//获取鼠标点击信息
		if(click == 1 && mousePoint.x >= 270 && mousePoint.x <=440){//点击登陆时
			while(res == 3||mousePoint.y >= 95 && mousePoint.y <= 165){ //res == 1时是返回 res == 0登陆成功
				res = this->loginA();
				if(res == 2){
					this->clear();
					cout<<"this->loginAName:"<<this->loginAName;
					res = this->findPwd();
					this->clear();
				}
			}
			if(mousePoint.y >= 200 && mousePoint.y <= 270){//点击注册
				this->loginB();
			}else if(mousePoint.y >= 320 && mousePoint.y <= 390){//点击设置
				this->set();
			}else if(mousePoint.y >= 440 && mousePoint.y <= 510){//点击排行
				this->rankList();
			}else if(mousePoint.y >= 560 && mousePoint.y <= 630){//点击说明
				this->explain();
			}
		}
		Sleep(5);
	}
}

int GameMenu::loginA(){
	putimage(0,0,&this->loginAImage);//加载登陆图片
	while(true){
		int click = this->catchMouse(mousePoint);//获取鼠标信息
		if(click){
			if(mousePoint.y >= 20 && mousePoint.y <= 70){
				if(mousePoint.x >= 0 && mousePoint.x <= 140){//点击BACK
					//back
					this->clear();
					return 1;
				}
			}
			if(mousePoint.x >= 290 && mousePoint.x <= 570){
				if(mousePoint.y >= 110 && mousePoint.y <= 165){//点击账号输入框
					//账号框
					stringstream stream;//方便用于字符串的拼接删减
					stream<<this->loginAName;//获取本来存在的内容，防止进行后，再回来时，原本输入的内容消失
					int length = this->loginAName.size();//获取长度
					
					while(true){
						int click = this->catchMouse(mousePoint);//鼠标
						if(click!=0 && !(mousePoint.x >= 290 && mousePoint.x <= 570 && mousePoint.y >= 110 && mousePoint.y <= 165)){//点击其他位置时
							this->loginAName = stream.str();
							break;
						}
						
						if(_kbhit()){//键盘有输入时
							char ch = _getch();//获取字符
							if(ch =='\r'){//若为回车 window回车键为"\r\n",读到‘\r’则是回车
								this->loginAName = stream.str();//将内容存到属性中，防止丢失
								enter = true;//确认
								break;
							}else if(ch == 9){
								this->loginAName = stream.str();//将内容存到属性中，防止丢失
								jump = true;//tab可进行下一逻辑的跳转
								break;
							}else if(ch==8){//按下删除键
								if(length > 0) {--length;//长度-1
								putimage(295,115,&this->bsA);//遮挡输入框内容
								string temp = stream.str().substr(0,length);//切割字符，使得删除的字符丢失
								stream.str("");//清空stream
								stream<<temp;//stream获取修改后的字符串
								text->textBox(295,115,TEXT_WIDTH,TEXT_HEIGHT,stream.str());//显示内容
								}
							}else if(ch>='0'&&ch<='9'||ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'){//若为数字字母
								if(length>=13)continue;//长度不得大于13位
								stream<<ch;
								text->textBox(295,115,TEXT_WIDTH,TEXT_HEIGHT,stream.str());//显示
								++length;//长度+1
							}
						}
					}
				}
				if(jump ||mousePoint.y >= 180 && mousePoint.y <= 240){//上一个输入框按下回车或者鼠标点击此处
					jump = false;//为下次回车做准备
					//密码框
					stringstream stream,stream1;//stream1为存储对应长度的‘*’号
					stream<<this->loginAPwd;
					int length = this->loginAPwd.size();
					for(int i = 0;i < length;++i){
						stream1<<'*';
					}
					int flash = -1;
					
					while(true){
						int click = this->catchMouse(mousePoint);
						if(click!=0 && !(mousePoint.x >= 290 && mousePoint.x <= 570 && mousePoint.y >= 180 && mousePoint.y <= 240)){
							this->loginAPwd = stream.str();
							cout<<"this->loginAPwd:"<<this->loginAPwd;
							break;
						}

						if(_kbhit()){
							char ch = _getch();
							if(ch=='\r'){
								enter = true;
								this->loginAPwd = stream.str();
								cout<<stream.str();
								break;
							}else if(ch==8){
								if(length > 0){
									--length;
									putimage(295,185,&this->bsA);
									string temp = stream.str().substr(0,length);
									stream.str("");
									stream1.str("");
									stream<<temp;
									for(int i = 0;i < length;++i){//获得对应长度的‘*’号
										stream1<<'*';
									}
									text->textBox(295,185,TEXT_WIDTH,TEXT_HEIGHT,stream1.str());//显示‘*’号
								}
							}else if(ch>='0'&&ch<='9'||ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'){
								if(length>=13)continue;
								stream<<ch;
								stream1<<'*';
								text->textBox(295,185,TEXT_WIDTH,TEXT_HEIGHT,stream1.str());//显示‘*’号
								++length;
							}
						}
					}
				}
			}
			//登陆与找回密码
			if(enter || mousePoint.y >= 250 && mousePoint.y <= 325){
				if(mousePoint.x >= 170 && mousePoint.x <= 390){
					//找回密码
					return 2;
				}else if(enter || mousePoint.x >= 435 && mousePoint.x <= 555){
					enter = false;
					//登陆
					//读取文件中的内容
					Account accounts[20];
					fstream fio("resourse\\AccountMsg.txt", ios::in|ios::binary);
					int i = 0;
					fio.peek();//peek() 与 eof()函数配合可以判断当前文件指针是否为空
					while(!fio.eof() && i < 20){
						fio.read((char *)&accounts[i], sizeof(Account));
						fio.peek();
						i++;
					}
					fio.close();//关闭文件流
					for(int j = 0;j < i;++j){
						//cout<<accounts[j].name<<endl;
						if(this->loginAName.compare(accounts[j].name)==0 && this->loginAPwd.compare(accounts[j].pwd)==0){
							cout<<"succeed"<<endl;
							//将文件读取到当前用户结构体中
							strcpy_s(pAccount->name, accounts[j].name);
							strcpy_s(pAccount->pwd, accounts[j].pwd);
							strcpy_s(pAccount->question, accounts[j].question);
							strcpy_s(pAccount->answer, accounts[j].answer);
							pAccount->score = accounts[j].score;

							return 0;
						}
					}

					putimage(215,20,&this->bsA);
					text->textBox(215,20,TEXT_WIDTH,TEXT_HEIGHT,"密码或账号错误！");
					
				}
			}
		}
		Sleep(5);
	}
}

//以下内容逻辑有些与上面有重复 不多做注释
int GameMenu::loginB(){
	putimage(0,0,&this->loginBImage);
	while(true){
		int click = this->catchMouse(mousePoint);
		if(click){

			if(mousePoint.x <= 95 && mousePoint.y <= 50){
				//back
				this->clear();
				return 0;
			}

			if(mousePoint.x >= 235 && mousePoint.x <= 620){
				if(mousePoint.y >= 100 && mousePoint.y <= 155){
					jump = false;
					//注册的账号
					stringstream stream;
					stream<<this->loginBName;
					int length = this->loginBName.size();
					int flash = -1;
					
					while(true){
						int click = this->catchMouse(mousePoint);
						if(click!=0 && !(mousePoint.x >= 235 && mousePoint.x <= 620 && mousePoint.y >= 100 && mousePoint.y <= 155)){
							this->loginBName = stream.str();
							cout<<"this->loginBName:"<<this->loginAName;
							break;
						}
						if(_kbhit()){
							char ch = _getch();
							if(ch=='\r'){
								this->loginBName = stream.str();
								enter = true;
								break;
							}else if(ch == 9){
								this->loginBName = stream.str();
								jump = true;//tab可进行下一逻辑的跳转
								break;
							}else if(ch==8){
								if(length > 0) {
									--length;
									putimage(235,105,&this->bsB);
									string temp = stream.str().substr(0,length);
									stream.str("");
									stream<<temp;
									text->textBox(235,105,TEXT_WIDTH,TEXT_HEIGHT,stream.str());
								}
							}else if(ch>='0'&&ch<='9'||ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'){
								if(length>=13)continue;
								stream<<ch;
								text->textBox(235,105,TEXT_WIDTH,TEXT_HEIGHT,stream.str());
								++length;
							}
						}
						Sleep(5);
					}
				}
				if(jump || mousePoint.y >= 175 && mousePoint.y <= 230){
					jump = false;
					//判断账号是否有重复
					bool flag = true;
					Account accountID;
					fstream fI("resourse\\AccountMsg.txt",ios::in|ios::binary);

					int i = 0;

					fI.peek();
					while(!fI.eof() && i < 20){
						fI.read((char*)&accountID,sizeof(accountID));
						if(loginBName.compare(accountID.name) == 0){
							 flag = false;
							 putimage(250,50,&this->bsB);
							 text->textBox(250,50,TEXT_WIDTH,TEXT_HEIGHT,"此账号已存在！");
						}
						i++;
						fI.peek();
					}
					fI.close();

					if(flag){
						//注册的密码
						putimage(250,50,&this->bsB);
						stringstream stream,stream1;
						stream<<this->loginBPwd;
						int length = this->loginBPwd.size();
						for(int i = 0;i < length;++i){
							stream1<<'*';
						}
						int flash = -1;
					
						while(true){
							int click = this->catchMouse(mousePoint);
							if(click!=0 && !(mousePoint.x >= 235 && mousePoint.x <= 620 && mousePoint.y >= 175 && mousePoint.y <= 230)){
								this->loginBPwd = stream.str();
								cout<<"this->loginBPwd:"<<this->loginBPwd;
								break;
							}
							if(_kbhit()){
								char ch = _getch();
								if(ch=='\r'){
									this->loginBPwd = stream.str();
									
									enter = true;
									break;
								}else if(ch == 9){
									this->loginBPwd = stream.str();
									jump = true;//tab可进行下一逻辑的跳转
									break;
								}else if(ch==8){
									if(length > 0) {
										--length;
										putimage(235,180,&this->bsB);
										string temp = stream.str().substr(0,length);
										stream.str("");
										stream1.str("");
										stream<<temp;
										for(int i = 0;i < length;++i){
											stream1<<'*';
										}
										text->textBox(235,180,TEXT_WIDTH,TEXT_HEIGHT,stream1.str());
									}
								}else if(ch>='0'&&ch<='9'||ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'){
									if(length>=13)continue;
									stream<<ch;
									stream1<<'*';
									text->textBox(235,180,TEXT_WIDTH,TEXT_HEIGHT,stream1.str());
									++length;
								}
							}
							Sleep(5);
						}
					}
					if(jump || mousePoint.y >= 255 && mousePoint.y <= 310){
						jump = false;
						//确认密码
						stringstream stream,stream1;
						stream<<this->loginBPwdCon;
						int length = this->loginBPwdCon.size();
						for(int i = 0;i < length;++i){
							stream1<<'*';
						}
						int flash = -1;
					
						while(true){
							int click = this->catchMouse(mousePoint);
							if(click!=0 && !(mousePoint.x >= 235 && mousePoint.x <= 620 && mousePoint.y >= 255 && mousePoint.y <= 310)){
								this->loginBPwdCon = stream.str();
								cout<<"this->loginBPwdCon:"<<this->loginBPwdCon;
								break;
							}
							if(_kbhit()){
								char ch = _getch();
								if(ch=='\r'){
									this->loginBPwdCon = stream.str();
									enter = true;
									break;
								}else if(ch == 9){
									this->loginBPwdCon = stream.str();
									jump = true;//tab可进行下一逻辑的跳转
									break;
								}else if(ch==8){
									if(length > 0) {
										--length;
										putimage(235,260,&this->bsB);
										string temp = stream.str().substr(0,length);
										stream.str("");
										stream1.str("");
										stream<<temp;
										for(int i = 0;i < length;++i){
											stream1<<'*';
										}
										text->textBox(235,260,TEXT_WIDTH,TEXT_HEIGHT,stream1.str());
									}
								}else if(ch>='0'&&ch<='9'||ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'){
									if(length>=13)continue;
									stream<<ch;
									stream1<<'*';
									text->textBox(235,260,TEXT_WIDTH,TEXT_HEIGHT,stream1.str());
									++length;
								}
							}
							Sleep(5);
						}
					}

				}
				if(jump || mousePoint.y >= 335 && mousePoint.y <= 390){
					jump = false;
					//密保问题
					stringstream stream;
					stream<<this->question;
					int length = this->question.size();
					int flash = -1;
					
					while(true){
						int click = this->catchMouse(mousePoint);
						if(click!=0 && !(mousePoint.x >= 235 && mousePoint.x <= 620 && mousePoint.y >= 335 && mousePoint.y <= 390)){
							this->question = stream.str();
							cout<<"this->question:"<<this->question;
							break;
						}
						if(_kbhit()){
							char ch = _getch();
							if(ch=='\r'){
								this->question = stream.str();
								cout<<stream.str();
								enter = true;
								break;
							}else if(ch == 9){
								this->question = stream.str();
								jump = true;//tab可进行下一逻辑的跳转
								break;
							}else if(ch==8){
								if(length > 0) {
									--length;
									putimage(235,340,&this->bsB);
									string temp = stream.str().substr(0,length);
									stream.str("");
									stream<<temp;
									text->textBox(235,340,TEXT_WIDTH,TEXT_HEIGHT,stream.str());
								}
								//密保问题可以有空格 和 问号字符
							}else if(ch=='?'||ch==' '||ch>='0'&&ch<='9'||ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'){
								if(length>=13)continue;
								stream<<ch;
								text->textBox(235,340,TEXT_WIDTH,TEXT_HEIGHT,stream.str());
								++length;
							}
						}
						Sleep(5);
					}

				}
				if(jump || mousePoint.y >= 410 && mousePoint.y <= 465){
					jump = false;
					//答案
					stringstream stream;
					stream<<this->answer;
					int length = this->answer.size();
					int flash = -1;
					
					while(true){
						int click = this->catchMouse(mousePoint);
						if(click!=0 && !(mousePoint.x >= 235 && mousePoint.x <= 620 && mousePoint.y >= 410 && mousePoint.y <= 465)){
							this->answer = stream.str();
							cout<<"this->question:"<<this->answer;
							break;
						}
						if(_kbhit()){
							char ch = _getch();
							if(ch=='\r'){
								this->answer = stream.str();
								cout<<stream.str();
								enter = true;
								break;
							}else if(ch==8){
								if(length > 0) {
									--length;
									putimage(235,415,&this->bsB);
									string temp = stream.str().substr(0,length);
									stream.str("");
									stream<<temp;
									text->textBox(235,415,TEXT_WIDTH,TEXT_HEIGHT,stream.str());
								}
							}else if(ch>='0'&&ch<='9'||ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'){
								if(length>=13)continue;
								stream<<ch;
								text->textBox(235,415,TEXT_WIDTH,TEXT_HEIGHT,stream.str());
								++length;
							}
						}
						
						Sleep(5);
					}
				}

				if(enter || mousePoint.x >= 240 && mousePoint.x <= 515 && mousePoint.y >= 530 && mousePoint.y <= 620){
					enter = false;
					//确定注册
					//输入的内容不能为空 为空则注册失败，且显示提示
					if(this->loginBName.compare("") == 0||this->loginBPwd.compare("") == 0||
								this->question.compare("") == 0||this->answer.compare("") == 0){
						putimage(250,50,&this->bsB);
						text->textBox(250,50,TEXT_WIDTH,TEXT_HEIGHT,"输入的内容不能为空！");
					}
					//字符串比较loginBPwd和loginBpwdCon
					else if(this->loginBPwd == this->loginBPwdCon) {
						//若相同，将用户信息写到文件中
						fstream fio("resourse\\AccountMsg.txt",ios::app|ios::binary);//文件输出流
						if(fio.bad()){
							cout << "打开文件出错" << endl;
							return 0;
						}else{
							Account *accountID = new Account;
							strcpy_s(accountID->name,this->loginBName.c_str());
							strcpy_s(accountID->pwd,this->loginBPwd.c_str());
							strcpy_s(accountID->question,this->question.c_str());
							strcpy_s(accountID->answer,this->answer.c_str());
							accountID->score = 0;

							fio.write((char*)accountID,sizeof(*accountID));
						}
						fio.close();
						
						putimage(250,50,&this->bsB);
						text->textBox(250,50,TEXT_WIDTH,TEXT_HEIGHT,"注册成功！2s后返回主菜单。");
						Sleep(2000);
						return 0;
					}else{
						cout<<"确认密码错误"<<endl;
					}
				}
			}
		}
	}
}

int GameMenu::findPwd(){
	Account accountID;
	putimage(0,0,&this->findPwdImage1);
	while(true){
		int click = this->catchMouse(mousePoint);
		if(click){
			if(mousePoint.y >= 20 && mousePoint.y <= 70){
				if(mousePoint.x >= 0 && mousePoint.x <= 140){
					//back
					return 3;
				}
			}
			if(mousePoint.y >= 90 && mousePoint.y <= 150){
				if(mousePoint.x >= 210 && mousePoint.x <= 550){
					//输入账号
					stringstream stream;
					stream<<this->loginAName;
					int length = this->loginAName.size();
					int flash = -1;
					
					while(true){
						int click = this->catchMouse(mousePoint);
						if(click!=0 && !(mousePoint.x >= 210 && mousePoint.x <= 550 && mousePoint.y >= 90 && mousePoint.y <= 150)){
							this->loginAName = stream.str();
							cout<<"this->loginAName"<<this->loginAName;
							break;
						}
						if(_kbhit()){
							char ch = _getch();
							if(ch=='\r'){
								this->loginAName = stream.str();
								cout<<stream.str();
								enter = true;
								break;
							}else if(ch==8){
								if(length > 0) {
									--length;
									putimage(210,95,&this->bsA);
									string temp = stream.str().substr(0,length);
									stream.str("");
									stream<<temp;
									text->textBox(210,95,TEXT_WIDTH,TEXT_HEIGHT,stream.str());
								}
							}else if(ch>='0'&&ch<='9'||ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'){
								if(length>=13)continue;
								stream<<ch;
								text->textBox(210,95,TEXT_WIDTH,TEXT_HEIGHT,stream.str());
								++length;
							}
						}
						Sleep(5);
					}
				}
			}
			if(enter || mousePoint.x >= 555 && mousePoint.x <= 685 && mousePoint.y >= 90 && mousePoint.y <= 150){
				enter = false;
				//确定账号

				//读取文件内容
				Account accounts[20];
				fstream fio("resourse\\AccountMsg.txt", ios::in|ios::binary);
				int i = 0;
				fio.peek();
				while(!fio.eof() && i < 20){
					fio.read((char *)&accounts[i], sizeof(Account));
					i++;
					fio.peek();
				}
				fio.close();
				int j;
				for(j = 0;j < i;++j){
					//若找到账号 ，显示出问题
					if(this->loginAName.compare(accounts[j].name)==0){
						text->textBox(230,175,TEXT_WIDTH,TEXT_HEIGHT,accounts[j].question);
						accountID = accounts[j];
						break;
					}
				}
				
				if(j==i){
					//无此账号
					putimage(215,20,&this->bsA);
					text->textBox(215,20,TEXT_WIDTH,TEXT_HEIGHT,"不存在此账号！");
				}else{
					//输入账号
					stringstream stream;
					stream<<this->answer;
					int length = this->answer.size();
					
					while(true){
						int click = this->catchMouse(mousePoint);
						if(click!=0 && !(mousePoint.x >= 225 && mousePoint.x <= 550 && mousePoint.y >= 245 && mousePoint.y <= 305)){
							this->answer = stream.str();
							cout<<"this->answer"<<this->answer;
							break;
						}
						if(_kbhit()){
							char ch = _getch();
							if(ch=='\r'){
								this->answer = stream.str();
								cout<<stream.str();
								enter = true;
								break;
							}else if(ch==8){
								if(length > 0) {
									--length;
									putimage(225,245,&this->bsA);
									string temp = stream.str().substr(0,length);
									stream.str("");
									stream<<temp;
									text->textBox(225,245,TEXT_WIDTH,TEXT_HEIGHT,stream.str());
								}
							}else if(ch>='0'&&ch<='9'||ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'){
								if(length>=13)continue;
								stream<<ch;
								text->textBox(225,245,TEXT_WIDTH,TEXT_HEIGHT,stream.str());
								++length;
							}
						}
						Sleep(5);
					}
				}

				if(enter || mousePoint.x >= 560 && mousePoint.x <= 685 && mousePoint.y >= 235 && mousePoint.y <= 310){
					enter = false;
					//确定答案	
					//若答案正确显示密码
					if(this->answer.compare(accountID.answer) == 0){
						putimage(0,0,&this->findPwdImage2);
						text->textBox(210,95,TEXT_WIDTH,TEXT_HEIGHT,accountID.name);
						text->textBox(230,175,TEXT_WIDTH,TEXT_HEIGHT,accountID.question);
						text->textBox(230,245,TEXT_WIDTH,TEXT_HEIGHT,accountID.answer);

						putimage(215,20,&this->bsA);
						text->textBox(215,20,TEXT_WIDTH,TEXT_HEIGHT,"3s后自动返回登陆界面！");

						//显示密码
						text->textBox(350,440,TEXT_WIDTH,TEXT_HEIGHT,accountID.pwd);

						Sleep(3000);
						return 3; //return 3 可以返回上一级
					}else{
						putimage(215,20,&this->bsA);
						text->textBox(215,20,TEXT_WIDTH,TEXT_HEIGHT,"答案错误！");
					}
				}
			}
		}
	}
	return 0;
}
void GameMenu::set(){
	//判断sound，判断音乐播放状态，显示对应图片
	if(sound)putimage(0,0,&this->setImage);
	else putimage(0,0,&this->setImage1);
	
	while(true){
		int click = this->catchMouse(mousePoint);
		if(click){
			if(mousePoint.x >= 0 && mousePoint.x <= 120 && mousePoint.y >= 0 && mousePoint.y <= 55){
				//BACK
				return;
			}
			if(mousePoint.x >= 330 && mousePoint.x <= 450 && mousePoint.y >= 200 && mousePoint.y <= 280){
				//
				if(sound){
					//音乐在播放时，暂停音乐
					mciSendString("stop bkmusic",NULL,0,NULL);
					putimage(0,0,&this->setImage1);
					sound = false;
				}else {
					//没有播放时，播放
					mciSendString("play bkmusic",NULL,0,NULL);
					putimage(0,0,&this->setImage);
					sound = true;
				}
			}
		}
	}
}

void GameMenu::rankList(){//只显示前11名
	putimage(0,0,&this->rankListImage);
	//读取文件内容
	Account accounts[20];
	fstream fio("resourse\\AccountMsg.txt", ios::in|ios::binary);
	int i = 0;
	fio.peek();
	while(!fio.eof() && i < 20){
		fio.read((char *)&accounts[i], sizeof(Account));
		i++;
		fio.peek();
	}
	fio.close();
	

	//对分数进行排序
	for(int j = 0;j < i;++j){
		int temp = accounts[j].score;
		for(int k = j+1;k < i;++k){
			if(temp < accounts[k].score) temp = accounts[k].score;
		}
		accounts[j].score = temp;
	}

	stringstream stream;

	//显示排行
	for(int j = 0;j < i;++j){
		cout<<accounts[j].name<<endl;
		stream<<j+1<<"、"<<accounts[j].name<<"     score:"<<accounts[j].score;
		text->textBox(110,30+j*60,TEXT_WIDTH,TEXT_HEIGHT,stream.str());
		stream.str("");
	}
	while(true){
		if((this->catchMouse(mousePoint) && mousePoint.x<=110 && mousePoint.y <= 50)) return;
		Sleep(5);
	}
	
}

void GameMenu::explain(){
	//显示说明
	putimage(0,0,&this->explainImage);
	while(true){
		if((this->catchMouse(mousePoint) && mousePoint.x<=80 && mousePoint.y <= 50)) return;
		Sleep(5);
	}
}

void GameMenu::clear(){
	//用于清楚类中属性
	string empty("");
	this->loginAName = empty;
	this->loginAPwd = empty;
	this->loginBName= empty;
	this->loginBPwd= empty;
	this->loginBPwdCon= empty;
	this->question= empty;
	this->answer= empty;
}

int GameMenu::catchMouse(Point &point){
	//用于获取鼠标的信息
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

