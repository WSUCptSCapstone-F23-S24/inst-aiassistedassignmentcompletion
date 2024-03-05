import json
import pandas as pd
import sys
from PyQt5.QtWidgets import QMainWindow, QApplication, QTableWidgetItem, QTableWidget, QVBoxLayout
from PyQt5 import uic
from PyQt5.QtGui import QIcon

qtCreatorFile = "423_application_frontend3.ui"  # Enter file here.
Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

class milestone2(QMainWindow):

    def __init__(self):
        super(milestone2, self).__init__()
        self.df = None
        self.uniqueCategories= None
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.load_data()
        self.ui.stateList.currentTextChanged.connect(self.show_cities_in_state)
        self.ui.cityList.currentTextChanged.connect(self.show_zipcodes_in_city)
        self.ui.zipList.currentTextChanged.connect(self.get_categories_in_zip)
        self.ui.zipList.currentTextChanged.connect(self.show_business_count_by_category)
        self.ui.zipList.currentTextChanged.connect(self.zip_code_stats)
        self.ui.categoriesList.currentTextChanged.connect(self.show_businesses_by_category)
        #self.ui.stateList.currentTextChanged.connect(self.stateChanged)

    def showAllStates(self):
        unique_states = self.df['state'].unique()
        for row in unique_states:
            self.ui.stateList.addItem(row)
            self.ui.stateList.setCurrentIndex(-1)
            self.ui.stateList.clearEditText()
        return unique_states
    
    def show_cities_in_state(self):
        self.ui.cityList.clear()
        state = self.ui.stateList.currentText()
        filtered_df = self.df[self.df['state'] == state]
        unique_zipcodes = filtered_df['city'].unique()
        for row in unique_zipcodes:
            self.ui.cityList.addItem(row)
        
        return unique_zipcodes

    def show_zipcodes_in_city(self):
        self.ui.zipList.clear()
        city = self.ui.cityList.currentItem().text()
        filtered_df = self.df[self.df['city'] == city]
        
        unique_zipcodes = filtered_df['postal_code'].unique()
        for row in unique_zipcodes:
            self.ui.zipList.addItem(row)
        
        return unique_zipcodes
    

    def zip_code_stats(self):
        self.ui.totalPop.clear()
        self.ui.meanIncome.clear()
        self.ui.numBusiness.clear()

        zip_code = self.ui.zipList.currentItem().text()
        zip_data = self.df[self.df['postal_code'] == zip_code]
        self.ui.numBusiness.setText(str(len(zip_data)))
        self.ui.meanIncome.setText("63173")
        self.ui.totalPop.setText("59545")
    
    def get_categories_in_zip(self):
        self.ui.categoriesList.clear()
        zip_code = self.ui.zipList.currentItem().text()
        zip_data = self.df[self.df['postal_code'] == zip_code]
        self.unique_categories = set()

        for categories_str in zip_data['categories']:
            categories_list = categories_str.split(', ')
            self.unique_categories.update(categories_list)
        for row in self.unique_categories:
            self.ui.categoriesList.addItem(row)

        return list(self.unique_categories)
    
    def show_business_count_by_category(self):
        self.ui.topCategories.clear()
        self.ui.topCategories.setRowCount(0)

        zip_code= self.ui.zipList.currentItem().text()

        # Get the categories and their counts for the selected zip code
        categories_counts = self.get_categories_count_in_zip(zip_code)

        # Set up the table headers
        self.ui.topCategories.setColumnCount(2)
        self.ui.topCategories.setHorizontalHeaderLabels(['Category', 'Number'])

        # Populate the table with category and count information
        rowCount = 0
        for category, count in categories_counts.items():
            self.ui.topCategories.insertRow(rowCount)
            self.ui.topCategories.setItem(rowCount, 0, QTableWidgetItem(category))
            self.ui.topCategories.setItem(rowCount, 1, QTableWidgetItem(str(count)))
            rowCount += 1
    
    def get_categories_count_in_zip(self, zip_code):
        zip_data = self.df[self.df['postal_code'] == zip_code]
        categories_counts = {}

        for categories_str in zip_data['categories']:
            categories_list = categories_str.split(', ')
            for category in categories_list:
                category = category.strip()  
                if category in categories_counts:
                    categories_counts[category] += 1
                else:
                    categories_counts[category] = 1

        return categories_counts

    
    def get_businesses_in_zip_by_category(self, zip_code, category):
        zip_data = self.df[(self.df['postal_code'] == zip_code) & (self.df['categories'].str.contains(category))]
        
        return zip_data

    
    def show_businesses_by_category(self):
        self.ui.businessList.clear()
        # Assuming you have a selected zip code and category in your UI
        zip_code = self.ui.zipList.currentItem().text()
        category = self.ui.categoriesList.currentItem().text()

        # Check if the selected category is in the list
        if category in self.unique_categories:
            # Call the existing function to get restaurants in the selected zip code and category
            restaurants_in_zip_by_category = self.get_businesses_in_zip_by_category(zip_code, category)

            # Clear existing items in the table
            self.ui.businessList.setRowCount(0)
            self.ui.businessList.setColumnCount(5)

            # Display the information in your UI table
            rowCount = 0
            self.initTable(rowCount)
            rowCount+=1
            for index, row in restaurants_in_zip_by_category.iterrows():
                self.ui.businessList.insertRow(rowCount)
                self.ui.businessList.setItem(rowCount, 0, QTableWidgetItem(str(row['name'])))
                self.ui.businessList.setItem(rowCount, 1, QTableWidgetItem(str(row['address'])))
                self.ui.businessList.setItem(rowCount, 2, QTableWidgetItem(str(row['city'])))
                self.ui.businessList.setItem(rowCount, 3, QTableWidgetItem(str(row['stars'])))
                self.ui.businessList.setItem(rowCount, 4, QTableWidgetItem(str(row['review_count'])))
                rowCount += 1
        else:
            print(f"No restaurants found in the selected category '{category}' for zip code '{zip_code}'.")

    def initTable(self,rowCount):
        self.ui.businessList.insertRow(rowCount)
        self.ui.businessList.setItem(rowCount, 0, QTableWidgetItem("Name"))
        self.ui.businessList.setItem(rowCount, 1, QTableWidgetItem("Address"))
        self.ui.businessList.setItem(rowCount, 2, QTableWidgetItem("City"))
        self.ui.businessList.setItem(rowCount, 3, QTableWidgetItem("Stars"))
        self.ui.businessList.setItem(rowCount, 4, QTableWidgetItem("Review Count"))

    def load_data(self):
        data = []
        with open('data/yelp_business.json', 'r') as file:
            for line in file:
                try:
                    json_obj = json.loads(line)
                    data.append(json_obj)
                except json.JSONDecodeError as e:
                    print(f"Error decoding JSON: {e}")

        # Parse JSON data into a pandas DataFrame
        self.df = pd.json_normalize(data)
        self.showAllStates()

    def stateChanged(self):
        # Example of querying data based on the selected state
        selected_state = self.ui.stateList.currentText()
        filtered_data = self.df[self.df['state'] == selected_state]

        # Display the results in your UI (replace 'column_name' with the actual column names you want to display)
        self.display_results(filtered_data[['business_id', 'name', 'address', 'city']])

    def display_results(self, results_df):
        self.ui.tableWidget.setRowCount(0)
        self.ui.tableWidget.setColumnCount(len(results_df.columns))

        for row_index, row_data in results_df.iterrows():
            self.ui.tableWidget.insertRow(row_index)
            for col_index, col_data in enumerate(row_data):
                self.ui.tableWidget.setItem(row_index, col_index, QTableWidgetItem(str(col_data)))

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = milestone2()
    window.show()
    sys.exit(app.exec_())