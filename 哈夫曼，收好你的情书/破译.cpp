#include <bits/stdc++.h>

#define run(i, a, b) for(int i = a; i <= b; i ++)

using namespace std;

const int N = 1e6 + 7;

char s[N], po[100][100], res[N];
// s是待破译串，po记录破译码，res是破译后的结果

int tot; // 记录破译码的数目

int len; // 加密码的长度

struct trie
{
    // 由于全部都是英文和某些符号于是种类不过100，单个编码长度也不过100，于是字典树开10000就够了
    int t[10000][2], tot; // tot记录字典树节点个数
    char ed[10000]; // ed记录某个破译码对应的破译后的字符
    void add(char* s)
    {
        int l = strlen(s), p = 0; l -= 2; // 由于读入时会把行末回车也读进来，懒得处理了这里就直接l-2
        run(i, 2, l)
        {
            int j = s[i] - '0';
            if(!t[p][j]) t[p][j] = ++ tot;
            p = t[p][j];
        }
        ed[p] = s[0];
    }
    void yyds() // 破译的关键程序，yyds！
    {
        // pos是待破译串当前破译的位置，cnt是辅助存储输出的
        int pos = 1, p = 0, cnt = 0;
        while(pos <= len)
        {
            int j = s[pos] - '0';
            p = t[p][j];
            if(ed[p])
            {
                res[++ cnt] = ed[p];
                p = 0;
            }
            pos ++;
        }
    }
} t;

int main()
{
    FILE* f = fopen("e:/想说的话.txt", "rt"); // 存储待破译码的文件
    fgets(s + 1, N, f);
//    printf("请输入要翻译的码:");
//    scanf("%s", s + 1);
//    printf("%s\n", s + 1);
    len = strlen(s + 1);
    fclose(f);
    f = fopen("e:/破译码.txt", "rt"); // 存储破译码的文件
    while(!feof(f)) fgets(po[++ tot], 100, f); tot --;
//    puts("请输入破译码：");
//    run(i, 1, tot) printf("%s", po[i]);
    fclose(f);
    f = nullptr;
    run(i, 1, tot) t.add(po[i]);
    t.yyds();
    printf("%s", res + 1);
}
