float pres0;    // 海面気圧
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void pres_init() {
  sensors_event_t event;
  
  // 接続テスト
  Serial.print("Initializing bmp180...");
  if ( bmp.begin() ) {
    // 接続成功
    Serial.println("connection successful");
    bmp.getEvent(&event);
    pres0 = event.pressure;   // 海面気圧を設定
  } else {
    // 接続失敗
    Serial.println("connection failed");
    stop_arduino();
  }
}

float get_height(){
  sensors_event_t event;
  bmp.getEvent(&event);

  // 高度を返す
  return bmp.pressureToAltitude(pres0, event.pressure);
}

