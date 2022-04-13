#include "FvSplit.h"
#include "Globals.h"

FvSplit::FvSplit(FvInfo &basefv, const unsigned short split_count)
{
	splits.clear();
	bfv = std::make_unique<FvInfo>(basefv);
	bfv->invquantity = split_count;
	splits.reserve(split_count);
}

void FvSplit::SetPartFv(const FvInfo & partfv)
{
	FvInfo tmp_fv = *bfv;

	tmp_fv -= partfv;
	is_valid = Validate(tmp_fv, partfv);
	if (!is_valid)
		return;

	*bfv = tmp_fv;

	splits.emplace_back(partfv);
	if (splits.size() == bfv->invquantity - 1)
	{
		Globals::vecFvFromImg.pop_back();
		Globals::vecFvFromImg.push_back(std::move(bfv));
		for (const auto sfv : splits)
		{
			Globals::vecFvFromImg.push_back(std::make_unique<FvInfo>(sfv));
		}
	}
}

bool FvSplit::Validate(const FvInfo &after_split_bfv, const FvInfo &partfv)
{
	if (bfv == nullptr)
		return false;

	if(!bfv->isCorrective() 
			&& (after_split_bfv.net_value * partfv.net_value <= 0
			|| after_split_bfv.gross_value * partfv.gross_value <= 0))
		return false;
	else
		return true;
}

bool FvSplit::isValidSplit() const
{
	return is_valid;
}
