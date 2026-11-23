#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>
#include <filesystem>
using namespace std;
using namespace std::chrono;

struct Bid {
    string bidderId;
    double amount;       // bid price
    long long timestamp; // Unix ms
    int auctionId;
};

// ---------- Utilities ----------
void printBids(const vector<Bid>& v, size_t limit = 10) {
    for (size_t i = 0; i < min(v.size(), limit); ++i)
        cout << "[" << v[i].bidderId << "] $" << v[i].amount
             << " @ " << v[i].timestamp << "\n";
    if (v.size() > limit) cout << "... (" << v.size() << " total)\n";
}
bool loadBids(const string& path, vector<Bid>& out) {
    ifstream f(path);
    if (!f) return false;
    Bid b;
    while (f >> b.bidderId >> b.amount >> b.timestamp >> b.auctionId)
        out.push_back(b);
    return true;
}
bool sosanhBids(const Bid& a, const Bid& b) {
    if (a.amount == b.amount)
        return a.timestamp < b.timestamp;
    return a.amount < b.amount;
}
void insertionSort(vector<Bid>& v) {
    for (int i = 1; i < v.size(); i++) {
        Bid key = v[i];
        int j = i - 1;
        while (j >= 0 && sosanhBids(key, v[j])) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}
void selectionSort(vector<Bid>& v) {
    for (int i = 0; i + 1 < v.size(); i++) {
        int maxIndex = i;
        for (int j = i + 1; j < v.size(); j++) {
            if (v[j].amount > v[maxIndex].amount) {
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            swap(v[i], v[maxIndex]);
        }
    }
    cout << "\nTop 3 Bidders:\n";
    for (int i = 0; i < min(3, (int)v.size()); i++) {
        cout << v[i].bidderId << " $"
             << v[i].amount << "\n";
    }
}
void interchangeSort(vector<Bid>& v) {
    long long swapCount = 0;
    for (int i = 0; i + 1 < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            if (sosanhBids(v[j], v[i])) {
                swap(v[i], v[j]);
                swapCount++;
            }
        }
    }
    cout << "Total swaps: " << swapCount << "\n";
}
bool bubbleSortEarlyStop(vector<Bid>& v) {
    int n = v.size();
    bool firstPassStable = true;
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (sosanhBids(v[j + 1], v[j])) {
                swap(v[j], v[j + 1]);
                swapped = true;
            }
        }
        if (i == 0 && swapped) {
            firstPassStable = false;
        }
        if (!swapped) {
            break;
        }
    }
    if (firstPassStable)
        cout << "STABLE\n";
    else
        cout << "UNSTABLE\n";
    return firstPassStable;
}
bool isSorted(const vector<Bid>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        if (sosanhBids(v[i], v[i - 1]))
            return false;
    }
    return true;
}
void quickSort(vector<Bid>& v, int lo, int hi) {
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    if (sosanhBids(v[mid], v[lo]))
        swap(v[lo], v[mid]);
    if (sosanhBids(v[hi], v[lo]))
        swap(v[lo], v[hi]);
    if (sosanhBids(v[hi], v[mid]))
        swap(v[mid], v[hi]);
    //dem no vè cuoi
    swap(v[mid], v[hi]);
    Bid pivot = v[hi];

    int i = lo;
    for (int j = lo; j < hi; j++) {
        if (sosanhBids(v[j], pivot)) {
            swap(v[i], v[j]);
            i++;
        }
    }
    swap(v[i], v[hi]);
    quickSort(v, lo, i - 1);
    quickSort(v, i + 1, hi);
}
void quickSortWrapper(vector<Bid>& v) {
    if (v.empty()) return;
    quickSort(v, 0, (int)v.size() - 1);
}

// ---------- Generate Large Test File ----------
void generateLargeTestFile(const string& filename, int num_records) {
    ofstream out(filename);
    if (!out) {
        cout << "Error: Cannot create file " << filename << "\n";
        return;
    }
    mt19937 gen(12345);
    uniform_real_distribution<double> dis_amount(10.0, 5000.0);
    uniform_int_distribution<long long> dis_time(1600000000, 1700000000);
    uniform_int_distribution<int> dis_auction(1, 50);
    for (int i = 0; i < num_records; i++) {
        out << "bidder_" << i << " "
            << dis_amount(gen) << " "
            << dis_time(gen) << " "
            << dis_auction(gen) << "\n";
    }
    out.close();
    cout << ">> Da tao thanh cong file: " << filename << " voi " << num_records << " records\n";
}
// ---------- Driver ----------
int main(int argc, char* argv[]) {
    filesystem::create_directories("../test_data");
    //tao du lieu
    generateLargeTestFile("../test_data/large.txt", 100000);
    vector<Bid> bids;
    if (!loadBids("../test_data/large.txt", bids)) {
        cout << "Cannot load large.txt!\n";
        return 1;
    }
    auto start = high_resolution_clock::now();
    quickSortWrapper(bids);
    auto end = high_resolution_clock::now();
    long long elapsedMs = duration_cast<milliseconds>(end - start).count();
    cout << "Runtime: " << elapsedMs << " ms\n";
    if (isSorted(bids))
        cout << "Verification: PASS (100000 records are sorted)\n";
    else
        cout << "Verification: FAIL (data is not sorted)\n";
    cout << "--- Ket qua sau khi sap xep ---\n";
    printBids(bids, 5);


    vector<Bid> smallBids;
    if (!loadBids("../test_data/small.txt", smallBids)) {
        cout << "ko mo dc tep\n";
        return 1;
    }
    cout << "\nInsertion Sort\n";
    vector<Bid> b1 = smallBids;
    insertionSort(b1);
    printBids(b1);

    cout << "\nSelection Sort\n";
    vector<Bid> b2 = smallBids;
    selectionSort(b2);

    cout << "\nInterchange Sort\n";
    vector<Bid> b3 = smallBids;
    interchangeSort(b3);
    printBids(b3);

    cout << "\nBubble Sort Early Stop\n";
    vector<Bid> b4 = smallBids;
    bubbleSortEarlyStop(b4);
    printBids(b4);
    return 0;
}
