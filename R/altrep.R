#' @useDynLib altrepr
#' @importFrom Rcpp evalCpp
NULL

#' Inspects an R data structure
#'
#' Specifically this prints a kind of tree that includes memory addresses,
#' `SEXPTYPE`s, and a few ALTREP tidbits.
#' This is useful in particular because ALTREP classes tend to have custom
#' implementations for inspect, which can be a useful way to summarise
#' ALTREP state.
#' @note This is a re-export of an internal R function, so outputs shouldn't be
#'   assumed to be stable.
#' @param x Any R object to inspect
#' @return `x`, invisibly
#' @export
#' @examples
#' alt_inspect(1:5)
alt_inspect <- function(x){
  .Internal(inspect(x))
}
