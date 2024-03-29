% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{alt_pkgname}
\alias{alt_pkgname}
\title{Gets the package in which an ALTREP class was defined}
\usage{
alt_pkgname(x)
}
\arguments{
\item{x}{An ALTREP object of any class}
}
\value{
The package name as a character scalar.
}
\description{
This finds the name of the package in which the ALTREP class
was defined.
}
\examples{
alt_pkgname(1:3)
}
