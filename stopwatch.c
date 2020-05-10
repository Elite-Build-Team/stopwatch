// Variables
int counter = 0;
int count = 0;
int temp=0;
int pressed=1;
int butt_pr=0;
int interrupt=0;
int secs=0;
int startPressed = 0;    // the moment the button was pressed
int endPressed = 0;      // the moment the button was released
int holdTime = 0;        // how long the button was hold
int idleTime = 0;
unsigned long previousMillis = 0;
extern unsigned long currentMillis=0;
bool reset_flag=false;

extern unsigned long time_elapsed=0;
// interval at which to blink (milliseconds)
const long interval = 1000; //1Hz
const long interval2 = 500; //2Hz

void buttonUpdate(){
  	pressed=digitalRead(2);
    butt_pr+=pressed;
  }
  
void whentoreset() {
  // the button has been just pressed
  if (digitalRead(2) == HIGH) {
      startPressed = millis();
      idleTime = startPressed - endPressed;
  // the button has been just released
  } else {
      endPressed = millis();
      holdTime = endPressed - startPressed;
      if (holdTime >= 1000) {
          Serial.println("Button was hold for one second or more");
        	reset();
      }

  }
}  	
/*
void check_butt_pres(){
  if (pressed){
	if (time_elapsed >=1000){
      reset();
    }else{
     	reset_flag=false;
    }
  }
}
*/
void reset(){
  currentMillis=0;
  previousMillis=0;
  counter = 0;
  temp=0;
  pressed=1;
  butt_pr=0;
  interrupt=0;
  reset_flag=false;
  secs=0;
  time_elapsed=0;
}
void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);	
  pinMode(4, OUTPUT);		
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
 //interrupt from button
  attachInterrupt(digitalPinToInterrupt(2),buttonUpdate,CHANGE);
}

void loop()
{
  whentoreset();
  	currentMillis = millis();
    //check_butt_pres();
  	if (butt_pr%2!=0){
        if (currentMillis - previousMillis >= interval2) {
         // save the last time you blinked the LED
          previousMillis = currentMillis;
          interrupt=1;
          //ENTER HOLD STATE
          digitalWrite(4, LOW);
          digitalWrite(7, LOW);
          digitalWrite(8, HIGH);
          digitalWrite(8, LOW);
        }else{
          interrupt=0;
        }
    }
  
  	if(!interrupt){
       if (currentMillis - previousMillis >= interval) {
          secs++;
		// save the last time you blinked the LED
          previousMillis = currentMillis;
		// if the LED is off turn it on and vice-versa:
		// set the LED with the ledState of the variable:
           digitalWrite(4, HIGH);
           digitalWrite(4, LOW);
           Serial.print(secs);
           if (secs %10 == 0)
        	{
              counter=counter+1; //10s counter
              temp=counter; 
		    }
         	if (secs==59){
       		 	currentMillis=0;
      			counter=0;
              	secs=0;
    		}
         //for 10s
           if (temp>0){ 
              digitalWrite(7, HIGH);
              digitalWrite(7, LOW);
              temp-=1;
			}
		}
	}
}
