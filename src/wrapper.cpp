#include <Rcpp.h>
#include "altrep.hpp"
using namespace Rcpp;

bool _is_wrapper(RObject x){
  if (!_is_altrep(x)){
    return FALSE;
  }
  std::string name = as<std::string>(alt_classname(x)[0]);
  return name.substr(0, 5) == "wrap_";
}

void _assert_wrapper(RObject x){
  if (!_is_wrapper(x)){
    stop("Not a wrapper!");
  }
}

//' @export
// [[Rcpp::export]]
List wrapper_details(RObject x){
  _assert_wrapper(x);
  IntegerVector data2 = as<IntegerVector>(alt_data2(x));
  RObject is_sorted;
  RObject descending;
  RObject na_first;

  switch(data2[0]){
    case SORTED_DECR_NA_1ST: {
      is_sorted = true;
      descending = true;
      na_first = true;
      break;
    }
    case SORTED_DECR: {
      is_sorted = true;
      descending = true;
      na_first = false;
      break;
    }
    case SORTED_INCR_NA_1ST: {
      is_sorted = true;
      descending = false;
      na_first = true;
      break;
    }
    case SORTED_INCR: {
      is_sorted = true;
      descending = false;
      na_first = false;
      break;
    }
    case KNOWN_UNSORTED: {
      is_sorted = false;
      descending = R_NilValue;
      na_first = R_NilValue;
      break;
    }
    case UNKNOWN_SORTEDNESS: {
      is_sorted = R_NilValue;
      descending = R_NilValue;
      na_first = R_NilValue;
      break;
    }
  }

  return List::create(
    Named("contents") = alt_data1(x),
    Named("has_na") = LogicalVector{(bool(data2[1]))},
    Named("is_sorted") = is_sorted,
    Named("descending") = descending,
    Named("na_first") = na_first
  );
}
