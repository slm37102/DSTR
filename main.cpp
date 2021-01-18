#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

class PlaylistName;
class SongCollection;
class PlaylistSong;
class Playlist;

void addSong(SongCollection** head_ref, string title, string singer, string duration);
void addPlaylistName(PlaylistName** head_ref, Playlist* selectedPlaylist, PlaylistSong* newSong);
void addPlaylist(Playlist** head_ref, string name);
void addPlaylistSong(Playlist** head_ref, SongCollection* selectedSong);
void displaySongCollection(SongCollection* last);
void displayPlaylistSong(PlaylistSong* last);
void displayPlaylist(Playlist* last);
void deleteSong(SongCollection** head_ref, int userSong);
void deletePlaylistName(PlaylistName** head_ref, Playlist* selectedPlaylist);
void deletePlaylist(Playlist** head_ref, int userPlaylist);
void deletePlaylistSong(PlaylistSong** head_ref, SongCollection* selectedSong);
void playlistSearch(SongCollection* head, int userSong);

SongCollection* song = NULL;
Playlist* playlist = NULL;

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

void addPlaylistName(PlaylistName** head_ref, Playlist* selectedPlaylist, PlaylistSong* newSong){
    PlaylistName* selectedPlaylistName = *head_ref;
    PlaylistName* newPlaylistName = new PlaylistName;
    newPlaylistName->next = NULL;
    newPlaylistName->playlist = selectedPlaylist; //playlist location
    newPlaylistName->songLocation = newSong; //playlist song location

    if (selectedPlaylistName == NULL){
        *head_ref = newPlaylistName;
        (*head_ref)->length = 1;
        return;
    }
    while (selectedPlaylistName->next != NULL)
    {
        selectedPlaylistName = selectedPlaylistName->next;
    }
    selectedPlaylistName->next = newPlaylistName;
    (*head_ref)->length++;
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

void addPlaylistSong(Playlist** head_ref, SongCollection* selectedSong){
    Playlist* selectedPlaylist = *head_ref;
    PlaylistSong* selectedPlaylistSong = selectedPlaylist->songList;
    PlaylistSong* newSong = new PlaylistSong(selectedSong);
    newSong->next = NULL;
    // if the playlist is empty
    if (selectedPlaylistSong == NULL){
        // add song to playlist
        newSong->length = 1;
        newSong->prev = NULL;
        selectedPlaylist->songList = newSong;
    } else {
        // loop to the last song and find if have the same song
        while (selectedPlaylistSong != NULL) {
            // if any duplicate song
            if (selectedPlaylistSong->song == selectedSong) {
                cout << "The playlist has this song";
                return;
            }
            selectedPlaylistSong = selectedPlaylistSong->next;
        }
        // append user selected song
        newSong->prev = selectedPlaylistSong;
        selectedPlaylistSong->next = newSong;
    }
    // add playlist name to song collection
    addPlaylistName(&(selectedSong->playlistName), selectedPlaylist, newSong);
}

void displaySongCollection(SongCollection* last){ //done
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

void displayPlaylistSong(PlaylistSong* last){ //done
    // if no song inside
    if(last == NULL){
        cout << "The Playlist is empty!";
        return;
    }
    // display
    int num = 1;
    while(last != NULL){
        cout << endl << num << ". " << last->song->getTitle() << " - " << last->song->getSinger() << "Duration: " << last->song->getDuration();
        last = last->next;
        num++;
    }
    cout << endl;
}

void displayPlaylist(Playlist* last){ //done
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

void deleteSong(SongCollection** head_ref, int userSong){ //done
    (*head_ref)->length--;
     // loop to the selected song
    SongCollection *prevSong, *selectedSong = *head_ref;
    if (userSong == 1) // if one song in collection
    {
        *head_ref = selectedSong->next;
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
    // delete song in the PlaylistSong
    PlaylistName* selectedPlaylistName = selectedSong->playlistName, *temp;
    while (selectedPlaylistName != NULL) // in every playlist that have the song
    {
        deletePlaylistSong(&(selectedPlaylistName->songLocation), selectedSong);
        temp = selectedPlaylistName->next;
        delete selectedPlaylistName;
        selectedPlaylistName = temp;
    }
    // delete the songs
    delete selectedSong;
}

void deletePlaylistName(PlaylistName** head_ref, Playlist* selectedPlaylist){ //done
    (*head_ref)->length--;
    // delete the playlist name in the collection
    (*head_ref)->length--;
    PlaylistName* deletePlaylistName = *head_ref, *prevPlaylistName;
    // find the playlist that needed to delete
    if (deletePlaylistName->playlist == selectedPlaylist) {
        *head_ref = deletePlaylistName->next;
        delete deletePlaylistName;
        return;
    }
    while (deletePlaylistName != NULL){
        if (deletePlaylistName->playlist == selectedPlaylist) {
            prevPlaylistName->next = deletePlaylistName->next;
            delete deletePlaylistName;
            return;
        } 
        prevPlaylistName = deletePlaylistName;
        deletePlaylistName = deletePlaylistName->next;
    }
}

void deletePlaylist(Playlist** head_ref, int userPlaylist){ //done
    (*head_ref)->length--;
    Playlist* prevNode, *selectedPlaylist = *head_ref;
    if (userPlaylist == 1) 
    { 
        *head_ref = selectedPlaylist->next;
    } 
    else 
    {
        // loop through playlist
        for (int i = 0; i < userPlaylist - 1; i++) 
        {
            prevNode = selectedPlaylist;
            selectedPlaylist = selectedPlaylist->next; // take the node needed to delete
        }
        // link previous to next
        prevNode->next = selectedPlaylist->next;
        // delete songs
    }
   // delete all the songs in the playlist
    PlaylistSong* deleteSong = selectedPlaylist->songList, *temp;
    while(deleteSong != NULL)
    {
        deletePlaylistName(&(deleteSong->song->playlistName), selectedPlaylist);
        temp = deleteSong->next;
        delete deleteSong;
        deleteSong = temp;
    }
    delete selectedPlaylist;
}

void deletePlaylistSong(PlaylistSong** head_ref, SongCollection* selectedSong){ //done
    (*head_ref)->length--;
    PlaylistSong* selectedPlaylistSong = *head_ref;
    if (selectedPlaylistSong->song == selectedSong) { // if the head is the song
        *head_ref = selectedPlaylistSong->next; // head set to next
    }
    if (selectedPlaylistSong->prev != NULL) { //prev got node
        selectedPlaylistSong->prev->next = selectedPlaylistSong->next; // prev's next to next
    }
    if (selectedPlaylistSong->next != NULL) { //next got node
        selectedPlaylistSong->next->prev = selectedPlaylistSong->prev; // next's prev to prev
    }
    (*head_ref)->length--;
    delete selectedPlaylistSong;
}

void playlistSearch(SongCollection* head, int userSong){
    // loop to the selected song
    for (int i = 0; i < userSong - 1; i++)
    {
        head = head->next;
    }
    PlaylistName* playlistName = head->playlistName;
    string title = head->getTitle();
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
            case 0: // back
                break;
            case 1: //Add song
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
            case 2:// display song            
            {
                displaySongCollection(song);
                break;
            }
            case 3: //delete music
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
                deleteSong(&song, userSong);
                break;
            }
            case 4: //Playlist search
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
                // display the playlist of the song 
                playlistSearch(song, userSong);
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
                // add song to playlist
                addPlaylistSong(&selectedPlaylist, selectedSong);
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
                deletePlaylist(&playlist, userPlaylist);
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
