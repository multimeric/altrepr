#' @useDynLib altrepr
#' @importFrom Rcpp evalCpp
NULL

#' @export
alt_inspect <- function(x){
  .Internal(inspect(x))
}

