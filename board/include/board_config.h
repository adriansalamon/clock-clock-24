#ifndef CONFIG_H
#define CONFIG_H

// CHANGE THIS FOR EACH BOARD
#define I2C_ADDRESS 0x06
#define INVERTED false


#define MAG_THRESHOLD 10

typedef struct mag_pin {
    uint8_t pin;
    bool analog;
} t_mag_pin;

#define N_STEPS 4320 // 360 degrees * 12 microsteps

#define A1_STEP 2
#define A1_DIR 0
#define A1_MAG mag_pin{12, false}

#define B1_STEP 3
#define B1_DIR 1
#define B1_MAG mag_pin{11, false}

#define A2_STEP 4
#define A2_DIR 2
#define A2_MAG mag_pin{15, false}

#define B2_STEP 5
#define B2_DIR 3
#define B2_MAG mag_pin{14, false}


#define A3_STEP 6
#define A3_DIR 4
#define A3_MAG mag_pin{17, false}


#define B3_STEP 7
#define B3_DIR 5
#define B3_MAG mag_pin{16, false}


#define A4_STEP 8
#define A4_DIR 6
#define A4_MAG mag_pin{A7, true}


#define B4_STEP 9
#define B4_DIR 7
#define B4_MAG mag_pin{A6, true}


#define RESET 13

#endif // CONFIG_H