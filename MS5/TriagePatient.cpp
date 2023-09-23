//Name: Nathaniel Ling
//SID: 110372208
//Email: nling@myseneca.ca
//Section: BTP200 NAA
//Prof: Cornel Barna
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "TriagePatient.h"
#include "Patient.h"
namespace sdds {
   int nextTriageTicket = 1;
   TriagePatient::TriagePatient() : Patient(nextTriageTicket) {
	   m_symptoms = nullptr;
	   nextTriageTicket += 1;
   }
   char TriagePatient::type()const {
	   return 'T';
   }
   std::ostream& TriagePatient::csvWrite(std::ostream& ostr)const {
	   Patient::csvWrite(ostr);
	   ostr << "," << m_symptoms;
	   return ostr;
   }
   std::istream& TriagePatient::csvRead(std::istream& istr) {
	   char temp[500];
	   delete[] m_symptoms;
	   Patient::csvRead(istr);
	   istr.ignore();
	   istr.getline(temp, 500);
	   m_symptoms = new char[strlen(temp) + 1];
	   strcpy(m_symptoms, temp);
	   nextTriageTicket = Patient::number() + 1;
	   return istr;
   }
   std::ostream& TriagePatient::write(std::ostream& ostr)const {
	   if (fileIO()) {
		   csvWrite(ostr);
	   }
	   else {
		   ostr << "TRIAGE\n";
		   Patient::write(ostr);
		   ostr << std::endl;
		   ostr << "Symptoms: " << m_symptoms << std::endl;
	   }
	   return ostr;
   }
   std::istream& TriagePatient::read(std::istream& istr) {
	   if (fileIO()) {
		   csvRead(istr);
	   }
	   else {
		   char temp[500];
		   delete[] m_symptoms;
		   Patient::read(istr);
		   std::cout << "Symptoms: ";
		   istr.getline(temp, 500);
		   m_symptoms = new char[strlen(temp) + 1];
		   strcpy(m_symptoms, temp);
	   }
	   return istr;
   }
   TriagePatient::~TriagePatient() {
	   delete[] m_symptoms;
   }
}