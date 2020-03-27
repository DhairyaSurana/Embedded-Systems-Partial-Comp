/* State Machine Enumeration Structure*/

#include "sensor_queue.h"

typedef enum {init, waiting_for_time1, waiting_for_time2, 
                waiting_for_time3} sensor_state;

/* State Machine Structure*/
typedef int timeVal_t;
typedef int sensorVal_t;
typedef struct { int curTime; int sensorTotal;
                    int sensorCount; char direction;} sensor_struct;

void sensorStructInit(sensor_struct *state);

void printSensorInfo(sensor_struct *sensor, data_struct *sens_msg);
    
