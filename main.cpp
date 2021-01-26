#include <iostream>
// to implement getline
#include <sstream>
// for padding
#include <iomanip>
// sleep for linux
#include <chrono>
#include <thread>
// // library to get key when looping in Windows
// #include <conio.h>
// // sleep for Windows
// #include <Windows.h>

using namespace std;

class PlaylistName;
class SongCollection;
class PlaylistSong;
class Playlist;

void addSong(SongCollection** head_ref, string title, string singer, string duration);
void addPlaylistName(SongCollection* selectedSong, Playlist* selectedPlaylist, PlaylistSong* newSong);
void addPlaylist(Playlist** head_ref, string name);
void addPlaylistSong(Playlist* selectedPlaylist, SongCollection* selectedSong);
void displaySongCollection(SongCollection* last);
void displayPlaylistSong(PlaylistSong* last);
void displayPlaylist(Playlist* last);
void deleteSong(SongCollection** head_ref, int userSong);
void deletePlaylistName(PlaylistSong* deleteSong, Playlist* selectedPlaylist);
void deletePlaylistName(SongCollection* selectedSong, Playlist* selectedPlaylist);
void deletePlaylist(Playlist** head_ref, int userPlaylist);
void deletePlaylistSong(PlaylistName* selectedPlaylistName, SongCollection* selectedSong); 
void deletePlaylistSong(Playlist* selectedPlaylist, SongCollection* selectedSong);
void playlistSearch(SongCollection* head, int userSong);
PlaylistSong* randomSonglist(PlaylistSong* playlistSong);

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
        cout << "Song \"" << title << "\" Added to Song Collection" << endl;
        return;
    }
    SongCollection* last = *head_ref;
    // first not yet check
    if (last->getTitle() == title && last->getSinger() == singer) {
        cout << "Song \"" << title << "\" By " << singer << " exist." << endl;
        return;
    }
    while(last->next != NULL){
        if (last->getTitle() == title && last->getSinger() == singer) {
            cout << "Song \"" << title << "\" By " << singer << " exist." << endl;
            return;
        }
        last = last->next;
    }
    last->next = newNode;
    (*head_ref)->length++;
    cout << "Song \"" << title << "\" Added to Song Collection" << endl;
}

void addPlaylistName(SongCollection* selectedSong, Playlist* selectedPlaylist, PlaylistSong* newSong){
    PlaylistName* selectedPlaylistName = selectedSong->playlistName;
    PlaylistName* newPlaylistName = new PlaylistName;
    newPlaylistName->next = NULL;
    newPlaylistName->playlist = selectedPlaylist; //playlist location
    newPlaylistName->songLocation = newSong; //playlist song location

    if (selectedPlaylistName == NULL){
        selectedSong->playlistName = newPlaylistName;
        (selectedSong->playlistName)->length = 1;
        return;
    }
    while (selectedPlaylistName->next != NULL)
    {
        selectedPlaylistName = selectedPlaylistName->next;
    }
    selectedPlaylistName->next = newPlaylistName;
    (selectedSong->playlistName)->length++;
}

void addPlaylist(Playlist** head_ref, string name) {
    Playlist* newNode = new Playlist(name);
    newNode->next = NULL;
    if (*head_ref == NULL)
    {
        *head_ref = newNode;
        (*head_ref)->length = 1;
        cout << "Playlist \"" << newNode->getPlaylistName() << "\" created" << endl;
        return;
    }
    Playlist* last = *head_ref;
    while(last->next != NULL){
        if (last->getPlaylistName() == name)
        {
            cout << "Playlist \"" << name << "\" exist." << endl;
            return;
        }
        last = last->next;
    }
    // the last not check
    if (last->getPlaylistName() == name)
    {
        cout << "Playlist \"" << name << "\" exist." << endl;
        return;
    }
    last->next = newNode;
    (*head_ref)->length++;
    cout << "Playlist \"" << newNode->getPlaylistName() << "\" created" << endl;
}

