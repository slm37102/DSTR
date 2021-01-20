# Function
- collection
1. Add songs            --
2. Display songs        --
3. Delete song          --not finished(got problem after adding in playlist)
4. Playlist search      --

- playlist
1. Create playlist      --
2. View playlist        --
3. Add songs            --
4. View songs           --
5. Remove songs         --not finished(got problem, 1 remove all, 2 do nothing) - failed (selectedPlaylist->length < userSong)
6. Playlist navigation  --not finished
7. Delete playlist      --not finished(error if playlist has song)

# Needed to add
1. playlist search          --finished
2. to multi music           --finished
3. duration to mm:ss        --finished (limit second)
4. error if exceed length   --TODO
5. try catch                --TODO
6. doubly linked list       --finished
7. no same song and playlist name

# Additional feature
- menu                --finished
- database            --can try if got time
- shuffle             --can try if got time
- countdown           --TODO
- queue on playlist   --may not needed
- doubly linked list  --finished

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
