#pragma once
#include<iostream>
#include <random>
#include <fstream>

using namespace std; 
namespace alg {

	struct stats {
		double comparison_count = 0;
		double copy_count = 0;
		stats& operator+=(const stats& rhs) {
			comparison_count += rhs.comparison_count;
			copy_count += rhs.copy_count;
			return *this;
		}
		stats& operator/(const int rhs) {
			comparison_count /= rhs;
			copy_count /= rhs;
			return *this;
		}
	};

	std::vector<int> random(int a, int b, int n) {
		std::vector<int> res;
		std::random_device random_device;
		std::mt19937 generator(random_device());
		std::uniform_int_distribution<> distribution(a, b);
		for (int i = 0; i < n; i++) {
			int x = distribution(generator);
			res.push_back(x);
		}
		return res;
	}
	std::vector<int> random_seed(int a, int b, int n, int seed) {
		std::vector<int> res;
		/*std::random_device random_device;*/
		std::mt19937 generator(seed);
		std::uniform_int_distribution<> distribution(a, b);
		for (int i = 0; i < n; i++) {
			int x = distribution(generator);
			res.push_back(x);
		}
		return res;
	}
	std::vector<int> ordered_vector(int n) {
		std::vector<int> res;
		for (int i = 0; i < n; i++) {
			res.push_back(i);
		}
		return res;
	}
	std::vector<int> reversed_ordered_vector(int n) {
		std::vector<int> res;
		for (int i = n; i > 0; i--) {
			res.push_back(i);
		}
		return res;
	}

	stats shaker_sort(vector<int>& list) {
		stats cur_stat;
		int control = static_cast<int>(list.size() - 1);
		int left = 0, right = control;
		do {
			for (int i = left; i < right; i++) {
				cur_stat.comparison_count++;
				if (list[i] > list[i + 1]) {
					cur_stat.copy_count++;
					std::swap(list[i], list[i + 1]);
					control = i;
				}
			}
			right = control;
			for (int i = right; i > left; i--) {
				cur_stat.comparison_count++;
				if (list[i] < list[i - 1]) {
					cur_stat.copy_count++;
					std::swap(list[i], list[i - 1]);
					control = i;
				}
			}
			left = control;
		} while (left < right);
		return cur_stat;
	}

	stats insert_sort(vector<int>& list) {
		stats cur_stat;
		for (int i = 1; i < list.size(); i++) {
			for (int j = i; j > 0 && list[j - 1] > list[j]; j--) {
				cur_stat.comparison_count++;
				cur_stat.copy_count++;
				std::swap(list[j - 1], list[j]);
			}
			cur_stat.comparison_count++;
		}
		return cur_stat;
	}
	std::vector<int> merge_ascending(std::vector<int> left, std::vector<int> right, stats& cur_stat) {
		std::vector<int> result;

		int i = 0, j = 0;

		if (left.size() > right.size() && left.back() == right.back())
			left.pop_back();
		else if (right.size() > left.size() && left.back() == right.back())
			right.pop_back();

		while (i < left.size() && j < right.size()) {
			cur_stat.comparison_count++;
			int item = left[i] <= right[j] ? left[i++] : right[j++];
			if (!result.empty() && item == result.back())
				continue;

			result.push_back(item);
			cur_stat.copy_count++;
		}

		cur_stat.copy_count += left.size() - i;
		cur_stat.copy_count += right.size() - j;

		result.insert(result.end(), left.begin() + i, left.end());
		result.insert(result.end(), right.begin() + j, right.end());

		return result;
	}

	std::vector<int> merge_descending(const std::vector<int>& left, const std::vector<int>& right, stats& cur_stat) {
		std::vector<int> result = merge_ascending(left, right, cur_stat);

		for (int i = 0; i < result.size() / 2; i++) {
			int temp = result[i];
			result[i] = result[result.size() - i - 1];
			result[result.size() - i - 1] = temp;
			cur_stat.copy_count += 2;
		}

		return result;
	}

