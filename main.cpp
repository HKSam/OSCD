//
//  main.cpp
//  osEx5
//
//  Created by 角马 on 03/11/2017.
//  Copyright © 2017 角马. All rights reserved.
//

#include <iostream>
#include <string>
typedef unsigned int NUM;
#define pageChartNum 5
using namespace std;

class pageChartTran{
    //页表结构
private:
    NUM pageChart[pageChartNum]={2,3,8,5,1};//对应的物理块号
    NUM pageMoveMaxLength = 1023;//页内最大偏移
    NUM pageMaxNum = 5;//最大的页号
    NUM moveAddress;//偏移量
    NUM pageNum;//页号
public:
    void pageTran();//转换函数
};

char *decToBin(int num,int bits){
    //实现十进制到二进制字符串的转换
    char *arr;
    char temp;
    int n=0;
    int _bits=bits;
    arr=(char *)malloc(sizeof(char)*(bits+1));
    while (num>0) {
        arr[n++]=num%2+'0';
        num/=2;
    }
    while (bits>0) {
        if (arr[bits-1]==0) {
            arr[bits-1]='0';
        }
        bits--;
    }
    n=_bits;
    for (int i=0; i<n/2; i++) {
        temp=arr[i];
        arr[i]=arr[n-1-i];
        arr[n-1-i]=temp;
    }
    arr[n]='\0';
    return arr;
}



void pageChartTran::pageTran(){
    cout<<"Plz insert the page num(no more than "<<pageMaxNum<<") and the move(no more than "<<pageMoveMaxLength<<") inside the page\n";
    while (true) {
        cin>>pageNum>>moveAddress;
        if (!(pageNum<=pageMaxNum&&moveAddress<=pageMoveMaxLength)) {
            cout<<"Invalid input, plz insert again\n";
        }else{
            cout<<"Correct input\n";
            break;
        }
    }
    cout<<"=========================================\n";
    cout<<"Your page's logical address is "<<"|"<<decToBin(pageNum-1,3)<<"|"<<decToBin(moveAddress,10)<<"|"<<"\n";
    cout<<"Your page's num corresponds with No."<<pageChart[pageNum-1]<<" block in Memory\n";
    cout<<"Your page's physical address is "<<"|"<<decToBin(pageChart[pageNum-1],3)<<"|"<<decToBin(moveAddress,10)<<"|"<<"\n";
    cout<<"=========================================\n";
}

int main(int argc, const char * argv[]) {
    pageChartTran _page;
    cout<<"=====Welcome to Logic To Physic Address Transformation Application=====\n";
    while (true) {
        _page.pageTran();
    }
}
