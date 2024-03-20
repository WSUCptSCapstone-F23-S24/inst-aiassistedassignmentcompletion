import pandas as pd
from PyQt5.QtWidgets import QMainWindow, QApplication
from PyQt5 import uic
import sys
#import script

qtCreatorFile = "YelpApp.ui"
Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

class YelpApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.loadBusinessData()
        self.populateUI()
        self.ui.stateList.currentIndexChanged.connect(self.stateSelected)

    # Load business data and store into a df
    def loadBusinessData(self):
        self.df = pd.read_json('Dataset/yelp_business.json', lines=True)

    # Populates the UI with the data
    def populateUI(self):
        self.showStates()

    # Displays states in statelist
    def showStates(self):
        # Drop NaN state rows
        self.df = self.df.dropna(subset=['state'])

        # Sort states alphabetically in the list instead of the order they show up in the dataset
        states = sorted(self.df['state'].unique())

        # Add states to the listbox
        for state in states:
            self.ui.stateList.addItem(state)
        self.ui.stateList.setCurrentIndex(-1)

    # Displays zip codes in ziplist
    def showZipcodes(self, selectedState):
        # Drop NaN state and postal code rows
        self.df = self.df.dropna(subset=['state', 'postal_code'])

        # Filter DataFrame for the selected state
        state_df = self.df[self.df['state'] == selectedState]

        # Get unique zipcodes for the selected state and sort them
        zipcodes = sorted(state_df['postal_code'].unique())

        # Clear items in zip list when a new state is selected
        self.ui.zipList.clear()

        # Add zip codes to the widget
        for zipcode in zipcodes:
            self.ui.zipList.addItem(zipcode)

    def showCities(self):
        pass

    def showZipcodeStatistics(self):
        pass

    def showCategories(self):
        pass

    def showPopulation(self):
        pass

    def showBusinesses(self):
        pass

    def showPopularBusinesses(self):
        pass

    def showSuccessfulBusinesses(self):
        pass

    def refresh(self):
        pass

    def clear(self):
        pass

    # Handles selecting a state and populating with the zip codes when changed
    def stateSelected(self):
        try:
            selectedState = self.ui.stateList.currentText()
            self.showZipcodes(selectedState)

        except Exception as e:
            print(f"Error: {e}")

    def citySelected(self):
        pass

    def zipSelected(self):
        pass

    def categorySelected(self):
        pass

if __name__ == '__main__':
    app = QApplication(sys.argv)
    mainWindow = YelpApp()
    mainWindow.show()
    sys.exit(app.exec_())
