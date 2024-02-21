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


def parseCheckin():
    print("Checkin Data:")


parseBusiness()
parseReview()
