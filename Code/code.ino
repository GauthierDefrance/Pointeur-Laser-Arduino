#include <myStepMotor.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <QMC5883LCompass.h>
#include <Wire.h>
#include <Ephem_Soleil.h>

Adafruit_MPU6050 mpu; //Création d'un objet pour l'accéléromètre

QMC5883LCompass compass; //Création d'un objet pour le magnétomètre

//Defitions du Lazer
#define LASER 1

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin
#define SW_PIN 3 //clique joystick

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis



int NbPas = 4096; //1 pas ~ 0,0789°
int liste[4]={1,0,0,0};
int pin1=4;
int pin2=5;
int pin3=6;
int pin4=7;

//Création des objets moteurs
myStepMotor MotorV = myStepMotor(NbPas,liste[4], pin1, pin2, pin3, pin4); //Objet moteur rotation verticale
myStepMotor MotorH = myStepMotor(NbPas,liste[4], 8, 9, 10, 11); //Objet moteur rotation horizontale

bool x = false;

int heure = 0;
double ha;
double az;
String lS, mS, cS;




void setup() {
	
Serial.begin(9600);
Serial.println("Début programme");


posSoleil("12/02/2017 22:00:00", 0, 48.8582333, 2.2944695, &ha, &az);  // pos actuelle le 15/08/2024
//Donne la position du soleil.
// az = azimut, ah = hauteur
//Non utilisé


Wire.begin();
digitalWrite(LASER,HIGH); //Activation du Lazer
pinMode(SW_PIN,INPUT);

// Init du magnétomètre
compass.init();

#define temps_attente 10 //temps en ms minimum 10.
int tmp=40;


//Début calibration perpendiculaire au sol
Wire.beginTransmission(0x68); //ici se trouve l'addresse de l'acceleromètre peut varier entre composants
//Vous pouvez trouver votre addresse en scannant les composants branchant à votre carte arduino sur les ports sda et scl
mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
mpu.begin();
sensors_event_t a, g, temp;
mpu.getEvent(&a, &g, &temp);
while((round(a.acceleration.y*10)!=0)){
if(abs(round(a.acceleration.y*15))<10)tmp=80;
mpu.getEvent(&a, &g, &temp);
if(round(a.acceleration.y*10)<0) MotorV.Step(true);
else MotorV.Step(false);
delay(tmp); 
}
Wire.endTransmission(); 
//Fin calibration perpendiculaire au sol


//Début calibration vers le nord
Wire.beginTransmission(0x0D); //ici se trouve l'addresse du magnétomètre peut varier entre composants
compass.read();
compass.getAzimuth(); //Ligne nécessaire car la première valeur est toujours un zéro
compass.read();
while(compass.getAzimuth()!=0){
if(compass.getAzimuth()>0)MotorH.Step(false);
else if(compass.getAzimuth()<0) MotorH.Step(true);
compass.read();
delay(40); 

}
 Wire.endTransmission();
//Fin calibration vers le nord

}





void loop() {
//scan du joystick
  int xValue = analogRead(VRX_PIN);
  int yValue = analogRead(VRY_PIN);

//Mouvement des moteurs selon le joystick
 if (xValue<=400){ 
    MotorH.Step(true);
  }
  else if (xValue>=800){ 
    MotorH.Step(false);
  }

  if (yValue<=400) {
    MotorV.Step(true);
  }
  else if (yValue>=800){ 
    MotorV.Step(false);
  }
 //temps d'attente entre chaque éxécution, minmum 10ms.
delay(temps_attente);
}



//Fonction pour effectuer des mouvements à peu près précis.
void Degrees(myStepMotor Motor, int degrees){
  float x;
  float constant = 0.0789;
  int y;
  int i;
  if (degrees<0){ //si le nombre de degrès est négatif
    degrees = abs(degrees);
    x = round(degrees/constant);
    y = int(x);
    for(i=0;i<y;i++){
      Motor.Step(false);
      delay(temps_attente);
    }
  }
  else{ //Si le nombre de degrès est positif
    x = round(degrees/constant);
    y = int(x);
    for(i=0;i<y;i++){
      Motor.Step(true);
      delay(temps_attente);
    }
  }
}
