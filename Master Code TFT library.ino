/*
 * Notes for Button and Joystick circuit
 * 
 * The space shows VIN; The following instructions are setup up 
 * from the right side of pins to left ending with the space then pin
 * 
 * Far right:
 * 
 * Gnd -> Gnd
 * A0 -> A0
 * A1 -> A1
 * A2 -> A2
 * D1 -> 2
 * P1 -> 3
 * D2 -> 8 //far left button
 * P2 -> 10
 * D3 -> 12 //far right button
 * P3 -> unkonw at moment out due to screen pins 6 or 11 are no longer avalable
 * VDD -> 5V
 * VIN -> VIN
 * const byte PIN_BUTTON_SELECT = 2; 
const byte PIN_BUTTON_RIGHT = 3;
const byte PIN_BUTTON_UP = 4;
const byte PIN_BUTTON_DOWN = 5;
const byte PIN_BUTTON_LEFT = 6;
const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;
 * I am not if all these pins are needed yet since the board have slots for
 * two joysticks and we are only using one.
 * 
 * 
 * 
 * https://www.virtuabotix.com/running-a-versalino-load-board-with-a-regular-arduino/
 * http://www.josephdattilo.com/writing-bluetooth-packet-based-sketch-versalino-control-board/
 * https://www.virtuabotix.com/arduino-gamepad-versalino-control-1-0-pin-usage/
 * 
 * 
 * 
 * 
 * 
 * 
 */

#include <SPI.h> // We'll use SPI to transfer data. Faster!
#include <TFT.h> // Calling the arduino graphical interface

#define cs   10
#define dc   9
#define rst  8
#define TFTscreenWidth 160
#define TFTscreenHeight 128

TFT TFTscreen = TFT(cs, dc, rst);

int pointX = TFTscreen.width() / 2;
int pointY = TFTscreen.height() / 2; // puts the pointer in the middle

const byte PIN_BUTTON_SELECT = 2; 

const byte PIN_BUTTON_RIGHT = 3;
const byte PIN_BUTTON_UP = 4;
const byte PIN_BUTTON_DOWN = 5;
const byte PIN_BUTTON_LEFT = 6;

const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;


void setup()
{
  Serial.begin(9600);
  pinMode(PIN_BUTTON_RIGHT, INPUT);
  pinMode(PIN_BUTTON_UP, INPUT);
  pinMode(PIN_BUTTON_LEFT, INPUT);
  pinMode(PIN_BUTTON_DOWN, INPUT);
  pinMode(PIN_BUTTON_SELECT, INPUT);

  randomSeed(analogRead(4));
  TFTscreen.begin();
  TFTscreen.background(255,255,255);
}

void loop()
{
  static int cursorX = 0;
  static int cursorY = 0;
  int choice;
  int buttonX = analogRead(PIN_ANALOG_X);
  int buttonY =  analogRead(PIN_ANALOG_Y);
  choice = menu(); //menu function call
  Serial.println("Made it back to menu");

  if(choice == 1)
  {
    TicTacToe(); 
  }
  else if(choice == 2)
  {
    Pong(); 
  }
  else
  {
    EtchaSketch();
  }  
}

