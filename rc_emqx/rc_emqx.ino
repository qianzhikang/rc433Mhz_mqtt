#include <RCSwitch.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 
#include <PubSubClient.h>
#include <ArduinoJson.h>


// MQTT Broker 配置

const char *mqtt_broker = "192.168.31.33";
const char *topic = "gate";
const char *mqtt_username = "gate_rc";
const char *mqtt_password = "19991007";
const int mqtt_port = 1883;


// 初始化发射模块（连接到 D1 引脚）
RCSwitch mySwitchS = RCSwitch();

// emqx对象初始化
WiFiClient espClient;
PubSubClient client(espClient);


// 按钮回调函数
void openProcess()
{
  Serial.println("发送开门命令...");
  mySwitchS.send(2032908, 24);  // 发送24位命令，2042908是数字编码
  mySwitchS.send(2032908, 24);  // 发送24位命令，2042908是数字编码
  mySwitchS.send(2032908, 24);  // 发送24位命令，2042908是数字编码
}

// 按钮回调函数
void closeProcess()
{
  Serial.println("发送关门命令...");
  mySwitchS.send(2033088, 24);  // 发送24位命令，2033088是数字编码
  mySwitchS.send(2033088, 24);  // 发送24位命令，2033088是数字编码
  mySwitchS.send(2033088, 24);  // 发送24位命令，2033088是数字编码
}


// 按钮回调函数
void stopProcess()
{
  Serial.println("发送停止命令...");
  mySwitchS.send(2032944, 24);  // 发送24位命令，2032944是数字编码
  mySwitchS.send(2032944, 24);  // 发送24位命令，2032944是数字编码
  mySwitchS.send(2032944, 24);  // 发送24位命令，2032944是数字编码
}





// 订阅主题收到消息的回调
void callback(char *topic, byte *payload, unsigned int length) {
  
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  // char数组，用于中转换payload的数组
  char str[length];
  // 循环取出payload中的内容，赋值给str中转串
  for (int i = 0; i < length; i++) {
    str[i] = (char)payload[i];
    Serial.print((char)payload[i]);
  }
  // 创建ArduinoJson的转换对象
  StaticJsonDocument<32> doc;
  // 转换错误的异常对象
  DeserializationError error = deserializeJson(doc, str, length);
  // 转换错误时执行的逻辑
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  // 取出转换后的内容
  const char *msg = doc["message"];  // 当前状态
  String option = (String)msg;     // 将当前状态的char转换为string用于开关状态的判断
  
  Serial.println(option);
  Serial.println("-----------------------");

  // 处理对应消息
  if (option == "open") {
    openProcess();
  } else if (option == "close") {
    closeProcess();
  } else if (option == "stop") {
    stopProcess();
  } else {
    Serial.println("未识别的命令");
  }
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySwitchS.enableTransmit(D1);  // 设置数据发送引脚（D1）
  // 建立WiFiManager对象
  WiFiManager wifiManager;
  // 自动连接WiFi。以下语句的参数是连接ESP8266时的WiFi名称
  wifiManager.autoConnect("AutoConnectAP");
  // WiFi连接成功后将通过串口监视器输出连接成功信息
  Serial.println("");
  Serial.print("ESP8266 Connected to ");
  Serial.println(WiFi.SSID());  // WiFi名称
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());  // IP


  // mqtt服务器连接
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);  // 设置接收消息服务器值
  while (!client.connected()) {
    Serial.println("Connecting to public emqx mqtt broker.....");
    String client_id = "gate-rc";
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public emqx mqtt broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  // 订阅主题
  client.subscribe(topic);
}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
}
