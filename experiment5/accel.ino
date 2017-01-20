MPU9150 sensor9axis;

void accel_init() {
  // 加速度センサーの初期化
  Serial.print("Initializing mpu9150...");
  sensor9axis.initialize();

  if ( sensor9axis.testConnection() ) {
    Serial.println("connection successful");
  } else {
    stop_arduino();
  }
}

float get_accel_mag() {
  int16_t ai[3] = {0, 0, 0};
  int16_t gi[3] = {0, 0, 0};
  int16_t mi[3] = {0, 0, 0};

  sensor9axis.getMotion9(&ai[0], &ai[1], &ai[2], &gi[0], &gi[1], &gi[2], &mi[0], &mi[1], &mi[2]);

  // 加速度を計算
  float x = 2.0f * (float)ai[0] / 32768.0f;
  float y = 2.0f * (float)ai[1] / 32768.0f;
  float z = 2.0f * (float)ai[2] / 32768.0f;

  // ノルムを返す
  return sqrt(x*x+y*y+z*z);
}

