//Name: Nathaniel Ling
//SID: 110372208
//Email: nling@myseneca.ca
//Section: BTP200 NAA
//Prof: Cornel Barna
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#ifndef SDDS_PATIENT_H
#define SDDS_PATIENT_H
#include "IOAble.h"
#include "Ticket.h"
namespace sdds {
	class Patient : public IOAble {
		char* m_patientName = nullptr;
		int m_OHIP;
		Ticket m_ticket;
		bool m_IOflag;
	public:
		Patient(int ticket = 0, bool IOflag = false);
		~Patient();
		Patient(const Patient& src) = delete;
		Patient& operator=(const Patient& src) = delete;
		virtual char type()const = 0;
		bool fileIO()const;
		void fileIO(bool IOflag);
		bool operator==(const char c)const;
		bool operator==(const Patient& P)const;
		void setArrivalTime();
		operator Time()const;
		int number()const;
		std::ostream& csvWrite(std::ostream& ostr)const;
		std::istream& csvRead(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
	};
}
#endif