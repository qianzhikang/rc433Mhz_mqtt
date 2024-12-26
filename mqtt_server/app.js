const app = require('./routes/routes')


// 设置端口并启动服务器
const PORT = 3000;
app.listen(PORT, '0.0.0.0', () => {
  console.log(`Server is running on port: ${PORT}`);
});
