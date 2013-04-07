#include <LiquidCrystal.h>

//IP address and port of the remote server
String IPaddress = "90.193.231.70";
String port = "6100";

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

String receivedString = "";

void setup() {  
  lcd.begin(16,2);
  digitalWrite(13, LOW);
  lcd.print("    POWER ON");
  delay(2300);
  
  setUpModem();

  configureModem(IPaddress,port);
  
} 


void loop() { 
  long time = millis()/1000;
  String stringToSend = "Time = ";
  stringToSend += time;
  
  //sendData(stringToSend);

   Serial1.println("AT+SDATASTART=1,1");
   delay(2000);
   receivedString = receiveFromModem(); 
   Serial.println(receivedString);

receiveData();
  

  lcd.clear();
  lcd.print("Waiting 20 secs.");
  delay(20000);
}

//Returns string received from the server
String receiveData(){
  lcd.clear();
  lcd.print("Waiting for RX  ");
  Serial.println("Waiting to receive data from remote server...");
  
    boolean receivedData = false;
    while(!receivedData){
      String modemStatus = receiveFromModem();
      if(modemStatus.equals("+STCPD:1")){
        lcd.setCursor(0,1);
        lcd.print("Data available. ");
        Serial.println("Data available from modem.");
        receivedData = true;
      }
    }
    
   Serial1.println("AT+SDATAREAD=1");
   delay(1000);
   receivedString = receiveFromModem(); 
   String message = "";
   if(receivedString.length() > 8){
       lcd.setCursor(0,1);
        lcd.print("Data read.      ");
        Serial.println("Data read from modem.");
        delay(1000);
        message = receivedString.substring(9); //From index 9 to the end of the string
   }
   Serial.println(message);
    
    

}

//Waits for +SIND: 4 to be returned, meaning modem is ready
void setUpModem(){
  lcd.clear();
  lcd.print("Modem set up...");

  lcd.setCursor(0,1);
  //Initalise serial ports for communication
  Serial.begin(9600); //Computer comms
  Serial1.begin(115200);//modem
  Serial.print("Starting SM5100B Communication...");
  lcd.print("Starting SM5100B");
  pinMode(13,OUTPUT);


  boolean registered = false;
  while(!registered){             //Loop until correct message returned (not required if only one message required)
    receivedString = receiveFromModem(); //Receive message from modem
    Serial.print('.');       //Show that something is happening each time message comes through
    if(receivedString.equals("+SIND: 4")){ //SIND 4 is the message that the SIM is registered with network
      lcd.setCursor(0,1);
      lcd.print("Registered on TM");
      Serial.println("\nModem is registered on network and ready to communicate.");
      registered = true;          //break out of loop
    }
  }
  Serial.println("Ready for configuration...");
  lcd.clear();
  lcd.print("Configuring...");
  delay(1000);
}

