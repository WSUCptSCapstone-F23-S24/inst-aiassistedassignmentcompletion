import sys
from PyQt5 import QtWidgets, uic
from PyQt5.QtGui import QStandardItemModel, QStandardItem
import psycopg2

Ui_MainWindow, QtBaseClass = uic.loadUiType("YelpApp.ui")


class YelpApp(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(YelpApp, self).__init__()
        self.setupUi(self)
        self.dbConnect()
        self.configureEventHandlers()
        self.initialLoad()

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

    def initialLoad(self):
        query = "SELECT DISTINCT state FROM Business ORDER BY state;"
        states = self.executeQuery(query)
        self.stateList.addItems([state[0] for state in states])

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
            # Assuming you have a label for this
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

    def executeQuery(self, query, params=None):
        if params is None:
            self.cur.execute(query)
        else:
            self.cur.execute(query, params)
        return self.cur.fetchall()

    def closeEvent(self, event):
        self.cur.close()
        self.conn.close()
        event.accept()


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    main_window = YelpApp()
    main_window.show()
    sys.exit(app.exec_())
