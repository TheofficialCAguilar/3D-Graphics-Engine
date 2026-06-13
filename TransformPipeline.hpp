/*
@file TransformPipeline.hpp
@name Carlos Aguilar
@date 04/21/2026
@brief Declaration of the TransformPipeline class, which stores and organizes
Transformation objects in a linked list for sequential processing.
*/

#ifndef TRANSFORM_PIPELINE_HPP
#define TRANSFORM_PIPELINE_HPP
 
#include "LinkedList.hpp"
#include "Transformation.hpp"
#include "Vector3D.hpp"
#include <string>
 
class TransformPipeline : public LinkedList<Transformation*> {
public:
      /**
     * @param transform: A pointer to a Transformation object.
     * @post: The transformation is appended to the end of the pipeline.
     */
    
    void enqueueTransform(Transformation* transform);
     /**
     * @param point: A reference to a Vector3D to be transformed.
     * @post: The first transformation is applied to the point, removed from the pipeline, and deleted.
     *        If the pipeline is empty, the point is unchanged.
     */

    void processNextTransform(Vector3D& point);
      /**
     * @param point: A reference to a Vector3D to be transformed.
     * @post: All transformations are applied to the point sequentially.
     *        The pipeline remains unchanged.
     */

    void runFullPipeline(Vector3D& point);
     /**
     * @post: The order of all transformations in the pipeline is reversed.
     *        Example: [T1 -> T2 -> S1] becomes [S1 -> T2 -> T1]
     */

    void reversePipeline();
    /**
     * @param type: The string type to remove (e.g., "SCALE" or "TRANSLATE").
     * @post: All transformations matching the given type are removed from the pipeline and deleted.
     * @return: The number of transformations removed.
     */

    int removeTransformationsOfType(const std::string& type);
};
 
#endif 

