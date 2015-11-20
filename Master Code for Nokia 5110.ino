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
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define screenHeight 48
#define screenHeight 84
#define scePin  7  // SCE - Chip select, pin 3 on LCD.
#define rstPin 6  // RST - Reset, pin 4 on LCD.
#define dcPin 5   // DC - Data/Command, pin 5 on LCD.
#define sdinPin  11  // DN(MOSI) - Serial data, pin 6 on LCD.
#define sclkPin 13  // SCLK - Serial clock, pin 7 on LCD.
#define blPin 8// LED - Backlight LED, pin 8 on LCD.

Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 5, 7, 6);

const byte PIN_BUTTON_SELECT = 2;

const byte PIN_BUTTON_RIGHT = 3;
const byte PIN_BUTTON_UP = 4;
const byte PIN_BUTTON_DOWN = 5;
const byte PIN_BUTTON_LEFT = 6;

const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_BUTTON_RIGHT, INPUT);
  pinMode(PIN_BUTTON_UP, INPUT);
  pinMode(PIN_BUTTON_LEFT, INPUT);
  pinMode(PIN_BUTTON_DOWN, INPUT);
  pinMode(PIN_BUTTON_SELECT, INPUT);

  randomSeed(analogRead(4));
  display.begin();
  display.clearDisplay();
  display.setContrast(70);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(12,14);
  display.println("B3 SYSTEMS");
  display.display();
  delay(2000);
  
  
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
  display.clearDisplay();
  display.display();

  if (choice == 1)
  {
    TicTacToe();
  }
  else if (choice == 2)
  {
    Pong();
  }
  else
  {
    Snake();
  }
  
}

int menu() //This will hold the call for the menu: from this function
//each game will be called
{
  int buttonY;
  int buttonX;
  char * game1 = ">TIC-TAC-TOE";
  char * game2 = ">SNAKE";
  char * game3 = ">PONG";
  int count = 1;

  display.clearDisplay();
  display.display();
  
  display.setCursor(12,0);
  display.println("Game Menu");
  
  display.setCursor(0,12);
  display.println(game1);
  display.setCursor(0,22);
  display.println(" SNAKE");
  display.setCursor(0,32);
  display.println(" PONG");
  display.display();
  for (int i = 0; ; i++)
  {
    int pressA;
    delay(200);
    pressA = digitalRead(PIN_BUTTON_RIGHT);
    if (pressA == LOW)
    {
      return count;
    }

    buttonY =  analogRead(A1);
    Serial.println(buttonY);
    if (buttonY < 300)
    {
      //delay(500);
      Serial.println(count);
      if ( count == 1)
      {
        Serial.println("Made it into first if an count");
        count = 2;

        display.clearDisplay();
        display.setCursor(12,0);
        display.println("Game Menu");
        display.setCursor(0,12);
        display.println(" TIC-TAC-TOE");
        display.setCursor(0,22);
        display.println(game2);
        display.setCursor(0,32);
        display.println(" PONG");
        display.display();
        //delay(1000);
        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        } while ( (buttonY >= 300) && (buttonY <= 400));
      }
      else if (count == 2)
      {
        count = 3;
        display.clearDisplay();
        display.setCursor(12,0);
        display.println("Game Menu");
        display.setCursor(0,12);
        display.println(" TIC-TAC-TOE");
        display.setCursor(0,22);
        display.println(" SNAKE");
        display.setCursor(0,32);
        display.println(game3);
        display.display();
        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          Serial.println(pressA);

          if (pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
          Serial.println(buttonY);
        } while ( (buttonY >= 300) && (buttonY <= 400));
      }
      else if (count == 3)
      {
        count = 1;
        display.clearDisplay();
        display.setCursor(12,0);
        display.println("Game Menu");
        display.setCursor(0,12);
        display.println(game1);
        display.setCursor(0,22);
        display.println(" SNAKE");
        display.setCursor(0,32);
        display.println(" PONG");
        display.display();

        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        } while ( (buttonY >= 300) && (buttonY <= 400));
      }
    }

    else if (buttonY > 400)
    {
      //delay(500);
      if ( count == 1)
      {
        count = 3;
        display.clearDisplay();
        display.setCursor(12,0);
        display.println("Game Menu");
        display.setCursor(0,12);
        display.println(" TIC-TAC-TOE");
        display.setCursor(0,22);
        display.println(" SNAKE");
        display.setCursor(0,32);
        display.println(game3);
        display.display();

        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        } while ( (buttonY >= 300) && (buttonY <= 400));
      }

      else if (count == 2)
      {
        count = 1;
        display.clearDisplay();
        display.setCursor(12,0);
        display.println("Game Menu");
        display.setCursor(0,12);
        display.println(game1);
        display.setCursor(0,22);
        display.println(" SNAKE");
        display.setCursor(0,32);
        display.println(" PONG");
        display.display();

        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        } while ( (buttonY >= 300) && (buttonY <= 400));
      }

      else if (count == 3)
      {
        count = 2;

        display.clearDisplay();
        display.setCursor(12,0);
        display.println("Game Menu");
        display.setCursor(0,12);
        display.println(" TIC-TAC-TOE");
        display.setCursor(0,22);
        display.println(game2);
        display.setCursor(0,32);
        display.println(" PONG");
        display.display();

        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        } while ( (buttonY >= 300) && (buttonY <= 400));
      }
    }
  }
}

