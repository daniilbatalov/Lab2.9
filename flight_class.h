#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "time_date_class.h"


using namespace std::string_literals;

namespace Validate
{
template <typename T>

bool validate (const T value, const T upper, const T lower)
{
	return ((value <= upper) && (value >= lower));
}
int get_int(std::string message, int lower, int upper)
{
	char str[STRING_LIMIT];
	int x;
	std::cout << message;
	fgets(str, sizeof(str), stdin);
	while (sscanf (str, "%d", &x) != 1 || !validate<int>(x, upper, lower))
	{
		std::cout << "Enter correct value!\n>";
		fgets(str, sizeof(str), stdin);
	}
	return x;
}
}

class Flight;

void open();
void print_line();
void print_str_line();
void print_empty_line();
void print_header();
void print_empty_table();
void print_flight(const Flight&, const int, const int);



class Flight
{
private:
	Date m_departureDate;
	Time m_departureTime;
	Time m_flightTime;
	bool m_breakfast;
	std::string m_airport;
public:
	Date getDepartureDate() const
	{
		return m_departureDate;
	}
	void setDepartureDate(const Date& dd)
	{
		m_departureDate = dd;
	}

	Time getDepartureTime() const
	{
		return m_departureTime;
	}
	void setDepartureTime(const Time& dt)
	{
		m_departureTime = dt;
	}

	Time getFlightTime() const
	{
		return m_flightTime;
	}
	void setFlightTime(const Time& ft)
	{
		m_flightTime = ft;
	}

	bool getBreakfast() const
	{
		return m_breakfast;
	}
	void setBreakfast(const bool br)
	{
		m_breakfast = br;
	}

	std::string getAirport() const
	{
		return m_airport;
	}
	void setAirport(const std::string ap)
	{
		m_airport = ap;
	}

	void breakfast_check ()
	{
		m_breakfast = ((m_flightTime.getHour() > 4 || (m_flightTime.getHour() == 4 && m_flightTime.getMinute() >= 1)));
	}

	Flight()
	{
		setDepartureDate(Date());
		setDepartureTime(Time());
		setFlightTime(Time());
		setAirport("Default Airport");
		breakfast_check();
	}
	Flight(const Date& departureDate, const Time& departureTime, const Time& flightTime, const std::string airport)
	{
		setDepartureDate(departureDate);
		setDepartureTime(departureTime);
		setFlightTime(flightTime);
		setAirport(airport);
		breakfast_check();
	}
	Flight(const Flight& flight)
	{
		setDepartureDate(flight.getDepartureDate());
		setDepartureTime(flight.getDepartureTime());
		setFlightTime(flight.getFlightTime());
		setAirport(flight.getAirport());
		breakfast_check();
	}
};

using flight_v = std::vector<Flight>;

void clear_stdin()
{
	int ch = getchar();
	while (ch != '\n' && ch != EOF)
	{
		ch = getchar();
	}
}

auto enterTime(const bool val)
{
	int hour, minute;
	if(val)
	{
		hour = Validate::get_int("Enter the hour of departure:\n>"s, LOWER_TIME, UPPER_HOUR) % UPPER_HOUR;
		minute = Validate::get_int("Enter the minute of departure:\n>"s, LOWER_TIME, UPPER_MINUTE) % UPPER_MINUTE;
	}
	else
	{
		hour = Validate::get_int("How many hours the flight will be?\n>"s, LOWER_TIME, UPPER_NO_VALID);
		minute = Validate::get_int("How many minutes the flight will be?\n>"s, LOWER_TIME, UPPER_MINUTE);
	}
	return Time(hour, minute);
}
auto enterDate()
{
	int day, month, year;
	day = Validate::get_int("Enter the day of the flight:\n>"s, LOWER_DATE, UPPER_DAY);
	month = Validate::get_int("Enter the month of the flight:\n>"s, LOWER_DATE, UPPER_MONTH);
	year = Validate::get_int("Enter the year of the flight:\n>"s, LOWER_DATE, UPPER_YEAR);
	return Date(day, month, year);
}
std::string enterAirport()
{
	std::cout << "What's the airport of destination?\n>";
	std::string ap;
	std::cin >> ap;
	clear_stdin();
	return ap;
}
void enterFlight(std::vector<Flight>& fl, const int n)
{
	print_str_line();
	std::cout << "Flight #" << n + 1 << std::endl;
	fl.push_back(Flight(enterDate(), enterTime(true), enterTime(false), enterAirport()));

}


