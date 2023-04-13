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
//' @return Logical scalar. `TRUE` if `x` is a deferred_string ALTREP,
//'   otherwise `FALSE`
//' @inheritParams is_altrep
//' @export
//' @examples
//' is_deferred_string("hi")
//' is_deferred_string(as.character(1))
// [[Rcpp::export]]
LogicalVector is_deferred_string(RObject x){
  return {_is_deferred_string(x)};
}

//' Checks is a deferred string has been expanded
//'
//' See [deferred_expand()] to force a deferred string to expand.
//' @param x Character vector with the `deferred_string` ALTREP class
//' @return Logical scalar. `TRUE` if `x` has been expanded, otherwise `FALSE`.
//' @export
//' @examples
//' x <- as.character(1)
//' deferred_is_expanded(x)
//' deferred_expand(x)
//' deferred_is_expanded(x)
// [[Rcpp::export]]
LogicalVector deferred_is_expanded(RObject x){
  _assert_deferred(x);
  return alt_data1(x) == R_NilValue;
}

//' Forces a deferred string into extended form
//' @export
//' @inheritParams deferred_is_expanded
//' @return `x`, not a copy of `x`, after expansion.
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
