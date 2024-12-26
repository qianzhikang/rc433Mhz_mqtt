#include <RCSwitch.h>
RCSwitch mySwitchR = RCSwitch();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySwitchR.enableReceive(D2);  // 设置接收引脚（D2）
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySwitchR.available()) {
    int value = mySwitchR.getReceivedValue();  // 获取接收到的值
    if (value != 0) {
      Serial.print("接收到的值：");
      Serial.println(value);  // 打印接收到的数据
    } else {
      Serial.println("未接收到有效信号");
    }
    mySwitchR.resetAvailable();  // 清除接收状态
  }
}
