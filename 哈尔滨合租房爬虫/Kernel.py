from PySide2.QtUiTools import QUiLoader
from PySide2.QtWidgets import QApplication, QMessageBox
from Mainlog import Mainlog, sig
from threading import Thread, Lock
from Spider import Spider
import Filtrater
import os
import time
from Sql import Sql

class Kernel:
    def __init__(self) -> None:
        # 主窗口
        self.mainlog = Mainlog()

        # 数据库
        self.sql = Sql()

        # 筛选窗口
        self.filtrater = Filtrater.Filtrater()

        header = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36 Edg/120.0.0.0',
            'Cookie': 'userid360_xml=3E480A513C9BF4503278874D1F3BDEAD; time_create=1703752231354; f=n; commontopbar_new_city_info=202%7C%E5%93%88%E5%B0%94%E6%BB%A8%7Chrb; commontopbar_ipcity=hrb%7C%E5%93%88%E5%B0%94%E6%BB%A8%7C0; 58home=hrb; city=hrb; 58tj_uuid=f2d192c9-0464-47c2-8c75-5551c89736c8; als=0; xxzl_deviceid=eaQEbiCH1M%2Fli3KpMnAhkv45I%2B29DoWg95Vk1J%2BrsLj6jv5R4NvxMFFnl5LltoT6; xxzlclientid=9a9eeefb-c25d-44ea-ad9e-1701395835384; xxzlxxid=pfmx2ArFTcj6SqRJMfHHlD2KW8YlozyBYac2Plnd14iMgNUFm2mDQaHx1Cq8QzuuWK/8; xxzl_smartid=3dc9af07b1f69dae9cd10bf4a837e3b5; ppStore_fingerprint=149543068114AB0AC99A7A67FAEF63DED7958FBBEDFD8E08%EF%BC%BF1701406786496; id58=CpQQXGV4AJBuLyczCOQgAg==; new_uv=10; utm_source=; spm=; init_refer=; new_session=0; wmda_uuid=6f8ab8a28805d9bdc476e022a43aa929; wmda_new_uuid=1; wmda_session_id_10104579731767=1702445580402-75dbbf76-2bb6-068f; wmda_visited_projects=%3B10104579731767; crmvip=; dk_cookie=; PPU=UID=100338252472131&UN=a2ivj6s8q&TT=ada33670e7a8d1cc8138c968571a1c00&PBODY=KrkOqGHsdRxj1cNEs-EgykuywzBKTA53VnTawYq9vlgXN-xxnRXojos_CnWQWjfouvMxZbifrztKivg4oEm11qyishz5hu-IEbGqUe92XxTUXFaZsvIa3RArFXZczH-i-bftp_UANK0HXl9YwWAJhHkl24MKPpG1JxbHB5hBrQk&VER=1&CUID=D3sNVhIosRTqra6VgIDDSg; www58com=UserID=100338252472131&UserName=a2ivj6s8q; 58cooper=userid=100338252472131&username=a2ivj6s8q; 58uname=a2ivj6s8q; passportAccount=atype=0&bstate=0; xxzlbbid=pfmbM3wxMDI5MnwxLjMuMXwxNzAyNDQ1NjI1OTcwfEdDZnJCWk1mL0RwRnBSa3lRMkU5MVRkdzROT0V5dzR0ajM1SXpubGZKNkE9fDU2MWFjYjNjMzA0ZmU4ODAyYmNkOGRlMDcxNzM3ZDFmXzE3MDI0NDU2MjMyNzBfMjMxOWJmZjcxZjliNDY4Zjg0NWI3ZGZhYzJiMTRjMDVfMjA5MDIwNTF8NDQxMTJlYTE3MWVjMDJkODBlZWFlMTg1ZDg4NzExM2NfMTcwMjQ0NTYyNDcwOF8yNTY=; xxzl_cid=773532f3c51540dc8c98be61ba43c1ea; xxzl_deviceid=MYgrnqvGiJFUkgDVN7I0CJVJbtqx4JtLZJMUFa6fGzWTkueM9Q3cMIQIuj7ztfes'
        }

        # 爬虫对象
        self.spider = Spider(header)
        self.spiderflag = False

        # 绑定信号
        sig.GetSource.connect(self.GetSource)
        sig.PutItem.connect(self.PutItem)
        sig.CacheLoadSuccess.connect(self.CacheLoadSuccess)
        sig.DownLoadComplete.connect(self.DownLoadComplete)
        sig.AddItemToSql.connect(self.AddItemToSql)
        sig.Filtrate.connect(self.Filtrate)
        sig.GetFiltrate.connect(self.GetFiltrate)
        sig.CheckSqlEmpty.connect(self.CheckSqlEmpty)

        self.ThreadId = 0 # 给每个线程的id
        self.ThreadDict = {} # 管理线程的字典
        self.lock = Lock() # 线程同步锁

        # sleep(1)
    
    def CheckSqlEmpty(self):
        self.filtrater.SqlEmpty = self.sql.Empty()

    def GetFiltrate(self, choose, sortflag, l, r):
        print(f'get filtrate: {choose} {sortflag} {l} {r}')
        res = {}
        # 先获取范围内的数据
        # 存在无限符号
        if l == '-∞' or r == '∞':
            # 全选
            if l == '-∞' and r == '∞':
                res = self.sql.SelectAll()
            elif l == '-∞':
                res = self.sql.FindLessThan(int(r))
            else:
                res = self.sql.FindGreaterThan(int(l))
        else:
            if int(l) > int(r):
                QMessageBox.critical(
                    self.mainlog.ui,
                    '错误',
                    '范围无效'
                )
                return
            res = self.sql.GetRange(int(l), int(r))
        print(res)
        if choose == '最贵':
            ma = max(key=lambda x: x[1], *res)[1]
            res = list(filter(lambda x: x[1] == ma, res))
            print(res)
        elif choose == '最便宜':
            mi = min(key=lambda x: x[1], *res)[1]
            res = list(filter(lambda x: x[1] == mi, res))
            print(res)
        res = list(res)
        if sortflag == '排序':
            res.sort(key=lambda x: x[1])
        elif sortflag == '逆序':
            res.sort(key=lambda x: x[1], reverse=True)
        print(res)
        self.ShowItemByIdList(res)

    def ShowItemByIdList(self, li):
        self.mainlog.Clear()
        for x in li:
            self.PutItem(x[0])

    def Filtrate(self):
        self.filtrater.ui.show()

    def AddItemToSql(self, id, price):
        self.sql.Insert(id, price)

    def DownLoadComplete(self):
        QMessageBox.information(
            self.mainlog.ui,
            '提示',
            '获取资源成功！'
        )
        self.mainlog.RefreshItem()

        # 爬虫恢复空闲状态
        self.spiderflag = False

        # 告知数据下载完成
        sig.SpiderEnd.emit()
        # self.mainlog.PutAll()
        

    def CacheLoadSuccess(self):
        # 发出提示，告知成功加载
        QMessageBox.information(
            self.mainlog.ui,
            '提示',
            '缓存已经加载完毕！'
        )

    def PutItem(self, id):
        self.mainlog.PutItem(id)

    # 获取资源
    def GetSource(self):
        page = self.mainlog.GetPage()
        print(page)
        # return
        if self.spiderflag:
            QMessageBox.critical(
                self.mainlog.ui,
                '警告',
                '当前爬虫正在获取资源中，请稍后再获取新资源'
            )
            return
        self.spiderflag = True
        print('GetSource')
        # 通知爬虫开始工作
        sig.SpiderWorking.emit()
        
        urlbase = 'https://hrb.58.com/hezu/pn{}/'

        with open('CacheUrl.txt', 'a+', encoding='utf8') as f:
            f.seek(0)
            t = f.read().split()
    
        ssr = self.spider.html

        for id in range(1, page + 1):
            url = urlbase.format(id)
            # 如果未访问过，则访问
            if url not in t:
                st = time.time()
                ssr = self.spider.Visit(url)
                ed = time.time()
                print(f'vis cost {ed - st}')
                with open('CacheUrl.txt', 'a', encoding='utf8') as f:
                    f.write(url + ' ')
            else:
            # 否则直接进入下一轮
                continue
                
            # 清洗获得的html文件提取有效信息
            st = time.time()
            self.res = self.spider.Clear(ssr)
            ed = time.time()
            print(f'Clear Cost {ed - st}s')


            # 读取缓存中的图片地址，判断图片是否已经下载，避免重复下载
            # 为了避免文件不存在而不能读报错，这里用写+打开
            with open('Cache.txt', 'a+', encoding='utf8') as f:
                # 为了不覆盖内容，用追加的写
                # 由于追加打开，于是光标在最后，没法读，先要让光标回到开头
                f.seek(0)
                t = f.read().split('♒')

                if t == ['']:
                    t = []
                else:
                    t = map(lambda x: x.split('❤')[0], t)

            for it in self.res:
                # 如果是新图片，则添加到新id
                if it[0] not in t:
                    self.mainlog.AddItem(it[1], it[5], it[3], it[2], it[4], it[0])
            # 睡眠5秒防止被网站发现是爬虫
            time.sleep(5)
        
        # 下载图片
        st = time.time()
        self.ThreadDict[self.ThreadId] = Thread(target=self.ThreadDownLoadPic, args=(self.ThreadId,))
        self.ThreadDict[self.ThreadId].start()
        self.ThreadId += 1
        ed = time.time()
        print(f'Download cost {ed - st}')
        # 重新加载所有item的图片
        self.mainlog.RefreshItem()
        print('spider over')

    # 下载所有可以下载的图片
    def ThreadDownLoadPic(self, tid):
        # 不存在src文件夹则创建一个
        if not os.path.exists('src'):
            os.mkdir('src')

        # 读取缓存
        with open('Cache.txt', 'a+', encoding='utf8') as f:
            f.seek(0)
            t = f.read().split('♒')
            # t用来获取图片url列表，用于判断是否已经下载
            if t == ['']:
                t = []
            else:
                t = list(map(lambda x: x.split('❤')[0], t))

        for it in self.mainlog.ItemDict.values():
            # 如果某个item的图片未下载则去下载
            if it.picurl not in t: 
                # print(it.picurl)
                
                # 下载图片到相应路径下
                self.spider.DownLoad(it.picurl, f'src/{it.id}.jpg')

                # 将已经下载的图片url追加到Cache文件中
                with open('Cache.txt', 'a', encoding='utf8') as f:
                    '''
                        写入格式为：
                            1.图片url（用来判断唯一）
                            2.id
                            3.详情链接
                            4.价格
                            5.大小
                            6.介绍
                            7.地理位置
                    '''
                    f.write(f'{it.picurl}❤{it.id}❤{it.url}❤{it.price}❤{it.size}❤{it.info}❤{it.location}♒')
        print('yes')
        sig.DownLoadComplete.emit()
        self.ThreadDict.pop(tid)

if __name__ == '__main__':
    app = QApplication()
    k = Kernel()
    app.exec_()
        