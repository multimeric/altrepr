#include <Rcpp.h>
#include "altrep.hpp"
using namespace Rcpp;

bool _is_deferred_string(RObject x){
  if (!_is_altrep(x)){
    return FALSE;
  }
  String name(alt_classname(x)[0]);
  return name == "deferred_string";
}

void _assert_deferred(RObject x){
  if (!_is_deferred_string(x)){
    stop("Not a deferred string!");
  }
}

//' Checks for deferred string ALTREPs
//' @export
// [[Rcpp::export]]
LogicalVector is_deferred_string(RObject x){
  return {_is_deferred_string(x)};
}

//' Checks is a deferred string has been expanded
//' @export
// [[Rcpp::export]]
LogicalVector deferred_is_expanded(RObject x){
  _assert_deferred(x);
  return alt_data1(x) == R_NilValue;
}


//' Forces a deferred string into extended form
//'
//' @export
//' @examples
//' x = as.character(1:3)
//' deferred_expand(x)
//' alt_inspect(x)
// [[Rcpp::export]]
RObject deferred_expand(RObject x){
  _assert_deferred(x);
  alt_touch_dataptr(x);
  return x;
}

//' @export
// [[Rcpp::export]]
RObject deferred_expand_elt(RObject x, NumericVector i){
  _assert_deferred(x);
  // auto idx = i[0];
  STRING_ELT(x, 0);
  return R_NilValue;
}
