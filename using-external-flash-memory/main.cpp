/**
 * Please note that this code is an extract from a larger project 
 * It outlines the major steps and structure you would implement 
 * 
 * Please report any error, ommission and/or improvement by cresting an issue
 * 
 * Some of the features of the DataLoger class have not been implemented - coming soon
 * /

#include "logger.h"

/* data logging */
uint8_t cs_pin = 5;
uint8_t flash_led_pin = 4;
char filename[] = "log.bin";   
uint32_t FILE_SIZE_512K = 524288L;  // 512KB
uint32_t FILE_SIZE_1M  = 1048576L;  // 1MB
uint32_t FILE_SIZE_4M  = 4194304L;  // 4MB
SerialFlashFile file;
unsigned long long previous_log_time = 0, current_log_time = 0;
uint16_t log_sample_interval = 10; // log data to flash every 10 ms
DataLogger data_logger(cs_pin, flash_led_pin, filename, file,  FILE_SIZE_4M);

/* example data */
typedef struct {
    uint8_t device_state;
    float co2_level;
    float temperature;
    float battery_voltage;

} sensor_data_type_t;


sensor_data_type_t sensor_data;


// READ SENSORS - somewhere in the superloop or a task in RTOS
void readSensors() {
    sensor_data.device_state = getState();
    sensor_data.co2_level = readCO2Level();
    sensor_data.temperature = readTemperature();
    sensor_data.battery_voltage = readVoltage();
}


void setup() {
	// do your setup here
	Serial.begin(115200);

	// init data logger
	data_logger.loggerInit();

}

void loop() {

	current_log_time = millis();

	// is it time to record?
    if(current_log_time - previous_log_time > log_sample_interval) {
        readSensors();
        data_logger.loggerWrite(sensor_data);
    }

}