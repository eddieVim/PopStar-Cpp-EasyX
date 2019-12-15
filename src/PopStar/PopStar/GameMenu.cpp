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

Point mousePoint;//������������

DisplayModule *text;//�ı�ģ�����ָ��

Account *pAccount;//�û�����ָ��

bool jump = false,enter = false;//enter���ڻس���½��jump tab��ת

bool sound = true;//�����Ƿ���

GameMenu::GameMenu(Account &account)
{
	pAccount = &account;//����main���������û��Ľṹ��

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

	//���ű�������
	mciSendString("open resourse\\canon.mp3 alias bkmusic",NULL,0,NULL);
	mciSendString("play bkmusic repeat",NULL,0,NULL);
	
	//��ʼ��
	text = new DisplayModule;
	
}

GameMenu::~GameMenu(){
	delete text;
}


void GameMenu::menu(){
	int res = 1;
	while(res){
		//���ز˵�ͼ��
		putimage(0,0,&this->menuImage);
		int click = this->catchMouse(mousePoint);//��ȡ�������Ϣ
		if(click == 1 && mousePoint.x >= 270 && mousePoint.x <=440){//�����½ʱ
			while(res == 3||mousePoint.y >= 95 && mousePoint.y <= 165){ //res == 1ʱ�Ƿ��� res == 0��½�ɹ�
				res = this->loginA();
				if(res == 2){
					this->clear();
					cout<<"this->loginAName:"<<this->loginAName;
					res = this->findPwd();
					this->clear();
				}
			}
			if(mousePoint.y >= 200 && mousePoint.y <= 270){//���ע��
				this->loginB();
			}else if(mousePoint.y >= 320 && mousePoint.y <= 390){//�������
				this->set();
			}else if(mousePoint.y >= 440 && mousePoint.y <= 510){//�������
				this->rankList();
			}else if(mousePoint.y >= 560 && mousePoint.y <= 630){//���˵��
				this->explain();
			}
		}
		Sleep(5);
	}
}

