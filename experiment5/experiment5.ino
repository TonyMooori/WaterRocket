#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Servo.h>
#include "I2Cdev.h"
#include "MPU9150.h"
#include "TopDetector.h"

#define ACCEL_TIME        100   // 加速されている時間[ms]
#define PIN_SERVO         10    // サーボのピン
#define ACCEL_THRESHOLD   2.0   // 加速度のノルムがこれを超えたら始まる
#define N_NECESSARY       20    // 最低限必要なデータ数
#define N_DATA            10    // データ数

Servo servo;
TopDetector td;
bool is_started;
float top_time;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // サーボ初期化
  servo.attach(PIN_SERVO);
  servo.write(0);

  // 気圧センサ初期化
  pres_init();
  accel_init();

  // 変数の初期化
  td.reset();
  is_started = false;
  top_time = 1e5;    // 適当な大きい数字
}

void loop() {
  if ( is_started == false) {
    // 大きな加速度が検出されるまで待つ
    is_started |= get_accel_mag() > ACCEL_THRESHOLD;

    // trueになったとき，上向きの加速度があるため少し待つ
    if( is_started )
      delay(ACCEL_TIME);
    
  } else {
    // 加速度が検出された場合，計算していく

    float t = millis() / 1000.0f;   // 時間
    float y = get_height();         // 高度
    td.push(t, y);

    // N_DATAだけ貯まるごとに頂点時間を更新
    if (td.get_n_data() >= N_NECESSARY && td.get_n_data() % N_DATA == 0 ) {
      td.calc();
      top_time = td.get_top_time();
    }

    Serial.print("time\t");
    Serial.print(t);
    Serial.print("\ty\t");
    Serial.print(y);
    Serial.print("\tend\t");
    Serial.print(top_time);
    Serial.print("\n");

    // 頂点時間を過ぎたらサーボを動かしてパラシュートを展開する
    if ( t > top_time ) {
      servo.write(90);
      stop_arduino();  // 停止
    }
  }
}

