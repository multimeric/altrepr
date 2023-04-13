#' Makes a memory-mapped vector
#' @param path Path to an existing file, or a file to write to if `data` is
#'  provided
#' @param data A double or integer vector to write to `path`, or `NULL` to
#'  only read from it.
#' @param type Either "double" or "integer", indicating the data type to
#'  read from disk. If not provided, it will be assumed to be the type of
#'  `data`.
#' @return A memory mapped vector, using the contents of `path`
#' @export
#' @examples
#' mmap_make(
#'   tempfile(),
#'   rnorm(n=5)
#' )
mmap_make <- function(path = NULL, data = NULL, type = NULL){
  if (is.null(data) && is.null(path)){
    stop("Either data or path or both must be provided!")
  }

  if (is.null(type)){
    if (is.null(data)){
      stop("type must be provided if data is not!")
    }
    type <- typeof(data)
  }

  if (is.null(path)){
    path <- tempfile()
  }

  if (!is.null(data)){
    writeBin(data, path)
  }
  else {
    file.create(path, showWarnings = FALSE)
  }

  .Internal(mmap_file(path, type))
}
