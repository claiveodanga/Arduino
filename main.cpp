//LEFT WHEEL
 #define LPWM 9 
  #define in1 50
  #define in2 51

//RIGHT WHEEL
  #define RPWM 10
  #define in3 38
  #define in4 39

#define kp 0.15
  #define kd 4
  #define s1 6
  
  #define s2 7


  int leftWheel;
   int rightWheel;
   int set_position = 200;
   int d = 0, last_p=0;
   int sum_w = 0;
   int max_speed = 65;
   int error = 0;
   int sum_i = 0;
   int i;
   int sensor[] = {0, 0, 0, 0, 0};

   float p;
   float cur_position = 0;


const int pingPin = 45; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 44; // Echo Pin of Ultrasonic Sensor

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
    pinMode(pingPin, OUTPUT);
   pinMode(echoPin, INPUT);

  pinMode(LPWM,OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(RPWM,OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  for (i=14;i<=18;++i)pinMode(i,INPUT);
  Serial.begin(9600);
}

void loop() {

  sum_w = 0;
  sum_i = 0;
  for (i=0; i<5; i++)
  {
    sensor[i] = digitalRead(i+14);
    sum_w = sum_w + (sensor[i]*i*100);
    sum_i = sum_i + sensor[i];
   }
 
    cur_position = sum_w/sum_i;
    p= set_position - cur_position;
    d = p-last_p;
    last_p = p;
    
    error =p*kp + d*kd;
    if (error < 0)
      {
        leftWheel = max_speed;
        rightWheel = max_speed - error;
      }
     else{
        rightWheel = max_speed;
        leftWheel = max_speed + error;
     }

    digitalWrite(in1,LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4, HIGH);
    analogWrite(RPWM,leftWheel);
    analogWrite(LPWM,rightWheel);
}

