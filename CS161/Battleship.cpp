#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

class Board
{
   public:

      struct Ship
      {
	 string stype;
	 int itype,spots,used;

      };
      int board[10][10];
      char col, dir;
      int row,irow, icol,inShip;
      Ship Car, Bat, Des, Sub, Pat;
      
      struct Ship{
	 int *itype, *spots, *used;
      }TheShip;
      Board();//instructor to initialize the ship
};


Board::Board()
{
   Car.stype = "Aircarft Carrier"; Car.itype=1; Car.spots=5; Car.used=0;
   Bat.stype = "Battleship"; Bat.itype=2; Bat.spots=4; Bat.used=0;
   Des.stype = "Destroyer"; Des.itype=3; Des.spots=3; Des.used=0;
   Sub.stype = "Submarine"; Sub.itype=4; Sub.spots=3; Sub.used=0;
   Pat.stype = "Patrol Boat"; Pat.itype=5; Pat.spots=2; Pat.used=0;
}



//Resetting the battle boards
void BoardReset(Board &p1, Board &p2)
{
   int y =10, x=10;
   for(int j=0; j<y; j++)
   {
      for(int i=0; i<x; i++)
      {
	 p1.board[y][x] = 0;
	 p2.board[y][x] = 0;
      }
   }
}

//Printing the board
void BoardPrint(int board[][10] )
{
   int y =10, x=10;
   cout<<"   A B C D E F G H I J "<<endl;
   for(int j=0; j<y; j++)
   {
      if(j<(y-1))
	 cout<<j+1<<"  ";
      else
	 cout<<j+1<<" ";
      for(int i=0; i<x; i++)
      {
	 cout<<board[y][x]<<" ";  //print array
      }
      cout<<"\n";
   }
}

//Print ship information
void ShipInfo()
{
   cout<<"Please choose a ship: \n [1] Aircraft Carrier - 5 spots\n [2] Battleship - 4 spots\n [3] Destroyer - 3 spots\n [4] Submarine - 3 spots\n [5] Patrol Boat -2 spots\n What ship would you like to put on a board?"<<endl;
}

//Change the input into an integer (Board grid)
void iInputX(Board &p) //interpret from letter to a number
{
   if(p.col=='a'||p.col=='A')
      p.icol=1;
   else if(p.col=='b'||p.col=='B')
      p.icol=2;
   else if(p.col=='c'||p.col=='C')
      p.icol=3;
   else if(p.col=='d'||p.col=='D')
      p.icol=4;
   else if(p.col=='e'||p.col=='E')
      p.icol=5;
   else if(p.col=='f'||p.col=='F')
      p.icol=6;
   else if(p.col=='g'||p.col=='G')
      p.icol=7;
   else if(p.col=='h'||p.col=='H')
      p.icol=8;
   else if(p.col=='i'||p.col=='I')
      p.icol=9;
   else if(p.col=='j'||p.col=='J')
      p.icol=10;
}

//Ask for input
void Input(Board &p)
{
   cout<<"Please insert a row [A-J]"<<endl;
   cin>>p.row;
   cout<<"Please insert a column [1-10]"<<endl;
   cin>>p.col;
   p.irow = p.row;
   iInputX(p);
}

//Check if the ship lies outside the bound
bool ShipBound(Board &p)
{
   if(p.dir=='N'||p.dir=='n'||p.dir=='W'||p.dir=='w') //if ship lies toward north or west
   {
      if((p.irow-p.TheShip.spots)<0||(p.icol-p.TheShip.spots)<0)
      {
	 cout<<"\n*** Error: Ship out of boundary ***\n"<<endl;
	 return (1==1);
      }
      else
	 return (1==0);
   }
   if(p.dir=='S'||p.dir=='s') //if ship lies toward south or east
   {
      if((p.irow+p.TheShip.spots)>11||(p.icol+p.TheShip.spots)>11)
      {
	 cout<<"\n*** Error: Ship out of boundary ***\n"<<endl;
	 return (1==1);
      }
      else
	 return (1==0);
   }
}

