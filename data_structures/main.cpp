#include "union_find.h"
#include "morris_traversal.h"
#include "string_utils.h"
#include "hash_table.h"


using Iitem = Item<int>;
using Collection = std::vector<Iitem>;

void TestUnionFind()
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
}


void TestMorrisTraversal()
{

    // create test tree (1, 2, 3, 4, 5, 6, 7)
    std::unique_ptr<Node<int> > root = std::make_unique<Node<int> >(4);
    std::unique_ptr<Node<int> > node1 = std::make_unique<Node<int> >(1);
    std::unique_ptr<Node<int> > node2 = std::make_unique<Node<int> >(2);
    std::unique_ptr<Node<int> > node3 = std::make_unique<Node<int> >(3);
    std::unique_ptr<Node<int> > node5 = std::make_unique<Node<int> >(5);
    std::unique_ptr<Node<int> > node6 = std::make_unique<Node<int> >(6);
    std::unique_ptr<Node<int> > node7 = std::make_unique<Node<int> >(7);
    

    node2->left_ = std::move(node1);
    node2->right_ = std::move(node3);

    node6->left_ = std::move(node5);
    node6->right_ = std::move(node7);

    root->left_ = std::move(node2);
    root->right_ = std::move(node6);

    Tree<int> tree(std::move(root));

    auto results = tree.MorrisTraversal();
    for (auto const& res : results)
    {
        std::cout << res << " ";
    }
    std::cout << std::endl;
    
}

void TestStringUtils()
{
    std::string str = "fsgbbfg, rsgfrg, adsgvdsbvf , wqrgvsfrb,  qwvfb,  wb frb  , rwf df , fvfsgvbfsbsbfb dfb  f , frgvfsb fbb , frswbfsb  ,thysaeafv ,354vrgvv ,dsbv fs ,sdf fsv sdfvsdvsdv,ads dfsvdsvdsvds, ds sdv ,dasgdbva";
    auto r1 = StringUtils::Split1(str);
    auto r2 = StringUtils::Split2(str);

    assert(r1.size() == r2.size());
}


void TesthashTable()
{
    HashTable<std::string, int> table;
    table.Insert("one", 1);
    table.Insert("two", 2);
    table.Insert("three", 3);
    
    int x = 0;
    if (table.Get("one", x))
    {
        std::cout << "found key one : " << x << std::endl;
    }
    else
    {
        std::cout << "Could not find key one" << std::endl;
    }
    


    table.Remove("one");
    if (table.Get("one", x))
    {
        std::cout << "found key one : " << x << std::endl;
    }
    else
    {
        std::cout << "Could not find key one" << std::endl;
    }
    table.Remove("two");
    table.Insert("one", 5);
    if (table.Get("one", x))
    {
        std::cout << "found key one : " << x << std::endl;
    }
    else
    {
        std::cout << "Could not find key one" << std::endl;
    }
}



int main(int argc, char **argv)
{

    TesthashTable();
    return 0;
}