#include "DateTime.h"
#include <iomanip>

DateTime::DateTime() : DateTime(0,0,0,0,0,0) {}

DateTime::DateTime(unsigned seconds, unsigned minutes, unsigned hours, unsigned day, unsigned month, unsigned year):
seconds(seconds), minutes(minutes), hours(hours), day(day), month(month), year(year) {}

void DateTime::printDateTime() const {
	printf("%02u:%02u:%02u %02u.%02u.%u", seconds, minutes, hours, day, month, year);
}

int DateTime::dateCompare(const DateTime& other) const {
	if (year < other.year)
		return -1;
	if (year > other.year)
		return 1;

	if (month < other.month)
		return -1;
	if (month > other.month)
		return 1;

	if (day < other.day)
		return -1;
	if (day > other.day)
		return 1;

	if (hours < other.hours)
		return -1;
	if (hours > other.hours)
		return 1;

	if (minutes < other.minutes)
		return -1;
	if (minutes > other.minutes)
		return 1;

	if (seconds < other.seconds)
		return -1;
	if (seconds > other.seconds)
		return 1;

	return 0; //is this bad practice xd ? cant think of faster way
}

