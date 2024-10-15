#include <iostream>
#include <map>
#include <vector>

using namespace std;

uint64_t quickByMod(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main()
{
    int mod = 998244353;
    int N,T;
    cin >> N >> T;
    vector<int> v(N);
    int v_sum = 0;
    int v_all_sum = 0;
    for (int i = 0; i < N; i++) {
        cin >> v[i];
        v_all_sum += v[i];
        if (i>0) {
            v_sum += v[i]-1;
        }
    }

    int F = T+1 - v_sum;
    uint64_t select_count = (T+1);
    for (int i=1; i<N ; i++) {
        select_count = (select_count * F) % mod;
        F += v[i]-1;
    }

    uint64_t answer = (((select_count) * (T+1-v_all_sum) / (T+1)) % mod);
    cout << answer % mod<< endl;
}