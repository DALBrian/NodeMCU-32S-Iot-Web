from flask import Flask, request, jsonify, render_template
import sqlite3
from datetime import datetime
import socket

app = Flask(__name__)

def insert_data(temp, hum):
    with sqlite3.connect("data.db") as conn:
        cur = conn.cursor()
        cur.execute("""CREATE TABLE IF NOT EXISTS readings (
            timestamp TEXT, temperature REAL, humidity REAL)""")
        cur.execute("INSERT INTO readings VALUES (?, ?, ?)", (datetime.now().isoformat(), temp, hum))
        conn.commit()

@app.route('/upload', methods=['POST'])
def upload():
    data = request.get_json()
    insert_data(data['temperature'], data['humidity'])
    return jsonify({"status": "ok"})

@app.route('/data')
def get_data():
    with sqlite3.connect("data.db") as conn:
        cur = conn.cursor()
        cur.execute("SELECT timestamp, temperature, humidity FROM readings ORDER BY timestamp DESC LIMIT 50")
        rows = cur.fetchall()
    return jsonify(rows)

@app.route('/')
def index():
    return render_template('index.html') # Display sensor data

@app.route('/calibrate')
def calibrate():
    return render_template('calibrate.html') # Sensor re-calibration

def run_flask(Ip, Port):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.bind((Ip, Port))
        print(f"[INFO] Flask Server running on: {Ip}:{Port}")
        app.run(host=Ip, port=Port)
        return True
    except OSError as e:
        print(f"[ERROR] {Ip}:{Port} is not available to bind {e}")
        return False

if __name__ == '__main__':
    Port = 5000
    IpAddress = ["192.168.137.1", "127.0.0.1", "192.168.1.1"]
    for Ip in IpAddress:
        if run_flask(Ip, Port):
            break
        else:
            print(f"[Error] All IP addresses are not available to start Flask server.")

