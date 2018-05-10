#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <algorithm>


template <typename T>
auto sort_impl(T &t, int = 0) -> decltype(std::declval<T>().sort(), std::declval<void>()) {

	std::cout << "v.sort();\n";
	t.sort();
}

template <typename T>
auto sort_impl(T &v, long = 0) -> decltype(std::sort(std::begin(std::declval<T>()), std::end(std::declval<T>())), std::declval<void>()) {
	using std::sort;
	using std::begin;
	using std::end;
	std::cout << "sort(v)\n";

	sort(begin(v), end(v));
}

template <typename T>
auto sort(T &t){
	sort_impl(t, 0);
}

int main(){


	std::vector<int> myvec{4,2,6,8,1,0};

	sort(myvec);
	
	std::copy(
		begin(myvec),
		end(myvec),
		std::ostream_iterator<int>(std::cout, " "));

}
