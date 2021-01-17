# TODO
- collection
1. Add songs
2. Display songs
3. Delete song
4. Playlist search

- playlist
1. Create playlist      --finished(merge song?)
2. View playlist        --finished(merge song?)
3. Add songs            --finished(add to collection)
4. View songs           --finished(?)
5. Remove songs         --finished(got problem, doubly, remove from collection)
6. Playlist navigation  --not finished
7. Delete playlist      --finished(always delete last one)

# Needed to add
1. playlist search          --finished
2. to multi music           --finished
3. duration to mm:ss        --finished (limit second)
4. error if exceed length   (implement length)
5. try catch
6. doubly linked list
7. add song to playlist


# additional feature
- menu              --finished
- database
- shuffle
- countdown
- queue on playlist
- doubly linked list to able to have prev music 

# data sturcture
- playlist
```
playlist -> playlist -> playlist
    ^           ^           ^
    |           |           |
    V           V           V
   song        song        song
    ^           ^           ^
    |           |           |
    V           V           V
   song        song        song
```
- collection
```
  song   ->   song   ->   song
    |           |           |
    V           V           V
playlist    playlist    playlist
    |           |           |
    V           V           V
playlist    playlist    playlist
```

# Requirement
- add song to collection
- create playlist
- add song to playlist
- can save several playlist
- can only add song from collection
- one song add to many playlist

# detail of TODO
- collection
1. Add songs – Add a song, with appropriate information, into the songs collection.
2. Display songs – Display all songs available in the collection
3. Delete songs – Delete a particular song in the collection. Playlist must be
properly updated.
4. Playlist search – Search and display all playlists that contains a specific song.

- playlist
1. Create playlist – Create a new playlist.
2. View playlist – View all available playlists.
3. Add songs – Add songs from the songs collection into a particular playlist.
4. View songs – View songs from a particular playlist.
5. Remove songs – Remove a song from a particular playlist.
6. Playlist navigation – Navigating a particular playlist.
7. Delete playlist – Delete a particular playlist.

PlaylistName
- length 
- Playlist (Playlist)
- song location (SC)
- next

SongCollection
- song detail (t,s,d)
- length
- playlistName (PN)
- next

PlaylistSong
- length
- song (SC)
- prev
- next

Playlist
- playlistName (string)
- length 
- next 
- songList (PlaylistSong)