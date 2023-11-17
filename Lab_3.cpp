#include <iostream>
#include <array>
#include <string>
#include <algorithm>
#include <vector>

template <std::size_t n>
using vector = std::array<int, n>;

template <std::size_t n, std::size_t m>
using matrix = std::array<std::array<int, m>, n>;

namespace bp
{
	static constexpr int weight = 15;
	static constexpr int count = 5;
	static vector<count> weights = { 6, 4, 3, 2, 5 };
	static vector<count> prices = { 5, 3, 1, 3, 6 };
	static int result = 0;
	static vector<count> incl = { 0, 0, 0, 0, 0 };

	void backpack() noexcept
	{
		matrix<count + 1, weight + 1> table = {};
		for (int i = 1; i < count + 1; ++i)
		{
			for (int j = 0; j <= weight; ++j)
			{
				if (j - weights[i - 1] >= 0)
					table[i][j] = std::max(table[i - 1][j], table[i - 1][j - weights[i - 1]] + prices[i - 1]);
				else
					table[i][j] = table[i - 1][j];
			}
		}
		result = table[count][weight];
		int j = weight;
		for (int i = count; i > 0; --i)
		{
			if (table[i][j] > table[i - 1][j])
			{
				incl[i - 1] = true;
				j -= weights[i - 1];
			}
			else
				incl[i - 1] = false;
		}
	}
}

namespace nv
{
#define WORD_A "agccgtagctaatc"
#define WORD_B "gcctagcctat"

	static std::string word_a = WORD_A;
	static std::string word_b = WORD_B;
	static std::string result;

	static constexpr std::size_t count_a = sizeof(WORD_A) - 1;
	static constexpr std::size_t count_b = sizeof(WORD_B) - 1;

	void nidlman_vunsh() noexcept
	{
		matrix<count_a, count_b> colors, values;
		bool row = false, col = false;
		for (std::size_t i = 0; i < count_a; ++i)
		{
			for (std::size_t j = 0; j < count_b; ++j)
			{
				colors[i][j] = word_a[i] == word_b[j] ? true : false;
				if (colors[0][j]) col = true;
				if (i == 0) values[0][j] = col ? 1 : 0;
			}
			if (colors[i][0]) row = true;
			values[i][0] = row ? 1 : 0;
		}
		for (std::size_t i = 1; i < count_a; ++i)
		{
			for (std::size_t j = 1; j < count_b; ++j)
				values[i][j] = colors[i][j] ? values[i - 1][j - 1] + 1 : std::max(values[i - 1][j], values[i][j - 1]);
		}
		result.reserve(std::max(count_a, count_b));
		std::size_t counter = values[count_a - 1][count_b - 1];
		for (int i = count_a - 1; i >= 0; --i)
		{
			for (int j = count_b - 1; j >= 0; --j)
			{
				if (colors[i][j] && values[i][j] == counter)
				{
					result.push_back(word_a[i]);
					--counter;
				}
			}
		}
		std::reverse(result.begin(), result.end());
	}
}

namespace op
{
	static constexpr std::size_t exponent = 6;
	static std::vector<int> sequence;
	static std::size_t result = 0;

	void min_operations() noexcept
	{
		vector<exponent + 1> op = {};
		std::vector<std::vector<int>> sequences;
		sequences.resize(exponent + 1);
		sequences[0].push_back(0);
		sequences[1].push_back(0);
		for (std::size_t i = 2; i <= exponent; ++i)
		{
			op[i] = op[i - 1] + 1;
			sequences[i] = sequences[i - 1];
			sequences[i].push_back(1);
			for (std::size_t j = 2; j <= i - 1; ++j)
			{
				int min_op = exponent;
				auto save = op[i];
				op[i] = std::min(op[i], op[j] + op[i - j] + 1);
				if (save == op[i] && op[i] < min_op)
				{
					sequences[i] = sequences[i - 1];
					sequences[i].push_back(1);
					min_op = op[i];
				}
				else if (op[i] < min_op)
				{
					sequences[i] = sequences[j];
					std::copy(sequences[i - j].begin(), sequences[i - j].end(),
						std::back_inserter(sequences[i]));
					sequences[i].push_back(1);
					min_op = op[i];
				}
				if (i % j == 0)
				{
					auto save = op[i];
					op[i] = std::min(op[i], static_cast<int>(op[i / j] + j - 1));
					if (save != op[i] && op[i] < min_op)
					{
						sequences[i] = sequences[i / j];
						sequences[i].push_back(j);
						sequences[i].push_back(1);
						min_op = op[i];
					}
				}
			}
		}
		result = op[exponent];
		sequence = sequences[exponent];
	}
}

namespace mw
{
	static constexpr int inf = 99;
	static constexpr std::size_t n = 4;
	static int result;
	static std::vector<int> way;
	static std::vector<std::vector<int>> rectangle = {
		{ 0, 7, 8, 99 },
		{ 5, 0, 7, 4 },
		{ 3, 2, 0, 99 },
		{ 2, 99, 5, 0 }
	};

