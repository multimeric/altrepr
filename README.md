
<!-- README.md is generated from README.Rmd. Please edit that file -->

# altrepr

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://lifecycle.r-lib.org/articles/stages.html#experimental)
[![CRAN
status](https://www.r-pkg.org/badges/version/altrepr)](https://CRAN.R-project.org/package=altrepr)
<!-- badges: end -->

`altrepr` shines light on the mysterious ALTREP objects in R.

It offers:

- Inspection of ALTREP types
- Specialized constructors and inspections for the 4 built-in ALTREP
  classes in R
- Detailed vignettes that explore these classes, how to use them in R,
  and their internal workings

## Installation

You can install the development version of altrepr like so:

``` r
remotes::install_github("multimeric/altrepr")
```

## Example

``` r
library(altrepr)
```

`1:5` is just a normal integer vector right? Wrong! It’s a sneaky ALTREP
masquerading as an integer vector.

``` r
x <- 1:5
is_altrep(x)
#> [1] TRUE
```

We can dig into the details:

``` r
alt_details(x)
#> $class_name
#> [1] "compact_intseq"
#> 
#> $pkg_name
#> [1] "base"
#> 
#> $base_type
#> [1] "integer"
#> 
#> $data1
#> [1] 5 1 1
#> 
#> $data2
#> NULL
```

``` r
compact_details(x)
#> $length
#> [1] 5
#> 
#> $start
#> [1] 1
#> 
#> $step
#> [1] 1
#> 
#> $expanded
#> NULL
```

And, if we’re feeling brave, we can even edit the ALTREP:

``` r
set_alt_data1(x, c(10, 1, 1))
x
#>  [1]  1  2  3  4  5  6  7  8  9 10
```

For more information, refer to the detailed vignettes!
