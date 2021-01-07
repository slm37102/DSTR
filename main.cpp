#include<iostream>
using namespace std;

class Music{
    string title, singer;
    Node* playlist;
    int duration;
    public:
        // Music(){
        //     duration = NULL;
        // }
        // Music(string t, string s, int d){
        //     title = t;
        //     singer = s;
        //     duration = d;
        // }
        void addSong(string t, string s, int d) {
            title = t;
            singer = s;
            duration = d;
        }
        string getTitle(){
            return title;
        }
        string getSinger(){
            return singer;
        }
        int getDuration(){
            return duration;
        }
        string playlistSearch(){
            return playlist->data;
        };
};

// class Playlist{
//     public:
    
// };

class Node{
    public:
        string data;
        Node* next;
};

void Append(Node** head_ref, string song){
    Node* newNode = new Node();
    newNode->data = song;
    newNode->next = NULL;
    if (*head_ref == NULL)
    {
        *head_ref = newNode;
        return;
    }
    Node* last = *head_ref;
    while(last->next != NULL){
        last = last->next;
    }
    last->next = newNode;
}

void collection(){
    int option;
    Music* music = new Music;
    do{
        cout << "Collection Menu" << endl;
        cin >> option;
        switch(option)
        {
            case 0:
                // exit
                break;
            case 1:
            {
                //add song
                string singer, title;
                int duration;
                cout << "title: ";
                cin >> title;
                cout << "singer: ";
                cin >> singer;
                cout << "duration: ";
                cin >> duration;
                music->addSong(title, singer, duration);
                break;
            }
            case 2:
                // display song
                cout << music->getTitle() << " " << music->getSinger() << " " << music->getDuration();
                break;
            case 3:
                //delete music
                music = new Music;
                break;
            case 4:
            {
                //Playlist search --not finished
                string song;
                cin >> song;
                // music->playlistSearch();  
                break;
            }
            default:
                //wrong output
                cout << "wrong input";
                break;
        }
        cout << endl << endl;
    } while(option != 0);

}

void playlist(){
    int option;
    do{
        cout << "Collection Menu" << endl;
        cin >> option;
        switch(option)
        {
            case 0:
                break;
            case 1:
            {
                // string singer, title;
                // int duration;
                // cout << "title: ";
                // cin >> title;
                // cout << "singer: ";
                // cin >> singer;
                // cout << "duration: ";
                // cin >> duration;
                // music->addSong(title, singer, duration);
                break;
            }
            case 2:
                // cout << music->getTitle() << " " << music->getSinger() << " " << music->getDuration();
                break;
            case 3:
                // delete music;
                break;
            case 4:
            {
                //Playlist search
                string song;
                cin >> song;
                // music->playlistSearch();  
                break;
            }
            default:
                cout << "wrong input";
                break;
        }
        cout << endl << endl;
    } while(option != 0);

}

int main(){
    int option;
    do{    
        cout << "Main Menu" << endl;
        cin >> option;

        switch (option)
        {
            case 0:
                //exit
                break;
            case 1:
                //to music collection
                collection();
                break;
            case 2:
                //to playlist 
                playlist();
                break;            
            default:
                cout << "wrong input"<< endl << endl << endl;
                break;
        }
    } while(option != 0);
    return 0;
}
