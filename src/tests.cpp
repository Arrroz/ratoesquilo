#include "tests.hpp"

#define DISPLAY_TEST_STAGE_SIZE 10
void testDisplay(Display *display) {
    static uint16_t stage = 0;

    if(stage < DISPLAY_TEST_STAGE_SIZE)
        display->print("\nA");
    else if(stage < DISPLAY_TEST_STAGE_SIZE*2)
        display->print("\nARE");
    else if(stage < DISPLAY_TEST_STAGE_SIZE*3)
        display->print("\nARESOL");
    else if(stage < DISPLAY_TEST_STAGE_SIZE*4)
        display->print("\nARESOLVI");
    else if(stage < DISPLAY_TEST_STAGE_SIZE*5)
        display->print("\nARESOLVIDAO");
    else
        stage = 0;
    
    stage++;
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
#define LS_TEST_RECTANGLE_WIDTH display->getWidth()/lineSensors->sensorCount - LS_TEST_RECTANGLE_SPACING
#define LS_TEST_RECTANGLE_HEIGHT display->getHeight()/2
#define LS_THRESHOLD 200
void testLineSensors(LineSensors *lineSensors, Display *display) {
    lineSensors->update();

    if(display) {
        display->firstPage();
        do {
            display->drawStr(0, 20, "Line Sensors");
            for(uint8_t i = 0; i < lineSensors->sensorCount; i++) {
                if(lineSensors->values[lineSensors->sensorCount-i-1] <= LS_THRESHOLD){ // flip the index to match the display with the sensor locations
                    display->drawRBox(i*(LS_TEST_RECTANGLE_WIDTH+LS_TEST_RECTANGLE_SPACING), display->getHeight()/2,
                                      LS_TEST_RECTANGLE_WIDTH, LS_TEST_RECTANGLE_HEIGHT,
                                      3);
                }
                else {
                    display->drawRFrame(i*(LS_TEST_RECTANGLE_WIDTH+LS_TEST_RECTANGLE_SPACING), display->getHeight()/2,
                                        LS_TEST_RECTANGLE_WIDTH, LS_TEST_RECTANGLE_HEIGHT,
                                        3);
                }
            }
        } while(display->nextPage());
    }

    for(uint8_t i = 0; i < lineSensors->sensorCount; i++) {
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

#define MOTORS_TEST_STAGE_SIZE 20
#define MOTOR_TEST_SPEED 0.2
void testMotors(Motor *motorL, Motor *motorR, Display *display) {
    static uint16_t stage = 0;

    if(stage < MOTORS_TEST_STAGE_SIZE) {
        if(display) display->print("Motors\nLeft");
        Serial.println("Left");
        motorL->input = MOTOR_TEST_SPEED;
        motorR->input = 0;
    }
    else if(stage < MOTORS_TEST_STAGE_SIZE*2) {
        if(display) display->print("Motors\nRight");
        Serial.println("Right");
        motorL->input = 0;
        motorR->input = MOTOR_TEST_SPEED;
    }
    else if(stage < MOTORS_TEST_STAGE_SIZE*3) {
        if(display) display->print("Motors\nForward");
        Serial.println("Forward");
        motorL->input = MOTOR_TEST_SPEED;
        motorR->input = MOTOR_TEST_SPEED;
    }
    else if(stage < MOTORS_TEST_STAGE_SIZE*4) {
        if(display) display->print("Motors\nBack");
        Serial.println("Back");
        motorL->input = -MOTOR_TEST_SPEED;
        motorR->input = -MOTOR_TEST_SPEED;
    }
    else if(stage < MOTORS_TEST_STAGE_SIZE*5) {
        if(display) display->print("Motors\nStop");
        Serial.println("Stop");
        motorL->stop();
        motorR->stop();
    }
    else
        stage = 0;
    
    motorL->update();
    motorR->update();

    stage++;
}
