// Подключаем библиотеку и сразу же поднимаем сервер на 8080 порт.
var io = require('socket.io').listen(8080);
// Load the http module to create an http server.
var http = require('http');
var server = undefined;

io.sockets.on('connection', function (socket) {
  // Создаем HTTP server если он не был создан.
  if (!server) {
    server = http.createServer(function (request, response) {
      var body = '';
      request.on('data', function (data) {
        body += data;

        // Too much POST data, kill the connection!
        // 1e6 === 1 * Math.pow(10, 6) === 1 * 1000000 ~~~ 1MB
        if (body.length > 1e6)
          request.connection.destroy();
      });

      request.on('end', function () {
        var post = JSON.parse(body);

        if (post && post.id && post.info && post.class) {
          socket.broadcast.emit('stream', {id: post.id, info: post.info, class: post.class});
        }
      });

      response.writeHead(200, {"Content-Type": "text/plain"});
      // На запрос вызываем метод библиотеки socket.io
      // чтобы отослать данные подключенным постоянно клиентам.
      // Выводим сообщение.
      response.end("sent to client\n");
    });

    // Биндим Http server на 8300 порт, IP defaults to 127.0.0.1
    server.listen(8300);
  }
});