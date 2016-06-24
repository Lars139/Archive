/*************************************************
 * Program: Battleship1
 * Author: Rattanai Sawaspanich
 * Date: 10 Dec 2012, 2:43 am
 * Description: A program that allows you to play battleship
 * Input:  integer, chracter, string?
 * Output: matrix of 10x10 (board)
 *         int from 1 to 5 (ships)
 *         sring says "hit" or "miss" and error
 *************************************************/
/************************************************
 * Function:  All functions are declared in class Board
 * Description: all of the variable in class are private only function can access the variables
 * Parameters: see in class Board
 * Pre-condition: none
 * Post-condition: display result may be a little bit confusing
 *************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

class Board
{
   public:
      Board();//instructor to initialize the ship

      struct Ship
      {
	 string stype;
	 int itype,spots;
	 bool used;

      };

      //Functions in wonder land
      void BoardReset();
      void BoardPrint();
      void ShipInfo();
      void iInputX();
      void Input();
      bool ShipBound();
      void ShipDup();
      void ShipSetting();
      int  P2Ship(Board &p1, Board &p2);
      void ShipDirect();
      void ShipPlacingNS();
      void ShipPlacingEW();
      bool AllShip();
      bool ShipStackNS(int d);
      bool ShipStackEW(int d);
      bool Hit();
      void Attack(Board &p);
      void SunkShip();
      bool CheckI(string InI);
      bool CheckC(char InC);
      bool CheckS(char InS);
      // bool Turn(int *turn);  declare in global
      bool GG(int &turn);
      void BoardCPrint();
      void BoardCReset();


      Ship *ShipMatch(int inShip);

   private:
      int board[10][10];
      char boardC[10][10];
      char col, dir;
      int row,irow, icol,inShip;
      Ship Car, Bat, Des, Sub, Pat;
      Ship *TheShip;      
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
void Board::BoardReset()
{
   int y =10, x=10;
   for(int j=0; j<y; j++)
   {
      for(int i=0; i<x; i++)
      {
	 board[j][i] = 0;
      }
   }
   BoardCReset();
}

//Printing the input  board
void Board:: BoardPrint()
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
	 if(board[j][i]!=0)
	    cout<<board[j][i]<<" ";  //print array
	 else
	    cout<<"  ";
      }
      cout<<"\n";
   }
}


//Resetting the interface boards
void Board::BoardCReset()
{
   int y =10, x=10;
   for(int j=0; j<y; j++)
   {
      for(int i=0; i<x; i++)
      {
	 boardC[j][i] = ' ';
      }
   }
}
//Print hit or miss board
void Board:: BoardCPrint()
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
	 cout<<boardC[j][i]<<" ";  //print array
      }
      cout<<"\n";
   }
}

//Allow 2nd player to put ships down
int Board::P2Ship(Board &p1, Board &p2)
{
   int r=0;
   if(p1.Car.used ==1 && p1.Bat.used==1 && p1.Des.used==1 && p1.Sub.used==1 && p1.Pat.used==1)
   {
      r=1; //if player 1 has placed all the ships
   }
   if(r==1 && p2.Car.used ==1 && p2.Bat.used==1 && p2.Des.used==1 && p2.Sub.used==1 && p2.Pat.used==1)
      r=2; //palyer 2 has placed all the ships
   return r;
}

//Print ship information
void Board::ShipInfo()
{

   BoardPrint();
   cout<<"\n Please choose a ship: \n [1] Aircraft Carrier - 5 spots\n [2] Battleship - 4 spots\n [3] Destroyer - 3 spots\n [4] Submarine - 3 spots\n [5] Patrol Boat -2 spots\n What ship would you like to put on a board?"<<endl;
}

//Change the input into an integer (Board grid)
void Board::iInputX() //interpret from letter to a number
{
   if(col=='a'||col=='A')
      icol=0;
   else if(col=='b'||col=='B')
      icol=1;
   else if(col=='c'||col=='C')
      icol=2;
   else if(col=='d'||col=='D')
      icol=3;
   else if(col=='e'||col=='E')
      icol=4;
   else if(col=='f'||col=='F')
      icol=5;
   else if(col=='g'||col=='G')
      icol=6;
   else if(col=='h'||col=='H')
      icol=7;
   else if(col=='i'||col=='I')
      icol=8;
   else if(col=='j'||col=='J')
      icol=9;
}

//Check input type if it is an integer
bool Board::CheckI(string InI)
{
   bool r=1;
   if(InI=="1"||InI=="2"||InI=="3"||InI=="4"||InI=="5"||InI=="6"||InI=="7"||InI=="8"||InI=="9"||InI=="10")
   {
      row = atoi(InI.c_str());
   }
   else
   {
      cout<<"*** Error: Please enter a valid integer ***\n";
      r=0;
   }
   return r;
}

//Check if input is a valid number of ship 
bool Board::CheckS(char InS)
{
   bool r=1;
   if(InS=='1'||InS=='2'||InS=='3'||InS=='4'||InS=='5')
   {
      if(InS=='1')
	 inShip = 1;
      else if(InS=='2')
	 inShip = 2;
      else if(InS=='3')
	 inShip = 3;
      else if(InS=='4')
	 inShip = 4;
      else if(InS=='5')
	 inShip = 5;
      r=1;
   }
   else
   {
      cout<<"\n\n*** Error: Please enter a valid ship number ***\n\n";
      r=0;
   }
   return r;
}

//Check if input is a valid alphabet
bool Board::CheckC(char InC)
{
   if(InC=='a'||InC=='A'||InC=='b'||InC=='B'||InC=='c'||InC=='C'||InC=='d'||InC=='D'||InC=='e'||InC=='E'||InC=='f'||InC=='F'||InC=='g'||InC=='G'||InC=='h'||InC=='H'||InC=='i'||InC=='I'||InC=='j'||InC=='J')
      return 1;
   else
   {
      cout<<"*** Error: Please enter a valid alphabet ***\n";
      return 0;
   }
}

//Ask for input
void Board::Input()
{
   char InC;
   string InI;
   bool r;
   do{
      cout<<"Please insert a column [A-J]"<<endl;
      cin>>InC;
      r=CheckC(InC);
      if(r)
	 col=InC;
   }while(!r);
   do{
      cout<<"Please insert a row [1-10]"<<endl;
      cin>>InI;
      r=CheckI(InI);
      if(r)
      {
	 irow = row-1;
	 iInputX();
      }
   }while(!r);
}

//Check if the ship lies outside the bound
bool Board::ShipBound()
{
   if(dir=='N'||dir=='n') //if ship lies toward north or west
   {
      if((irow-TheShip->spots)<0)
      {
	 cout<<"\n*** Error: Ship out of North boundary ***\n"<<endl;
	 TheShip->used=0;
	 return (1==1);
      }
      else
	 return (1==0);
   }

   else if(dir=='W'||dir=='w') //if ship lies toward north or west
   {
      if((icol-TheShip->spots)<0)
      {
	 cout<<"\n*** Error: Ship out of West boundary ***\n"<<endl;
	 TheShip->used=0;
	 return (1==1);
      }
      else
	 return (1==0);
   }

   else if(dir=='S'||dir=='s') //if ship lies toward south or east
   {
      if((irow+TheShip->spots)>11)
      {
	 cout<<"\n*** Error: Ship out of South boundary ***\n"<<endl;
	 TheShip->used=0;
	 return (1==1);
      }
      else
	 return (1==0);
   }
   else if(dir=='E'||dir=='e') //if ship lies toward south or east
   {
      if((icol+TheShip->spots)>11)
      {
	 cout<<"\n*** Error: Ship out of East boundary ***\n"<<endl;
	 TheShip->used=0;
	 return (1==1);
      }
      else
	 return (1==0);
   }
}

//Matching the ship  and return the ship struck to be stored in *TheShip
Board::Ship * Board::ShipMatch(int inShip) 
{
   switch (inShip)
   {
      case 1:
	 {
	    return &(Car);
	    break;
	 }
      case 2:
	 {
	    return &(Bat);
	    break;
	 }
      case 3:
	 {
	    return &(Des);
	    break;
	 }
      case 4:
	 {
	    return &(Sub);
	    break;
	 }
      case 5:
	 {
	    return &(Pat);
	    break;
	 }
   }

}

//Check if the ship has been used
void Board::ShipDup()
{
   bool k,r;
   char InS;
   do{

      k=0; 
      do{
	 ShipInfo(); //print out the ship info and ask what kind of ship the user want (store in int tyep)
	 cin>>InS;
	 r=CheckS(InS);
      }while(!r);

      TheShip = ShipMatch(inShip); //return the struct addresss of the ship.
      if(TheShip->used!=0)
      {
	 cout<<"\n\n *** Error: The "<<TheShip->stype<<" has been used. ***\n"<<endl;
	 TheShip->used =1;
	 k=1;
      }
      TheShip->used = 1; 
   }while(k);

}


//Ask What direction to place a ship
/*void Board::ShipDirect()
  {
  bool t;
  cout<<"What direction to put a ship?\n[N] North  [E] East  [W] West  [S] South"<<endl;
  cin>>dir;
  t=ShipBound();
  if(t)
  {
  ShipSetting();
  }  
  }*/