int menu() //This will hold the call for the menu: from this function 
//each game will be called
{
  int buttonY;
  int buttonX;
  char * game1 = ">TIC-TAC-TOE";
  char * game2 = ">Etch-a-Sketch";
  char * game3 = ">PONG";
  int count=1;

  TFTscreen.stroke(0,0,0);
  TFTscreen.text("Game Menu", 12, 0);

  TFTscreen.text(game1, 0, 12);
  TFTscreen.text(" Etch-a-Sketch", 0, 22);
  TFTscreen.text(" PONG", 0, 32);
  
  for(int i =0; ; i++)
  { 
    int pressA;
    delay(200);
    pressA = digitalRead(PIN_BUTTON_RIGHT);
    if(pressA == LOW)
    {
       return count;
    }
    
    buttonY =  analogRead(A1);
    Serial.println(buttonY);
    if(buttonY < 500)
    {
      //delay(500);
      Serial.println(count);
      if( count == 1)
      {
        Serial.println("Made it into first if an count");
        count = 2;
        TFTscreen.background(255,255,255);
        TFTscreen.text("Game Menu", 12, 0);
        TFTscreen.text(" TIC-TAC-TOE", 0, 12);
        TFTscreen.text(game2, 0, 22);
        TFTscreen.text(" PONG", 0, 32);
        
        //delay(1000);
        do
        {
           pressA = digitalRead(PIN_BUTTON_RIGHT); 
          if(pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        }while( (buttonY >= 500) && (buttonY <= 550));
      }
      else if(count == 2)
      {
        count = 3;
        TFTscreen.background(255,255,255);
        TFTscreen.text("Game Menu", 12, 0);
        TFTscreen.text(" TIC-TAC-TOE", 0, 12);
        TFTscreen.text(" Etch-a-Sketch", 0, 22);
        TFTscreen.text(game3, 0, 32);
        do
        {
           pressA = digitalRead(PIN_BUTTON_RIGHT);
           Serial.println(pressA);
           
          if(pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
          Serial.println(buttonY);
        }while( (buttonY >= 500) && (buttonY <= 550));
      }
     else if(count == 3)
      {
        count = 1;
        TFTscreen.background(255,255,255);
        TFTscreen.text("Game Menu", 12, 0);
        TFTscreen.text(game1, 0, 12);
        TFTscreen.text(" Etch-a-Sketch", 0, 22);
        TFTscreen.text(" PONG", 0, 32);
       
        do
        {
           pressA = digitalRead(PIN_BUTTON_RIGHT); 
          if(pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        }while( (buttonY >= 500) && (buttonY <= 550));
      } 
    }

    else if (buttonY > 550)
    {
      //delay(500);
      if( count == 1)
      {
        count = 3;
        TFTscreen.background(255,255,255);
        TFTscreen.text("Game Menu", 12, 0);
        TFTscreen.text(" TIC-TAC-TOE", 0, 12);
        TFTscreen.text(" Etch-a-Sketch", 0, 22);
        TFTscreen.text(game3, 0, 32);
        
        do
        {
           pressA = digitalRead(PIN_BUTTON_RIGHT); 
          if(pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        }while( (buttonY >= 500) && (buttonY <= 550));
      }
      
      else if(count == 2)
      {
        count = 1;
        TFTscreen.background(255,255,255);
        TFTscreen.text("Game Menu", 12, 0);
        TFTscreen.text(game1, 0, 12);
        TFTscreen.text(" Etch-a-Sketch", 0, 22);
        TFTscreen.text(" PONG", 0, 32);
          
        do
        {
           pressA = digitalRead(PIN_BUTTON_RIGHT);
          if(pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        }while( (buttonY >= 500) && (buttonY <= 550));
      }
      
      else if(count == 3)
      {
        count = 2;
        TFTscreen.background(255,255,255);
        TFTscreen.text("Game Menu", 12, 0);
        TFTscreen.text(" TIC-TAC-TOE", 0, 12);
        TFTscreen.text(game2, 0, 22);
        TFTscreen.text(" PONG", 0, 32);

        do
        {
           pressA = digitalRead(PIN_BUTTON_RIGHT);
          if(pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        }while( (buttonY >= 500) && (buttonY <= 550));
      }
      }
    } 
  } 

void Pong()
{

  
}

void EtchaSketch()
{
  
  TFTscreen.begin();
  TFTscreen.background(255, 255, 255);   // make the background white
}

void draw()
{
  int xValue = analogRead(0);
  int yValue = analogRead(1); // reads the joystick values
delay(50);

  pointX = pointX + (map(xValue, 0, 1023, -2, 3)) / 2;
  pointY = pointY + (map(yValue, 1023, 0, -2, 2)) / 2;   // map the values and update the position

  if (pointX > 159) {
    (pointX = 159);
  }

  if (pointX < 0) {
    (pointX = 0);
  }
  if (pointY > 127) {
    (pointY = 127);
  }

  if (pointY < 0) {
    (pointY = 0);   // won't let you draw past the edge of the screen
  }

  TFTscreen.stroke(0, 0, 0);
  TFTscreen.rect(pointX, pointY, 2, 2); // declares the color and size of the pointer

  if (digitalRead(PIN_BUTTON_RIGHT) == LOW) {
    TFTscreen.background(255, 255, 255); // clears the screen if the button is pushed
  }
  
}

void TicTacToe()
{
  int buttonY;
  char ans;
  char player2;
  int x, y;
  char respo; //for the do while loop for continue game play
  char * b[3][3];
  char  *p1;
  char  *p2 ;
  char *empty;

   *p1='X';
   *p2='O';
   *empty= '\n';
  
  for(int i =0; i<3; i++)
  {
    for(int j=0; j<3; j++)
    {
        b[i][j] =empty;  
    }  
  }
  int count = 1;
  TFTscreen.background(255, 255, 255);
TFTscreen.text("Player 2:human or computer?",0,0);
TFTscreen.text("> C",0,22);
TFTscreen.text(" H",0,32);
TFTscreen.stroke(0,0,0);
TFTscreen.setTextSize(1);
  for (int j = 0; ; j++)
  {
    int pressA;
    delay(200);
    pressA = digitalRead(PIN_BUTTON_RIGHT);
    if (pressA == LOW)
    {
      player2 = 'C';
      goto stop;
    }
    buttonY =  analogRead(A1);
    if (buttonY < 500)
    {
      if (count = 1)
      {
        count = 2;
  TFTscreen.background(255, 255, 255);
TFTscreen.text("Player 2:human or computer?",0,0);
TFTscreen.text(" C",0,22);
TFTscreen.text("> H",0,32);
TFTscreen.stroke(0,0,0);
TFTscreen.setTextSize(1);
        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            player2 = 'H';
            goto stop;
          }
          buttonY =  analogRead(A1);
        } while ( (buttonY >= 500) && (buttonY <= 550));
      }
      else if (count = 2)
      {
        count = 1;
  TFTscreen.background(255, 255, 255);
TFTscreen.text("Player 2:human or computer?",0,0);
TFTscreen.text("> C",0,22);
TFTscreen.text(" H",0,32);
TFTscreen.stroke(0,0,0);
TFTscreen.setTextSize(1);
        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            player2 = 'C';
            goto stop;
          }
          buttonY =  analogRead(A1);
        } while ( (buttonY >= 500) && (buttonY <= 550));
      }
    }
  }
stop:

TFTscreen.background(255,255,255);
  if (player2 == 'H') // For two player humans
  {
    ans = EndGame(b);
    Printarray(b);
    while ( ans == 'c')
    {
TFTscreen.background(255,255,255);
      TFTscreen.text("Player 1: ",0,0);
      TFTscreen.stroke(0,0,0);
      TFTscreen.setTextSize(1);
      HumanMoves(x, y, b);
      b[x][y]=p1;
      Printarray(b);
      ans =EndGame(b);
      if (ans != 'c')
      {
        goto s;
      }
      TFTscreen.background(255,255,255);
      TFTscreen.text("Player 2: ",0,0);
      TFTscreen.stroke(0,0,0);
      TFTscreen.setTextSize(1);
      HumanMoves(x, y, b);
      b[x][y]=p2;
      Printarray(b);
      ans = EndGame(b);
    }
s:
    if (ans == 't')
    {
      TFTscreen.background(255,255,255);
      TFTscreen.text("It is a Tie!",0,32);
      TFTscreen.stroke(0,0,0);
      TFTscreen.setTextSize(1);
      delay(4000);
    }
    else if (ans == '1')
    {
      TFTscreen.background(255,255,255);
      TFTscreen.text("Player 1 Wins!",0,32);
      TFTscreen.stroke(0,0,0);
      TFTscreen.setTextSize(1);
      delay(4000);
    }
    else if (ans == '2')
    {
      TFTscreen.background(255,255,255);
      TFTscreen.text("Player 2 Wins!",0,32);
      TFTscreen.stroke(0,0,0);
      TFTscreen.setTextSize(1);
      delay(4000);
    }
  }

  if ( player2 == 'C') // For One human against computer
  {
    ans = EndGame(b);
    Printarray(b);

    while (ans == 'c')
    {
      TFTscreen.background(255,255,255);
      TFTscreen.text("Player 1: ",0,0);
      TFTscreen.stroke(0,0,0);
      TFTscreen.setTextSize(1);
      HumanMoves(x, y, b);
      b[x][y]=p1;
      Printarray(b);
      ans = EndGame(b);
      if (ans != 'c')
      {
        goto sto;
      }
      RandomMoves(b);
      Printarray(b);
      ans = EndGame(b);
    }
sto:
    if (ans == 't')
    {
      TFTscreen.background(255,255,255);
      TFTscreen.text("It is a Tie!",0,32);
      TFTscreen.stroke(0,0,0);
      TFTscreen.setTextSize(1);
      delay(4000);
    }
    else if (ans == '1')
    {
      TFTscreen.background(255,255,255);
      TFTscreen.text("Player 1 Wins!",0,32);
      TFTscreen.stroke(0,0,0);
      TFTscreen.setTextSize(1);
      delay(4000);
    }
    else if (ans == '2')
    {
      TFTscreen.background(255,255,255);
      TFTscreen.text("Player 2 Wins!",0,32);
      TFTscreen.stroke(0,0,0);
      TFTscreen.setTextSize(1);
      delay(4000);
    }
  }
}

void Printarray( char* b[3][3] )
{
   TFTscreen.stroke(255,255,255);
  char* a = b[0][0];
  char* c = b[0][1];
  char* d = b[0][2];
  char* e = b[1][0];
  char* f = b[1][1];
  char* g = b[1][2];
  char* h = b[2][0];
  char* i = b[2][1];
  char* j = b[2][2];
  //Row 1
  TFTscreen.text("+---+---+---+", 0, 0);
 TFTscreen.text("| ", 0, 12);   
  TFTscreen.text(a, 3, 12);      
  TFTscreen.text("| ", 6, 12);   
  TFTscreen.text(c, 14, 12); 
  TFTscreen.text("| ", 16, 12);   
  TFTscreen.text(d, 18, 12); 
  TFTscreen.text("| ", 20, 12);   
  TFTscreen.text("+---+---+---+", 0, 14); 
  TFTscreen.stroke(0,0,0);
  TFTscreen.setTextSize(1);
 
   //Row 2  
  TFTscreen.text("| ", 0, 22);   
  TFTscreen.text(e, 3, 22);      
  TFTscreen.text("| ", 6, 22);   
  TFTscreen.text(f, 14, 22); 
  TFTscreen.text("| ", 16, 22);   
  TFTscreen.text(g, 18, 22); 
  TFTscreen.text("| ", 20, 22);   
  TFTscreen.text("+---+---+---+", 0, 24); 
  TFTscreen.stroke(0,0,0);
  TFTscreen.setTextSize(1);

  //Row 3
  TFTscreen.text("+---+---+---+", 0, 0);
  TFTscreen.text("| ", 0, 32);   
  TFTscreen.text(h, 3, 32);      
  TFTscreen.text("| ", 6, 32);   
  TFTscreen.text(i, 14, 32); 
  TFTscreen.text("| ", 16, 32);   
  TFTscreen.text(j, 18, 32); 
  TFTscreen.text("| ", 20, 32);   
  TFTscreen.text("+---+---+---+", 0, 34); 
  TFTscreen.stroke(0,0,0);
  TFTscreen.setTextSize(1);
  delay(3000);
}

void HumanMoves( int& x, int& y, char * b[][3] )
{
  int count = 1;
  int pressA;
  int pressB;
  int buttonY;
int w ;
   int v ;
   char  *p1;
   char  *p2 ;

   *p1='X';
   *p2='Y';
   
   TFTscreen.text("Row: 1 ", 0, 38);
   TFTscreen.text("Column: 1 ", 0, 38);
   TFTscreen.stroke(0,0,0);
   TFTscreen.setTextSize(1);
  do
  {
    for (int i = 0; ; i++)
    {
      pressA = digitalRead(PIN_BUTTON_RIGHT);
      if (pressA == LOW)
      {
        x = 1;
        goto end;
      }
      buttonY =  analogRead(A1);
      if (buttonY < 500)
      {
        if (count == 1)
        {
          count = 2;
          TFTscreen.text("Row: 1 ",0,15);
          TFTscreen.stroke(255,255,255);
          TFTscreen.text("Row: 2 ",0,15);
          TFTscreen.stroke(0,0,0);
          TFTscreen.setTextSize(1);
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              x = 2;
              goto end;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 500) && (buttonY <= 550));
        }
        else if (count == 2)
        {
          count = 3;
          TFTscreen.text("Row: 2 ",0,15);
          TFTscreen.stroke(255,255,255);
          TFTscreen.text("Row: 3 ",0,15);
          TFTscreen.stroke(0,0,0);
          TFTscreen.setTextSize(1);
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              x = 3;
              goto end;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 500) && (buttonY <= 550));
        }
        else if (count == 3)
        {
          count = 1;
          TFTscreen.text("Row: 3 ",0,15);
          TFTscreen.stroke(255,255,255);
          TFTscreen.text("Row: 1 ",0,15);
          TFTscreen.stroke(0,0,0);
          TFTscreen.setTextSize(1);
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              x = 1;
              goto end;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 500) && (buttonY <= 550));
        }
      }
    }
    
