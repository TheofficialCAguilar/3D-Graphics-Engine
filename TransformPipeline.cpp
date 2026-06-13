// Carlos Aguilar

#include "TransformPipeline.hpp"
 
void TransformPipeline::enqueueTransform(Transformation* transform) {
    insert(itemCount_ + 1, transform);
}
 

void TransformPipeline::processNextTransform(Vector3D& point) {
    if (isEmpty()) {
        return;
    }
 
    Transformation* first = getEntry(1);
    point = first->apply(point);
    remove(1);
    delete first;
}
 

void TransformPipeline::runFullPipeline(Vector3D& point) {
    int length = getLength();
    for (int i = 1; i <= length; i++) {
        point = getEntry(i)->apply(point);
    }
}
 

void TransformPipeline::reversePipeline() {
    if (itemCount_ <= 1) {
        return;
    }
 
    Node<Transformation*>* prev    = nullptr;
    Node<Transformation*>* current = headPtr_;
    Node<Transformation*>* next    = nullptr;
 
    while (current != nullptr) {
        next = current->getNext();
        current->setNext(prev);
        prev = current;
        current = next;
    }
 
    headPtr_ = prev;
}
 

int TransformPipeline::removeTransformationsOfType(const std::string& type) {
    int removed = 0;
    int i = 1;
 
    while (i <= getLength()) {
        Transformation* t = getEntry(i);
        if (t->getType() == type) {
            remove(i);
            delete t;
            removed++;
        } else {
            i++;
        }
    }
 
    return removed;
}
