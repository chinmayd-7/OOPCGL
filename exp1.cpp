#include<iostream>
#include<graphics.h>
#include<cmath>
void dda(int x1,int y1,int x2,int y2){
    float dx=x2-x1;
    float dy=y2-y1;
    int  steps;
    if(abs(dx)>abs(dy)){
        steps=dx;
    }
    else{
        steps=dy;
    }

    for(int i=1;i<=steps;i++){
        putpixel(round(x1),round(y1),RED);
        x1=x1+(dx/steps);
        y1=y1+(dy/steps);
    }
}
void bresenhams(int xc,int yc,int r){
    int d=3-2*r;
    int x=0;
    int y=r;
    putpixel(xc+x,xc+y,RED);
    while(x<=y){
        if(d<0){
            d=d+(4*x)+6;
            x++;
        }
        else{
            d=d+(4*(x-y))+10;
            x++;
            y--;
        }
        putpixel(xc+x,yc+y,RED);
        putpixel(xc+x,yc-y,RED);
        putpixel(xc-x,yc+y,RED);
        putpixel(xc-x,yc-y,RED);
        putpixel(xc+y,yc+x,RED);
        putpixel(xc+y,yc-x,RED);
        putpixel(xc-y,yc+x,RED);
        putpixel(xc-y,yc-x,RED);
    }
}
int main(){
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    dda(100,100,500,100);
    dda(100,100,100,500);
    dda(500,100,500,500);
    dda(100,500,500,500);
    dda(300,100,100,300);
    dda(300,100,500,300);
    dda(500,300,300,500);
    dda(100,300,300,500);

    bresenhams(300,300,142);
    delay(3000);
    getch();

    closegraph();
    // return 0;
}