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
//' The altrep class is a [raw] vector whose
//' value uniquely distinguishes the class from other classes.
//' The altrep class is not the same as the name of the class. For that,
//' you can use [alt_classname()].
//' You are unlikely
//' to find much meaning in the actual vector values, but you might find it
//' useful to check if two objects belong to the same class. The other
//' meaningful use of the class is to check its [attributes()], but it is
//' recommended that you instead use the dedicated wrapper functions for
//' these attributes: [alt_classname()], [alt_pkgname()], and [alt_type()], or
//' [alt_details()].
//' @export
//' @param x An ALTREP object of any class
//' @return A raw vector uniquely identifying the altrep class of `x`
//' @seealso [alt_classname()] [alt_pkgname()] [alt_type()] [alt_details()]
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
//' @inheritParams alt_class
//' @return The class name as a character scalar.
//' @examples
//' alt_classname(1:3)
// [[Rcpp::export]]
CharacterVector alt_classname(RObject x){
  _assert_altrep(x);
  return as<CharacterVector>(_all_attribs(alt_class(x))[0]);
}

//' Gets the package in which an ALTREP class was defined
//'
//' This finds the name of the package in which the ALTREP class
//' was defined.
//' @export
//' @inheritParams alt_class
//' @return The package name as a character scalar.
//' @examples
//' alt_pkgname(1:3)
// [[Rcpp::export]]
CharacterVector alt_pkgname(RObject x){
  _assert_altrep(x);
  return as<CharacterVector>(_all_attribs(alt_class(x))[1]);
}

//' Gets the name of the type that this ALTREP is representing.
//'
//' This will almost certainly return the same result as `typeof(x)`. However,
//' the author would be interested to know if it doesn't!
//' @export
//' @inheritParams alt_class
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
//' check if `x` **is** an ALTREP class
//' (ie the return value from [alt_class()]), which is more difficult to
//' achieve.
//' @param x Any R object
//' @export
//' @return A scalar logical. `TRUE` if `x` is ALTREP, otherwise `FALSE`.
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
//' hold the "expanded" state. See the `vignette("altrepr")` for more
//' information.
//' @inheritParams alt_class
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
//' @inheritParams alt_class
//' @inherit alt_data1 description return details
//' @note **Warning**: storing the result will cause an R session crash with a
//' `deferred_string` ALTREP object.
//' @examples
//' sort(3:1) |> alt_data2()
// [[Rcpp::export]]
RObject alt_data2(RObject x){
  _assert_altrep(x);
  return R_altrep_data2(x);
}

//' Sets the `data1` value of an ALTREP
//'
//' **Don't use this function unless you know what you're doing** or just
//' don't care about your R session.
//' If you set the data to some
//' unexpected value you are very likely to cause a SEGFAULT and crash the
//' entire R session. Also, this modifies the existing object in-place, meaning
//' that all variables pointing to this same ALTREP will be modified.
//' @param x An ALTREP object to modify
//' @param value The new value of the `altrep_data1` slot
//' @return `x`, invisibly (because `x` has been modified in-place you generally
//'   won't want or need to store the return value)
//' @keywords advanced
//' @export
//' @examples
//' x <- 1:5
//' set_alt_data1(x, c(10, 10, -1))
//' x
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
//' @keywords advanced
//' @examples
//' x <- 1:5
//' set_alt_data2(x, 10:15)
//' x
// [[Rcpp::export(invisible=true)]]
RObject set_alt_data2(RObject x, RObject value){
  _assert_altrep(x);
  R_set_altrep_data2(x, value);
  return x;
}

//' Touches the DATAPTR of a vector
//'
//' This is a utility function that accesses the `DATAPTR` of a vector, but
//' doesn't touch it or do anything else. The `DATAPTR` is a pointer to the
//' actual array data of the vector. This is useful because it often triggers
//' certain behaviours in ALTREP vectors like expanding them into full form.
//' @param x Any R object
//' @return `x`, invisibly, unchanged.
//' @export
//' @keywords advanced
//' @examples
//' x <- 1:5
//' compact_is_expanded(x)
//' alt_touch_dataptr(x)
//' compact_is_expanded(x)
// [[Rcpp::export(invisible=true)]]
RObject alt_touch_dataptr(RObject x){
  DATAPTR(x);
  return x;
}

//' Returns a summary of the properties of an ALTREP object
//' @inherit alt_data2 note
//' @inheritParams alt_class
//' @return A list with the following entries:
//'   * `class_name` (character scalar): see [alt_classname()]
//'   * `pkg_name` (character scalar): see [alt_classname()]
//'   * `base_type` (character scalar): see [alt_type()]
//'   * `data1` (anything): see [alt_data1()]
//'   * `data2` (anything): see [alt_data2()]
//' @export
//' @examples
//' alt_details(1:4)
// [[Rcpp::export]]
List alt_details(RObject x){
  _assert_altrep(x);
  return List::create(
    Named("class_name") = alt_classname(x),
    Named("pkg_name") = alt_pkgname(x),
    Named("base_type") = alt_type(x),
    Named("data1") = alt_data1(x),
    Named("data2") = alt_data2(x)
  );
}
