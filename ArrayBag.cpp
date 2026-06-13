// Carlos Aguilar

#include "ArrayBag.hpp"
#include <vector>

template<class ItemType>
ArrayBag<ItemType>::ArrayBag() : item_count_(0) {}

template<class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const {
    return item_count_;
}

template<class ItemType>
bool ArrayBag<ItemType>::isEmpty() const {
    return item_count_ == 0;
}

template<class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newEntry) {
    if (item_count_ < DEFAULT_CAPACITY) {
        items_[item_count_] = newEntry;
        item_count_++;
        return true;
    }
    return false;
}

template<class ItemType>
std::vector<ItemType> ArrayBag<ItemType>::toVector() const {
    std::vector<ItemType> bagContents;
    for (int i = 0; i < item_count_; i++) {
        bagContents.push_back(items_[i]);
    }
    return bagContents;
}

template<class ItemType>
void ArrayBag<ItemType>::clear() {
    item_count_ = 0;
}

template<class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anEntry) {
	int target = getIndexOf(anEntry);
	if (target == -1) return false;
	
	item_count_--;
	items_[target] = std::move(items_[item_count_]);

	return true;
}

template<class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anEntry) const {
	return getIndexOf(anEntry) != -1;
}

template<class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const {
	int freq = 0;
    for (int i = 0; i < item_count_; i++) {
        if (items_[i] == anEntry)
            freq++;
    }
    return freq;
}

template<class ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType& target) const {
	for (int i = 0; i < item_count_; i++) {
		if (items_[i] == target) return i;
	}
	return -1;
}
 