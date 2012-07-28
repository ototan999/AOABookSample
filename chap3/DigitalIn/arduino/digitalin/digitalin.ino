#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

// スイッチのポートを定義
#define SWITCH A6

// AndroidAccessoryオブジェクト作成
AndroidAccessory acc("MyManufacturer",         // 製造者名
                "MyModel",                     // モデル名
                "This is a sample accessory",  // 説明文
                "1.0",                         // バージョン名
                "http://android.com",          // URL
                "0000000012345678");           // シリアル番号

byte previous; // スイッチの前回の状態を保持する変数

void setup()
{
  Serial.begin(115200);
  Serial.print("\r\nStart");

  pinMode(SWITCH, INPUT);
  digitalWrite(SWITCH, HIGH); // プルアップを有効にする

  previous = digitalRead(SWITCH); // スイッチ初期状態を読み込む

  acc.powerOn();
}

void loop()
{
  byte status;
  byte msg[1];

  if (acc.isConnected()) {
    // スイッチのポートを読み込む
    status = digitalRead(SWITCH);
    if (status != previous) {
      // 変化があった場合、Androidに通知する
      Serial.print("status changed");
      msg[0] = status ? 1 : 0;

      // Androidへ通知
      acc.write(msg, sizeof(msg));
      previous = status;
    }
  }
  
  delay(1);
}
