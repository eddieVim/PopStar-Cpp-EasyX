#include "Star.h"
#include<graphics.h>
#include<iostream>


using namespace std;

 LPCTSTR ImageFile[11]={
	"Image\\white.jpg",
	"Image\\bear.jpg",
	"Image\\lion.jpg",
	"Image\\frog.jpg",
	"Image\\panda.jpg",
	"Image\\cola.jpg",
	"Image\\bear1.jpg",
	"Image\\lion1.jpg",
	"Image\\frog1.jpg",
	"Image\\panda1.jpg",
	"Image\\cola1.jpg"
};

Star::Star(){
	//预加载
	for(int i = 0;i < 11;++i){
		loadimage(&starImage[i],ImageFile[i],STAR_X,STAR_Y);
	}
}

Star::~Star(void){
}


void Star::display(int x,int y,int color){//用于加载星星图片及其位图
	if(color==0) return;

	putimage(x,y,&starImage[color+5],NOTSRCERASE);
	putimage(x,y,&starImage[color],SRCINVERT);
}
