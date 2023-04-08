#include <Rcpp.h>
using namespace Rcpp;

//' Expands a compact vector, setting the value of its `data2` to a standard
//' representation vector
// [[Rcpp::export]]
RObject expand(RObject x){
  DATAPTR(x);
  return x;
}
