#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<string>
#include<sstream>
#include<cstdlib>
#include<time.h>
using namespace std;

#define NC 47

ifstream fin("scor.txt");

vector<int> scors[NC];
void load(){
    string line="";
    while(getline(fin,line)){
        stringstream sin(line);
        int lineNR; char c;
        sin>>lineNR>>c;
        --lineNR;
        int nr;
        while(sin>>nr)scors[lineNR].push_back(nr);
    }
}
int next_test(){
    struct element{
        int index, last_scor;
        size_t scor_size;
        element(int _index,int _last_scor,size_t _scor_size){
            index=_index;
            last_scor=_last_scor;
            scor_size=_scor_size;
        }
    };
    vector<element>last_scors;
    for(int i=0;i<NC;++i)last_scors.push_back(element(i+1,scors[i].back(),scors[i].size()));
    sort(last_scors.begin(),last_scors.end(),[](element p1,element p2){
        if(p1.last_scor!=p2.last_scor)return p1.last_scor<p2.last_scor;
        if(p1.scor_size!=p2.scor_size)return p1.scor_size<p2.scor_size;
        return rand()%14%2==0;
    });
    //cout<<last_scors[0].last_scor<<" - ";
    return last_scors[0].index;
}
void update(int testNR,int newScore){
    --testNR;
    scors[testNR].push_back(newScore);
    fin.close();
    ofstream fout("scor.txt");
    for(int i=0;i<NC;++i){fout<<i+1<<": ";for(auto it:scors[i])fout<<it<<" ";fout<<"\n";}
}
int main(){
    srand(time(0));
    load();
    //for(int i=0;i<NC;++i){for(auto it:scors[i])cout<<it<<" ";cout<<"\n";}
    cout<<"1 - get next test to redo\n2 - add new scor\n3 - kill program\n";
    int select;
    cin>>select;
    if(select==1){
        cout<<"next test: "<<next_test();
    }else if(select==2){
        cout<<"enter test number and scor\n";
        int testNR,newScore;
        cin>>testNR>>newScore;
        update(testNR,newScore);
    }
    return 0;
}