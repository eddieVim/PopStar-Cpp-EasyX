#include <iostream>
#include<graphics.h>
#include <conio.h>
#include< windows.h>
#include"Star.h"
#include"GameLogic.h"
#include"GameMenu.h"


using namespace std;


int main(int argc, char *argv[]){
	Account mainAccount;
	int flag = -1;
	GameMenu *menu = new GameMenu(mainAccount);
	while(flag){
		menu->menu();
		GameLogic *game = new GameLogic(mainAccount);
		while(flag == -1){
			flag = game->mainLogic();
		}
		delete game;
		Sleep(5);
	}
	delete menu;

	return 0;
}
