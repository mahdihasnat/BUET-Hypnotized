int cnt[1<<16];
void preprocess(){
    for(int mask=0;mask<(1<<16);mask++) {
        for(int i=0;i<16;i++) {
            if(mask&(1<<i)) cnt[mask]++;
        }
    }
}
int query(ll x){
    int ans=0,G=(1<<16)-1;
    ans+=cnt[x&G];x>>=16;
    ans+=cnt[x&G];x>>=16;
    ans+=cnt[x&G];x>>=16;
    ans+=cnt[x&G];
    return ans;
}