typedef enum {Init, WaitingForTime1, WaitingForTime2, WaitingForTime3} state_t;

typedef struct { //contains current status of state and values
    state_t curState;
    int curTime;
    int sensorTotal;
    int sensorCount;
} status_t;

void status_init(status_t *state);
int StateMachine(status_t *curStatus, int timeInc, int sensorVal);
