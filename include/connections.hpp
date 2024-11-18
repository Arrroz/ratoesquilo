#ifndef CONNECTIONS_H_
#define CONNECTIONS_H_

// Pinouts

#ifdef MEGA2560PRO

#define PINOUT_LS_EMMITER_EVEN 67
#define PINOUT_LS_EMMITER_ODD 68
#define PINOUT_LS_SENSORS (const uint8_t[]){66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54}

#define PINOUT_M_PWML 2
#define PINOUT_M_PWMR 4
#define PINOUT_M_DIRF 3
#define PINOUT_M_DIRB 5

#define PINOUT_ENC_LA 51
#define PINOUT_ENC_LB 50
#define PINOUT_ENC_RA 52
#define PINOUT_ENC_RB 53

#endif

#ifdef ESP32

#define PINOUT_LS_EMMITER_ODD 23
#define PINOUT_LS_EMMITER_EVEN 13
#define PINOUT_LS_SENSORS (const uint8_t[]){25, 26, 27, 14, 19, 18, 5, 17, 16, 4, 0, 2, 15}

#define PINOUT_M_PWML 32
#define PINOUT_M_PWMR 33
#define PINOUT_M_DIRF 33
#define PINOUT_M_DIRB 34

#define PINOUT_ENC_LA 25
#define PINOUT_ENC_LB 26
#define PINOUT_ENC_RA 27
#define PINOUT_ENC_RB 14

#endif

#endif