//Matching the ship
Board::Ship ShipMatch(int inShip, Board &p) //I suppose to funciton to set the point "TheShip" point to a struct that is chosen, so it can act as a struct of Car,Bat,Des,Sub,Pat itself.
{
   switch (inShip)
   {
      case 1:
	 {
	    p.TheShip = &(p.Car); 
	    p.TheShip.itype = &(p.Car.itype);
	    p.TheShip.spots = &(p.Car.spots);
	    p.TheShip.used  = &(p.Car.used);
	    break;
	 }
      case 2:
	 {
	    p.TheShip = &(p.Bat);
	    p.TheShip.itype = &(p.Bat.itype);
	    p.TheShip.spots = &(p.Bat.spots);
	    p.TheShip.used  = &(p.Bat.used);
	    break;
	 }
      case 3:
	 {
	    p.TheShip = &(p.Des);
	    p.TheShip.itype = &(p.Des.itype);
	    p.TheShip.spots = &(p.Des.spots);
	    p.TheShip.used  = &(p.Des.used);
	    break;
	 }
      case 4:
	 {
	    p.TheShip = &(p.Sub);
	    p.TheShip.itype = &(p.Sub.itype);
	    p.TheShip.spots = &(p.Sub.spots);
	    p.TheShip.used  = &(p.Sub.used);
	    break;
	 }
      case 5:
	 {
	    p.TheShip = &(p.Pat);
	    p.TheShip.itype = &(p.Pat.itype);
	    p.TheShip.spots = &(p.Pat.spots);
	    p.TheShip.used  = &(p.Pat.used);
	    break;
	 }
   }

}

//Check if the ship has been used
void ShipDup(Board &p)
{
   do{
      if(p.TheShip.used==1)
	 cout<<"The Ship has been used"<<endl;
      ShipInfo();
      cin>> p.inShip;
      ShipMatch(p.inShip, Board &p); // I suppose the ShipMatch to  return the struct address of the ship that matched so I can pass it to other function.   
   }while(p.TheShip.used==1);   
   p.TheShip.used=1;   
}

void ShipSetting(Board &p);

//Ask What direction to place a ship
void ShipDirect(Board &p)
{
   bool t;
   cout<<"What direction to put a ship?\n[N] North  [E] East  [W] West  [S] South"<<endl;
   cin>>p.dir;
   t=ShipBound(p);
   if(t)
   {
      ShipSetting(p);
   }  
}

void ShipPlacing(Board &p) //placing the ship on the board  
   //This function is tricky and I don't know how to deal with it because I    have to deal with class and struct inside the class.
{
   if(p.dir=='n'||p.dir=='N')
   {
      for(int i=0;i<p.TheShip.spots-1;i++) //I would like the struct whatever that was returned from ShipMatch() to go in the place called TheShip in p.Ship.spots so that I can test the value.
      {
	 p.board[p.irow-i][p.icol]=p.TheShip.itype;
      }
   }

   if(p.dir=='s'||p.dir=='S')
   {
      for(int i=0;i<p.TheShip.spots-1;i++)
      {
	 p.board[p.irow+i][p.icol]=p.TheShip.itype;
      }
   }

   if(p.dir=='w'||p.dir=='W')
   {
      for(int i=0;i<p.TheShip.spots-1;i++)
      {
	 p.board[p.irow][p.icol-i]=p.TheShip.itype;
      }
   }

   if(p.dir=='s'||p.dir=='S')
   {
      for(int i=0;i<p.TheShip.spots-1;i++)
      {
	 p.board[p.irow][p.icol+1]=p.TheShip.itype;
      }
   }
}

bool AllShip(Board &p)//check if all the ships are used
{
   if(p.Car.used==1&&p.Bat.used==1&&p.Des.used==1&&p.Sub.used==1&&p.Pat.used==1)
      return (1==1);
   else
      return (0==1);
}

bool ShipStack(Board &p)
{
   
}

//Where to put the ship in the board
void ShipSetting(Board &p) //the object that was passed now name p
{
   bool r,e;
   do{
      do{
      ShipDup(p);
      Input(p);
      ShipDirect(p);
      e=ShipBound(p);
      }while(e)
      ShipPlacing(p,p.TheShip);
   r = AllShip(p);
   }while(r);
}

int main()
{
   Board p1, p2;
   BoardReset(p1, p2); //first method of passing --passing object
   BoardPrint(p1.board);  //second method of passing --passing board
   ShipSetting(p2);
   cout<<p2.row<<endl;
   cout<<p2.col<<endl;


   return 0;
}
