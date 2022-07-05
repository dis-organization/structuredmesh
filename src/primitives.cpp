#include <cpp11.hpp>
using namespace cpp11;

namespace writable = cpp11::writable;

[[cpp11::register]]
integers quad_ib(int nx, int ny, bool ydown) {
  int len;
  int nc1;
  len = (nx) * (ny) * 4;
  nc1 = nx + 1L; // nx columns
  //int nr1 = ny[0] + 1; // ny rows
  writable::integers quad(len);
  int bl, br, tr, tl; // bottom left, bottom right, top left, top right
  int count = 0;
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      bl = i + j * nc1;
      br = i + 1 + j * nc1;
      tr = br + nc1;
      tl = bl + nc1;
      if (ydown) {
        // this is confusing but corner orientation is taken from R image() plot
        quad[count + 0 ] = bl;
        quad[count + 1] = tl;
        quad[count + 2] = tr;
        quad[count + 3] = br;
        count = count + 4;

      } else {
        quad[count] = bl;
        quad[count + 1] = br;
        quad[count + 2] = tr;
        quad[count + 3] = tl;
        count = count + 4;
      }
    }
  }
  return quad;
}



// flesh out x and y coordinates at edges of 2D array of nx*ny quads
[[cpp11::register]]
doubles quad_vb(int nx, int ny,
                              bool ydown,
                              bool zh) {
     int nc1 = nx + 1;  // column edges
     int nr1 = ny + 1;  // row edges
     int nrow = 2;
     if (zh) {
       nrow = 4;
     }
     double len = nc1 * nr1 * nrow; // total length of output
     int count = 0;   // ease chunking through loop
     // output vector
     writable::doubles vertex(len);

     // step size from 0 to 1
     double dx = 1/(double)nx;
     double dy = 1/(double)ny;

     double ystart = 0;  // so we can ydown start at 1 and -dy
     if (ydown) {
       ystart = 1;
       dy = -dy;
     }
     // the 1D arrays across each margin, we calculate them first then expand-xy
     writable::doubles xx(nc1);
     writable::doubles yy(nr1);
     for (int jj = 0; jj < nr1; jj++) {
         // increment columns first
         for (int ii = 0; ii < nc1; ii++) {
           vertex[count + 0] = ii * dx; //xx[ii];
           vertex[count + 1] = ystart + jj * dy; //yy[jj];
           if (zh) {
             vertex[count + 2] = 0; // z constant
             vertex[count + 3] = 1; // h constant

           }
           count = count + nrow;
         }
    }
   return vertex;
 }