void addPlaylistSong(Playlist* selectedPlaylist, SongCollection* selectedSong){
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
        while (selectedPlaylistSong->next != NULL) {
            // if any duplicate song
            if (selectedPlaylistSong->song == selectedSong) {
                cout << "The Playlist \"" << selectedPlaylist->getPlaylistName() << "\" already has this song inside" << endl;
                return;
            }
            selectedPlaylistSong = selectedPlaylistSong->next;
        }
        // last not check
        if (selectedPlaylistSong->song == selectedSong) {
            cout << "The Playlist \"" << selectedPlaylist->getPlaylistName() << "\" already has this song inside" << endl;
            return;
        }
        // append user selected song
        newSong->prev = selectedPlaylistSong;
        selectedPlaylistSong->next = newSong;
        selectedPlaylist->songList->length++;
    }
    // add playlist name to song collection
    addPlaylistName(selectedSong, selectedPlaylist, newSong);
    cout << "Song \"" << selectedSong->getTitle() << "\" Added to the Playlist \"" << selectedPlaylist->getPlaylistName() << "\"" << endl;
}

void displaySongCollection(SongCollection* last){ 
    // if no song inside
    if(last == NULL){
        cout << "There is no Song in Song Collection. Please create Song in Song Collection" << endl;
        return;
    }
    // display
    int num = 1;
    while(last != NULL){
        cout << num << ". " << last->getTitle() << " by " << last->getSinger() << "   Duration: " << last->getDuration() << endl;
        last = last->next;
        num++;
    }
    cout << endl;    
}

void displayPlaylistSong(PlaylistSong* last){
    int num = 1;
    while(last != NULL){
        cout << num << ". " << last->song->getTitle() << " - " << last->song->getSinger() << " Duration: " << last->song->getDuration() << endl;
        last = last->next;
        num++;
    }
    cout << endl;
}

void displayPlaylist(Playlist* last){ 
    // if user haven't create any playlists
    if(last == NULL){
        cout << "There is no Playlist created, Please Create Playlist First" << endl;
        return;
    }
    int num = 1;
    while(last != NULL){
        cout << num << ". " << last->getPlaylistName() << ":";
        PlaylistSong* playlistSong = last->songList;
        for(int i=0; i < 3 && playlistSong != NULL; i++){
            cout << " " << playlistSong->song->getTitle();
            playlistSong = playlistSong->next;
        }
        cout << endl;
        last = last->next;
        num++;
    }
    cout << endl;
} 

