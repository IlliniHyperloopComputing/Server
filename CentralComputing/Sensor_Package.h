#ifndef SENSOR_PACKAGE_H
#define SENSOR_PACKAGE_H

#include <map>
#include <vector>
#include <thread>
#include <mutex>

#include "Sensor.h"
#include "Spi.h"

using namespace std;

class Sensor_Package {
	public:	
		/**
		* Creates a SensorPackage
		* @param  configuration a vector of sensor configurations for each sensor.  Initalized in the main thread
		**/
		Sensor_Package(vector<Sensor_Configuration> configuration, bool xmega_connect);

		/**
		* Destructor, cleans up map and deletes sensor_group objects
		**/
		~Sensor_Package();

		/**
		* Calls update on every sensor group
		* @param transfer the Xmega transfer struct
		**/
		void update(Xmega_Transfer & transfer);

		/**
		* Sends a reset command to each sensor group
		**/
		void reset(); 

		/**
		* Returns a vector of the sensor data from a sensor group
		* @return a vector of sensor data
		**/
		vector<double> get_sensor_data(Sensor_Type type);
    
		/**
		* Prints the status of all sensors to output.  For debugging only
		**/
		void print_status();

		static long long get_current_time();
		static long long start_time;
		bool connect;

    static uint8_t * bpi1;
    static uint8_t * bpi2;
    static Xmega_Setup x1;
    static Xmega_Setup x2;
	private:
		map<Sensor_Type, Sensor_Group * > sensor_groups;
		Spi * spi;	
};

#endif
