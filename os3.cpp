#include <iostream>
#include <string>
#include <math.h>
using namespace std;

char *decToBin(int num,int bits){
    //实现十进制到二进制的转换
    char *arr;
    char temp;
    int n=0;
    int _bits=bits;
    arr=(char *)malloc(sizeof(char)*4);
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
int BinToInt(string num,int bits){
    //实现二进制到十进制的转换
    int _bits=bits;
    int number=0;
    while (_bits>0) {
        if (num[_bits-1]=='1') {
            number+=pow(2,bits-_bits);
        }
        _bits--;
    }
    return number;
}


class diskAllocation{
private:
    //用来代表位示图的bool数组
    bool diskSignP[8][2][4];
public:
    diskAllocation(){
    //构造函数
        for (int i=0; i<8; i++) {
            for (int j=0; j<2; j++) {
                for (int k=0; k<4; k++) {
                    diskSignP[i][j][k]=0;
                }
            }
        }
    }
    bool askForAllocation();//申请
    bool askForDelete(string addr);//删除
    void askForPlot();//展示函数
};

void diskAllocation::askForPlot(){
    //展示硬盘占用情况
    cout<<"=====================================================\n";
    for (int i=0; i<8; i++) {
        cout<<"No."<<i<<" CYL (column:Side | row:Record)"<<"\n";
        for (int j=0; j<2; j++) {
            for (int k=0; k<4; k++) {
                cout<<diskSignP[i][j][k];
            }
            cout<<"\n";
        }
    }
    cout<<"=====================================================\n";
}
bool diskAllocation::askForAllocation(){
    //申请内存分配
    for (int i=0; i<8; i++) {
        for (int j=0; j<2; j++) {
            for (int k=0; k<4; k++) {
                if(diskSignP[i][j][k]==0){
                    diskSignP[i][j][k]=1;
                    cout<<"=====================================================\n";
                    cout<<"CYL num："<<i<<"\n";
                    cout<<"Side num："<<j<<"\n";
                    cout<<"Record num："<<k<<"\n";
                    //说明分配的硬盘资源的地址
                    cout<<"The address is "<<decToBin(i,3)<<decToBin(j,1)<<decToBin(k,2)<<"\n";
                    return 1;
                }
            }
        }
    }
    cout<<"No enough space\n";
    return 0;
}

bool diskAllocation::askForDelete(string addr){
    //申请删除
    string CYL,Side,Record;
    int CylNum,SideNum,RecordNum;
    //把用户输入的二进制地址转换为十进制，然后进行删除
    CYL.assign(addr,0,3);
    Side.assign(addr,3,1);
    Record.assign(addr,4,2);
    CylNum=BinToInt(CYL,3);
    SideNum=BinToInt(Side,1);
    RecordNum=BinToInt(Record,2);
    if ((CylNum<8)&&(CylNum>=0)&&(SideNum<2)&&(SideNum>=0)&&(RecordNum<4)&&(RecordNum>=0)) {
        cout<<"=====================================================\n";
        cout<<"CYL num："<<CylNum<<"\n";
        cout<<"Side num："<<SideNum<<"\n";
        cout<<"Record num："<<RecordNum<<"\n";
        if (diskSignP[CylNum][SideNum][RecordNum]==1) {
            diskSignP[CylNum][SideNum][RecordNum]=0;
            cout<<"Delete successfully\n";
        }else{
            cout<<"This place have not been occupied\n";
        }
    }else{
        cout<<"Invalid number,please try again\n";
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    //调用函数
    diskAllocation da;
    bool choice;
    string addressInsert;
    cout<<"=======Welcome to disk place allocation system=======\n";
    while (true) {
        cout<<"Select your choice(1, allocate|0, delete)\n";
        cin>>choice;
        if (choice) {
            da.askForAllocation();
            da.askForPlot();
        }else{
            cout<<"Please insert the address\n";
            cin>>addressInsert;
            da.askForDelete(addressInsert);
            da.askForPlot();
        }
    }
    return 0;
}