	stats natural_two_way_sort(std::vector<int>& list) {
		stats cur_stat;

		if (list.size() < 2)
			return cur_stat;

		while (true) {
			std::vector<std::vector<int>> series;

			int left = -1,
				right = list.size();

			while (left < right) {
				std::vector<int> one_series;

				do {
					left++;
					one_series.push_back(list[left]);
					cur_stat.copy_count++;
					if (left < list.size() - 1 && left + 1 < right) {
						cur_stat.comparison_count++;
					}
				} while (left < list.size() - 1 && left + 1 < right && list[left] <= list[left + 1]);

				series.push_back(one_series);

				one_series.clear();

				do {
					right--;
					one_series.push_back(list[right]);
					cur_stat.copy_count++;
					if (right > 1 && left - 1 < right) {
						cur_stat.comparison_count++;
					}
				} while (right > 0 && left - 1 < right && list[right - 1] >= list[right]);

				series.push_back(one_series);
			}

			if (series.size() == 2 && series[1].size() == 1)
				break;

			std::vector<std::vector<int>> result_left;
			std::vector<std::vector<int>> result_right;

			int current_series = 0;

			while (current_series < series.size() - 1) {
				result_left.push_back(merge_ascending(series[current_series], series[current_series + 1], cur_stat));
				current_series += 2;

				if (current_series >= series.size() - 1)
					break;

				result_right.insert(result_right.begin(), merge_descending(series[current_series], series[current_series + 1], cur_stat));
				current_series += 2;
			}

			list.clear();
			for (auto& s : result_left) {
				list.insert(list.end(), s.begin(), s.end());
				cur_stat.copy_count += s.size();
			}
			for (auto& s : result_right)
			{
				list.insert(list.end(), s.begin(), s.end());
				cur_stat.copy_count += s.size();
			}
		}

		return cur_stat;
	}

	void merge(std::vector<int>& list, const size_t left_start, const size_t left_end, const size_t right_end, const bool ascending) {
		std::vector<int> temp(right_end - left_start);
		size_t i = left_start, j = left_end, k = 0;

		while (i < left_end && j < right_end) {
			if ((ascending && list[i] <= list[j]) || (!ascending && list[i] > list[j])) {
				temp[k++] = list[i++];
			}
			else {
				temp[k++] = list[j++];
			}
		}

		while (i < left_end) temp[k++] = list[i++];
		while (j < right_end) temp[k++] = list[j++];

		std::ranges::copy(temp, list.begin() + left_start);
	}

	std::vector<int> natural_two_way_sorts(std::vector<int>& list) {
		if (list.size() < 2)
			return list;

		bool sorted = false;
		while (!sorted) {
			sorted = true;
			size_t start = 0;
			bool ascending = true;

			for (size_t i = 0; i < list.size() - 1; ++i) {
				if ((ascending && list[i] > list[i + 1]) || (!ascending && list[i] < list[i + 1])) {
					merge(list, start, i + 1, std::min(i + 1 + (i - start + 1), list.size()), ascending);
					start = i + 1;
					ascending = !ascending;
					sorted = false;
				}
			}

			if (start < list.size()) {
				merge(list, start, list.size(), list.size(), ascending);
			}
		}

		return list;
	}
	stats get_stat(int vect_len, int trial_count, int sort_choice) {
		stats stat;
		for (int i = 0; i < trial_count; i++) {
			std::vector<int> test = random(-1000, 1000, vect_len);
			cout << "iteration: " << i << endl;
			switch (sort_choice) {
			case 1:
				stat += insert_sort(test);
				break;
			case 2:
				stat += shaker_sort(test);
				break;
			case 3:
				stat += natural_two_way_sort(test);
				break;
			}
		}
		stat = stat / trial_count;
		return stat;
	}

	vector<stats> get_full_stat(int sort_choice) {
		vector<stats> stat;
		for (int i = 1; i < 11; i++) {
			stat.push_back(get_stat(i * 1000, 100, sort_choice));
			cout << "len: " << i*1000 << endl;
		}
		cout << "len: " << 25000 << endl;
		stat.push_back(get_stat(25000, 100, sort_choice));
		cout << "len: " << 50000 << endl;
		stat.push_back(get_stat(50000, 100, sort_choice));
		cout << "len: " << 100000 << endl;
		stat.push_back(get_stat(100000, 100, sort_choice));
		return stat;
	}
	void write_stat_file(vector<stats> stat) {
		ofstream fout;
		fout.open("C:\\Users\\Сергей\\Desktop\\masha\\reversed_insert_sort_stat.txt");
		for (int i = 0; i < stat.size(); i++) {
			fout << stat[i].comparison_count << " " << stat[i].copy_count << endl;
		}
		fout.close();
		return;
	}

	template<typename T>
	std::ostream& operator << (std::ostream& os, const std::vector<T> a)
	{
		os << "{ ";
		for (int i = 0; i < a.size(); i++) {
			if (i < a.size() - 1)
				os << a[i] << ", ";
			else {
				os << a[i] << " }";
			}
		}
		return os;
	}

	std::ostream& operator <<(std::ostream& os, const stats a) {
		os << "compasion count: " << a.comparison_count<<" " << "copy count: " << a.copy_count;
		return os;
	}
}