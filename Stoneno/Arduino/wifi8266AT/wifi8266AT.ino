#include <dht.h>   
#define dht_dpin 8          //定義訊號要從Pin 8 進來  
dht DHT;   
#define baudrate   115200
//-- IoT Information
#define SSID "Xiaomi_4823"
#define PASS "09090909"
#define IP "184.106.153.149"  // ThingSpeak IP Address: 184.106.153.149
// 使用 GET 傳送資料的格式
// GET /update?key=[THINGSPEAK_KEY]&field1=[data 1]&filed2=[data 2]...;
String GET = "GET /update?key=ENOSD6ERB2228A9B";

void setup() {
    Serial.begin( baudrate );
    Serial.println("AT");
    delay(3000);
    if(Serial.find("OK"))
    {
        Serial.println("RECEIVED: OK\nData ready to sent!");
        connectWiFi();
    }
    else{
    Serial.println("NO RESEPONCE!");
  }
}
void loop() {
    delay(10000);   // 10 second
    DHT.read11(dht_dpin);   //去library裡面找DHT.read11  
    int temp = DHT.temperature ;
    int humi = DHT.humidity ;
    delay(500);
    SentOnCloud( String(temp), String(humi) );
}

boolean connectWiFi()
{
    String cmd="AT+CWJAP=\"";
    cmd+=SSID;
    cmd+="\",\"";
    cmd+=PASS;
    cmd+="\"";
    Serial.println(cmd);
    delay(3000);
    while(1){
      if(Serial.find("OK"))
      {
        Serial.println("Connect AP: OK");
        break;
      }
      else
      {
        Serial.println("Connect AP: Error");
      }
    }
}
void SentOnCloud( String T, String H )
{
    // 設定 ESP8266 作為 Client 端
    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += IP;
    cmd += "\",80";
    Serial.println(cmd);
//    esp8266.println(cmd);
    delay(2000);
    if( Serial.find( "Error" ) )
    {
        Serial.print( "CIPSTART: Error\nExit1" );
        return;
    }
    cmd = GET + "&field1=" + T + "&field2=" + H +"\r\n";//資料放上THINK網站
    //Serial.println( cmd.length());
    Serial.print( "AT+CIPSEND=" );
    Serial.println( cmd.length() );
    if(Serial.find( ">" ) )
    {
        Serial.print(">");
        Serial.print(cmd);
  //      esp8266.print(cmd);
    }
    else
    {
        Serial.print( "AT+CIPCLOSE" );
    }
    if( Serial.find("OK") )
    {
        Serial.println( "Data send: OK" );
    }
    else
    {
        Serial.println( "Data send: Error\nExit2" );
    }
}

