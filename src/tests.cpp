#include "tests.hpp"

#define DISPLAY_TEST_TIME 4000 // in milliseconds
void testDisplay(unsigned long time) {
    if(time % DISPLAY_TEST_TIME < DISPLAY_TEST_TIME/4)
        display.printAll("RE");
    else if(time % DISPLAY_TEST_TIME < DISPLAY_TEST_TIME*2/4)
        display.printAll("RESOL");
    else if(time % DISPLAY_TEST_TIME < DISPLAY_TEST_TIME*3/4)
        display.printAll("RESOLVI");
    else
        display.printAll("RESOLVIDAO");
}

// WARNING: all tests beyond this point, require the display to be working properly

void testLightSensor() {
    float lux = getLux();

    switch(illuminated()) {
        case 1:
            display.printAll("Light On\n", lux);
            Serial.print("Light On\t");
            Serial.println(lux);
            break;

        case 0:
            display.printAll("Light off\n", lux);
            Serial.print("Light off\t");
            Serial.println(lux);
            break;
        
        default:
            display.printAll("Error\n");
            Serial.println("Error");
            break;
    }
}

#define LS_TEST_RECTANGLE_SPACING 2
#define LS_TEST_RECTANGLE_WIDTH SCREEN_WIDTH/LINE_SENSOR_COUNT - LS_TEST_RECTANGLE_SPACING/2
#define LS_TEST_RECTANGLE_HEIGHT SCREEN_HEIGHT/2
#define LS_THRESHOLD 200
void testLineSensors() {
    lineSensors.update();

    display.clearDisplay();
    for(uint8_t i = 0; i < LINE_SENSOR_COUNT; i++) {
        display.drawRect(i*(LS_TEST_RECTANGLE_WIDTH+LS_TEST_RECTANGLE_SPACING), LS_TEST_RECTANGLE_HEIGHT/2,
                         LS_TEST_RECTANGLE_WIDTH, LS_TEST_RECTANGLE_HEIGHT,
                         WHITE);
        
        if(lineSensors.values[LINE_SENSOR_COUNT-i-1] <= LS_THRESHOLD){ // flip the index to match the display with the sensor locations
            display.fillRect(i*(LS_TEST_RECTANGLE_WIDTH+LS_TEST_RECTANGLE_SPACING), LS_TEST_RECTANGLE_HEIGHT/2,
                             LS_TEST_RECTANGLE_WIDTH, LS_TEST_RECTANGLE_HEIGHT,
                             WHITE);
        }
        
        Serial.print(lineSensors.values[i]);
        Serial.print('\t');
    }
    display.display();
    Serial.println();
}

void testEncoders() {
    static float distL = 0, distR = 0;

    encoderL.updateSpeed();
    encoderR.updateSpeed();
    distL += encoderL.speed;
    distR += encoderR.speed;

    display.printAll(distL, " ", distR);
    Serial.print(distL);
    Serial.print("\t");
    Serial.println(distR);
}

#define MOTORS_TEST_TIME 5000 // in milliseconds
#define MOTOR_TEST_SPEED 0.2
void testMotors(unsigned long time) {
    if(time % MOTORS_TEST_TIME < MOTORS_TEST_TIME/5) {
        display.printAll("Left");
        motorL.input = MOTOR_TEST_SPEED;
        motorR.input = 0;
    }
    else if(time % MOTORS_TEST_TIME < MOTORS_TEST_TIME*2/5) {
        display.printAll("Right");
        motorL.input = 0;
        motorR.input = MOTOR_TEST_SPEED;
    }
    else if(time % MOTORS_TEST_TIME < MOTORS_TEST_TIME*3/5) {
        display.printAll("Forward");
        motorL.input = MOTOR_TEST_SPEED;
        motorR.input = MOTOR_TEST_SPEED;
    }
    else if(time % MOTORS_TEST_TIME < MOTORS_TEST_TIME*4/5) {
        display.printAll("Back");
        motorL.input = -MOTOR_TEST_SPEED;
        motorR.input = -MOTOR_TEST_SPEED;
    }
    else {
        display.printAll("Stop");
        motorL.stop();
        motorR.stop();
    }
    
    motorL.update();
    motorR.update();
}
