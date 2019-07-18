/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h> // se deben descargar las librerias
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "8wRdz3TwuNIgqQ5P92BXnRLT7NzISeNU";// se recibio por correo, para cada proyecto es uno nuevo

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "HOME-2A12"; // de la red wifi conectada a internet
char pass[] = "64A1B6166758ACA2"; //clave de la red wifi
WidgetLED led3(V3); // valor del puerto del led en blynk


void notifyOnButtonPress() // funcion para verificar el pulsador y activar el led de blynk no de NodeMCU y ver la accion en monitorserial (opcional)
{
  // Invert state, since button is "Active LOW"
  int isButtonPressed = !digitalRead(0); // puerto del pulsador en NodeMCU
  if (isButtonPressed) {
    Serial.println("Button is pressed.");
    led3.on(); // escribe en app blynk el estado on del led
    // Note:
    //   We allow 1 notification per 5 seconds for now.
    //Blynk.notify("Yaaay... button is pressed!"); // envia un mensaje al celular , primero activar el widget de notificacion celular vibra
    //Blynk.email("julian.lamprea@hotmail.com","Activacion pul"," Se activo el pulsador del Pin0"); // para enviar un email.
    // You can also use {DEVICE_NAME} placeholder for device name,
    // that will be replaced by your device name on the server side.
    //Blynk.notify("Yaaay... {DEVICE_NAME}  button is pressed!");
  }
}
void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(0,INPUT);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run(); 
   if (!digitalRead(0)){  // mantiene el led prendido // codigo adicional para prender y apagar el led de blynk
    //led3.on(); // prende el led  de blink directo
    notifyOnButtonPress();  // opcional
  }
  led3.off(); // apaga el led en app blynk
}
