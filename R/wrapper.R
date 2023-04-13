#' Makes a custom wrapper ALTREP
#' @param x Any R object to wrap
#' @param has_na Logical scalar. `FALSE` if `x` should be considered to be free
#'  of `NA` values, otherwise should be set to `TRUE`
#' @param is_sorted Logical scalar. `TRUE` if `x` should be considered sorted,
#'  `FALSE` if it should be considered unsorted, or `NA` if its sorted status
#'  is unknown
#' @param descending Logical scalar. `TRUE` if `x` should be considered to be
#'  sorted in descending order, `FALSE` for ascending order.
#'  If `x` is unsorted this is unused.
#' @param na_first Logical scalar. `TRUE` if `x` should be treated as if it
#'  has `NA` values at the start of the vector, `FALSE` if they are at the end.
#'  If `x` is unsorted this is unused.
#' @return An object identical to `x` but with some hidden ALTREP metadata
#'  applied to it.
#' @export
#' @examples
#' wrapper <- wrapper_make(c(5, 3, NA, 1), is_sorted = TRUE, has_na = FALSE)
#' wrapper_details(wrapper)
wrapper_make <- function(x, has_na = FALSE, is_sorted = NA, descending = FALSE, na_first = FALSE){
  sorted_status <- if (is.na(is_sorted)){
    # UNKNOWN_SORTEDNESS
    NA_integer_
  }
  else if (!is_sorted){
    # KNOWN_UNSORTED
    0
  }
  else {
    if (descending){
      if (na_first){
        # SORTED_DECR_NA_1ST
        -2
      }
      else {
        # SORTED_DECR
        -1
      }
    }
    else {
      if (na_first){
        # SORTED_INCR_NA_1ST
        2
      }
      else {
        # SORTED_INCR
        1
      }
    }
  }

  # The third argument is "no_na", so is the inverse of "has_na"
  .Internal(wrap_meta(x, sorted_status, as.integer(!has_na)))
}
