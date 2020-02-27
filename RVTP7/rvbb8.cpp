#include "rvbb8.h"

RVBB8::RVBB8()
    :RVModel ("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/bb8.obj")
{
    m_meshes[0]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/HEAD diff MAP.jpg");
    m_meshes[1]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/Head ring diff MAP.jpg");
    m_meshes[2]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/Head ring diff MAP.jpg");
    m_meshes[3]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/Head ring MAP.jpg");
    m_meshes[4]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/Head top diff MAP.jpg");
    m_meshes[5]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/Head top diff MAP.jpg");
    m_meshes[6]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/Body diff MAP.jpg");

}

void RVBB8::draw(){

//    m_meshes[0]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/HEAD_diff_MAP.jpg");

   for(RVMesh* meches : m_meshes){
       meches->draw();
   }
}
