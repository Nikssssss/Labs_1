#include "Tritset.h"

static Trit GetTrit(unsigned int currentUint, long long index) {
	unsigned int bigMask = pow(2, (sizeof(unsigned int) * 8 - 2) - 2 * (index % (sizeof(unsigned int) * 8 / 2)) + 1);
	unsigned int littleMask = pow(2, (sizeof(unsigned int) * 8 - 2) - 2 * (index % (sizeof(unsigned int) * 8 / 2)));
	unsigned int tempMask = (bigMask | littleMask);
	if ((currentUint & tempMask) == bigMask)
		return True;
	else if ((currentUint & tempMask) == littleMask)
		return False;
	else
		return Unknown;
}

static void SetTrit(unsigned int &currentUint, long long index, Trit value) {
	unsigned int bigMask = pow(2, (sizeof(unsigned int) * 8 - 2) - 2 * (index % (sizeof(unsigned int) * 8 / 2)) + 1);
	unsigned int littleMask = pow(2, (sizeof(unsigned int) * 8 - 2) - 2 * (index % (sizeof(unsigned int) * 8 / 2)));
	switch (value) {
	case False:
		currentUint &= ((~littleMask) & (~bigMask));
		currentUint |= littleMask;
		break;
	case True:
		currentUint &= ((~littleMask) & (~bigMask));
		currentUint |= bigMask;
		break;
	case Unknown:
		currentUint &= ((~littleMask) & (~bigMask));
		break;
	}
}

Trit operator&(Trit left, Trit right) {
	if (left == False || right == False)
		return False;
	if (left == True && right == True)
		return True;
	return Unknown;
}

Trit operator|(Trit left, Trit right) {
	if (left == True || right == True)
		return True;
	if (left == False && right == False)
		return False;
	return Unknown;
}

Trit operator~(Trit value) {
	switch (value) {
	case (True): return False;
	case (False): return True;
	case (Unknown): return Unknown;
	}
}

std::ostream &operator<<(std::ostream &out, Trit value) {
	switch (value) {
	case (True): {
		out << "True";
		break;
	}
	case (False): {
		out << "False";
		break;
	}
	case (Unknown): {
		out << "Unknown";
		break;
	}
	}
	return out;
}

Tritset::reference::operator Trit() const {
	if (ind > mainTritset->numberOfTrits - 1)
		return Unknown;
	else
		return GetTrit(mainTritset->set[ind / (sizeof(unsigned int) * 8 / 2)], ind);
}

Tritset::Tritset() {}

Tritset::Tritset(long long value) {
	if (value < 0)
		throw std::invalid_argument("Number of Trits should not be negative");
	numberOfTrits = value;
	if (value > 0) {
		numberOfUInts = (value / 4 / sizeof(unsigned int)) + 1;
		set.resize(numberOfUInts);
	}
	else {
		numberOfUInts = 0;
		set.resize(0);
	}
}

Trit Tritset::operator[](long long index) const {
	if (index < 0)
		throw std::invalid_argument("Index of Trit should not be negative");
	else if (index > numberOfTrits - 1)
		return Unknown;
	return GetTrit(set[index / (sizeof(unsigned int) * 8 / 2)], index);
}

Tritset::reference Tritset::operator[](long long index) {
	if (index < 0)
		throw std::invalid_argument("Index of Trit should not be negative");
	return reference(index, this);
}

Tritset::reference::reference(long long index, Tritset *tritset) {
	ind = index;
	mainTritset = tritset;
}

Tritset::reference &Tritset::reference::operator=(Trit value) {
	long long curMaxIndexOfTrits = mainTritset->numberOfUInts * 4 * sizeof(unsigned int) - 1;
	if (value != Unknown) {
		if (ind > mainTritset->numberOfTrits - 1) {
			if (ind > curMaxIndexOfTrits) {
				mainTritset->numberOfUInts = ind / 4 / sizeof(unsigned int) + 1;
				mainTritset->set.resize(mainTritset->numberOfUInts);
			}
			mainTritset->numberOfTrits = ind + 1;
		}
		SetTrit(mainTritset->set[ind / (sizeof(unsigned int) * 8 / 2)], ind, value);
	}
	else if (ind <= curMaxIndexOfTrits)
		SetTrit(mainTritset->set[ind / (sizeof(unsigned int) * 8 / 2)], ind, value);
	return *this;
}

