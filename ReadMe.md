
  <h1 id="ardunio-handheld-gaming-system">Ardunio-Handheld-Gaming-System</h1>
</blockquote>

<p>Contributors: <br>
    Brayden, Brennen, Brooke <br>
    
    bclar686@gmail.com <br>
    brennen.b@hotmail.ca <br>
    Fall 2015</p>

<p>License Information: <br>
  The license for this project is GNU GENERAL PUBLIC LICENSE. For more information please look under the License file.</p>

<p>Overview: <br>
  This project is to create a handheld gaming system using the Ardunio Uno. This program includes <br>
    ~ Menu Function <br>
    ~ Four games ( Snake, Pong, Tic-Tac-Toe, Etch-A-Sketch) <br>
    ~ Bluetooth connection between Ardunios (comming soon...) </p>


<p>Hardware Used: <br>
  ~Arduino Uno <br>
  ~ Nokia 5110 LCD Screen <br>
  ~ Arduino TFT LCD screen <br>
  ~Joystick Shield V2.4 from ElecFreaks.com  <br>
  ~Push and Lock Button (for power switch) <br>
  ~9 Volt Battery and Battery case <br>
  ~BlueTooth Module HC-05</p>

<p>Project Design:</p>

<p>~ Nokia 5110 Screen HookUp: <br>
      8 pins are used for the LCD Screen. The following decribes the hookup: <br>
       -VCC = 3.3 Volts ****PLEASE NOTE ANYMORE THEN 3.3 VOLTS WILL BLOW OUT THE LEDS IN THE SCREEN <br>
      -GND = Ground Pin <br>
      -SCE = Pin 7  - Chip select <br>
      -RST = Pin 6  - Reset <br>
      -D/C = Pin 5  -Data/Command <br>
      -DN = Pin 11 - Serial data <br>
      -SCLK = Pin 13  - Serial clock <br>
      -LED = 9    - Backlight LED</p>
      
  <p> ~TFT Screen Hookup: <br>
      -5V = 5V <br>
      -Miso = pin 2 <br>
      -SCK = pin 3 <br>
      -MOSI = pin 4 <br>
      -LCD CS = pin 10 <br>
      -SD CS = not hooked up <br>
      -D/C = pin 9 <br>
      -Reset = pin 8 <br>
      -BL = 5V <br>
      -Ground = GND <br>
<p>~ JoyStick Shield Hookup <br>
    This shield provides very easy hookup. The shield simply connects straight into the ardunio board. It also has direct <br>      connection for the Nokia 5110 screen, however it is slightly skewed to the side.</p>

<p>~ Power Switch and Battery Hookup <br>
    For this setup wire was first soldered onto the battery casing on the positve and negative terminals. <br>      
    From the positive terminal the switch was connected. Our switch had 6 pins on it, we has to use a multimeter to <br> 
    test which controlled the current. We ended up soldering the positive wire to the left pin, and the wire which would lead <br> 
    to the Arduino to the middle pin.(Both pins on the same side). Both the negative and new positive wire were then solder straight <br>
    to the Arduino in the place of the previous battery input jack. </p>
  
<p>~ Bluetooth Hookup <br>
      BHurl currently researching, will also update soon!</p>

<p>~Installation Instructions:<br>
      Choose which code to download based off of the screen you are using. If using the Nokia 5110 Screen <br> 
      look at the Libaries Required section below. Simply download the two libaries, and place them in your Arduino Libary folder </p>
      
<p>~Libaries Required: <br>
      If using the Nokia 5110 screen you will need to download both the Adafruit-PCD8544-Nokia-5110-LCD library. <br>
      and the Adafruit-GFX-Library-master library. Links both listed here: <br>
      https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library.git <br>
      https://github.com/adafruit/Adafruit-GFX-Library.git </p>
