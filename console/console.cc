#include<iostream>
#include<algorithm/algorithm.h>

using namespace std;
using namespace alg;

int main(){
	vector<int> test = random(-1000, 1000, 1000);
	stats a = natural_two_way_sort(test);
	cout << a;
	return 0;
}