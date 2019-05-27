#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <vector>
#include <string>
#include <type_traits>
#include <iostream>

// generic entry object to be stored in table
template <typename K, typename V>
struct Entry
{
    bool isValid_;
    K key_;
    V value_;

    Entry();

    Entry(K const& key, V const& value);

    Entry (Entry const&) = delete;
    Entry& operator=(Entry const&) = delete;

    void Set(K const& key, V const& value, bool isValid = true);

    void SetValid(bool isValid);
};

template <typename K, typename V>
Entry<K,V>::Entry()
:
    isValid_(false)
{}


template <typename K, typename V>
Entry<K,V>::Entry(
    K const& key,
    V const& value
)
:
    isValid_(false),
    key_(key),
    value_(value)
{}

template <typename K, typename V>
void Entry<K, V>::Set(
    K const& key,
    V const& value,
    bool isValid
)
{
    isValid_ = isValid;
    key_ = key;
    value_ = value;
}

template <typename K, typename V>
void Entry<K, V>::SetValid(bool isValid)
{
    isValid_ = isValid;
}

// Generic Hash callable implementation
template <typename K, typename Enable = void>
class Hashimpl 
{};


// partial template class specialization for integral types
template <typename K>
class Hashimpl<K, 
    typename std::enable_if< std::is_integral<K>::value, K>::type
    >
{
    public:
        Hashimpl(unsigned int p);

        Hashimpl( Hashimpl const& ) = delete;
        Hashimpl& operator=( Hashimpl const& ) = delete;

        unsigned int operator()(K const& key);
    private:
        unsigned int p_;
};

template <typename K>
Hashimpl<K, typename std::enable_if< std::is_integral<K>::value, K>::type>::Hashimpl(unsigned int p)
:
    p_(p)
{
    std::cout << "Invoking integral specialization" << std::endl;
}

template <typename K>
unsigned int Hashimpl<K, typename std::enable_if< std::is_integral<K>::value, K>::type>::operator() (K const& key)
{
    return key % p_;
}
// specialization for integral types ends here


// full template class specialization for string types
template <>
class Hashimpl<std::string, std::string>
{
    public:
        Hashimpl(unsigned int p)
        :
        p_(p)
        {
            std::cout << "Invoking Hashimpl specialization for string - inline" << std::endl;            
        }

        Hashimpl( Hashimpl const& ) = delete;
        Hashimpl& operator=( Hashimpl const& ) = delete;

        unsigned int operator()(std::string const& key)
        {
            unsigned int sum = 0;
            for (auto const& c : key)
            {
                sum += static_cast<unsigned int>(c);
            }
            return sum % p_;
        }
    private:
        unsigned int p_;
};


// full template specialization for string ends here

template <
    typename K,
    typename V,
    typename Hash = Hashimpl<K, K>,
    typename Collection = std::vector<Entry<K, V> > 
    >
class HashTable
{
    public:
        HashTable();

        HashTable( HashTable const& ) = delete;
        HashTable& operator= (HashTable const& ) = delete;

        bool Insert(K const& key, V const& value);
        bool Get(K const& key, V& value);
        bool Remove(K const& key);

    private:

        bool GetImpl(K const& key, unsigned int& idx);

        static constexpr unsigned int TABLE_SIZE = 13337;
        Collection table_;
        Hash hash_;
};

template <
    typename K,
    typename V,
    typename Hash,
    typename Collection
    >
HashTable<K, V, Hash, Collection>::HashTable()
:
    table_(TABLE_SIZE),
    hash_(TABLE_SIZE)
{
    // check if hash is invocable
    // static_assert(std::is_invocable< decltype(hash_) >::value);

    std::cout << "table size : " << table_.size() << " , " << TABLE_SIZE << std::endl;
}


template <
    typename K,
    typename V,
    typename Hash,
    typename Collection
    >
bool HashTable<K, V, Hash, Collection>::Insert(
    K const& key,
    V const& value
)
{
    unsigned int index = hash_(key);
    
    for (unsigned int i = index; i < table_.size(); ++i)
    {
        auto& entry = table_[i];
        if (!entry.isValid_ || entry.key_ == key)
        {
            entry.Set(key, value, true);
            return true;
        }
    }

    for (unsigned int i = 0; i < index; ++i)
    {
        auto& entry = table_[i];
        if (!entry.isValid_ || entry.key_ == key)
        {
            entry.Set(key, value, true);
            return true;
        }
    }
    return false;
}

template <
    typename K,
    typename V,
    typename Hash,
    typename Collection
    >
bool HashTable<K, V, Hash, Collection>::GetImpl(
    K const& key,
    unsigned int& idx
)
{
    unsigned int index = hash_(key);
    for (unsigned int i = index; i < table_.size(); ++i)
    {
        auto& entry = table_[i];
        if (entry.isValid_ && entry.key_ == key)
        {
            idx = i;
            return true;
        }
    }
    for (unsigned int i = 0; i < index; ++i)
    {
        auto& entry = table_[i];
        if (entry.isValid_ && entry.key_ == key)
        {
            idx = i;
            return true;
        }
    }
    return false;
}

template <
    typename K,
    typename V,
    typename Hash,
    typename Collection
    >
bool HashTable<K, V, Hash, Collection>::Get(
    K const& key,
    V& value
)
{
    unsigned int idx = 0;
    if (!GetImpl(key, idx))
    {
        return false;
    }
    value = table_[idx].value_;
    return true;
}


template <
    typename K,
    typename V,
    typename Hash,
    typename Collection
    >
bool HashTable<K, V, Hash, Collection>::Remove(
    K const& key
)
{
    unsigned int idx = 0;
    if (!GetImpl(key, idx))
    {
        return false;
    }
    auto& entry = table_[idx];
    entry.SetValid(false);
    return true;
}

#endif

