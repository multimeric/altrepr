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
//' @return The class name as a [character], or `NULL` if
//'   `x` is not an altrep object.
//' @examples
//' alt_classname(1:3)
// [[Rcpp::export]]
RObject alt_classname(RObject x){
  if (_is_altrep(x)){
    return as<CharacterVector>(_all_attribs(alt_class(x))[0]);
  }
  return R_NilValue;
}

//' Gets the package in which an ALTREP class was defined
//'
//' Specifically this finds the name of the package in which the altrep class
//' was defined. This is almost definitely not the same as the S3/S4 [class()],
//' was defined, which is likely to be one of the core vector types like
//' `integer`.
//' @return The package name as a [character], or `NULL` if `x` is not an altrep
//'   object.
//' @examples
//' alt_pkgname(1:3)
// [[Rcpp::export]]
RObject alt_pkgname(RObject x){
  if (_is_altrep(x)){
    return as<CharacterVector>(_all_attribs(alt_class(x))[1]);
  }
  return R_NilValue;
}

//' Gets the name of the type that this ALTREP is representing.
//'
//' This will almost certainly return the same result as `typeof(x)`, but
//' please let the author of this package know if it doesn't!
//' @return The name of the fundamental vector type of that `x` is representing,
//' as a [character] scalar. For example "integer" or "character".
//' @examples
//' alt_type(1:3)
// [[Rcpp::export]]
RObject alt_type(RObject x){
  if (_is_altrep(x)){
    return Rf_type2rstr((_all_attribs(alt_class(x))[2]));
  }
  return R_NilValue;
}

//' Checks if an R object is ALTREP
//'
//' This checks if `x` is an instance of an ALTREP class. Notably it doesn't
//' check if `x` **is** an ALTREP class, which is more difficult to achieve.
//' @return A scalar logical
//' @examples
//' is_altrep(1)
//' is_altrep(1:2)
// [[Rcpp::export]]
LogicalVector is_altrep(RObject x){
    return {_is_altrep(x)};
}

//' Gets the first altrep data slot
//'
//' ALTREP objects have two data slots, both of which can hold any R type.
//' The exact meaning of each slot can depend entirely on the ALTREP class and
//' how it wants to represent data.
//'
//' Although the exact meaning of each slot is flexible, a *convention* used in
//' R core is
//' for `data1` to hold the "compressed" state of a type, and for `data2` to
//' hold the "expanded" state. See the `compact_seq` vignette for more information
//' @return Possibly any R object, including `NULL`
//' @examples
//' alt_data1(1:3)
// [[Rcpp::export]]
RObject alt_data1(RObject x){
  return R_altrep_data1(x);
}

//' Gets the second altrep data slot.
//' @inherit alt_data1 description return
//' alt_data2(1:3)
// [[Rcpp::export]]
RObject alt_data2(RObject x){
  return R_altrep_data2(x);
}
