from PySide2.QtWidgets import QApplication, QWidget, QMessageBox
from PySide2.QtUiTools import QUiLoader
from PySide2.QtGui import QIcon, QPixmap
from PySide2.QtCore import QSize
import Mainlog
import webbrowser

class Item(QWidget):
    def __init__(self) -> None:
        super().__init__()
        self.ui = QUiLoader().load('item.ui')

        self.ui.picbutton.clicked.connect(self.GoToBuy)

        Mainlog.sig.ItemUpdate.connect(lambda x: x.Update())
        # self.ui.show()

    def SetInfo(self, id = 0, url = '', price = '', size = (), info = '', location = '', pic = '', picurl = ''):
        self.id = id
        self.url = url
        self.price = price
        self.size = size
        self.info = info
        self.location = location
        self.pic = pic
        self.picurl = picurl
        # self.Update()
    
    def Update(self):
        # print(233)
        self.picsrc = QPixmap(self.pic)
        self.ui.picbutton.setIcon(QIcon(self.picsrc))
        self.ui.picbutton.setIconSize(self.picsrc.size())
        self.ui.label_price.setText(self.price)
        self.ui.label_size1.setText(self.size[0])
        self.ui.label_size2.setText(self.size[1])
        self.ui.label_info.setText(self.info)
        self.ui.label_location.setText(self.location)
    
    # 点击后打开网页
    def GoToBuy(self):
        try:
            webbrowser.open(self.url)
        except webbrowser.Error as e:
            QMessageBox.critical(self.ui, '浏览器出错', f'{e}')
            print(e)

if __name__ == '__main__':
    a = QApplication()
    i = Item()
    i.SetInfo(1, 'https://www.baidu.com', '666',
              ('主卧', '10'), '我也不知道',
              '哈尔滨理工大学', pic='1.jpg')
    i.Update()
    i.ui.show()
    a.exec_()


