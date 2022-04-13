#include "Price.h"

Price::Price()
{
	this->pd = 0.0;
	this->ps = "";
}

Price::Price(const std::string &p_str)
{
	this->SetPrice(p_str);
}

Price::Price(const double &p)
{
	this->SetPrice(p);
}

double Price::GetPrice() const
{
	return this->pd;
}

std::string Price::GetPriceStr() const
{
	return this->ps;
}

std::string Price::GetPriceStrCurr() const
{
	return this->ps + " z³";
}

void Price::SetPrice(const std::string &p_str)
{
	if (p_str.empty())
	{
		*this = Price();
		return;
	}
	
	try 
	{
		auto expr = std::make_unique<SimplExpr>(p_str);

		this->pd = expr->getValue();
		this->ps = convert::string_cast<double>(pd, 2, convert::thou_sep);
		addZeros(this->ps);
	}
	catch (std::exception &e)
	{
		throw e;
	}
}

void Price::SetPrice(const double &p)
{
	if (p == 0)
	{
		*this = Price();
		return;
	}
	this->pd = p;
	this->ps = convert::string_cast<double>(p, 2, convert::thou_sep);
	addZeros(this->ps);
}


inline bool operator!=(const Price &p1, const Price &p2)
{
	return !(p1.GetPrice() == p2.GetPrice());
}

inline bool operator==(const Price &p1, const Price &p2)
{
	return p1.GetPrice() == p2.GetPrice();
}

inline bool operator<(const Price &p1, const Price &p2)
{
	return p1.GetPrice() < p2.GetPrice();
}

inline const Price operator *(const Price &p1, const Price &p2)
{
	return Price(p1.GetPrice() * p2.GetPrice());
}

inline const Price operator /(const Price &p1, const Price &p2)
{
	if (p2.GetPrice() == 0.0)
		throw std::domain_error("Nast¹pi³a próba dzielenia przez 0 dla " + std::to_string(p2.GetPrice()));
	return Price(p1.GetPrice() / p2.GetPrice());
}