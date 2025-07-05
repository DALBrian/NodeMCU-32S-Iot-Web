from flask import Flask, request, jsonify, render_template
import sqlite3
from datetime import datetime

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
    return render_template('index.html')

if __name__ == '__main__':
    app.run(host='192.168.137.1', port=5000)