int GameMenu::loginA(){
	putimage(0,0,&this->loginAImage);//���ص�½ͼƬ
	while(true){
		int click = this->catchMouse(mousePoint);//��ȡ�����Ϣ
		if(click){
			if(mousePoint.y >= 20 && mousePoint.y <= 70){
				if(mousePoint.x >= 0 && mousePoint.x <= 140){//���BACK
					//back
					this->clear();
					return 1;
				}
			}
			if(mousePoint.x >= 290 && mousePoint.x <= 570){
				if(mousePoint.y >= 110 && mousePoint.y <= 165){//����˺������
					//�˺ſ�
					stringstream stream;//���������ַ�����ƴ��ɾ��
					stream<<this->loginAName;//��ȡ�������ڵ����ݣ���ֹ���к��ٻ���ʱ��ԭ�������������ʧ
					int length = this->loginAName.size();//��ȡ����
					
					while(true){
						int click = this->catchMouse(mousePoint);//���
						if(click!=0 && !(mousePoint.x >= 290 && mousePoint.x <= 570 && mousePoint.y >= 110 && mousePoint.y <= 165)){//�������λ��ʱ
							this->loginAName = stream.str();
							break;
						}
						
						if(_kbhit()){//����������ʱ
							char ch = _getch();//��ȡ�ַ�
							if(ch =='\r'){//��Ϊ�س� window�س���Ϊ"\r\n",������\r�����ǻس�
								this->loginAName = stream.str();//�����ݴ浽�����У���ֹ��ʧ
								enter = true;//ȷ��
								break;
							}else if(ch == 9){
								this->loginAName = stream.str();//�����ݴ浽�����У���ֹ��ʧ
								jump = true;//tab�ɽ�����һ�߼�����ת
								break;
							}else if(ch==8){//����ɾ����
								if(length > 0) {--length;//����-1
								putimage(295,115,&this->bsA);//�ڵ����������
								string temp = stream.str().substr(0,length);//�и��ַ���ʹ��ɾ�����ַ���ʧ
								stream.str("");//���stream
								stream<<temp;//stream��ȡ�޸ĺ���ַ���
								text->textBox(295,115,TEXT_WIDTH,TEXT_HEIGHT,stream.str());//��ʾ����
								}
							}else if(ch>='0'&&ch<='9'||ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'){//��Ϊ������ĸ
								if(length>=13)continue;//���Ȳ��ô���13λ
								stream<<ch;
								text->textBox(295,115,TEXT_WIDTH,TEXT_HEIGHT,stream.str());//��ʾ
								++length;//����+1
							}
						}
					}
				}
				if(jump ||mousePoint.y >= 180 && mousePoint.y <= 240){//��һ��������»س�����������˴�
					jump = false;//Ϊ�´λس���׼��
					//�����
					stringstream stream,stream1;//stream1Ϊ�洢��Ӧ���ȵġ�*����
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
									for(int i = 0;i < length;++i){//��ö�Ӧ���ȵġ�*����
										stream1<<'*';
									}
									text->textBox(295,185,TEXT_WIDTH,TEXT_HEIGHT,stream1.str());//��ʾ��*����
								}
							}else if(ch>='0'&&ch<='9'||ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'){
								if(length>=13)continue;
								stream<<ch;
								stream1<<'*';
								text->textBox(295,185,TEXT_WIDTH,TEXT_HEIGHT,stream1.str());//��ʾ��*����
								++length;
							}
						}
					}
				}
			}
			//��½���һ�����
			if(enter || mousePoint.y >= 250 && mousePoint.y <= 325){
				if(mousePoint.x >= 170 && mousePoint.x <= 390){
					//�һ�����
					return 2;
				}else if(enter || mousePoint.x >= 435 && mousePoint.x <= 555){
					enter = false;
					//��½
					//��ȡ�ļ��е�����
					Account accounts[20];
					fstream fio("resourse\\AccountMsg.txt", ios::in|ios::binary);
					int i = 0;
					fio.peek();//peek() �� eof()������Ͽ����жϵ�ǰ�ļ�ָ���Ƿ�Ϊ��
					while(!fio.eof() && i < 20){
						fio.read((char *)&accounts[i], sizeof(Account));
						fio.peek();
						i++;
					}
					fio.close();//�ر��ļ���
					for(int j = 0;j < i;++j){
						//cout<<accounts[j].name<<endl;
						if(this->loginAName.compare(accounts[j].name)==0 && this->loginAPwd.compare(accounts[j].pwd)==0){
							cout<<"succeed"<<endl;
							//���ļ���ȡ����ǰ�û��ṹ����
							strcpy_s(pAccount->name, accounts[j].name);
							strcpy_s(pAccount->pwd, accounts[j].pwd);
							strcpy_s(pAccount->question, accounts[j].question);
							strcpy_s(pAccount->answer, accounts[j].answer);
							pAccount->score = accounts[j].score;

							return 0;
						}
					}

					putimage(215,20,&this->bsA);
					text->textBox(215,20,TEXT_WIDTH,TEXT_HEIGHT,"������˺Ŵ���");
					
				}
			}
		}
		Sleep(5);
	}
}

