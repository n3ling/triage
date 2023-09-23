//Name: Nathaniel Ling
//SID: 110372208
//Email: nling@myseneca.ca
//Section: BTP200 NAA
//Prof: Cornel Barna
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>
#include "PreTriage.h"
#include "Patient.h"
#include "Ticket.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
#include "Menu.h"
#include "Time.h"
#include "utils.h"
namespace sdds {
	PreTriage::PreTriage(const char* dataFilename) : m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2) {
		delete[] m_dataFilename;
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		m_averCovidWait = 15;
		m_averTriageWait = 5;
		load();
	}
	PreTriage::~PreTriage() {
		std::ofstream f;
		f.open(m_dataFilename);
		if (f.is_open()) {
			f << m_averCovidWait << "," << m_averTriageWait << std::endl;
			std::cout << "Saving Average Wait Times,\n" << "   COVID Test: " << m_averCovidWait << "\n   Triage: " << m_averTriageWait << std::endl;
			std::cout << "Saving m_lineup...";
			for (auto i = 0; i < m_lineupSize; i++) {
				std::cout << "\n" << i + 1 << "- ";
				m_lineup[i]->csvWrite(std::cout);
				m_lineup[i]->csvWrite(f) << std::endl;
			}
			for (auto i = 0; i < m_lineupSize; i++) {
				delete m_lineup[i];
			}
			delete[] m_dataFilename;
			m_dataFilename = nullptr;
			std::cout << "\ndone!" << std::endl;
			f.close();
		}
		
	}
	const Time PreTriage::getWaitTime(const Patient& p)const {
		unsigned num = 0;
		Time temp;
		for (auto i = 0; i < m_lineupSize; i++) {
			if (p.type() == m_lineup[i]->type()) {
				num++;
			}
		}
		if (p == 'C') {
			temp = m_averCovidWait * num;
		}
		if (p == 'T') {
			temp = m_averTriageWait * num;
		}
		return temp;
	}
	void PreTriage::setAverageWaitTime(const Patient& p) {
		if (p == 'C') {
			m_averCovidWait = ((getTime() - (unsigned int)Time(p)) + (unsigned int)(m_averCovidWait * (unsigned int)(p.number() - 1))) / p.number();
		}
		if (p == 'T') {
			m_averTriageWait = ((getTime() - (unsigned int)Time(p)) + (unsigned int)(m_averTriageWait * (unsigned int)(p.number() - 1))) / p.number();
		}
	}
	void PreTriage::removePatientFromLineup(int index) {
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}
	int PreTriage::indexOfFirstInLine(char type)const {
		for (auto i = 0; i < m_lineupSize; i++) {
			if (m_lineup[i]->type() == type) {
				return i;
			}
		}
		return -1;
	}
	void PreTriage::load() {
		std::cout << "Loading data..." << std::endl;
		std::string str;
		char del;
		std::ifstream f;
		f.open(m_dataFilename);
		if (f.is_open()) {
			getline(f, str, '\n');
			std::stringstream ss(str);
			ss >> m_averCovidWait >> del >> m_averTriageWait;
			ss.ignore('\n');
			for (int i = 0; i < maxNoOfPatients; i++) {
				Patient* temp = nullptr;
				if (!f.fail() || !f.eof()) {
					getline(f, str, ',');
					if (!strcmp(str.c_str(), "C")) {
						temp = new CovidPatient();
					}
					else if (!strcmp(str.c_str(), "T")) {
						temp = new TriagePatient();
					}
					if (temp != nullptr) {
						temp->fileIO(true);
						temp->read(f);
						temp->fileIO(false);
						m_lineup[i] = temp;
						m_lineupSize++;
					}
				}
				else {
					break;
				}
			}
			if (!f.eof()) {
				std::cout << "Warning: number of records exceeded 100" << std::endl;
			}
			if (m_lineupSize == 0) {
				std::cout << "No data or bad data file!\n" << std::endl;
			}
			else {
				std::cout << m_lineupSize << " Records imported...\n" << std::endl;
			}
			f.close();
		}
		else {
			std::cout << "No data or bad data file!";
		}
	}
	void PreTriage::reg() {
		int selection;
		if (m_lineupSize == maxNoOfPatients) {
			std::cout << "Line up full!" << std::endl;
			return;
		}
		else {
			m_pMenu >> selection;
			if (selection == 1) {
				m_lineup[m_lineupSize] = new CovidPatient();
			}
			else if (selection == 2) {
				m_lineup[m_lineupSize] = new TriagePatient();
			}
			else if (selection == 0) {
				return;
			}
			m_lineup[m_lineupSize]->setArrivalTime();
			std::cout << "Please enter patient information: " << std::endl;
			m_lineup[m_lineupSize]->fileIO(false);
			m_lineup[m_lineupSize]->read(std::cin);
			std::cout << "\n******************************************" << std::endl;
			m_lineup[m_lineupSize]->write(std::cout);
			std::cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]) << std::endl;
			std::cout << "******************************************\n"<< std::endl;
			++m_lineupSize;
		}
	}
	void PreTriage::admit() {
		int selection, index;
		char type;
		m_pMenu >> selection;
		if (selection == 1) {
			type = 'C';
		}
		else if (selection == 2) {
			type = 'T';
		}
		else if (selection == 0) {
			return;
		}
		index = indexOfFirstInLine(type);
		if (index == -1) {
			return;
		}
		std::cout << "\n******************************************" << std::endl;
		m_lineup[index]->fileIO(false);
		std::cout << "Calling for ";
		m_lineup[index]->write(std::cout);
		std::cout << "******************************************\n" << std::endl;
		setAverageWaitTime(*m_lineup[index]);
		removePatientFromLineup(index);
	}
	void PreTriage::run(void) {
		int selection = -1;
		while (selection != 0) {
			m_appMenu >> selection;
			if (selection == 1) {
				reg();
			}
			else if (selection == 2) {
				admit();
			}
		}
	}
}