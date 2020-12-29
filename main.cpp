#include <iostream>
#include "speechManager.h"
using namespace std;

int main() {

    SpeechManager sm;

//    for (map<int,Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); ++it) {
//        cout<< it->first << "---" <<it->second.m_Name << "---" <<it->second.m_Score[0 ]<<endl;
//    }
    
     int choice = 0;

    while (true){
        sm.ShowMenu();

        cout<<"请输入选择"<<endl;
        cin>>choice;

        switch (choice) {
            case 0:
                sm.ExitSystem();
                break;
            case 1:
                sm.StartSpeech();
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                system("cls");
                break;
        }
    }

    return 0;
}
