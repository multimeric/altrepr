#include <Rcpp.h>
#include "altrep.hpp"
using namespace Rcpp;

Function identical("identical");

bool _is_compact_vec(RObject x){
  if (!_is_altrep(x)){
    return FALSE;
  }
  String name(alt_classname(x)[0]);
  switch (x.sexp_type()){
  case INTSXP:
    return name == "compact_intseq";
  case REALSXP:
    return name == "compact_realseq";
  }
  return FALSE;
}

//' Checks for compact vector ALTREPs
//' @export
// [[Rcpp::export]]
LogicalVector is_compact_vec(RObject x){
  return {_is_compact_vec(x)};
}

void _assert_compact(RObject x){
  if (!_is_compact_vec(x)){
    stop("Not a compact vector!");
  }
}

bool _compact_is_expanded(RObject x){
  _assert_compact(x);
  if (alt_data2(x) == R_NilValue){
    return false;
  }
  return true;
}

//' Forces a compact vector into extended form
//'
//' This will allocate the entire vector as a standard representation vector,
//' and store it in the `data2` slot.
//' @export
//' @examples
//' x = 1:3
//' compact_expand(x)
//' alt_inspect(x)
// [[Rcpp::export]]
RObject compact_expand(RObject x){
  _assert_compact(x);
  alt_touch_dataptr(x);
  return x;
}

//' Checks if a compact vector has been expanded
//' @return A logical scalar. `TRUE` if the vector is expanded, `FALSE` if it
//'   is compact
//' @export
// [[Rcpp::export]]
LogicalVector compact_is_expanded(RObject x){
  return _compact_is_expanded(x);
}

//' @export
// [[Rcpp::export]]
IntegerVector compact_fields(RObject x){
  _assert_compact(x);
  IntegerVector data = as<IntegerVector>(alt_data1(x));
  data.names() = CharacterVector{"length", "start", "step"};
  return data;
}

//' @export
// [[Rcpp::export]]`
RObject compact_to_standard(RObject x){
  _assert_compact(x);
  return clone(x);
 }

