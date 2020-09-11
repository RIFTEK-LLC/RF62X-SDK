import numpy as np #np.ctypeslib.as_array()
import sys, threading
import matplotlib
matplotlib.use('QT5Agg')
import matplotlib.pylab as plt
from matplotlib.backends.backend_qt5agg import FigureCanvas 
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar
from PyQt5 import QtCore, QtWidgets, uic
from PyQt5.QtWidgets import QMessageBox,QTableWidgetItem
from time import sleep

import sys
sys.path.append("../../../rf62Xwrappers/Python/")
from PYSDK import const_protocol, const_scanner_type, const_parameter_name, const_old_data_type  # enums
from PYSDK import rf627_Error, rf627_device  # PySDK classes
from PYSDK import sdk_init, get_sdk_version, search_scanners, select_scanner  # PySDK functions
from PYSDK_functions import _CONST_parameter_names_array #parameter names as list of strings (for current demo)

# ===================== RF627 Python SDK demo ================
# Program GUI is done using PyQt5.
# Profiles acquisition and display is done in two separate threads.
# Profiles are converted to numpy structured arrays using numpy.
# Profiles are displayed using matplotlib.

class MyWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super(MyWindow, self).__init__()
        #Load GUI file
        self.ui=uic.loadUi('gui.ui', self)  
        
        #Init class variables
        self.list_of_scanners=[]
        self.current_scanner=None
        self.prof=None
        self.prof_count=0 #for fps
        self.EXIT=0 #exit from threads flag
        
        #Init SDK
        sdk_init()
        
        #UI setup
        self.pushButton.clicked.connect(self.click_search_scanners)
        self.listWidget.itemClicked.connect(self.click_scanner_selected) 
        self.comboBox.activated.connect(self.click_parameter_selected)
        self.comboBox.clear()
        self.comboBox.addItems([str(i)+'  '+_CONST_parameter_names_array[i] for i in range(len(_CONST_parameter_names_array))])
        self.fig1 = plt.figure()
        self.ax1 = self.fig1.add_subplot(111)
        self.fig1.canvas.draw()
        self.plotWidget = FigureCanvas(self.fig1)
        lay = QtWidgets.QVBoxLayout(self.plot_graph)  
        lay.setContentsMargins(0, 0, 0, 0)      
        lay.addWidget(self.plotWidget)
        self.ui.tableWidget.horizontalHeader().setStretchLastSection(True)
        self.ui.tableWidget.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers)
        self.addToolBar(QtCore.Qt.BottomToolBarArea, NavigationToolbar(self.plotWidget, self))

        #Start profile acquisition thread
        self.read_profiles_thread = threading.Thread(target=self.read_profiles_in_thread, args=())
        self.read_profiles_thread.start()
        #Start profile display thread
        self.show_profiles_thread = threading.Thread(target=self.show_profiles_in_thread, args=())
        self.show_profiles_thread.start()

    def read_profiles_in_thread(self):
        ''' update self.prof in thread'''
        while(not self.EXIT):
            if self.current_scanner:
                prof = self.current_scanner.get_profile2D_from_scanner()
                if prof:
                    self.prof=prof
                    self.prof_count+=1

    def show_profiles_in_thread(self):
        ''' show self.prof every second in this thread'''
        while(not self.EXIT):
            last_profile_number=self.prof_count
            sleep(1) #wait for 1 second
            fps=self.prof_count-last_profile_number
            if self.prof:
                    xz=np.ctypeslib.as_array(self.prof['points'], shape=(self.prof['points_count'],)) 
                    #xz is Numpy Structured Array
                    self.ax1.cla()
                    self.ax1.scatter(xz['x'], xz['z'], s=1, color='r')
                    if self.current_scanner:
                        plt.title('Name: '+str(self.current_scanner.info['device_name'])+', FPS: '+str(fps))
                    else:
                        plt.title('Please, select scanner from the list')
                    self.fig1.canvas.draw()
                    self.fig1.canvas.flush_events()
 
    def click_parameter_selected(self,item):
        ''' read parameter from device'''
        self.ui.tableWidget.setRowCount(0)
        if (self.current_scanner):
            info = self.current_scanner.get_parameter(item)
            if info:
                print('+',item,info['name'])
                for key, value in info.items():
                    if key!='ctypes':
                        print('\t',str(key),str(value))
                        rowPosition = self.ui.tableWidget.rowCount()
                        self.ui.tableWidget.insertRow(rowPosition)
                        self.ui.tableWidget.setItem(rowPosition, 0, QTableWidgetItem(str(key))) 
                        self.ui.tableWidget.setItem(rowPosition, 1, QTableWidgetItem(str(value))) 
            else:
                print('-',item,_CONST_parameter_names_array[item])

        else:
            QMessageBox.about(self, "Error", "Please, click 'Search Scanners' and select scanner from the list")

    def click_scanner_selected(self,item):
        ''' select device from self.list_of_scanners'''
        if self.current_scanner:
            self.current_scanner.disconnect_from_scanner()

        ip=self.list_of_scanners[ self.ui.listWidget.currentRow() ].info['ip_address']
        self.current_scanner=select_scanner(self.list_of_scanners, ip_address=ip)
        if not self.current_scanner:
             QMessageBox.about(self, "Error", "Scanner with ip '"+ip+"' was not selected")
        else:
            self.current_scanner.read_params_from_scanner()
            self.ui.comboBox.setEnabled(True)

    def click_search_scanners(self):
        '''search_scanners and save result to self.list_of_scanners'''
        self.ui.listWidget.clear()
        if self.current_scanner:
            self.current_scanner.disconnect_from_scanner()
            self.current_scanner=None
        self.list_of_scanners = search_scanners(protocol=const_protocol.kSERVICE, scanner_type=const_scanner_type.kRF627_OLD)
        self.ui.comboBox.setEnabled(False)
        if (len(self.list_of_scanners)==0):
            QMessageBox.about(self, "Error", "No scanners were found")
        else:
            for i in range(len(self.list_of_scanners)):
                self.ui.listWidget.addItem("Device "+str(i)+": "+self.list_of_scanners[i].info['device_name']+" ["+self.list_of_scanners[i].info['ip_address']+"] ")
   
    def closeEvent(self, event):
        '''stop threads and exit'''
        self.EXIT=True #stop thread flag
        self.read_profiles_thread.join()
        self.show_profiles_thread.join()
        event.accept()
        app.quit()
        sys.exit()    

if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec_())