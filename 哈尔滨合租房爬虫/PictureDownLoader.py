import requests

class PictureDownLoader:
    def __init__(self, header):
        self.head = header

    def DownLoad(self, url, path):
        self.url = url
        self.path = path
        res = requests.get(url=self.url, headers=self.head)
        with open(self.path, 'wb') as f:
            f.write(res.content)

if __name__ == '__main__':
    print(666)

    p = PictureDownLoader({})
    # url = 'https://pic1.58cdn.com.cn/anjuke_58/d202c6b5e3caafcf13ed4b382ddd5cdb?w=696&h=522&crop=1&t=1&srotate=1&w=640&h=480&crop=1'

    # cookie = 'userid360_xml=3E480A513C9BF4503278874D1F3BDEAD; time_create=1703752231354; f=n; commontopbar_new_city_info=202%7C%E5%93%88%E5%B0%94%E6%BB%A8%7Chrb; commontopbar_ipcity=hrb%7C%E5%93%88%E5%B0%94%E6%BB%A8%7C0; 58home=hrb; city=hrb; 58tj_uuid=f2d192c9-0464-47c2-8c75-5551c89736c8; als=0; xxzl_deviceid=eaQEbiCH1M%2Fli3KpMnAhkv45I%2B29DoWg95Vk1J%2BrsLj6jv5R4NvxMFFnl5LltoT6; id58=CrINbGVomEoD70rKBEr1Ag==; new_uv=5; utm_source=; spm=; init_refer=https%253A%252F%252Fhrb.58.com%252Fhezu%252F%253FPGTID%253D0d100000-000c-a919-c94f-27906ce7718d%2526ClickID%253D9; f=n; new_session=0; xxzlclientid=9a9eeefb-c25d-44ea-ad9e-1701395835384; xxzlxxid=pfmx2ArFTcj6SqRJMfHHlD2KW8YlozyBYac2Plnd14iMgNUFm2mDQaHx1Cq8QzuuWK/8; crmvip=; dk_cookie=; PPU=UID=100338252472131&UN=a2ivj6s8q&TT=f224eca82c5cf59e419b8cfa3cafe704&PBODY=aeQ1V-zaigoIfk-IvuLiwlrO0tMi_BCjZ4C_MJe-5ZbRh0J1HXImsz-O67ajt8GGFOD6y4PPs9YTfUQsEJnB128rxAS6dqBAaCJTv3Z5nfR9MCDHdk_YMsP1Y0THQpYfrg45AuMT0Itg-cw6wjV_0THMhxrpn5n6ccP53oxwKbg&VER=1&CUID=D3sNVhIosRTqra6VgIDDSg; www58com=UserID=100338252472131&UserName=a2ivj6s8q; 58cooper=userid=100338252472131&username=a2ivj6s8q; 58uname=a2ivj6s8q; passportAccount=atype=0&bstate=0; xxzl_smartid=3dc9af07b1f69dae9cd10bf4a837e3b5; ppStore_fingerprint=149543068114AB0AC99A7A67FAEF63DED7958FBBEDFD8E08%EF%BC%BF1701395947864; xxzl_cid=773532f3c51540dc8c98be61ba43c1ea; xxzl_deviceid=/Q1rgRgdF846t9myMC9PmGxod3BmxKIJhamNsFmYiIYsrwh9bOAv6m0p0iw0f00J; xxzlbbid=pfmbM3wxMDI5MnwxLjMuMXwxNzAxMzk1OTUwNDI0fHZZeGg0d2wzQzlGWWhqaDhtS0ZEMGNBRjF5Ylc4RjduRHp3cWpxOVBXK0U9fGYxZTBiYzBkZDMxMWMzMWQ5MzllN2RmMjlkNjc4ODJkXzE3MDEzOTU5NDg0MTJfYjk0NTczNWEzNjk3NGIyZDg0NTk0YWZkZWU2NThiYmRfMTg2NDg5Njk2OHw5MjNlMTlhMmY1MjA0N2RhMDhiMTI4YWM2MWJhNmEwMF8xNzAxMzk1OTQ5MTk3XzI1Ng=='

    # header = {
    #     'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36 Edg/119.0.0.0',
    #     'Cookie': cookie
    # }