#ifndef PID_H_
#define PID_H_

class PID_t {
    public:
        float error, iError, dError, prevError;
        float output;
        float kp, ki, kd, kf;

        PID_t(float kp, float ki = 0, float kd = 0, float kf = 0);
        float update(float ref, float value, float dt);
};

#endif
