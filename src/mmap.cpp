#include <Rcpp.h>
#include "altrep.h"
using namespace Rcpp;

bool _is_mmap(RObject x){
  if (!_is_altrep(x)){
    return FALSE;
  }
  String name(alt_classname(x)[0]);
  return name == "mmap_integer" || name == "mmap_real";
}

void _assert_mmap(RObject x){
  if (!_is_mmap(x)){
    stop("Not a memmap!");
  }
}

//' Checks for memmap vector ALTREPs
//' @param x Any R object
//' @return A scalar logical. `TRUE` if `x` is a mmap vector, otherwise
//'  `FALSE`
//' @export
//' @examples
//' is_mmap(1)
//' mmap_make(data = 1:100) |> is_mmap()
// [[Rcpp::export]]
 LogicalVector is_mmap(RObject x){
   return {_is_mmap(x)};
 }

//' Returns a list containing the fields of a memory mapped vector
//' @param x A vector which has an mmap ALTREP class
//' @return A list with the fields:
//'   * `file_name`: A character scalar. The file name of that file that was
//'     mapped
//'   * `size_bytes`: An integer scalar. The number of bytes of the memory
//'     map
//'   * `length`: An integer scalar. The number of entries in the memory mapped
//'     vector
//'   * `type`: "double", or "integer", indicating the data type of the memory
//'     map
//'   * `ptrOK`: logical scalar. Unknown meaning
//'   * `wrtOK`: logical scalar. `TRUE` if writing to the memory map is allowed
//'   * `serOK`: logical scalar. Unknown meaning
//' @export
//' @examples
//' mmap_make(data = 1:10) |> mmap_details()
// [[Rcpp::export]]
List mmap_details(RObject x){
  _assert_mmap(x);
  List data2 = as<List>(alt_data2(x));
  IntegerVector entry1 = data2[1];
  IntegerVector entry2 = data2[2];

  return List::create(
    Named("file_name") = data2[0],
    Named("size_bytes") = entry1[0],
    Named("length") = entry1[1],
    Named("type") = Rf_type2rstr(entry2[0]),
    Named("ptrOK") = LogicalVector{bool(entry2[1])},
    Named("wrtOK") = LogicalVector{bool(entry2[2])},
    Named("serOK") = LogicalVector{bool(entry2[3])}
  );
}
