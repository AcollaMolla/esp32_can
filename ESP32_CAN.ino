#include <driver/can.h>
#include <driver/gpio.h>

void setup(){
  Serial.begin(115200);
  setup_can_driver();
}

void setup_can_driver(){
  can_general_config_t general_config={
    .mode = CAN_MODE_ NORMAL,
    .tx_io = (gpio_num_t)GPIO_NUM_5,
    .rx_io = (gpio_num_t)GPIO_NUM_4,
    .clkout_io = (gpio_num)CAN_IO_UNUSED,
    .bus_off_io = (gpio_num)CAN_IO_UNUSED,
    .tx_queue_len = 0,
    .rx_queue_len = 65,
    .alerts_enable = CAN_ALERT_ALL,
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
}

void loop(){
  can_message_t rx_frame;
  if(can_receive(&rx_frame,pdMS_TO_TICKS(1000))==ESP_OK){
    Serial.println("new msg");
  }
}
