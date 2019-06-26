#include "ADCManager.h"

bool ADCManager::initialize_source() {
  fileName = "/dev/iio:device0";
  inFile.open(fileName, std::ifstream::in | std::ifstream::binary);
  if (!inFile) {
    print(LogLevel::LOG_DEBUG, "ADC Manager setup failed\n");
    return false;
  } else {
    print(LogLevel::LOG_DEBUG, "ADC Manager setup successful\n");
    return true;
  }
}

void ADCManager::stop_source(){
  if (inFile) {
    inFile.close();
    print(LogLevel::LOG_DEBUG, "ADC Manager stopped\n");
  } else {
    print(LogLevel::LOG_DEBUG, "ADC Manager never opened\n");
  }
}

std::shared_ptr<ADCData> ADCManager::refresh() {
    std::shared_ptr<ADCData> new_data = std::make_shared<ADCData>();
    uint16_t buffer [NUM_ADC];
    inFile.read((char *) buffer, NUM_ADC * 2);
    for (int i = 0; i < NUM_ADC; i++) {
      uint16_t * val = (buffer + i);
      new_data -> accel[i] = (*val); //* 4096 / 1.8;
    }
    print(Utils::LOG_ERROR, "%d \t%d\t%d\t %d\t%d\t%d\t%d\t\n", new_data->accel[0], 
                            new_data->accel[1], new_data->accel[2], 
                            new_data->accel[3], new_data->accel[4],
                            new_data->accel[5], new_data->accel[6]);
    return new_data;
}

std::shared_ptr<ADCData> ADCManager::refresh_sim() {
  #ifdef SIM
  return SimulatorManager::sim.sim_get_adc();
  #else
  return empty_data();
  #endif
}

void ADCManager::initialize_sensor_error_configs() {
  if (!(ConfiguratorManager::config.getValue("error_accel_diff", error_accel_diff) && 
      ConfiguratorManager::config.getValue("error_pneumatic_1_over_pressure", error_pneumatic_1_over_pressure) &&
      ConfiguratorManager::config.getValue("error_pneumatic_2_over_pressure", error_pneumatic_2_over_pressure) &&
      ConfiguratorManager::config.getValue("error_pneumatic_3_over_pressure", error_pneumatic_3_over_pressure) &&
      ConfiguratorManager::config.getValue("error_pneumatic_4_over_pressure", error_pneumatic_4_over_pressure) &&
      ConfiguratorManager::config.getValue("error_battery_box_over_pressure",  error_battery_box_over_pressure) &&
      ConfiguratorManager::config.getValue("error_battery_box_under_pressure", error_battery_box_under_pressure))) {
    print(LogLevel::LOG_ERROR, "CONFIG FILE ERROR: ADCManager Missing necessary configuration\n");
    exit(1);
  }
  // For accelerometers
  // Get Standard Deviation to check against (or just the difference)

  // For other measurements
  // Pneumatic pressure over pressure 1
  // Pneumatic pressure over pressure 2
  // Pneumatic pressure over pressure 3
  // Pneumatic pressure over pressure 4
  // Battery Box over pressure
  // Battery Box under pressure
}

void ADCManager::check_for_sensor_error(const std::shared_ptr<ADCData> & check_data) {
}
