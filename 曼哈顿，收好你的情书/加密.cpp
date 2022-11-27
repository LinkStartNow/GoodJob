#include <bits/stdc++.h>

#define run(i, a, b) for(int i = a; i <= b; i ++)

using namespace std;

const int N = 1e6 + 7;

char s[N];

char* ans[N];

int l;

typedef struct tree
{
    char old;
    int cnt;
    tree* l;
    tree* r;
    char mi[10000];
} tree, *tp;

struct cmp
{
    bool operator()(const tp &a, const tp &b)
    {
        return a->cnt > b->cnt;
    }
};

tp creat(char old, int x)
{
    tp t = (tp)malloc(sizeof(tree));
    t->cnt = x, t->l = t->r = nullptr;
    t->mi[0] = '\0', t->old = old;
    return t;
}

map<char, int> mp;

map<char, char*> key;

priority_queue<tp, vector<tp>, cmp> q;

void build()
{
    while(!q.empty())
    {
        tp l = q.top();
        q.pop();
        if(q.empty())
        {
            q.push(l);
            break;
        }
        tp r = q.top();
        q.pop();
        tp f = creat('*', l->cnt + r->cnt);
        f->l = l, f->r = r;
        q.push(f);
    }
}

void yyds(tp f)
{
    if(f->l == nullptr) return;
    tp l = f->l, r = f->r;
    strcpy(l->mi, f->mi), strcpy(r->mi, f->mi);
    int lg = strlen(f->mi);
    l->mi[lg] = '0', l->mi[lg + 1] = '\0';
    r->mi[lg] = '1', r->mi[lg + 1] = '\0';
    yyds(l), yyds(r);
}

void showmi(tp t)
{
    if(t)
    {
        tp l = t->l, r = t->r;
        if(t->old != '*')
            printf("%c:%s\n", t->old, t->mi), key[t->old] = t->mi;
        showmi(l), showmi(r);
    }
}

int main()
{
    printf("������Ҫ���ܵ����ݣ���س���:");
    gets(s + 1);
    l = strlen(s + 1);
    run(i, 1, l) mp[s[i]] ++;
    for(auto x : mp) q.push(creat(x.first, x.second));
    build();
    yyds(q.top());
    tp t = q.top();
    puts("���뱾Ϊ��");
    showmi(t);
    puts("-------------------");
    run(i, 1, l) ans[i] = key[s[i]];
    printf("���ܺ����Ϊ��");
    run(i, 1, l) printf("%s", ans[i]);
}
