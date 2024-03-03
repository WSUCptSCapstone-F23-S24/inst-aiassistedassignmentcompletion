import json


def getAttributes(attributes):
    attr = []
    for (attribute, value) in list(attributes.items()):
        if isinstance(value, dict):
            attr += getAttributes(value)
        else:
            attr.append((attribute, value))
    return attr


def parseBusiness():
    print("Business:")
    with open('.//yelp_business.JSON', 'r') as f:
        line = f.readline()
        count = 0
        while line:
            data = json.loads(line)
            business = data['business_id']
            business_str = "'" + data['name'] + "'," + \
                "'" + data['address'] + "'," + \
                "'" + data['city'] + "'," +  \
                "'" + data['state'] + "'," + \
                "'" + data['postal_code'] + "'," +  \
                str(data['latitude']) + "," +  \
                str(data['longitude']) + "," + \
                str(data['stars']) + "," + \
                str(data['review_count']) + "," + \
                str(data['is_open'])
            print(business_str)

            for category in data['categories']:
                category_str = "'" + business + "','" + category + "'"
                print(category_str)

            for (day, hours) in data['hours'].items():
                hours_str = "'" + business + "','" + \
                    str(day) + "','" + \
                    hours.split('-')[0] + "','" + hours.split('-')[1] + "'"
                print(hours_str)

            for (attr, value) in getAttributes(data['attributes']):
                attr_str = "'" + business + "','" + \
                    str(attr) + "','" + str(value) + "'"
                print(attr_str)

            line = f.readline()
            count += 1


def parseReview():
    print("Reviews:")
    with open('.//yelp_review.JSON', 'r') as f:
        line = f.readline()
        count = 0
        while line:
            data = json.loads(line)
            review_str = "'" + data['review_id'] + "'," +  \
                         "'" + data['user_id'] + "'," + \
                         "'" + data['business_id'] + "'," + \
                         str(data['stars']) + "," + \
                         "'" + data['date'] + "'," + \
                         "'" + data['text'] + "'," +  \
                         str(data['useful']) + "," +  \
                         str(data['funny']) + "," + \
                         str(data['cool'])
            print(review_str)
            line = f.readline()
            count += 1


def parseUser():
    print("Users:")
    with open('.//yelp_user.JSON', 'r') as f:
        line = f.readline()
        while line:
            data = json.loads(line)
            user_str = "'" + data['user_id'] + "'," + \
                       "'" + data['name'] + "'," + \
                       str(data['review_count']) + "," + \
                       str(data['yelping_since']) + "," + \
                       str(data['useful']) + "," + \
                       str(data['funny']) + "," + \
                       str(data['cool']) + "," + \
                       str(data['elite']) + "," + \
                       str(data['friends']) + "," + \
                       str(data['fans']) + "," + \
                       str(data['average_stars']) + "," + \
                       str(data['compliment_hot']) + "," + \
                       str(data['compliment_more']) + "," + \
                       str(data['compliment_profile']) + "," + \
                       str(data['compliment_cute']) + "," + \
                       str(data['compliment_list']) + "," + \
                       str(data['compliment_note']) + "," + \
                       str(data['compliment_plain']) + "," + \
                       str(data['compliment_cool']) + "," + \
                       str(data['compliment_funny']) + "," + \
                       str(data['compliment_writer']) + "," + \
                       str(data['compliment_photos'])
            print(user_str)
            line = f.readline()


def parseCheckin():
    print("Checkin Data:")
    with open('.//yelp_checkin.JSON', 'r') as f:
        line = f.readline()
        while line:
            data = json.loads(line)
            business_id = data['business_id']
            for day, hours in data['time'].items():
                for hour, count in hours.items():
                    checkin_str = "'" + business_id + "'," + \
                                  "'" + day + "','" + hour + "'," + \
                                  str(count)
                    print(checkin_str)
            line = f.readline()


parseBusiness()
parseReview()
parseUser()
parseCheckin()
