# Function
- collection
1. Add songs            --
2. Display songs        --
3. Delete song          --
4. Playlist search      --

- playlist
1. Create playlist      --
2. View playlist        --
3. Add songs            --
4. View songs           --
5. Remove songs         --
6. Playlist navigation  --
7. Delete playlist      --

# Needed to add
1. playlist search          --finished
2. to multi music           --finished
3. duration to mm:ss        --finished
4. error if exceed length   --finished
5. try catch                --not implemented
6. doubly linked list       --finished
7. no same song, playlist   --finished 
8. getline to store space   --finished
9. add attribute durationInS to the song collection? -- not implemented

# Additional feature
- menu                --finished
- shuffle             --finished
- countdown           --finished
- doubly linked list  --finished
- queue on playlist   --not implemented
- database            --not implemented

# Data sturcture
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
# Classes
1. PlaylistName
- length 
- Playlist (Playlist)
- song location (SC)
- next

2. SongCollection
- song detail (t,s,d)
- length
- playlistName (PN)
- next

3. PlaylistSong
- length
- song (SC)
- prev
- next

4. Playlist
- playlistName (string)
- length 
- next 
- songList (PlaylistSong)

# Requirement
- add song to collection
- create playlist
- add song to playlist
- can save several playlist
- can only add song from collection
- one song add to many playlist

# Detail of function
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
