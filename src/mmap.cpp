#include <Rcpp.h>
#include "altrep.hpp"
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

//' @export
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
