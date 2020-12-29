//
// Created by lee on 2020/12/29.
//
#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>
#include "speaker.h"

using namespace std;

//演讲管理类
class SpeechManager{
public:
    SpeechManager();
    ~SpeechManager();

    //初始化容器和变量
    void InitSpeaker();

    //创建选手
    void CreateSpeaker();

    //开始比赛
    void StartSpeech();

    //抽签
    void SpeechDraw();

    //比赛
    void SpeechContest();

    //显示晋级
    void ShowWin();

    //保存记录
    void SaveScore();

    //菜单
    void ShowMenu();

    //退出系统
    void ExitSystem();

    //成员属性
    //保存第一轮人员
    vector<int> v1;

    //保存第二轮人员
    vector<int> v2;

    //保存胜利人员
    vector<int> v3;

    //存放编号和选手
    map<int,Speaker> m_Speaker;

    //存放轮数
    int m_Index;

};
