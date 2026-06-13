// Carlos Aguilar

#ifndef ARRAY_BAG_HPP
#define ARRAY_BAG_HPP

#include <vector>
#include <cstddef>

template<class ItemType>
class ArrayBag {
public:
 
    ArrayBag();

    virtual ~ArrayBag() = default;

    int getCurrentSize() const;

    bool isEmpty() const;

    bool add(const ItemType& newEntry);

    bool remove(const ItemType& anEntry);

    void clear();

    bool contains(const ItemType& anEntry) const;

    int getFrequencyOf(const ItemType& anEntry) const;

    std::vector<ItemType> toVector() const;

protected:
    static const int DEFAULT_CAPACITY = 20;
    ItemType items_[DEFAULT_CAPACITY];
    int item_count_;

    int getIndexOf(const ItemType& target) const;
};

#include "ArrayBag.cpp"
#endif 