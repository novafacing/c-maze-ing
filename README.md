# c-maze-ing
It does mazes but in C. 

'''
Usage:
Download the repo and extract. If you want to just make a basic maze, use
./makeandsolve
If you want to change the size of the maze, edit generator.fs and change the bounds at the bottom of the file.
To compile generator.fs, you can use 
fsharpc generator.fs
and then 
generator.exe > <maze_name_here>
And then solve the maze with 
./solvemaze <maze_name>