//Configures modem with specified IP and port for remote server
//TODO include APN settings as parameters here.
void configureModem(String IPaddress, String port){
  int successfulCommands = 0; //This int is incremented each time a successful command goes through to stop
  //later commands being carried out after failed command

  do{
    //Set up PDP context
    Serial1.println("AT+CGDCONT=1,\"IP\",\"general.t-mobile.uk\"");
    delay(2000);
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("OK")){ //OK is expected
      lcd.setCursor(0,1);
      lcd.print("PDP context set ");
      Serial.println("\n\tPDP context set up successfully.");
      successfulCommands++; //increment, therefore breaking out of loop.
    }
    else{
      Serial.println("Something went wrong, retrying");
    }
  }
  while(successfulCommands == 0);

  do{
    //Set up PDP context parameters (APN username/password)
    Serial1.println("AT+CGPCO=0,\"tmobile\",\"tm\",1");
    delay(2000);
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("OK")){ //OK is expected
      Serial.println("\tPDP context parameters set up successfully.");
      lcd.setCursor(0,1);
      lcd.print("PDP params set  ");
      successfulCommands++; //increment, therefore breaking out of loop.
    }
  }
  while(successfulCommands <= 1);

  do{
    //Activate PDP context
    Serial1.println("AT+CGACT=1,1");
    delay(2000);
    receivedString = receiveFromModem(); //Receive message from modem
    //    Serial.println(receivedString);
    if(receivedString.equals("OK")){ //OK is expected
      Serial.println("\tPDP context activated.");
      lcd.setCursor(0,1);
      lcd.print("PDP cont. active");
      successfulCommands++; //increment, therefore breaking out of loop.
    }
  }
  while(successfulCommands <= 2);

  do{
    //Configure remote host and port, then a TCP connection can be opened
    String remoteConfiguration = "AT+SDATACONF=1, \"TCP\", \"";
    remoteConfiguration += IPaddress;
    remoteConfiguration += "\", ";
    remoteConfiguration += port;
    Serial1.println(remoteConfiguration);
    delay(2000);
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("OK")){ //OK is expected
      Serial.println("\tTCP parameters for connection to remote server configured.");
      lcd.setCursor(0,1);
      lcd.print("TCP params set  ");
      successfulCommands++; //increment, therefore breaking out of loop.
    }
  }
  while(successfulCommands <= 3);
  
   do{
    //Configure remote host and port, then a TCP connection can be opened
    Serial1.println("AT+SDATARXMD=1,1");
    delay(2000);
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("OK")){ //OK is expected
      Serial.println("\tReceive mode set to string rather than hex.");
      lcd.setCursor(0,1);
      lcd.print("RXMD String set ");
      successfulCommands++; //increment, therefore breaking out of loop.
    }
  }
  while(successfulCommands <= 4);

  delay(2000);

  Serial.println("\nSet up complete, ready to send over GPRS/GSM.");
  lcd.setCursor(0,1);
  lcd.print("complete.       ");
  delay(2000);
}
//Called when data is required to be sent to remote server
void sendData(String sendString){
  lcd.clear();
  lcd.print("Sending data"); 
  int successfulSend = 0;
  do{
    //Open connection
    Serial1.println("AT+SDATASTART=1,1");
    delay(2000);
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("OK")){ //OK is expected
      Serial.println("\n\tAttempted to open socket.");
      lcd.setCursor(0,1);
      lcd.print("Opening socket  ");
      boolean querySuccess = false;
      do{
        //Check that socket is connected
        Serial1.println("AT+SDATASTATUS=1");
        delay(2000);
        receivedString = receiveFromModem(); //Receive message from modem
        String trimmedString = receivedString.substring(0,11);
        if(trimmedString.equals("+SOCKSTATUS")){ //This is the start of the returned message
          if(receivedString[16] == '1'){ //+SOCKSTATUS:  1,0,0000,0,0,0 this is the returned message
            querySuccess=true;            //16th character is 0 for not connected, 1 for connected
            successfulSend++; //increment, therefore breaking out of main loop.
            Serial.println("\tConnected to remote server.");
            lcd.setCursor(0,1);
            lcd.print("Connected server");
            digitalWrite(13, HIGH);
            delay(2000);
          }
          else{
            Serial.println("\tUnsuccessful connection, trying again...");
            querySuccess= true;
            lcd.setCursor(0,1);
            lcd.print("Trying again... ");
            //no index increment

              //Send close socket command to ensure that modem has closed socket
            //before trying again.
            boolean successfulCommand=false;
            do{
              Serial1.println("AT+SDATASTART=1,0");
              delay(2000);
              receivedString = receiveFromModem(); //Receive message from modem
              if(receivedString.equals("OK")){ //OK is expected
                successfulCommand=true;
              }
            }
            while(!successfulCommand);
          }
        }
      }
      while(!querySuccess);
    }
  }
  while(successfulSend == 0);

  //Send some data
  Serial.println("\tSending data...");
  lcd.setCursor(0,1);
  lcd.print("Sending...      ");
  long currentTime = millis();
  String stringToSend = "AT+SSTRSEND=1, \"";
  stringToSend += sendString;
  stringToSend += "\"";
  Serial1.println(stringToSend);

  do{
    delay(8000);
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("OK")){ //This is the start of the returned message
      Serial.println("\tData sent.");
      lcd.setCursor(0,1);
      lcd.print("Data sent.       ");
      successfulSend++; //increment, therefore breaking out of loop.
    }
    else{
      Serial.println("\tStill waiting for data to send...");
      lcd.setCursor(0,1);
      lcd.print("Still sending...");
    }
  }
  while(successfulSend == 1);

  //Close the socket
  do{
    Serial1.println("AT+SDATASTART=1,0");
    delay(2000);
    receivedString = receiveFromModem(); //Receive message from modem
    if(receivedString.equals("OK")){ //OK is expected
      Serial.println("\tSocket closed.");
      lcd.setCursor(0,1);
      lcd.print("Socket closed.  ");
      digitalWrite(13, LOW);
      successfulSend++;
      delay(2000);
    }
  }
  while(successfulSend == 2); 
}


//Should be run when message is expected from modem
//Returns the message from modem that can be compared.
String receiveFromModem(){ 
  String inString="";
  char incoming = 0;
  boolean receivedMessage = false;

  while(!receivedMessage){  //while no message found
    if(Serial1.available()>0){ //Look for serial data
      incoming = Serial1.read(); //read one byte from buffer    
      if(incoming == '\n'){ //if the byte is the new line character (indicates end of modem message)
        inString.trim();   //Remove unnecessary white space (causes issues with.equals)
        if(inString.length()>0){
          return inString;  //return the string
        }
        else{
          inString = "";
        }
      }
      inString += incoming;  //else add to the message and look for another byte
    } 
  }
}














