// Classification with more than two classes: per-class precision, recall and F1, and two ways to average them.
// Classification thread, version 3. The predictions are invented.
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

double ratio(double numerator, double denominator)
{
    if (denominator == 0.0) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return numerator / denominator;
}

// Add `count` samples with the given true class and predicted class.
void add(std::vector<std::string>& actual, std::vector<std::string>& predicted, const std::string& true_class,
         const std::string& predicted_class, int count)
{
    for (int i = 0; i < count; ++i) {
        actual.push_back(true_class);
        predicted.push_back(predicted_class);
    }
}

void print_value(double value)
{
    if (std::isnan(value)) {
        std::cout << std::setw(10) << "n/a";
    } else {
        std::cout << std::setw(10) << value;
    }
}

int main()
{
    std::vector<std::string> actual;
    std::vector<std::string> predicted;
    //            true class   predicted   how many
    add(actual, predicted, "healthy", "healthy", 17);
    add(actual, predicted, "healthy", "benign", 1);
    add(actual, predicted, "benign", "healthy", 3);
    add(actual, predicted, "benign", "benign", 4);
    add(actual, predicted, "benign", "malignant", 1);
    add(actual, predicted, "malignant", "benign", 2);
    add(actual, predicted, "malignant", "malignant", 2);

    // For each class: how many true members (support), true positives, false positives, false negatives.
    std::map<std::string, int> support;
    std::map<std::string, int> tp;
    std::map<std::string, int> fp;
    std::map<std::string, int> fn;
    for (std::size_t i = 0; i < actual.size(); ++i) {
        ++support[actual[i]];
        if (actual[i] == predicted[i]) {
            ++tp[actual[i]];
        } else {
            ++fp[predicted[i]]; // flagged as this class, but wrongly
            ++fn[actual[i]];    // belongs to this class, but was missed
        }
    }

    const std::vector<std::string> classes = {"healthy", "benign", "malignant"};
    std::cout << std::fixed << std::setprecision(3);
    std::cout << std::left << std::setw(11) << "class" << std::right << std::setw(8) << "support" << std::setw(10)
              << "precision" << std::setw(10) << "recall" << std::setw(10) << "F1" << '\n';

    double f1_sum = 0.0;
    int total_tp = 0;
    int total_fp = 0;
    int total_fn = 0;
    for (const std::string& name : classes) {
        // operator[] on a map creates a missing key with the value 0, which is exactly what we want here.
        const double precision = ratio(tp[name], tp[name] + fp[name]);
        const double recall = ratio(tp[name], tp[name] + fn[name]);
        const double f1 = ratio(2.0 * tp[name], 2.0 * tp[name] + fp[name] + fn[name]);
        std::cout << std::left << std::setw(11) << name << std::right << std::setw(8) << support[name];
        print_value(precision);
        print_value(recall);
        print_value(f1);
        std::cout << '\n';
        f1_sum += f1;
        total_tp += tp[name];
        total_fp += fp[name];
        total_fn += fn[name];
    }

    const double macro_f1 = f1_sum / static_cast<double>(classes.size());
    const double micro_f1 = ratio(2.0 * total_tp, 2.0 * total_tp + total_fp + total_fn);
    std::cout << "\nmacro-averaged F1 (mean of the class F1 values): " << macro_f1 << '\n';
    std::cout << "micro-averaged F1 (all counts pooled):           " << micro_f1 << '\n';
    std::cout << "accuracy (" << total_tp << " of " << actual.size() << " correct):                      "
              << ratio(total_tp, static_cast<double>(actual.size())) << '\n';
    return 0;
}
