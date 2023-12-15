from PySide2.QtUiTools import QUiLoader
from PySide2.QtWidgets import QApplication, QMessageBox
from Mainlog import sig
import time

class Filtrater:
    def __init__(self):
        self.SpiderStatus = False
        self.SqlEmpty = 0 # 0表示非空，1表示空，-1表示正在查询

        self.ui = QUiLoader().load('Filtrater.ui')

        # 绑定按钮信号的槽
        self.ui.pushButton_Do.clicked.connect(self.Filtrate)
        self.ui.pushButton_Min.clicked.connect(self.TurnToMin)
        self.ui.pushButton_Max.clicked.connect(self.TurnToMax)
        self.ui.pushButton_Undo.clicked.connect(self.Cancel)
        sig.SpiderWorking.connect(self.SpiderWorking)
        sig.SpiderEnd.connect(self.SpiderEnd)
    
    def SpiderEnd(self):
        self.SpiderStatus = False

    def SpiderWorking(self):
        self.SpiderStatus = True

    def Cancel(self):
        self.ui.hide()

    def TurnToMin(self):
        self.ui.lineEdit_num_left.setText('-∞')

    def TurnToMax(self):
        self.ui.lineEdit_num_right.setText('∞')

    def Filtrate(self):
        if self.SpiderStatus:
            QMessageBox.critical(
                self.ui,
                '警告',
                '正在爬取资源中，为了更好的用户体验,禁止筛选!请耐心等待！'
            )
            self.ui.hide()
            return
        # 去获取是否有数据
        self.SqlEmpty = -1
        sig.CheckSqlEmpty.emit()

        # 每隔0.5秒检查一次，是否已经检查完数据库为空情况
        while self.SqlEmpty == -1:
            time.sleep(0.5)

        if self.SqlEmpty:
            QMessageBox.information(
                self.ui,
                '提示',
                '数据库为空，请先获取资源！'
            )
            self.ui.hide()
            return
        choose = self.ui.buttonGroup_Choose.checkedButton().text()
        sortflag = self.ui.buttonGroup_Sort.checkedButton().text()
        l = self.ui.lineEdit_num_left.text()
        r = self.ui.lineEdit_num_right.text()
        print(choose, sortflag)
        print(l, r)
        sig.GetFiltrate.emit(choose, sortflag, l, r)
        self.ui.hide()


if __name__ == '__main__':
    app = QApplication()
    f = Filtrater()
    f.ui.show()
    app.exec_()
