#include "FacultyValue.h"

std::istream & operator>>(std::istream & inp, FacultyValue & fValue)
{
	int n;
	inp >> n;
	fValue.setFaculty(n);
	return inp;
}

std::ostream & operator<<(std::ostream & out, const FacultyValue & fValue)
{
	switch (fValue.getFaculty())
	{
	case 1:
		out << "Computer Sience";
		break;
	case 2:
		out << "Medicine";
		break;
	case 3:
		out << "Literature";
		break;
	default:
		out << fValue.getFaculty();
		break;
	}
	return out;
}

bool operator>=(const FacultyValue & f1, const FacultyValue & f2)
{
	if(f1.getFaculty() >= f2.getFaculty())
		return true;
	return false;
}

bool operator<=(const FacultyValue & f1, const FacultyValue & f2)
{
	if (f1.getFaculty() <= f2.getFaculty()) 
		return true;
	return false;
}
