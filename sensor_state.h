/* State Machine Enumeration Structure*/

typedef enum {init, waiting_for_time1, waiting_for_time2, 
                waiting_for_time3, waiting_for_time4} sensor_state;

/* State Machine Structure*/
typedef int timeVal_t;
typedef int sensorVal_t;
typedef struct { int curTime; sensor_state curState; int sensorTotal; 
                    int sensorCount; int sensorAvg; char direction;} sensor_struct;

sensor_struct sensorStructInit(sensor_struct *state);
int FSM(sensor_struct *externalState, timeVal_t timeInc, 
sensorVal_t sensorVal, char direction);
    
