#include <iostream>
#include <string>

bool isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(const std::string &date) {
	if (date.size() != 10u)
		return false;
	if (date[2u] != '/' || date[5u] != '/')
		return false;

	for (size_t i = 0u; i < 10u; ++i) {
		if (i == 2u || i == 5u)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
	}

	int dd = std::stoi(date.substr(0u, 2u));
	int mm = std::stoi(date.substr(3u, 2u));
	int yyyy = std::stoi(date.substr(6u, 4u));

	if (mm < 1 || mm > 12)
		return false;
	if (dd < 1)
		return false;
	if (yyyy < 1)
		return false;

	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (isLeapYear(yyyy))
		daysInMonth[1] = 29;

	return dd <= daysInMonth[mm - 1];
}

int anchor(int year) {
	int c = year / 100;
	return ((5 * (c % 4)) % 7 + 2) % 7;
}

int anchorDate(int year) {
	int T = year % 100;

	if (T % 2 == 1)
		T += 11;

	T /= 2;

	if (T % 2 == 1)
		T += 11;

	T = 7 - (T % 7);

	return (T + anchor(year)) % 7;
}

int dayOfWeek(int year, int month, int day) {
	int DOOMSDAYS[] = {3, 28, 14, 4, 9, 6, 11, 8, 5, 10, 7, 12};

	if (isLeapYear(year)) {
		DOOMSDAYS[0] = 4;
		DOOMSDAYS[1] = 29;
	}

	int doomsday = DOOMSDAYS[month - 1];

	day = ((day - doomsday) % 7 + 7) % 7;

	return (day + anchorDate(year)) % 7;
}

int main() {

	std::cout
		<< "Program based on Conway's Doomsday Aglorithm to determine the day "
		<< '\n'
		<< "of the week of any given date on the Gregeorian calendar"
		<< std::endl;

	std::string DAYS[] = {"Sunday",	  "Monday", "Tuesday", "Wednesday",
						  "Thursday", "Friday", "Saturday"};

	char choice = 'y';

	while (choice == 'Y' || choice == 'y') {
		std::string date;
		std::cout << "Enter a date (dd/mm/yyyy): " << std::endl;
		std::cin >> date;

		if (!isValidDate(date)) {
			std::cout << "Please enter a valid date.";
			continue;
		}
		int day = std::stoi(date.substr(0u, 2u));
		int month = std::stoi(date.substr(3u, 2u));
		int year = std::stoi(date.substr(6u, 4u));

		int weekday = dayOfWeek(year, month, day);

		std::cout << date << " was a " << DAYS[weekday] << "!" << std::endl;

		std::cout << "Do you want to pick another date [N/y]?" << std::endl;
		std::cin >> choice;
	}

	return 0;
}
