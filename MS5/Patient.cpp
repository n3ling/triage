//Name: Nathaniel Ling
//SID: 110372208
//Email: nling@myseneca.ca
//Section: BTP200 NAA
//Prof: Cornel Barna
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Patient.h"
#include "Ticket.h"
#include "utils.h"
namespace sdds {
	Patient::Patient(int ticket, bool IOflag) {
		m_ticket = Ticket(ticket);
		m_IOflag = IOflag;
	}
	Patient::~Patient() {
		delete[] m_patientName;
	}
	bool Patient::fileIO()const {
		return m_IOflag;
	}
	void Patient::fileIO(bool IOflag) {
		m_IOflag = IOflag;
	}
	bool Patient::operator==(const char c)const {
		bool tf = false;
		if (this->type() == c) {
			tf = true;
		}
		return tf;
	}
	bool Patient::operator==(const Patient& P)const {
		bool tf = false;
		if (this->type() == P.type()) {
			tf = true;
		}
		return tf;
	}
	void Patient::setArrivalTime() {
		m_ticket.resetTime();
	}
	Patient::operator Time()const {
		return Time(m_ticket);
	}
	int Patient::number()const {
		return m_ticket.number();
	}
	std::ostream& Patient::csvWrite(std::ostream& ostr)const {
		ostr << type() << "," << m_patientName << "," << m_OHIP << ",";
		m_ticket.csvWrite(ostr);
		return ostr;
	}
	std::istream& Patient::csvRead(std::istream& istr) {
		char name[100];
		istr.getline(name, 100, ',');
		delete[] m_patientName;
		m_patientName = nullptr;
		m_patientName = new char[strlen(name) + 1];
		strcpy(m_patientName, name);
		istr >> m_OHIP;
		istr.ignore();
		m_ticket.csvRead(istr);
		return istr;
	}
	std::ostream& Patient::write(std::ostream& ostr)const {
		ostr << m_ticket << std::endl;
		if (m_patientName[0] == '\n') {
			for (unsigned i = 1; i < strlen(m_patientName); i++) {
				ostr << m_patientName[i];
			}
			ostr << ", OHIP: " << m_OHIP;
		}
		else {
			if (strlen(m_patientName) > 25) {
				ostr.write(m_patientName, 25) << ", OHIP: " << m_OHIP;
			}
			else {
				ostr << m_patientName << ", OHIP: " << m_OHIP;
			}
		}
		return ostr;
	}
	std::istream& Patient::read(std::istream& istr) {
		char name[100];
		std::cout << "Name: ";
		istr.getline(name, 100);
		delete[] m_patientName;
		m_patientName = nullptr;
		m_patientName = new char[strlen(name) + 1];
		strcpy(m_patientName, name);
		m_OHIP = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ");
		return istr;
	}
}