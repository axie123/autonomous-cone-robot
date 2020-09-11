// This code is a modified template for the functionality of out LCD UI.

#include<stdio.h>
#include<stdlib.h>

typedef motors {
    bool begin_running;
    bool run;
    bool stop_running;
    bool start_reversing;
    bool apply_voltage;
}

typedef lcd{
    bool begin;
    bool print_on_screen;
    bool clear_screen;
}

typedef sensor{
    bool initiate;
    string check_on_what_its_sensing;
    bool stuff_detected;
    bool scan_surroundings;
    bool apply_voltage;
}

typedef arm{
    float position;
    bool grabbing;
    bool apply_voltage;
}


lcd.begin();
keypad.begin();
lcd.print_on_screen("Welcome to the cone deploying robot\n");
lcd.print_on_screen("Please select the option that you would like to take\n");
lcd.clear_screen();

lcd.print_on_screen("Press 1 for Deployment\n");
lcd.print_on_screen("Press 2 for Calibration\n");
lcd.print_on_screen("Press 3 to Restart\n");
lcd.print_on_screen("Press A to Restart\n");

if keypad.input() == "1" {
    status = calibration.check();
    if status == False {
        lcd.clear_screen();
        lcd.print_on_screen("Please calibrate the device first.");
        keypad.input() = none;
    }
    if else status == True {
        lcd.clear_screen();
        sensor.initiate();
        sensor.check_on_what_its_sensing();
        motors.begin_running();
        timer.begin();
        if sensor.initiate() == supposed {
            motors.run();
            if timer.distancetravelled() == 1 {
                timer.distance() += 1;
                if timer.distance() == 4 {
                    motors.stop_running();
                    motors.start_reversing();
                    timer.reset();
                }
            }
            if sensor.stuff_detected() = "crack" {
                motors.stop();
                position = arm.position(stack);
                arm.grabbing() == True;
                position = arm.position(sen1st_pos);
                arm.grabbing() == False;
                position = arm.position(stack);
                arm.grabbing() == True;
                osition = arm.position(sen2nd_pos);
                arm.grabbing() == False;
                position = arm.position(stack);
            }
            if sensor.stuff_detected() = "hole" {
                motors.stop_running();
                position = arm.position(stack);
                arm.grabbing() == True;
                position = arm.position(sen1st_pos);
                arm.grabbing() == False;
                position = arm.position(stack);
            }
        }
    }
}
if keypad.input() == "2" {
    sensor.initiate();
    orientation = sensor.scan_surroundings();
    if orientiation == False {
        motor.adjust();
    }
    else {
        lcd.print_on_screen("Calibrated");
    }
}

if keypad.input() == "3" {
    motors.apply_voltage() == False;
    sensor.apply_voltage() == False;
    arm.apply_voltage() == False;
    delay(5 sec);
    motors.apply_voltage() == True;
    sensor.apply_voltage() == True;
    arm.apply_voltage() == True;
}

if keypad.input() == "A" {
    a = motors.comms_check()
    b = sensor.comms_check()
    c = arm.comms_check()
    d = motors.circ_check()
    e = sensor.circ_check()
    f = arm.circ_check()
    if (a or b or c == False){
        report_comms_issue();
        break;
    }
    if (d or e or f == False){
        report_circ_issue();
        break;
    }
    finished();
}
