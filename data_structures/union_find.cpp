#include "union_find.h"

using Iitem = Item<int>;
using Collection = std::vector<Iitem>;

int main(int argc, char **argv)
{

    Collection items{Iitem(0, 0), Iitem(1,1), Iitem(2,2), Iitem(3,3), Iitem(4,4), Iitem(5,5)};
    UnionFind<int> uf{items};


    // merge (0, 1) , (2, 3), (1, 4)
    uf.MergeSet(items[0], items[1]);
    uf.MergeSet(items[2], items[3]);
    uf.MergeSet(items[1], items[4]);

    // check if (0, 4) are in the same set and (3, 5) are not
    Iitem ref0, ref4;
    if (!uf.FindSet(items[0], ref0))
    {
	throw std::runtime_error("item0 not in set");
    }
    if(!uf.FindSet(items[4], ref4))
    {
	throw std::runtime_error("item4 not in set");
    }

    assert(ref0 == ref4);

    Iitem ref3, ref5;
    if (!uf.FindSet(items[3], ref3))
    {
	throw std::runtime_error("item3 not in set");
    }
    if (!uf.FindSet(items[5], ref5))
    {
	throw std::runtime_error("item5 not in set");
    }
    assert(ref3 != ref5);
    std::cout << "Success!" << std::endl;
    return 0;
}
