import sqlite3

class Sql:
    def __init__(self) -> None:
        self.con = sqlite3.connect('data.db')

        self.cur = self.con.cursor()

        self.cur.execute('''CREATE TABLE IF NOT EXISTS house(
                            id INT PRIMARY KEY,
                            price INT
        )''')
    
    def SearchById(self, id: int):
        self.cur.execute('SELECT * FROM house WHERE id = ?', (id, ))
        return self.cur.fetchall()

    # 检测是否为空
    def Empty(self):
        self.cur.execute('SELECT * FROM house')
        if self.cur.fetchall():
            return False
        return True

    # 插入数据
    def Insert(self, id: int, price: str):
        # 已经有该数据了就不插入了
        self.cur.execute('SELECT * FROM house WHERE id = ?', (id,))
        if self.cur.fetchall():
            return
        
        self.cur.execute('INSERT INTO house VALUES(?, ?)', (id, int(price)))
        self.con.commit()

    # 获取所有
    def SelectAll(self):
        self.cur.execute('SELECT * FROM house')
        res = self.cur.fetchall()
        return res

    # 获取最贵房子
    def FindMax(self):
        self.cur.execute('''SELECT * FROM house WHERE price = (
                            SELECT max(price) FROM house
        )''')
        res = self.cur.fetchall()
        res = list(map(lambda x: x, res))
        return res
    
    # 获取最便宜房子
    def FindMin(self):
        self.cur.execute('''SELECT * FROM house WHERE price = (
                            SELECT min(price) FROM house
        )''')
        res = self.cur.fetchall()
        res = list(map(lambda x: x, res))
        return res
    

    def FindGreaterThan(self, price: int):
        self.cur.execute('''SELECT * FROM house WHERE price >= ?''', (price, ))
        res = self.cur.fetchall()
        res = set(map(lambda x: x, res))
        return res

    def FindLessThan(self, price: int):
        self.cur.execute('''SELECT * FROM house WHERE price <= ?''', (price, ))
        res = self.cur.fetchall()
        res = set(map(lambda x: x, res))
        return res

    def GetRange(self, l: int, r: int):
        res = self.FindGreaterThan(l) & self.FindLessThan(r)
        return res

    # 将要返回的值排序
    def GetSort(self, li):
        res = list(li)
        res.sort(key=lambda x: x[1])
        return res
    
    # 将要返回的列表逆序
    def GetSortReserve(self, li):
        return tuple(reversed(self.GetSort(li)))

if __name__ == '__main__':
    s = Sql()
    # s.Insert(1, 3)
    print(s.Empty())
    # print(s.SelectAll())
    print(s.SearchById(210))