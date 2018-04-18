/*************************************************************************************************
 *
 * Modeling and animation (TNM079) 2007
 * Code base for lab assignments. Copyright:
 *   Gunnar Johansson (gunnar.johansson@itn.liu.se)
 *   Ken Museth (ken.museth@itn.liu.se)
 *   Michael Bang Nielsen (bang@daimi.au.dk)
 *   Ola Nilsson (ola.nilsson@itn.liu.se)
 *   Andreas Sˆderstrˆm (andreas.soderstrom@itn.liu.se)
 *
 *************************************************************************************************/
#include "Quadric.h"

Quadric::Quadric(const Matrix4x4<float> &q) { this->mQuadric = q; }

Quadric::~Quadric() {}

/*!
 * Evaluation of world coordinates are done through either transformation
 * of the world-coordinates by mWorld2Obj, or transformation of the quadric
 * coefficient matrix by GetTransform() ONCE (see Section 2.2 in lab text).
 */
float Quadric::GetValue(float x, float y, float z) const { 
	Matrix4x4<float> Q = GetTransform()*mQuadric;

	Vector4<float> p = { x, y, z, 1.0f };
	
	return (p * (Q * p)); 
}

/*!
 * Use the quadric matrix to evaluate the gradient.
 */
Vector3<float> Quadric::GetGradient(float x, float y, float z) const {
	Matrix4x4<float> Q = GetTransform()*mQuadric;
	Vector4<float> p = { x, y, z, 1.0f };

	Matrix4x4<float> Q_sub = Q;
	Q_sub(3, 0) = Q_sub(3, 1) = Q_sub(3, 2) = 0;
	Q_sub(3, 3) = 1;

	Vector4<float> temp = 2 * (Q_sub * p);

  return Vector3<float>(temp[0], temp[1], temp[2]);
}
