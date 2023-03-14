#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::make_pair;
using std::pair;
using std::swap;
using std::vector;

class HeapBuilder
{
private:
    vector<int> data_;
    vector<pair<int, int>> swaps_;
    // prints the amount of swaps and each swap that took place
    void WriteResponse() const
    {
        cout << "\n"
             << "Output:" << std::endl
             << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i)
        {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }
    // reads user data and stores each value into a integer vector
    void ReadData()
    {
        cout << "Input:" << std::endl;
        int n;
        cin >> n;
        data_.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> data_[i];
    }
    // start from the last non-leaf node and sift up
    void GenerateSwaps()
    {
        swaps_.clear();
        for (int i = data_.size(); i >= 0; i--)
        {
            heapify(i);
        }
    }
    // heapify a subtree with i as the parent
    void heapify(int i)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i; // this becomes the current parent

        // If left child is smaller than parent
        if (left < data_.size() && data_[left] < data_[smallest])
        {
            smallest = left;
        }
        // If right child is smaller than parent
        if (right < data_.size() && data_[right] < data_[smallest])
        {
            smallest = right;
        }
        // If smallest is not parent then swap the parent with smallest and record the pair
        if (smallest != i)
        {
            swap(data_[i], data_[smallest]);
            swaps_.push_back(make_pair(i, smallest));
            // heapify the subtree for the smallest value
            heapify(smallest);
        }
    }

public:
    void Solve()
    {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
