#include <gtest/gtest.h>
#include <algorithm/algorithm.h>
using namespace std;
using namespace alg;

//TEST(FunctionsTest, shaker_sort) {
//	std::vector<int> a{10,9,8,7,6,5,4,3,2,1};
//	std::vector<int> c{ 100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 };
//	stats b = shaker_sort(c);
//	cout << b;
//	
//}
//
//TEST(FunctionsTest, insert_sort) {
//	std::vector<int> a{ 10,9,8,7,6,5,4,3,2,1 };
//	std::vector<int> c{ 100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 };
//	stats b = insert_sort(c);
//	cout << c;
//
//}
//TEST(FunctionsTest, natural_two_way_sort_sort) {
//	std::vector<int> a{ 10,9,8,7,6,5,4,3,2,1 };
//	std::vector<int> c{ 100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 };
//	stats b = natural_two_way_sort(c);
//	cout << b;
//
//}
//TEST(FunctionTest, write_to_file) {
//    std::vector<stats> insert = get_full_stat(1);
//    write_stat_file(insert);
//
//}
TEST(FunctionTest, inv_stat) {
    std::vector<stats> stat;
    for (int i = 1; i < 11; i++) {
        std::vector<int> test = reversed_ordered_vector(i * 1000);
        stat.push_back(insert_sort(test));
    }
    std::vector<int> test = reversed_ordered_vector(25000);
    stat.push_back(insert_sort(test));
    std::vector<int> test1 = reversed_ordered_vector(50000);
    stat.push_back(insert_sort(test1));
    std::vector<int> test2 = reversed_ordered_vector(100000);
    stat.push_back(insert_sort(test2));
    write_stat_file(stat);
}