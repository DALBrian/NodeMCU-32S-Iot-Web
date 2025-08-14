import sqlite3
from pprint import pprint

conn = sqlite3.connect("file:data.db?mode=ro", uri=True)
cur = conn.cursor()

print("\n== readings (latest 10) ==")
cur.execute("""
SELECT timestamp, raw_temp, raw_hum, corrected_temp, corrected_hum
FROM readings
ORDER BY timestamp DESC
LIMIT 10
""")
pprint(cur.fetchall())

print("\n== last calibration ==")
cur.execute("""
SELECT id, timestamp, temp_offset, humidity_offset
FROM calibration
ORDER BY timestamp DESC
LIMIT 1
""")
pprint(cur.fetchone())

conn.close()
