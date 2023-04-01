#pragma once

class DateTime {
private:
	unsigned seconds;
	unsigned minutes;
	unsigned hours;
	unsigned day;
	unsigned month;
	unsigned year;
public:
	DateTime();
	DateTime(unsigned seconds, unsigned minutes, unsigned hours, unsigned day, unsigned month, unsigned year);
	void printDateTime() const;
	int dateCompare(const DateTime& other) const;
};

