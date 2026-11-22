// Counting true/false positives and negatives, and why accuracy alone can mislead.
// Classification thread, version 1: two vectors in, four counts out.
// Labels: 1 = positive (for example "diseased"), 0 = negative ("healthy"). The data are invented.
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

// Compare the true labels with the predictions and count the four outcomes.
// (Four reference parameters are clumsy: handout 9 replaces them by a ConfusionMatrix class.)
void count_confusion(const std::vector<int>& actual, const std::vector<int>& predicted, int& tp, int& tn, int& fp,
                     int& fn)
{
    tp = 0;
    tn = 0;
    fp = 0;
    fn = 0;
    for (std::size_t i = 0; i < actual.size(); ++i) {
        if (actual[i] == 1 && predicted[i] == 1) {
            ++tp; // true positive: sick, and found
        } else if (actual[i] == 0 && predicted[i] == 0) {
            ++tn; // true negative: healthy, and cleared
        } else if (actual[i] == 0 && predicted[i] == 1) {
            ++fp; // false positive: healthy, but flagged
        } else {
            ++fn; // false negative: sick, but missed
        }
    }
}

void report(const std::vector<int>& actual, const std::vector<int>& predicted)
{
    int tp = 0, tn = 0, fp = 0, fn = 0;
    count_confusion(actual, predicted, tp, tn, fp, fn);

    std::cout << "                  predicted 1   predicted 0\n";
    std::cout << "  actual 1        " << std::setw(8) << tp << "      " << std::setw(8) << fn << "      (TP, FN)\n";
    std::cout << "  actual 0        " << std::setw(8) << fp << "      " << std::setw(8) << tn << "      (FP, TN)\n";

    const double accuracy = static_cast<double>(tp + tn) / static_cast<double>(actual.size());
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  accuracy = (TP + TN) / all = " << accuracy << '\n';
}

int main()
{
    // 20 samples: 8 sick (first eight), 12 healthy.
    const std::vector<int> actual = {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    const std::vector<int> predicted = {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};

    std::cout << "A test on 20 samples:\n";
    report(actual, predicted);

    // 100 samples, only 5 sick. A "classifier" that always answers "healthy".
    std::vector<int> actual_rare(100, 0);
    for (std::size_t i = 0; i < 5; ++i) {
        actual_rare[i] = 1;
    }
    const std::vector<int> always_negative(100, 0);

    std::cout << "\nAlways answering 'healthy', 100 samples with 5 sick:\n";
    report(actual_rare, always_negative);
    return 0;
}
