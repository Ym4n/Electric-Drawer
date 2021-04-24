#include <Stepper.h>


#include <IRremote.h>


// 150 is the max speed we can get
#define MotorSpeed 150  // 150 
#define stepsPerRevolution 200
#define Steps_for_1cm 250
#define buttonPin 8
#define Sensor_Home 2
#define Sensor_Far 3
#define DECODE_NEC 1
#define IR_RECEIVE_PIN  9
#define Sensor_Blocked false
#define Sensor_Open true


Stepper myStepper(stepsPerRevolution, 4, 5, 6, 7);

bool Dirction_back = false;
// the movement of the jig ( 200steps==1rev==0.8cm , 1cm==250steps)
int Jig_increment = Steps_for_1cm/10;

int Current_Location = 0;
int Target_Location = 0;
// steps between Start to End of the movement 
int Edge_to_Edge_steps = Steps_for_1cm*27; // need to be - 28

bool available_for_new_mission = true;

// Repeat_flag - for jig movement run smootly . 
// 1 ==> JIG move Back, 2 ==> JIG move Forward, 0 ==> Not JIG
int Repeat_flag = 0 ;

// JIG - moving by XX cm  
void JIG_MOVE(){
  if (Dirction_back==true){
    if (digitalRead(Sensor_Home)==Sensor_Open){
      Target_Location = Current_Location - Jig_increment;
    }
    else{
      Target_Location = Current_Location;
    }
  }
  else{
    if (digitalRead(Sensor_Far)==Sensor_Open){
      Target_Location = Current_Location + Jig_increment;
    }
    else{
      Target_Location = Current_Location;
    } 
  }
  move();
  //available_for_new_mission=false;
}

// Edge to Edge movement 
void Edge_move(){
  Serial.println("Edge move");
  if (digitalRead(Sensor_Home)==Sensor_Blocked){
    Current_Location=0;
  }

  if (Current_Location==0){
    Dirction_back=false;
    Target_Location = Edge_to_Edge_steps*-1;
  }
  else{
    Target_Location = 0;
    Dirction_back=true;
  }
  available_for_new_mission =false;
}

void Stop_motor(){
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
}


// increment movement
void move(){
  if (Current_Location==Target_Location){
    available_for_new_mission= true;
    Stop_motor();
  }
  int Steps = stepsPerRevolution/2;
  int gap = abs(Current_Location - Target_Location);
  Serial.print("Current Location and Target_Location : ");
  Serial.print(Current_Location);
  Serial.print("  ,  ");
  Serial.println(Target_Location);
  if (Steps > gap){
    Steps= gap;
  }
  if (Dirction_back){
    myStepper.step(Steps);
    Current_Location += Steps;
  }
  else{
    myStepper.step(-Steps);
    Current_Location -= Steps;
  }
}

void Sensor_Home_Reach(){
  Stop_motor();
  Dirction_back = !Dirction_back;
  available_for_new_mission = true;
  Current_Location=0;
  Serial.println("Reach to the Home Pos");
}

void Sensor_Far_Reach(){
  Stop_motor();
  Dirction_back = !Dirction_back;
  Serial.println("Reach to the End");
  available_for_new_mission = true;
}

// Remote functions
void read_Remote(){
  if (IrReceiver.decode()) {
        // Chaines Remote
        if (IrReceiver.decodedIRData.address==0){
          if (available_for_new_mission==true){
            switch(IrReceiver.decodedIRData.decodedRawData) {
            case 0xE718FF00:                      // UP arrow - Move to Home Pos
              Serial.println("go back");
              Dirction_back=true; 
              Repeat_flag = 1 ;
              JIG_MOVE();
              break;   
            
            case 0xAD52FF00:                      // down arrow - Move Out
              Serial.println("go forward");
              Dirction_back=false; 
              Repeat_flag = 2 ;
              JIG_MOVE(); 
              break;   
            
            case 0xE31CFF00:                      // OK btn
              Serial.println(" -OK- Stop motors"); 
              Repeat_flag = 0 ;
              Stop_motor();
              break;             
            
            case 0xB946FF00:                      // 2 - move to home pos
              Repeat_flag = 0 ;
              if (digitalRead(Sensor_Home)!=Sensor_Blocked){
                Current_Location =Edge_to_Edge_steps ;
                Edge_move();
              }
              break;                              
            
            case 0xEA15FF00:                      // 8 - move to far pos
              Repeat_flag = 0 ; 
              if (digitalRead(Sensor_Far)!=Sensor_Blocked){
                Current_Location = 0 ;
                Edge_move();
              }
              break;                
            
            case 0x0: 
              switch (Repeat_flag)
              {
              case 1:
                Dirction_back=true; 
                JIG_MOVE();
                break;
              
              case 2:
                Dirction_back=false; 
                JIG_MOVE();
                break;
              }
              break;
            
            default:
              Repeat_flag = 0 ;
            }
            delay(200); // Do not get immediate repeat
          }
          else{
            if (IrReceiver.decodedIRData.decodedRawData==0xE31CFF00){
              Stop_motor();
              available_for_new_mission=true;
              delay(200);
            }
          }
        }
        // Polaris Remote
        if (IrReceiver.decodedIRData.address==0xCF00){
          if (available_for_new_mission==true){
            switch(IrReceiver.decodedIRData.command) {
              case 0xB:                                    // - btn
                Serial.println("Feldman remote");
                Serial.println(" - btn");
                Repeat_flag = 0 ;
                if (digitalRead(Sensor_Home)!=Sensor_Blocked){
                  Current_Location =Edge_to_Edge_steps ;
                  Edge_move();
                }
                break;

              case 0xA:                                    // + btn
                Serial.intln("Feldman remote");
                Serial.priprntln(" + btn");
                Repeat_flag = 0 ; 
                if (digitalRead(Sensor_Far)!=Sensor_Blocked){
                  Current_Location = 0 ;
                  Edge_move();
                }
                break;
              
              case 0x1A:                                    // Power(ON/OFF) btn
                Serial.println("Feldman remote");
                Serial.println(" Power btn");
                Repeat_flag = 0 ;
                if (digitalRead(Sensor_Home)!=Sensor_Blocked){
                  Current_Location =Edge_to_Edge_steps ;
                  Edge_move();
                }
                break;
            }
          }


        }
        IrReceiver.resume(); // Enable receiving of the next value
    }
}

void setup()
{  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(Sensor_Home, INPUT_PULLUP);
  pinMode(Sensor_Far, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Sensor_Home), Sensor_Home_Reach, FALLING);
  attachInterrupt(digitalPinToInterrupt(Sensor_Far), Sensor_Far_Reach, FALLING);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);

  if (digitalRead(Sensor_Far)==0){
    Current_Location = -Edge_to_Edge_steps;
  }
  Serial.println(Current_Location);
  myStepper.setSpeed(MotorSpeed);
  Serial.begin(9600);
  Serial.println("Setup Done");
  Serial.println(Current_Location);
}

void loop(){   
  if (available_for_new_mission){
    Stop_motor();
    //check buttom
    if (digitalRead(buttonPin)==false){
      // Edge_move
      Edge_move();
      Serial.println("Button clicked");
    }
    read_Remote();
  }
  else{
    read_Remote();
    move();
  }
}
