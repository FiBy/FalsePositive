#ifndef MAIN_HPP
#define MAIN_HPP

#include <climits>
#include <random>
#include <vector>

/**
 * @brief getRandomEntry lets you easily access a random item of a std::vector
 * @param vec the vector
 * @param a veto, which values should not be returned
 * @return a random item of the vector (but not elements with value of veto)
 * @todo allow list of vetos
 */
template<class vtype>
vtype getRandomEntry(const std::vector<vtype>& vec, const vtype veto)
{
	vtype result = veto;
	std::random_device rdev{};
	static std::default_random_engine e{rdev()};
	std::uniform_real_distribution<float> d(0,1);

	switch (vec.size())
	{
	case 0:
		return veto;
	case 1:
		return vec.front();
	default:
		while (result == veto)
		{
			result = vec[static_cast<size_t>(floor(d(e)*vec.size()))];
		}
		return result;
	}
}

#endif // MAIN_HPP