Tritset::reference &Tritset::reference::operator=(const Tritset::reference &ref) {
	*this = (Trit)ref;
	return *this;
}

Tritset &Tritset::operator=(Tritset rightSet) {
	this->numberOfTrits = rightSet.numberOfTrits;
	this->numberOfUInts = rightSet.numberOfUInts;
	this->set = rightSet.set;
	return *this;
}

Tritset operator&(Tritset left, Tritset right) {
	long long maxNumberOfTrits;
	if (left.numberOfTrits >= right.numberOfTrits)
		maxNumberOfTrits = left.numberOfTrits;
	else
		maxNumberOfTrits = right.numberOfTrits;
	Tritset tempSet(maxNumberOfTrits);
	Trit leftTr, rightTr;
	for (long long i = 0; i < maxNumberOfTrits; i++) {
		leftTr = left[i];
		rightTr = right[i];
		tempSet[i] = (leftTr & rightTr);
	}
	return tempSet;
}

Tritset operator|(Tritset left, Tritset right) {
	long long maxNumberOfTrits;
	if (left.numberOfTrits >= right.numberOfTrits)
		maxNumberOfTrits = left.numberOfTrits;
	else
		maxNumberOfTrits = right.numberOfTrits;
	Tritset tempSet(maxNumberOfTrits);
	Trit leftTr, rightTr;
	for (long long i = 0; i < maxNumberOfTrits; i++) {
		leftTr = left[i];
		rightTr = right[i];
		tempSet[i] = (leftTr | rightTr);
	}
	return tempSet;
}

Tritset operator~(Tritset set) {
	Tritset tempSet(set.numberOfTrits);
	for (long long i = 0; i < set.numberOfTrits; i++) {
		tempSet[i] = ~(set[i]);
	}
	return tempSet;
}

long long Tritset::Capacity() {
	return numberOfUInts;
}

long long Tritset::TritCapacity() {
	return numberOfTrits;
}

void Tritset::Shrink() {
	long long i = numberOfTrits - 1;
	while ((i >= 0) && ((*this)[i] == Unknown))
		i--;
	if (i < 0) {
		numberOfTrits = 0;
		numberOfUInts = 0;
		set.resize(0);
	}
	else {
		numberOfTrits = i + 1;
		numberOfUInts = (numberOfTrits / 4 / sizeof(unsigned int)) + 1;
		set.resize(numberOfUInts);
	}
}

long long Tritset::Cardinality(Trit value) {
	long long count = 0;
	for (long long i = 0; i < numberOfTrits; i++) {
		if ((*this)[i] == value)
			count++;
	}
	return count;
}

std::map<Trit, long long> Tritset::Cardinality() {
	std::map<Trit, long long> tempMap;
	for (long long i = 0; i < numberOfTrits; i++) {
		tempMap[(*this)[i]]++;
	}
	return tempMap;
}

void Tritset::Trim(long long lastIndex) {
	if (lastIndex < 0)
		throw std::invalid_argument("Index of Trit should not be negative");
	if ((lastIndex != 0) && (lastIndex > numberOfTrits - 1))
		throw std::invalid_argument("Index of Trit should not be greater than max index");
	long long i = numberOfTrits - 1;
	while ((i >= 0) && (i != lastIndex))
		i--;
	if (i < 0) {
		numberOfTrits = 0;
		numberOfUInts = 0;
		set.resize(0);
	}
	else {
		numberOfTrits = i;
		numberOfUInts = (numberOfTrits / 4 / sizeof(unsigned int)) + 1;
		set.resize(numberOfUInts);
	}
}

long long Tritset::Length() {
	long long i = numberOfTrits - 1;
	while ((i >= 0) && ((*this)[i] == Unknown))
		i--;
	if (i < 0)
		return 0;
	else
		return (i + 1);
}