void Pong()
{


}

void Snake()
{


}

void TicTacToe()
{
  int buttonY;
  char ans;
  char player2;
  int x, y;
  char respo; //for the do while loop for continue game play
  char b[3][3];
  for(int i =0; i<3; i++)
  {
    for(int j=0; j<3; j++)
    {
        b[i][j] ='\n';  
    }  
  }
  int count = 1;
  display.clearDisplay();
  display.display();
  display.setCursor(0,0);
  display.println("Player 2:human or computer?");
  display.setCursor(0,22);
  display.println("> C");
  display.setCursor(0,32);
  display.println(" H");
  display.display();
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
    if (buttonY < 300)
    {
      if (count = 1)
      {
        count = 2;
         display.clearDisplay();
        display.setCursor(0,0);
        display.println("Player 2:human or computer?");
        display.setCursor(0,22);
        display.println("  C");
        display.setCursor(0,32);
        display.println("> H");
        display.display();
        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            player2 = 'H';
            goto stop;
          }
          buttonY =  analogRead(A1);
        } while ( (buttonY >= 300) && (buttonY <= 400));
      }
      else if (count = 2)
      {
        count = 1;
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("Player 2:human or computer?");
        display.setCursor(0,22);
        display.println("> C");
        display.setCursor(0,32);
        display.println("  H");
        display.display();
        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            player2 = 'C';
            goto stop;
          }
          buttonY =  analogRead(A1);
        } while ( (buttonY >= 300) && (buttonY <= 400));
      }
    }
  }
stop:

  display.clearDisplay();
  if (player2 == 'H') // For two player humans
  {
    ans = EndGame(b);
    Printarray(b);
    while ( ans == 'c')
    {
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("Player 1: ");
      display.display();
      HumanMoves(x, y, b);
      b[x][y]='X';
      Printarray(b);
      ans =EndGame(b);
      if (ans != 'c')
      {
        goto s;
      }
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("Player 2: ");
      display.display();
      HumanMoves(x, y, b);
      b[x][y]='O';
      Printarray(b);
      ans = EndGame(b);
    }
s:
    if (ans == 't')
    {
      display.clearDisplay();
      display.setCursor(0,32);
      display.println("It is a Tie!");
      display.display();
      delay(4000);
    }
    else if (ans == '1')
    {
      display.clearDisplay();
      display.setCursor(0,32);
      display.println("Player 1 Wins!");
      display.display();
      delay(4000);
    }
    else if (ans == '2')
    {
      display.clearDisplay();
      display.setCursor(0,32);
      display.println("Player 2 Wins!");
      display.display();
      delay(4000);
    }
  }

  if ( player2 == 'C') // For One human against computer
  {
    ans = EndGame(b);
    Printarray(b);

    while (ans == 'c')
    {
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("Player 1: ");
      display.display();
      HumanMoves(x, y, b);
      b[x][y]='X';
      Printarray(b);
      ans = EndGame(b);
      if (ans != 'c')
      {
        goto sto;
      }
      RandomMoves(x, y, b);
      Printarray(b);
      ans = EndGame(b);
    }
sto:
    if (ans == 't')
    {
      display.clearDisplay();
      display.setCursor(0,32);
      display.println("It is a Tie!");
      display.display();
      delay(4000);
    }
    else if (ans == '1')
    {
      display.clearDisplay();
      display.setCursor(0,32);
      display.println("Player 1 Wins!");
      display.display();
      delay(4000);
    }
    else if (ans == '2')
    {
      display.clearDisplay();
      display.setCursor(0,32);
      display.println("Player 2 Wins!");
      display.display();
      delay(4000);
    }
  }
}

