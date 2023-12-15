from Viser import Viser
from Analyer import Analyer
from PictureDownLoader import PictureDownLoader
import re

class Spider:
    def __init__(self, header):
        self.header = header
        self.viser = Viser(self.header)
        self.analyer = Analyer()
        self.down = PictureDownLoader(self.header)
        self.html = ''
    
    def Visit(self, url = ''):
        self.html = self.viser.Visit(url)
        return self.html
    
    def DownLoad(self, url = '', path = ''):
        self.down.DownLoad(url, path)
    
    def SetAnalyer(self, pattern):
        self.analyer.SetPattern(pattern)
    
    def Analyse(self, text):
        self.res = self.analyer.Analy(text)
        return self.res

    def Clear(self, html):
        '''
            返回一个res列表
            第一个元素为图片链接: str
            第二个元素为购买链接: str
            第三个元素为描述信息: str
            第四个元素为面积: (居室, 平方)
            第五个元素为地理位置: str
            第六个元素为价格: str
        '''
        r = self.analyer
        res = []
        p = re.compile(r'<li  class="house-cell realverify".*?<div class="img-list">.*?<img lazy_src="(.*?)".*?'
                    r'<div class="des">.*?<h2>.*?<a href="(.*?)".*?'
                        r'target="_blank">.*?(.*?)</h2>.*?<p class="room">(.*?)</p>.*?'
                        r'<p class="infor">(.*?)</p>.*?'
                        r'<div class="money">.*?<b class="strongbox">(.*?)</b>'
                        ,re.DOTALL)
        # p = re.compile(r'<li  class="house-cell realverify".*?<div class="img-list">.*?<img lazy_src="(.*?)"', re.DOTALL)
        r.SetPattern(p)
        r.Analy(html)
        # print(r.res[0])
        # for i in range(5):
        #     print('*' * 5)
        for li in r.res:
            z = [0] * 6

            # 第一个元素
            z[0] = li[0]

            # 第二个元素
            z[1] = li[1]

            # 第三个元素
            ssr = li[2].strip()
            ssr = ssr.strip('</a>')
            ssr = ssr.strip()
            z[2] = ssr

            # 第四个元素
            ssr = li[3].strip()
            ssr = ssr.split()
            yyds = (ssr[0], ssr[1].split(';')[-1])
            z[3] = yyds

            # 第五个元素
            ssr = li[4]
            # print(ssr)
            r.SetPattern(re.compile(r'<a href.*?>(.*?)</a>', re.DOTALL))
            r.Analy(ssr)
            yyds = r.res
            r.SetPattern(re.compile(r'</em>(.*?) '))
            r.Analy(ssr)
            yyds += r.res
            z[4] = ' '.join(yyds)

            # 第六个元素
            z[5] = li[5]

            res.append(z)

        return res

if __name__ == '__main__':
    s = Spider({})
    print(233)
    with open('t.txt', 'r', encoding='utf-8') as f:
        t = f.read()
    r = s.Clear(t)
    print(r[0])
    s.DownLoad(r[0][0], '2.jpg')
