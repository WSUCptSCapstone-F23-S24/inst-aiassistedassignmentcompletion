# CS 423 Case Study 2: Yelp Application
import json
import time
import psycopg2


# Cleans item
def cleanStr4SQL(s):
    return s.replace("'", "`").replace("\n", " ")


def insert2UserTable():
    # Use utf-8 encoding to avoid UniDecodeError
    with open('Dataset/yelp_user.JSON', 'r', encoding='utf-8') as f:

        line = f.readline()

        # Connects to database (Needs changing based on the dbname, your user login to the db, the host name and your password to the db
        try:
            conn = psycopg2.connect("dbname='YelpDB' user='postgres' host='localhost' password='423yelp'")
        except:
            print('Unable to connect to the database!')

        # Used to execute queries
        cur = conn.cursor()

        while line:
            try:
                data = json.loads(line)
            except json.JSONDecodeError as e:
                print("JSON decoding error:", e)
                line = f.readline()
                continue

            try:
                # Pass SQL query string
                cur.execute(
                    "INSERT INTO users (user_id, username, review_count, average_stars)"
                    " VALUES (%s, %s, %s, %s)",
                    (data["user_id"], cleanStr4SQL(data["name"]), data["review_count"], data["average_stars"]))

            except Exception as e:
                print("Insert to user failed!", e)
            conn.commit()

            line = f.readline()

        cur.close()
        conn.close()

    f.close()
    print("User finished")


def insert2ReviewTable():
    # Use utf-8 encoding to avoid UniDecodeError
    with open('Dataset/yelp_review.JSON', 'r', encoding='utf-8') as f:

        line = f.readline()

        # Connects to database (Needs changing based on the dbname, your user login to the db, the host name and your password to the db
        try:
            conn = psycopg2.connect("dbname='YelpDB' user='postgres' host='localhost' password='423yelp'")

        except:
            print('Unable to connect to the database!')

        cur = conn.cursor()

        while line:
            data = json.loads(line)

            # Try to insert the review data we received from parsing
            # We only need review_id, user_id, business_id, and stars in our project, so we ignore all other data
            try:
                # Check if the user_id exists in the users table and
                cur.execute("SELECT user_id FROM users WHERE user_id = %s", (data["user_id"],))

                # Gets the next row
                user_exists = cur.fetchone()

                if user_exists:
                    # Insert into Reviews if user_id exists
                    cur.execute(
                        "INSERT INTO Reviews (review_id, user_id, business_id, stars)"
                        " VALUES (%s, %s, %s, %s)",
                        (data["review_id"], data["user_id"], data["business_id"], data["stars"]))

            except Exception as e:
                print("Insert to reviews failed!", e)
            conn.commit()

            line = f.readline()

        cur.close()
        conn.close()

    f.close()
    print("Review finished")


def insert2BusinessTable():
    # Use utf-8 encoding to avoid UniDecodeError
    with open('Dataset/yelp_business.JSON', 'r', encoding='utf-8') as f:

        line = f.readline()

        # Connects to database (Needs changing based on the dbname, your user login to the db, the host name and your password to the db
        try:
            conn = psycopg2.connect("dbname='YelpDB' user='postgres' host='localhost' password='423yelp'")

        except:
            print('Unable to connect to the database!')

        cur = conn.cursor()

        while line:
            data = json.loads(line)

            try:
                cur.execute(
                    "INSERT INTO business (business_id, business_name, address, city, state, zipcode, stars, review_count) VALUES (%s, %s, %s, %s, %s, %s, %s, %s)",
                    (data['business_id'], cleanStr4SQL(data["name"]), cleanStr4SQL(data["address"]), data["city"], data["state"], data["postal_code"],
                     data["stars"], data["review_count"]
                     ))

                category_data = data["categories"]

                for category in category_data:
                    # Try to attach the category to the business. Skips the category that business already has it attached
                    try:
                        cur.execute("INSERT INTO categories (business_id, category_name) VALUES (%s, %s) ON CONFLICT DO NOTHING",
                                    (data['business_id'], category.strip()))
                    except Exception as e:
                        print("Insert to categories failed!", e)

            except Exception as e:
                print("Insert to business failed!", e)
            conn.commit()

            line = f.readline()

        cur.close()
        conn.close()

    f.close()
    print("Business finished")


def insert2Checkin():
    # Does not run into a UniDecodeError (Most likely not needed for this function)
    with open('Dataset/yelp_checkin.JSON', 'r') as f:

        # Connects to database (Needs changing based on the dbname, your user login to the db, the host name and your password to the db
        try:
            conn = psycopg2.connect("dbname='YelpDB' user='postgres' host='localhost' password='423yelp'")

        except Exception as e:
            print('Unable to connect to the database!', e)

        cur = conn.cursor()

        # Hold number of checkins for some business
        checkin_counts = {}

        for line in f:
            data = json.loads(line)

            business_id = data['business_id']
            checkin_dates = data["time"]
            checkin_counts[business_id] = checkin_counts.get(business_id, 0) + len(checkin_dates)

        # Insert business_id and checkin_count which is used for business once in database
        for business_id, count in checkin_counts.items():
            try:
                # If there is a conflict of business_ids, business row is updated with the new number of checkins
                cur.execute("INSERT INTO Checkins (business_id, checkin_count) VALUES (%s, %s) ON CONFLICT (business_id) DO UPDATE SET checkin_count = Checkins.checkin_count + EXCLUDED.checkin_count", (business_id, count))
            except Exception as e:
                print(f"Failed to checkin!", e)

        conn.commit()
        cur.close()
        conn.close()
        print("Checkins finished")
    f.close()


# Keeping track of how long the program takes to run
start = time.time()

# Insert all the data
insert2UserTable()
insert2BusinessTable()
insert2ReviewTable()
insert2Checkin()

# How much time (seconds) were taken when running
end = time.time() - start
print("Time taken", end)