//Check if ship stack on top of each other
bool Board::ShipStackNS(int d) //check for the north and south; recieve 'd' to multiply to control direction of N or S.
{
   int c=0, co,ro;
   for(int i=0;i<TheShip->spots;i++)
   {
      if(board[irow-(i*d)][icol]==0)
      {
	 c++;
      }
      else
      {
	 co = icol;
	 ro = (irow -(i*d));
      }
   }
   if(c==TheShip->spots)
   {
      return (1);//if ship doesn't stack return true
   }
   else
   {
      cout<<"\n\n *** Error: "<<TheShip->stype<<" cannot be placed at ("<<col<<","<<ro+1<<") ***\n"<<endl;
      TheShip->used=0;
      return (0); //if ship stack return false
   }
}

bool Board::ShipStackEW(int d) //check for the East and West ; recieve 'd' to multiply to control direction of E or W.
{
   int c=0, co,ro ;
   for(int i=0;i<TheShip->spots;i++)
   {
      if(board[irow][icol+(i*d)]==0)
      {
	 c++;
      }
      else
      {
	 co = (icol+(i*d));
	 ro = irow;
      }
   }
   if(c==TheShip->spots)
      return (1); //if ship doesn't stack return true.
   else
   {
      cout<<"\n\n *** Error: "<<TheShip->stype<<" cannot be placed at ("<<col<<","<<ro+1<<")"<<endl;
      TheShip->used=0;
      return (0);//if ship stacks return flase
   }
}


