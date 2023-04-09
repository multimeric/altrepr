#include <Rcpp.h>
using namespace Rcpp;

bool _is_altrep(RObject x);
Pairlist _all_attribs(RObject x);
RawVector alt_class(RObject x);
CharacterVector alt_classname(RObject x);
CharacterVector alt_pkgname(RObject x);
CharacterVector alt_type(RObject x);
LogicalVector is_altrep(RObject x);
RObject alt_data1(RObject x);
RObject alt_data2(RObject x);
