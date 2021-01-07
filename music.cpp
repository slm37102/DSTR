#include<iostream>
using namespace std;

class Music{
    string title, singer;
    int duration;
    public:
        void AddSong(string t, string s, int d){
            title = t;
            singer = s;
            duration = d;
        }
};