//Placing Ships
void Board::ShipPlacingNS() //placing the ship on the board in direction of N and S.
{
   int d=0; bool SS;
   if(dir=='n'||dir=='N')
      d=1;
   if(dir=='s'||dir=='S')
      d = -1;
   if(d==-1||d==1)
   {
      SS=ShipStackNS(d);
      if(SS)//if ship doesn't go on top of other ship, place it.
      {
	 for(int i=0;i<TheShip->spots;i++) 
	 {
	    board[irow-(i*d)][icol]=TheShip->itype;
	 }
      }
   }
   else
   {
      cout<<"Please enter a valid direction";
   }
}


void Board::ShipPlacingEW() //placing the ship on the board in direction of E and W.
{
   int d=0; bool SS;
   if(dir=='e'||dir=='E')
      d=1;
   if(dir=='w'||dir=='W')
      d = -1;
   if(d==-1||d==1)
   {
      SS=ShipStackEW(d);
      if(SS) //if ship doesn't go on top of other place the ship
      {
	 for(int i=0;i<TheShip->spots;i++)
	 {
	    board[irow][icol+(i*d)]=TheShip->itype; ///need to look at*****
	 }
      }
   }
   else
   {
      cout<<"Please enter a valid direction";
   }
}


bool Board::AllShip()//check if all the ships are used
{
   if(Car.used==1&&Bat.used==1&&Des.used==1&&Sub.used==1&&Pat.used==1)
      return (1==1);
   else
      return (0==1);
}


