/*
 * M5StickC code for
 * M5.A.R.S Quad
 * based on the project
 * https://www.hackster.io/AJB2K3/m5-a-r-s-quad-372968
 *
 * The bot is controlled thanks to an bluetooth joypad
 * Please install ESP32 + Bluepad32 Arduino / M5Stick-C
 * Tested with M5Stick-C (first version)
 */


#include <M5StickC.h>
#include "M5ars.h"
#include <Bluepad32.h>

ControllerPtr myControllers[BP32_MAX_CONTROLLERS];

// the setup routine runs once when M5StickC starts up
void setup(){ 
  
  // Initialize the M5StickC object
  M5.begin();
  digitalWrite (M5_LED, HIGH); // turn off the LED
  pinMode(M5_LED, OUTPUT);
  digitalWrite (M5_LED, HIGH); // off

  // LCD display
  M5.Lcd.println("");
  M5.Lcd.println("");
  M5.Lcd.println("");
  M5.Lcd.println("   M5.A.R.S");

  // Initialize serial
  Serial.begin(115200);
  while (!Serial) {
    // wait for serial port to connect.
    // You don't have to do this in your game. This is only for debugging
    // purposes, so that you can see the output in the serial console.
    ;
  }

  Serial.println();
  Serial.println("M5.A.R.S");

  String fv = BP32.firmwareVersion();
  Serial.print("Firmware version installed: ");
  Serial.println(fv);

  // To get the BD Address (MAC address) call:
  const uint8_t* addr = BP32.localBdAddress();
  Serial.print("BD Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(addr[i], HEX);
    if (i < 5)
      Serial.print(":");
    else
      Serial.println();
  }

  IIC_Servo_Init();     //sda  0     scl  26 

  // This call is mandatory. It setups Bluepad32 and creates the callbacks.
  BP32.setup(&onConnectedController, &onDisconnectedController);

  // "forgetBluetoothKeys()" should be called when the user performs
  // a "device factory reset", or similar.
  // Calling "forgetBluetoothKeys" in setup() just as an example.
  // Forgetting Bluetooth keys prevents "paired" gamepads to reconnect.
  // But might also fix some connection / re-connection issues.
  BP32.forgetBluetoothKeys();
}

// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.
void onConnectedController(ControllerPtr ctl) {
  bool foundEmptySlot = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == nullptr) {
      Serial.print("CALLBACK: Controller is connected, index=");
      Serial.println(i);
      myControllers[i] = ctl;
      foundEmptySlot = true;

      // Optional, once the gamepad is connected, request further info about the
      // gamepad.
      ControllerProperties properties = ctl->getProperties();
      char buf[80];
      sprintf(buf,
              "BTAddr: %02x:%02x:%02x:%02x:%02x:%02x, VID/PID: %04x:%04x, "
              "flags: 0x%02x",
              properties.btaddr[0], properties.btaddr[1], properties.btaddr[2],
              properties.btaddr[3], properties.btaddr[4], properties.btaddr[5],
              properties.vendor_id, properties.product_id, properties.flags);
      Serial.println(buf);
      break;
    }
  }
  if (!foundEmptySlot) {
    Serial.println(
        "CALLBACK: Controller connected, but could not found empty slot");
  }
}

void onDisconnectedController(ControllerPtr ctl) {
  bool foundGamepad = false;

  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == ctl) {
      Serial.print("CALLBACK: Controller is disconnected from index=");
      Serial.println(i);
      myControllers[i] = nullptr;
      foundGamepad = true;
      break;
    }
  }

  if (!foundGamepad) {
    Serial.println(
        "CALLBACK: Controller disconnected, but not found in myControllers");
  }
}

void processGamepad(ControllerPtr gamepad) {
  // There are different ways to query whether a button is pressed.
  // By query each button individually:
  //  a(), b(), x(), y(), l1(), etc...

  if (gamepad->a()) {    
    // press A for initial position
    M5ars_position_start(100);
  }

  if (gamepad->b()) {
    //press B for down position
    for(int i=1;i<=4;i++)
    {
      M5ars_knee_set(i,60);
      //M5ars_leg_set(i,0);
    }   
  }

  if (gamepad->y())
  {
    char buf[256];
    for(int i=1;i<=4;i++)
    {
      snprintf(buf, sizeof(buf) - 1,
            "id=%d, leg: %4li, knee: %4li",
            i,        // Gamepad Index
            M5ars_leg_read(i),
            M5ars_knee_read(i)
      );      
      Serial.println(buf);
    } 
  }

  if (gamepad->axisY()<-500) {
    M5ars_forward(100);
  }
  else if (gamepad->axisY()>500) {
    M5ars_backward(100);
  }

  if (gamepad->axisX()<-500) {
    M5ars_turn_left(100);
  }
  else   if (gamepad->axisX()>500) {
    M5ars_turn_right(100);
  }
}

// the loop routine runs over and over again forever
void loop() {

  BP32.update();

  // It is safe to always do this before using the controller API.
  // This guarantees that the controller is valid and connected.
  for (int i = 0; i < BP32_MAX_CONTROLLERS; i++) {
    ControllerPtr myController = myControllers[i];

    if (myController && myController->isConnected()) {
      if (myController->isGamepad())
        processGamepad(myController);
    }
  }
  delay(50);
}
