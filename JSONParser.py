import json

def clean_str_for_sql(s):
    return s.replace("'", "''").replace("\n", " ")

def get_attributes(attributes):
    attribute_list = []
    for attribute, value in attributes.items():
        if isinstance(value, dict):
            attribute_list += get_attributes(value)
        else:
            attribute_list.append((attribute, value))
    return attribute_list

def parse_business_data():
    print("Parsing businesses...")
    
    with open('data/yelp_business.JSON', 'r') as file:
        with open('.//yelp_business.txt', 'w') as outfile:
            line = file.readline()
            count_lines = 0

            while line:
                data = json.loads(line)
                business_id = data['business_id']
                business_str = (
                    f"'{data['name']}',"
                    f"'{clean_str_for_sql(data['address'])}',"
                    f"'{clean_str_for_sql(data['city'])}',"
                    f"'{data['state']}',"
                    f"'{data['postal_code']}',"
                    f"{data['latitude']},{data['longitude']},"
                    f"{data['stars']},{data['review_count']},{data['is_open']}"
                )
                outfile.write(business_str + '\n')

                for category in data['categories'].split(','):
                    category_str = f"'{business_id}','{category}'"
                    outfile.write(category_str + '\n')

                for day, hours in data['hours'].items():
                    hours_str = (
                        f"'{business_id}','{day}','{hours.split('-')[0]}','{hours.split('-')[1]}'"
                    )
                    outfile.write(hours_str + '\n')

                for attr, value in get_attributes(data['attributes']):
                    attr_str = f"'{business_id}','{attr}','{value}'"
                    outfile.write(attr_str + '\n')

                line = file.readline()
                count_lines += 1

    print(count_lines)

def parse_tip_data():
    print("Parsing tips...")

    with open('data/yelp_tip.JSON', 'r') as file:
        with open('.//yelp_tip.txt', 'w') as outfile:
            line = file.readline()
            count_lines = 0

            while line:
                data = json.loads(line)
                review_str = (
                    f"'{data['business_id']}',"
                    f"'{data['date']}',"
                    f"{data['likes']},"
                    f"'{clean_str_for_sql(data['text'])}',"
                    f"'{data['user_id']}'"
                )
                outfile.write(review_str + '\n')

                line = file.readline()
                count_lines += 1

    print(count_lines)

def parse_user_data():
    print("Parsing users...")

    with open('data/yelp_user.JSON', 'r') as file:
        with open('.//yelp_user.txt', 'w') as outfile:
            line = file.readline()
            count_lines = 0

            while line:
                data = json.loads(line)
                user_id = data.get('user_id', '')

                # Extract all key-value pairs from the JSON object
                user_data = [(key, data[key]) for key in data.keys()]

                # Convert key-value pairs to SQL-friendly string
                user_str = ",".join([f"'{key}':'{clean_str_for_sql(str(value))}'" for key, value in user_data])

                outfile.write(f"{user_str}\n")

                friends = data.get('friends', [])
                for friend in friends:
                    friend_str = f"'{user_id}','{friend}'\n"
                    outfile.write(friend_str)

                line = file.readline()
                count_lines += 1

    print(count_lines)

def parse_checkin_data():
    print("Parsing checkins...")

    with open('data/yelp_checkin.JSON', 'r') as file:
        with open('yelp_checkin.txt', 'w') as outfile:
            line = file.readline()
            count_lines = 0

            while line:
                data = json.loads(line)
                business_id = data['business_id']

                for date_str in data['date'].split(','):
                    checkin_str = f"'{business_id}','{date_str.strip()}'"
                    outfile.write(checkin_str + "\n")

                line = file.readline()
                count_lines += 1

    print(count_lines)

parse_business_data()
parse_user_data()
parse_checkin_data()
parse_tip_data()
