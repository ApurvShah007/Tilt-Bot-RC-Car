# Tilt-Bot-RC-Car
Part of the GitHub Artic Code Vault

An RC toy car that can be maneuvered using the motion of a wireless remote board.

Technical Contributions:
1) Motion of remote board (ESP32 microcontroller) detected by a MPU6050 6-axis IMU mounted on the ESP32 board
2) Two DC motors powered by a L298N Motor driver
3) IMU data relayed from Remote board (ESP32) to another ESP32 board mounted on the car via a peer-to-peer master slave          connection established using ESP-NOW through WiFi.
4) The remote is established as the master(sender) while the RC car is established as a slave (reciever). The code features f     unctions from esp_now.h library that allows the boards to connect to form a peer-to-peer connection over the wifi and send     and recieve data. 
