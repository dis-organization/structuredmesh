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
            quad[count + 3] = bl;
            quad[count + 2] = br;
            quad[count + 1] = tr;
            quad[count + 0] = tl;
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
