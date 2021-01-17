#include<iostream>
#include <chrono>
#include <thread>
using namespace std;

class Playlist;
class PlaylistSong;

class PlaylistName{
    public:
        int length=0;
        Playlist* playlist;
        PlaylistSong* songLocation; // to store the song location in the playlist
        PlaylistName* next;
};

class SongCollection{
    string title, singer, duration; 
    public:
        int length=0;
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
        int length=0;
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
        int length=0;
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
        (*head_ref)->length = 1;
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
    (*head_ref)->length++;
}

void displaySongCollection(SongCollection* last){
    // if no song inside
    if(last == NULL){
        cout << "The collection is empty!";
        return;
    }
    // display
    int num = 1;
    while(last != NULL){
        cout << endl << num << ". " << last->getTitle() << " - " << last->getSinger() << " Duration: " << last->getDuration();
        last = last->next;
        num++;
    }
    cout << endl;
}

void removeSong(SongCollection** head_ref, int index){

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
    num++;
}

void addPlaylist(Playlist** head_ref, string name) {
    Playlist* newNode = new Playlist(name);
    newNode->next = NULL;
    if (*head_ref == NULL)
    {
        *head_ref = newNode;
        (*head_ref)->length = 1;
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
    (*head_ref)->length++;
}

void displayPlaylistSong(PlaylistSong* last){
    // if no song inside
    if(last == NULL){
        cout << "The Playlist is empty!";
        return;
    }
    // display
    int num = 1;
    while(last != NULL){
        cout << endl << num << ". " << last->song->getTitle() << " - " << last->song->getSinger() << " ";
        last = last->next;
        num++;
    }
    cout << endl;
}

void displayPlaylist(Playlist* last){
    // if no song inside
    if(last == NULL){
        cout << "There is no playlist!";
        return;
    }
    int num = 1;
    while(last != NULL){
        cout << endl << num << ". " << last->getPlaylistName() << ":";
        PlaylistSong* playlistSong = last->songList;
        for(int i=0; i < 3 && playlistSong != NULL; i++){
            cout << " " << playlistSong->song->getTitle();
            playlistSong = playlistSong->next;
        }
        last = last->next;
        num++;
    }
    cout << endl;
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
            case 0: // back
                break;
            case 1: //Add song --finished (?)
            {
                cout << "Title: ";
                cin >> title;
                cout << "Singer: ";
                cin >> singer;
                cout << "Duration (mm:ss): ";
                cin >> duration;
                addSong(&song ,title, singer, duration);
                break;
            }
            case 2:// display song --not finished (need loop through songs)                
            {
                displaySongCollection(song);
                break;
            }
            case 3: //delete music --not finished (find userSong and delete it)
            {
                // if no song in collection
                if (song == NULL) 
                {
                    cout << "no song";
                    break;
                }
                displaySongCollection(song);
                cin >> userSong;
                if (song->length < userSong){
                    cout << "no such number";
                    break;
                }
                // loop to the selected song
                SongCollection *prevSong, *selectedSong = song;
                if (song->next == NULL) // if one song in collection
                {
                    song = NULL;
                } 
                else // more then one song
                {
                    for (int i = 0; i < userSong - 1; i++)
                    {
                        prevSong = selectedSong;
                        selectedSong = selectedSong->next;
                    }
                    prevSong->next = selectedSong->next;
                }
                // delete song in the playlist
                PlaylistName* selectedPlaylist = selectedSong->playlistName;
                while (selectedPlaylist != NULL) // in every playlist that have the song
                {
                    //loop to the song location in the playlist
                    PlaylistSong* selectedPlaylistSong = selectedPlaylist->songLocation; 
                    if (selectedPlaylistSong->song == selectedSong) { // if the head is the song
                        selectedPlaylist->playlist->songList = selectedPlaylistSong->next; // head set to next
                    }
                    if (selectedPlaylistSong->prev != NULL) { //prev got node
                        selectedPlaylistSong->prev->next = selectedPlaylistSong->next; // prev's next to next
                    }
                    if (selectedPlaylistSong->next != NULL) { //next got node
                        selectedPlaylistSong->next->prev = selectedPlaylistSong->prev; // next's prev to prev
                    }
                    delete selectedPlaylistSong;
                    selectedPlaylist = selectedPlaylist->next;
                }
                // delete the songs
                delete selectedSong;
                break;
            }
            case 4: //Playlist search --not finished (find userSong and display playlist it)
            {
                // if no song in collection
                if (song == NULL) 
                {
                    cout << "no song";
                    break;
                }
                // display all the song in song collection
                displaySongCollection(song);
                cin >> userSong;
                if (song->length < userSong){
                    cout << "no such number";
                    break;
                }
                // loop to the selected song
                SongCollection *selectedSong = song;
                for (int i = 0; i < userSong - 1; i++)
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
            case 0: // back
                break;
            case 1: // Create playlist --finished (?)
            {
                cin >> playlistName;
                addPlaylist(&playlist, playlistName);
                break;
            }
            case 2: // View playlist --finished (?)
            {
                // display all playlist
                // -- loop through all playlist
                // -- get playlist name, 3 songs
                displayPlaylist(playlist);
                break;
            }
            case 3: // Add songs --finished (add to song collection) change to display able to add song?
            {
                // display all playlist
                displayPlaylist(playlist);
                cin >> userPlaylist;
                if (playlist->length < userPlaylist){
                    cout << "no such number";
                    break;
                }
                // display all/avaliable songs in collection
                displaySongCollection(song);
                cin >> userSong;
                if (song->length < userSong){
                    cout << "no such number";
                    break;
                }
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
                PlaylistSong* newSong = new PlaylistSong(selectedSong);
                newSong->next = NULL;
                // if the playlist is empty
                if (selectedPlaylist->songList == NULL){
                    // add song to playlist
                    newSong->prev = NULL;
                    selectedPlaylist->songList = newSong;
                    // add playlist name to song collection
                    PlaylistName* playlistName = new PlaylistName;
                    playlistName->next = NULL;
                    playlistName->length = 1;
                    playlistName->playlist = selectedPlaylist; //playlist location
                    playlistName->songLocation = newSong; //playlist song location
                    selectedSong->playlistName= playlistName;
                    break;
                }
                // loop to the last song and find if have the same song
                PlaylistSong *lastPlaylistSong = selectedPlaylist->songList;
                while (lastPlaylistSong != NULL) {
                    // if any duplicate song
                    if (lastPlaylistSong->song == selectedSong) {
                        cout << "The playlist has this song";
                        break;
                    }
                    lastPlaylistSong = lastPlaylistSong->next;
                }
                // append user selected song
                newSong->prev = lastPlaylistSong;
                lastPlaylistSong->next = newSong;
                // add playlist name to song collection
                PlaylistName* playlistName = new PlaylistName;
                playlistName->next = NULL;
                playlistName->length++; 
                playlistName->playlist = selectedPlaylist; //playlist location
                playlistName->songLocation = newSong; //playlist song location
                selectedSong->playlistName= playlistName;

                break;
            }
            case 4: // View songs -- finished (maybe?)
            {
                // if the playlist is empty
                if (playlist == NULL){  
                    cout << "no playlist";
                    break;
                }
                // display all playlist
                displayPlaylist(playlist);
                cin >> userPlaylist;
                if (playlist->length < userPlaylist){
                    cout << "no such number";
                    break;
                }
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
            case 5: // Remove songs --not finished (if no song, doubly, delete from song collection)
            {
                // display all playlist
                displayPlaylist(playlist);
                cin >> userPlaylist;
                if (playlist->length < userPlaylist){
                    cout << "no such number";
                    break;
                }
                // loop through playlist
                Playlist* selectedPlaylist = playlist;
                for (int i = 0; i < userPlaylist - 1; i++)
                {
                    selectedPlaylist = selectedPlaylist->next;
                }
                // display songs in playlist
                displayPlaylistSong(selectedPlaylist->songList);
                cin >> userSong;
                if (selectedPlaylist->length < userSong){
                    cout << "no such number";
                    break;
                }
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
            case 6: // Playlist navigation --not finished ?????
            {
                // if the playlist is empty
                if (playlist == NULL){  
                    cout << "no playlist";
                    break;
                }
                // show user all the playlist
                displayPlaylist(playlist);                
                cin >> userPlaylist;
                 if (playlist->length < userPlaylist){
                    cout << "no such number";
                    break;
                }
                // loop through the selected playlist
                Playlist* selectedPlaylist= playlist;
                for (int i = 0; i < userPlaylist - 1; i++)
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
            case 7: // Delete playlist --not finished (error when delete the last node)
            {                
                // if the playlist is empty
                if (playlist == NULL){  
                    cout << "no playlist";
                    break;
                }
                // display all playlist
                displayPlaylist(playlist);                
                cin >> userPlaylist;
                 if (playlist->length < userPlaylist){
                    cout << "no such number";
                    break;
                }
                Playlist* prevNode, *deletePlaylist = playlist;
                if (playlist->next == NULL) { //only one playlist
                    playlist = NULL;
                } else {
                    // loop through playlist
                    for (int i = 0; i < userPlaylist - 1; i++) {
                        prevNode = deletePlaylist;
                        deletePlaylist = deletePlaylist->next; // take the node needed to delete
                    }
                    // link previous to next
                    prevNode->next = deletePlaylist->next;
                    // delete songs
                    if (deletePlaylist->songList != NULL) { // if there is song in playlist
                        // delete all the songs in the playlist
                        PlaylistSong* deleteSong = deletePlaylist->songList, *temp;
                        while(deleteSong != NULL){
                            temp = deleteSong->next;
                            // delete the playlist name in the collection
                            PlaylistName* deletePlaylistName = deleteSong->song->playlistName, *prevPlaylistName = NULL;
                            // find the playlist that needed to delete
                            if (deletePlaylistName->playlist == deletePlaylist) {
                                deleteSong->song->playlistName = deletePlaylistName->next;
                                delete deletePlaylistName;
                                deletePlaylistName = NULL;
                            }
                            while (deletePlaylistName != NULL){
                                if (deletePlaylistName->playlist == deletePlaylist) {
                                    prevPlaylistName->next = deletePlaylistName->next;
                                    delete deletePlaylistName;
                                    break;
                                } 
                                prevPlaylistName = deletePlaylistName;
                                deletePlaylistName = deletePlaylistName->next;
                            }
                            // delete song
                            delete deleteSong;
                            deleteSong = temp;
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
