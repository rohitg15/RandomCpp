#include <iostream>
#include  <vector>
#include <assert.h>

template <typename T>
struct Item
{
    T item_;
    int idx_;
    int parent_;
    int rank_;

    Item();
    Item(T item, int idx);
    Item(Item<T> const& item);
    Item<T>& operator=(Item<T> const& item);

    friend bool operator==(Item<T> const& item0, Item<T> const& item1)
    {
	    return ((item0.item_ == item1.item_) && (item0.idx_ == item1.idx_) && (item0.parent_ == item1.parent_) && (item0.rank_ == item1.rank_));
    }
    friend bool operator!=(Item<T> const& item0, Item<T> const& item1)
    {
	    return !(item0 == item1);
    }
};

template <typename T>
Item<T>::Item()
    :
	idx_(-1),
	parent_(-1),
	rank_(-1)
{}

template <typename T>
Item<T>::Item(T item, int idx)
    :	item_(item),
	idx_(idx),
	parent_(idx),
	rank_(0)
{}

template <typename T>
Item<T>::Item(Item<T> const& item)
    :
	item_(item.item_),
	idx_(item.idx_),
	parent_(item.parent_),
	rank_(item.rank_)
{}

template <typename T>
Item<T>& Item<T>::operator=(Item<T> const& item)
{
    if (this != &item)
    {
        item_ = item.item_;
        idx_ = item.idx_;
        parent_ = item.parent_;
        rank_ = item.rank_;
    }
}


template <typename T, typename Collection = std::vector<Item<T> > >
class UnionFind
{

    public:
	UnionFind();

	UnionFind(Collection const& items);

	UnionFind(UnionFind const&) = delete;
	UnionFind& operator=(UnionFind const&) = delete;

	void CreateSet(Item<T> const& item);

	void MergeSet(Item<T> const& item0, Item<T> const& item1);

	bool FindSet(Item<T> const& item, Item<T> & res);
    private:

	int FindSetImpl(int idx);

	Collection items_;
};

template <typename T, typename Collection>
UnionFind<T, Collection>::UnionFind()
{}

template <typename T, typename Collection>
UnionFind<T, Collection>::UnionFind(Collection const& items)
    :	items_(items)
{}

template <typename T, typename Collection>
void UnionFind<T, Collection>::CreateSet(Item<T> const& item)
{
    items_.emplace_back(item);
}

template <typename T, typename Collection>
bool UnionFind<T, Collection>::FindSet(Item<T> const& item, Item<T> & res)
{
    int idx = item.idx_;
    if (idx < 0 || idx >= items_.size())
    {
	    return false;
    }

    // implement path compression
    auto parentIdx = FindSetImpl(idx);
    if (parentIdx < 0)
    {
	    return false;
    }

     // copy assignment
    res = items_[parentIdx];

    return true;
}

template <typename T, typename Collection>
int UnionFind<T, Collection>::FindSetImpl(int idx)
{
    if (idx < 0 || idx >= items_.size())
    {
	    return -1;
    }

    // implementing path compression
    if (idx != items_[idx].parent_)
    {
	    items_[idx].parent_ = FindSetImpl(items_[idx].parent_);
    }
    return items_[idx].parent_;
}

template <typename T, typename Collection>
void UnionFind<T, Collection>::MergeSet(Item<T> const& item0, Item<T> const& item1)
{
    if (item0.idx_ == item1.idx_)
    {
	    return;
    }

    // get indices of representatives
    auto p0 = FindSetImpl(item0.idx_);
    auto p1 = FindSetImpl(item1.idx_);
    if (p0 == -1 || p1 == -1)
    {
	    throw std::runtime_error("items do not exist in set");
    }

    // get the actual representative items
    assert(p0 >= 0 && p0 <= items_.size());
    assert(p1 >= 0 && p1 <= items_.size());
    if (p0 == p1)
    {
	    // item0 and item1 already belong to the same set
	    return;
    }
    auto& pItem0 = items_[p0];
    auto& pItem1 = items_[p1];

   // union by rank - smaller subtree is appended to larger subtree based on rank
    if (pItem0.rank_ > pItem1.rank_)
    {
	    pItem1.parent_ = pItem0.idx_;
    }
    else
    {
	    pItem0.parent_ = pItem1.idx_;
    }

    if (pItem0.rank_ == pItem1.rank_)
    {
	    ++pItem1.rank_;
    }
}


