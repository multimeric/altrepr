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

//' Checks for compact sequence ALTREPs
//' @param x Any R object
//' @return A scalar logical. `TRUE` if `x` is a compact sequence, otherwise
//'  `FALSE`
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
//' Note: this modifies `x` in-place, so will modify any copies of `x`, and
//' is irreversible.
//' @return `x`, **not a copy of `x`**
//' @param x An ALTREP vector of class `compact_realseq` or `compact_intseq`
//' @export
//' @examples
//' x = 1:3
//' compact_expand(x)
//' compact_details(x)
// [[Rcpp::export]]
RObject compact_expand(RObject x){
  _assert_compact(x);
  alt_touch_dataptr(x);
  return x;
}

//' Checks if a compact vector has been expanded
//' @inheritParams compact_expand
//' @return A logical scalar. `TRUE` if the vector is expanded, `FALSE` if it
//'   is compact
//' @export
// [[Rcpp::export]]
LogicalVector compact_is_expanded(RObject x){
  return _compact_is_expanded(x);
}

//' Returns a list containing the fields of a compact vector
//' @inheritParams compact_expand
//' @return A list with the elements:
//'   * `length` (integer scalar): the length of the sequence
//'   * `start` (integer scalar): the first value of the sequence
//'   * `step` (integer scalar) : the increment between entries in the sequence
//'   * `expanded` (double, integer vector, or `NULL`): a non-ALTREP version of
//'      `x`, or `NULL` if it hasn't been expanded
//' @export
// [[Rcpp::export]]
List compact_details(RObject x){
  _assert_compact(x);
  IntegerVector data = as<IntegerVector>(alt_data1(x));
  return List::create(
    Named("length") = data[0],
    Named("start") = data[1],
    Named("step") = data[2],
    Named("expanded") = alt_data2(x)
  );
}

//' Returns a non-ALTREP copy of a compact vector
//' @inheritParams compact_expand
//' @export
//' @examples
//' compact_to_standard(1:5)
// [[Rcpp::export]]
RObject compact_to_standard(RObject x){
  _assert_compact(x);
  return clone(x);
 }

