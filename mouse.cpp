#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>

time_t now, later;

void sleep(int delay)
{
 now=time(NULL);
 later=now+delay;
 while(now<=later)now=time(NULL);
}

enum direction {up,down,left,right};

char MAZE[24][80]={{"###############################################################################"},
                   {"#M#       # #     ###     #   #     #       #         #                   # # #"},
                   {"# # ### # # ### ####### ### ### ##### ### # # # # ##### ### # ##### # ##### # #"},
                   {"# # # # #   #   #       #   #           # #   # # # # # #   # #   # # # #     #"},
                   {"# ### # ### ### # ### ### # # ##### ### ######### # # ##### # ### ### # ### # #"},
                   {"#   #   # #   #     #     #       # # # #       # #   #     # # #   # #   # # #"},
                   {"### ### # ### ####### ### ######### # ####### ### # # ##### ### # ### # # # # #"},
                   {"#      # # #     #     #     # #         # #   #   #     #   #     #   # # # #"},
                   {"# # ##### # ### ############### ####### ### ### # ##### # ### # # ####### ### #"},
                   {"# #C# #   #   #       #       #   #       #     # #     # #   # # # #   #     #"},
                   {"##### # # # # ##### ### ### ### # ####### ##### ### # ### ### # ### # ##### # #"},
                   {"#   #   # # #     #       #     #       #         # # #       #           # # #"},
                   {"# ### ##### ### ##### ####### ##### ### ##### ### # ########### ######### # ###"},
                   {"# # # #       #     # #     # # # # #   #       # #   #       #   # #   # #   #"},
                   {"# # # # ####### # # ##### # ### # ### # # ######### ##### # ### ### ### # ### #"},
                   {"# #     #   #   # # ###   #         # # #   #       #     # # #       # #     #"},
                   {"# # ####### # # ######### # ####### # ####### ######### ##### ### # # # ### ###"},
                   {"#   #       # #     # #   # #     # # # # #       #         # #   # #   #     #"},
                   {"# # # # ### # ####### # ### # # # ### # # ##### ### ##### ### ### ##### ##### #"},
                   {"# # # #   # #       #     #   # #   #         # #       # #         #   # #   #"},
                   {"### ##### ### # ### # ############# ### ##### # ### # ### # ##### ##### # ### #"},
                   {"###         # # #               #         #     #   # #       #     #     #   #"},
                   {"###############################################################################"}};
                   
struct position{
       int x;
       int y;
       };
       
struct position mouse; 
struct position cheese;        
       
struct position GetMousePosition()
{
  struct position mousepos;
  for(int i=0;i<23;i++)
  { for(int j=0;j<79;j++)
  { if(MAZE[i][j]=='M'){mousepos.x=j;mousepos.y=i;return mousepos;}}
  }
}       
struct position GetCheesePosition()
{
     struct position cheesepos;
  for(int i=0;i<23;i++)
  { for(int j=0;j<79;j++)
  { if(MAZE[i][j]=='C'){cheesepos.x=j;cheesepos.y=i;return cheesepos;}}
  }   
}                   
void DisplayMaze()
 {
 for(int i=0;i<23;i++)
         {for(int j=0;j<79;j++)
         {printf("%c",MAZE[i][j]);}
   printf("\n");
  }
  mouse=GetMousePosition();
  cheese=GetCheesePosition();
  printf("Mouse position : %d %d",mouse.x,mouse.y);
  printf("Cheese position : %d %d\n",cheese.x,cheese.y);
 }
 
 float CalcDistance(struct position pos1,struct position pos2)
 {
  float distance;     
  if(MAZE[pos1.y][pos1.x]!='#')
  {distance = sqrt(pow((pos1.x-pos2.x),2) + pow((pos1.y-pos2.y),2));}
  else
  {distance=9999;}
  return distance;
     }
int MouseGotCheese()
{
 if(mouse.x==cheese.x &&mouse.y==cheese.y)
 return 1;
 else   
 return 0;   
}     
int SolveMaze()
{
  
  struct position north;
  struct position south;
  struct position west;
  struct position east;
  float distance,min=9999;
  direction dir;int count=0;
  
 while(!MouseGotCheese()) 
 { 
  north.x=mouse.x;north.y=mouse.y-1;
  south.x=mouse.x;south.y=mouse.y+1;
  west.x=mouse.x-1;west.y=mouse.y;
  east.x=mouse.x+1;east.y=mouse.y;
  min=9999;
  distance = CalcDistance(south,cheese);
  if(distance<min)
  {min=distance;dir=down;}
  
  distance=CalcDistance(north,cheese);
  if(distance<min)
  {min=distance;dir=up;}
  
  distance=CalcDistance(west,cheese);
  if(distance<min)
  {min=distance;dir=left;}
  
  distance=CalcDistance(east,cheese);
  if(distance<min)
  {min=distance;dir=right;}
  
  if(dir==right)
  {MAZE[mouse.y][mouse.x]=' ';
   mouse.x+=1;
   MAZE[mouse.y][mouse.x]='M';
  }
  else if(dir==up)
  {MAZE[mouse.y][mouse.x]=' ';
   mouse.y-=1;
   MAZE[mouse.y][mouse.x]='M';
  }
  else if(dir==down)
  {MAZE[mouse.y][mouse.x]=' ';
   mouse.y+=1;
   MAZE[mouse.y][mouse.x]='M';
  }
  else if(dir==left)
  {MAZE[mouse.y][mouse.x]=' ';
   mouse.x-=1;
   MAZE[mouse.y][mouse.x]='M';
  }
  DisplayMaze();     
  printf("Distance : %f\n",min);
  count++; 
  sleep(2);
}  
  return count;   
     }
int main()
{
  int sol;
                
  DisplayMaze(); 
  sleep(2);
  sol=SolveMaze();
  if(sol!=0)
  printf("\nMouse Got the Cheese in %d steps!!",sol);
  getch();
}
