void loraSetup(){
  drawProgressBar(0);
  //1
  Serial2.println("AT\r\n");
  delay(500);
  drawProgressBar(round((100/9)*1));
 
  //2
  Serial2.println("AT+MODE=" + String(loraMode) + "\r\n");
  delay(500);
  drawProgressBar(round((100/9)*2));
  
  //3
  Serial2.println("AT+IPR=" + String(baud) + "\r\n");
  delay(500);
  drawProgressBar(round((100/9)*3));
  
  //4
  Serial2.println("AT+PARAMETER=" + String(spread) + "," + String(bandwith) + "," + String(codingRate) + "," + String(preamble) + "\r\n");
  delay(500);
  drawProgressBar(round((100/9)*4));
  
  //5
  Serial2.println("AT+BAND=" + String(band) + "\r\n");
  delay(500);
  drawProgressBar(round((100/9)*5));
  
  //6
  Serial2.println("AT+ADDRESS=" + String(address) + "\r\n");
  delay(500);
  drawProgressBar(round((100/9)*6));
  
  //7
  Serial2.println("AT+NETWORKID=" + String(networkID) + "\r\n");
  delay(500);
  drawProgressBar(round((100/9)*7));
  
  //8
  Serial2.print("AT+CPIN=" + String(cpin) + "\r\n");
  delay(500);
  drawProgressBar(round((100/9)*8));
  
  //9
  Serial2.println("AT+CRFOP=" + String(crfop) + "\r\n");
  delay(500);
  drawProgressBar(round((100/9)*9));
}
