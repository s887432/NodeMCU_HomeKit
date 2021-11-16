#include <Arduino.h>
#include <arduino_homekit_server.h>

#include "wifi_info.h"
#include "wificonfig.h"

#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

#define PIN_KEY     4
#define PIN_CTRL    5

void setup() {
  int flag = 0;
  Serial.begin(115200);

  pinMode(PIN_KEY, INPUT);
  pinMode(PIN_CTRL, OUTPUT);

  flag = digitalRead(PIN_KEY);

  if( flag == 1 ) {
    //key pressed
    Serial.println("Force go into WiFi configure mode");  
    digitalWrite(PIN_CTRL, LOW);
  } else {
    //key is not pressed
    for(int i=0; i<3; i++) {
      digitalWrite(PIN_CTRL, HIGH);
      delay(300);
      digitalWrite(PIN_CTRL, LOW);
      delay(300);
    }
  }

  WiFiConfig.connectWiFi(flag);
  homekit_storage_reset(); // to remove the previous HomeKit pairing storage when you first run this new HomeKit example
  my_homekit_setup();
}

void loop() {
	my_homekit_loop();
	delay(10);
}

//==============================
// HomeKit setup and loop
//==============================

// access your HomeKit characteristics defined in my_accessory.c
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on;

static uint32_t next_heap_millis = 0;

//Called when the switch value is changed by iOS Home APP
void cha_switch_on_setter(const homekit_value_t value) {
	bool on = value.bool_value;
	cha_switch_on.value.bool_value = on;	//sync the value
	LOG_D("Switch: %s", on ? "ON" : "OFF");
	digitalWrite(PIN_CTRL, on ? LOW : HIGH);
}

void my_homekit_setup() {
	pinMode(PIN_CTRL, OUTPUT);
	digitalWrite(PIN_CTRL, LOW);

	//Add the .setter function to get the switch-event sent from iOS Home APP.
	//The .setter should be added before arduino_homekit_setup.
	//HomeKit sever uses the .setter_ex internally, see homekit_accessories_init function.
	//Maybe this is a legacy design issue in the original esp-homekit library,
	//and I have no reason to modify this "feature".
	cha_switch_on.setter = cha_switch_on_setter;
	arduino_homekit_setup(&config);

	//report the switch value to HomeKit if it is changed (e.g. by a physical button)
	//bool switch_is_on = true/false;
	//cha_switch_on.value.bool_value = switch_is_on;
	//homekit_characteristic_notify(&cha_switch_on, cha_switch_on.value);
}

void my_homekit_loop() {
	arduino_homekit_loop();
	const uint32_t t = millis();
	if (t > next_heap_millis) {
		// show heap info every 5 seconds
		next_heap_millis = t + 5 * 1000;
		LOG_D("Free heap: %d, HomeKit clients: %d",
				ESP.getFreeHeap(), arduino_homekit_connected_clients_count());

	}
}
