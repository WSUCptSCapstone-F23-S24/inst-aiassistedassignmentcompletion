import sys
from PyQt5 import QtWidgets, uic
from PyQt5.QtGui import QStandardItemModel, QStandardItem
import psycopg2
import json

Ui_MainWindow, QtBaseClass = uic.loadUiType("YelpApp.ui")


class YelpApp(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(YelpApp, self).__init__()
        self.setupUi(self)
        self.dbConnect()
        self.initialLoad()
        self.configureEventHandlers()

    def dbConnect(self):
        try:
            self.conn = psycopg2.connect(
                dbname='YelpDB',
                user='postgres',
                password='root',
                host='localhost'
            )
            self.cur = self.conn.cursor()
            print("Database connected successfully")
        except psycopg2.DatabaseError as e:
            print(f"Failed to connect to the database: {e}")
            sys.exit(1)

    def configureEventHandlers(self):
        self.stateList.currentIndexChanged.connect(self.onStateSelected)
        self.cityList.itemSelectionChanged.connect(self.onCitySelected)
        self.zipList.itemSelectionChanged.connect(self.onZipSelected)
        self.searchButton.clicked.connect(self.onSearchButtonClicked)
        self.clearButton.clicked.connect(self.onClearButtonClicked)
        self.refreshButton.clicked.connect(self.onRefreshButtonClicked)

    def initialLoad(self):
        query = "SELECT DISTINCT state FROM Business ORDER BY state;"
        states = self.executeQuery(query)
        self.stateList.addItems([state[0] for state in states])
        self.loadCategories()
        self.categoryList.selectionModel().selectionChanged.connect(self.onCategorySelected)

    def onStateSelected(self, index):
        state = self.stateList.itemText(index)
        self.loadCities(state)

    def loadCities(self, state):
        self.cityList.clear()
        query = "SELECT DISTINCT city FROM Business WHERE state = %s ORDER BY city;"
        cities = self.executeQuery(query, (state,))
        for city in cities:
            self.cityList.addItem(city[0])

    def onCitySelected(self):
        city_items = self.cityList.selectedItems()
        if city_items:
            city = city_items[0].text()
            state = self.stateList.currentText()
            self.loadZipCodes(state, city)

    def loadZipCodes(self, state, city):
        self.zipList.clear()
        query = "SELECT DISTINCT zipcode FROM Business WHERE state = %s AND city = %s ORDER BY zipcode;"
        zip_codes = self.executeQuery(query, (state, city))
        for zip_code in zip_codes:
            self.zipList.addItem(zip_code[0])

    def onZipSelected(self):
        zip_items = self.zipList.selectedItems()
        if zip_items:
            zipcode = zip_items[0].text()
            self.displayZipInfo(zipcode)
            self.displayTopCategories(zipcode)

    def loadCategories(self):
        query = "SELECT DISTINCT category_name FROM Categories ORDER BY category_name;"
        categories = self.executeQuery(query)
        model = QStandardItemModel()
        model.setHorizontalHeaderLabels(['Category'])
        for category in categories:
            model.appendRow(QStandardItem(category[0]))
        self.categoryList.setModel(model)

    def onCategorySelected(self, selected, deselected):
        pass

    def onSearchButtonClicked(self):
        city_items = self.cityList.selectedItems()
        zip_items = self.zipList.selectedItems()
        if city_items and zip_items:
            state = self.stateList.currentText()
            city = city_items[0].text()
            zipcode = zip_items[0].text()
            selected_category = None
            indexes = self.categoryList.selectionModel().selectedIndexes()
            if indexes:
                selected_category = indexes[0].data()
            self.searchBusinesses(state, city, zipcode, selected_category)

    def searchBusinesses(self, state, city, zipcode, category=None):
        base_query = """
        SELECT b.business_name, b.address, b.city, b.stars, COALESCE(r.review_count, 0), 
        ROUND(COALESCE(r.avg_stars, 0)::numeric, 2), COALESCE(c.checkin_count, 0)
        FROM Business b
        LEFT JOIN (
            SELECT business_id, COUNT(*) as review_count, AVG(stars) as avg_stars
            FROM Reviews
            GROUP BY business_id
        ) r ON b.business_id = r.business_id
        LEFT JOIN Checkins c ON b.business_id = c.business_id
        WHERE b.state = %s AND b.city = %s AND b.zipcode = %s
        """

        params = [state, city, zipcode]
        if category:
            category_query = """
            AND b.business_id IN (
                SELECT business_id FROM Categories WHERE category_name = %s
            )
            """
            params.append(category)
            query = base_query + category_query
        else:
            query = base_query

        results = self.executeQuery(query, tuple(params))
        self.populateBusinessGrid(results)

    def populateBusinessGrid(self, business_data):
        model = QStandardItemModel()
        model.setHorizontalHeaderLabels(
            ['Name', 'Address', 'City', 'Rating', '# Reviews', 'Avg Rating', 'Check-Ins'])
        for row in business_data:
            model.appendRow([QStandardItem(str(field)) for field in row])
        self.businessGrid.setModel(model)

    def displayZipInfo(self, zipcode):
        query_business = "SELECT COUNT(*) FROM Business WHERE zipcode = %s;"
        query_zipinfo = "SELECT population, medianIncome, meanIncome FROM ZipcodeData WHERE zipcode = %s;"
        business_count = self.executeQuery(query_business, (zipcode,))
        zip_info = self.executeQuery(query_zipinfo, (zipcode,))
        if business_count:
            self.numBusinessLabel.setText(
                f"# of Businesses: {business_count[0][0]}")
        if zip_info:
            self.populationLabel.setText(f"Total Population: {zip_info[0][0]}")
            self.averageIncomeLabel.setText(
                f"Average Income: ${zip_info[0][2]}")

    def displayTopCategories(self, zipcode):
        query = """
        SELECT category_name, COUNT(*) as category_count
        FROM Categories
        JOIN Business ON Business.business_id = Categories.business_id
        WHERE Business.zipcode = %s
        GROUP BY category_name
        ORDER BY category_count DESC
        LIMIT 5;
        """
        categories = self.executeQuery(query, (zipcode,))
        model = QStandardItemModel()
        model.setHorizontalHeaderLabels(['Category', 'Count'])
        for category, count in categories:
            model.appendRow(
                [QStandardItem(category), QStandardItem(str(count))])
        self.topCategoryList.setModel(model)

    def onClearButtonClicked(self):
        self.stateList.setCurrentIndex(0)

        self.cityList.clear()

        self.zipList.clear()

        self.loadCategories()
        if hasattr(self.categoryList.selectionModel(), 'clear'):
            self.categoryList.selectionModel().clear()

        self.businessGrid.setModel(QStandardItemModel())

        self.numBusinessLabel.setText("# of Businesses:")
        self.populationLabel.setText("Total Population:")
        self.averageIncomeLabel.setText("Average Income:")

        self.topCategoryList.setModel(QStandardItemModel())

    def executeQuery(self, query, params=None):
        if params is None:
            self.cur.execute(query)
        else:
            self.cur.execute(query, params)
        return self.cur.fetchall()

    def onRefreshButtonClicked(self):
        selected_zip = self.zipList.currentItem()
        if selected_zip:
            zipcode = selected_zip.text()
            self.displayPopularBusinesses(zipcode)
            self.displaySuccessfulBusinesses(zipcode)

    def displayPopularBusinesses(self, zipcode):
        query = """
        SELECT business_name, address, city, stars, review_count
        FROM Business
        WHERE zipcode = %s
        ORDER BY review_count DESC, stars DESC
        LIMIT 10
        """
        results = self.executeQuery(query, (zipcode,))
        self.populateTable(self.popularBusinesses, results, [
                           'Name', 'Address', 'City', 'Rating', 'Reviews'])

    def displaySuccessfulBusinesses(self, zipcode):
        query = """
        SELECT business_name, address, city, stars, checkin_count
        FROM Business
        WHERE zipcode = %s
        ORDER BY checkin_count DESC, stars DESC
        LIMIT 10
        """
        results = self.executeQuery(query, (zipcode,))
        self.populateTable(self.successfulBusinesses, results, [
                           'Name', 'Address', 'City', 'Rating', 'Check-ins'])

    def populateTable(self, table, data, headers):
        model = QStandardItemModel()
        model.setHorizontalHeaderLabels(headers)
        for row in data:
            items = [QStandardItem(str(field)) for field in row]
            model.appendRow(items)
        table.setModel(model)

    def closeEvent(self, event):
        self.cur.close()
        self.conn.close()
        event.accept()


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    main_window = YelpApp()
    main_window.show()
    sys.exit(app.exec_())
