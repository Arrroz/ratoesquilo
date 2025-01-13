#include "tests.hpp"

#define DISPLAY_TEST_TIME 3000 // in milliseconds
void testDisplay(Display *display, unsigned long time) {
    if(time % DISPLAY_TEST_TIME < DISPLAY_TEST_TIME/5)
        display->print("\nA");
    else if(time % DISPLAY_TEST_TIME < DISPLAY_TEST_TIME*2/5)
        display->print("\nARE");
    else if(time % DISPLAY_TEST_TIME < DISPLAY_TEST_TIME*3/5)
        display->print("\nARESOL");
    else if(time % DISPLAY_TEST_TIME < DISPLAY_TEST_TIME*4/5)
        display->print("\nARESOLVI");
    else
        display->print("\nARESOLVIDAO");
}

void testLightSensor(Display *display) {
    float lux = getLux();

    switch(illuminated()) {
        case 1:
            if(display) display->print("Light On\n", lux);
            Serial.print("Light On\t");
            Serial.println(lux);
            break;

        case 0:
            if(display) display->print("Light off\n", lux);
            Serial.print("Light off\t");
            Serial.println(lux);
            break;
        
        default:
            if(display) display->print("Light Sensor\nError");
            Serial.println("Error");
            break;
    }
}

#define LS_TEST_RECTANGLE_SPACING 2
#define LS_TEST_RECTANGLE_WIDTH SCREEN_WIDTH/LINE_SENSOR_COUNT - LS_TEST_RECTANGLE_SPACING/2
#define LS_TEST_RECTANGLE_HEIGHT SCREEN_HEIGHT/2
#define LS_THRESHOLD 200
void testLineSensors(LineSensors *lineSensors, Display *display) {
    lineSensors->update();

    if(display) {
        display->firstPage();
        do {
            display->drawStr(0, 20, "Line Sensors");
            for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
                if(lineSensors->values[LINE_SENSOR_COUNT-i-1] <= LS_THRESHOLD){ // flip the index to match the display with the sensor locations
                    display->drawRBox(i*(LS_TEST_RECTANGLE_WIDTH+LS_TEST_RECTANGLE_SPACING), SCREEN_HEIGHT/2,
                                      LS_TEST_RECTANGLE_WIDTH, LS_TEST_RECTANGLE_HEIGHT,
                                      4);
                }
                else {
                    display->drawRFrame(i*(LS_TEST_RECTANGLE_WIDTH+LS_TEST_RECTANGLE_SPACING), SCREEN_HEIGHT/2,
                                        LS_TEST_RECTANGLE_WIDTH, LS_TEST_RECTANGLE_HEIGHT,
                                        4);
                }
            }
        } while(display->nextPage());
    }

    for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
        Serial.print(lineSensors->values[i]);
        Serial.print('\t');
    }
    Serial.println();
}

void testEncoders(Encoder *encoderL, Encoder *encoderR, Display *display) {
    static float distL = 0, distR = 0;

    encoderL->updateSpeed();
    encoderR->updateSpeed();
    distL += encoderL->speed;
    distR += encoderR->speed;

    if(display) display->print("Encoders\n", distL, "     ", distR);
    Serial.print(distL);
    Serial.print("\t");
    Serial.println(distR);
}

#define MOTORS_TEST_TIME 5000 // in milliseconds
#define MOTOR_TEST_SPEED 0.2
void testMotors(Motor *motorL, Motor *motorR, unsigned long time, Display *display) {
    if(time % MOTORS_TEST_TIME < MOTORS_TEST_TIME/5) {
        if(display) display->print("Motors\nLeft");
        Serial.println("Left");
        motorL->input = MOTOR_TEST_SPEED;
        motorR->input = 0;
    }
    else if(time % MOTORS_TEST_TIME < MOTORS_TEST_TIME*2/5) {
        if(display) display->print("Motors\nRight");
        Serial.println("Right");
        motorL->input = 0;
        motorR->input = MOTOR_TEST_SPEED;
    }
    else if(time % MOTORS_TEST_TIME < MOTORS_TEST_TIME*3/5) {
        if(display) display->print("Motors\nForward");
        Serial.println("Forward");
        motorL->input = MOTOR_TEST_SPEED;
        motorR->input = MOTOR_TEST_SPEED;
    }
    else if(time % MOTORS_TEST_TIME < MOTORS_TEST_TIME*4/5) {
        if(display) display->print("Motors\nBack");
        Serial.println("Back");
        motorL->input = -MOTOR_TEST_SPEED;
        motorR->input = -MOTOR_TEST_SPEED;
    }
    else {
        if(display) display->print("Motors\nStop");
        Serial.println("Stop");
        motorL->stop();
        motorR->stop();
    }
    
    motorL->update();
    motorR->update();
}
