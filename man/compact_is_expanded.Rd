% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{compact_is_expanded}
\alias{compact_is_expanded}
\title{Checks if a compact vector has been expanded}
\usage{
compact_is_expanded(x)
}
\arguments{
\item{x}{An ALTREP vector of class \code{compact_realseq} or \code{compact_intseq}}
}
\value{
A logical scalar. \code{TRUE} if the vector is expanded, \code{FALSE} if it
is compact
}
\description{
Checks if a compact vector has been expanded
}
\examples{
x <- 1:3
compact_is_expanded(x)
compact_expand(x)
compact_is_expanded(x)
}
