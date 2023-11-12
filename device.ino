#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define DHTPIN D7  // Define the pin where your DHT11 sensor is connected
#define LEDPIN 2   // Define the GPIO pin for the built-in LED
#define DHTTYPE DHT11  // Set the DHT sensor type

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Local";       // Replace with your network credentials
const char* password = "va1234av";

const char* host = "b04e-2402-8100-2664-5dfa-4a64-c809-e7cc-3d93.ngrok-free.app";  // Replace with the your ngrok Url without https://

void setup() {
    Serial.begin(115200);
    pinMode(LEDPIN, OUTPUT);  // Set the LED pin as an output

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Connecting to WiFi...");
        delay(500);
    }
    Serial.println("Connected to WiFi");

    dht.begin();
}

void loop() {
    // Read temperature and humidity from DHT11 sensor
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Check if temperature and humidity are valid values
    if (!isnan(temperature)) {
        Serial.print("Temperature: ");
        Serial.println(temperature);
        Serial.print("Humidity: ");
        Serial.println(humidity);

        // Blink the LED
        digitalWrite(LEDPIN, HIGH);  // Turn the LED on
        delay(300);  // Wait for 500 milliseconds
        digitalWrite(LEDPIN, LOW);   // Turn the LED off

        // Create a TCP connection to the Raspberry Pi server
        WiFiClient client;
        if (client.connect(host, 80)) {
            String tempUrl = "/write?temperature=" + String(temperature);


            // Send HTTP GET requests for temperature and humidity
            Serial.println("Sending temperature HTTP request...");
            client.println("GET " + tempUrl + " HTTP/1.1");
            client.println("Host: " + String(host));
            client.println("Connection: close");
            client.println();

            delay(400);

            // Read and print the server's response
            while (client.available()) {
                String line = client.readStringUntil('\r');
                Serial.print(line);
            }
            Serial.println("HTTP requests complete.");
        } else {
            Serial.println("Connection to server failed");
        }
        client.stop();
    }


    if (!isnan(humidity)) {
        Serial.print("Humidity: ");
        Serial.println(humidity);

        // Blink the LED
        digitalWrite(LEDPIN, HIGH);  // Turn the LED on
        delay(300);  // Wait for 500 milliseconds
        digitalWrite(LEDPIN, LOW);   // Turn the LED off

        // Create a TCP connection to the Raspberry Pi server
        WiFiClient client;
        if (client.connect(host, 80)) {
            String humidityUrl = "/write?humidity=" + String(humidity);

        

            Serial.println("Sending humidity HTTP request...");
            client.println("GET " + humidityUrl + " HTTP/1.1");
            client.println("Host: " + String(host));
            client.println("Connection: close");
            client.println();

            // Wait for the server to respond
            delay(400);

            // Read and print the server's response
            while (client.available()) {
                String line = client.readStringUntil('\r');
                Serial.print(line);
            }
            Serial.println("HTTP requests complete.");
        } else {
            Serial.println("Connection to server failed");
        }
        client.stop();
    }

    delay(500);  // Wait for a minute before taking another reading
}
