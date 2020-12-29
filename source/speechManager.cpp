//
// Created by lee on 2020/12/29.
//
#include "speechManager.h"

//构造
SpeechManager::SpeechManager() {
    //初始化
    this->InitSpeaker();
    this->CreateSpeaker();
}

//析构
SpeechManager::~SpeechManager() {

}

//菜单
void SpeechManager::ShowMenu() {
    cout << "1,开始演讲比赛" << endl;
    cout << "2,查看往届比赛" << endl;
    cout << "3,清空比赛记录" << endl;
    cout << "0,退出系统" << endl;
}

//退出系统
void SpeechManager::ExitSystem() {
    cout << "欢迎下次使用" << endl;
    exit(0);
}

//初始化
void SpeechManager::InitSpeaker() {
    this->v1.clear();
    this->v2.clear();
    this->v3.clear();
    this->m_Speaker.clear();
    this->m_Index = 1;
}

//创建选手
void SpeechManager::CreateSpeaker() {
    string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < nameSeed.size(); ++i) {
        string name = "选手";
        name += nameSeed[i];
        Speaker sp;
        sp.m_Name = name;
        for (int j = 0; j < 2; ++j) {
            sp.m_Score[j] = 0;
        }
        this->v1.push_back(10001 + i);
        this->m_Speaker.insert(make_pair(10001 + i, sp));

    }
}

//抽签
void SpeechManager::SpeechDraw() {
     cout<<"第<"<< this->m_Index<<">轮正在抽签"<<endl;
     cout<<"--------------------------------"<<endl;
     cout<<"抽签顺序如下："<<endl;

     if (this->m_Index == 1 ){
         random_shuffle(v1.begin(),v1.end());
         for (vector<int>::iterator it=v1.begin(); it != v1.end() ; ++it) {
             cout<<*it<<" ";
         }
         cout<<endl;
     } else{
         random_shuffle(v2.begin(),v2.end());
         for (vector<int>::iterator it=v2.begin(); it != v2.end() ; ++it) {
             cout<<*it<<" ";
         }
         cout<<endl;
     }

    cout<<"--------------------------------"<<endl;
    cout<<endl;
}

//比赛
void SpeechManager::SpeechContest() {
    cout<<"第<"<< this->m_Index<<">轮比赛正式开始"<<endl;

    //准备临时容器存放小组成绩
    multimap<double,int,greater<double>> groupScore;
    int num = 0;//用于记录人数


    vector<int> vCurrent;//当前比赛选手容器
    if (this->m_Index == 1){
        vCurrent = v1;
    } else{
        vCurrent = v2;
    }

    for (vector<int>::iterator it = vCurrent.begin(); it!=vCurrent.end() ; ++it) {
        num++;
        //评委打分
        deque<double> d;
        for (int i = 0; i < 10; ++i) {
            double score = (rand()%401+600)/10.f;
            d.push_back(score);
        }
        sort(d.begin(),d.end(),greater<double>());//排序
        d.pop_back();
        d.pop_front();
        double sum = accumulate(d.begin(),d.end(),0.0f);
        double avg = sum/(double )d.size();//求平均分
        this->m_Speaker[*it].m_Score[this->m_Index-1] = avg;

        //将打分放入临时小组容器
        groupScore.insert(make_pair(avg,*it));
        if (num%6 == 0){
            cout<< "第<" << num/6 << ">组小组比赛名次"<<endl;
            for (multimap<double,int,greater<double>>::iterator iterator = groupScore.begin(); iterator != groupScore.end(); ++iterator) {
                cout<< this->m_Speaker[iterator->second].m_Name <<"---"<< this->m_Speaker[iterator->second].m_Score[this->m_Index-1] <<endl;
            }
            //取前3个
            int count = 0;
            for (multimap<double,int,greater<double>>::iterator iterator = groupScore.begin(); iterator != groupScore.end() && count<3; ++iterator,++count) {
                if (this->m_Index == 1){
                   v2.push_back((*iterator).second);
                } else{
                    v3.push_back((*iterator).second);
                }
            }
            groupScore.clear();//收集满6个之后清空
        }
    }
    cout<< "第<" << this->m_Index << ">轮比赛完成"<<endl;
}

//显示晋级
void SpeechManager::ShowWin() {
    cout << "第<" << this->m_Index << ">轮晋级如下"<< endl;
    vector<int> vWin;
    if (this->m_Index == 1){
        vWin = v2;
    } else{
        vWin = v3;
    }
    for (vector<int>::iterator it=vWin.begin();it!=vWin.end(); ++it) {
        cout<< this->m_Speaker[*it].m_Name << " ";
    }
    cout<<endl;
    this->ShowMenu();
}

//保存分数
void SpeechManager::SaveScore() {
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app);//用追加的方式写文件
    for (vector<int>::iterator it=v3.begin();it!=v3.end(); ++it) {
         ofs << *it << "," << this->m_Speaker[*it].m_Score[1]<<",";
    }
    ofs<<endl;
    ofs.close();
    cout<<"文件已保存"<<endl;

}

//开始比赛
void SpeechManager::StartSpeech() {
    //抽签
    this->SpeechDraw();
    //比赛
    this->SpeechContest();
    //显示晋级
    this->ShowWin();
    //抽签
    this->m_Index++;
    this->SpeechDraw();
    //比赛
    this->SpeechContest();
    //显示晋级
    this->ShowWin();
    //保存
    this->SaveScore();
    cout<<"本届比赛完毕"<<endl;
}