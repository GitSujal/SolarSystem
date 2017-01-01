#ifndef GLGEOMETRY_H
#define GLGEOMETRY_H

#include <vector>


    class GLModel
    {
    public:
        std::vector<float> position;
        std::vector<float> color;
        std::vector<float> texcoord;
        std::vector<float> normal;
        
        long numVertices()
        {
            return position.size() / 3;
        }
        
        void PushVertex3(std::vector<float> &geometry, float x, float y, float z);
        void PushVertex2(std::vector<float> &geometry, float x, float y);
        
        void drawModel(GLModel);
        
        GLModel Gen2DMesh(int subdiv);
        GLModel GenSphere(int segments, int slices,int flag,float radius);
        GLModel GenCylinder(int segments, int slices);
        
    };





#endif