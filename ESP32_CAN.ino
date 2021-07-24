#include <ESP32CAN.h>
#include <CAN_config.h>

CAN_device_t CAN_cfg;

void setup(){
  Serial.begin(115200);
  CAN_cfg.speed CAN_SPEED_125KBPS;
  CAN_cfg.tx_pin_id GPIO_NUM_5;
  CAN_cfg.rx_pin_id GPIO_NUM_4;

  CAN_cfg.rx_queue = xQueueCreate(10, sizeof(CAN_frame_t));
  ESP32Can.CANInit();
}

void loop(){
  CAN_frame_t rx_frame;
  if(xQueueReceive(CAN_cfg.rx_queue, rx_frame), 3 * portTICK_PERIOD_MS) == pdTRUE{
    Serial.println("received data");
  }
}
