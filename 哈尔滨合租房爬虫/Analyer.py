import re
import os

class Analyer:
    def SetPattern(self, pattern):
        self.pattern = pattern
    
    def Analy(self, text):
        self.res = self.pattern.findall(text)
        return self.res

def Clear(html, r):
    '''
        返回一个res列表
        第一个元素为图片链接
        第二个元素为购买链接
        第三个元素为描述信息
        第四个元素为面积
        第五个元素为地理位置
        第六个元素为价格
    '''
    res = []
    p = re.compile(r'<li  class="house-cell realverify".*?<div class="img-list">.*?<img lazy_src="(.*?)".*?'
                   r'<div class="des">.*?<h2>.*?<a href="(.*?)".*?'
                    r'target="_blank">.*?(.*?)</h2>.*?<p class="room">(.*?)</p>.*?'
                    r'<p class="infor">(.*?)</p>.*?'
                    r'<div class="money">.*?<b class="strongbox">(.*?)</b>'
                     ,re.DOTALL)
    # p = re.compile(r'<li  class="house-cell realverify".*?<div class="img-list">.*?<img lazy_src="(.*?)"', re.DOTALL)
    r.SetPattern(p)
    r.Analy(t)
    # print(r.res[0])
    for i in range(5):
        print('*' * 5)
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
        z[4] = yyds

        # 第六个元素
        z[5] = li[5]

        res.append(z)

    return res

if __name__ == '__main__':
    print(123)
    with open('t.txt', 'r', encoding='utf-8') as f:
        t = f.read() 

    r = Analyer()

    res = Clear(t, r)

    print(res[0])

    # # 分析页面，获取链接，以及标题
    # p1 = re.compile(r'<div class="des">\s*?<h2>\s*?<a href="(.*?)".*?target="_blank">\s*?(.*?)</h2>', re.DOTALL)

    # # 分析页面获取图片地址
    # p2 = re.compile(r'<img lazy_src="(.*?)"')

    # # 获取钱数
    # p3 = re.compile(r'<div class="money">.*?<b class="strongbox">(.*?)</b>', re.DOTALL)

    # # 全部获取
    # p4 = re.compile(r'<li  class="house-cell realverify".*?<h2>.*?<a href="(.*?)".*?' # 链接
    #                 r'target="_blank">.*?(.*?)</h2>.*?<p class="room">(.*?)</p>.*?'
    #                 r'<p class="infor">(.*?)</p>.*?'
    #                 r'<div class="money">.*?<b class="strongbox">(.*?)</b>',
    #                  re.DOTALL)
    # r.SetPattern(p4)

    # r.Analy(t)

    # # for x in r.res[0]:
    # #     print(x)
    # #     print('*' * 50)
    # print(len(r.res))
    # x = r.res[0][3]
    # print(x)
    # p6 = re.compile(r'<a href.*?>(.*?)</a>', re.DOTALL)
    # r.SetPattern(p6)
    # r.Analy(x)
    # print(r.res)
    # ssr = r.res
    # r.SetPattern(re.compile(r'</em>(.*?) '))
    # r.Analy(x)
    # ssr += r.res
    # print(ssr)






