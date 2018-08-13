#include <dht.h>   
dht DHT;   
#define dht_dpin 8          //定義訊號要從Pin 8 進來  

void setup()
{
  Serial.begin(9600);   
  delay(1000);             //等待 1 秒暖機
}

void loop()
{
  DHT.read11(dht_dpin);         //讀取DHT11數值  
  Serial.print("temperature: ");
  Serial.print(DHT.temperature);
  Serial.print("humidity:");
  Serial.println(DHT.humidity);
  delay(1000);
}  
