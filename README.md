# Raspberry Pi Server for ESP8266 Communication

## Overview

This project utilizes a Raspberry Pi 3 to act as a server for communicating with an ESP8266 device. The server, implemented in Python using Flask, manages the interaction between the Raspberry Pi and the ESP8266. Additionally, the server serves a real-time webpage to display data received from the ESP8266.

**-- 3D Pi Server Case in OhShape --**

If you're looking to add a unique case for your Raspberry Pi server, check out the 3D Pi Server Case designed in OhShape. This case is specially crafted to house your Raspberry Pi 3 server in a stylish and functional manner.

### Features:

- **Design:** A sleek and modern design that complements the Raspberry Pi 3.

- **Ventilation:** Adequate ventilation holes for efficient cooling of the Raspberry Pi.

- **Accessibility:** Easy access to ports and GPIO pins.

### How to Get the 3D Case:

1. **Download STL Files:**
   - Visit the OhShape community or contact the designer to download the STL files for the 3D case.

2. **3D Print the Case:**
   - Use a 3D printer to print the case using the downloaded STL files.

3. **Assemble the Case:**
   - Follow the provided instructions to assemble the 3D Pi Server Case.

4. **Place the Raspberry Pi:**
   - Carefully place your Raspberry Pi 3 inside the assembled case.

5. **Enjoy the Unique Design:**
   - Once assembled, you'll have a unique and visually appealing case for your Raspberry Pi server.


## Components

- **Backend (Python):**
  - Utilizes Flask to create a simple web server.
  - Responsible for handling responses from the ESP8266.
  - Cleans up and maintains a limited number of recent data entries in a CSV file.

- **Frontend (JavaScript and HTML):**
  - A dynamic webpage hosted on the Raspberry Pi.
  - Fetches and displays real-time data from the ESP8266.
  - Utilizes CSS for styling and includes animations for visual appeal.

- **ESP8266 Code (`device.ino`):**
  - The firmware code for the ESP8266 acting as a client.
  - Sends humidity and temperature data to the Raspberry Pi server.

## File Structure

- **`server.py`**: Python script containing the Flask backend logic.
- **`templates/index.html`**: HTML file for the frontend, defining the webpage structure and styling.
- **`static/data.csv`**: CSV file storing data received from the ESP8266.
- **`device.ino`**: Code for the ESP8266, acting as a client and sending humidity and temperature data to the server.

## Usage

1. **Install Flask:**
   ```bash
   pip install flask
2. **Run the Server:**
   ```bash
   python3 server.py
3. **Expose the Server using ngrok:**
   ```bash
   ./ngrok http 8080
  - If the above command doesn't work, refer to this video(https://www.youtube.com/watch?v=RIEArLa7kEQ) for troubleshooting.
  - Copy the ngrok URL (e.g., https://ngrok.8462-4739-748J.app) generated after running the command.

4. **Configure ESP8266 Code (device.ino):**
- Open the device.ino file in the Arduino IDE or your preferred code editor.
- Locate line number 10, which may contain the server URL. Replace it with the ngrok URL copied in the previous step.

5. **Connect DHT11 Sensor:**
- Attach the DHT11 sensor to the designated pin on the ESP8266, as specified in the **`device.ino`** code.

6. ** Access the Webpage:**
- Open the ngrok URL (e.g., https://ngrok.8462-4739-748J.app) in any web browser to view the real-time data webpage.

   
