/*
 - ST TP INTEGRADOR 
*/

//Librerías
//*****************

//Datos del Display 
//*****************

//Pines
#define PIN_BOTON_1 1
#define PIN_BOTON_2 2
#define PIN_BOTON_3 3 
#define PIN_BOTON_4 4
//#define PIN_BOTON_5 5 
bool estadoBoton1 = false;
bool estadoBoton2 = false;
bool estadoBoton3 = false;
//bool estadoBoton4 = false;
//bool estadoBoton5 = false;

//Máquina de Estados
#define PANTALLA_INICIAL 1 
#define CHECK_BOTON 2   
#define AJUSTAR_TEMPERATURA 3
#define AJUSTAR_HUMEDAD 4
#define AJUSTAR_GMT 5
#define AJUSTAR_MQTT 6

//Estado inicial de la máquina
int estado = 1;  

//Variables
int temperaturaUmbral = 0;
int humedadUmbral = 0;
int gmt = 0;
int mqtt = 0;
int pantalla = 1;

//Inicializar rtc
int gmt;
struct tm timeinfo;
ESP32Time rtc;

//Reloj
long unsigned int timestamp; 
const char *ntpServer = "south-america.pool.ntp.org";
long gmtOffset_sec = -10800;
const int daylightOffset_sec = 0;

//WiFi
const char* ssid = "ORT-IoT";           
const char* password = "OrtIOTnew22$2";

//Constructores y variables globales
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//Funciones
void pedir_lahora(void);
void setup_rtc_ntp(void);
void initWiFi();

void setup() 
{
  
  Serial.begin(9600);
  u8g2.begin();
  pinMode(PIN_BOTON_1, INPUT_PULLUP);    
  pinMode(PIN_BOTON_2, INPUT_PULLUP);  
  pinMode(PIN_BOTON_3, INPUT_PULLUP);    
  pinMode(PIN_BOTON_4, INPUT_PULLUP); 
  //pinMode(PIN_BOTON_5, INPUT_PULLUP);    

  Serial.println("Conectandose a Wi-Fi...");

  //Llamo a las funciones
  initWiFi(); 
  setup_rtc_ntp();

  }

