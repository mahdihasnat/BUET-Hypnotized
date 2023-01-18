#define pc(x) putchar(x);
inline void writeInt (int n)
{
    if(n<0)
    {
        pc('-');
        return writeInt(-n);
    }
    int N = n, rev, count = 0;
    rev = N;
    if (N == 0)
    {
        pc('0');
        return ;
    }
    while ((rev % 10) == 0)
    {
        count++;    //obtain the count of the number of 0s
        rev /= 10;
    }
    rev = 0;
    while (N != 0)
    {
        rev = (rev<<3) + (rev<<1) + N % 10;    //store reverse of N in rev
        N /= 10;
    }
    while (rev != 0)
    {
        pc(rev % 10 + '0');
        rev /= 10;
    }
    while (count--)
        pc('0');
}
inline void writeLongLong (long long  n)
{
    if(n<0LL)
    {
        pc('-');
        return writeLongLong(-n);
    }
    long long N = n, rev, count = 0;
    rev = N;
    if (N == 0LL)
    {
        pc('0');
        return ;
    }
    while ((rev % 10LL) == 0LL)
    {
        count++;    //obtain the count of the number of 0s
        rev /= 10LL;
    }
    rev = 0LL;
    while (N != 0LL)
    {
        rev = (rev<<3LL) + (rev<<1LL) + N % 10LL;    //store reverse of N in rev
        N /= 10LL;
    }
    while (rev != 0LL)
    {
        pc((rev % 10LL) + '0');
        rev /= 10LL;
    }
    while (count--)
        pc('0');
}
inline void writeString(char *s)
{
    while(*s) { pc(*s);s++;}
}

inline int nextInt() {
    int n = 0;
    char c = getchar();
    while (!('0' <= c && c <= '9')) {
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        n = n * 10 + c - '0';
        c = getchar();
    }
    return n;
}
inline long long nextLongLong() {
    long long n = 0LL;
    char c = getchar();
    while (!('0' <= c && c <= '9')) {
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        n = n * 10LL + c - '0';
        c = getchar();
    }
    return n;
}

inline void nextString(char *s)
{
    int i=0;
    while(1)
    {
        int ch =getchar();
        if((ch==' '|| ch == '\n') && i==0) continue;
        if(ch==' '|| ch==EOF || ch == '\n') break;
        s[i]=ch;
        s[++i]=0;
    }
}

