
//var sock = new WebSocket("wss://echo.websocket.org");
var sock = new WebSocket("ws://127.0.0.1:8000");
sock.onopen = function(event) {
    alert("websock opened")
    setTimeout(function() {
        sock.send("test 1 2 3");
    }, 1000);
}
sock.onmessage = function(event) {
    console.log("onmessage ev:", event);
};
