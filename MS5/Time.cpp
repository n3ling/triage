//Name: Nathaniel Ling
//SID: 110372208
//Email: nling@myseneca.ca
//Section: BTP200 NAA
//Prof: Cornel Barna
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds {
	Time& Time::setToNow() {
		m_min = getTime();
		return *this;
	}
	Time::Time(unsigned int min) {
		m_min = min;
	}
	ostream& Time::write(ostream& ostr) const {
		int h, m;
		m = m_min % 60;
		h = m_min / 60;
		ostr << setw(2) << setfill('0') << h << ":" << setw(2) << m;
		return ostr;
	}
	istream& Time::read(istream& istr) {
		int h = 0, m = 0;
		char temp = ' ';
		bool tf = true;
		istr >> h;
		istr >> temp;
		istr >> m;
		if (temp != ':' || h < 0 || m < 0) {
			tf = false;
		}
		else {
			m_min = m + (h * 60);
		}
		if (!tf) {
			istr.setstate(ios::failbit);
		}
		return istr;
	}
	Time& Time::operator-=(const Time& D) {
		if (m_min >= D.m_min) {
			m_min -= D.m_min;
		}
		else {
			while (m_min < D.m_min) {
				m_min += 1440;
			}
			m_min -= D.m_min;
		}
		return *this;
	}
	Time Time::operator-(const Time& D) const {
		Time temp;
		if (this->m_min >= D.m_min) {
			temp.m_min = this->m_min - D.m_min;
		}
		else {
			temp.m_min += this->m_min;
			while (temp.m_min < D.m_min) {
				temp.m_min += 1440;
			}
			temp.m_min -= D.m_min;
		}
		return temp;
	}
	Time& Time::operator+=(const Time& D) {
		m_min += D.m_min;
		return *this;
	}
	Time Time::operator+(const Time& D)const {
		Time temp;
		temp.m_min = this->m_min + D.m_min;
		return temp;
	}
	Time& Time::operator=(unsigned int val) {
		m_min = val;
		return *this;
	}
	Time& Time::operator*=(unsigned int val) {
		m_min *= val;
		return *this;
	}
	Time Time::operator*(unsigned int val)const {
		Time temp;
		temp.m_min = this->m_min * val;
		return temp;
	}
	Time& Time::operator/=(unsigned int val) {
		m_min /= val;
		return *this;
	}
	Time Time::operator/(unsigned int val)const {
		Time temp;
		temp.m_min = this->m_min / val;
		return temp;
	}
	Time::operator int()const {
		return this->m_min;
	}
	Time::operator unsigned int()const {
		return this->m_min;
	}
	ostream& operator<<(ostream& ostr, const Time& D) {
		return D.write(ostr);
	}
	istream& operator>>(istream& istr, Time& D) {
		return D.read(istr);
	}
}