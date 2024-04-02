import json
import sqlite3
import sys
from PyQt5.QtWidgets import QMainWindow, QApplication, QTableWidgetItem
from PyQt5 import uic

qtCreatorFile = "423_application_frontend3.ui"
Ui_MainWindow, _ = uic.loadUiType(qtCreatorFile)

class Milestone3(QMainWindow):
    def __init__(self):
        super(Milestone3, self).__init__()
        self.checkinavg = 0
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.setupUiConnections()
        self.loadStateList()

    def setupUiConnections(self):
        self.ui.stateList.currentTextChanged.connect(self.stateChanged)
        self.ui.cityList.currentTextChanged.connect(self.cityChanged)
        self.ui.zipList.currentTextChanged.connect(self.zipChanged)
        self.ui.searchButton.clicked.connect(self.categoryChanged)
        self.ui.refreshButton.clicked.connect(self.refreshChanged)
        self.ui.clearButton.clicked.connect(self.clearList)

    def executeQuery(self, sqlstr):
        try:
            conn = sqlite3.connect('BusinessData.db')
            cur = conn.cursor()
            cur.execute(sqlstr)
            result = cur.fetchall()
            conn.commit()
            conn.close()
            return result
        except Exception as e:
            print(f'Query execution failed: {e}')

    def loadItemsToList(self, list_widget, sqlstr):
        try:
            results = self.executeQuery(sqlstr)
            for row in results:
                list_widget.addItem(row[0])
        except Exception as e:
            print(f'Loading items to list failed: {e}')

    def loadStateList(self):
        sqlstr = "SELECT DISTINCT state FROM business ORDER BY state;"
        self.loadItemsToList(self.ui.stateList, sqlstr)

    def loadCityList(self, state):
        if state:
            sqlstr = f"SELECT DISTINCT city FROM business WHERE state = '{state}' ORDER BY city;"
            self.loadItemsToList(self.ui.cityList, sqlstr)

    def loadZipList(self, state, city):
        if state and city:
            sqlstr = f"SELECT DISTINCT postal_code FROM business WHERE city = '{city}' AND state = '{state}' ORDER BY postal_code;"
            self.loadItemsToList(self.ui.zipList, sqlstr)

    def stateChanged(self):
        self.ui.cityList.clear()
        self.ui.zipList.clear()
        state = self.ui.stateList.currentText()
        self.loadCityList(state)

    def cityChanged(self):
        self.ui.zipList.clear()
        state = self.ui.stateList.currentText()
        city = self.ui.cityList.currentItem()
        if state and city:
            sqlstr = f"SELECT DISTINCT postal_code FROM business WHERE city = '{city.text().strip()}' AND state = '{state}' ORDER BY postal_code;"
            self.loadItemsToList(self.ui.zipList, sqlstr)

    def zipChanged(self):
        self.ui.businessList.setRowCount(0)
        state = self.ui.stateList.currentText()
        city = self.ui.cityList.currentItem()
        zipcode = self.ui.zipList.currentItem()
        if state and city and zipcode:
            sqlstr = f"SELECT DISTINCT name, address, city, stars, review_count, checkin_count, postal_code, categories FROM business WHERE postal_code = '{zipcode.text().strip()}' AND state = '{state}' ORDER BY postal_code;"
            try:
                results = self.executeQuery(sqlstr)
                self.populateBusinessList(results)
                self.ui.numBusiness.setText(str(len(results)))
            except Exception as e:
                print(f'Error in zip changed: {e}')
            sqlstr = f"SELECT zipcode, population, meanIncome FROM zipcodeData WHERE zipcode = '{zipcode.text().strip()}';"
            try:
                results = self.executeQuery(sqlstr)
                self.ui.totalPop.setText(str(results[0][1]))
                self.ui.meanIncome.setText(str(results[0][2]))
            except Exception as e:
                print(f'Error in zip changed: {e}')

    def populateBusinessList(self, results):
        self.ui.businessList.clearContents()
        rowCount = 0
        categories = []
        category_count = {}

        self.ui.businessList.setColumnCount(len(results[0]) - 2)
        self.ui.businessList.setRowCount(len(results))
        self.ui.businessList.setHorizontalHeaderLabels(['name', 'address', 'city', 'stars', 'review_count', 'numcheckins'])

        for row in results:
            self.ui.businessList.setItem(rowCount, 0, QTableWidgetItem(row[0]))
            self.ui.businessList.setItem(rowCount, 1, QTableWidgetItem(row[1]))
            self.ui.businessList.setItem(rowCount, 2, QTableWidgetItem(row[2]))
            self.ui.businessList.setItem(rowCount, 3, QTableWidgetItem(str(row[3])))
            self.ui.businessList.setItem(rowCount, 4, QTableWidgetItem(str(row[4])))
            self.ui.businessList.setItem(rowCount, 5, QTableWidgetItem(str(row[5])))

            if isinstance(row[5], int):
                self.checkinavg += row[5]

            for ca in row[7].split(', '):
                if ca not in categories:
                    categories.append(ca)
                    category_count[ca] = 1
                else:
                    category_count[ca] += 1

            rowCount += 1

        self.checkinavg = round(self.checkinavg / (1.0 * rowCount), 2)
        self.loadCategoriesList(categories, category_count)

    def loadCategoriesList(self, categories, category_count):
        self.ui.categoriesList.clear()
        self.ui.topCategories.clear()
        rowCount = 0
        temp = dict(sorted(category_count.items(), key=lambda item: item[1], reverse=True))
        self.ui.topCategories.setColumnCount(2)
        self.ui.topCategories.setRowCount(len(categories))
        self.ui.topCategories.setHorizontalHeaderLabels(['# of businesses', 'name'])

        for x, y in temp.items():
            self.ui.topCategories.setItem(rowCount, 1, QTableWidgetItem(x))
            self.ui.topCategories.setItem(rowCount, 0, QTableWidgetItem(str(y)))
            rowCount += 1

        for row in categories:
            self.ui.categoriesList.addItem(row)
            rowCount += 1

    def categoryChanged(self):
        self.ui.businessList.setRowCount(0)
        state = self.ui.stateList.currentText()
        city = self.ui.cityList.currentItem()
        zipcode = self.ui.zipList.currentItem()
        category = self.ui.categoriesList.currentItem()
        if state and city and zipcode:
            sqlstr = f"SELECT DISTINCT name, address, city, stars, review_count, checkin_count, postal_code, categories FROM business WHERE postal_code = '{zipcode.text().strip()}' AND state = '{state}' AND categories LIKE '%{category.text()}%' ORDER BY postal_code;"
            try:
                results = self.executeQuery(sqlstr)
                self.populateBusinessList(results)
            except Exception as e:
                print(e)

    def refreshChanged(self):
        state = self.ui.stateList.currentText()
        city = self.ui.cityList.currentItem()
        zipcode = self.ui.zipList.currentItem()
        if state and city and zipcode:
            sqlstr = f"SELECT Distinct (name), address, city, stars, review_count, checkin_count, postal_code, categories FROM business  WHERE postal_code = '{zipcode.text().strip()}' AND state = '{state}' AND stars"
            sqlstr += " >= 4.0 ORDER BY stars desc;"
            try:
                results = self.executeQuery(sqlstr)
                self.loadSuccessfulList(results)
            except Exception as e:
                print(f'Error in refresh changed (successful list): {e}')

            sqlstr = f"SELECT Distinct (name), address, city, stars, review_count, checkin_count, postal_code, categories FROM business WHERE postal_code = '{zipcode.text().strip()}' AND state = '{state}' AND checkin_count >= 50 ORDER BY stars desc;"
            try:
                results = self.executeQuery(sqlstr)
                self.loadPopularList(results)
            except Exception as e:
                print(f'Error in refresh changed (popular list): {e}')

    def loadSuccessfulList(self, results):
        self.ui.successfulList.clearContents()
        self.ui.successfulList.setColumnCount(4)
        self.ui.successfulList.setRowCount(len(results))
        self.ui.successfulList.setHorizontalHeaderLabels(['name', 'stars', 'Review Rating', '# of Reviews'])
        rowCount = 0
        for row in results:
            self.ui.successfulList.setItem(rowCount, 0, QTableWidgetItem(row[0]))
            self.ui.successfulList.setItem(rowCount, 1, QTableWidgetItem(str(row[3])))
            self.ui.successfulList.setItem(rowCount, 2, QTableWidgetItem(str(row[5])))
            self.ui.successfulList.setItem(rowCount, 3, QTableWidgetItem(str(row[4])))
            rowCount += 1

    def loadPopularList(self, results):
        self.ui.popularList.clearContents()
        self.ui.popularList.setColumnCount(3)
        self.ui.popularList.setRowCount(len(results))
        self.ui.popularList.setHorizontalHeaderLabels(['name', '# of Reviews', '# of Checkins'])
        rowCount = 0
        for row in results:
            self.ui.popularList.setItem(rowCount, 0, QTableWidgetItem(row[0]))
            self.ui.popularList.setItem(rowCount, 1, QTableWidgetItem(str(row[4])))
            self.ui.popularList.setItem(rowCount, 2, QTableWidgetItem(str(row[5])))
            rowCount += 1

    def clearList(self):
        self.ui.businessList.clearContents()
        self.ui.zipList.clear()
        self.ui.cityList.clear()
        self.ui.stateList.clear()
        self.ui.stateList.clearEditText()
        self.ui.categoriesList.clear()
        self.ui.topCategories.clear()
        self.ui.numBusiness.clear()
        self.ui.successfulList.clearContents()
        self.ui.popularList.clearContents()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = Milestone3()
    window.show()
    sys.exit(app.exec_())