void loop() 
{

  switch(estado)
  {
    //Pantalla que muestra hora y temperatura
    case PANTALLA_INICIAL: 
   
{      
    Serial.println("PANTALLA INICIAL"); 
    delay(2000);
    pedir_lahora();
    
    //IMPRIMIR VALORES EN EL DISPLAY
    Serial.println("TEMPERATURA UMBRAL"); 
    Serial.println("HUMEDAD UMBRAL"); 
    Serial.println("GMT"); 
    Serial.println("MQTT"); 

    //IMPRIMIR VALORES POR PUERTO SERIE
    Serial.println(temperaturaUmbral); 
    Serial.println(humedadUmbral); 
    Serial.println(gmt); 
    Serial.println(mqtt); 
   
      if(digitalRead(PIN_BOTON_1) == LOW)
      {
        estado = CHECK_BOTON;
      }
      
}
    break;

    case CHECK_BOTON: 
    { 
      Serial.println("CHECK BOTON"); 

      //DISPLAY A TEMPERATURA
      if(digitalRead(PIN_BOTON_1) == HIGH && estadoBoton1 == false)
      {
        estadoBoton1 = true;
        estado = AJUSTAR_TEMPERATURA;
      }

      //CUALQUIERA A DISPLAY
      if(digitalRead(PIN_BOTON_1) == HIGH && estadoBoton1 == true)
      {
        estadoBoton1 = false;
        estado = PANTALLA_INICIAL;
      }

      //TEMPERATURA A HUMEDAD
      if(digitalRead(PIN_BOTON_4) == HIGH && pantalla == 2)
      {
        estado = AJUSTAR_HUMEDAD;
      }

      //HUMEDAD A GMT
      if(digitalRead(PIN_BOTON_4) == HIGH && pantalla == 3)
      {
        estado = AJUSTAR_GMT;
      }

      //GMT A MQTT
      if(digitalRead(PIN_BOTON_4) == HIGH && pantalla == 4)
      {
        estado = AJUSTAR_MQTT;
      }

      //HUMEDAD A GMT
      if(digitalRead(PIN_BOTON_4) == HIGH && pantalla == 1)
      {
        estado = AJUSTAR_TEMPERATURA;
      }

    }
    break;

    //Pantalla que permite cambiar la temperatura
    case AJUSTAR_TEMPERATURA: 
    { 

    Serial.println("AJUSTAR TEMPERATURA");
    Serial.println(temperaturaUmbral);  
    
      //SUMA
      if(digitalRead(PIN_BOTON_2) == LOW) 
      {
        estadoBoton2 = true;
        Serial.println("BOTON_PRESIONADO");
      }
     
      if(digitalRead(PIN_BOTON_2) == HIGH && estadoBoton2 == true) 
      {
        estadoBoton2 = false;
        Serial.println("BOTON_SUELTO");
        temperaturaUmbral = temperaturaUmbral++;
        Serial.println(temperaturaUmbral);  
        
      }    

      //RESTA
      if(digitalRead(PIN_BOTON_3) == LOW)
      {
        estadoBoton3 = true;
        Serial.println("BOTON_PRESIONADO");
      }
      if(digitalRead(PIN_BOTON_3) == HIGH && estadoBoton3 == true)
      {
        estadoBoton3 = false;
        Serial.println("BOTON_SUELTO");
        temperaturaUmbral = temperaturaUmbral--;
        Serial.println(temperaturaUmbral);  
      }    
      
      //TEMPERATURA A DISPLAY
      if(digitalRead(PIN_BOTON_1) == LOW && estadoBoton1 == true) 
      {
        estado = CHECK_BOTON;
      }

      //TEMPERATURA A HUMEDAD
      if(digitalRead(PIN_BOTON_4) == LOW && pantalla == 1) 
      {
        pantalla = 2;
        estado = CHECK_BOTON;
      }
    }
    break;

    case AJUSTAR_HUMEDAD: 
    { 

    Serial.println("AJUSTAR HUMEDAD");
    Serial.println(humedadUmbral);  
    
      //SUMA
      if(digitalRead(PIN_BOTON_2) == LOW) 
      {
        estadoBoton2 = true;
        Serial.println("BOTON_PRESIONADO");
      }
     
      if(digitalRead(PIN_BOTON_2) == HIGH && estadoBoton2 == true) 
      {
        estadoBoton2 = false;
        Serial.println("BOTON_SUELTO");
        humedadUmbral = humedadUmbral++;
        Serial.println(humedadUmbral);  
        
      }    

      //RESTA
      if(digitalRead(PIN_BOTON_3) == LOW)
      {
        estadoBoton3 = true;
        Serial.println("BOTON_PRESIONADO");
      }
      if(digitalRead(PIN_BOTON_3) == HIGH && estadoBoton3 == true)
      {
        estadoBoton3 = false;
        Serial.println("BOTON_SUELTO");
        humedadUmbral = humedadUmbral--;
        Serial.println(humedadUmbral);  
      }    
      
      //HUMEDAD A DISPLAY
      if(digitalRead(PIN_BOTON_1) == LOW && estadoBoton1 == true) 
      {
        estado = CHECK_BOTON;
      }

      //HUMEDAD A GMT
      if(digitalRead(PIN_BOTON_4) == LOW && pantalla == 2) 
      {
        pantalla = 3;
        estado = CHECK_BOTON;
      }
    }
    break;

case AJUSTAR_GMT: 
    { 

    Serial.println("AJUSTAR GMT");
    Serial.println(gmt);  
    
      //SUMA
      if(digitalRead(PIN_BOTON_2) == LOW) 
      {
        estadoBoton2 = true;
        Serial.println("BOTON_PRESIONADO");
      }
     
      if(digitalRead(PIN_BOTON_2) == HIGH && estadoBoton2 == true) 
      {
        estadoBoton2 = false;
        Serial.println("BOTON_SUELTO");
        gmt = gmt++;
        Serial.println(gmt);  
        
      }    

      //RESTA
      if(digitalRead(PIN_BOTON_3) == LOW)
      {
        estadoBoton3 = true;
        Serial.println("BOTON_PRESIONADO");
      }
      if(digitalRead(PIN_BOTON_3) == HIGH && estadoBoton3 == true)
      {
        estadoBoton3 = false;
        Serial.println("BOTON_SUELTO");
        gmt = gmt--;
        Serial.println(gmt);  
      }    
      
      //GMT A DISPLAY
      if(digitalRead(PIN_BOTON_1) == LOW && estadoBoton1 == true) 
      {
        estado = CHECK_BOTON;
      }

      //GMT A MQTT
      if(digitalRead(PIN_BOTON_4) == LOW && pantalla == 3) 
      {
        pantalla = 4;
        estado = CHECK_BOTON;
      }
    }
    break;

    case AJUSTAR_MQTT: 
    { 

    Serial.println("AJUSTAR MQTT");
    Serial.println(mqtt);  
    
      //SUMA
      if(digitalRead(PIN_BOTON_2) == LOW) 
      {
        estadoBoton2 = true;
        Serial.println("BOTON_PRESIONADO");
      }
     
      if(digitalRead(PIN_BOTON_2) == HIGH && estadoBoton2 == true) 
      {
        estadoBoton2 = false;
        Serial.println("BOTON_SUELTO");
        mqtt = mqtt++;
        Serial.println(mqtt);  
        
      }    

      //RESTA
      if(digitalRead(PIN_BOTON_3) == LOW)
      {
        estadoBoton3 = true;
        Serial.println("BOTON_PRESIONADO");
      }
      if(digitalRead(PIN_BOTON_3) == HIGH && estadoBoton3 == true)
      {
        estadoBoton3 = false;
        Serial.println("BOTON_SUELTO");
        mqtt = mqtt--;
        Serial.println(mqtt);  
      }    
      
      //HUMEDAD A DISPLAY
      if(digitalRead(PIN_BOTON_1) == LOW && estadoBoton1 == true) 
      {
        estado = CHECK_BOTON;
      }

      //HUMEDAD A GMT
      if(digitalRead(PIN_BOTON_4) == LOW && pantalla == 4) 
      {
        pantalla = 1;
        estado = CHECK_BOTON;
      }
    }
    break;

}

//Función conexión WiFi
void initWiFi() 
{                                         
  WiFi.begin(ssid , password );
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

//Funciones Tiempo
void setup_rtc_ntp(void)
{
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  timestamp = time(NULL);
  rtc.setTime(timestamp + gmtOffset_sec);
}


void pedir_lahora(void)
{
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Veo la hora del rtc interno ");
    timestamp = rtc.getEpoch() - gmtOffset_sec;
    timeinfo = rtc.getTimeStruct();
  }

  else
  {
    Serial.print("NTP Time:");
    timestamp = time(NULL);
  }

  return;
}
