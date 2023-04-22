#pragma once

#include <stdlib.h>

typedef long long dsf_tm;

#define dsf_kilo 1000
#define dsf_mega 1000000
#define dsf_giga 1000000000

namespace dsf
{

	struct DSFTime
	{
		dsf_tm sec = 0;
		dsf_tm nanosec = 0;

		DSFTime(dsf_tm s = 0, dsf_tm ns = 0);

		dsf_tm toMs()const;
		static DSFTime fromMs(dsf_tm ms);

		static DSFTime current();

		static const DSFTime secFloor(const DSFTime& time);
		static const DSFTime secCeil(const DSFTime& time);

		const DSFTime operator+(const DSFTime& right)const;
		const DSFTime operator-(const DSFTime& right)const;
		bool operator==(const DSFTime& right)const;
		bool operator!=(const DSFTime& right)const;
		bool operator>(const DSFTime& right)const;
		bool operator<(const DSFTime& right)const;
		bool operator>=(const DSFTime& right)const;
		bool operator<=(const DSFTime& right)const;

	};
}
