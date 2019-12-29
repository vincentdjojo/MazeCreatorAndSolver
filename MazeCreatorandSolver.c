

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
          printf ( "S" );
        }
        else if ( i == ( w - 2 ) && j == (  h - 2 ) )
        {
          printf ( "G" );
        }
        else {
          switch(maze[j * w + i]) {
            case 1:  printf("#");  break;
            case 2:
              printf(".");
              break;
            default:
              printf(" ");  break;
          }
        }
      }
      printf("\n");
   }
}

void imperfect ( char *maze, int w, int h )//make the maze imperfect
{
  char* temp;
  temp = (char*)malloc(w * h * sizeof(char));
  for(int j = 0; j < h; j++) {
     for(int i = 0; i < w; i++) {
        temp[j * w + i] = maze[j * w + i];
     }
   }
  int* dewall;
//=====================
  int choice, counter;
  int i, j,l=0;
  int dx, dy;
  int forward;

  /* Remove the entry and exit. */
  temp[0 * w + 1] = 1;
  temp[(h - 1) * w + (w - 2)] = 1;
  int x = 1, y = 1, done = 0;
  forward = 1;
  choice = 0;
  counter = 0;
  i = 1;
  j = 1;
  while(i != w - 2 || j != h - 2) {//traverse through the maze. Similar to Solve_Maze
    dx = 0; dy = 0;
    switch(choice) {
    case 0:  dx = 1;  break;
    case 1:  dy = 1;  break;
    case 2:  dx = -1; break;
    default: dy = -1; break;
    }
    if( (forward  && temp[(j + dy) * w + (i + dx)] == 0)
       || (!forward && temp[(j + dy) * w + (i + dx)] == 2)) { //If traversable then do the following
       temp[j * w + i] = forward ? 2 : 1;

       if ( forward != 1 ) //If next location is path
       {
         if ( j < w-2 && i < h-2 && maze [ j+1 * w + i] == 1 &&  maze [ j * w + i+1] ==1 && done == 0)
         {//Break the wall once
           maze [ j * w + i + 1] = 0;
           done = 1;
         }
         else if ( j < w-2 && i < h-2 && maze [ j * w + i+1] == 1 &&  maze [ j+1 * w + i] ==1 && done == 0 )
         {//break the wall once
           maze [ j + 1 * w + i] = 0;
           done = 1;
         }
       }


       i += dx;
       j += dy;
       forward = 1;
       counter = 0;
       choice = 0;
    } else {
       choice = (choice + 1) % 4;
       counter += 1;
       if(counter > 3) {
          forward = 0;
          counter = 0;
       }
    }
  }
  printf ( "\n" );
  for ( int k = 0; k < l; k++ )
  {
    maze[dewall[k]] = 0;
  }

  temp[0 * w + 1] = 1;
  temp[(h - 1) * w + (w - 2)] = 1;
  if ( done == 0 )
  {
    printf ( "\nMaze can't be made imperfect this time\n" );
  }
  maze[x * w + y] = 0;
}

void filePrint ( char *maze, int w, int h )
{
     FILE *cfPtr;

    if ( ( cfPtr = fopen ( "maze.dat", "w" ) ) == NULL )
    {
      printf ( "File could not be opened\n" );
    }
    else
    {
       int i, j,k=0;
       for(j = 0; j < h; j++) {
          for(i = 0; i < w; i++) {
            if ( i == ( 1 ) && j == ( 1 ) )
            {
              fprintf ( cfPtr, "S" );
            }
            else if ( i == ( w - 2 ) && j == (  h - 2 ) )
            {
              fprintf ( cfPtr, "G" );
            }
            else {
              switch(maze[j * w + i]) {
                case 1:  fprintf( cfPtr, "#");  break;
                case 2:

                  fprintf( cfPtr, ".");
                  break;
                default:
                  fprintf( cfPtr, " ");  break;
              }
            }
          }
          fprintf(cfPtr, "\n");
        }
        fclose (cfPtr);
     }
}

void fileRead ( char *maze, int w, int h )
{
    FILE *cfPtr;


    if ( ( cfPtr = fopen ( "maze.dat", "r" ) ) == NULL )
    {
      printf ( "File could not be opened\n" );
    }
    else
    {
      char** grid=(char*)malloc(sizeof(char)*h); //creating dynamic 2d array for storing the maze from the text file
         for(int i=0;i<h;i++)
          {
              grid[i]=(char*)malloc(sizeof(char)*w);
          }


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

void DispMazeValue( char *maze, int w, int h ) {  //function  for displaying  the message having three parameters maze ,width and height

   int i, j,k=0;
   for(j = 0; j < h; j++) {
      for(i = 0; i < w; i++) {
          printf("%d",maze[j * w + i]);

      }
          printf("\n");
    }

 }

  void changeToValue( char *maze, int w, int h ) {  //function  for displaying  the message having three parameters maze ,width and height

     int i, j,k=0;
     int count=0;
     for(j = 0; j < ( h * w ); j++) {

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
         //count++;
     }
     maze[0 * w + 1] = 1;
     maze[(h - 1) * w + (w - 2)] = 1;

   }

void cutMaze(char *maze, int w, int h, int i, int j) {

   int x1, y1;//location in the maze
   int x2, y2;//Check x1 and y1 locations with x2 and y2 to see where to move
   int dx, dy;//Locations around the current location in maze
   int choice, counter;

   choice = rand() % 4;//random the direction
   counter = 0;
   while(counter < 4) {//The maze consists of 4 by 4 paths, here we check the surroundings to choose the direction of the current path
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
void Solve_Maze(char *maze, int w, int h) {

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
      switch(choice) {
        case 0:  dx = 1;  break;
        case 1:  dy = 1;  break;
        case 2:  dx = -1; break;
        default: dy = -1; break;
      }
      if(   (forward  && maze[(j + dy) * w + (i + dx)] == 0)
         || (!forward && maze[(j + dy) * w + (i + dx)] == 2)) {
         maze[j * w + i] = forward ? 2 : 3;
         i += dx;
         j += dy;
         forward = 1;
         counter = 0;
         choice = 0;
      } else {
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

   printf("Maze \n");
   printf("usage: maze <w> <h> [s]\n");
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

   //DispMaze ( maze, w, h ); //display the perfect maze
   imperfect ( maze, w, h );//make generated maze imperfect
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
