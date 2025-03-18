#ifndef SIMPLEXPR_H
#define SIMPLEXPR_H

#include <string>
#include <vector>
#include <algorithm>

class SimplExpr
{
public:
    SimplExpr() = delete;
    SimplExpr(const std::string &str) : expr(str)
    {
		skip_ws(expr);

        if(!parse())
            throw std::logic_error::exception(std::string("Wykonanie działań niemożliwe dla: "+ str).c_str());
    }

    double getValue() const;

private:
    std::string expr {""};
    std::vector<std::pair<double, char>> nums {};

    bool parse();
    bool tryAddNum(std::string &num, char sign);
    bool is_num(const std::string &num) const;
    std::string & skip_ws(std::string &str) const;

};

#endif // SIMPLEXPR_H
