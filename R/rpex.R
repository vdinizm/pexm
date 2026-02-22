## Draw random samples from the piecewise exponential distribution. Arguments:
## "n" = number of samples to draw.
## "rates" = vector of non-negative incidence rates
## "grid" = vector of change points for the incidence rates. The elements of "grid" should be
##          strictly positive and increasing. The length of the grid vector should be one less
##          than the length of the rates vector.
## "lower" = optional lower bound. If set this should be a positive scalar
## "upper" = optional upper bound. If set this should be a positive scalar
rpex <- function(n, rates=1, grid=numeric(0), lower=NULL, upper=NULL)
{
    nr <- length(rates)
    ## Check rates
    if (nr < 1) {
        stop("Must specify at least one rate")
    }
    if (any(rates < 0)) {
        stop("Rates must be non-negative")
    }

    ## Check grid
    if (length(grid) != nr - 1) {
        stop("Length mismatch between rates and grid")
    }
    if (any(grid <= 0)) {
        stop("Grid values must be positive")
    }
    if (length(grid) > 1 && any(diff(grid) <= 0)) {
        stop("Grid values must be strictly increasing")
    }

    ## Check bounds
    if (!is.null(lower)) {
        if (length(lower) != 1) {
            stop("Lower bound must be scalar")
        }
        if (lower <= 0) {
            stop("Lower bound must be positive")
        }
    }
    if (!is.null(upper)) {
        if (length(upper) != 1) {
            stop("Upper bound must be scalar")
        }
        if (upper <= 0) {
            stop("Upper bound must be positive")
        }
        if (!is.null(lower) && upper <= lower) {
            stop("Upper bound must be greater than lower bound")
        }
    }

    lo <- 0
    up <- 1
    grid <- c(0, grid)

    if (!is.null(lower)) {
        ## Find integrated hazard up to lower bound
        M <- max(which(grid < lower))
        g <- c(grid[1:M], lower)
        Ht <- sum(rates[1:M] * diff(g))
        lo <- 1 - exp(-Ht)
    }

    if (!is.null(upper)) {
        ## Find integrated hazard up to upper bound
        M <- max(which(grid < upper))
        g <- c(grid[1:M], upper)
        Ht <- sum(rates[1:M] * diff(g))
        up <- 1 - exp(-Ht)
    }   
    
    if (up - lo < 0.0001) {
        warning("Ignoring upper & lower limits that are too close")
        lo <- 0
        up <- 1
    }

    ## F(t)= 1-S(t)= 1-exp{-H(t)}, H(t)= -log(1-F(t))
    Ht <- c(0, cumsum(rates[-nr] * diff(grid)))
    
    y <- numeric(n)
    w = -log(1 - runif(n, lo, up));
    for (i in 1:n) {
        M <- max(which(Ht < w[i]))
        y[i] <- grid[M] + (w[i] - Ht[M])/rates[M]
    }
    return(y)
}
