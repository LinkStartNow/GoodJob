#include <bits/stdc++.h>

#define run(i, a, b) for(int i = a; i <= b; i ++)

using namespace std;

const int N = 1e6 + 7;

char s[N], po[100][100], res[N];
// s�Ǵ����봮��po��¼�����룬res�������Ľ��

int tot; // ��¼���������Ŀ

int len; // ������ĳ���

struct trie
{
    // ����ȫ������Ӣ�ĺ�ĳЩ�����������಻��100���������볤��Ҳ����100�������ֵ�����10000�͹���
    int t[10000][2], tot; // tot��¼�ֵ����ڵ����
    char ed[10000]; // ed��¼ĳ���������Ӧ���������ַ�
    void add(char* s)
    {
        int l = strlen(s), p = 0; l -= 2; // ���ڶ���ʱ�����ĩ�س�Ҳ�����������ô����������ֱ��l-2
        run(i, 2, l)
        {
            int j = s[i] - '0';
            if(!t[p][j]) t[p][j] = ++ tot;
            p = t[p][j];
        }
        ed[p] = s[0];
    }
    void yyds() // ����Ĺؼ�����yyds��
    {
        // pos�Ǵ����봮��ǰ�����λ�ã�cnt�Ǹ����洢�����
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
    FILE* f = fopen("e:/��˵�Ļ�.txt", "rt"); // �洢����������ļ�
    fgets(s + 1, N, f);
//    printf("������Ҫ�������:");
//    scanf("%s", s + 1);
//    printf("%s\n", s + 1);
    len = strlen(s + 1);
    fclose(f);
    f = fopen("e:/������.txt", "rt"); // �洢��������ļ�
    while(!feof(f)) fgets(po[++ tot], 100, f); tot --;
//    puts("�����������룺");
//    run(i, 1, tot) printf("%s", po[i]);
    fclose(f);
    f = nullptr;
    run(i, 1, tot) t.add(po[i]);
    t.yyds();
    printf("%s", res + 1);
}
