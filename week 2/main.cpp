#include <iostream>
#include<vector>
#include <deque>
#include <list>
#include <array>
#include <forward_list>
#include <chrono>
#include"timer.hpp"

int main() {
    Timer<std::chrono::microseconds> t(false);
	{

		std::vector <int> v;
		for (auto i = 1; i < 1000000; ++i)
		{
			v.push_back(1000000-i);
		}
		std::sort(v.begin(), v.end());

	}
	{

		std::array <int, 1000000> a;
		for (auto i = 1; i < 1000000; ++i) {
            a[i] = 1000000-i;
        }
		std::sort(a.begin(), a.end());

	}
	{

		std::deque <int> d;
		for (auto i = 1; i < 1000000; ++i)
		{
			d.push_back(1000000 - i);
		}
		std::sort(d.begin(), d.end());

	}
	{

		std::list <int> l;
		for (auto i = 1; i < 1000000; ++i)
		{
			l.push_back(1000000 - i);
		}
		l.sort();

	}
	{
        t.start();
		std::forward_list <int> fl;
		for (auto i = 1; i < 1000000; ++i)
		{
			fl.push_front(i);
		}
		fl.sort();
        t.stop();
	}
	return 0;
}
//vector - 47622,47533,48099,47087,46767
//array -11946,12329,13546,12269,12275
//deque - 87570,85173,88654,84827,86208
//list - 487361,459282,466791,468040,468782
//forward_list - 208096,209842,206245,215131,270301