void deleteSong(SongCollection** head_ref, int userSong){ 
     // loop to the selected song
    SongCollection *prevSong = NULL, *selectedSong = *head_ref;
    if (userSong == 1) // if user choose the first song
    {
        *head_ref = selectedSong->next;
        if(*head_ref != NULL) {
            (*head_ref)->length = selectedSong->length;
        }
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
        deletePlaylistSong(selectedPlaylistName, selectedSong);
        temp = selectedPlaylistName->next;
        delete selectedPlaylistName;
        selectedPlaylistName = temp;
    }
    // delete the songs
    if(*head_ref != NULL) {
        (*head_ref)->length--;
    }
    cout << "Song \""<< selectedSong->getTitle() <<"\" in Song Collection deleted" << endl;
    delete selectedSong;
}
//to update song nodes that contain the playlist to be deleted
void deletePlaylistName(PlaylistSong* deleteSong, Playlist* selectedPlaylist){ 
    // head_ref = deleteSong->song->playlistName
    // delete the playlist name in the collection
    PlaylistName* deletePlaylistName = deleteSong->song->playlistName, *prevPlaylistName = NULL;
    // if the head is the playlist
    if (deletePlaylistName->playlist == selectedPlaylist) {
        deleteSong->song->playlistName = deletePlaylistName->next;
        if(deleteSong->song->playlistName != NULL) {        
            (deleteSong->song->playlistName)->length = deletePlaylistName->length;
        }
    } else {
        // find the playlist that needed to delete
        while (deletePlaylistName != NULL){
            if (deletePlaylistName->playlist == selectedPlaylist) {
                prevPlaylistName->next = deletePlaylistName->next;
                break;
            } 
            prevPlaylistName = deletePlaylistName;
            deletePlaylistName = deletePlaylistName->next;
        }
    }
    if(deleteSong->song->playlistName != NULL) {
        (deleteSong->song->playlistName)->length--;
    }
    delete deletePlaylistName;
}
//for delete song in playlist
void deletePlaylistName(SongCollection* selectedSong, Playlist* selectedPlaylist){ 
    // head_ref = selectedSong->playlistName
    // delete the playlist name in the collection
    PlaylistName* deletePlaylistName = selectedSong->playlistName, *prevPlaylistName = NULL;
    // if the head is the playlist
    if (deletePlaylistName->playlist == selectedPlaylist) {
        selectedSong->playlistName = deletePlaylistName->next;
        if(selectedSong->playlistName != NULL) {        
            selectedSong->playlistName->length = deletePlaylistName->length;
        }
    } else {
        // find the playlist that needed to delete
        while (deletePlaylistName != NULL){
            if (deletePlaylistName->playlist == selectedPlaylist) {
                prevPlaylistName->next = deletePlaylistName->next;
                break;
            } 
            prevPlaylistName = deletePlaylistName;
            deletePlaylistName = deletePlaylistName->next;
        }
    }
    if(selectedSong->playlistName != NULL) {
        selectedSong->playlistName->length--;
    }
    delete deletePlaylistName;
}

void deletePlaylist(Playlist** head_ref, int userPlaylist){ 
    Playlist* prevNode = NULL, *selectedPlaylist = *head_ref;
    if (userPlaylist == 1) 
    { 
        *head_ref = selectedPlaylist->next;
        if(*head_ref != NULL) {
            (*head_ref)->length = selectedPlaylist->length;
        }
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
        deletePlaylistName(deleteSong, selectedPlaylist);
        temp = deleteSong->next;
        delete deleteSong;
        deleteSong = temp;
    }
    if(*head_ref != NULL) {
        (*head_ref)->length--;
    }
    cout << "Playlist \""<< selectedPlaylist->getPlaylistName() <<"\" deleted" << endl;
    delete selectedPlaylist;
}
//for delete song in collection
void deletePlaylistSong(PlaylistName* selectedPlaylistName, SongCollection* selectedSong){ 
    // head_ref = selectedPlaylistName->playlist
    PlaylistSong* selectedPlaylistSong = selectedPlaylistName->playlist->songList;
    if (selectedPlaylistSong->song == selectedSong) { // if the head is the song
        selectedPlaylistName->playlist->songList = selectedPlaylistSong->next; // head set to next
        if(selectedPlaylistName->playlist->songList != NULL) {
            selectedPlaylistName->playlist->songList->length = selectedPlaylistSong->length;
        }
    } else {
        while (selectedPlaylistSong->song != selectedSong) {
            selectedPlaylistSong = selectedPlaylistSong->next;
        }
    }
    if (selectedPlaylistSong->prev != NULL) { //prev got node
        selectedPlaylistSong->prev->next = selectedPlaylistSong->next; // prev's next to next
    }
    if (selectedPlaylistSong->next != NULL) { //next got node
        selectedPlaylistSong->next->prev = selectedPlaylistSong->prev; // next's prev to prev
    }
    if(selectedPlaylistName->playlist->songList != NULL) {
        selectedPlaylistName->playlist->songList->length--;
    }
    delete selectedPlaylistSong;
}
//for delete song in playlist
void deletePlaylistSong(Playlist* selectedPlaylist, PlaylistSong* selectedPlaylistSong){ 
    // head_ref = selectedPlaylist->songList
    if (selectedPlaylist->songList->song == selectedPlaylistSong->song) { // if the head is the song
        selectedPlaylist->songList = selectedPlaylistSong->next; // head set to next
        if(selectedPlaylist->songList != NULL) {
            selectedPlaylist->songList->length = selectedPlaylistSong->length;
        }
    }
    // no need to loop because the selected playlist song is already looped before passing
    if (selectedPlaylistSong->prev != NULL) { //prev got node
        selectedPlaylistSong->prev->next = selectedPlaylistSong->next; // prev's next to next
    }
    if (selectedPlaylistSong->next != NULL) { //next got node
        selectedPlaylistSong->next->prev = selectedPlaylistSong->prev; // next's prev to prev
    }
    // head_ref != NULL
    if(selectedPlaylist->songList != NULL) {
        selectedPlaylist->songList->length--;
    }
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
        cout << "Song \"" << title << "\" not found in any playlists!";
        return;   
    }
    cout << title << " is in playlists: " << endl;
    while(playlistName != NULL){
        cout << num << ". " << playlistName->playlist->getPlaylistName() << endl; 
        playlistName = playlistName->next;
        num++;
    }
}

