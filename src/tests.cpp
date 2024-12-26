#include "tests.hpp"

#define DISPLAY_TEST_TIME 4000 // in milliseconds
void testDisplay(Display *display, unsigned long time) {
    if(time % DISPLAY_TEST_TIME < DISPLAY_TEST_TIME/4)
        display->printAll("RE");
    else if(time % DISPLAY_TEST_TIME < DISPLAY_TEST_TIME*2/4)
        display->printAll("RESOL");
    else if(time % DISPLAY_TEST_TIME < DISPLAY_TEST_TIME*3/4)
        display->printAll("RESOLVI");
    else
        display->printAll("RESOLVIDAO");
}

void testLightSensor(Display *display) {
    float lux = getLux();

    switch(illuminated()) {
        case 1:
            if(display) display->printAll("Light On\n", lux);
            Serial.print("Light On\t");
            Serial.println(lux);
            break;

        case 0:
            if(display) display->printAll("Light off\n", lux);
            Serial.print("Light off\t");
            Serial.println(lux);
            break;
        
        default:
            if(display) display->printAll("Error\n");
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

    if(display) display->clearDisplay();
    for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
        if(display) display->drawRect(i*(LS_TEST_RECTANGLE_WIDTH+LS_TEST_RECTANGLE_SPACING), LS_TEST_RECTANGLE_HEIGHT/2,
                                     LS_TEST_RECTANGLE_WIDTH, LS_TEST_RECTANGLE_HEIGHT,
                                     WHITE);
        
        if(lineSensors->values[LINE_SENSOR_COUNT-i-1] <= LS_THRESHOLD){ // flip the index to match the display with the sensor locations
            if(display) display->fillRect(i*(LS_TEST_RECTANGLE_WIDTH+LS_TEST_RECTANGLE_SPACING), LS_TEST_RECTANGLE_HEIGHT/2,
                                         LS_TEST_RECTANGLE_WIDTH, LS_TEST_RECTANGLE_HEIGHT,
                                         WHITE);
        }
        
        Serial.print(lineSensors->values[i]);
        Serial.print('\t');
    }
    if(display) display->display();
    Serial.println();
}

void testEncoders(Encoder *encoderL, Encoder *encoderR, Display *display) {
    static float distL = 0, distR = 0;

    encoderL->updateSpeed();
    encoderR->updateSpeed();
    distL += encoderL->speed;
    distR += encoderR->speed;

    if(display) display->printAll(distL, " ", distR);
    Serial.print(distL);
    Serial.print("\t");
    Serial.println(distR);
}

#define MOTORS_TEST_TIME 5000 // in milliseconds
#define MOTOR_TEST_SPEED 0.2
void testMotors(Motor *motorL, Motor *motorR, unsigned long time, Display *display) {
    if(time % MOTORS_TEST_TIME < MOTORS_TEST_TIME/5) {
        if(display) display->printAll("Left");
        Serial.println("Left");
        motorL->input = MOTOR_TEST_SPEED;
        motorR->input = 0;
    }
    else if(time % MOTORS_TEST_TIME < MOTORS_TEST_TIME*2/5) {
        if(display) display->printAll("Right");
        Serial.println("Right");
        motorL->input = 0;
        motorR->input = MOTOR_TEST_SPEED;
    }
    else if(time % MOTORS_TEST_TIME < MOTORS_TEST_TIME*3/5) {
        if(display) display->printAll("Forward");
        Serial.println("Forward");
        motorL->input = MOTOR_TEST_SPEED;
        motorR->input = MOTOR_TEST_SPEED;
    }
    else if(time % MOTORS_TEST_TIME < MOTORS_TEST_TIME*4/5) {
        if(display) display->printAll("Back");
        Serial.println("Back");
        motorL->input = -MOTOR_TEST_SPEED;
        motorR->input = -MOTOR_TEST_SPEED;
    }
    else {
        if(display) display->printAll("Stop");
        Serial.println("Stop");
        motorL->stop();
        motorR->stop();
    }
    
    motorL->update();
    motorR->update();
}
