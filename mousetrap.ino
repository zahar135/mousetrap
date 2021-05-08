
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266TelegramBOT.h>
#define PIN_TRIG 5
#define PIN_ECHO 4
 

int t;
long duration, cm;

 

WiFiClientSecure client;
// Initialize Wifi connection to the router
char ssid[] = "Len_NEW";        // Имя точки доступа
char password[] = "*******";  // Пароль от точки доступа
int status = 0;


// Initialize Telegram BOT

#define BOTtoken "****************************************"  //Токен бота 
#define BOTname "Mouse" // Имя бота
#define BOTusername "Mouse135_bot" // Логин бота
TelegramBOT bot(BOTtoken, BOTname, BOTusername);

int Bot_mtbs = 1000; //среднее время между сканированием сообщений
long Bot_lasttime;   //

bool Start = false;



/


void setup() {
  
  Serial.begin (9600);
  //delay(3000);

  byte test();
 pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
pinMode(2, OUTPUT);
digitalWrite(2, HIGH);

  
 client.setInsecure();
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
 
  // Подключаемся к Wifi:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  
  bot.begin();      // Включаем бота
}




void loop() {
// Сначала генерируем короткий импульс длительностью 2-5 микросекунд.

label:

  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);

  // Выставив высокий уровень сигнала, ждем около 10 микросекунд. В этот момент датчик будет посылать сигналы с частотой 40 КГц.
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  //  Время задержки акустического сигнала на эхолокаторе.
  duration = pulseIn(PIN_ECHO, HIGH);

  // Теперь осталось преобразовать время в расстояние
  cm = (duration / 2) / 29.1;

  delay(50);
int t = (cm);
if ( t > 10) 
{ goto label;  }




if ( t <= 10){
  Bot_lasttime = 0;
       digitalWrite(2, LOW);
      Serial.print("Есть движение ");
      Serial.print(cm);
      Serial.println(" см.");
      
delay(1000);// Время для работы электрошокера
digitalWrite(2, HIGH); 
   }
  
delay(50);  
  




if (millis() > Bot_lasttime + Bot_mtbs)  {
    
    bot.sendMessage("881742452", "Возможно поймалась мышь", ""); // Здесь вписываем ID чата с ботом
    
   
    Bot_lasttime = millis();
  }

    Serial.println(Bot_lasttime);
    

}


  
