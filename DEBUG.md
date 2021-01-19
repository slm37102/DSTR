# 19/01/2020 Version
1. deletePlaylistSong() - (*head_ref)->length need to delete twice? Why?


2. deletePlaylistSong() - no need traverse the playlist? SongCollection* selectedSong 没有用到?


3. deletePlaylistSong() got error because of this (?):
   addPlaylistSong() no 'newSong->length++' for else{} block, only if{} block has.
   
   
4. <= userSong instead of < userSong? because when length = 1 and userSong = 1, then how?
   <= userPlaylist instead of < userPlaylist?


5. addPlaylistSong() if (selectedPlaylistSong->song == selectedSong) move in front of while (selectedPlaylistSong->next != NULL) ? 
ANS: Nonid. Because we put the if statement behind is because the while loop cannot check whether the last song in playlist
     is the same as the song to be added by user.


6. addPlaylist() - if using while(last->next != NULL) cannot check for the last node whether the playlist exist or not because last node 的 next is NULL, 
   it will break from the loop before checking the last node.


7. displayPlaylist() - why i < 3 in the for loop?


8. deleteSong() - if(userSong == 1) // if user choose the first song (update comment line)


9. PlaylistMenu(), case 5:
   why using SongCollection* selectedSong since it is not use in deletePlaylistSong()?


10. playlistSearch() - can straight use head to traverse? no need to create another pointer?
<<<<<<< HEAD

testing
=======
>>>>>>> d92a9e0141dbd2caec0d34dc25d326cce5a4130a
