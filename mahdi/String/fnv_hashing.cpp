typedef unsigned long long ULL;


ULL fnv_hashing(int data[], int k)
{
    ULL h = 2166136261U;

    for(int i = 1; i <= k; ++i)
        h = (h * 16777619U) ^ data[i];

    return h;
}
