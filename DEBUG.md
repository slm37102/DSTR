# 19/01/2020 Version
1. deletePlaylistSong() - (*head_ref)->length need to delete twice? Why?

- oh haha solved

2. deletePlaylistSong() - no need traverse the playlist? SongCollection* selectedSong 没有用到?

- i think this part got some problem cos i need this function in the deletePlaylistName() maybe will need a new function to solve this

3. deletePlaylistSong() got error because of this (?):
   addPlaylistSong() no 'newSong->length++' for else{} block, only if{} block has.

- ya, solved
   
4. <= userSong instead of < userSong? because when length = 1 and userSong = 1, then how?
   <= userPlaylist instead of < userPlaylist?

- ~~yes, solved~~
- no it actually is display no such song in playlist so no need include that. 

5. addPlaylistSong() if (selectedPlaylistSong->song == selectedSong) move in front of while (selectedPlaylistSong->next != NULL) ? 
ANS: Nonid. Because we put the if statement behind is because the while loop cannot check whether the last song in playlist
     is the same as the song to be added by user.


6. addPlaylist() - if using while(last->next != NULL) cannot check for the last node whether the playlist exist or not because last node 的 next is NULL, 
   it will break from the loop before checking the last node.

- i think add another if then can liao right but idk if got a better solution..

7. displayPlaylist() - why i < 3 in the for loop?

- oh i just make it show 3 song in the playlist only

8. deleteSong() - if(userSong == 1) // if user choose the first song (update comment line)

- ok

9. PlaylistMenu(), case 5:
   why using SongCollection* selectedSong since it is not use in deletePlaylistSong()?

- it got use ah haha, in the first if

10. playlistSearch() - can straight use head to traverse? no need to create another pointer?

- ya i think no need cos we only take the head value not the head reference, same as display(s) function 

---

11. all the delete got the length problem i yesterday solve but didn't save..
argghh i yesterday midnight did a bit of debug but didn't save...

- done

12. deleteplaylistsong and deleteplaylistName got problem
after deleteplaylistsong 

- solved