//Where to put the ship in the board
void Board::ShipSetting() //the object that was passed now name p
{
   bool r,e ;
   do{
      do{
	 ShipDup();
	 Input();
	 do{
	    cout<<"What direction to put a ship?\n[N] North  [E] East  [W] West  [S] South"<<endl;
	    cin>>dir;
	 }while(!(dir=='n'||dir=='N'||dir=='s'||dir=='S'||dir=='w'||dir=='W'||dir=='e'||dir=='E'));
	 e=ShipBound();
      }while(e);
      if(dir=='s'||dir=='S'||dir=='n'||dir=='N') 
	 ShipPlacingNS();
      else if(dir=='e'||dir=='E'||dir=='w'||dir=='W')
	 ShipPlacingEW();
      r=AllShip();
   }while(!r);

}



bool Turn(int &turn)
{

   if((turn)%2==0)
   {
      (turn)++;
      return(0); // false if it is an even number
   }
   else 
   {
      (turn)++;
      return(1); // true if it's an odd number
   }
}




//Check if the game is over
bool Board::GG(int &turn)
{
   int left=0;
   int y =10, x=10;
   for(int j=0; j<y; j++)
   {
      for(int i=0; i<x; i++)
      {
	 if(board[j][i]< 0)
	    left++;
      }
   }
   if(left==17)
      return (0);
   else
      return (1);

}


//Check if the ship is sunk
void Board::SunkShip()
{
   if(TheShip->spots<=0)
   {
      cout<<"\n\n >>>  You have sunk the "<<TheShip->stype<<" <<<\n\n"<<endl;

   }
}

//Check if it hits a ship
bool Board::Hit()
{
   int dmg;
   bool r;
   if(board[irow][icol]==0)
   {
      boardC[irow][icol]='O';
      cout<<"\n\n  Miss \n \n"<<endl;
      r=0;
   }
   else
   {
      if(board[irow][icol]>0)
      {
	 dmg = board[irow][icol];
	 TheShip=ShipMatch(dmg);
	 board[irow][icol] *= -1;
	 TheShip->spots -=1;
	 boardC[irow][icol]='X';
	 r=0;
	 cout<<"\n\n ** Hit ** \n\n"<<endl;
	 SunkShip();
      }
      else
      {
	 cout<<"\n\n\n*** Error: You have already hit this spot ***\n\n\n\n";
	 r=1;
      }
   }
   return r;
}

//Begin to attck ship
void Board::Attack(Board &p) //passing the board of opponent
{
   bool r;
   do{
      p.BoardCPrint();
      cout<<"\n\n\nSelect target:"<<endl;
      p.Input(); //input will be stored in irow, icol.
      r=p.Hit();
   }while(r);


}


int main()
{
   bool r, gg, rTurn;
   int turn=1,n;
   Board p1, p2;
   cout<<"\n\n Player 1's Turn to place ships\n\n";
   p1.BoardReset(); //first method of passing --passing object
   p1.ShipSetting();
   cout<<"\n\n Player 2 Turn to place ships\n\n";
   p2.BoardReset();
   p2.ShipSetting();

   do{
      rTurn = Turn(turn);
      if(rTurn)
      {
	 cout<<"\nPlayer 1 turn\n";
	 p1.Attack(p2);
	 gg=p2.GG(turn);
	 n=1;
      }
      else
      {
	 cout<<"\nPlayer 2 turn\n";
	 p2.Attack(p1);
	 gg=p1.GG(turn);
	 n=2;
      }
   }while(gg);
   cout<<"\n             ### Player "<<n<<" has won the game ###\n\n\n";

   return 0;
}
