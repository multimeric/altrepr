#include <Rcpp.h>
#include "altrep.h"
using namespace Rcpp;

bool _is_wrapper(RObject x){
  if (!_is_altrep(x)){
    return FALSE;
  }
  std::string name = as<std::string>(alt_classname(x)[0]);
  return name.substr(0, 5) == "wrap_" &&
    as<std::string>(alt_pkgname(x)) == "base";
}

void _assert_wrapper(RObject x){
  if (!_is_wrapper(x)){
    stop("Not a wrapper!");
  }
}

//' Checks for wrapper object ALTREPs
//' @return Logical scalar. `TRUE` if `x` is a wrapper ALTREP,
//'   otherwise `FALSE`
//' @inheritParams is_altrep
//' @export
//' @examples
//' is_wrapper("5:1")
//' sort(5:1) |> is_wrapper()
// [[Rcpp::export]]
LogicalVector is_wrapper(RObject x){
  return {_is_wrapper(x)};
}

//' Returns a list containing the fields of a wrapper object
//' @param x Any R object belonging with a `wrap` ALTREP class
//' @return A list with the following entries:
//'   * `contents`: Any R object. The underlying object being wrapped
//'   * `has_na`: Logical scalar. `TRUE` if `contents` **might** contain
//'     `NA`, or `FALSE` if it **definitely doesn't**.
//'   * `is_sorted`: Logical scalar. `TRUE` if `contents` is sorted in any
//'     order
//'   * `descending`: Logical scalar. `TRUE` if `contents` is sorted in
//'     descending order, `FALSE` if it is sorted in ascending order, or
//'     `NA` if it isn't sorted or its sorting status is unknown.
//'   * `na_first` Logical scalar. `TRUE` if `contents` is sorted in an order
//'     that puts `NA` values first, `FALSE` if it is sorted last, or `NA`
//'     if `contents` is unsorted or its sorting status is unknown
//' @export
//' @examples
//' sort(5:1) |> wrapper_details()
// [[Rcpp::export]]
List wrapper_details(RObject x){
  _assert_wrapper(x);
  IntegerVector data2 = as<IntegerVector>(alt_data2(x));
  RObject is_sorted;
  RObject descending;
  RObject na_first;

  switch(data2[0]){
    case SORTED_DECR_NA_1ST: {
      is_sorted = LogicalVector{true};
      descending = LogicalVector{true};
      na_first = LogicalVector{true};
      break;
    }
    case SORTED_DECR: {
      is_sorted = LogicalVector{true};
      descending = LogicalVector{true};
      na_first = LogicalVector{false};
      break;
    }
    case SORTED_INCR_NA_1ST: {
      is_sorted = LogicalVector{true};
      descending = LogicalVector{false};
      na_first = LogicalVector{true};
      break;
    }
    case SORTED_INCR: {
      is_sorted = LogicalVector{true};
      descending = LogicalVector{false};
      na_first = LogicalVector{false};
      break;
    }
    case KNOWN_UNSORTED: {
      is_sorted = LogicalVector{false};
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
    Named("has_na") = LogicalVector{!bool(data2[1])},
    Named("is_sorted") = is_sorted,
    Named("descending") = descending,
    Named("na_first") = na_first
  );
}
