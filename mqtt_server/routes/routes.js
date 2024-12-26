// 导入 express 模块
const express = require("express");

const authService = require("../service/auth");
const mqttService = require("../service/mqtt");

// 创建一个 Express 应用实例
const app = express();
app.use(express.json());
// 设置一个简单的路由，响应 GET 请求
app.get("/", (req, res) => {
  res.send("blinker bridge server");
});

app.post("/public", (req, res) => {
  if (authService.check(req, res)) {
    const { topic, message } = req.body;
    mqttService.publish(topic, message);
    res.send({msg: "ok"});
  }
});

module.exports = app;
