
#ifndef _DECIMATION_INTERFACE
#define _DECIMATION_INTERFACE

#include <cstddef>

class DecimationInterface
{
public :
  DecimationInterface() { }
  virtual ~DecimationInterface() { }

  virtual bool decimate() = 0;

  virtual bool decimate(size_t targetFaces) = 0;


};

#endif
