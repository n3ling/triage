//Name: Nathaniel Ling
//SID: 110372208
//Email: nling@myseneca.ca
//Section: BTP200 NAA
//Prof: Cornel Barna
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#include <iostream>
#include "CovidPatient.h"
#include "Patient.h"
namespace sdds {
   int nextCovidTicket = 1;
   CovidPatient::CovidPatient() : Patient(nextCovidTicket) {
	   nextCovidTicket += 1;
   }
   char CovidPatient::type()const {
	   return 'C';
   }
   std::istream& CovidPatient::csvRead(std::istream& istr) {
	   Patient::csvRead(istr);
	   nextCovidTicket = Patient::number() + 1;
	   istr.ignore(2000, '\n');
	   return istr;
   }
   std::ostream& CovidPatient::write(std::ostream& ostr)const {
	   if (fileIO()) {
		   Patient::csvWrite(ostr);
	   }
	   else {
		   ostr << "COVID TEST\n";
		   Patient::write(ostr);
			ostr << std::endl;
	   }
	   return ostr;
   }
   std::istream& CovidPatient::read(std::istream& istr) {
	   if (fileIO()) {
		   csvRead(istr);
	   }
	   else {
		   Patient::read(istr);
	   }
	   return istr;
   }
}