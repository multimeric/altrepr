#include <Rcpp.h>
using namespace Rcpp;

bool _is_altrep(RObject x){
  return bool(ALTREP(x));
}

Pairlist _all_attribs(RObject x){
  return ATTRIB(x);
}

//' Gets the altrep class of an object.
//'
//' The altrep class is not the same as the name of the class. For that,
//' you can use [alt_classname()]. The altrep class is a [raw] vector whose
//' value uniquely distinguishes the class from other classes. You are unlikely
//' to find much meaning in the actual vector values, but you might find it
//' useful to check if two objects belong to the same class.The other
//' meaningful use of the class is to check its [attributes()], but it is
//' recommended that you instead use the three dedicated wrapper functions for
//' these attributes: [alt_classname()], [alt_pkgname()], and [alt_type()].
//'
//' @return A raw vector uniquely identifying the altrep class of `x`, or `NULL`
//'   if `x` is not an altrep object.
//' @seealso [alt_classname()] [alt_pkgname()] [alt_type()]
//' @examples
//' identical(alt_class(1:2), alt_class(2:3))
// [[Rcpp::export]]
RawVector alt_class(RObject x){
  return ALTREP_CLASS(x);
}

//' Gets the name of the altrep class of an object
//'
//' This is a a human-readable name for the altrep class.
//'
//' @return The class name as a [name()] (**not** a character), or `NULL` if
//'   `x` is not an altrep object.
//' @examples
//' alt_classname(1:3)
// [[Rcpp::export]]
RObject alt_classname(RObject x){
  if (_is_altrep(x)){
    return _all_attribs(alt_class(x))[0];
  }
  return R_NilValue;
}

//' Gets the package in which an altrep class was defined
//'
//' Specifically this finds the package in which the altrep class, which may
//' not be the same as the S3/S4 [class()], was defined.
//' @return The package name as a [name()], or `NULL` if `x` is not an altrep
//'   object.
//' @examples
//' alt_pkgname(1:3)
// [[Rcpp::export]]
RObject alt_pkgname(RObject x){
  if (_is_altrep(x)){
    return _all_attribs(alt_class(x))[1];
  }
  return R_NilValue;
}

//' Gets the name of
// [[Rcpp::export]]
RObject alt_type(RObject x){
  if (_is_altrep(x)){
    return Rf_type2rstr((_all_attribs(alt_class(x))[2]));
  }
  return R_NilValue;
}

// [[Rcpp::export]]
LogicalVector is_altrep(RObject x){
    return {_is_altrep(x)};
}

// [[Rcpp::export]]
RObject altrep_data1(RObject x){
  return R_altrep_data1(x);
}

// [[Rcpp::export]]
RObject altrep_data2(RObject x){
  return R_altrep_data2(x);
}

