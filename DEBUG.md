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

# 21/01/2020 Version
1. deletePlaylist() 
Why need (*head_ref)->length = selectedPlaylist->length? straight away (*head_ref)->length-- jiu ok le ma not?
Is it because you only store the length in the head_ref there? since the head_ref change, now the length data is lost?

- so our length is mainly save in the head, so if head is delete so we need to save the head length to the next one which is the head now.

2. deletePlaylistSong() for Collection
Why need if(selectedPlaylistName->playlist->songList != NULL) 2 times? 
Since the length will always need to minus de, so, the second if{} why not remove it and just remain the (selectedPlaylistName->playlist->songList->length--)?

- same as 1. or else the length will be delete.

3. this->song = song;'this' refer to the playlistSong class obj created by this constructor?

- the this is refer to the variable/attribute(?) of the class, because the variable name is the same so it need to have a key work to say which variable is which

4. addSong()
add another if{} statement after while loop? Cause while loop using 'last->next' will break b4 checking for the title & singer of the last song. 

- ya, true i changed 

5. addPlaylistSong() - Can use (selectedPlaylist->songList->length++) instead of (newSong->length = 1) ? Cause we want to direct affect **head_ref not ma?

- cannot cos when it is initialize it has no value inside one.

6. displayPlaylist() - (// if no song inside) change to (// if user haven't create any playlists)

- ok done

7. PlaylistMenu(), case 5:
why: 
SongCollection* selectedSong = song;
                for (int i = 0; i < userSong - 1; i++)
                {
                    selectedSong = selectedSong->next;
                }

Memory address of the song in the song collection is the same as memory address of the song in the playlist meh? Should be selectedPlaylist->songList 才对 not ma?

- oh ya good spot

8. deletePlaylistName(PlaylistSong...) - (//delete song in song collection) change (//to update song nodes that contain the playlist to be deleted)

- ok

9. For duration, sscanf will return an int, that int is the number of item that has been read and return -1 when error. So, change if(sscanf(...) == 2), more accurate?

- hmmm ya it make sense because i saw this implementation online so i didnt like think about it, but oh it still have problem when it type like 1:11:11, it will still able to be added...

10. playlistMenu(), case 5:
since we are deleting songs, why need check the song collection (using the if statement)? Because we are not adding song.

if (selectedPlaylist->length < userSong) should change to (selectedPlaylist->songList->length) 才对 not ma?
Cause we are checking the length of selectedPlaylist 的 songList not the playlist class itself 的 length 啊

- ya true same as the problem as 7. last time me too confuse on this part ba haha

11. PlaylistMenu(), case 6, case 'n',
The if{} statement should check (selectedSong->next) instead of (selectedSong->prev) not ma? Cause it is checking for next song.  

- ya haha copy forgot change

# 22/01/2020 Version
1. playlistMenu(), case 5:
Since we are deleting songs from playlist, why need (if song == NULL) statement? We are not adding songs right? 而且我们要的是user selected playlist 里面的 song 不是吗?

2. same as yesterday de '2', I mean the 2nd if{} statement ah, need meh? Cause the first if{} is to assign back the length to the **head_ref, this I know. 
But the last if{} to minus the length, just before the 'delete' keyowrd there, why is it needed? Cause confirm is != NULL 的不是吗? Let's say selectedPlaylistSong got 1 song then after update **head_ref = selectedPlaylistSong->next, it will equal to NULL. Then no need to update the length ady. But if selectedPlaylistSong got more than 1 song, we delete first song again and update **head_Ref = selectedPlaylistSong->next. Now, because update **head_ref de part we ady check != NULL to update it right? So at the bottom there, straight away length-- jiu ok le ma not? 而且, If we want to delete de is not the first song, then confirm **head_ref is != NULL not ma, it is pointing to the first song ah.

3. deletePlaylistSong() both - if the head is not the song, then how? Cause there is no looping for selectedPlaylistSong ah. So need to put a loop?
