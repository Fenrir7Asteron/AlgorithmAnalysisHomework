#include <chrono>
#include <iostream>
#include <iomanip>
#include "sort.h"
using namespace std;

int main()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    const int TEST_COUNT = 10000;
    const int MAX_TEST_SIZE = 50;

    for (int test_size = 1; test_size < MAX_TEST_SIZE; test_size++) {
        double total_time_quick = 0.0f;
        double total_time_insertion = 0.0f;

        for (int test_idx = 0; test_idx < TEST_COUNT; ++test_idx) {
            float test_arr[test_size];
            for (int i = 0; i < test_size; ++i) {
                test_arr[i] = test_size - i;
            }

            auto t1 = high_resolution_clock::now();
            sort(test_arr, test_arr + test_size, [](const float &a, const float &b) { return a < b; });

            auto t2 = high_resolution_clock::now();

            duration<double, std::milli> ms_double_quick = t2 - t1;

            for (int i = 0; i < test_size; ++i) {
                test_arr[i] = test_size - i;
            }

            auto t3 = high_resolution_clock::now();
            insertion_sort(test_arr, test_arr + test_size, [](const float &a, const float &b) { return a < b; });
            auto t4 = high_resolution_clock::now();

            duration<double, std::milli> ms_double_insertion = t4 - t3;

            total_time_quick += ms_double_quick.count();
            total_time_insertion += ms_double_insertion.count();
        }

        total_time_quick /= TEST_COUNT;
        total_time_insertion /= TEST_COUNT;

//        cout << std::setprecision(6);
        cout << fixed << std::setprecision(6) << total_time_quick << " " << fixed << std::setprecision(6) << total_time_insertion << endl;
    }

    return 0;
}