# Status

March 30, 2026

*2:02 PM*

As of writing this, I just began writing the main part of the shell a little while ago, i haven't, really
coded in almost 2 weeks T_T. I know, thats probably why I feel so empty headed when I code, Like no ideas are coming out of my head. Especially since I just quit vibe coding recently, so yeah... Its basic as of now, I still use iostream. I will make my own I/O layer soon so I can control the input and output, but for now, well stick to iostream. for now it sits at 1-3% Done, -_-.

*7:04 PM*

I finally added a process handler in process.hpp for myshell which will be helpful in the future, as of now.
It only creates a new process for the shell and waits for it to finish, then closes  the handles. its made with CreateProcessA,
its so mind blowing how much I've learned by just reading windows documentation on windows.h. I also added some string helpers in
utility like Ult_Trim and Trim, and replace_all. which are all utilizing the algorithm libraries functions, its the gift that keeps on giving =D.

*9:52 PM*

Directory navigation is still broken, But i will fix it tomorrow, I'm getting sleepy and my laptop is on 5% =<.

March 31, 2026

*11:38 AM*

I finally fixed the directory navigation, turns out I am not parsing curr properly at all.
I fixed it, took be an hour to figure it out, wtf T_T.

*5:52 PM*

I finally added the I/O layer and replaced all the couts, and remained one cerr, just incase the screen buffer doesnt get made.
I just reused my I/O handler from my text adventure game **Deathly Hollows**.

*6:55 PM*

Small update: I finally fixed the sigint looping issue since i have my own input handler =D, by breaking the input loop.
