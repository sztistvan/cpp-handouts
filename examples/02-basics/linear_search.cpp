// Linear search in a hard-coded array.
// Search thread, version 1: look at the elements one by one.
#include <iostream>
#include <iterator>

int main()
{
    // Sample IDs in the order in which the samples were measured.
    const int ids[] = {4017, 2093, 7781, 1250, 9034, 3318, 5521, 6402};
    const int count = static_cast<int>(std::size(ids));

    const int targets[] = {3318, 5521, 8888};

    for (int target : targets) {
        int found_at = -1; // -1 means "not found"
        int comparisons = 0;

        for (int i = 0; i < count; ++i) {
            ++comparisons;
            if (ids[i] == target) {
                found_at = i;
                break;
            }
        }

        if (found_at >= 0) {
            std::cout << "ID " << target << " found at position " << found_at;
        } else {
            std::cout << "ID " << target << " not found";
        }
        std::cout << " after " << comparisons << " comparisons\n";
    }
    return 0;
}
