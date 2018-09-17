# TNM079-Labs
Labs for the course TNM079 Modelling and Animation. 

#### Lab 1: Mesh data structures
The aim of this lab was to learn about the half-edge mesh data structure and the attributes of a mesh. 
Using the half-edge mesh data structure makes algorithms that need neighboring information much more efficient, 
for example when you need to calculate the vertex normals to be able to use them for Phong shading. With the use 
of this data structure the following attributes were calculated for a mesh: the vertex normals, the surface area, 
the volume, the curvature (both Gaussian and mean) and the genus.

#### Lab 2: Mesh Decimation
The purpose of the lab was to implement the error metric quadric presented by Garland and Heckbert to be used to 
calculate the cost of removing a vertex during mesh decimation and where the new position should be. The algorithm 
computing the cost and the position takes the appearance of the mesh into account. It keeps the overall details since 
it will always choose the best position for the new vertex with the lowest cost. The error metric was found to be very good, 
especially compared to another error metric where the new position was in the middle of the collapsed edge and the cost 
was the distance moved. 

#### Lab 3: Splines and Subdivision
The purpose of this lab was to get acquainted with spines and use them for subdivision of curves and meshes. 
The following things was learned from this lab: how to implement curve subdivision using cubic splines, how to implement Loop's 
algorithm for subdivision of meshes and how to optimize the calculations of the splines by localizing the evaluations to only 
use the ones that make a difference. The different algorithms used for subdivision was found to be very good and gave a smooth result.
The optimization made minimized the evaluation call from 4000 times to 2397 times.

#### Lab 4: Implicit Surfaces and Modeling
This lab handles implicit surfaces in computer graphics. It brings up how constructive solid geometry (CSG) operators works, 
how it is possible to find the value and the gradient of a point on a quadric surface and how to calculate the gradient and 
the curvature of a general implicit surface.

#### Lab 5: Level-Set Methods
The aim of this lab was to learn more about levelset functions. How an implicit surface can be transformed using partial 
differential equations. Four different transformations were implemented: erosion, dilation, advection from an external vector 
field and smoothing using the mean curvature flow. All transformations worked as expected. The lab also contained how to implement 
the different derivatives that was needed for the transformations and how the signed distance function is correlated to the 
levelset function. 

#### Lab 6: Fluid Simulation
Simulations of fluids such as water or fire have become something very common in the visual effect business. This lab was about 
learning how to simulate water using the Navier-Stokes equations. Functionality such as external forces, the Dirichlet boundary 
condition, volume conservation and semi-Lagrangian self advection was implemented.
