______________________________________________________________
[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
####################### Pointeur Laser #######################
[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]


Ce projet Arduino a été conçu en utilisant différents 
composants, qui vous seront nécessaire si vous souhaitez
réaliser ce projet.

Il vous faudra :
______________________________________________________________
| - 2 moteur pas à pas  28byj-48
| - 2 panneau de commande ULN2003
| https://fr.aliexpress.com/i/4000844084806.html
|
| - Une carte Arduino UNO
| - Des câbles et résistances en tout genre
| - Un acceleromètre  (gy-521 MPU6050)
| - un magnétomètre (GY-271 QMC5883L)
| - Un laser (KY-008)
| - Un ordinateur avec l'arduino IDE
|_____________________________________________________________

Je recommande d'utiliser également un "Sensor Shield" pour
Arduino UNO, mais aussi des supports métalliques afin d'avoir
une structure solide.


L'idée sera alors d'avoir un moteur pas à pas, monté sur un
autre moteur sur lequel sera monté nos capteurs et notre laser.
L'accéléromètre nous permettra de savoir où se trouve le sol
tandis que le magnétomètre nous montrera où se trouve le nord.
Ainsi, le pointeur laser cherchera au démarrage à se positionner
perpendiculaire au sol et en direction du nord polaire.

Maintenant, imaginons que nous cherchons à pointer le Soleil
par exemple. Il nous suffit de renseigner l'Azimut et la hauteur.
L'appareil pourra grâce au magnétomètre et à l'accéléromètre
savoir où se trouve le Soleil.


Bibliothèque utilisé :


Wire (installé par défaut)

Ephem_Soleil 
http://pr.chauveau.free.fr/spip/spip.php?page=article_pgm&id_rubrique=60



QMC5883LCompass




Adafruit_Sensor




Adafruit_MPU6050




myStepMotor (Bibliothèque conçu par moi même pour controler les moteurs pas à pas).




Comment installer une Bibliothèque :
https://knowledge.parcours-performance.com/librairies-arduino-installer/