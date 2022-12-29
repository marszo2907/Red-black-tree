#include <algorithm>
#include <map>
#include <numeric>
#include <vector>

#include "RedBlackTree.hpp"

#define TEST_BEGIN_VALUE    0
#define TEST_VECTOR_SIZE    8

/*
 * test() function was provided by Jacek Klimaszewski from the West Pomeranian
 * University of Technology in Szczecin
 * source: http://jklimaszewski.zut.edu.pl/a2/
 */
void test()
{
    std::vector<int> testVector(TEST_VECTOR_SIZE);
    std::map<int, int> heights;
    std::map<int, int> rootData;

    std::iota(testVector.begin(), testVector.end(), TEST_BEGIN_VALUE);

    auto comp = [](const int &a, const int &b) {
        return a - b;
    };

    do
    {
        RedBlackTree<int> redBlackTree;

        for (auto i : testVector) {
            redBlackTree.add(i, comp);
        }

        ++heights[redBlackTree.getHeight()];
        ++rootData[redBlackTree.getRootData()];
    } while (std::next_permutation(testVector.begin(), testVector.end()));

    for (auto [height, cnt] : heights) {
        std::cout << height << ": " << cnt << std::endl;
    }
    std::cout << "*****" << std::endl;
    for (auto [data, cnt] : rootData) {
        std::cout << data << ": " << cnt << std::endl;
    }
}

int main() {
    test();

    return 0;
}
