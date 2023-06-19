/*-----------------------------------------------------------------------

  File  : labsolve.c

Author: Stephan Schulz (schulz@eprover.org)

Contents

   Program reading and solving simple ASCII labyrinths.

Copyright 2015 by the author.
This code is released under the GNU General Public Licence, version
  2, or, at your choice, any later version.

Changes

<1> Tue Jun  2 18:01:34 CEST 2015
    New
-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

#define MAXCOLS  256
#define MAXROWS  256


/* Data type: Labyrinth - ASCII map, costs, direction */

typedef struct labyrinth
{
   char lab[MAXCOLS+2][MAXROWS];
   long costs[MAXCOLS][MAXROWS];
   int maxrow;
   int maxcol;
   int startx;
   int starty;
   int treasurex;
   int treasurey;
}LabCell, *Lab_p;


/* Data structure for represeting individual moves */

typedef struct relpos
{
   int dx;
   int dy;
}RelPos;

/* Legal moves in the base case */

RelPos straight_moves[] =
{
   { 0,  1},
   { 0, -1},
   { 1,  0},
   {-1,  0},
   {INT_MAX, INT_MAX}
};

/* Legal moves if diagonals are ok */

RelPos all_moves[] =
{
   { 0,  1},
   { 0, -1},
   { 1,  0},
   {-1,  0},
   { 1,  1},
   { 1, -1},
   {-1,  1},
   {-1, -1},
   {INT_MAX, INT_MAX}
};




/*-----------------------------------------------------------------------
//
// Function: xmalloc()
//
//   Thin wrapper around malloc() - fail noisily (with error message)
//   if no memory is available.
//
// Global Variables: -
//
// Side Effects    : Only via malloc() or in case of error
//
/----------------------------------------------------------------------*/

void* xmalloc(size_t size)
{
   void *mem = malloc(size);
   if(!mem)
   {
      fprintf(stderr, "Out of memory\n");
      exit(EXIT_FAILURE);
   }
   return mem;
}

/*-----------------------------------------------------------------------
//
// Function: xstrdup()
//
//   Thin wrapper around strdup() - fail noisily (with error message)
//   if no memory is available.
//
// Global Variables: -
//
// Side Effects    : Only via malloc() or in case of error
//
/----------------------------------------------------------------------*/

char* xstrdup(char* str)
{
   void *newstr = strdup(str);
   if(!newstr)
   {
      fprintf(stderr, "Out of memory\n");
      exit(EXIT_FAILURE);
   }
   return newstr;
}

/*-----------------------------------------------------------------------
//
// Function: LabInit()
//
//   Verify and Initialize the lab: seach for and record Start and
//   Treasure positions. End with error if they are not found.
//
// Global Variables: -
//
// Side Effects    : Only in error case.
//
/----------------------------------------------------------------------*/

void LabInit(Lab_p lab)
{
   int i,j;
   bool start = false, treasure = false;

   lab->maxcol = 0;
   for(i=0; i< lab->maxrow; i++)
   {
      for(j=0; j<MAXCOLS; j++)
      {
         if((lab->lab[i][j]=='\n') && (j>lab->maxcol))
         {
            lab->maxcol = j;
         }
         lab->costs[i][j] = LONG_MAX;
         if(lab->lab[i][j] == 'S')
         {
            if(start)
            {
               fprintf(stderr, "Error: Multiple start positions\n");
               exit(EXIT_FAILURE);
            }
            lab->startx = i;
            lab->starty = j;
            start = true;
         }
         if(lab->lab[i][j] == 'X')
         {
            if(treasure)
            {
               fprintf(stderr, "Error: Multiple treasure positions\n");
               exit(EXIT_FAILURE);
            }
            lab->treasurex = i;
            lab->treasurey = j;
            treasure = true;
         }
      }
   }
   if(!start)
   {
      fprintf(stderr, "Error: No start position\n");
      exit(EXIT_FAILURE);
   }
   if(!treasure)
   {
      fprintf(stderr, "Error: No treasure position\n");
      exit(EXIT_FAILURE);
   }
}



