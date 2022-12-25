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

    for (auto it = b.iterator(); it.hasNext(); it.next()) {
        std::cout << it.get() << " ";
    }

    cout << endl;

    for (auto it = b.reverseIteratorBegin(), end = b.reverseIteratorEnd(); it < end; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    auto c = std::move(b);

    b = b;

    b.insert(1234);
    for (auto it = b.reverseIteratorBegin(), end = b.reverseIteratorEnd(); it < end; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    for (auto it = c.reverseIteratorBegin(), end = c.reverseIteratorEnd(); it < end; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}
