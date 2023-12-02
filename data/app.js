"use strict";

//------------------------------------------------- ESP Back-end Functions -------------------------------------------//
var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
window.addEventListener("load", onLoad);

function onLoad(event) {
  initWebSocket();
}

function initWebSocket() {
  console.log("Trying to open a WebSocket connection...");
  websocket = new WebSocket(gateway);
  websocket.onopen = onOpen;
  websocket.onclose = onClose;
  websocket.onmessage = onMessage;
}

function onOpen(event) {
  console.log("Connection opened, requesting data from Server");
  websocket.send("getStates");
}

function onClose(event) {
  console.log("Connection closed");
  setTimeout(initWebSocket, 2000);
}

function onMessage(event) {
  var data = event.data;

  if(data == "ON") {
    document.getElementById("liveState").innerHTML  = "Solar Relay State: ON";
    document.getElementById("SolarRelayToggle").checked = true;
    return;
  }

  if(data == "OFF") {
    document.getElementById("liveState").innerHTML  = "Solar Relay State: OFF";
    document.getElementById("SolarRelayToggle").checked = false;
    return;
  }

  var jsonData = JSON.parse(event.data);
  var keys = Object.keys(jsonData);

  for (var i = 0; i < keys.length; i++) {
    var key = keys[i];

    if (key.includes("Time")) {
      document.getElementById("time").innerHTML  = jsonData[key];
    }
  }
}

function toggleSolarRelay(element) {
    if(element.checked) {
      console.log("Turning On Relay");
      websocket.send("solarRelayOn");
    }
    else {
      console.log("Turning Off Relay");
      websocket.send("solarRelayOff");
    }
}
