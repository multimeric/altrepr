#include <Rcpp.h>
using namespace Rcpp;

// These underscore functions are used internally but not exported

bool _is_altrep(RObject x){
  return bool(ALTREP(x));
}

Pairlist _all_attribs(RObject x){
  return ATTRIB(x);
}

void _assert_altrep(RObject x){
  if (!_is_altrep(x)){
    stop("Not ALTREP!");
  }
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
//' @export
//' @return A raw vector uniquely identifying the altrep class of `x`, or `NULL`
//'   if `x` is not an altrep object.
//' @seealso [alt_classname()] [alt_pkgname()] [alt_type()]
//' @examples
//' identical(alt_class(1:2), alt_class(2:3))
// [[Rcpp::export]]
RawVector alt_class(RObject x){
  _assert_altrep(x);
  return ALTREP_CLASS(x);
}

//' Gets the name of the altrep class of an object
//'
//' This is a a human-readable name for the altrep class.
//' @export
//' @return The class name as a [character], or `NULL` if
//'   `x` is not an altrep object.
//' @examples
//' alt_classname(1:3)
// [[Rcpp::export]]
CharacterVector alt_classname(RObject x){
  _assert_altrep(x);
  return as<CharacterVector>(_all_attribs(alt_class(x))[0]);
}

//' Gets the package in which an ALTREP class was defined
//'
//' Specifically this finds the name of the package in which the altrep class
//' was defined. This is almost definitely not the same as the S3/S4 [class()],
//' was defined, which is likely to be one of the core vector types like
//' `integer`.
//' @export
//' @return The package name as a [character], or `NULL` if `x` is not an altrep
//'   object.
//' @examples
//' alt_pkgname(1:3)
// [[Rcpp::export]]
CharacterVector alt_pkgname(RObject x){
  _assert_altrep(x);
  return as<CharacterVector>(_all_attribs(alt_class(x))[1]);
}

//' Gets the name of the type that this ALTREP is representing.
//'
//' This will almost certainly return the same result as `typeof(x)`, but
//' please let the author of this package know if it doesn't!
//' @export
//' @return The name of the fundamental vector type of that `x` is representing,
//' as a [character] scalar. For example "integer" or "character".
//' @examples
//' alt_type(1:3)
// [[Rcpp::export]]
CharacterVector alt_type(RObject x){
  _assert_altrep(x);
    return Rf_type2rstr((_all_attribs(alt_class(x))[2]));
}

//' Checks if an R object is ALTREP
//'
//' This checks if `x` is an instance of an ALTREP class. Notably it doesn't
//' check if `x` **is** an ALTREP class, which is more difficult to achieve.
//' @export
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
//' @export
//' @return Possibly any R object, including `NULL`
//' @examples
//' alt_data1(1:3)
// [[Rcpp::export]]
RObject alt_data1(RObject x){
  _assert_altrep(x);
  return R_altrep_data1(x);
}

//' Gets the second altrep data slot.
//' @export
//' @inherit alt_data1 description return
//' @examples
//' alt_data2(1:3)
// [[Rcpp::export]]
RObject alt_data2(RObject x){
  _assert_altrep(x);
  return R_altrep_data2(x);
}

//' Sets the `data1` value of an ALTREP
//'
//' **Don't use this function unless you know what you're doing**.
//' If you set the data to some
//' unexpected value you are very likely to cause a SEGFAULT and crash the
//' entire R session. Also, this modifies the existing object in-place, meaning
//' that all variables pointing to this same ALTREP will be modified.
//' @param x An ALTREP object to modify
//' @param value The new value of the `altrep_data1` slot
//' @return `x`, invisibly (because `x` has been modified in-place you generally
//'   won't want or need to store the return value)
//' @export
// [[Rcpp::export(invisible=true)]]
RObject set_alt_data1(RObject x, RObject value){
  _assert_altrep(x);
  R_set_altrep_data1(x, value);
  return x;
}

//' Sets the `data2` value of an ALTREP
//' @inherit set_alt_data1
//' @param value The new value of the `altrep_data2` slot
//' @export
// [[Rcpp::export(invisible=true)]]
RObject set_alt_data2(RObject x, RObject value){
  _assert_altrep(x);
  R_set_altrep_data2(x, value);
  return x;
}
