
#include "UniformCubicSplineSubdivisionCurve.h"

UniformCubicSplineSubdivisionCurve::UniformCubicSplineSubdivisionCurve(
    const std::vector<Vector3<float>> &joints, Vector3<float> lineColor,
    float lineWidth)
    : mCoefficients(joints), mControlPolygon(joints) {
  this->mLineColor = lineColor;
  this->mLineWidth = lineWidth;
}

void UniformCubicSplineSubdivisionCurve::Subdivide() {
  // Allocate space for new coefficients
  std::vector<Vector3<float>> newc;

  assert(mCoefficients.size() > 4 && "Need at least 5 points to subdivide");
  
  // Implement the subdivision scheme for a natural cubic spline here
  for (int i = 0; i < mCoefficients.size(); i++) {
	  if (i == 0) {
		  newc.push_back(mCoefficients[i]);
		  newc.push_back((4.0f * mCoefficients[i] + 4.0f * mCoefficients[i + 1]) / 8.0f);
	  }
	  else if (i == mCoefficients.size() - 1) {
		  newc.push_back(mCoefficients[i]);
	  }
	  else {
		  newc.push_back((mCoefficients[i - 1] + 6.0f * mCoefficients[i] + mCoefficients[i + 1]) / 8.0f);
		  newc.push_back((4.0f * mCoefficients[i] + 4.0f * mCoefficients[i + 1]) / 8.0f);
	  }
  }
  // If 'mCoefficients' had size N, how large should 'newc' be? Perform a check
  // here!
  assert(true && "Incorrect number of new coefficients!");

  mCoefficients = newc;
}

void UniformCubicSplineSubdivisionCurve::Render() {
  // Apply transform
  glPushMatrix(); // Push modelview matrix onto stack

  // Convert transform-matrix to format matching GL matrix format
  // Load transform into modelview matrix
  glMultMatrixf(mTransform.ToGLMatrix().GetArrayPtr());

  mControlPolygon.Render();

  // save line point and color states
  glPushAttrib(GL_POINT_BIT | GL_LINE_BIT | GL_CURRENT_BIT);

  // draw segments
  glLineWidth(mLineWidth);
  glColor3fv(mLineColor.GetArrayPtr());
  glBegin(GL_LINE_STRIP);
  // just draw the spline as a series of connected linear segments
  for (size_t i = 0; i < mCoefficients.size(); i++) {
    glVertex3fv(mCoefficients.at(i).GetArrayPtr());
  }
  glEnd();

  // restore attribs
  glPopAttrib();

  glPopMatrix();

  GLObject::Render();
}
