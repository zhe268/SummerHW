int incomeByte[6];        //紀錄感測器資料
int data;                 //紀錄讀取到的感測器資料
int z=0;                
int sum;
 
void setup()
{
  Serial.begin(9600);     //監控視窗鮑率
  Serial1.begin(2400);    //粉塵感測器傳輸鮑率
  Serial.println("waiting......");
  delay(2000);
}
 
void loop(){
  while (Serial1.available()>0){    //接收到感測器傳送資料訊息
     data=Serial1.read();           //讀取感測器資料
     delay(1000);
    if(data == 170){                //紀錄感測器感測資料
      z=0;
      incomeByte[z]=data;
    }
    else{
      z++;
      incomeByte[z]=data;
    } 
    if(z==6)                      //讀取感測器資料驗證
    {
      sum=incomeByte[1]+ incomeByte[2]+ incomeByte[3] + incomeByte[4];
      if(incomeByte[5]==sum && incomeByte[6]==255 )   //判斷讀區之資料是否有效
      {
        for(int k=0;k<7;k++)            //顯示讀取到的資料及空氣品質數值
        {
          Serial.print(incomeByte[k]);
          Serial.print("|");
        }
        Serial.print(" Vo=");
        float vo=(incomeByte[1]*256.0+incomeByte[2])/1024.0*5.00;
        Serial.print(vo,3);
        Serial.print("v | ");
        float c=vo*700;
        Serial.print(" PM2.5 = ");
        Serial.print(c,2);
        Serial.print("ug/m3 ");
        Serial.println();
      }
      else{
        Serial1.flush();
        for(int m=0;m<7;m++){
          incomeByte[m]=0;
        }
      }
    }
  } 
}
