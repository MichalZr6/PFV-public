#pragma once

#include "conversion.hpp"
#include "SimplExpr.h"

typedef std::vector<std::pair<double, char>> Num_vec;

class Price
{
public:
	Price();
	explicit Price(const std::string &p);
	explicit Price(const double &p);
	double GetPrice() const;
	std::string GetPriceStr() const;
	std::string GetPriceStrCurr() const;
	void SetPrice(const std::string &p);
	void SetPrice(const double &p);

	constexpr operator double() const
	{
		return pd;
	}

	bool operator !=(const Price &p) const
	{
		return ps != p.ps;
	}

	//constexpr operator int() const
	//{ return static_cast<int>(pd); }

private:
	double pd;
	std::string ps;
};