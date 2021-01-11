#include<iostream>
using namespace std;

class SongCollection{
    Node* playlist;
    string title, singer;
    int duration;
    public:
        SongCollection* next;
        SongCollection(string t, string s, int d) {
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
        Node* playlistSearch(){
            //loop through the playlist data --not finish (loop through playlist)
            return playlist;
        };
};

class Playlist{
    string playlistName;
    public:
        Playlist(string name){
            playlistName = name;
        }
        Playlist* next;
        SongCollection* data;
        string getPlaylistName(){
            return playlistName;
        }
};

class Node{
    public:
        string data;
        Node* next;
};

void addSong(SongCollection** head_ref, string t, string s, int d) {
    SongCollection* newNode = new SongCollection(t, s, d);
    newNode->next = NULL;
    if (*head_ref == NULL)
    {
        *head_ref = newNode;
        return;
    }
    SongCollection* last = *head_ref;
    while(last->next != NULL){
        last = last->next;
    }
    last->next = newNode;
}

void addPlaylist(Playlist** head_ref, string name) {
    Playlist* newNode = new Playlist(name);
    newNode->next = NULL;
    if (*head_ref == NULL)
    {
        *head_ref = newNode;
        return;
    }
    Playlist* last = *head_ref;
    while(last->next != NULL){
        last = last->next;
    }
    last->next = newNode;
}

// void Append(Node** head_ref, string song){
//     Node* newNode = new Node();
//     newNode->data = song;
//     newNode->next = NULL;
//     if (*head_ref == NULL)
//     {
//         *head_ref = newNode;
//         return;
//     }
//     Node* last = *head_ref;
//     while(last->next != NULL){
//         last = last->next;
//     }
//     last->next = newNode;
// }

void collectionMenu(SongCollection* song){
    int option, userSong, duration;
    string singer, title;
    do{
        // system("cls");
        cout << "Collection Menu" << endl;
        cin >> option;
        switch(option)
        {
            case 0:
                // back
                break;
            case 1:
            {
                //Add song --finished (?)
                cout << "title: ";
                cin >> title;
                cout << "singer: ";
                cin >> singer;
                cout << "duration: ";
                cin >> duration;
                addSong(&song ,title, singer, duration);
                break;
            }
            case 2:
            {
                // display song --not finished (need loop through songs)
                cout << song->getTitle() << " " << song->getSinger() << " " << song->getDuration();
                break;
            }
            case 3:
            {
                //delete music --not finished (find userSong and delete it)
                cin >> userSong;
                break;
            }
            case 4:
            {
                //Playlist search --not finished (find userSong and display playlist it)
                cin >> userSong;
                break;
            }
            default:
                //wrong output
                cout << "wrong input";
                // system("pause");
                break;
        }
        cout << endl << endl;
    } while(option != 0);

}

void playlistMenu(SongCollection* song, Playlist* playlist){
    int option, userPlaylist, userSong;
    string playlistName;
    do{
        // system("cls");
        cout << "Collection Menu" << endl;
        cin >> option;
        switch(option)
        {
            case 0:
                // back
                break;
            case 1:
            {
                // Create playlist --finished (?)

                cin >> playlistName;
                addPlaylist(&playlist, playlistName);
                break;
            }
            case 2:
            {
                // View playlist --not finished 

                // display all playlist
                // -- loop through all playlist 
                // -- get pl name, 3 songs in it 
                break;
            }
            case 3:
            {
                // Add songs --not finished 

                // display all songs in collection
                cin >> userSong;
                // display all songs in playlist
                cin >> userPlaylist;
                // findSong
                // if not in playlist: addSong
                break;
            }
            case 4:
            {
                // View songs --not finished 

                cin >> userPlaylist;

                break;
            }
            case 5:
            {
                // Remove songs --not finished 
                
                break;
            }
            case 6:
            {
                // Playlist navigation --not finished ?????

                break;
            }
            case 7:
            {
                // Delete playlist --not finished 

                
                // display all songs in playlist
                cin >> userPlaylist;
                break;
            }
            default:
                cout << "wrong input";
                // system("pause");
                break;
        }
        cout << endl << endl;
    } while(option != 0);

}

int main(){
    int option;
    SongCollection* song;
    Playlist* playlist;
    do{
        // system("cls");
        cout << "Main Menu" << endl;
        cin >> option;
        switch (option)
        {
            case 0:
                //exit
                break;
            case 1:
                //to music collection
                collectionMenu(song);
                break;
            case 2:
                //to playlist 
                playlistMenu(song, playlist);
                break;            
            default:
                cout << "wrong input"<< endl << endl << endl;
                // system("pause");
                break;
        }
    } while(option != 0);
    return 0;
}
