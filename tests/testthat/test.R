# load required R libraries
library("pexm")
loadpexm()

####################################
# Generate the data:

# Real values.
lambda <- c(0.3, 0.6, 0.8, 1.3)

# Set the fixed time grid vector.
# Requirements: 
#   - 1st element must be 0, 
#   - values must be in ascending order.
#   - length(tau) must match length(lambda).
tau <- c(0.0, 2.0, 3.0, 5.0)
m <- length(tau)

# Generate from the 
# Piecewise Exponential model (via R package "msm").
n <- 1000
t <- rpexp(n, lambda, tau)

# Probabilities related to target quantiles
pq = c(1,2,seq(5,95,5),98,99)/100
nq = length(pq) 

####################################
# Information for JAGS
data <- list(t=t, n=n, tau=tau, m=m, pq=pq, nq=nq)
parameters <- c("lambda", "ht1", "ht81", "Ht1", "Ht81",
                paste0("q[",1:nq,"]"), 
                paste0("loglik[",1:n,"]"), 
                paste0("St[",1:n,"]"))

inits <- function(){list( lambda=rexp(m) )}

# MCMC setup:
burnin <- 150
thin <- 1
npost <- 10
n.iter <- burnin + thin*npost
n.chains <- 1

####################################

model <- textConnection(
  "
  model {
    for (i in 1:n) {
      t[i] ~ dpex(lambda[], tau[])
      St[i] <- 1-ppex(t[i], lambda[], tau[])
      loglik[i] <- log(dpex(t[i], lambda[], tau[]))
    }
    #
    Ht1 <- hcpex(t[1], lambda[], tau[])
    Ht81 <- hcpex(t[81], lambda[], tau[])
    ht1 <- hpex(t[1],lambda[],tau[])
    ht81 <- hpex(t[81],lambda[],tau[])
    #
    for (j in 1:m) {
      lambda[j] ~ dgamma(0.01,0.01)
    }
    for (k in 1:nq) {
      q[k] <- qpex(pq[k], lambda[], tau[])
    }  
  }"
)

fit = jags.model(file=model, data=data, inits=inits, n.chains = n.chains, 
                 n.adapt=round(burnin/2), quiet=FALSE)

# running JAGS
initial.time <- proc.time()
samp = coda.samples(fit, variable.names = parameters, n.iter = n.iter, thin = thin)
time.jags <- proc.time() - initial.time
time.jags

#########################################################
# Check the values of hazard and cumulative hazard functions for t[1] and t[81]
labels <- c("ht1","ht81","Ht1","Ht81")
summary(samp[,labels])
