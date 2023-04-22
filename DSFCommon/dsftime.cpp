#include "dsftime.h"

dsf::DSFTime::DSFTime(dsf_tm s /*= 0*/, dsf_tm ns /*= 0*/) :sec(s), nanosec(ns)
{

}

dsf_tm dsf::DSFTime::toMs() const
{
	return sec * dsf_kilo + nanosec / dsf_mega;
}

dsf::DSFTime dsf::DSFTime::fromMs(dsf_tm ms)
{
	return DSFTime(ms / dsf_kilo, ms % dsf_mega);
}


dsf::DSFTime dsf::DSFTime::current()
{
	//todo

	return DSFTime();
}


const dsf::DSFTime dsf::DSFTime::secFloor(const DSFTime& time)
{
	return DSFTime(time.sec, 0);
}

const dsf::DSFTime dsf::DSFTime::secCeil(const DSFTime& time)
{
	if (time.nanosec > 0)
	{
		return DSFTime(time.sec + 1, 0);
	}
	return time;
}

const dsf::DSFTime dsf::DSFTime::operator+(const DSFTime& right) const
{
	DSFTime stamp;
	stamp.sec = sec + right.sec;
	stamp.nanosec = nanosec + right.nanosec;
	if (stamp.nanosec >= dsf_giga)
	{
		stamp.nanosec -= dsf_giga;
		stamp.sec += 1;
	}
	return stamp;
}

const dsf::DSFTime dsf::DSFTime::operator-(const DSFTime& right) const
{
	DSFTime dur;
	dur.sec = sec - right.sec;
	dur.nanosec = nanosec;
	if (nanosec < right.nanosec)
	{
		dur.nanosec += dsf_giga;
		dur.sec -= 1;
	}
	dur.nanosec -= right.nanosec;
	return dur;
}

bool dsf::DSFTime::operator>(const DSFTime& right) const
{
	return sec > right.sec ||
		(sec == right.sec&&nanosec > right.nanosec);
}

bool dsf::DSFTime::operator<=(const DSFTime& right) const
{
	return !(*this > right);
}

bool dsf::DSFTime::operator>=(const DSFTime& right) const
{
	return !(*this < right);
}

bool dsf::DSFTime::operator<(const DSFTime& right) const
{
	return sec < right.sec ||
		(sec == right.sec&&nanosec < right.nanosec);
}


bool dsf::DSFTime::operator!=(const DSFTime& right) const
{
	return !(*this == right);
}

bool dsf::DSFTime::operator==(const DSFTime& right) const
{
	return sec == right.sec&&nanosec == right.nanosec;
}
