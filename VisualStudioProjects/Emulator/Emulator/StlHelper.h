#ifndef _stl_helper_h_
#define _stl_helper_h_
#include <functional>

namespace bnssemulator {
	
	template <class T1, class T2, class Pred = std::less<T1> >
	struct compare_pair_first {
		bool operator()(const std::pair<T1, T2> &left, const std::pair<T1, T2> &right) const {
			Pred p;
			return p(left.first, right.first);
		}
	};

	template <class T1, class T2, class Pred = std::less<T2> >
	struct compare_pair_second {
		bool operator()(const std::pair<T1, T2> &left, const std::pair<T1, T2> &right) const {
			Pred p;
			return p(left.second, right.second);
		}
	};

	template <class T, class Pred = std::less<T> >
	struct compare_pair_difference {
		bool operator()(const std::pair<T, T> &left, const std::pair<T, T> &right) const {
			Pred p;
			return p(left.second - left.first, right.second - right.first);
		}
	};
}

#endif