end:


    for (int i = 0; ; i++)
    {
      pressA = digitalRead(PIN_BUTTON_RIGHT);
      if (pressA == LOW)
      {
        y = 1;
        goto end;
      }
      pressB = digitalRead(PIN_BUTTON_DOWN);
        if (pressB == HIGH)
        {
          HumanMoves(x,y,b);
        }
      buttonY =  analogRead(A1);
      if (buttonY < 500)
      {
        pressB = digitalRead(PIN_BUTTON_DOWN);
        if (pressB == HIGH)
        {
          HumanMoves(x,y,b);
        }
        if (count == 1)
        {
          count = 2;
          TFTscreen.text("Column: 1 ",0,25);
          TFTscreen.stroke(255,255,255);
          TFTscreen.text("Column: 2 ",0,25);
          TFTscreen.stroke(0,0,0);
          TFTscreen.setTextSize(1);
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              y = 2;
              goto done;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 500) && (buttonY <= 550));
        }
        else if (count == 2)
        {
          count = 3;
          TFTscreen.text("Column: 2 ",0,25);
          TFTscreen.stroke(255,255,255);
          TFTscreen.text("Column: 3 ",0,25);
          TFTscreen.stroke(0,0,0);
          TFTscreen.setTextSize(1);
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              y = 3;
              goto done;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 500) && (buttonY <= 550));
        }
        else if (count == 3)
        {
          count = 1;
          TFTscreen.text("Column: 3 ",0,25);
          TFTscreen.stroke(255,255,255);
          TFTscreen.text("Column: 1 ",0,25);
          TFTscreen.stroke(0,0,0);
          TFTscreen.setTextSize(1);
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              y = 1;
              goto done;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 500) && (buttonY <= 550));
        }
      }
    }
  done:
           w = x-1;
           v = y-1;
       
 }while((b[w][v] == p1) || (b[w][v] == p2)) ;  
  
}

