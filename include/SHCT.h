// Spherical Harmonic nnormalization terms developed by Everett M. Carpenter fit into a compile time class
#include <array>
#include <limits>

constexpr unsigned int factorial(unsigned int n) // only using at compile time so i don't really care if this is slow
{
	return n == 0 ? 1 : n * factorial(n - 1);
}

template<unsigned MaxOrder>
class NLOUP
{
protected:
	static constexpr unsigned MAX_ORDER = MaxOrder + 1; // set
	static constexpr unsigned MAX_DEGREE = 2 * MaxOrder + 1;
	std::array<std::array<float, MAX_DEGREE>, MAX_ORDER> loup;

	constexpr float calcSN3D(unsigned order, int degree) // calculate SN3D value for loup
	{
		int d = (degree == 0) ? 1 : 0;                                                                     // Kronecker delta
		float ratio = static_cast<float>(factorial(order - abs(degree))) / factorial(order + abs(degree)); // ratio of factorials
		return sqrtf((2.f - d) * ratio);
	}

	constexpr void fillLoup() // fill loup with results
	{
		for (int order = 0; order <= MAX_ORDER; order++)
		{
			for (int degree = -order; degree <= order; degree++)
			{
				loup[order][degree + order] = calcSN3D(order, degree); // can't actually have negative indices so we + current order so that degree = -order is at 0
			}
		}
	}
public:
	constexpr NLOUP() : loup{} // init
	{
		fillLoup();
	}

	constexpr float SN3D(size_t order, size_t degree) // retrieve SN3D
	{
		return order <= MAX_ORDER && degree <= order ? loup[order][degree + order] : 0; // safety check
	}

	constexpr float N3D(size_t order, size_t degree) // retrieve N3D
	{
		return order <= MAX_ORDER && degree <= order ? sqrtf(2*order + 1) * loup[order][degree + order] : 0; // safety check + convert to N3D
	}
};
