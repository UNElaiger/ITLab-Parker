#include <WiFi.h>
#include <Ps3Controller.h>  

#ifndef STASSID
#define STASSID "ESP01"
#define STAPSK  "12345678"
#endif

const char* ssid     = STASSID;
//const char* password = STAPSK;
int x,y;
//bool state_up, state_down, state_left, state_right;
bool state_up, state_down, state_left, state_right, state_tank_left, state_tank_right = false;
int oldX,oldY = 0;
IPAddress ip(192, 168, 4, 1);
const uint16_t port = 80;
String message;
String sub;
WiFiClient client;
void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);


  WiFi.mode(WIFI_STA);
  //WiFi.begin(ssid, password);
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  while (1)
  {
  Serial.print("connecting to ");
  Serial.print(ip);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  //WiFiClient client;
  if (!client.connect(ip, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }
  else 
  {
    Serial.println("connection success");
    delay(5000);
    break;
    }

  // This will send a string to the server
  Serial.println("sending data to server");
  if (client.connected()) 
    {
      client.println("PS3");
      
    }
  }

    Ps3.begin("c0:14:3d:29:43:24"); //домашний
    //Ps3.begin("30:5a:3a:0f:6b:c7");  
    //Serial.println("Ready.");
 
}







void loop()
{
      
        /*
       if (Ps3.event.analog_changed.stick.lx != 0 ||  Ps3.event.analog_changed.stick.ly != 0 )
       {
        x = int(Ps3.data.analog.stick.lx);
        y = int(Ps3.data.analog.stick.ly);
        if (x>0)  
            message ="r";
         else if(x<0)
            message ="l";
        if (y>0)
            message ="b";
         else if(y<0)
            message ="f";

       Serial.print(" x="); Serial.print(x);
       Serial.print(" y="); Serial.print(y);
        
        /*sub = "X: " + int(x);
        message +=sub;
        sub = "";
        sub = " Y:" + int(y);
        message += sub;
        */ 
       //}


        if(Ps3.event.button_down.up && state_up == false)
        {
          state_up = true;
          //message +="forward";
          message ="f";
          client.println(message);
          Serial.println("f"); 
        }
        else if (Ps3.event.button_up.up && state_up == true)
        {
          state_up = false;
          message ="z";
          client.println(message); 
          delay(100);  
          client.println(message);
          Serial.println("z");
           
        }
        if(Ps3.event.button_down.down && state_down == false)
        {
          state_down = true;
          //message +="forward";
          message ="b";
          client.println(message);
          Serial.println("b");
           
        }
        else if (Ps3.event.button_up.down && state_down == true)
        {
          message ="z";
          state_down = false;
          client.println(message); 
          delay(100);  
          client.println(message);
          Serial.println("z");
            
        }   


        if(Ps3.event.button_down.left && state_left == false)
        {
          state_left = true;
          //message +="forward";
          message ="l";
          client.println(message);
          Serial.println("l"); 

        }
        else if (Ps3.event.button_up.left && state_left == true)
        {
          state_left = false;
          message ="z";
          client.println(message); 
          delay(100);  
          client.println(message); 
          Serial.println("z");
           
        }
        if(Ps3.event.button_down.right && state_right == false)
        {
          state_right = true;
          //message +="forward";
          message ="r";
          client.println(message);
          Serial.println("r"); 
        }
        else if (Ps3.event.button_up.right && state_right == true)
        {
          state_right = false;
          message ="z";
          client.println(message); 
          delay(100);  
          client.println(message); 
          Serial.println("z");
           
        }
        if(Ps3.event.button_down.l2 && state_tank_left == false)
        {
          state_tank_left = true;
          //message +="forward";
          message ="q";
          client.println(message);
          Serial.println("q"); 
        }
        else if (Ps3.event.button_up.l2 && state_tank_left == true)
        {
          state_tank_left = false;
          message ="z"; 
          client.println(message); 
          delay(100);  
          client.println(message);
          Serial.println("z");
            
        } 
        if(Ps3.event.button_down.r2 && state_tank_right == false)
        {
          state_tank_right = true;
          //message +="forward";
          message ="e";
          client.println(message); 
          delay(100);  
          client.println(message);
          Serial.println("e"); 
        }
        else if (Ps3.event.button_up.r2 && state_tank_right == true)
        {
          state_tank_right = false;
          message ="z";
          client.println(message); 
          delay(100);  
          client.println(message); 
          Serial.println("z");
           
        } 
        /*
        else if(Ps3.data.button.down)
        {
          //message +="back";
          message ="b"; 
        }
        
        else if(Ps3.data.button.left)
        {
          //message +="left";
          message ="l"; 
        }
        
        else if(Ps3.data.button.right)
        {
          //message +="right";
          message ="r"; 
        }

        else if(Ps3.data.button.l2 || Ps3.data.button.r2)
        {
        if (Ps3.data.button.l2)
            {
              //message +=" tankLeft ";
              message ="q"; 
            } 
        if (Ps3.data.button.r2)
            {
              //message +=" tankRight ";
              message ="e"; 
            } 
        }
        else
          message ="z"; 
          */

  //Serial.print(message);
  //Serial.println();

  message="";
  //Serial.println("this is the end");
  //delay(100);
  
}
