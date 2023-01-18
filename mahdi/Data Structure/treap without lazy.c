#include <bits/stdc++.h>
using namespace std;

#define FastIO ios::sync_with_stdio(false); cin.tie(nullptr);cout.tie(nullptr)

const int oo=INT_MAX;

typedef struct node
{
    int prior,size,val,max_val, min_val, max_ans, min_ans;
    //value in array,info of segtree,lazy update
    struct node *l,*r;
} node;
typedef node* pnode;
int sz(pnode t);
int sz(pnode t)
{
    return t?t->size:0;
}
void upd_sz(pnode t);
void upd_sz(pnode t)
{
    if(t)
        t->size=sz(t->l)+1+sz(t->r);
}
void reset(pnode t);
void reset(pnode t)
{
    if(t)
        t->min_val =  t->max_val = t->val, t->min_ans = oo, t->max_ans = 0;
}
void combine(pnode& t,pnode l,pnode r) //combine segtree ranges , caution ( t== l or t== r)
{
    if(!l || !r)
        return void(t = l?l:r);
    assert(l->max_val< r->min_val);


    int max_ans = max(l->max_ans, r->max_ans);
    int min_ans = min(l->min_ans, r->min_ans);



    t->max_ans  = max(max_ans,r->max_val - l->min_val );
    t->min_ans   = min(min_ans, r->min_val - l->max_val);

    t->min_val =l->min_val;
    t->max_val = r->max_val;

}
void operation(pnode t) //operation of segtree
{
    if(!t)
        return;
    reset(t);//node represents single element of array
    combine(t,t->l,t);
    combine(t,t,t->r);
}
void split(pnode t,pnode &l,pnode &r,int pos,int add=0) // 0-indexed
{
    if(!t)
        return void(l=r=NULL);
    int curr_pos = add + sz(t->l);
    if(curr_pos<=pos)//element at pos goes to "l"
        split(t->r,t->r,r,pos,curr_pos+1),l=t;
    else
        split(t->l,l,t->l,pos,add),r=t;
    upd_sz(t);
    operation(t);
}

void split_by_value(pnode t,pnode &l,pnode &r,int val) //use if value are ascending ordered
{
    if(!t)
        return void(l=r=NULL);
    if(t->val<=val)//element at pos goes to "l"
        split_by_value(t->r,t->r,r,val),l=t;
    else
        split_by_value(t->l,l,t->l,val),r=t;
    upd_sz(t);
    operation(t);
}


void merge(pnode &t,pnode l,pnode r) //result/left/right array
{
    if(!l || !r)
        t = l?l:r;
    else if(l->prior>r->prior)
        merge(l->r,l->r,r),t=l;
    else
        merge(r->l,l,r->l),t=r;
    upd_sz(t);
    operation(t);
}
pnode init(int val) // new node using val
{
    pnode ret = (pnode)malloc(sizeof(node));
    ret->l = ret->r = 0;
    ret->prior=rand();
    ret->size=1;
    ret->val=val;
    reset(ret);
    return ret;
}


void pr(pnode t,ll add= 0)
{
    if(t)
    {
        cout<<" ( ";
        pr(t->l, add);
        cout<<" ) ";
        ll i = sz(t->l) + add;
        cout<<" { "<<i<<" , "<<t->val<<" } ";
        cout<<" [ ";
        pr(t->r, i+1);
        cout<<" ] ";
    }
}


/*
https://www.spoj.com/problems/TREAP/
I k : Insert k into S, if k is not in S

D k : Delete k from S, if k is in S

N i j : Print min{abs(S[x] - S[y]) | i <= x, y <= j} or -1 if the range has 1 element

X i j : Print max{abs(S[x] - S[y]) | i <= x, y <= j} or -1 if the range has 1 element
*/


int32_t main()
{
    srand(time(0));

    pnode t = 0;
    int q;
    cin>>q;
    while(q--)
    {
        char c;
        cin>>c;
        if(c=='I')
        {
            int k;
            cin>>k;
            pnode l, r, mid;
            l=r = mid =0;
            split_by_value(t, l, r, k);
            split_by_value(l,  l, mid, k-1);
            if(mid == 0)
                mid = init(k);
            merge(l,l,mid);
            merge(t, l, r);
        }
        else if(c=='D')
        {
            int k;
            cin>>k;
            pnode l, r, mid;
            l=r = mid =0;
            split_by_value(t, l, r, k);
            split_by_value(l,  l, mid, k-1);

            if(mid != 0)
                free(mid ), mid = 0;
            merge(l,l,mid);
            merge(t, l, r);

        }
        else if(c=='N')
        {
            int i,j;
            cin>>i>>j;

            i= max(i,0);
            j= min(j,t->size-1);

            if(i>=j)
            {
                cout<<"-1\n";
                continue;
            }
            pnode l,r,mid;
            l=r=mid = 0;
            split(t,l,r,j);
            split(l,l,mid,i-1);
            if(mid->size>=2)
                cout<<(mid->min_ans )<<"\n";
            else
                cout<<-1<<"\n";

            merge(l,l,mid);
            merge(t,l,r);
        }
        else if(c=='X')
        {
            int i,j;
            cin>>i>>j;


            i= max(i,0);
            j= min(j,t->size-1);

            if(i>=j)
            {
                cout<<"-1\n";
                continue;
            }


            pnode l,r,mid;
            l=r=mid = 0;
            split(t,l,r,j);
            split(l,l,mid,i-1);


            if(mid->size >=2 )
                cout<<(mid->max_ans ) <<"\n";
            else
                cout<<-1<<"\n";

            merge(l,l,mid);
            merge(t,l,r);
        }
    }
    return 0;
}
