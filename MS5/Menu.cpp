//Name: Nathaniel Ling
//SID: 110372208
//Email: nling@myseneca.ca
//Section: BTP200 NAA
//Prof: Cornel Barna
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "utils.h"
namespace sdds {
	Menu::Menu(const char* MenuContent, int NoOfSelections) {
		m_text = new char[strlen(MenuContent) + 1];
		strcpy(m_text, MenuContent);
		m_noOfSel = NoOfSelections;
	}
	Menu::~Menu() {
		delete[] m_text;
	}
	Menu::Menu(const Menu& src) {
		m_noOfSel = src.m_noOfSel;
		if (src.m_text != nullptr) {
			m_text = new char[strlen(src.m_text) + 1];
			strcpy(m_text, src.m_text);
		}
		else {
			m_text = nullptr;
		}
	}
	void Menu::display()const {
		std::cout << m_text << std::endl;
		std::cout << "0- Exit" << std::endl;
	}
	int& Menu::operator>>(int& Selection) {
		display();
		Selection = getInt(0, m_noOfSel, "> ", "Invalid option ");
		return Selection;
	}
}