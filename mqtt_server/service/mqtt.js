// 导入 mqtt 库
const mqtt = require("mqtt");

// 连接到 MQTT 代理（例如 Mosquitto 或 HiveMQ）
const brokerUrl = "mqtt://192.168.31.33:1883"; 
// MQTT 连接选项，包含用户名和密码
const options = {
  username: "mqtt_manager", 
  password: "19991007", 
};


const client = mqtt.connect(brokerUrl, options);

// 连接成功后，订阅一个主题
client.on("connect", () => {
  console.log("Connected to MQTT broker");
});

// 处理连接错误
client.on("error", (err) => {
  console.log("Connection error:", err);
});

// 处理断开连接
client.on("close", () => {
  console.log("Disconnected from MQTT broker");
});

// 发送mqtt消息
function publish(topic, message) {
  client.publish(topic, message);
}

module.exports = {
  client,
  publish,
};
