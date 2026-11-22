// Searching as functions. Search thread, version 2: linear search and binary search.
// Both return the position of the target (or -1) and report how many steps they needed.
#include <iomanip>
#include <iostream>
#include <iterator>

// Look at the elements one by one.
int linear_find(const int values[], int count, int target, int& comparisons)
{
    comparisons = 0;
    for (int i = 0; i < count; ++i) {
        ++comparisons;
        if (values[i] == target) {
            return i;
        }
    }
    return -1;
}

// Binary search: the values MUST be sorted in ascending order.
// Each step looks at the middle of the remaining range and throws away the wrong half.
// (We count one step per look at the middle, although the code asks two questions.)
int binary_find(const int values[], int count, int target, int& comparisons, bool verbose = false)
{
    comparisons = 0;
    int low = 0;
    int high = count - 1;
    while (low <= high) {
        const int mid = low + (high - low) / 2; // not (low + high) / 2: see the handout
        ++comparisons;
        if (verbose) {
            std::cout << "  low=" << low << " high=" << high << " mid=" << mid << " value=" << values[mid] << '\n';
        }
        if (values[mid] == target) {
            return mid;
        }
        if (values[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main()
{
    // The IDs of handout 2, now sorted.
    const int ids[] = {1250, 2093, 3318, 4017, 5521, 6402, 7781, 9034};
    const int count = static_cast<int>(std::size(ids));

    int steps = 0;
    std::cout << "Binary search for 5521:\n";
    int position = binary_find(ids, count, 5521, steps, true);
    std::cout << "  -> position " << position << " after " << steps << " steps\n";

    std::cout << "Binary search for 8888 (not in the list):\n";
    position = binary_find(ids, count, 8888, steps, true);
    std::cout << "  -> position " << position << " after " << steps << " steps\n\n";

    // A longer sorted list: 1000 values 3, 10, 17, ... (7 * i + 3).
    int values[1000];
    for (int i = 0; i < 1000; ++i) {
        values[i] = 7 * i + 3;
    }

    const int targets[] = {3, 3503, 6996, 5000};
    const char* names[] = {"first element", "middle element", "last element", "not in the list"};

    std::cout << std::setw(18) << "target" << std::setw(10) << "linear" << std::setw(10) << "binary" << '\n';
    for (int k = 0; k < 4; ++k) {
        int linear_steps = 0;
        int binary_steps = 0;
        const int p1 = linear_find(values, 1000, targets[k], linear_steps);
        const int p2 = binary_find(values, 1000, targets[k], binary_steps);
        std::cout << std::setw(18) << names[k] << std::setw(10) << linear_steps << std::setw(10) << binary_steps
                  << (p1 == p2 ? "" : "   MISMATCH") << '\n';
    }
    return 0;
}
