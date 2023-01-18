/// O(n^2)
// A dynamic programming based function to find nth
// Catalan number
unsigned long int catalanDP(unsigned int n)
{
    // Table to store results of subproblems
    unsigned long int catalan[n+1];

    // Initialize first two values in table
    catalan[0] = catalan[1] = 1;

    // Fill entries in catalan[] using recursive formula
    for (int i=2; i<=n; i++)
    {
        catalan[i] = 0;
        for (int j=0; j<i; j++)
            catalan[i] += catalan[j] * catalan[i-j-1];
    }

    // Return last entry
    return catalan[n];
}
ll Catalan(ll n)
{
    ll factorial[2*n+1];
    factorial[0]=1;
    for(ll i=1;i<=2*n;i++)
    {
        factorial[i]= ( i* factorial[i-1])%oo;
//        DBG(i);
//        DBG(factorial[i]);
    }
    ll ans=1;
    /// catalan(n) = C(2n,n)/(n+1)== (2n)! /(( n+1)!*(n!));
    ans*=(modinverse((n+1)*factorial[n]%oo,oo)*factorial[2*n]%oo)*modinverse(factorial[n],oo)%oo;
    ans =(ans+oo)%oo;
    return ans;
}