PlaylistSong* randomSonglist(PlaylistSong* playlistSong){
    PlaylistSong* randomHead= new PlaylistSong;
    PlaylistSong* last = randomHead;
    int len = playlistSong->length;
    // clone a playlistSong
    for (int i = 0; i < len; i++)
    {
        last->song = playlistSong->song;
        last->next = new PlaylistSong;
        playlistSong = playlistSong->next;
        // if not last - will not next in last
        if (i != (len - 1))
        {
            last = last->next;
        }        
    }
    PlaylistSong* prevLoop = NULL;
    srand(time(0));
    // loop from len to 1
    for (int i = len; i > 0; i--) {
        PlaylistSong* selectedPlaylistSong = randomHead;
        // loop to the random selected song
        // rand() % i: random number from 0 till (i - 1)
        int randNum = (rand() % i);
        // selected is head
        if (randNum == 0) {
            // remove head node
            randomHead = randomHead->next;
        } else {
            PlaylistSong* prevPlaylistSong = NULL;
            for (int j = 0; j < randNum; j++) {
                prevPlaylistSong = selectedPlaylistSong;
                selectedPlaylistSong = selectedPlaylistSong->next;
            }
            // delete node
            prevPlaylistSong->next = selectedPlaylistSong->next;
        }           
        // set selectedPlaylistSong->prev
        selectedPlaylistSong->prev = prevLoop;
        selectedPlaylistSong->next = NULL;
        prevLoop = selectedPlaylistSong;
        // append head to last->next
        last->next = selectedPlaylistSong;
        last = last->next;
    }
    last->next = NULL;
    randomHead->length = len;
    return randomHead;
}

