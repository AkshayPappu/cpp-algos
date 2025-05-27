#include <vector>
#include <iostream>

class BIT {
    private:
        std::vector<int> bit;
    public:
        BIT(int n) : bit(n) {};

        int sum(int i) {
            int res = 0;
            while (i >= 1) {
                res += bit[i];
                i -= i & -i;
            }
            return res;
        }

        void add(int i, int x) {
            while (i < bit.size()) {
                bit[i] += x;
                i += i & -i;
            }
            return;
        }
};

int main() {
    int n = 10;
    BIT bit(n + 1);  // +1 because your bit vector is size n, but uses 1-based indices

    // Add values: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    for (int i = 1; i <= n; ++i) {
        bit.add(i, i);  // add i at index i
    }

    // Query prefix sums
    std::cout << "Prefix sums:" << std::endl;
    for (int i = 1; i <= n; ++i) {
        std::cout << "sum(1.." << i << ") = " << bit.sum(i) << std::endl;
    }

    // Expected:
    // sum(1) = 1
    // sum(2) = 1 + 2 = 3
    // sum(3) = 1 + 2 + 3 = 6
    // sum(4) = 10
    // sum(5) = 15
    // sum(10) = 55
    return 0;
}