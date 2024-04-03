CREATE TABLE Business (
    business_id VARCHAR(25),
    business_name VARCHAR(255),
    address VARCHAR(255),
    city VARCHAR(255),
    state VARCHAR(10),
    zipcode VARCHAR(20),
    stars FLOAT,
    review_count INTEGER,
    checkin_count INTEGER DEFAULT 0,
    PRIMARY KEY(business_id)
);

CREATE TABLE Users (
    user_id VARCHAR(25),
    username VARCHAR(255),
    review_count INTEGER,
    average_stars FLOAT,
    PRIMARY KEY(user_id)
);

CREATE TABLE Reviews (
    review_id VARCHAR(255),
    user_id VARCHAR(25),
    business_id VARCHAR(25),
    stars FLOAT,
    PRIMARY KEY(review_id),
    FOREIGN KEY (user_id) REFERENCES Users(user_id),
    FOREIGN KEY (business_id) REFERENCES Business(business_id)
);

CREATE TABLE Categories (
    business_id VARCHAR(255),
    category_name VARCHAR(255),
    PRIMARY KEY (business_id, category_name),
    FOREIGN KEY (business_id) REFERENCES Business(business_id)
);

CREATE TABLE Business_Attribute (
    business_id VARCHAR(25),
    attr_key VARCHAR(255),
    attr_value VARCHAR(255),
    PRIMARY KEY (business_id, attr_key),
    FOREIGN KEY (business_id) REFERENCES Business(business_id)
);

CREATE TABLE Checkins (
    business_id VARCHAR(25),
    checkin_count INTEGER DEFAULT 0,
    PRIMARY KEY (business_id),
    FOREIGN KEY (business_id) REFERENCES Business(business_id)
);

CREATE TABLE ZipcodeData (
    zipcode INTEGER,
    medianIncome INTEGER,
    meanIncome INTEGER,
    population INTEGER,
    PRIMARY KEY (zipcode, medianIncome, meanIncome, population)
);
