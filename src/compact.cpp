#include <Rcpp.h>
using namespace Rcpp;

//' Expands a compact vector, setting the value of its `data2` to a standard
//' representation vector
//' @export
//' @examples
//' x = 1:3
//' compact_expand(x)
//' alt_inspect(x)
// [[Rcpp::export]]
RObject compact_expand(RObject x){
  DATAPTR(x);
  return x;
}
