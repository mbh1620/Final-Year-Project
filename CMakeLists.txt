cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

foreach(p
CMP0071
)

if(POLICY ${p}) 
cmake_policy(SET ${p} NEW)
endif() 
endforeach()
PROJECT( EdgeCollapse )

set(CPack_GENERATOR "DragNDrop") #CPack Generator set to the standard MacOs installer drag and Drop

include(CPack)

include(CTest)

set( CMAKE_INCLUDE_CURRENT_DIR ON)


add_library( edge_collapse_libs ./Classes/Vertex/Vertex.cpp
								./Classes/Triangle/Triangle.cpp
								./Classes/ReadWriter/ReadWriter.cpp
								./Classes/Vector3D/Vector3D.cpp
								./Classes/Cluster/Cluster.cpp
								./Classes/Material/Material.cpp
								./Classes/Edge/Edge.cpp
)

add_executable( EdgeCollapse MACOSX_BUNDLE ./Classes/Cluster/ClusterTest.cpp)

