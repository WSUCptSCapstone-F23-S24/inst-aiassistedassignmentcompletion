import sqlite3
import json

def count_checkins(data):
    checkin_counts = {}
    for entry in data:
        business_id = data['business_id']
        checkins = data['date'].split(',')
        checkin_counts[business_id] = len(checkins)
    return checkin_counts

def update_checkin_count(checkin_counts):
    cursor = conn.cursor()

    for business_id, count in checkin_counts.items():
        cursor.execute("UPDATE business SET checkin_count = ? WHERE business_id = ?;", (count, business_id))

    conn.commit()
    
# Connect to the SQLite database (creates a new one if not exists)
conn = sqlite3.connect('BusinessData.db')

# Create a cursor object to execute SQL commands
cursor = conn.cursor()

# Define the SQL statement to create the 'Business' table
with open('data/yelp_business.json', 'r') as file:
    # Read the first line to get the columns dynamically
    first_entry = json.loads(file.readline())
    columns = ', '.join([f"{key} TEXT" for key in first_entry.keys()])

    # Create the Business table if not exists
    cursor.execute(f'''
        CREATE TABLE IF NOT EXISTS Business (
            {columns}
        )
    ''')

    # Insert data into the Business table
    for line in file:
        entry = json.loads(line)
        placeholders = ', '.join(['?'] * len(entry)) + ', ?'
        values = [json.dumps(value) if isinstance(value, (dict, list)) else value for value in entry.values()]
        values.append('checkin_count')

        # Use INSERT OR IGNORE to handle duplicate business_id
        cursor.execute(f'''
            INSERT OR IGNORE INTO Business VALUES ({placeholders})
        ''', values)
        
with open('data/yelp_checkin.json', 'r') as file:
    # Read the first line to get the columns dynamically
    first_entry = json.loads(file.readline())
    columns = ', '.join([f"{key} TEXT" for key in first_entry.keys()])

    # Create the CheckIn table if not exists
    cursor.execute(f'''
        CREATE TABLE IF NOT EXISTS CheckIn (
            {columns}
        )
    ''')

    # Insert data into the CheckIn table
    for line in file:
        entry = json.loads(line)
        placeholders = ', '.join(['?'] * len(entry))
        values = [json.dumps(value) if isinstance(value, (dict, list)) else value for value in entry.values()]
        
        # Use INSERT OR IGNORE to handle duplicate business_id
        cursor.execute(f'''
            INSERT OR IGNORE INTO CheckIn VALUES ({placeholders})
        ''', values)
        
with open('data/yelp_tip.json', 'r') as file:
    # Read the first line to get the columns dynamically
    first_entry = json.loads(file.readline())
    columns = ', '.join([f"{key} TEXT" for key in first_entry.keys()])

    # Create the CheckIn table if not exists
    cursor.execute(f'''
        CREATE TABLE IF NOT EXISTS Tip (
            {columns}
        )
    ''')

    # Insert data into the CheckIn table
    for line in file:
        entry = json.loads(line)
        placeholders = ', '.join(['?'] * len(entry))
        values = [json.dumps(value) if isinstance(value, (dict, list)) else value for value in entry.values()]
        
        # Use INSERT OR IGNORE to handle duplicate business_id
        cursor.execute(f'''
            INSERT OR IGNORE INTO Tip VALUES ({placeholders})
        ''', values)
        
with open('data/yelp_user.json', 'r') as file:
    # Read the first line to get the columns dynamically
    first_entry = json.loads(file.readline())
    columns = ', '.join([f"{key} TEXT" for key in first_entry.keys()])

    # Create the User table if not exists
    cursor.execute(f'''
        CREATE TABLE IF NOT EXISTS User (
            {columns}
        )
    ''')
    for line in file:
        entry = json.loads(line)
        placeholders = ', '.join(['?'] * len(entry))
        values = [json.dumps(value) if isinstance(value, (dict, list)) else value for value in entry.values()]
        # Use INSERT OR IGNORE to handle duplicate business_id
        cursor.execute(f'''
            INSERT OR IGNORE INTO User VALUES ({placeholders})
        ''', values)
cursor.execute('SELECT * FROM User')
conn.commit()

# Commit the changes
conn.commit()
with open('data/yelp_checkin.JSON', 'r') as file:
    for line in file:
        data = json.loads(line)
        update_checkin_count(count_checkins(data))
cursor.execute('DROP TABLE IF EXISTS ZipCodeData;')

# Commit changes
conn.commit()
with open("data/zipData.sql") as file:
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS zipcodeData (
        zipcode TEXT PRIMARY KEY,
        medianIncome INTEGER,
        meanIncome INTEGER,
        population INTEGER
    );
    ''')
    conn.commit()
    
    for line in file:
        # Strip newline character and split values by comma
        line = line[:-2]
        line = line.replace('(','').replace(')','').replace('\'', '')
        print(line)
        values = line.split(',')
        # Construct the SQL query with placeholders
        sql_query = "INSERT INTO zipcodeData (zipcode, medianIncome, meanIncome, population) VALUES (?, ?, ?, ?);"
        # Execute the SQL query with the values from the file
        cursor.execute(sql_query, values)
conn.commit()
cursor.execute('SELECT * FROM zipcodeData')
conn.commit()
data = cursor.fetchall()

for row in data:
    print(row)
# Execute the SQL query
try:
    cursor.execute(sql_query)
except:
    print("")

# Commit changes and close connection
conn.commit()

cursor.execute('SELECT checkin_count FROM Business')
data = cursor.fetchall()
conn.close()