void Printarray( char b[3][3] )
{
  //Row 1
  display.setTextSize(0.1);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("+---+---+---+");
  display.setCursor(0,10);
  display.println("| ");
  display.setCursor(10,8);
  display.println(b[0][0]);
  display.setCursor(24,10);
  display.println("| ");
  display.setCursor(36,8);
  display.println(b[0][1]);
  display.setCursor(48,10);
  display.println("| ");
  display.setCursor(60,8);
  display.println(b[0][2]);
  display.setCursor(72,10);
  display.println("| ");
  display.setCursor(0,14);
  display.println("+---+---+---+");

  //Row 2
  display.setCursor(0,22);
  display.println("| "); 
  display.setCursor(10,22);
  display.println(b[1][0]);
  display.setCursor(24,22);
  display.println("| ");
  display.setCursor(36,22);
  display.println(b[1][1]);
  display.setCursor(48,22);
  display.println("| ");
  display.setCursor(60,22);
  display.println(b[1][2]);
  display.setCursor(72,22);
  display.println("| ");
  display.setCursor(0,28);
  display.println("+---+---+---+");

  //Row 3
  display.setCursor(0,38);
  display.println("| ");
  display.setCursor(10,35);
  display.println(b[2][0]);
  display.setCursor(24,38);
  display.println("| ");
  display.setCursor(36,35);
  display.println(b[2][1]);
  display.setCursor(48,38);
  display.println("| ");
  display.setCursor(60,35);
  display.println(b[2][2]);
  display.setCursor(72,38);
  display.println("| ");
  display.setCursor(0,40);
  display.println("+---+---+---+"); 
  display.display();
  delay(3000);
}

void HumanMoves( int& x, int& y, char b[][3] )
{
  int count = 1;
  int pressA;
  int pressB;
  int buttonY;

  display.setCursor(0,15);
  display.println("Row: 1 ");
  display.setCursor(0,25);
  display.println("Column: 1 ");
  display.display();
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
      if (buttonY < 300)
      {
        if (count == 1)
        {
          count = 2;
          display.setTextColor(WHITE);
          display.setCursor(0,15);
          display.println("Row: 1 ");
          display.setTextColor(BLACK);
          display.setCursor(0,15);
          display.println("Row: 2 ");
          display.display();
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              x = 2;
              goto end;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 300) && (buttonY <= 400));
        }
        else if (count == 2)
        {
          count = 3;
          display.setTextColor(WHITE);
          display.setCursor(0,15);
          display.println("Row: 2 ");
          display.setTextColor(BLACK);
          display.setCursor(0,15);
          display.println("Row: 3 ");
          display.display();
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              x = 3;
              goto end;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 300) && (buttonY <= 400));
        }
        else if (count == 3)
        {
          count = 1;
          display.setTextColor(WHITE);
          display.setCursor(0,15);
          display.println("Row: 3 ");
          display.setTextColor(BLACK);
          display.setCursor(0,15);
          display.println("Row: 1 ");
          display.display();
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              x = 1;
              goto end;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 300) && (buttonY <= 400));
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
      if (buttonY < 300)
      {
        pressB = digitalRead(PIN_BUTTON_DOWN);
        if (pressB == HIGH)
        {
          HumanMoves(x,y,b);
        }
        if (count == 1)
        {
          count = 2;
          display.setTextColor(WHITE);
          display.setCursor(0,25);
          display.println("Column: 1 ");
          display.setTextColor(BLACK);
          display.setCursor(0,25);
          display.println("Column: 2 ");
          display.display();
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              y = 2;
              goto done;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 300) && (buttonY <= 400));
        }
        else if (count == 2)
        {
          count = 3;
          display.setTextColor(WHITE);
          display.setCursor(0,25);
          display.println("Column: 2 ");
          display.setTextColor(BLACK);
          display.setCursor(0,25);
          display.println("Column: 3 ");
          display.display();
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              y = 3;
              goto done;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 300) && (buttonY <= 400));
        }
        else if (count == 3)
        {
          count = 1;
          display.setTextColor(WHITE);
          display.setCursor(0,25);
          display.println("Column: 3 ");
          display.setTextColor(BLACK);
          display.setCursor(0,25);
          display.println("Column: 1 ");
          display.display();
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              y = 1;
              goto done;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 300) && (buttonY <= 400));
        }
      }
    }
