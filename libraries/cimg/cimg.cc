// This file exists mainly so that the libraries needed by CImg can be
// linked. This is a total hack at the moment.
// TODO(cmsweeney): Figure out a way around this.
#include "CImg.h"

// CImg includes X11 which has a macro that conflicts with an Eigen
// enum. Undefining this macro should not have any effect (hopefully!!).
#ifdef Success
  #undef Success
#endif
