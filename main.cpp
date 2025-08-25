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

ifstream fin("score.txt");

vector<int> scores[NC];
void load(){
    string line="";
    while(getline(fin,line)){
        stringstream sin(line);
        int lineNR; char c;
        sin>>lineNR>>c;
        --lineNR;
        int nr;
        while(sin>>nr)scores[lineNR].push_back(nr);
    }
}
int next_test(){
    struct element{
        int index, last_score;
        size_t score_size;
        element(int _index,int _last_score,size_t _score_size){
            index=_index;
            last_score=_last_score;
            score_size=_score_size;
        }
    };
    vector<element>last_scores;
    for(int i=0;i<NC;++i)last_scores.push_back(element(i+1,scores[i].back(),scores[i].size()));
    sort(last_scores.begin(),last_scores.end(),[](element p1,element p2){
        if(p1.last_score!=p2.last_score)return p1.last_score<p2.last_score;
        if(p1.score_size!=p2.score_size)return p1.score_size<p2.score_size;
        return rand()%14%2==0;
    });
    //cout<<last_scores[0].last_score<<" - ";
    return last_scores[0].index;
}
void update(int testNR,int newscore){
    --testNR;
    scores[testNR].push_back(newscore);
    fin.close();
    ofstream fout("score.txt");
    for(int i=0;i<NC;++i){fout<<i+1<<": ";for(auto it:scores[i])fout<<it<<" ";fout<<"\n";}
}
int main(){
    srand(time(0));
    load();
    //for(int i=0;i<NC;++i){for(auto it:scores[i])cout<<it<<" ";cout<<"\n";}
    cout<<"1 - get next test to redo\n2 - add new score\n3 - kill program\n";
    int select;
    cin>>select;
    if(select==1){
        cout<<"next test: "<<next_test();
    }else if(select==2){
        cout<<"enter test number and score\n";
        int testNR,newscore;
        cin>>testNR>>newscore;
        update(testNR,newscore);
    }
    return 0;
}