# 通过http请求实现远程控制433Mhz遥控器

## 内容物

- rc_receive 接收端
- rc_emqx   发射端
- mqtt_server  服务端

## 运行环境

- node.js 23.3
- emqx server  5.8.3
- Arduino
- esp8266 NodeMCU 开发板
- 433Mhz 射频接收模块
- 433Mhz 射频发射模块

## 配置

- 使用rc_receive 接收端代码配置开发板接收 433Mhz 非滚动信号并记录
- 将信号值配置入rc_emqx中
- 修改rc_emqx中 mqtt部分连接信息
- 修改`mqtt_server/service/mqtt.js`中端mqtt部分配置信息
- 完成

