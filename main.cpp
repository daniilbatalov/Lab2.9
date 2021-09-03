#define _GLIBCXX_USE_CXX11_ABI 0

#include <any>
#include <iostream>
#include <vector>
#include <variant>
#include <algorithm>

#include "limit.h"
#include "validate.h"
#include "menu_class.h"
#include "time_date_class.h"
#include "flight_class.h"
#include "print_class.h"

using namespace std::string_literals;

void addFlights(std::vector<Flight>& fl)
{
	system("cls");
	int number = 0;
	int amount = fl.size();
	if (amount == 0)
	{
		number = Validate::get_int("How many flights are there?\n>"s, LOWER_FLIGHTS, UPPER_NO_VALID);
	}
	else
	{
		number = Validate::get_int("How many flights would you like to add?\n>"s, LOWER_FLIGHTS, UPPER_NO_VALID);
	}
	amount += number;
	for(int i = amount - number; i < amount; i++)
	{
		enterFlight(fl, i);
	}
}
void printFlights(std::vector<Flight>& fl)
{
	print_header();
	int i = 1;
	for (auto f : fl)
    {
        print_flight(f, i, ON_SCREEN);
		i++;
    }
	if(!fl.size())
	{
		print_empty_table();
	}
	else
	{
		print_line();
	}
	getchar();
}
void deleteFlight(std::vector<Flight>& fl)
{
	if (!fl.size())
	{
		std::cout << "Warning! Nothing to delete";
		getchar();
	}
	else
	{
		int toDelete = Validate::get_int("Which flight do you want to delete?\n>", 1, fl.size()) - 1;
		fl.erase(fl.begin() + toDelete);
	}
}
void clearFlights(std::vector<Flight>& fl)
{
	std::vector<Flight>().swap(fl);
}
void importFlights(std::vector<Flight>& fl)
{
	int am = 0;
	try
	{
		std::ifstream in("input.txt");
		in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		in >> am;
		for(int i = 0; i < am; i++)
		{
			int dyear, dmonth, dday, dhour, dminute, fhour, fminute;
			std::string ap;
			in >> dday;
			in >> dmonth;
			in >> dyear;
			in >> dhour;
			in >> dminute;
			in >> fhour;
			in >> fminute;
			std::getline(in, ap);
			std::getline(in, ap);
			int result = 1;
			result = Validate::validate(dday, UPPER_DAY, LOWER_DATE) * Validate::validate(dmonth, UPPER_MONTH, LOWER_DATE) * Validate::validate(dyear, UPPER_YEAR, LOWER_DATE);
			result = result * Validate::validate(dhour, UPPER_HOUR, LOWER_TIME) * Validate::validate(dminute, UPPER_MINUTE, LOWER_TIME) * Validate::validate(fhour, UPPER_NO_VALID, LOWER_TIME) * Validate::validate(fminute, UPPER_MINUTE, LOWER_TIME);
			try
			{
				if(result)
				{
					auto ddate = Date(dday, dmonth, dyear);
					auto dtime = Time(dhour, dminute);
					auto ftime = Time(fhour, fminute);
					auto r = Flight(ddate, dtime, ftime, ap);
					fl.push_back(r);
				}
				else
				{
					throw "Error: incorrect data in file string #"s;
				}
			}
			catch(std::string except)
			{
				std::cerr << except << i << std::endl;
				getchar();
			}
		}
        in.close();
	}
	catch (std::ios_base::failure &fail)
	{
		std::cout << fail.what() << std::endl;
	}
}
void exportFlights(std::vector<Flight>& fl)
{
    try
    {
        std::ofstream out("output.txt");
        out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
        out << fl.size() << std::endl;
        for (auto f : fl)
        {
            out << std::setw(02) << std::setfill('0') << f.getDepartureDate().getDay() << " "
                << std::setw(02) << std::setfill('0') << f.getDepartureDate().getMonth() << " "
                << std::setw(04) << std::setfill('0') << f.getDepartureDate().getYear() << " "
                << std::setw(02) << std::setfill('0') << f.getDepartureTime().getHour() << " "
                << std::setw(02) << std::setfill('0') << f.getDepartureTime().getMinute() << " "
                << std::setw(02) << std::setfill('0') << f.getFlightTime().getHour() << " "
                << std::setw(02) << std::setfill('0') << f.getFlightTime().getMinute() << std::endl
                << f.getAirport() << std::endl;
        }
        out.close();
    }
    catch (std::ios_base::failure &fail)
	{
		std::cout << fail.what() << std::endl;
	}
}
void sortDate(std::vector<Flight>& fl)
{
    std::sort(fl.begin(), fl.end(), compare_date_time);
}
void sortFlightTime(std::vector<Flight>& fl)
{
    std::sort(fl.begin(), fl.end(), compare_ftime);
}
void sortAirport(std::vector<Flight>& fl)
{
    std::sort(fl.begin(), fl.end(), compare_by_airport);
}
int main()
{

	Menu sort_menu {"How do you want to sort the flights?"s, {{"1. Sort by date and time of departure"s, sortDate}, {"2. Sort by travel time"s, sortFlightTime}, {"3. Sort by availability of breakfast"s, sortFlightTime}, {"4. Sort by airport of destination"s, sortAirport}}};
	Menu print_menu {"How do you want to print the flights?"s, {{"1. Print the flights on screen"s, printFlights}, {"2. Export the flights into output.txt"s, exportFlights}}};
	Menu enter_menu {"How do you want to enter the flights?"s, {{"1. Enter the flights manually"s, addFlights}, {"2. Import the flights from input.txt"s, importFlights}}};
	Menu main_menu {"What do you want to do?"s, {{"1. Enter the flights"s, &enter_menu}, {"2. Delete the flight"s, deleteFlight}, {"3. Sort the flights"s, &sort_menu}, {"4. Print the flights"s, &print_menu}, {"5. Clear all the flights"s, clearFlights}}};


	using Params = std::vector<Flight>;
	auto param = Params {};
	main_menu.menu(param);

}


