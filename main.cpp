#include <iostream>
#include <vector>
using namespace std;
typedef unsigned int NUM;//把无符号数命名为NUM
#define chartItemNum 3//说明表列数
#define MaxNum 1000//定义最大数以供使用

class romTest{
private:
    NUM romSize;//用户给定的内存大小
    NUM chartNum;//用户给定的说明表行数
    NUM (*chartPtr)[chartItemNum]=NULL;//动态数组指针
    NUM chart[MaxNum][chartItemNum];//定义说明表
    vector<pair<int, int>> runtimeTable;//
public:
    romTest(NUM rS,NUM cS);//构造函数
    void run();//运行
    void insert(NUM spaceNum);//插入内存
    void _delete();//删除内存
    void display();//展示
    void checkForRepetition();//检查是否重叠
};

romTest::romTest(NUM rS,NUM cS){
    romSize=rS;chartNum=cS;
    for (int i=0; i<cS; i++) {
        for (int j=0; j<chartItemNum; j++) {
            chart[i][j]=0;
        }
    }
    //令说明表第一项为当前空闲内存
    chart[0][0]=0;chart[0][1]=rS;chart[0][2]=1;
    chartPtr=&chart[0];//动态数组指针指向数组表
    //展示
    display();
}

void romTest::run(){
    //运行函数,提示用户进行选择，并调用相应函数
    bool choice;NUM Num;
    while (true) {
        cout<<"Plz insert your choice,0 means delete,1 means add\n";
        cin>>choice;
        if (choice) {
            cout<<"Plz insert the space num\n";
            cin>>Num;
            insert(Num);
        }else{
            _delete();
        }
    }
}

void romTest::insert(NUM spaceNum){
    //插入说明表项
    bool key=false;
    for (int i=0; i<chartNum; i++) {
    //判断当前说明表项中是否有足够空间
        if (chartPtr[i][1]>spaceNum) {
            //对于有足够空间的说明项来说，判断插入后是否能占用其他表项
            runtimeTable.push_back({chartPtr[i][0],spaceNum});
            chartPtr[i][0]=chartPtr[i][0]+spaceNum;
            chartPtr[i][1]=chartPtr[i][1]-spaceNum;
            key=true;
            break;
        }else if(chartPtr[i][1]==spaceNum){
            //对于有足够空间的说明项来说，判断插入后是否能替代其他表项
            runtimeTable.push_back({chartPtr[i][0],spaceNum});
            chartPtr[i][0]=chartPtr[i][1]=chartPtr[i][2]=0;
            key=true;
            break;
        }
    }
    if (key) {
        cout<<"Insert successfully!\n";
        display();
    }else{
        cout<<"No enough space\n";
        display();
    }
}

void romTest::checkForRepetition(){
    //检查合并过后是否还是会有能结合的点
    for(int i=0;i<chartNum;i++){
        for(int j=i+1;j<chartNum;j++){
            if (((chartPtr[i][0]+chartPtr[i][1])==chartPtr[j][0])) {
                chartPtr[j][0]=chartPtr[i][0];
                chartPtr[j][2]=1;
                chartPtr[j][1]=chartPtr[j][1]+chartPtr[i][1];
                chartPtr[i][0]=chartPtr[i][1]=chartPtr[i][2]=0;
            }else if(((chartPtr[j][0]+chartPtr[j][1])==chartPtr[i][0])){
                chartPtr[j][1]=chartPtr[j][1]+chartPtr[i][1];
                chartPtr[j][2]=1;
                chartPtr[i][0]=chartPtr[i][1]=chartPtr[i][2]=0;
            }
        }
    }
}

void romTest::_delete(){
    //删除说明表项
    if (runtimeTable.size()==0) {
        //当前没有可删除的表项
        cout<<"This is no running process now\n";
    }else{
        //展示当前可删除的表项
        auto it=runtimeTable.begin();int count=1;
        cout<<"Here are the process info\n";
        cout<<"count|start|space\n";
        while (it!=runtimeTable.end()) {
            cout<<count<<"\t"<<it->first<<"\t"<<it->second<<"\n";
            count++;
            it++;
        }
        cout<<"Which one do you wanna delete?\n";
        cin>>count;
        it=runtimeTable.begin()+count-1;
        //检查删除当前表项后是否会能合并其他表项
        bool key=0;
        for (int i=0; i<chartNum; i++) {
            if (chartPtr[i][0]==(it->first+it->second-1+1)) {
                chartPtr[i][0]=it->first;
                chartPtr[i][1]=chartPtr[i][1]+it->second;
                key=1;
                break;
            }else if(chartPtr[i][1]+1==it->first){
                chartPtr[i][1]=chartPtr[i][1]+it->second;
                key=1;
                break;
            }
        }
        //表明不会对其他表项造成影响，新建表项
        if (!key) {
            for (int i=0; i<chartNum; i++) {
                if (chartPtr[i][1]==0) {
                    chartPtr[i][0]=it->first;
                    chartPtr[i][1]=it->first+it->second;
                    chartPtr[i][2]=1;
                    break;
                }
            }
        }
        //检查是否重复
        checkForRepetition();
        runtimeTable.erase(runtimeTable.begin()+count-1);
        display();
    }
}

void romTest::display(){
    //展示函数
    cout<<"====================\n";
    cout<<"start"<<"|"<<"space"<<"|"<<"status"<<"\n";
    for (int i=0; i<chartNum; i++) {
        for (int j=0; j<chartItemNum; j++) {
            if (j!=chartItemNum-1) {
                cout<<chartPtr[i][j];
            }else{
                if (chartPtr[i][2]==1) {
                    cout<<"empty block";
                }else{
                    cout<<"empty chart";
                }
            }
            cout<<"\t";
        }
        cout<<"\n";
    }
    cout<<"====================\n";
}

int main(int argc, const char * argv[]) {
    NUM rS,cS;
    cout<<"=============Welcome to the rom test progress=============\n";
    cout<<"Plz insert the rom size and chart size\n";
    cin>>rS>>cS;
    romTest rom(rS,cS);
    rom.run();
    return 0;
}
