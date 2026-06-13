/**
 * @file ArrayBag.hpp
 * @author [Your Name]
 * @date [Current Date]
 * @brief Header file for an array-based implementation of the ADT Bag.
 */

#ifndef ARRAY_BAG_HPP
#define ARRAY_BAG_HPP

#include <vector>
#include <cstddef>

template<class ItemType>
class ArrayBag {
public:
    /**
     * @post: Initializes item_count_ to 0.
     */
    ArrayBag();

    /**
     * @brief Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~ArrayBag() = default;

    /**
     * @return: The current number of items in the bag.
     */
    int getCurrentSize() const;

    /**
     * @return: True if the bag is empty (item_count_ == 0), false otherwise.
     */
    bool isEmpty() const;

    /**
     * @param newEntry: The item to add to the bag.
     * @return: True if the item was successfully added, false if the bag is full.
     * @post: Adds the item to the bag if there is room.
     */
    bool add(const ItemType& newEntry);

    /**
     * @param anEntry: The item to remove from the bag.
     * @return: True if the item was successfully removed, false if it was not found.
     * @post: Removes one occurrence of anEntry from the bag.
     */
    bool remove(const ItemType& anEntry);

    /**
     * @post: Sets item_count_ to 0, effectively clearing the bag.
     */
    void clear();

    /**
     * @param anEntry: The item to search for.
     * @return: True if the item is found in the bag, false otherwise.
     */
    bool contains(const ItemType& anEntry) const;

    /**
     * @param anEntry: The item to count.
     * @return: The number of times anEntry appears in the bag.
     */
    int getFrequencyOf(const ItemType& anEntry) const;

    /**
     * @return: A vector containing all items currently in the bag.
     */
    std::vector<ItemType> toVector() const;

protected:
    static const int DEFAULT_CAPACITY = 20;
    ItemType items_[DEFAULT_CAPACITY];
    int item_count_;

    /**
     * @param target: The item to search for.
     * @return: The index of the first occurrence of target, or -1 if not found.
     */
    int getIndexOf(const ItemType& target) const;
};

#include "ArrayBag.cpp"
#endif