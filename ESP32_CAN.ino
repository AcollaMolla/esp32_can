#include <driver/can.h>
#include <driver/gpio.h>

void setup(){
  Serial.begin(115200);
  Serial.println("setup");
  setup_can_driver();
}

void setup_can_driver(){
  can_general_config_t general_config={
    .mode = CAN_MODE_LISTEN_ONLY,
    .tx_io = (gpio_num_t)GPIO_NUM_5,
    .rx_io = (gpio_num_t)GPIO_NUM_4,
    .clkout_io = (gpio_num_t)CAN_IO_UNUSED,
    .bus_off_io = (gpio_num_t)CAN_IO_UNUSED,
    .tx_queue_len = 0,
    .rx_queue_len = 65,
    .alerts_enabled = CAN_ALERT_ALL,
    .clkout_divider = 0
  };

  can_timing_config_t timing_config = CAN_TIMING_CONFIG_125KBITS();
  can_filter_config_t filter_config = CAN_FILTER_CONFIG_ACCEPT_ALL();
  esp_err_t error;
  error = can_driver_install(&general_config, &timing_config, &filter_config);

  if(error==ESP_OK){
    Serial.println("Driver installed successfully");
  }
  else{
    Serial.println("Driver installation failed...");
    return;
  }
  if(can_start() == ESP_OK){
    Serial.println("started successfully!");
  }
  else{
    Serial.println("cant start driver...");
  }
}

void loop(){
  can_message_t rx_frame;
  uint32_t alerts;
  if(can_receive(&rx_frame,pdMS_TO_TICKS(1000))==ESP_OK){
    Serial.print(rx_frame.identifier);
    Serial.print(": ");
    if(!(rx_frame.flags & CAN_MSG_FLAG_RTR)){
      for(int i=0;i<rx_frame.data_length_code;i++){
        Serial.print(rx_frame.data[i]);
        Serial.print(",");
      }
      Serial.println();
    }
  }else{
    Serial.print(can_read_alerts(&alerts, pdMS_TO_TICKS(1000)));
  }
}
