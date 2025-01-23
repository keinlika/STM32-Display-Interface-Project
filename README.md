# Project Title

## Description
This project focuses on gaining experience with peripherals, working with both graphical LCDs (GLCD) and character LCDs, and utilizing SPI and I2C communication protocols. The project also serves as preparation for a final, more comprehensive project.

---

## Part 1: Graphics LCD (GLCD) Using SPI Communication

### Objectives
- Learn how to interface with a graphics LCD (GLCD) using the SPI communication protocol.
- Display custom characters and graphics on the GLCD.

### Implementation
#### Hardware Connections
- **MOSI:** PA7
- **SCK:** PA5
- **Chip Enable (CE):** PB6
- **Data/Command (DC):** PA0
- **Reset:** PA1

#### Software Workflow
1. **Initialize SPI1**: Configure the SPI1 peripheral with the correct settings for the GLCD.
2. **GLCD Initialization**: Send initialization commands to set up the GLCD for operation.
3. **Data Transmission**: Write functions to send commands and data to the GLCD via SPI.
4. **Display Output**: Create and display custom characters, shapes, and patterns.

---

## Part 2: Character LCD Using I2C Communication

### Objectives
- Interface with a 16x2 character LCD via the PCF8574 I2C I/O expander.
- Display text characters on the LCD.

### Implementation
#### Hardware Connections
- **SDA:** PB9
- **SCL:** PB8

#### Software Workflow
1. **Initialize I2C1**: Set up the I2C1 peripheral for communication.
2. **Configure PCF8574**: Set up the PCF8574 I/O expander to control the character LCD.
3. **Send Commands and Data**: Write functions to send commands and characters to the LCD.
4. **Test Output**: Display a simple message on the LCD.

---

## Part 3: Additional Objectives and Specifications

### Objectives
- Gain more insight and practice using peripherals.
- Learn how to display characters on both a graphical LCD (GLCD) and a character LCD.
- Learn how to use the SPI and I2C communication protocols.
- Prepare for the final project.

### Schematic
**Figure 1**: A schematic showing the connections for the final circuit of the project.

### Specifications
#### Part A: SPI1 Interface
- **MOSI:** PA7 (GPIO Port A, Pin 7)
- **SCK:** PA5 (GPIO Port A, Pin 5)
- **Chip Enable (CE) or Slave Select:** PB6 (GPIO Port B, Pin 6)
- **Data/Command (DC) or Data/Instruction (D/I):** PA0 (GPIO Port A, Pin 0)
- **Reset:** PA1 (GPIO Port A, Pin 1)
<img width="363" alt="Screenshot 2025-01-23 at 2 01 34 AM" src="https://github.com/user-attachments/assets/a6827644-fc62-4fcd-bdb7-898d1a3651f6" />


#### Part B: PCF8574 I2C I/O Expander (connected to the 16x2 Character LCD)
- **I2C1 Interface:**
  - **SDA:** PB9 (GPIO Port B, Pin 9)
  - **SCL:** PB8 (GPIO Port B, Pin 8)
<img width="469" alt="Screenshot 2025-01-23 at 2 01 47 AM" src="https://github.com/user-attachments/assets/50bea307-777c-4eb6-9fcf-8c172bb5ef61" />


#### Part C: GPIO Configurations
- **GPIO Port A:**
  - **Pin 0 (PA0):** Used as an external interrupt input (rising edge trigger)
  - **Pin 5 (PA5):** Output pin for TIM2 (Timer 2)
- **GPIO Port B:**
  - **Pin 8 (PB8):** I2C1_SCL (I2C1 Clock)
  - **Pin 9 (PB9):** I2C1_SDA (I2C1 Data)
- **GPIO Port C:**
  - **Pin 13 (PC13):** Used as an external interrupt input (rising edge trigger)

<img width="631" alt="Screenshot 2025-01-23 at 2 02 02 AM" src="https://github.com/user-attachments/assets/25153f9c-2c00-43a0-9a54-7bde130b6d45" />

---

## Notes
This project documentation was adapted from a template originally created for ECEN 260 during the Spring 2023 semester. Usage of this documentation for other semesters is not permitted and may constitute academic dishonesty.

---

## Conclusion
This project provided hands-on experience with SPI and I2C communication protocols while exploring the use of both graphical and character LCDs. It also serves as a preparatory step for the final project.
