#include "Array.h"

using namespace std;

int main() {
    Array<int> a = Array<int>();
    a.insert(5);
    cout << a[0] << endl;
    a[0] = 3;
    cout << a[0] << endl;

    Array<int> b = Array<int>(a);
    b.insert(10);
    b.insert(2);
    b.insert(0, 1);

    for (auto element : b) {
        cout << element << " ";
    }
    cout << endl;

    for (auto it = b.cbegin(), end = b.cend(); it != end; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    for (auto it = b.reverseIterator(), begin = b.begin(); it >= begin; --it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}
