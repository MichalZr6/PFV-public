#include "SimplExpr.h"

const std::set<char> SimplExpr::const_signs = { plus, minus, multipl, div };

double SimplExpr::getValue() const
{
    double total { 0 };

    if (nums.empty())
        return 0;

    if (nums.size() == 1)
        return nums[0].first;

    for(auto it = nums.begin(); it < nums.end(); ++it)
    {
        total += priority_calc(it);
    }
    return total;
}

double SimplExpr::priority_calc(std::vector<std::pair<double, char>>::const_iterator &iter) const
{
    double part_val;
    
    part_val = iter++->first;    

    while (iter != nums.end())
    {
        if (iter->second == multipl)
            part_val *= iter->first;
        else if (iter->second == div)
            part_val /= iter->first;
        else
            break;

        iter++;
    }

    iter--;       // because for loop will increment iterator
    return part_val;
}

bool SimplExpr::parse()
{
    unsigned int i = 0;
    char sign;
    std::string tmp{""};

    if(expr.empty())
        return false;

    sign = expr[0] == minus ? minus : ' ';

    for(; i < expr.size(); i++)
    {
        if(const_signs.count(expr[i]))
        {
            if(!tryAddNum(tmp, sign))
                return false;

            sign = expr[i];
            tmp.clear();
        }
        else
            tmp += expr[i];
    }

    if(!tmp.empty())
    {
        if(!tryAddNum(tmp, sign))
            return false;
    }

    return true;
}

bool SimplExpr::tryAddNum(std::string &num, char sign)
{
    if(num.empty())
        num = "0";

    if(!is_num(num))
        return false;

    if(sign != ' ' && const_signs.count(sign) == 0)
        return false;

    replace_comma_with_point(num);
    if (sign == minus)
        num.insert(num.begin(), minus);

    nums.push_back({ stod(num), sign });

    return true;

}

bool SimplExpr::is_num(const std::string &num) const
{
    unsigned int found_points = 0;
    unsigned int found_commas = 0;
    std::string tmp { num };
    size_t i = 0;
    if (tmp[i] == '-') i++;
    for(; i<tmp.size(); i++)
    {
        if (tmp[i] == '.')
            found_points++;
        else if (tmp[i] == ',')
            found_commas++;
        else if(tmp[i] < 48 || tmp[i] > 57)
            return false;
    }
    if(found_points + found_commas >= 2)
        return false;
    else return true;
}

std::string & SimplExpr::skip_ws(std::string &str) const
{
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}

void SimplExpr::replace_comma_with_point(std::string& num) const
{
    auto pos = num.find(',');
    while (pos != std::string::npos)
    {
        num.replace(pos, 1, ".");
        pos = num.find(',');
    }
}

