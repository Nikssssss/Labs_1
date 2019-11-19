#include <iostream>
#include <vector>
#include <cmath>
#include <map>

enum Trit { False, Unknown, True };

Trit operator&(Trit left, Trit right);
Trit operator|(Trit left, Trit right);
Trit operator~(Trit value);
std::ostream &operator<<(std::ostream &out, Trit value);

class Tritset
{
private:
	long long numberOfTrits;
	long long numberOfUInts;
	std::vector<unsigned int> set;
public:
	class reference 
	{
	private:
		long long ind;
		Tritset *mainTritset;
	public:
		reference(long long index, Tritset *tritset);
		reference &operator=(Trit value);
		reference &operator=(const reference &ref);
		operator Trit() const;
	};
	Tritset();
	Tritset(long long value);
	Trit operator[](long long index) const;
	reference operator[](long long index);
	Tritset &operator=(Tritset rightSet);
	friend Tritset operator&(Tritset left, Tritset right);
	friend Tritset operator|(Tritset left, Tritset right);
	friend Tritset operator~(Tritset value);
	long long Capacity();
	long long TritCapacity();
	void Shrink();
	long long Cardinality(Trit value);
	std::map<Trit, long long> Cardinality();
	void Trim(long long lastIndex);
	long long Length();
};

