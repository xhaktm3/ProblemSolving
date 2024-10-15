#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<int64_t> v, acc, m, memo, memo2;
int N,K;
int64_t dp(int);
int64_t M(int);

int64_t dp(int pos) {
    if (pos < K-1) {
        return 0;
    }
    if (memo[pos] != -1) {
        return memo[pos];
    }

    memo[pos] = max(dp(pos-1),M(pos)+acc[pos]);
    return memo[pos];
}

int64_t M(int pos) {
    if (pos<K) {
        return 0;
    }
    if (memo2[pos] != -1) {
        return memo2[pos];
    }

    memo2[pos] = max(M(pos-1),dp(pos-K)-acc[pos-K]);
    return memo2[pos];
}

int main()
{
    iostream::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> K;
    v.resize(N+2*K-2);
    acc.resize(N+2*K-2);
    m.resize(N+2*K-2);
    memo.assign(N+2*K-2, -1);
    memo2.assign(N+2*K-2, -1);

    for (int i = 0; i < K-1; i++) {
        v[i] = 0;
    }
    for (int i=K-1;i<N+K-1;i++) {
        cin >> v[i];
    }
    for (int i=N+K-1;i<N+2*K-2;i++) {
        v[i] = 0;
    }
    acc[0] = v[0];
    for (int i=1; i<N+2*K-2; i++) {
        acc[i] = acc[i-1] + v[i];
    }
    cout << dp(N+2*K-3) << "\n";
    return 0;
}