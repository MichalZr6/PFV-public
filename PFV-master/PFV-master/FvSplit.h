#pragma once

#include "FvClasses.h"


class FvSplit
{
public:
	FvSplit(FvInfo &basefv, const unsigned short split_count);

	void SetPartFv(const FvInfo &partfv);
	std::vector<FvInfo> GetSplits() const;
	bool isValidSplit() const;

private:
	bool is_valid = false;
	std::unique_ptr<FvInfo> bfv;
	std::vector<FvInfo> splits;

	bool Validate(const FvInfo &, const FvInfo &);
};