void print_line()
{
	std::cout << "+----+------------+--------+-------------+-----------+---------------+\n";
}
void print_str_line()
{
	std::cout <<  "----------------------------\n";
}
void print_empty_line()
{
	std::cout <<  "+--------------------------------------------------------------------+\n";
}
void print_header()
{
	print_line();
	std::cout << "| No |    Date    |  Time  | Travel time | Breakfast |    Airport    |\n";
}
void print_empty_table()
{
	print_empty_line();
	std::cout << "|                     There's no flights yet...                      |\n";
	print_empty_line();
}
void print_flight(const Flight& fl, const int i, const int mode)
{
	std::string b = (fl.getBreakfast() ? "+" : "-");
	print_line();
	//choose_stream(mode, str) << "| %2i | %02d.%02d.%04d | %02d:%02d  |    %02d:%02d    |     %s     | %13s |\n", i, fl.getDepartureDate().getDay(), fl.getDepartureDate().getMonth(), fl.getDepartureDate().getYear(), fl.getDepartureTime().getHour(), fl.getDepartureTime().getMinute(), fl.getFlightTime().getHour(), fl.getFlightTime().getMinute(), b, fl.getAirport());
	std::cout << "| "           << std::right << std::setw(02) << i
			  << " | "          << std::setw(02) << std::setfill('0') << fl.getDepartureDate().getDay()
			  << "."            << std::setw(02) << std::setfill('0') << fl.getDepartureDate().getMonth()
			  << "."            << std::setw(04) << std::setfill('0') << fl.getDepartureDate().getYear()
			  << " | "          << std::setw(02) << std::setfill('0') << fl.getDepartureTime().getHour()
			  << ":"            << std::setw(02) << std::setfill('0') << fl.getDepartureTime().getMinute()
			  << "  |    "      << std::setw(02) << std::setfill('0') << fl.getFlightTime().getHour()
			  << ":"            << std::setw(02) << std::setfill('0') << fl.getFlightTime().getMinute()
			  << "    |     "   << b
			  << "     | "      << std::setw(14) << std::left << std::setfill(' ') << fl.getAirport()
			  << "|\n";
}

int signum(const int x)
{
    return (!x) ? 1 : (x / abs(x));
}
int compare_time (const Flight& first, const Flight& second)
{
    int result = 0;
    int arr[2];
    arr[0] = signum(first.getDepartureTime().getHour() - second.getDepartureTime().getHour());
    arr[1] = signum(first.getDepartureTime().getMinute() - second.getDepartureTime().getMinute());
    result = signum(10 * arr[0] + arr[1]);
    return result;
}

bool compare_date_time (const Flight& first, const Flight& second)
{
    int result = 0;
    int arr[4];
    arr[0] = signum(first.getDepartureDate().getYear() - second.getDepartureDate().getYear());
    arr[1] = signum(first.getDepartureDate().getMonth() - second.getDepartureDate().getMonth());
    arr[2] = signum(first.getDepartureDate().getDay() - second.getDepartureDate().getYear());
    arr[3] = compare_time(first, second);
    result = signum(1000 * arr[0] + 100 * arr[1] + 10 * arr[2] + arr[3]);
    if (result == -1)
    {
        return true;
    }
    return false;
}

bool compare_ftime (const Flight& first, const Flight& second)
{
    int result = 0;
    int arr[2];
    arr[0] = signum(first.getFlightTime().getHour() - second.getFlightTime().getHour());
    arr[1] = signum(first.getFlightTime().getMinute() - second.getFlightTime().getMinute());
    result = signum(10 * arr[0] + arr[1]);
    if (result == -1)
    {
        return true;
    }
    return false;
}
bool compare_by_airport (const Flight& first, const Flight& second)
{
    return ((first.getAirport().compare(second.getAirport()) < 0) ?  true : false);
}
