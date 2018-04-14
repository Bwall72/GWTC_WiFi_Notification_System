#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "dweetESP8266.h"

#include "network.h"
#include "param.h"

void setup() {
  Serial.begin(115200);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUTTON, INPUT);

  // set all notifications to off
  for(k = 0; k < NUM_NOTIFICATIONS; k++)
    active[k] = 0;

  client.wifiConnection(SSID, PSWD);

  poll_time = millis() - 2000;
  led_time  = millis() - 500;
}

void loop() {

  run_dweet();

  run_led();

  check_reset();
}

void run_dweet()
{
  // poll dweet?
  if(millis() - poll_time > DELAY)
  {
    String value = client.getDweet(THING, "my_key");
    Serial.println("Value: " + value);
    if(value == keys[KEY0])
    {
      if(!active[KEY0])
        notifications++;
      active[KEY0] = 1;
      reset_dweet();
    }
    else if(value == keys[KEY1])
    {
      if(!active[KEY1])
        notifications++;
      active[KEY1] = 1;
      reset_dweet();
    }
    else if(value == keys[KEY2])
    {
      if(!active[KEY2])
        notifications++;
      active[KEY2] = 1;
      reset_dweet();
    }
    // add else if for all other notifications added
    poll_time = millis();
  }
}

void run_led()
{
  // RGB LED Control
  if(millis() - led_time > 500)
  {
    led_time = millis();
    if(active[j])
    {
      analogWrite(RED, red[j]);
      analogWrite(GREEN, green[j]);
      analogWrite(BLUE, blue[j]);
    }
    else if (notifications == 0)
    {
      RED_OFF;
      GREEN_OFF;
      BLUE_OFF;
    }
    j = (j + 1) % NUM_NOTIFICATIONS;
    print_active();
  }
}
// send post to dweet to cancel IFTTT post
void reset_dweet()
{
  http.begin("https://dweet.io/dweet/for/" + String(THING));
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST("?" + String("my_key") + "=False");
  http.end();
}

void check_reset()
{
  if(notifications && !digitalRead(BUTTON)) {
    Serial.println("Notifications Reset");
    notifications = 0;
    for(k = 0; k < NUM_NOTIFICATIONS; k++)
      active[k] = 0;
    delay(200);
  }
}

void print_active()
{
  Serial.println("Notifications: " + String(notifications));
  for(k = 0; k < NUM_NOTIFICATIONS; k++)
  {
    Serial.println(String(keys[k]) + ":" + String(active[k]));
  }
}

