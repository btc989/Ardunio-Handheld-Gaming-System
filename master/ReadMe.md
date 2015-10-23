


> Written with [StackEdit](https://stackedit.io/).
> 



> # Ardunio-Handheld-Gaming-System

License Information:
  The license for this project is GNU GENERAL PUBLIC LICENSE. For more information please look under the License file.


Hardware Used:
  ~Arduino Uno
  ~ Nokia 5110 LCD Screen
  ~Joystick Shield V2.4 
  ~BlueTooth Module HC-05


Project Design:

  ~Screen HookUp:
      8 pins are used for the LCD Screen. The following decribes the hookup:
       -VCC = 3.3 Volts ****PLEASE NOTE ANYMORE THEN 3.3 VOLTS WILL BLOW OUT THE LEDS IN THE SCREEN
      -GND = Ground Pin
      -SCE = Pin 7  - Chip select
      -RST = Pin 6  - Reset
      -D/C = Pin 5  -Data/Command
      -DN<MOSI> = Pin 11 - Serial data
      -SCLK = Pin 13  - Serial clock
      -LED = 9    - Backlight LED

  ~ JoyStick Shield Hookup
	  Currently waiting for shields to arrive in the mail, will update once they are here!
  
     
      
  ~ Bluetooth Hookup
      BHurl currently researching, will also update soon!
  

Installation Instructions:

  ~Libaries Required:
      Currently the only library planned is for the Tic-Tac-Toe game which is currently being built. 