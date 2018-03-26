#include "Cube.h"

Cube::Cube() {
  Vector3<float> lowP(-1.1f, -1.1f, -1.1f);
  Vector3<float> highP(1.1f, 1.1f, 1.1f);
  SetBoundingBox(Bbox(lowP, highP));

  Matrix4x4<float> matrix;
  matrix(0, 0) = 0.0;
  matrix(1, 1) = 0.0;
  matrix(2, 2) = 0.0;
  matrix(3, 3) = 0.0;

  matrix(0, 3) = 0.0;
  matrix(1, 3) = 0.5;
  matrix(2, 3) = 0.0;

  // Plane 1
  Quadric *q = new Quadric(matrix);
  q->Translate(0.0f, 0.5f, 0.0f);
  q->SetBoundingBox(Bbox(lowP, highP));
  mPlanes.push_back(q);

  // Plane 2
  matrix(0, 3) = 0.0f;
  matrix(1, 3) = -0.5f;
  matrix(2, 3) = 0.0f;
  q = new Quadric(matrix);
  q->Translate(0.0f, -0.5f, 0.0f);
  q->SetBoundingBox(Bbox(lowP, highP));
  mPlanes.push_back(q);

  // Plane 3
  matrix(0, 3) = 0.5f;
  matrix(1, 3) = 0.0f;
  matrix(2, 3) = 0.0f;
  q = new Quadric(matrix);
  q->Translate(0.5f, 0.0f, 0.0f);
  q->SetBoundingBox(Bbox(lowP, highP));
  mPlanes.push_back(q);

  // Plane 4
  matrix(0, 3) = -0.5f;
  matrix(1, 3) = 0.0f;
  matrix(2, 3) = 0.0f;
  q = new Quadric(matrix);
  q->Translate(-0.5f, 0.0f, 0.0f);
  q->SetBoundingBox(Bbox(lowP, highP));
  mPlanes.push_back(q);

  // Plane 5
  matrix(0, 3) = 0.0f;
  matrix(1, 3) = 0.0f;
  matrix(2, 3) = 0.5f;
  q = new Quadric(matrix);
  q->Translate(0.0f, 0.0f, 0.5f);
  q->SetBoundingBox(Bbox(lowP, highP));
  mPlanes.push_back(q);

  // Plane 6
  matrix(0, 3) = 0.0f;
  matrix(1, 3) = 0.0f;
  matrix(2, 3) = -0.5f;
  q = new Quadric(matrix);
  q->Translate(0.0f, 0.0f, -0.5f);
  q->SetBoundingBox(Bbox(lowP, highP));
  mPlanes.push_back(q);
}

Cube::~Cube() {
  for (size_t i = 0; i < mPlanes.size(); i++) {
    delete mPlanes[i];
  }
}

float Cube::GetValue(float x, float y, float z) const {
  TransformW2O(x, y, z);

  float value = mPlanes[0]->GetValue(x, y, z);
  for (size_t i = 1; i < mPlanes.size(); i++) {
    value = std::max(value, mPlanes[i]->GetValue(x, y, z));
  }

  return value;
}
