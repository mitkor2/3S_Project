//-- Libraries Included --------------------------------------------------------------
  #include <Wire.h>
  #include <WiFi.h>              // Built-in
  #include <WiFiMulti.h>         // Built-in
  #include <ESP32WebServer.h>    // https://github.com/Pedroalbuquerque/ESP32WebServer download and place in your Libraries folder
  #include <ESPmDNS.h>
//------------------------------------------------------------------------------------
// Defining I/O Pins
//------------------------------------------------------------------------------------
  #define       LED0      2         // WIFI Module LED
  #define       LED1      0        // Connectivity With Client #1
  #define       LED2      3        // Connectivity With Client #2
  #define       BUTTON    1        // Connectivity ReInitiate Button
  #define       TWI_FREQ  400000L   // I2C Frequency Setting To 400KHZ
//------------------------------------------------------------------------------------
  // Authentication Variables
  char*       TKDssid;              // SERVER WIFI NAME
  char*       TKDpassword;          // SERVER PASSWORD
//------------------------------------------------------------------------------------
  #define     MAXSC     2           // MAXIMUM NUMBER OF CLIENTS
  WiFiServer  TKDServer(9001);      // THE SERVER AND THE PORT NUMBER
  WiFiClient  TKDClient[MAXSC];     // THE SERVER CLIENTS
//====================================================================================

  void setup()
  {
    // Setting The Serial Port
    Serial.begin(115200);           // Computer Communication
    
    // Setting The Mode Of Pins
    pinMode(LED0, OUTPUT);          // WIFI OnBoard LED Light
    pinMode(LED1, OUTPUT);          // Indicator For Client #1 Connectivity
    pinMode(LED2, OUTPUT);          // Indicator For Client #2 Connectivity
    pinMode(BUTTON, INPUT_PULLUP);  // Initiate Connectivity
    
    // Print Message Of I/O Setting Progress
    Serial.println();
    Serial.println("I/O Pins Modes Set .... Done");

    // Setting Up A Wifi Access Point
    SetWifi("TAKEONE", "");
  }

//====================================================================================
  
  void loop()
  {
    
    IsClients2();
    
  }

//====================================================================================
  
  void SetWifi(char* Name, char* Password)
  {
    // Stop Any Previous WIFI
    WiFi.disconnect();

    // Setting The Wifi Mode
    WiFi.mode(WIFI_AP_STA);
    Serial.println("WIFI Mode : AccessPoint Station");
    
    // Setting The Access Point
    TKDssid      = Name;
    TKDpassword  = Password;
    
    // Starting The Access Point
    WiFi.softAP(TKDssid, TKDpassword);
    Serial.println("WIFI < " + String(TKDssid) + " > ... Started");
    
    // Wait For Few Seconds
    delay(1000);
    
    // Getting Server IP
    IPAddress IP = WiFi.softAPIP();
    
    // Printing The Server IP Address
    Serial.print("AccessPoint IP : ");
    Serial.println(IP);

    // Starting Server
    TKDServer.begin();
    Serial.println("Server Started");
  }

//====================================================================================

  void IsClients()
  {
    if(TKDServer.hasClient())
    {
      WiFiClient TKDClient = TKDServer.available();
      
      if(digitalRead(LED0) == HIGH) digitalWrite(LED0, LOW);
      
      digitalWrite(LED1, HIGH);

      while(1)
      {

        //--[ Draft ] ---------------------------------------------------

        
              
        //---------------------------------------------------------------
        // If Clients Are Connected 
        //---------------------------------------------------------------
        
        if(TKDClient.available())
        {
          // Here We Read The Message
          String Message = TKDClient.readStringUntil('\r');
          // Here We Print The Message On The Screen
          Serial.println(Message);
          // Here We Reply To The Client With A Message
          TKDClient.print("\nWe Got Your Message");
          TKDClient.flush();
        }
        
        //---------------------------------------------------------------
        // If Clients Are Disconnected
        //---------------------------------------------------------------
        
        if(!TKDClient || !TKDClient.connected())
        {
          // Here We Turn Off The LED To Indicated The Its Disconnectted
          digitalWrite(LED1, LOW);
          // Here We Jump Out Of The While Loop
          break;
        }

        //----------------------------------------------------------------
        
      }
      
    }
    else
    {
      // This LED Blinks If No Clients Where Available
      digitalWrite(LED0, HIGH);
      delay(250);
      digitalWrite(LED0, LOW);
      delay(250);
    }
  }

//====================================================================================

  void IsClients2()
  {
    if (TKDServer.hasClient())
    {
      for(int i = 0; i < MAXSC; i++)
      {
        //find free/disconnected spot
        if (!TKDClient[i] || !TKDClient[i].connected())
        {
          if(TKDClient[i]) TKDClient[i].stop();
          TKDClient[i] = TKDServer.available();
          Serial.print("New Client : "); Serial.print(String(i+1) + " - ");
          continue;
        }
      }
      // no free / disconnected spot so reject
      digitalWrite(LED1, HIGH);
      WiFiClient TKDClient = TKDServer.available();
      TKDClient.stop();
    }

    //check clients for data -------------------------------------------------------
    
    for(int i = 0; i < MAXSC; i++)
    {
      if (TKDClient[i] && TKDClient[i].connected())
      {
        if(TKDClient[i].available())
        {
          // If Any Data Was Available We Read IT
          while(TKDClient[i].available()) 
          {
            // Read From Client
            Serial.println(TKDClient[i].readStringUntil('\n'));
            // Reply To Client
            TKDClient[i].println("<OK>");
          }
        }
      }
    }
  }

//====================================================================================