done:
   x= x-1;
   y=y-1;

  } while ((b[x][y] == 'X') || (b[x][y] == 'O')) ; 
  
}

void RandomMoves( int& x, int& y, char board[][3] )
{
  x = random(3); //Finds first random values of x and y between 1 and 3
  y = random(3);
  
  while ((board[x][y] == 'X') || ( board[x - 1][y - 1] == 'Y')) // If there is already a letter there it will enter loop
  {
    x = random(3); //It will keep looping until a new place is found without a letter
    y = random(3);
  }
   board[x][y]='O';
}
char EndGame(char b[][3]) // returns a t for tie, c for continue, 1 for player 1 won, 2 for player two won
{
  bool tieTest=true;
  char const tie='t';
  char const cont= 'c';
  char const p1w = '1';
  char const p2w = '2';

  for(int i=0; i<3; i++) //Tests to see if it is a tie, at the end of all the if statements it will check if the bool is true
  {
    for(int j=0; j<3; j++)
    {
      if( b[i][j] == '\n')//sets array to 0
      {
        tieTest = false;
      }
    }
  }
  
  //All of the following statements check to see if the various ways to win have happened
  
  if(b[0][0]=='X'&&b[0][1]=='X'&&b[0][2]=='X')
  {
    return p1w;
  }
  else if(b[0][0]=='O'&&b[0][1]=='O'&&b[0][2]=='O')
  {
    return p2w;
  }
  else if(b[1][0]=='X'&&b[1][1]=='X'&&b[1][2]=='X')
  {
    return p1w;
  }
  else if(b[1][0]=='O'&&b[1][1]=='O'&&b[1][2]=='O')
  {
    return p2w;
  }
  else if(b[2][0]=='X'&&b[2][1]=='X'&&b[2][2]=='X')
  {
    return p1w;
  }
  else if (b[2][0]=='O'&&b[2][1]=='O'&&b[2][2]=='O')
  {
    return p2w;
  }
  else if (b[0][0]=='X'&&b[1][0]=='X'&&b[2][0]=='X')
  {
    return p1w;
  }
  else if(b[0][0]=='O'&&b[1][0]=='O'&&b[2][0]=='O')
  {
    return p2w;
  }
  else if(b[0][1]=='X'&&b[1][1]=='X'&&b[2][1]=='X')
  {
    return p1w;
  }
  else if(b[0][1]=='O'&&b[1][1]=='O'&&b[2][1]=='O')
  {
    return p2w;
  }
  else if(b[0][2]=='X'&&b[1][2]=='X'&&b[2][2]=='X')
  {
    return p1w;
  }
  else if(b[0][2]=='O'&&b[1][2]=='O'&&b[2][2]=='O')
  {
    return p2w;
  }
  else if(b[0][0]=='X'&&b[1][1]=='X'&&b[2][2]=='X')
  {
    return p1w;
  }
  else if(b[0][0]=='O'&&b[1][1]=='O'&&b[2][2]=='O')
  {
    return p2w;
  }
  else if(b[0][2]=='X'&&b[1][1]=='X'&&b[2][0]=='X')
  {
    return p1w;
  }
  else if(b[0][2]=='O'&&b[1][1]=='O'&&b[2][0]=='O')
  {
    return p2w;
  }
  else if(tieTest) //Tests the previous set bool to check if a tie has been made
  {
    return tie;
  }
  else  //If no other conditions return first then the game can continue
    return cont;//there is no win. 
}
