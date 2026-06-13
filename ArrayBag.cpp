/**
 * @file ArrayBag.cpp
 * @author [Your Name]
 * @date [Current Date]
 * @brief Implementation of the ArrayBag template class methods.
 */

#include "ArrayBag.hpp"
#include <vector>

/**
 * @post: Initializes item_count_ to 0.
 */
template<class ItemType>
ArrayBag<ItemType>::ArrayBag() : item_count_(0) {}

/**
 * @return: The current number of items in the bag.
 */
template<class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const {
    return item_count_;
}

/**
 * @return: True if the bag is empty (item_count_ == 0), false otherwise.
 */
template<class ItemType>
bool ArrayBag<ItemType>::isEmpty() const {
    return item_count_ == 0;
}

/**
 * @param newEntry: The item to add to the bag.
 * @return: True if the item was successfully added, false if the bag is full.
 * @post: Adds the item to the bag if there is room.
 */
template<class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newEntry) {
    if (item_count_ < DEFAULT_CAPACITY) {
        items_[item_count_] = newEntry;
        item_count_++;
        return true;
    }
    return false;
}

/**
 * @return: A vector containing all items currently in the bag.
 */
template<class ItemType>
std::vector<ItemType> ArrayBag<ItemType>::toVector() const {
    std::vector<ItemType> bagContents;
    for (int i = 0; i < item_count_; i++) {
        bagContents.push_back(items_[i]);
    }
    return bagContents;
}

/**
 * @post: Sets item_count_ to 0, effectively clearing the bag.
 */
template<class ItemType>
void ArrayBag<ItemType>::clear() {
    item_count_ = 0;
}

/**
 * @param anEntry: The item to remove from the bag.
 * @return: True if the item was successfully removed, false if it was not found.
 * @post: Removes one occurrence of anEntry from the bag.
 */
template<class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anEntry) {
	int target = getIndexOf(anEntry);
	if (target == -1) return false;
	
	item_count_--;
	items_[target] = std::move(items_[item_count_]);

	return true;
}

/**
 * @param anEntry: The item to search for.
 * @return: True if the item is found in the bag, false otherwise.
 */
template<class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anEntry) const {
	return getIndexOf(anEntry) != -1;
}

/**
 * @param anEntry: The item to count.
 * @return: The number of times anEntry appears in the bag.
 */
template<class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const {
	int freq = 0;
    for (int i = 0; i < item_count_; i++) {
        if (items_[i] == anEntry)
            freq++;
    }
    return freq;
}

/**
 * @param target: The item to search for.
 * @return: The index of the first occurrence of target, or -1 if not found.
 */
template<class ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType& target) const {
	for (int i = 0; i < item_count_; i++) {
		if (items_[i] == target) return i;
	}
	return -1;
}
