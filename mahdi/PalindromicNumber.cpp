struct PalindromicNumber
{
    string s;
    int parity;
    PalindromicNumber(const string &ss)
    {
        parity=ss.size()%2;
        for(int i=(ss.size()-1)/2;i>=0;i--)
            s.push_back(ss[i]);
    }

    PalindromicNumber Next()
    {
        PalindromicNumber p=*this;
        int vagses=1;
        for(int i=0;i<p.s.size();i++)
        {
            int zog= p.s[i]-'0'+vagses;
            p.s[i]=zog%10+'0';
            vagses=zog/10;
            if(!vagses) return p;
        }

        if(vagses)
        {
            p.parity=!p.parity;
            if(p.parity)
            {

                p.s.push_back('1');
            }
            else
            {

                for(int i=0;i<s.size();i++)
                    p.s[i]='0';
                p.s[s.size()-1]='1';
            }
        }
        return p;
    }
    PalindromicNumber(const PalindromicNumber  &p)
    {
        s=p.s;
        parity=p.parity;
    }
    string getString()
    {
        string ret=s;
        reverse(ret.begin(),ret.end());
        if(!parity)
        {
            ret.push_back(s[0]);
        }
        for(int i=1;i<s.size();i++)
            ret.push_back(s[i]);
        return ret;
    }

    friend ostream &operator<<(ostream &os,const PalindromicNumber &p)
    {
        for(int i=p.s.size()-1;i>=0;i--)
            os<<p.s[i];
        if(!p.parity) os<<p.s[0];
        for(int i=1;i<p.s.size();i++)
            os<<p.s[i];
        return os;
    }


};
