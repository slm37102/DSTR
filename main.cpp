#include<iostream>
using namespace std;

class Node{
    public:
        string data;
        Node* next;
};

class SongCollection{
    Node* playlist;
    string title, singer;
    int duration;
    public:
        SongCollection* next;
        SongCollection(){}
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
        string playlistSearch(){
            //loop through the playlist data --not finish (loop through playlist)
            return playlist->data;
        };
};

class Playlist{
    string playlistName;
    public:
        Playlist(){}
        Playlist(string name){
            playlistName = name;
        }
        Playlist* next;
        SongCollection* data = NULL;
        string getPlaylistName(){
            return playlistName;
        }
};


void addSong(SongCollection** head_ref, string t, string s, int d) {
    SongCollection* newNode = new SongCollection(t, s, d);
    newNode->next = NULL;
    if (*head_ref == NULL){
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

void removeSong(SongCollection** head_ref, int index){
    SongCollection* head = *head_ref;
    if (index = 0){
        head_ref = &head->next;
    }
}

void removePlaylist(){

}

void displaySong(SongCollection* last){
    // if no song inside
    // if(last == NULL){
    //     cout << "No song";
    //     return;
    // }
    int num = 1;
    while(last != NULL){
        cout << endl << num << ". " << last->getTitle() << " - " << last->getSinger() << " " << endl;
        last = last->next;
        num++;
    }
} 

void displayPlaylist(Playlist* last){
    // if no playlist inside 
    // if(last == NULL){
    //     cout << "No Playlist";
    //     return;
    // }
    int num = 1;
    while(last != NULL){
        cout << endl << num << ". " << last->getPlaylistName() << ": ";
        SongCollection* songHead = last->data;
        for(int i=0; i < 3 && songHead != NULL; i++){
            cout << songHead->getTitle() << " ";
            songHead = songHead->next;
        }
        last = last->next;
        num++;
    }
} 

void collectionMenu(SongCollection* song){
    int option, userSong, duration;
    string singer, title;
    do{
        // system("cls");
        cout << "Collection Menu" << endl;
        cout << "1. Add songs" << endl;
        cout << "2. Display songs" << endl;
        cout << "3. Delete song" << endl;
        cout << "4. Playlist search" << endl;
        cout << "0. Back" << endl;
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
        cout << "Playlist Menu" << endl;
        cout << "1. Create playlist " << endl;
        cout << "2. View playlist" << endl;
        cout << "3. Add songs" << endl;
        cout << "4. View songs" << endl;
        cout << "5. Remove songs" << endl;
        cout << "6. Playlist navigation" << endl;
        cout << "7. Delete playlist" << endl;
        cout << "0. Back" << endl;
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
                displayPlaylist(playlist);
                break;
            }
            case 3:
            {
                // Add songs --not finished (check if song alr in playlist)

                // display all playlist
                displayPlaylist(playlist);
                cin >> userPlaylist;

                // display all/avaliable songs in collection
                displaySong(song);
                cin >> userSong;
                // loop to user selected playlist
                Playlist* selectedPlaylist = playlist;
                for (int i = 0; i < userPlaylist - 1; i++)
                {
                    selectedPlaylist = selectedPlaylist->next;
                }
                // loop to the last song 
                
                // loop to user selected song
                SongCollection* selectedSong = song;
                for (int i = 0; i < userSong - 1; i++)
                {
                    selectedSong = selectedSong->next;
                }
                // append user selected song
                selectedPlaylist;
                break;
            }
            case 4:
            {
                // View songs --not finished (maybe)

                // display all playlist
                displayPlaylist(playlist);
                cin >> userPlaylist;
                // show all song in playlist
                Playlist* selectedPlaylist = playlist;
                for (int i = 0; i < userPlaylist - 1; i++)
                {
                    selectedPlaylist = selectedPlaylist->next;
                }
                cout << selectedPlaylist->getPlaylistName();
                displaySong(selectedPlaylist->data);
                break;
            }
            case 5:
            {
                // Remove songs --not finished 
                
                // display all playlist
                displayPlaylist(playlist);
                cin >> userPlaylist;
                // display all/avaliable songs in collection
                cin >> userSong;
                // loop through playlist
                // loop through song
                // if song == song delete song
                break;
            }
            case 6:
            {
                // Playlist navigation --not finished ?????

                displayPlaylist(playlist);                
                cin >> userPlaylist;

                break;
            }
            case 7:
            {
                // Delete playlist --not finished (error when delete the last node)

                // display all playlist
                displayPlaylist(playlist);                
                cin >> userPlaylist;
                if (playlist->next == NULL){
                    playlist = NULL;
                } else {
                    Playlist* prevNode = playlist, *deletePlaylist;
                    // loop through playlist
                    for (int i = 0; i < userPlaylist - 2; i++) {
                        prevNode = prevNode->next;
                    }
                    // take remove current node
                    deletePlaylist = prevNode->next;
                    prevNode->next = deletePlaylist->next;
                    // delete songs
                    if (deletePlaylist->data != NULL) {
                        SongCollection* deleteSong = deletePlaylist->data, *temp;
                        while(deleteSong != NULL){
                            temp = deleteSong;
                            delete temp;
                            deleteSong = deleteSong->next;
                        }
                    }
                    // delete playlist
                    deletePlaylist = NULL;
                }
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
    SongCollection* song = NULL;
    Playlist* playlist = NULL;
    do{
        // system("cls");
        cout << "Main Menu" << endl;
        cout << "1. Collection" << endl;
        cout << "2. Playlist" << endl;
        cout << "0. Exit" << endl;
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