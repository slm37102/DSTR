#include<iostream>
#include<string>
using namespace std;

class Playlist;

class PlaylistName
{
public:
	Playlist* playlist;
	PlaylistName* nxtPlaylist;
};

class SongCollection 
{
	string title;
	string singer;

	// minus 1sec everytime
	string duration;

public:
	SongCollection* nxtSong;
	PlaylistName* playlistName;
	
	SongCollection(string t, string s, string d) 
	{
		title = t;
		singer = s;
		duration = d;
	}

	string getTitle() 
	{
		return title;
	}

	string getSinger() 
	{
		return singer;
	}


	string getDuration() 
	{
		return duration;
	}
};

class PlaylistSong
{
public:
	SongCollection* thisSong;
	PlaylistSong* nxtSong;

	PlaylistSong(SongCollection* song)
	{
		thisSong = song;
	}
};

class Playlist
{
	string playlistName;

public:
	Playlist* nxtPlaylist;
	PlaylistSong* songList;

	Playlist(string name)
	{
		playlistName = name;
	}

	string getPlayListName()
	{
		return playlistName;
	}
};

// Append song at the end
void addSong(SongCollection** headRef, string t, string s, string d) 
{
	SongCollection* newNode = new SongCollection(t, s, d);
	newNode->nxtSong = NULL;

	if ((*headRef) == NULL) 
	{
		(*headRef) = newNode;
		return;
	}

	SongCollection* current = *headRef;
	while (current->nxtSong != NULL) 
	{
		current = current->nxtSong;
	}

	current->nxtSong = newNode;
	return;
}

void displaySong(SongCollection* head) 
{
	int counter = 1;
	SongCollection* current = head;

	if (current == NULL) 
	{
		cout << "The collection is empty!" << endl << endl;
		return;
	}

	while (current != NULL) 
	{
		cout << counter << ". " << current->getTitle() << " " << current->getSinger() << " " << current->getDuration() << " minutes" << endl;
		current = current->nxtSong;
		counter++;
	}

	cout << endl;
}

void deleteSong(SongCollection** headRef, string toBeDeleted) 
{
	SongCollection* previous = NULL;
	SongCollection* current = (*headRef);
	string deleteSong = toBeDeleted;

	if ((*headRef) == NULL) 
	{
		cout << "No songs to be deleted!";
		return;
	}

	if (current != NULL && current->getTitle() == deleteSong)
	{
		(*headRef) = current->nxtSong;

		PlaylistName* currentName = current->playlistName;
		PlaylistName* prevName = NULL;

		/*while (currentName->playlist != NULL) 
		{
			while (currentName->playlist->songList != NULL)
			{
				if (currentName->playlist->songList->thisSong->getTitle() == deleteSong)
				{
					prevName->playlist->songList->nxtSong = currentName->playlist->songList->nxtSong;
						
					// since here already delete thisSong
					delete currentName->playlist->songList->thisSong;
					break;
				}
				prevName->playlist->songList = currentName->playlist->songList;
				currentName->playlist->songList = currentName->playlist->songList->nxtSong;
			}
			currentName->playlist = currentName->playlist->nxtPlaylist;
		}
		*/
		// Here need to delete again? (This 'current' is direct from SongCollection)
		delete current;
		return;
	}


	while (current != NULL && current->getTitle() != deleteSong)
	{
		previous = current;
		current = current->nxtSong;
	}

	// No need to check for other linked lists, because if the song is not found in the SongCollection class
	// it is impossible to be present in any playlists. 
	if (current == NULL) 
	{
		cout << "Song not found!";
		return;
	}

	/*
	PlaylistName* currentName = current->playlistName;
	PlaylistName* prevName = NULL;

	while (currentName->playlist != NULL)
	{
		while (currentName->playlist->songList != NULL)
		{
			if (currentName->playlist->songList->thisSong->getTitle() == deleteSong)
			{
				prevName->playlist->songList->nxtSong = currentName->playlist->songList->nxtSong;

				// since here already delete thisSong
				delete currentName->playlist->songList->thisSong;
				break;
			}
			prevName->playlist->songList = currentName->playlist->songList;
			currentName->playlist->songList = currentName->playlist->songList->nxtSong;
		}
		currentName->playlist = currentName->playlist->nxtPlaylist;
	}
	*/

	previous->nxtSong = current->nxtSong;
	// need to delete this 'current'?
	delete current;

}

void playlistSearch(SongCollection* head, string title) 
{
	int counter = 1;

	SongCollection* current = head;

	if (current == NULL) 
	{
		cout << "No songs found!";
		return;
	}
	
	if (current != NULL) 
	{
		while (current != NULL) 
		{
			PlaylistName* currentName = current->playlistName;

			while (currentName != NULL)
			{
				if (currentName->playlist->getPlayListName() == title)
				{
					cout << counter << currentName->playlist->getPlayListName();
					counter++;
				}
				currentName = currentName->nxtPlaylist;
			}

			current = current->nxtSong;
		}
		
	}

	if (counter == 1) 
	{
		cout << "The song entered is not found in any playlists!";
	}
}

void CollectionMenu(SongCollection* song) 
{
	int option;
	string duration;
	string userSong;
	string singer;
	string title;
	
	
	do 
	{
		cout << "---Music Library---" << endl;
		cout << "1. Add Song" << endl;
		cout << "2. Display All Songs" << endl;
		cout << "3. Delete Song" << endl;
		cout << "4. Playlist Search" << endl;
		cout << "0. Back to main menu" << endl;

		cout << endl;

		cout << "Option: ";
		cin >> option;

		switch (option) 
		{
			case 0:
				break;

			case 1:
				cout << "Title: ";
				cin.ignore();
				getline(cin, title);

				cout << "Singer: ";
				getline(cin, singer);
				

				cout << "Duration (mm:ss): ";
				getline(cin, duration);
				

				addSong(&song, title, singer, duration);
				cout << endl;
				break;
			
			case 2:
				displaySong(song);
				break;

			case 3:
				displaySong(song);
				cout << "Please enter the name of the song to be deleted: ";
				cin >> userSong;

				deleteSong(&song, userSong);
				break;

			case 4:
				cout << "---Find your playlists that contained the specific song---" << endl << endl;
				cout << "Please enter the name of the song: ";
				cin >> userSong;

				playlistSearch(song, userSong);
				break;

			default:
				cout << "Invalid Input!" << endl << endl;
		}
	} while (option != 0);
}

int main() 
{
	int option;
	SongCollection* songHead = NULL;

	do 
	{
		cout << "---Welcome to Music Management Application---" << endl;
		cout << "What would you like to do today?" << endl;
		cout << "1. Music Library" << endl;
		cout << "0. Exit" << endl;
		
		cout << endl;
		
		cout << "Option: ";
		cin >> option;

		switch (option) 
		{
			case 0:
				break;

			case 1:
				cout << endl;
				CollectionMenu(songHead);

			default:
				cout << "Invalid input!" << endl << endl;
		}
	} while (option != 0);
	
	return 0;
}

