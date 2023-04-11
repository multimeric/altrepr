#' @export
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
