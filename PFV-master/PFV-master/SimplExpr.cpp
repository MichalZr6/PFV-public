#include "SimplExpr.h"

double SimplExpr::getValue() const
{
    double val {0};
    for(auto it : nums)
    {
        switch (it.second)
        {
            case '+':
                val += it.first;
            break;

            case '-':
                val -= it.first;
            break;
        }
    }
    return val;
}

bool SimplExpr::parse()
{
    unsigned int i = 0;
    char sign {' '};
    const char p = '+';
    const char m = '-';
    std::string tmp{""};

    if(expr.empty())
        return false;

    sign = expr[0] == m ? m : p;

    for(; i < expr.size(); i++)
    {
        if(expr[i] == p || expr[i] == m)
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

    if(sign != '-' && sign != '+')
        return false;

    auto pos = num.find(',');
    while(pos != std::string::npos)
    {
        num.replace(pos, 1, ".");
        pos = num.find(',');
    }
    nums.push_back({stod(num), sign});

    return true;

}

bool SimplExpr::is_num(const std::string &num) const
{
    unsigned int found_point = 0;
    std::string tmp { num };
    size_t i = 0;
    if (tmp[i] == '-') i++;
    for(; i<tmp.size(); i++)
    {
        if(tmp[i] == ',')
            found_point++;
        else if(tmp[i] < 48 || tmp[i] > 57)
            return false;
    }
    if(found_point > 1)
        return false;
    else return true;
}

std::string & SimplExpr::skip_ws(std::string &str) const
{
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}

