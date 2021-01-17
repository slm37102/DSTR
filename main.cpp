#include<iostream>
#include <chrono>
#include <thread>
using namespace std;

class Playlist;
class PlaylistSong;

class PlaylistName{
    public:
        Playlist* playlist;
        PlaylistSong* songLocation;
        PlaylistName* next;
};

class SongCollection{
    string title, singer, duration; 
    public:
        SongCollection* next;
        PlaylistName* playlistName;
        SongCollection(){}
        SongCollection(string title, string singer, string duration) {
            this->title = title;
            this->singer = singer;
            this->duration = duration;
        }
        string getTitle(){
            return title;
        }
        string getSinger(){
            return singer;
        }
        string getDuration(){
            return duration;
        }
};

class PlaylistSong{
    public:
        SongCollection* song;
        PlaylistSong* prev;
        PlaylistSong* next;
        PlaylistSong(){}
        PlaylistSong(SongCollection* song){
            this->song = song;
        }
};

class Playlist{
    string playlistName;
    public:
        Playlist* next;
        PlaylistSong* songList;
        Playlist(){}
        Playlist(string playlistName){
            this->playlistName = playlistName;
        }
        string getPlaylistName(){
            return playlistName;
        }
};

SongCollection* song = NULL;
Playlist* playlist = NULL;

void addSong(SongCollection** head_ref, string title, string singer, string duration) {
    SongCollection* newNode = new SongCollection(title, singer, duration);
    newNode->next = NULL;
    if (*head_ref == NULL){
        *head_ref = newNode;
        return;
    }
    SongCollection* last = *head_ref;
    while(last->next != NULL){
        if (last->getTitle() == title && last->getSinger() == singer)
        {
            cout << "Song with this singer exist.";
            return;
        }
        last = last->next;
    }
    last->next = newNode;
}

void removeSong(SongCollection** head_ref, int index){

}

void displaySongCollection(SongCollection* last){
    if(last == NULL){
        cout << "The collection is empty!";
        return;
    }
    int num = 1;
    while(last != NULL){
        cout << endl << num << ". " << last->getTitle() << " - " << last->getSinger() << " Duration: " << last->getDuration();
        last = last->next;
        num++;
    }
} 

void playlistSearch(SongCollection* song){
    PlaylistName* playlistName = song->playlistName;
    string title = song->getTitle();
    int num=1;
    if (playlistName == NULL)
    {
        cout << "The song (" << title << ") is not found in any playlists!";
        return;   
    }
    cout << title << " is in playlists: ";
    while(playlistName != NULL){
        cout << num << ". " << playlistName->playlist->getPlaylistName() << endl; 
        playlistName = playlistName->next;
    }
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
        if (last->getPlaylistName() == name)
        {
            cout << "Playlist exist.";
            return;
        }
        last = last->next;
    }
    last->next = newNode;
}

void displayPlaylistSong(PlaylistSong* last){
    // if no song inside
    // if(last == NULL){
    //     cout << "No song";
    //     return;
    // }
    int num = 1;
    while(last != NULL){
        cout << endl << num << ". " << last->song->getTitle() << " - " << last->song->getSinger() << " " << endl;
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
        PlaylistSong* playlistSong = last->songList;
        for(int i=0; i < 3 && playlistSong != NULL; i++){
            cout << playlistSong->song->getTitle() << " ";
            playlistSong = playlistSong->next;
        }
        last = last->next;
        num++;
    }
} 

