//Name: Nathaniel Ling
//SID: 110372208
//Email: nling@myseneca.ca
//Section: BTP200 NAA
//Prof: Cornel Barna
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#include <iostream>
#include "IOAble.h"
namespace sdds {
	std::ostream& operator<<(std::ostream& ostr, const IOAble& IO) {
		return IO.write(ostr);
	}
	std::istream& operator>>(std::istream& istr, IOAble& IO) {
		return IO.read(istr);
	}
}