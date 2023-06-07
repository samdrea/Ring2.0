# Low-budget Ring Camera Alternative

Author: Samdrea Hsu 

**Project Overview:** 

The goal of this project is to recreate the Ring Video Doorbell with Arduino parts. The original  objective was to be able to start a live video stream when motion is detected. However, due to constraints, the final product showcases the ability to capture 3 pictures upon motion detection and display the photos onto a webpage upon user intervention. 

**The Process:**

The closest [tutorial](https://randomnerdtutorials.com/esp32-cam-take-photo-display-web-server/) I could find online uses a ESP32-CAM, which is a microcontroller with a camera and WiFi connections, to host a webpage that allows users to take pictures and display the pictures on it. I modified the source code and the hardware set-up so that the camera would take pictures when a motion sensor detects motion. When the user is notified of motion by an LED that lights up, the user can display the picture on the web page with the click of a button.

**The Design:**

*Sensor choice:*
Between a passive infrared(PIR) and ultrasonic(US) sensor, which are the most common technology in motion detection, I chose a passive infrared sensor for two reasons. One, because I only needed to detect motion in line-of-sight. Second, the PIR sensor trumps the US sensor with its quiescent current of 50 μA as opposed to 2mA. 




*Sensor Calibration and Algorithm:*
To prevent false positives, I adjusted the sensitivity and time-delay of the PIR sensor before integration with the ESP32-CAM. I used an Elegoo microcontroller to turn the LED on if the PIR sensor outputs HIGH to indicate motion. With a phone timer, I calibrated the sensor so that insignificant motion, such as a quick wave in front of the sensor to mimic a fallen leaf or any sudden disturbances, turned the LED on for less than 3 seconds. Whereas true motion, such as when I walked across the room, turned the LED on for at least 8 seconds. 


*Handling Unsigned Long Overflow(Code):*
The problem with using Arduino’s built-in timer that can keep track of how many seconds have elapsed is that when the time exceeds 4,294,967,295 milliseconds, the timer resets to 0. If motion was detected right before the reset, it could complicate calculations to find the motion duration, which is found by subtracting current time with last recorded time. Therefore, I implemented an algorithm to check whether the timer has overflowed and adjusted the calculations accordingly. “millis()” is the timer that keeps track of current time. “MIN_MOTION” is a constant to set a minimum time(in milliseconds) that would confirm that motion is continuous, which I set to 3000. The “10” is a generous offset to account for any delays in calculations since the motion started. 




*Web Page Modification:*

The original tutorial had three buttons on the page. “Capture a photo” saves a photo onto the SPIFFS, which is the filesystem of the ESP32-CAM. Users needed to press “refresh page” to load the picture. “Rotate” turns the photo 90 degrees counterclockwise immediately.  

The final web page with the hardware integration has only one button, because image capturing is automatic as the PIR sensor detects motion for more than 3 seconds. When the camera captures three images, saves it onto SPIFFS, and turns on the LED for 10 seconds, the user will know to refresh the page to see the captured images. Any random motion, like a quick wave in front of the PIR sensor doesn’t trigger the camera to take pictures.  






**Conclusion:**

The final project showcases the key features of the Ring Doorbell Camera. It is able to detect true motion without throwing any false positives. The web page mimics the Ring application in that the user could see the media captured via WiFi-connection. 

While the project has been successful, there is room for improvement. For example, the next steps would be to include video streaming abilities and implementing a button and buzzer to simulate the doorbell. Furthermore, two ESP-32 modules can be incorporated to support the wireless communication between the motion sensor and ESP-32 CAM so the two can be installed in different places for better camera angles. 
