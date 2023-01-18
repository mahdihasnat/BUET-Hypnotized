const int SIGMA = 27; /// 1+ total distonct char , 0 te suffix link
const int MAXNODE= 1e5;/// maximum node


int next[MAXNODE][SIGMA];
int freq[MAXNODE];
void init()
{
    memset(next,-1,sizoef next);
    memset(freq,0,sizoef freq);
}
int Insert(char s[],int  totalnode)
{
    int now=0;
    for(int i=0; s[i]; i++)
    {
        char ch = s[i]-'a'+1;
        if(next[now][ch]!=-1)
            now= next[now][ch];
        else
            now = next[now][ch]=++totalnode;
    }
}
void bild_Suffix_link()
{
    queue < int > q;
    int a, cur;
    next[0][0] = -1;
    q.push(0);
    while(!q.empty())
    {
        a = q.front();
        q.pop();
        for(int i = 1; i<SIGMA; i++)
        {
            if(next[a][i]==-1)
                continue;
            q.push(next[a][i]);
            cur = next[a][0];
            while(cur!=-1 && next[cur][i]==-1)
                cur = next[cur][0];
            if(cur==-1)
                cur = 0;
            else
                cur = next[cur][i];
            next[next[a][i]][0] = cur;
        }
    }
}

void match(char * text)
{
    int now=0;
    for(int i = 0; text[i]; i++) {
		char c = text[i]-'a'+1 ;
		while(now!=-1 && next[now][c]==-1) /// test this line
            now = next[now][0];
        if(now==-1) now=0;
        else
		now= next[now][c];
		freq[now]++;
	}
}

