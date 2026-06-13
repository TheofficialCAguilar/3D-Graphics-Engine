/*
@file TransformPipeline.cpp
@name Carlos Aguilar
@date 04/21/2026
@brief Implementation of the TransformPipeline class, which manages and applies
a sequence of 3D transformations using a linked list.
*/

#include "TransformPipeline.hpp"
 
/**
 * @param transform: A pointer to a Transformation object.
 * @post: The transformation is appended to the end of the pipeline.
 */

void TransformPipeline::enqueueTransform(Transformation* transform) {
    insert(itemCount_ + 1, transform);
}
 
/**
 * @param point: A reference to a Vector3D to be transformed.
 * @post: The first transformation is applied to the point, removed from the pipeline, and deleted.
 *        If the pipeline is empty, the point is unchanged.
 */

void TransformPipeline::processNextTransform(Vector3D& point) {
    if (isEmpty()) {
        return;
    }
 
    Transformation* first = getEntry(1);
    point = first->apply(point);
    remove(1);
    delete first;
}
 
/**
 * @param point: A reference to a Vector3D to be transformed.
 * @post: All transformations are applied to the point sequentially.
 *        The pipeline remains unchanged.
 */

void TransformPipeline::runFullPipeline(Vector3D& point) {
    int length = getLength();
    for (int i = 1; i <= length; i++) {
        point = getEntry(i)->apply(point);
    }
}
 
/**
 * @post: The order of all transformations in the pipeline is reversed.
 *        Example: [T1 -> T2 -> S1] becomes [S1 -> T2 -> T1]
 */

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
 
/**
 * @param type: The string type to remove (e.g., "SCALE" or "TRANSLATE").
 * @post: All transformations matching the given type are removed from the pipeline and deleted.
 * @return: The number of transformations removed.
 */

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
