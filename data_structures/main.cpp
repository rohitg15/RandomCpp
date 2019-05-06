#include "union_find.h"
#include "morris_traversal.h"


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


int main(int argc, char **argv)
{

    TestMorrisTraversal();
    
    return 0;
}