void collectionMenu(){
    int option, userSong;
    string singer, title, duration;
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
                cout << "Title: ";
                cin >> title;
                cout << "Singer: ";
                cin >> singer;
                cout << "Duration (mm:ss): ";
                cin >> duration;
                addSong(&song ,title, singer, duration);
                break;
            }
            case 2:
            {
                // display song --not finished (need loop through songs)
                displaySongCollection(song);
                break;
            }
            case 3:
            {
                //delete music --not finished (find userSong and delete it)
                displaySongCollection(song);
                cin >> userSong;
                // loop to the selected song
                SongCollection *prevSong = song, *selectedSong;
                if (song == NULL)
                {
                    cout << "no song";
                }
                else if (song->next == NULL)
                {
                    selectedSong = song;
                    song = NULL;
                } 
                else
                {
                    for (int i = 0; i < userSong - 2; i++)
                    {
                        prevSong = prevSong->next;
                    }
                    selectedSong = prevSong->next;
                    prevSong->next = selectedSong->next;
                }

                // delete song in the playlist
                PlaylistName* selectedPlaylist = selectedSong->playlistName;
                while (selectedPlaylist != NULL) // in every playlist that have the song
                {
                    //loop to the song location in the playlist
                    PlaylistSong* selectedPlaylistSong = selectedPlaylist->songLocation; 
                    if (selectedPlaylistSong->song == selectedSong) // if the head is the song
                    {
                        selectedPlaylist->playlist->songList = selectedPlaylistSong->next; // head set to next
                    }
                    // else // the head is not the song 
                    // {
                    //     // loop till the song in playlist
                    //     while(selectedPlaylistSong != NULL){ 
                    //         if (selectedPlaylistSong->song == selectedSong){
                    //             break;
                    //         }
                    //         selectedPlaylistSong = selectedPlaylistSong->next;
                    //     }
                    // }
                    if (selectedPlaylistSong->prev != NULL){
                        selectedPlaylistSong->prev->next = selectedPlaylistSong->next;
                    }
                    if (selectedPlaylistSong->next != NULL){
                        selectedPlaylistSong->next->prev = selectedPlaylistSong->prev;
                    }

                    delete selectedPlaylistSong;
                    selectedPlaylist = selectedPlaylist->next;
                }
                // delete the songs
                delete selectedSong;

                break;
            }
            case 4:
            {
                //Playlist search --not finished (find userSong and display playlist it)

                // display all the song in song collection
                displaySongCollection(song);
                cin >> userSong;
                // loop to the selected song
                SongCollection *selectedSong = song;
                for (int i = 0; i < userSong; i++)
                {
                    selectedSong = selectedSong->next;
                }
                // display the playlist of the song 
                playlistSearch(selectedSong);
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

void playlistMenu(){
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
                // View playlist --finished (?)

                // display all playlist
                // -- loop through all playlist
                // -- get playlist name, 3 songs
                displayPlaylist(playlist);
                break;
            }
            case 3:
            {
                // Add songs --finished (doubly, add to song collection) change to display able to add song?

                // display all playlist
                displayPlaylist(playlist);
                cin >> userPlaylist;

                // display all/avaliable songs in collection
                displaySongCollection(song);
                cin >> userSong;
                // loop to user selected playlist
                Playlist* selectedPlaylist = playlist;
                for (int i = 0; i < userPlaylist - 1; i++)
                {
                    selectedPlaylist = selectedPlaylist->next;
                }
                // loop to user selected song
                SongCollection* selectedSong = song;
                for (int i = 0; i < userSong - 1; i++)
                {
                    selectedSong = selectedSong->next;
                }
                // if the playlist is empty
                if (selectedPlaylist->songList == NULL){
                    selectedPlaylist->songList = new PlaylistSong(selectedSong);
                    break;
                }
                // loop to the last song and find if have the same song
                bool same = false;
                PlaylistSong *playlistSong = selectedPlaylist->songList, *newSong = new PlaylistSong(selectedSong);
                while (playlistSong != NULL)
                {
                    // if any duplicate song
                    if (playlistSong->song == selectedSong) {
                        cout << "The playlist has this song";
                        same = true;
                        break;
                    }
                    playlistSong = playlistSong->next;
                }
                // append user selected song
                if (!same)
                    playlistSong = newSong;
                break;
            }
            case 4:
            {
                // View songs -- finished (maybe?)

                // display all playlist
                displayPlaylist(playlist);
                cin >> userPlaylist;
                // show all song in playlist
                Playlist* selectedPlaylist = playlist;
                for (int i = 0; i < userPlaylist - 1; i++)
                {
                    selectedPlaylist = selectedPlaylist->next;
                }
                cout << selectedPlaylist->getPlaylistName() << ":";
                displayPlaylistSong(selectedPlaylist->songList);
                break;
            }
            case 5:
            {
                // Remove songs --not finished (if no song, doubly, delete from song collection)
                
                // display all playlist
                displayPlaylist(playlist);
                cin >> userPlaylist;
                // loop through playlist
                Playlist* selectedPlaylist = playlist;
                for (int i = 0; i < userPlaylist - 1; i++)
                {
                    selectedPlaylist = selectedPlaylist->next;
                }
                // display songs in playlist
                displayPlaylistSong(selectedPlaylist->songList);
                cin >> userSong;
                // loop through song
                PlaylistSong* selectedSong, *prevSong = selectedPlaylist->songList;

                if (prevSong->next == NULL){
                    playlist = NULL;
                } else {
                    for (int i = 0; i < userSong - 2; i++)
                    {
                        prevSong = prevSong->next;
                    }
                    selectedSong = prevSong->next;
                    prevSong->next = selectedSong->next;
                }
                // delete song
                delete selectedSong;
                break;
            }
            case 6:
            {
                // Playlist navigation --not finished ?????

                // show user all the playlist
                displayPlaylist(playlist);                
                cin >> userPlaylist;
                // loop through the selected playlist
                Playlist* selectedPlaylist= playlist;
                for (int i = 0; i < userPlaylist; i++)
                {
                    selectedPlaylist = selectedPlaylist->next;   
                }
                // Play songs from start 
                PlaylistSong* selectedSong = selectedPlaylist->songList;
                int songOption, countdown = 0;
                do{
                    songOption = 0;
                    string title = selectedSong->song->getTitle();
                    string singer = selectedSong->song->getSinger();
                    string duration = selectedSong->song->getDuration();
                    int m, s;
                    sscanf(duration.c_str(), "%d:%d", &m, &s);
                    s = s + m * 60;
                    cout << "1. Pause";
                    cout << "2. Stop";
                    cout << "3. Next Song";
                    cout << "4. Previous song";
                    // display countdown
                    cout << "Now playing: " << title << " - "<< singer <<endl;
                    for (countdown; countdown < s; countdown++)
                    {
                        cout << "\rDuration: " << countdown << " / " << duration;
                        // sleep for 1 sec
                        std::this_thread::sleep_for(chrono::seconds(1));
                    }

                    switch (songOption)
                    {
                        // pause
                        case 1:
                            break;
                        // stop
                        case 2:
                            break;
                        // next song
                        case 3:
                            selectedSong = selectedSong->next;                        
                            countdown = 0;
                            break;
                        // previous song
                        case 4:
                            break;
                        default:
                            selectedSong = selectedSong->next;
                            countdown = 0;
                            break;
                    }

                }while (selectedSong != NULL && songOption == 2);
                break;
            }
            case 7:
            {
                // Delete playlist --not finished (error when delete the last node)

                // display all playlist
                displayPlaylist(playlist);                
                cin >> userPlaylist;
                if (playlist == NULL && playlist->next == NULL){
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
                    if (deletePlaylist->songList != NULL) {
                        PlaylistSong* deleteSong = deletePlaylist->songList, *temp;
                        while(deleteSong != NULL){
                            temp = deleteSong;
                            delete temp;
                            deleteSong = deleteSong->next;
                        }
                    }
                    
                    /*
                    Try: (Line 510 - 514)
                    PlaylistSong* deleteSong = deletePlaylist->songList, *nextSong;
                    while(deleteSong != NULL){
                    nextSong = deleteSong->next;
                    delete deleteSong;
                    deleteSong = nextSong;
                    }
                    deleteSong = NULL;
                    */
                    
                    // delete playlist
                    delete deletePlaylist;
                    /* Add: (Line 531)
                    deletePlaylist = NULL;
                    */
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
                collectionMenu();
                break;
            case 2:
                //to playlist 
                playlistMenu();
                break;            
            default:
                cout << "wrong input"<< endl << endl << endl;
                // system("pause");
                break;
        }
    } while(option != 0);
    return 0;
}