void RandomMoves( char * board[][3] )
{
  char  *p1;
  char  *p2 ;
  *p1='X';
  *p2='O';
  int x = random(3); //Finds first random values of x and y between 1 and 3
  int y = random(3);
  
  while((board[x][y] == p1) || ( board[x-1][y-1] == p2))// If there is already a letter there it will enter loop
  {
    
    x = random(3); //It will keep looping until a new place is found without a letter
    y = random(3);
  }
   board[x][y]=p1;
}
char EndGame(char* b[][3]) // returns a t for tie, c for continue, 1 for player 1 won, 2 for player two won
{
  bool tieTest=true;
  char const tie='t';
  char const cont= 'c';
  char const p1w = '1';
  char const p2w = '2';
  char  *p1;
  char  *p2 ;
  char *empty;
  *empty = '\n';
  *p1='X';
  *p2='O';
  
  for(int i=0; i<3; i++) //Tests to see if it is a tie, at the end of all the if statements it will check if the bool is true
  {
    for(int j=0; j<3; j++)
    {
      if( b[i][j] == empty)//sets array to 0
      {
        tieTest = false;
      }
    }
  }
  
  //All of the following statements check to see if the various ways to win have happened
  
  if(b[0][0]==p1&&b[0][1]==p1&&b[0][2]==p1)
  {
    return p1w;
  }
  else if(b[0][0]==p2&&b[0][1]==p2&&b[0][2]==p2)
  {
    return p2w;
  }
  else if(b[1][0]==p1&&b[1][1]==p1&&b[1][2]==p1)
  {
    return p1w;
  }
  else if(b[1][0]==p2&&b[1][1]==p2&&b[1][2]==p2)
  {
    return p2w;
  }
  else if(b[2][0]==p1&&b[2][1]==p1&&b[2][2]==p1)
  {
    return p1w;
  }
  else if (b[2][0]==p2&&b[2][1]==p2&&b[2][2]==p2)
  {
    return p2w;
  }
  else if (b[0][0]==p1&&b[1][0]==p1&&b[2][0]==p1)
  {
    return p1w;
  }
  else if(b[0][0]==p2&&b[1][0]==p2&&b[2][0]==p2)
  {
    return p2w;
  }
  else if(b[0][1]==p1&&b[1][1]==p1&&b[2][1]==p1)
  {
    return p1w;
  }
  else if(b[0][1]==p2&&b[1][1]==p2&&b[2][1]==p2)
  {
    return p2w;
  }
  else if(b[0][2]==p1&&b[1][2]==p1&&b[2][2]==p1)
  {
    return p1w;
  }
  else if(b[0][2]==p2&&b[1][2]==p2&&b[2][2]==p2)
  {
    return p2w;
  }
  else if(b[0][0]==p1&&b[1][1]==p1&&b[2][2]==p1)
  {
    return p1w;
  }
  else if(b[0][0]==p2&&b[1][1]==p2&&b[2][2]==p2)
  {
    return p2w;
  }
  else if(b[0][2]==p1&&b[1][1]==p1&&b[2][0]==p1)
  {
    return p1w;
  }
  else if(b[0][2]==p2&&b[1][1]==p2&&b[2][0]==p2)
  {
    return p2w;
  }
  else if(tieTest) //Tests the previous set bool to check if a tie has been made
  {
    return tie;
  }
  else  //If no other conditions return first then the game can continue
    return cont;//there is no win. 

    return tie;
  
}