//���������߼���Щ���������ظ� ������ע��
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
					//ע����˺�
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
								jump = true;//tab�ɽ�����һ�߼�����ת
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
					//�ж��˺��Ƿ����ظ�
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
							 text->textBox(250,50,TEXT_WIDTH,TEXT_HEIGHT,"���˺��Ѵ��ڣ�");
						}
						i++;
						fI.peek();
					}
					fI.close();

					if(flag){
						//ע�������
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
									jump = true;//tab�ɽ�����һ�߼�����ת
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
						//ȷ������
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
									jump = true;//tab�ɽ�����һ�߼�����ת
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
					//�ܱ�����
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
								jump = true;//tab�ɽ�����һ�߼�����ת
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
								//�ܱ���������пո� �� �ʺ��ַ�
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
					//��
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
					//ȷ��ע��
					//��������ݲ���Ϊ�� Ϊ����ע��ʧ�ܣ�����ʾ��ʾ
					if(this->loginBName.compare("") == 0||this->loginBPwd.compare("") == 0||
								this->question.compare("") == 0||this->answer.compare("") == 0){
						putimage(250,50,&this->bsB);
						text->textBox(250,50,TEXT_WIDTH,TEXT_HEIGHT,"��������ݲ���Ϊ�գ�");
					}
					//�ַ����Ƚ�loginBPwd��loginBpwdCon
					else if(this->loginBPwd == this->loginBPwdCon) {
						//����ͬ�����û���Ϣд���ļ���
						fstream fio("resourse\\AccountMsg.txt",ios::app|ios::binary);//�ļ������
						if(fio.bad()){
							cout << "���ļ�����" << endl;
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
						text->textBox(250,50,TEXT_WIDTH,TEXT_HEIGHT,"ע��ɹ���2s�󷵻����˵���");
						Sleep(2000);
						return 0;
					}else{
						cout<<"ȷ���������"<<endl;
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
					//�����˺�
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
				//ȷ���˺�

				//��ȡ�ļ�����
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
					//���ҵ��˺� ����ʾ������
					if(this->loginAName.compare(accounts[j].name)==0){
						text->textBox(230,175,TEXT_WIDTH,TEXT_HEIGHT,accounts[j].question);
						accountID = accounts[j];
						break;
					}
				}
				
				if(j==i){
					//�޴��˺�
					putimage(215,20,&this->bsA);
					text->textBox(215,20,TEXT_WIDTH,TEXT_HEIGHT,"�����ڴ��˺ţ�");
				}else{
					//�����˺�
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
					//ȷ����	
					//������ȷ��ʾ����
					if(this->answer.compare(accountID.answer) == 0){
						putimage(0,0,&this->findPwdImage2);
						text->textBox(210,95,TEXT_WIDTH,TEXT_HEIGHT,accountID.name);
						text->textBox(230,175,TEXT_WIDTH,TEXT_HEIGHT,accountID.question);
						text->textBox(230,245,TEXT_WIDTH,TEXT_HEIGHT,accountID.answer);

						putimage(215,20,&this->bsA);
						text->textBox(215,20,TEXT_WIDTH,TEXT_HEIGHT,"3s���Զ����ص�½���棡");

						//��ʾ����
						text->textBox(350,440,TEXT_WIDTH,TEXT_HEIGHT,accountID.pwd);

						Sleep(3000);
						return 3; //return 3 ���Է�����һ��
					}else{
						putimage(215,20,&this->bsA);
						text->textBox(215,20,TEXT_WIDTH,TEXT_HEIGHT,"�𰸴���");
					}
				}
			}
		}
	}
	return 0;
}
void GameMenu::set(){
	//�ж�sound���ж����ֲ���״̬����ʾ��ӦͼƬ
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
					//�����ڲ���ʱ����ͣ����
					mciSendString("stop bkmusic",NULL,0,NULL);
					putimage(0,0,&this->setImage1);
					sound = false;
				}else {
					//û�в���ʱ������
					mciSendString("play bkmusic",NULL,0,NULL);
					putimage(0,0,&this->setImage);
					sound = true;
				}
			}
		}
	}
}

void GameMenu::rankList(){//ֻ��ʾǰ11��
	putimage(0,0,&this->rankListImage);
	//��ȡ�ļ�����
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
	

	//�Է�����������
	for(int j = 0;j < i;++j){
		int temp = accounts[j].score;
		for(int k = j+1;k < i;++k){
			if(temp < accounts[k].score) temp = accounts[k].score;
		}
		accounts[j].score = temp;
	}

	stringstream stream;

	//��ʾ����
	for(int j = 0;j < i;++j){
		cout<<accounts[j].name<<endl;
		stream<<j+1<<"��"<<accounts[j].name<<"     score:"<<accounts[j].score;
		text->textBox(110,30+j*60,TEXT_WIDTH,TEXT_HEIGHT,stream.str());
		stream.str("");
	}
	while(true){
		if((this->catchMouse(mousePoint) && mousePoint.x<=110 && mousePoint.y <= 50)) return;
		Sleep(5);
	}
	
}

void GameMenu::explain(){
	//��ʾ˵��
	putimage(0,0,&this->explainImage);
	while(true){
		if((this->catchMouse(mousePoint) && mousePoint.x<=80 && mousePoint.y <= 50)) return;
		Sleep(5);
	}
}

void GameMenu::clear(){
	//���������������
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
	//���ڻ�ȡ������Ϣ
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

