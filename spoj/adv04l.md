#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class Converter
{
	public:
		void calculate(const long long limit);
		long long convert(long long miles) const;

	private:
		vector<long long> _fibonacci;
};

void Converter::calculate(const long long limit)
{
	vector<long long>::const_reverse_iterator iter;

	this->_fibonacci.clear();
	this->_fibonacci.push_back(1);
	this->_fibonacci.push_back(1);

	while (this->_fibonacci.back() <= limit)
	{
		iter = this->_fibonacci.rbegin();
		this->_fibonacci.push_back(*iter + *(iter + 1));
	}

}

long long Converter::convert(long long miles) const
{
	long long kilometers = 0;
	vector<long long>::const_reverse_iterator iter;

	for (iter = this->_fibonacci.rbegin(); iter != this->_fibonacci.rend();
	     iter++)
	{
		if (*iter <= miles)
		{
			miles -= *iter;
			kilometers += *(iter - 1); // Next in sequence
		}
	}

	return kilometers;
}


int main()
{
	Converter converter;
	converter.calculate(1000000000000000LL);

	int numCases;
	cin >> numCases;

	while (numCases--)
	{
		long long miles;
		cin >> miles;
		cout << converter.convert(miles) << endl;
	}

	return 0;
}