/*-----------------------------------------------------------------------
//
// Function: LabRead()
//
//   Read a labyrinth from an input stream and return it.
//
// Global Variables: -
//
// Side Effects    : Input, memory.
//
/----------------------------------------------------------------------*/

Lab_p LabRead(FILE* in)
{
   Lab_p handle = xmalloc(sizeof(LabCell));
   char  *inp;

   handle->maxrow = 0;

   while((inp=fgets(handle->lab[handle->maxrow], MAXCOLS, in)))
   {
      handle->maxrow++;
      if(handle->maxrow>MAXROWS)
      {
         fprintf(stderr, "Labyrinth too long\n");
         exit(EXIT_FAILURE);
      }
   }
   return handle;
}


/*-----------------------------------------------------------------------
//
// Function: LabPrint()
//
//   Print the current state of a labyrinth.
//
// Global Variables: -
//
// Side Effects    : Output
//
/----------------------------------------------------------------------*/

void LabPrint(FILE* out, Lab_p lab)
{
   int i;

   for(i=0; i<lab->maxrow; i++)
   {
      fprintf(out, "%s", lab->lab[i]);
   }
}




/*-----------------------------------------------------------------------
//
// Function: LabSolve()
//
//   For all reachable fields, compute the cost of going there.
//
// Global Variables: -
//
// Side Effects    : Computes the lab costs and directions.
//
/----------------------------------------------------------------------*/

long LabSolve(Lab_p lab, RelPos moves[], int x, int y, bool print)
{
   int i;
   long res;
   char current;

   if(print)
   {
      system("clear");
      LabPrint(stdout, lab);
      printf("Exploring: %d, %d\n", x,y);
      system("sleep 0.05");
   }
   current = lab->lab[x][y];
   switch(current)
   {
   case '#': return -1;
   case '.': return -1;
   case '!': return -1;
   case 's': return -1;
   case 'X': return 0;
   default:
         break;
   }
   lab->lab[x][y] = '.';
   for(i=0; moves[i].dx != INT_MAX; i++)
   {
      res = LabSolve(lab, moves, x+moves[i].dx, y+moves[i].dy, print);
      if(res != -1)
      {
         return res+1;
      }
   }
   lab->lab[x][y] = '!';
   return -1;
}



/*-----------------------------------------------------------------------
//
// Function: main()
//
//
//
// Global Variables:
//
// Side Effects    :
//
/----------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
   FILE *in = stdin;
   Lab_p lab;
   long  cost;
   int   arg, args=argc,  farg;
   RelPos *moves = straight_moves;
   bool  print = true;

   for(arg = 1; arg<argc; arg++)
   {
      if(strcmp(argv[arg], "-a")==0)
      {
         moves = all_moves;
         args--;
      }
      else if(strcmp(argv[arg], "-n")==0)
      {
         print = false;
         args--;
      }
      else
      {
         farg = arg;
      }
   }

   if(args > 2)
   {
      fprintf(stderr, "Usage: %s [-a] [<file>]\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   if(args == 2)
   {
      in = fopen(argv[farg], "r");
      if(!in)
      {
         perror(argv[0]);
         exit(EXIT_FAILURE);
      }
   }
   lab = LabRead(in);
   LabInit(lab);
   cost = LabSolve(lab, moves, lab->startx, lab->starty, print);
   if(cost==-1)
   {
      LabPrint(stdout, lab);
      fprintf(stdout, "There is no way from S to X\n");
   }
   else
   {
      LabPrint(stdout, lab);
      printf("Cost: %ld\n", cost);
   }
   exit(EXIT_SUCCESS);
}

/*---------------------------------------------------------------------*/
/*                        End of File                                  */
/*---------------------------------------------------------------------*/
