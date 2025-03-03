
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 40;

struct Matrix {
    vector<vector<ll>> mat;
    int size;

    Matrix(int n) : size(n) {
        mat.assign(n, vector<ll>(n, 0));
    }

    static Matrix identity(int n) {
        Matrix I(n);
        for (int i = 0; i < n; i++)
            I.mat[i][i] = 1;
        return I;
    }

    Matrix operator*(const Matrix &other) const {
        int n = size;
        Matrix result(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    result.mat[i][j] = (result.mat[i][j] + mat[i][k] * other.mat[k][j]) % 1000000007;
                }
            }
        }
        return result;
    }

    Matrix power(ll exp, ll mod) const {
        Matrix result = Matrix::identity(size);
        Matrix base = *this;

        while (exp > 0) {
            if (exp % 2 == 1)
                result = result * base;
            base = base * base;
            exp /= 2;
        }

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                result.mat[i][j] %= mod;

        return result;
    }
};

void solve() {
    int N;
    cin >> N;

    vector<ll> coeff(N + 1);
    for (int i = 0; i <= N; i++)
        cin >> coeff[i];

    vector<ll> initial(N);
    for (int i = 0; i < N; i++)
        cin >> initial[i];

    int Q;
    cin >> Q;
    
    while (Q--) {
        ll T, M;
        cin >> T >> M;

        if (T < N) {
            cout << (initial[T] % M) << "\n";
            continue;
        }

        Matrix trans(N);
        
        for (int i = 0; i < N; i++)
            trans.mat[0][i] = coeff[i + 1] % M;

        for (int i = 1; i < N; i++)
            trans.mat[i][i - 1] = 1;

        trans = trans.power(T - N + 1, M);

        ll result = coeff[0] % M;
        for (int i = 0; i < N; i++)
            result = (result + trans.mat[0][i] * initial[i]) % M;

        cout << result << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}






/*

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 40;

struct Matrix {
    vector<vector<ll>> mat;
    int size;

    Matrix(int n) : size(n) {
        mat.assign(n, vector<ll>(n, 0));
    }

    static Matrix identity(int n) {
        Matrix I(n);
        for (int i = 0; i < n; i++)
            I.mat[i][i] = 1;
        return I;
    }

    Matrix operator*(const Matrix &other) const {
        int n = size;
        Matrix result(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    result.mat[i][j] = (result.mat[i][j] + mat[i][k] * other.mat[k][j]) % 1000000007; // Modulo for safety
                }
            }
        }
        return result;
    }

    Matrix power(ll exp, ll mod) const {
        Matrix result = Matrix::identity(size);
        Matrix base = *this;

        while (exp > 0) {
            if (exp % 2 == 1)
                result = result * base;
            base = base * base;
            exp /= 2;
        }

        for (int i = 0; i < size; i++)  // Apply modulo manually
            for (int j = 0; j < size; j++)
                result.mat[i][j] %= mod;

        return result;
    }
};

void solve() {
    int N;
    cin >> N;

    vector<ll> coeff(N + 1);
    for (int i = 0; i <= N; i++)
        cin >> coeff[i];

    vector<ll> initial(N);
    for (int i = 0; i < N; i++)
        cin >> initial[i];

    int Q;
    cin >> Q;
    
    while (Q--) {
        ll T, M;
        cin >> T >> M;

        if (T < N) {
            cout << (initial[T] % M) << "\n";
            continue;
        }

        Matrix trans(N + 1);
        
        for (int i = 0; i < N; i++)
            trans.mat[0][i] = coeff[i + 1] % M;
        trans.mat[0][N] = coeff[0] % M;

        for (int i = 1; i < N; i++)
            trans.mat[i][i - 1] = 1;
        trans.mat[N][N] = 1;

        vector<ll> state(N + 1);
        for (int i = 0; i < N; i++)
            state[i] = initial[i] % M;
        state[N] = 1;

        trans = trans.power(T - N + 1, M);

        ll result = 0;
        for (int i = 0; i <= N; i++)
            result = (result + trans.mat[0][i] * state[i]) % M;

        cout << result << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
*/
