#include <SoftwareSerial.h>
SoftwareSerial Serial1(2, 3);

#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

int ldr1 = 8;
int ldr2 = 9;
int ldr3 = 10;
int ldr4 = 11;

int l1 = 0;
int l2 = 0;
int l3 = 0;
int l4 = 0;

int id[4];
int i = 0;

float latitude[4] = {5.7,20.3,8.4,1.9};
float longitude[4] = {6.8,21.5,5.9,6.7};

int k = 0;
int count = 0;
int temp = 0;

String pvtKey="wY9DPG5vzpH99KNrNkx2";     // private key for posting data to sparkfun
String publicKey="w5nXxM6rp0tww5YVYg3G";  // public key for open page of sparkfun 
String url="";
String ip="\"data.sparkfun.com\"";        // sparkfun server ip or url
int port=80;                              // sparkfun server port

String SendCmd="AT+CIPSEND=";           // sending number of byte command
String Start="AT+CIPSTART=\"TCP\"";     // TCPIP start command 

// strings and variables
//String msg="";
String instr="";
String str_sms="";
String str1="";
//int i=0,temp=0;

//#include <Keypad.h>               // keypad library for interfacing keypad
/*
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
int x=0;
int y=0;
int n=0;
int minValue=0;
int maxValue=0;
char keyPress=0;
int keyPressTime=100;
String msg="";
*/


void setup()
{
// set up the LCD's number of columns and rows:
lcd.begin(16, 2);
lcd.clear();

pinMode(ldr1, INPUT);
pinMode(ldr2, INPUT);
pinMode(ldr3, INPUT);
pinMode(ldr4, INPUT);

Serial1.begin(9600);    // init serial1 for GSM
  lcd.begin(16,2);        // init LCD
  lcd.print("Sending Data  ");
  lcd.setCursor(0,1);
  lcd.print("to Server");
  delay(2);

  lcd.clear();
  lcd.print("Initializing GSM");
  //initGSM();      // init GSM module
  lcd.clear();
  lcd.print("Initializing GPRS");
  //initGPRS();     // init GPRS in GSM Module
  lcd.clear();
  lcd.print("System Ready");
  delay(2);

}

void loop()
{
int count = 0;
 i = k;
  //Bulb1
lcd.setCursor(0,0); 
lcd.print("Bulb1:"); 
l1 = digitalRead(ldr1);
lcd.print(l1); 
if(l1 == 0)
{
  id[i] = 0;
  i = i+1;
  count = count + 1;
  }

 //Bulb2
lcd.setCursor(9,0); 
lcd.print("Bulb2:");
l2 = digitalRead(ldr2); 
lcd.print(l2);
if(l2 == 0)
{
  id[i] = 1;
  i = i+1;
  count = count + 1;
  }

 //Bulb3
lcd.setCursor(0,1); 
lcd.print("Bulb3:"); 
l3 = digitalRead(ldr3);
lcd.print(l3);
if(l3 == 0)
{
  id[i] = 2;
  i = i+1;
  count = count + 1;
  }

 //Bulb4
lcd.setCursor(9,1); 
lcd.print("Bulb4:"); 
l4 = digitalRead(ldr4);
lcd.print(l4);
delay(1);

if(l4 == 0)
{
  id[i] = 3;
  i = i+1;
  count = count + 1;
  }

  temp = count;
//location();
k = i;
k = k+1; // increamenting i for next loop so that values are not overrided in the previous index

int n=0;
  lcd.clear();
  lcd.noCursor();
  while(1)
  {
    lcd.cursor();
  
      lcd.clear();
      lcd.noBlink();
      lcd.print("Sending Data");
      lcd.setCursor(0,1);
      lcd.print("To Server");

      location();
      
 /*     
      url="GET /input/";
      url+=publicKey;
      url+="?private_key=";
      url+=pvtKey;
      url+="&log=";
      url+=msg;
      url+=" HTTP/1.0\r\n\r\n";
      String svr=Start+","+ip+","+port;
      delay(1000);
      connectGSM(svr,"CONNECT");
      delay(1000);
      int len = url.length();
      String str="";
      str=SendCmd+len;
      //sendToServer("Hi");
      
       Serial1.print(url);
      delay(1000);
      Serial1.write(0x1A);
      delay(1000);
      lcd.clear();
      lcd_status();
       //  clearmsg();
       n=0;
       i=0;
       x=0;
       y=0;
       msg="";
  */  
  }

}

void location()
{
  int j = 0;
  for (int s = 0; s<temp; s++)
  {
    j = id[s];
    lcd.clear();
    lcd.setCursor(0,0);          
    
    lcd.print("latitude:");
    lcd.print(latitude[j]);
    delay(1);
    lcd.setCursor(0,1);
    lcd.print("longitude");
    lcd.print(longitude[j]);
    delay(1);
    }
  }

  void lcd_status()
{
  lcd.clear();
  lcd.print("Data Sent to");
  lcd.setCursor(0,1);
  lcd.print("Server");
  delay(2);
  lcd.clear();
}

void sendToServer(String str)
{
  Serial1.println(str);
  delay(1);
}

void initGSM()
{
  connectGSM("AT","OK");
  connectGSM("ATE1","OK");
  connectGSM("AT+CPIN?","READY");
}
void initGPRS()
{
  connectGSM("AT+CIPSHUT","OK");
  connectGSM("AT+CGATT=1","OK");
  connectGSM("AT+CSTT=\"airtelgprs.com\",\"\",\"\"","OK");
  connectGSM("AT+CIICR","OK");
  delay(1);
  Serial1.println("AT+CIFSR");
  delay(1);
}
void connectGSM (String cmd, char *res)
{
  while(1)
  {
    Serial.println(cmd);
    Serial1.println(cmd);
    delay(2);
    while(Serial1.available()>0)
    {
      if(Serial1.find(res))
      {
        delay(1);
        return;
      }
    }
    delay(1);
   }
 }
