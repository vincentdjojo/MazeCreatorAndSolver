#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/*displaying  the  maze. */

void DispMaze( char *maze, int w, int h ) {  //function  for displaying  the message having three parameters maze ,width and height
   int i, j,k=0;
   for(j = 0; j < h; j++) {
      for(i = 0; i < w; i++) {
        if ( i == ( 1 ) && j == ( 1 ) )
        {
          printf ( "S" );//Display the S
        }
        else if ( i == ( w - 2 ) && j == (  h - 2 ) )
        {
          printf ( "G" );//Display the G
        }
        else {
          switch(maze[j * w + i]) {
            case 1:  printf("#");  break; //Display the wall
            case 2:
              printf(".");//Display the solution path
              break;
            default:
              printf(" ");  break;//Display a path
          }
        }
      }
      printf("\n");
   }
}

int imperfect3 ( char *maze, int w, int h )
{
   int deadEnds;
   int index = 0;
   int counter;
   int destroy = 0;

   //get dead ends in this loop
   for (int j = h/2; j < h - 2; j++)
   {
     for (int i = i/2; i < w -2; i++)
     {
       counter = 0;
       if ( maze[j * w + i] == 1)//if a wall then continue
       {
         continue;
       }

       if( maze[j * w + i] == 0 )//if not a wall check if it is a dead end
       {
         counter = 0;
         destroy = 0;
         if ( maze[(j + 1) * w + i] != 1)//check if the surroundings of the current location is a wall or not, if space add 1.
         {
           counter = counter + 1;
           destroy = 1;
         }

         if ( maze[(j - 1) * w + i ] != 1)//check if the surroundings of the current location is a wall or not, if space add 1.
         {
           counter = counter + 1;
           destroy = 2;
         }

         if ( maze[j * w + (i + 1) ] != 1)//check if the surroundings of the current location is a wall or not, if space add 1.
         {
           counter = counter + 1;
           destroy = 3;
         }
         if ( maze[j * w + (i - 1)] != 1)//check if the surroundings of the current location is a wall or not, if space add 1.
         {
           counter = counter + 1;
           destroy = 4;
         }



         if ( counter == 1 )//if counter is only 1 then it is a deadend because a dead end only has one space and 3 walls
         {
           //calculate the wall that needs to be destroyed to make the maze imperfect
           if ( destroy == 1 )
           {
            deadEnds = (j - 1) * w + i;
           }
           else if ( destroy == 2 )
           {
             deadEnds = (j + 1) * w + i;
           }
           else if ( destroy == 3 )
           {
             deadEnds  = j * w + (i - 1);
           }
           else if ( destroy == 4 )
           {
             deadEnds = j * w + (i + 1);
           }
         }
         else
         {
           continue;//if not deadend continue to look for a deadend
         }
       }
     }
   }
    return deadEnds;//return the location and delete the wall
}


void filePrint ( char *maze, int w, int h )
{
     FILE *cfPtr;//delcare filePtr

    if ( ( cfPtr = fopen ( "maze.dat", "w" ) ) == NULL )
    {
      printf ( "File could not be opened\n" );
    }
    else
    {
       int i, j,k=0;
       for(j = 0; j < h; j++) {//Loop through the file
          for(i = 0; i < w; i++) {
            if ( i == ( 1 ) && j == ( 1 ) )
            {
              fprintf ( cfPtr, "S" ); //Visual effect to show S in the file
            }
            else if ( i == ( w - 2 ) && j == (  h - 2 ) )
            {
              fprintf ( cfPtr, "G" ); //Visual effect to show G in the file
            }
            else {
              switch(maze[j * w + i]) {
                case 1:  fprintf( cfPtr, "#");  break; //Print the walls into the file
                case 2:
                  fprintf( cfPtr, ".");
                  break;
                default:
                  fprintf( cfPtr, " ");  break; //Print the spaces into the file
              }
            }
          }
          fprintf(cfPtr, "\n");//Print the spsace into te file
        }
        fclose (cfPtr);//Close the file once everything is read
     }
}

void fileRead ( char *maze, int w, int h )
{
    FILE *cfPtr;//Declar filePtr

    if ( ( cfPtr = fopen ( "maze.dat", "r" ) ) == NULL )
    {
      printf ( "File could not be opened\n" );
    }
    else
    {
          for(int i=0;i<h;i++)    //saving maze in a grid
          {

              for(int j=0;j<w;j++)
              {
                 maze[i*w+j]=fgetc(cfPtr);
              }
              if(fgetc(cfPtr)=='\n')
              {
                 continue;
              }
          }
      }
}

void DispMazeValue( char *maze, int w, int h ) {  //function  for displaying  the message having three parameters maze, width and height
                                                  //You can use this to check the values of the maze
   int i, j,k=0;
   for(j = 0; j < h; j++) {
      for(i = 0; i < w; i++) {
          printf("%d",maze[j * w + i]);
      }
          printf("\n");
    }

 }

  void changeToValue( char *maze, int w, int h ) {  //funciton to convert symbols in the .dat file to values to be used by the solver

     int i, j,k=0;
     int count=0;
     for(j = 0; j < ( h * w ); j++) { //loop thorugh maze array and replace each char with a corresponding value

         if ( maze [j] == '\n')
         {
           continue;
         }
         if ( maze [j] == '#')
         {
           maze[j] = 1;
         }
         else
         {
           maze [j] = 0;
         }
     }
     maze[0 * w + 1] = 1; //Remember to close the start and goal
     maze[(h - 1) * w + (w - 2)] = 1;

   }

