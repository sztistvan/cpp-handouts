// Classification metrics from a file of true labels and classifier scores.
// Classification thread, version 2: precision, recall, specificity and F1.
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

std::vector<std::string> split(const std::string& line, char delimiter)
{
    std::vector<std::string> fields;
    std::istringstream stream(line);
    std::string field;
    while (std::getline(stream, field, delimiter)) {
        fields.push_back(field);
    }
    return fields;
}

bool parse_double(const std::string& text, double& value)
{
    std::istringstream stream(text);
    stream >> value;
    if (stream.fail()) {
        return false;
    }
    stream >> std::ws;
    return stream.eof();
}

// File format: sample,actual,score  (actual is 1 or 0, score is the classifier's output between 0 and 1)
bool load_predictions(const std::string& path, std::vector<int>& actual, std::vector<double>& score)
{
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Cannot open " << path << '\n';
        return false;
    }
    std::string line;
    int line_number = 0;
    while (std::getline(in, line)) {
        ++line_number;
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line_number == 1 || line.empty()) {
            continue;
        }
        const std::vector<std::string> fields = split(line, ',');
        double label = 0.0;
        double s = 0.0;
        if (fields.size() != 3 || !parse_double(fields[1], label) || !parse_double(fields[2], s)) {
            std::cerr << "Bad line " << line_number << ": " << line << '\n';
            return false;
        }
        actual.push_back(static_cast<int>(label));
        score.push_back(s);
    }
    return true;
}

// A score at or above the threshold counts as a positive prediction.
void count_confusion(const std::vector<int>& actual, const std::vector<double>& score, double threshold, int& tp,
                     int& tn, int& fp, int& fn)
{
    tp = 0;
    tn = 0;
    fp = 0;
    fn = 0;
    for (std::size_t i = 0; i < actual.size(); ++i) {
        const bool predicted_positive = score[i] >= threshold;
        if (actual[i] == 1 && predicted_positive) {
            ++tp;
        } else if (actual[i] == 0 && !predicted_positive) {
            ++tn;
        } else if (actual[i] == 0 && predicted_positive) {
            ++fp;
        } else {
            ++fn;
        }
    }
}

// numerator / denominator, or NaN if the denominator is 0 (the ratio is then undefined).
double ratio(double numerator, double denominator)
{
    if (denominator == 0.0) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return numerator / denominator;
}

void print_value(double value)
{
    if (std::isnan(value)) {
        std::cout << std::setw(9) << "n/a";
    } else {
        std::cout << std::setw(9) << value;
    }
}

int main()
{
    std::vector<int> actual;
    std::vector<double> score;
    if (!load_predictions(std::string(DATA_DIR) + "/predictions.csv", actual, score)) {
        return 1;
    }

    int positives = 0;
    for (int a : actual) {
        positives += a;
    }
    std::cout << "predictions.csv: " << actual.size() << " samples, " << positives << " positive, "
              << actual.size() - static_cast<std::size_t>(positives) << " negative\n\n";

    std::cout << std::fixed << std::setprecision(3);

    // One threshold in detail.
    int tp = 0, tn = 0, fp = 0, fn = 0;
    count_confusion(actual, score, 0.5, tp, tn, fp, fn);
    std::cout << "Threshold 0.5\n";
    std::cout << "              predicted 1   predicted 0\n";
    std::cout << "  actual 1    " << std::setw(11) << tp << "   " << std::setw(11) << fn << '\n';
    std::cout << "  actual 0    " << std::setw(11) << fp << "   " << std::setw(11) << tn << '\n';
    std::cout << "  accuracy    = " << ratio(tp + tn, tp + tn + fp + fn) << '\n';
    std::cout << "  precision   = " << ratio(tp, tp + fp) << "   TP / (TP + FP)\n";
    std::cout << "  recall      = " << ratio(tp, tp + fn) << "   TP / (TP + FN), also called sensitivity\n";
    std::cout << "  specificity = " << ratio(tn, tn + fp) << "   TN / (TN + FP)\n";
    std::cout << "  F1          = " << ratio(2.0 * tp, 2.0 * tp + fp + fn) << "   2 TP / (2 TP + FP + FN)\n";

    // The same measures for several thresholds.
    std::cout << "\nThreshold   TP   FP   FN   TN" << std::setw(11) << "precision" << std::setw(9) << "recall"
              << std::setw(9) << "F1" << '\n';
    const double thresholds[] = {0.3, 0.5, 0.7, 0.95};
    for (double threshold : thresholds) {
        count_confusion(actual, score, threshold, tp, tn, fp, fn);
        std::cout << std::setw(9) << threshold << std::setw(5) << tp << std::setw(5) << fp << std::setw(5) << fn
                  << std::setw(5) << tn;
        print_value(ratio(tp, tp + fp));
        print_value(ratio(tp, tp + fn));
        print_value(ratio(2.0 * tp, 2.0 * tp + fp + fn));
        std::cout << '\n';
    }
    return 0;
}
