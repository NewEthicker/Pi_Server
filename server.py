from flask import Flask, request, jsonify, render_template
import csv 

app = Flask(__name__)

# Define the CSV file path
csv_file = 'static/data.csv'
rows_to_keep = 10  # Number of rows to keep in the CSV

def clean_csv():
    try:
        with open(csv_file, 'r') as file:
            lines = file.readlines()
            if len(lines) > rows_to_keep:
                with open(csv_file, 'w') as outfile:
                    outfile.writelines(lines[-rows_to_keep:])
    except Exception as e:
        print("Error cleaning the CSV file:", str(e))

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/write', methods=['GET'])
def write_data():
    try:
        temperature = request.args.get('temperature')
        humidity = request.args.get('humidity')

        if temperature:
            with open(csv_file, 'a', newline='') as csvfile:
                csvwriter = csv.writer(csvfile)
                csvwriter.writerow(["temperature", temperature])

        if humidity:
            with open(csv_file, 'a', newline='') as csvfile:
                csvwriter = csv.writer(csvfile)
                csvwriter.writerow(["humidity", humidity])

        clean_csv()  # Call the cleaner to remove old data

        return "Data written to CSV: temperature = {}, humidity = {}".format(temperature, humidity)
    except Exception as e:
        return "Error: {}".format(str(e))

@app.route('/read', methods=['GET'])
def read_data():
    try:
        with open(csv_file, 'r') as csvfile:
            csvreader = csv.reader(csvfile)
            data_list = list(csvreader)

            if data_list:
                temperature = None
                humidity = None

                for row in data_list:
                    if row[0] == "temperature":
                        temperature = row[1]
                    elif row[0] == "humidity":
                        humidity = row[1]

                response = ""
                if temperature:
                    response += "Temperature: {}°C\n".format(temperature)
                if humidity:
                    response += "Humidity: {}%\n".format(humidity)

                if response:
                    return response
                else:
                    return "No temperature or humidity data in the CSV file."
            else:
                return "No data in the CSV file."
    except Exception as e:
        return "Error: {}".format(str(e))

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=8080)