	void min_way() noexcept
	{
		std::size_t n1 = 0;
		std::size_t n2 = n - 1;
		vector<n> a = {};
		vector<n> b;
		for (std::size_t i = 0; i < n; b[i] = rectangle[n1][i], ++i);
		vector<n> c;
		for (auto i = c.begin(); i != c.end(); *i = -1, ++i);
		for (std::size_t i = 0; i < n; ++i)
		{
			int min_element = inf, min_index = 0;
			for (std::size_t j = 0; j < n; ++j)
			{
				if (!a[j] && min_element > b[j])
				{
					min_element = b[j];
					min_index = j;
				}
			}
			a[min_index] = true;
			for (std::size_t j = 0; j < n; ++j)
			{
				if (!a[j])
				{
					b[j] = std::min(b[j], min_element + rectangle[min_index][j]);
					c[j] = min_index;
				}
			}
		}
		result = b[n2];
		for (int i = n2; i != -1; i = c[i])
			way.push_back(i);
		std::reverse(way.begin(), way.end());
	}
}

namespace tr
{
	static constexpr std::size_t n = 5;
	static int result;
	static vector<n> way;
	static std::vector<std::vector<int>> triangle = {
		{ 0, 7, 0, 0, 0, 0 },
		{ 0, 3, 8, 0, 0, 0 },
		{ 0, 8, 1, 0, 0, 0 },
		{ 0, 2, 7, 4, 4, 0 },
		{ 0, 4, 5, 2, 6, 5 }
	};

	void max_triangle() noexcept
	{
		matrix<n, n + 1> result_triangle;
		for (std::size_t i = 0; i < n; ++i)
		{
			for (std::size_t j = 0; j < n + 1; ++j)
				result_triangle[i][j] = triangle[i][j];
		}
		for (std::size_t i = 1; i < n; ++i)
		{
			for (std::size_t j = 1; j < n + 1; ++j)
				result_triangle[i][j] = std::max(result_triangle[i - 1][j - 1] + result_triangle[i][j],
					result_triangle[i - 1][j] + result_triangle[i][j]);
		}
		std::size_t maxIndex = 1;
		for (std::size_t i = 2; i < n + 1; ++i)
		{
			if (result_triangle[n - 1][maxIndex] < result_triangle[4][i])
				maxIndex = i;
		}
		result = result_triangle[n - 1][maxIndex];
		way[n - 1] = maxIndex;
		for (std::size_t i = n - 1; i > 0; --i)
		{
			if (result_triangle[i][way[i]] - result_triangle[i - 1][way[i]] == triangle[i][way[i]])
				way[i - 1] = way[i];
			else if (result_triangle[i][way[i]] - result_triangle[i - 1][way[i] - 1] == triangle[i][way[i]])
				way[i - 1] = way[i] - 1;
		}
		for (std::size_t i = 0; i < n; ++i)
			way[i] = triangle[i][way[i]];
	}
}

void main()
{
	std::cout << "BACKPACK PROBLEM" << std::endl;
	bp::backpack();
	std::cout << "w: ";
	for (auto i = bp::weights.begin(); i != bp::weights.end(); std::cout << *i << "  ", ++i);
	std::cout << std::endl;
	std::cout << "p: ";
	for (auto i = bp::prices.begin(); i != bp::prices.end(); std::cout << *i << "  ", ++i);
	std::cout << std::endl;
	std::cout << "max price: " << bp::result << std::endl;
	std::cout << "indecies: ";
	for (std::size_t i = 0; i < bp::count; bp::incl[i] ? std::cout << i + 1 << "  " : std::cout, ++i);
	std::cout << std::endl << std::endl;

	std::cout << "NIDLMAN-VUNSH ALGORITHM" << std::endl;
	nv::nidlman_vunsh();
	std::cout << "word a: " << nv::word_a << std::endl;
	std::cout << "word b: " << nv::word_b << std::endl;
	std::cout << "max subchain: " << nv::result << std::endl;
	std::cout << std::endl;

	std::cout << "OPERATION SEARCH" << std::endl;
	op::min_operations();
	std::cout << "exponent: " << op::exponent << std::endl;
	std::cout << "min operations count: " << op::result << std::endl;
	std::cout << "sequence: ";
	for (auto i = op::sequence.begin(); i != op::sequence.end();
		*i == 1 ? std::cout << "mult  " : (*i == 0 ? std::cout : std::cout << "power of " << *i << "  "), ++i);
	std::cout << std::endl << std::endl;

	std::cout << "RECTANGLE PROBLEM" << std::endl;
	mw::min_way();
	std::cout << "rectangle:" << std::endl;
	for (std::size_t i = 0; i < mw::n; ++i)
	{
		for (std::size_t j = 0; j < mw::n; ++j)
		{
			if (!(mw::rectangle[i][j] == mw::inf))
				std::cout << mw::rectangle[i][j] << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << "length: " << mw::result << std::endl;
	std::cout << "way: ";
	for (auto i = mw::way.begin(); i != mw::way.end(); std::cout << *i << "  ", ++i);
	std::cout << std::endl << std::endl;

	std::cout << "TRIANGLE PROBLEM" << std::endl;
	tr::max_triangle();
	std::cout << "triangle:" << std::endl;
	for (std::size_t i = 0; i < tr::n; ++i)
	{
		for (std::size_t j = 0; j < tr::n + 1; ++j)
			std::cout << tr::triangle[i][j] << "  ";
		std::cout << std::endl;
	}
	std::cout << "sum: " << tr::result << std::endl;
	std::cout << "way: ";
	for (auto i = tr::way.begin(); i != tr::way.end(); std::cout << *i << "  ", ++i);
	std::cout << std::endl << std::endl;
}