void cutMaze(char *maze, int w, int h, int i, int j) {

   int x1, y1;//location in the maze
   int x2, y2;//Check x1 and y1 locations with x2 and y2 to see where to move
   int dx, dy;//Locations around the current location in maze
   int choice, counter;

   choice = rand() % 4;//random the direction
   counter = 0;
   while(counter < 4) {//The maze consists of 2 by 2 paths, here we check the surroundings to choose the direction of the current path
      dx = 0; dy = 0;
      switch(choice) {
        case 0:  dx = 1;
          break;
        case 1:  dy = 1;
          break;
        case 2:  dx = -1;
          break;
        default: dy = -1;
          break;
      }
      //Where to move next in the maze
      x1 = i + dx;
      y1 = j + dy;
      x2 = x1 + dx;
      y2 = y1 + dy;

      if(   x2 > 0 && x2 < w && y2 > 0 && y2 < h
         && maze[y1 * w + x1] == 1 && maze[y2 * w + x2] == 1) {//Checks if the chosen location next to the current location is available.
         maze[y1 * w + x1] = 0;//assign current position with path
         maze[y2 * w + x2] = 0;//assign current position with path
         i = x2; j = y2;
         choice = rand() % 4;
         counter = 0;
      } else {//otherwise re random the direcion
         choice = (choice + 1) % 4;
         counter += 1;
      }
   }

}

void MadeMaze(char *maze, int w, int h) {

   int i, j;

   /* Initialize the maze. */
   for(i = 0; i < w * h; i++) {
      maze[i] = 1;
   }
   maze[1 * w + 1] = 0;

   /* Seed the random number generator. */
   srand(time(0));

   /* Carve the maze. */
   for(j = 1; j < h; j += 2) {
      for(i = 1; i < w; i += 2) {
         cutMaze(maze, w, h, i, j);//generates the maze randomly
      }
   }

   /* Set up the entry and exit. */
   maze[0 * w + 1] = 1;
   maze[(h - 1) * w + (w - 2)] = 1;

}

/* Solve the maze. */
void Solve_Maze(char *maze, int w, int h) { //DFS solver

   int choice, counter;
   int i, j;
   int dx, dy;
   int forward;

   /* Remove the entry and exit. */
   maze[0 * w + 1] = 0;
   maze[(h - 1) * w + (w - 2)] = 0;

   forward = 1;
   choice = 0;
   counter = 0;
   i = 1;
   j = 1;
   while(i != w - 2 || j != h - 2) {
      dx = 0; dy = 0;
      switch(choice) {//Traverse through the maze
        case 0:  dx = 1;  break;
        case 1:  dy = 1;  break;
        case 2:  dx = -1; break;
        default: dy = -1; break;
      }
      if( (forward  && maze[(j + dy) * w + (i + dx)] == 0)|| (!forward && maze[(j + dy) * w + (i + dx)] == 2) ) {
         //if the current location can traverse to the next meaning there's a wall or a discovered path then traverse
         maze[j * w + i] = forward ? 2 : 3;
         i += dx;
         j += dy;
         forward = 1;
         counter = 0;
         choice = 0;
      } else { //Otherwise you cant travel there and try another direction
         choice = (choice + 1) % 4;
         counter += 1;
         if(counter > 3) {
            forward = 0;
            counter = 0;
         }
      }
   }


   maze[0 * w + 1] = 1;
   maze[(h - 1) * w + (w - 2)] = 1;
}

int main() {
   int w, h;
   char *maze;
   char *readMaze;
   int *deadEnds;
   printf("Maze \n");
   printf("usage: maze <w> <h>\n");
   scanf ( "%d %d", &w, &h );

   w = w * 2 + 3;
   h = h * 2 + 3;
   while(w < 7 || h < 7) { //My maze only works if the width and height are above 7 and the w and h are odd
      printf("error: illegal maze size\n");
      printf("usage: maze <w> <h> [s]\n");
      scanf ( "%d %d", &w, &h );
      w = w * 2 + 3;
      h = h * 2 + 3;
   }


   maze = (char*)malloc(w * h * sizeof(char));//Malloc location for maze in memory
   readMaze = (char*)malloc(w * h * sizeof(char));//Malloc location for maze stored in file to program

   if(maze == NULL) {
      printf("error: not enough memory\n");
      return 0;
   }


   MadeMaze(maze, w, h);//generate a maze
   printf ( "The generated maze:\n" );

   maze[ imperfect3 ( maze, w, h ) ] = 0;//make generated maze imperfect
   DispMaze ( maze, w, h );//display the generated imperfect maze before solving
   filePrint ( maze, w, h );//print maze into .dat file

   fileRead ( readMaze, w, h );//read the maze from the .dat file

   printf("\n");

   changeToValue( readMaze, w, h );//change the format of the maze so it can be read by the solver
   printf ("\nThe solved maze:\n");
   Solve_Maze(readMaze, w, h);//solve the maze read from the file
   DispMaze ( readMaze, w, h);//display the solved maze from the file

   /* Free memory */
   free(maze);
   return 0;

}
