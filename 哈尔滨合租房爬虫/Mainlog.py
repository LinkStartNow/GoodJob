from PySide2.QtUiTools import QUiLoader
from PySide2.QtWidgets import QApplication, QMessageBox, QPushButton
from PySide2.QtCore import QObject, Signal
from Item import Item
from threading import Thread, Lock
from time import sleep

class MySignals(QObject):
    # 按下获取按钮后，信号通知Kernel调用获取方法
    GetSource = Signal()

    # 每从缓存中读取到一个对象信息后，就通知mainlog生成一个item对象
    AddLoadItem = Signal(int, str, str, tuple, str, str, str)

    # 当缓存加载完毕后，告知Kernel缓存加载完毕
    CacheLoadSuccess = Signal()

    # 当下载线程完成后，通知Kernel下载完成
    DownLoadComplete = Signal()

    # 每创建一个item对象，通知kernel将信息录入数据库
    AddItemToSql = Signal(int, str)

    # 当按下了筛选键，通知kernel显示筛选窗口
    Filtrate = Signal()

    # 当在筛选框选择好条件进行筛选时，将筛选条件发送给kernel处理
    GetFiltrate = Signal(str, str, str, str)

    # 爬虫开始工作，通知筛选器将爬虫工作状态设置成忙碌
    SpiderWorking = Signal()

    # 爬虫工作完毕，通知筛选器将爬虫工作状态设置成空闲
    SpiderEnd = Signal()

    # 在筛选框中点击筛选后，通知kernel查询数据库是否为空
    CheckSqlEmpty = Signal()

    # 爬虫的html文件获取并分析完成后通知kernel打开下载图片线程
    VisitComplete = Signal()

    # 在子线程分析的时候每分析出一条item的信息通知mainlog创造一个item
    NewItemFind = Signal(str, str, tuple, str, str, str)

    # 每下载成功一个图片，通知这个图片对应的item去更新信息，重新加载图片
    ItemUpdate = Signal(Item)


sig = MySignals()

class Mainlog:
    ItemCnt = 0

    def __init__(self) -> None:
        self.ui = QUiLoader().load('mainlog.ui')

        self.ItemDict = {}

        # 线程锁，用来锁定itemdict
        self.lock = Lock()
        
        

        # 可选取页数的集合
        self.PageList = {'1', '2', '3'}
        k = list(self.PageList)
        k.sort(key=lambda x: int(x))
        self.PageList = set(k)

        # 添加页数选项
        self.ui.comboBox_Chose_page.addItems(k)

        # 绑定信号与槽
        self.ui.pushButton_2.clicked.connect(lambda: sig.Filtrate.emit())
        self.ui.lineEdit_Page.returnPressed.connect(self.InPutPage)
        self.ui.pushButton.clicked.connect(lambda: sig.GetSource.emit())
        # 缓存读取出一个数据就让主线程创建一个item
        sig.AddLoadItem.connect(self.AddLoadItem)
        sig.SpiderWorking.connect(self.SpiderWorking)
        sig.NewItemFind.connect(self.NewItemFind)

        # 创建一个线程用于加载缓存，避免影响用户体验
        self.t = Thread(target=self.Thread_init)
        self.t.start()

        self.ui.show()
    
    def NewItemFind(self, url, price, size, info, location, picurl):
        self.AddItem(url, price, size, info, location, picurl)

    def GetPage(self) -> int:
        return int(self.ui.comboBox_Chose_page.currentText())

    def SpiderWorking(self):
        QMessageBox.information(
            self.ui,
            '提示',
            '爬虫开始工作，可能需要一些时间获取资源，请耐心等待！'
        )

    # 清空所有
    def Clear(self):
        print('clear')
        for it in self.ItemDict.values():
            it.ui.hide()
        

    # 展示所有item
    def PutAll(self):
        for it in self.ItemDict.values():
            self.PutItem(it.id)

    # 添加缓存中的item
    def AddLoadItem(self, id, url, price, size, info, location, pic):
        t = self.ItemDict[id] = Item()
        t.SetInfo(id, url, price, size, info, location, pic)
        t.Update()
        # self.PutItem(id)
        
        # 如果此时已经是最后一个，说明加载完毕了
        if id == self.ItemCnt:
            print('Cache Load Successfully!')
            # 发出信号通知Kernel可以继续了
            sig.CacheLoadSuccess.emit()

    def Thread_init(self):
        # 重启软件后，我们需要加载缓存中的内容生成对应的item
        with open('Cache.txt', 'a+', encoding='utf8') as f:
            f.seek(0)
            t = f.read().split('♒')
            
            # 没有缓存文件直接跳过
            if t == ['']:
                print('Cache Load Successfully!')
                return

            # 获得id
            l1 = map(lambda x: x.split('❤')[1], t[:-1])
            l1 = list(map(eval, l1))

            # 获得url
            l2 = list(map(lambda x: x.split('❤')[2], t[:-1]))

            # 获得价格
            l3 = list(map(lambda x: x.split('❤')[3], t[:-1]))

            # 获得大小
            l4 = map(lambda x: x.split('❤')[4], t[:-1])
            l4 = list(map(eval, l4))

            # 获得介绍
            l5 = list(map(lambda x: x.split('❤')[5], t[:-1]))

            # 获得地理位置
            l6 = list(map(lambda x: x.split('❤')[6], t[:-1]))
        
        # self.lock.acquire()
        for i in range(len(l1)):
            sig.AddLoadItem.emit(l1[i], l2[i], l3[i], l4[i], l5[i], l6[i], f'src/{l1[i]}.jpg')

        self.ItemCnt = max(l1)

    # 重新加载信息
    def RefreshItem(self):
        for it in self.ItemDict.values():
            it.Update()

    def AddItem(self, url, price, size, info, location, picurl):
        self.lock.acquire()
        self.ItemCnt += 1
        id = self.ItemCnt
        sig.AddItemToSql.emit(id, price)
        t = self.ItemDict[id] = Item()
        self.lock.release()
        pic = f'src/{id}.jpg'
        t.SetInfo(id, url, price, size, info, location, pic, picurl)

    # 将id对应的item显示出来
    def PutItem(self, id):
        ui = self.ItemDict[id].ui
        self.ui.verticalLayout.addWidget(ui)
        ui.show()


    # 输入框按下回车的槽函数
    def InPutPage(self):
        t = self.ui.lineEdit_Page.text()
        if not t:
            QMessageBox.critical(self.ui, '错误', '输入不能为空')
            return
        if int(t) <= 0:
            QMessageBox.critical(self.ui, '错误', '请输入正整数页数')
            return
        self.PageList |= {t}
        k = list(self.PageList)
        k.sort(key=lambda x: int(x))
        print(k)
        self.PageList = set(k)
        self.ui.comboBox_Chose_page.clear()
        self.ui.comboBox_Chose_page.addItems(k)
        self.ui.comboBox_Chose_page.setCurrentText(t)

if __name__ == '__main__':
    a = QApplication()
    i = Mainlog()
    # i.AddItem('https://www.baidu.com', '123', '不知道', '我', '地点', '123')
    # i.RefreshItem()
    # i.PutItem(1)
    i.ui.show()
    a.exec_()


