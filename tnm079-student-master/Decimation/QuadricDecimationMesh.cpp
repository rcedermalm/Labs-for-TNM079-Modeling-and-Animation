/*************************************************************************************************
 *
 * Modeling and animation (TNM079) 2007
 * Code base for lab assignments. Copyright:
 *   Gunnar Johansson (gunnar.johansson@itn.liu.se)
 *   Ken Museth (ken.museth@itn.liu.se)
 *   Michael Bang Nielsen (bang@daimi.au.dk)
 *   Ola Nilsson (ola.nilsson@itn.liu.se)
 *   Andreas Sderstrm (andreas.soderstrom@itn.liu.se)
 *
 *************************************************************************************************/
#include "QuadricDecimationMesh.h"

const QuadricDecimationMesh::VisualizationMode
    QuadricDecimationMesh::QuadricIsoSurfaces =
        NewVisualizationMode("Quadric Iso Surfaces");

void QuadricDecimationMesh::Initialize() {
  // Allocate memory for the quadric array
  size_t numVerts = mVerts.size();
  mQuadrics.reserve(numVerts);
  std::streamsize width = std::cerr.precision(); // store stream precision
  for (size_t i = 0; i < numVerts; i++) {

    // Compute quadric for vertex i here
    mQuadrics.push_back(createQuadricForVert(i));

    // Calculate initial error, should be numerically close to 0

    Vector3<float> v0 = mVerts[i].pos;
    Vector4<float> v(v0[0], v0[1], v0[2], 1);
    Matrix4x4<float> m = mQuadrics.back();

    float error = v * (m * v);
    // std::cerr << std::scientific << std::setprecision(2) << error << " ";
  }
  std::cerr << std::setprecision(width) << std::fixed; // reset stream precision

  // Run the initialize for the parent class to initialize the edge collapses
  DecimationMesh::Initialize();
}

/*! \lab2 Implement the computeCollapse here */
/*!
 * \param[in,out] collapse The edge collapse object to (re-)compute,
 * DecimationMesh::EdgeCollapse
 */
void QuadricDecimationMesh::computeCollapse(EdgeCollapse *collapse) { // -------------------------------------------------------------------------------------------------------------------------------- IT DOES NOT WORK, COW IS NO COW
  // Compute collapse->position and collapse->cost here
  // based on the quadrics at the edge endpoints
	Matrix4x4<float> Q = mQuadrics[mEdges[collapse->halfEdge].vert] + mQuadrics[mEdges[mEdges[collapse->halfEdge].pair].vert];
	Matrix4x4<float> Q_hat = Q;
	Q_hat(3, 0) = Q_hat(3, 1) = Q_hat(3, 2) = 0;
	Q_hat(3, 3) = 1;
	
	if (!Q_hat.IsSingular()) {
		Q_hat.Inverse();
		const Vector4<float> zero = { 0,0,0,1 };
		const Vector4<float> v_new = Q_hat * zero;
		const Vector3<float> pos_new = { v_new[0],v_new[1],v_new[2] };
		collapse->position = pos_new;
		collapse->cost = v_new*(Q*v_new);
	}		
	else {
		const Vector3<float> &v0 = mVerts[mEdges[collapse->halfEdge].vert].pos;
		const Vector3<float> &v1 = mVerts[mEdges[mEdges[collapse->halfEdge].pair].vert].pos;
		collapse->position = (v0 + v1) * 0.5;
		collapse->cost = (collapse->position - v0).Length();
	}
}

/*! After each edge collapse the vertex properties need to be updated */
void QuadricDecimationMesh::updateVertexProperties(size_t ind) {
  DecimationMesh::updateVertexProperties(ind);
  mQuadrics[ind] = createQuadricForVert(ind);
}

/*!
 * \param[in] indx vertex index, points into HalfEdgeMesh::mVerts
 */
Matrix4x4<float>
QuadricDecimationMesh::createQuadricForVert(size_t indx) const {
  float q[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  Matrix4x4<float> Q(q);

  // The quadric for a vertex is the sum of all the quadrics for the adjacent
  // faces Tip: Matrix4x4 has an operator +=
  std::vector<size_t> foundFaces = HalfEdgeMesh::FindNeighborFaces(indx);

  for (int i = 0; i < foundFaces.size(); i++) {
	  Q += createQuadricForFace(foundFaces[i]);
  }
  return Q;
}

/*!
 * \param[in] indx face index, points into HalfEdgeMesh::mFaces
 */
Matrix4x4<float>
QuadricDecimationMesh::createQuadricForFace(size_t indx) const {
	Vector3<float> v0 = v(e(mFaces[indx].edge).vert).pos;
	Vector3<float> normal = mFaces[indx].normal;
	float d = -(v0 * normal);
	Vector4<float> p = Vector4<float>(normal[0], normal[1], normal[2], d);
	Matrix4x4<float> k = calculateK(p);

	return k;
}

/*!
* \param[in] p point vector
*/
Matrix4x4<float> QuadricDecimationMesh::calculateK(Vector4<float> p) const {
	Matrix4x4<float> temp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp(i, j) = (p[i]*p[j]);
		}
	}
	return temp;
}

void QuadricDecimationMesh::Render() {
  DecimationMesh::Render();

  glEnable(GL_LIGHTING);
  glMatrixMode(GL_MODELVIEW);

  if (mVisualizationMode == QuadricIsoSurfaces) {
    // Apply transform
    glPushMatrix(); // Push modelview matrix onto stack

    // Implement the quadric visualization here
    std::cout << "Quadric visualization not implemented" << std::endl;

    // Restore modelview matrix
    glPopMatrix();
  }
}