void collectionMenu(){
    int option, userSong;
    string singer, title, duration;
    do{
        system("cls");
        cout << "===================================" << endl;
        cout << "    Song Collection Menu" << endl;
        cout << "===================================" << endl;
        cout << " 1. Add New Song to Collection" << endl;
        cout << " 2. Display Songs in Collection" << endl;
        cout << " 3. Delete Song in Collection" << endl;
        cout << " 4. Playlist Search" << endl;
        cout << " 0. Back" << endl;
        cout << "-----------------------------------" << endl << endl;
        cout << "Select your Option: ";
        cin >> option;
        switch(option)
        {
            case 0: // back
                break;
            case 1: //Add song
            {
                system("cls");
                cout << "===================================" << endl;
                cout << "    Add Song to Collection" << endl;
                cout << "===================================" << endl << endl;
                cin.ignore();
                cout << "Enter Song Title: ";
                getline(cin, title);
                cout << "Enter Singer of the song: ";
                getline(cin, singer);
                cout << "Enter Duration of the song (mm:ss): ";
                getline(cin, duration);
                int m, s;
                if (sscanf(duration.c_str(), "%d:%d", &m, &s) > 1) {
                    if (s >= 60){
                        cout << "The second in the duration over 60" << endl;
                        break;
                    }
                } else {
                    cout << "Duration format not right" << endl;
                    break;
                }
                addSong(&song ,title, singer, duration);
                break;
            }
            case 2:// display song            
            {
                system("cls");
                cout << "===================================" << endl;
                cout << "    Display Collection" << endl;
                cout << "===================================" << endl << endl;
                displaySongCollection(song);
                break;
            }
            case 3: //delete music
            {
                system("cls");
                cout << "===================================" << endl;
                cout << "    Delete Song in Collection" << endl;
                cout << "===================================" << endl << endl;
                // if no song in collection
                if (song == NULL) 
                {
                    cout << "There is no Song in Song Collection. Please create Song in Song Collection" << endl;
                    break;
                }
                // display all the song in song collection
                displaySongCollection(song);
                cout << "Select a Song: ";
                cin >> userSong;
                if (song->length < userSong){
                    cout << "Number Out of Range" << endl;
                    break;
                }
                deleteSong(&song, userSong);
                break;
            }
            case 4: //Playlist search
            {
                system("cls");
                cout << "===================================" << endl;
                cout << "    Playlist Search" << endl;
                cout << "===================================" << endl << endl;
                // if no song in collection
                if (song == NULL) 
                {
                    cout << "There is no Song in Song Collection. Please create Song in Song Collection" << endl;
                    break;
                }
                // display all the song in song collection
                displaySongCollection(song);
                cout << "Select a Song: ";
                cin >> userSong;
                if (song->length < userSong){
                    cout << "Number Out of Range" << endl;
                    break;
                }
                // display the playlist of the song 
                system("cls");
                cout << "===================================" << endl;
                cout << "    Playlist Search" << endl;
                cout << "===================================" << endl << endl;
                playlistSearch(song, userSong);
                break;
            }
            default:
                //wrong output
                cout << "Invalid Input" << endl;
                break;
        }
        cout << endl;
        system("pause");
    } while(option != 0);
}

