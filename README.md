# Jetblack Power Meter Project

This project aims to create a power meter for the Jetblack cycling fluid trainer using an ESP32 microcontroller and a hall-effect speed sensor. The power meter will communicate via Bluetooth Low Energy (BLE) and will be calibrated using commercial power meter pedals.

## Project Structure

```
jetblack-powermeter
├── src
│   ├── main.cpp               # Entry point of the application
│   └── sensors
│       └── hall_effect_sensor.cpp  # Implementation of hall-effect sensor functionality
├── include
│   └── hall_effect_sensor.h    # Header file for hall-effect sensor interface
├── lib                         # Directory for additional libraries
├── platformio.ini             # PlatformIO configuration file
└── README.md                  # Project documentation
```

## Getting Started

### Prerequisites

- Install PlatformIO extension for your code editor.
- Ensure you have the necessary libraries for BLE and sensor integration.

### Setup Instructions

1. Clone the repository to your local machine.
2. Open the project folder in your code editor.
3. Install the required libraries specified in `platformio.ini`.
4. Connect the ESP32 board to your computer.

### Usage

- Upload the code from `src/main.cpp` to the ESP32 board.
- The power meter will initialize the hall-effect speed sensor and start broadcasting data over BLE.
- Use a BLE scanner to detect the power meter and monitor the output.

### Calibration

To calibrate the power meter:
1. Ride on the Jetblack trainer while monitoring the output from the Favero power meter pedals.
2. Record the speed data from the hall-effect sensor.
3. Analyze the data to establish a correlation between roller speed and power output.

## Contributing

Feel free to contribute to this project by submitting issues or pull requests. Your feedback and suggestions are welcome!

## License

This project is licensed under the MIT License. See the LICENSE file for more details.