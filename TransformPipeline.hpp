// Carlos Aguilar

#ifndef TRANSFORM_PIPELINE_HPP
#define TRANSFORM_PIPELINE_HPP
 
#include "LinkedList.hpp"
#include "Transformation.hpp"
#include "Vector3D.hpp"
#include <string>
 
class TransformPipeline : public LinkedList<Transformation*> {
public:

    void enqueueTransform(Transformation* transform);

    void processNextTransform(Vector3D& point);

    void runFullPipeline(Vector3D& point);

    void reversePipeline();

    int removeTransformationsOfType(const std::string& type);
};
 
#endif 