void playlistMenu(){
    int option, userPlaylist, userSong;
    string playlistName;
    do{
        system("cls");
        cout << "===================================" << endl;
        cout << "    Playlist Menu" << endl;
        cout << "===================================" << endl;
        cout << " 1. Create a New Playlist" << endl;
        cout << " 2. View Existing Playlist" << endl;
        cout << " 3. Add New Song to Playlist" << endl;
        cout << " 4. View songs in Playlist" << endl;
        cout << " 5. Remove song in the Playlist" << endl;
        cout << " 6. Music Player" << endl;
        cout << " 7. Delete Entire Playlist" << endl;
        cout << " 0. Back" << endl;
        cout << "-----------------------------------" << endl << endl;
        cout << "Select your Option: ";
        cin >> option;
        switch(option)
        {
            case 0: // back
                break;
            case 1: // Create playlist
            {
                system("cls");
                cout << "===================================" << endl;
                cout << "    Create New Playlist" << endl;
                cout << "===================================" << endl << endl;
                cout << "Enter Playlist Name: ";
                cin.ignore();
                getline(cin, playlistName);
                addPlaylist(&playlist, playlistName);
                break;
            }
            case 2: // View playlist
            {
                system("cls");   
                cout << "===================================" << endl;
                cout << "    View Exist Playlist" << endl;
                cout << "===================================" << endl << endl;
                // display all playlist
                // -- loop through all playlist
                // -- get playlist name, 3 songs
                displayPlaylist(playlist);
                break;
            }
            case 3: // Add songs
            {
                system("cls");
                cout << "===================================" << endl;
                cout << "    Add Song to Playlist" << endl;
                cout << "===================================" << endl << endl;
                // display all playlist
                if (playlist == NULL){  
                    cout << "There is no Playlist created, Please Create Playlist First" << endl;
                    break;
                }
                displayPlaylist(playlist);
                cout << "Select a Playlist: ";
                cin >> userPlaylist;
                if (playlist->length < userPlaylist){
                    cout << "Number Out of Range" << endl;
                    break;
                }
                // if no song in collection
                if (song == NULL) 
                {
                    cout << "There is no Song in Song Collection. Please create Song in Song Collection" << endl;
                    break;
                }
                // display all/avaliable songs in collection
                displaySongCollection(song);
                cout << "Select a Song: ";
                cin >> userSong;
                if (song->length < userSong){
                    cout << "Number Out of Range" << endl;
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
                addPlaylistSong(selectedPlaylist, selectedSong);
                break;
            }
            case 4: // View songs
            {
                system("cls");
                cout << "===================================" << endl;
                cout << "    View songs in Playlist" << endl;
                cout << "===================================" << endl << endl;
                // if the playlist is empty
                if (playlist == NULL){  
                    cout << "There is no Playlist created, Please Create Playlist First" << endl;
                    break;
                }
                // display all playlist
                displayPlaylist(playlist);
                cout << "Select a Playlist: ";
                cin >> userPlaylist;
                if (playlist->length < userPlaylist){
                    cout << "Number Out of Range" << endl;
                    break;
                }
                system("cls");
                cout << "===================================" << endl;
                cout << "    View songs in Playlist" << endl;
                cout << "===================================" << endl << endl;
                // show all song in playlist
                Playlist* selectedPlaylist = playlist;
                for (int i = 0; i < userPlaylist - 1; i++)
                {
                    selectedPlaylist = selectedPlaylist->next;
                }
                cout << selectedPlaylist->getPlaylistName() << ":" << endl;
                displayPlaylistSong(selectedPlaylist->songList);
                break;
            }
            case 5: // Remove songs
            {
                system("cls");
                cout << "===================================" << endl;
                cout << "    Remove Song in Playlist" << endl;
                cout << "===================================" << endl << endl;
                // display all playlist
                if (playlist == NULL){  
                    cout << "There is no Playlist created, Please Create Playlist First" << endl;
                    break;
                }
                displayPlaylist(playlist);
                cout << "Select a Playlist: ";
                cin >> userPlaylist;
                if (playlist->length < userPlaylist){
                    cout << "Number Out of Range" << endl;
                    break;
                }
                // loop through playlist
                Playlist* selectedPlaylist = playlist;
                for (int i = 0; i < userPlaylist - 1; i++)
                {
                    selectedPlaylist = selectedPlaylist->next;
                }
                // if no song in collection
                if (selectedPlaylist->songList == NULL) 
                {
                    cout << "There is no Song in Playlist. Please add Song in Playlist" << endl;
                    break;
                }
                // display songs in playlist
                displayPlaylistSong(selectedPlaylist->songList);
                cout << "Select a Song: ";
                cin >> userSong;
                if (selectedPlaylist->songList->length < userSong){
                    cout << "Number Out of Range" << endl;
                    break;
                }
                PlaylistSong* selectedPlaylistSong = selectedPlaylist->songList;
                for (int i = 0; i < userSong - 1; i++)
                {
                    selectedPlaylistSong = selectedPlaylistSong->next;
                }
                // delete song in the playlist
                string songString = selectedPlaylistSong->song->getTitle(), playlistString = selectedPlaylist->getPlaylistName();
                deletePlaylistSong(selectedPlaylist, selectedPlaylistSong);
                // delete playlistName in song collection 
                deletePlaylistName(selectedPlaylistSong, selectedPlaylist);
                cout << "Song \""<< songString <<"\" deleted in Playlist \""<< playlistString <<"\"" << endl;
                break;
            }
            case 6: // Playlist navigation
            {
                // if the playlist is empty
                system("cls");
                cout << "===================================" << endl;
                cout << "    Music Player" << endl;
                cout << "===================================" << endl << endl;
                if (playlist == NULL){  
                    cout << "There is no Playlist created, Please Create Playlist First" << endl;
                    break;
                }
                // show user all the playlist
                displayPlaylist(playlist);
                cout << "Select a Playlist: ";
                cin >> userPlaylist;
                 if (playlist->length < userPlaylist){
                    cout << "Number Out of Range" << endl;
                    break;
                }
                // loop through the selected playlist
                Playlist* selectedPlaylist= playlist;
                for (int i = 0; i < userPlaylist - 1; i++)
                {
                    selectedPlaylist = selectedPlaylist->next;   
                }
                // Play songs from start 
                bool random;
                cout << endl << "Do you want to shuffle your playlist?" << endl;
                cout << " 1. Yes" << endl;
                cout << " 0. No" << endl << endl;
                cout << " Enter an option: " << endl;
                cin >> random;
                PlaylistSong* selectedSong;
                if (random) {
                    selectedSong = randomSonglist(selectedPlaylist->songList);
                } else {
                    selectedSong = selectedPlaylist->songList;
                }                
                int countdown = 0;
                bool play = true, stop = false;
                system("cls");
                cout << "===================================" << endl;
                cout << "    Music Player" << endl;
                cout << "===================================" << endl;
                cout << " Press the following key to perform" << endl; 
                cout << " action." << endl;
                cout << " P: Play/Pause" << endl;
                cout << " N: Next Song" << endl;
                cout << " B: Previous song" << endl;
                cout << " S: Stop and Exit" << endl;
                cout << "-----------------------------------" << endl << endl;
                string title = selectedSong->song->getTitle();
                string singer = selectedSong->song->getSinger();
                string duration = selectedSong->song->getDuration();
                string prevSongName = "-";
                string nextSongName;
                if (selectedSong->next != NULL) {
                    nextSongName = selectedSong->next->song->getTitle();
                }
                else {
                    nextSongName = "-";
                }                
                char chars[] = { '-', '\\', '|', '/', '-' };
                int m, s;
                // duration to seconds
                if (sscanf(duration.c_str(), "%d:%d", &m, &s) > 1){
                    s += m * 60;
                }
                // display countdown
                for (countdown; countdown < s && selectedSong != NULL && !stop; countdown+=int(play))
                {
                    for (int i = 0; i < 10; i++)
                    {
                        // // uncomment Windows
                        // // if key is press
                        // if (_kbhit()) {
                        //     switch (_getch()){
                        //         // play/pause
                        //         case 'p':
                        //         case 'P':
                        //             play = !play;
                        //             break;
                        //         // stop
                        //         case 's':
                        //         case 'S':
                        //             stop = true;
                        //             break;
                        //         // next song
                        //         case 'n':
                        //         case 'N':
                        //             if (selectedSong->next != NULL){
                        //                 prevSongName = title;
                        //                 selectedSong = selectedSong->next;
                        //                 title = selectedSong->song->getTitle();
                        //                 singer = selectedSong->song->getSinger();
                        //                 duration = selectedSong->song->getDuration();
                        //                 if (sscanf(duration.c_str(), "%d:%d", &m, &s) > 1){
                        //                     s += m * 60;
                        //                 }
                        //                 countdown = 0;
                        //                 if (selectedSong->next != NULL) {
                        //                     nextSongName = selectedSong->next->song->getTitle();
                        //                 }
                        //                 else {
                        //                     nextSongName = "-";
                        //                 }     
                        //             }
                        //             break;
                        //         // previous song
                        //         case 'b':
                        //         case 'B':
                        //             if (selectedSong->prev != NULL){
                        //                 nextSongName = title;
                        //                 selectedSong = selectedSong->prev;
                        //                 title = selectedSong->song->getTitle();
                        //                 singer = selectedSong->song->getSinger();
                        //                 duration = selectedSong->song->getDuration();
                        //                 if (sscanf(duration.c_str(), "%d:%d", &m, &s) > 1){
                        //                     s += m * 60;
                        //                 }
                        //                 countdown = 0;
                        //                 if (selectedSong->prev != NULL) {
                        //                     prevSongName = selectedSong->prev->song->getTitle();
                        //                 }
                        //                 else {
                        //                     prevSongName = "-";
                        //                 }  
                        //             }
                        //             break;
                        //     }
                        // }
                        cout << "Now playing: " << title << " by " << singer << " |";
                        if (play) {
                            cout << setfill(' ') << setw(10) << "Playing " << chars[i % sizeof(chars)];
                        }
                        else {
                            cout << setfill(' ') << setw(10) << "Paused " << "-";
                        }
                        cout << " |  Duration: " << countdown / 60 << ":" << setfill('0') << setw(2) << countdown % 60 << "/" << duration;
                        cout << " |  Previous Song: " << prevSongName << " |  Next Song: " << nextSongName << "\r" << flush;
                        // sleep for 1 sec for linux
                        this_thread::sleep_for(chrono::milliseconds(100));
                        // // sleep for Windows
                        // Sleep(100);
                    }
                    // if one song finished
                    if (countdown == s - 1 && selectedSong->next != NULL) {
                        prevSongName = title;
                        selectedSong = selectedSong->next;
                        title = selectedSong->song->getTitle();
                        singer = selectedSong->song->getSinger();
                        duration = selectedSong->song->getDuration();
                        if (sscanf(duration.c_str(), "%d:%d", &m, &s) > 1){
                            s += m * 60;
                        }
                        countdown = 0;
                        if (selectedSong->next != NULL) {
                            nextSongName = selectedSong->next->song->getTitle();
                        }
                        else {
                            nextSongName = "-";
                        }
                    }
                }
                cout << endl << endl << "Song ended" << endl;
                break;
            }
            case 7: // Delete playlist
            {                
                system("cls");
                cout << "===================================" << endl;
                cout << "    Delete Playlist" << endl;
                cout << "===================================" << endl << endl;
                // if the playlist is empty
                if (playlist == NULL){  
                    cout << "There is no Playlist created, Please Create Playlist First" << endl;
                    break;
                }
                // display all playlist
                displayPlaylist(playlist);
                cout << "Select a Playlist: ";              
                cin >> userPlaylist;
                 if (playlist->length < userPlaylist){
                    cout << "Number Out of Range" << endl;
                    break;
                }
                deletePlaylist(&playlist, userPlaylist);
                break;
            }
            default:
                cout << "Invalid Input" << endl;
                break;
        }
        cout << endl;
        system("pause");
    } while(option != 0);
}

int main(){
    int option;
    // test case
    // playlist1: song1, song2, song3
    // playlist2: song1
    // playlist3: 
    addSong(&song, "song1", "singer1", "0:05");
    addSong(&song, "song2", "singer2", "0:10");
    addSong(&song, "song3", "singer3", "0:15");
    addSong(&song, "song4", "singer4", "0:03");
    addSong(&song, "song5", "singer5", "0:03");
    addSong(&song, "song6", "singer6", "0:03");
    addPlaylist(&playlist, "playlist1");
    addPlaylist(&playlist, "playlist2");
    addPlaylist(&playlist, "playlist3");
    addPlaylistSong(playlist, song);
    addPlaylistSong(playlist, song->next);
    addPlaylistSong(playlist, song->next->next);
    addPlaylistSong(playlist, song->next->next->next);
    addPlaylistSong(playlist, song->next->next->next->next);
    addPlaylistSong(playlist, song->next->next->next->next->next);
    addPlaylistSong(playlist->next, song);
    // test end here
    do{
        system("cls");
        cout << "===================================" << endl;
        cout << "    Main Menu" << endl;
        cout << "===================================" << endl;
        cout << " 1. Song Collection Menu" << endl;
        cout << " 2. Playlist Menu" << endl;
        cout << " 0. Exit " << endl;
        cout << "-----------------------------------" << endl << endl;
        cout << "Select your Option: ";
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
                cout << "Invalid Input" << endl << endl;
                system("pause");
                break;
        }
    } while(option != 0);
    return 0;
}