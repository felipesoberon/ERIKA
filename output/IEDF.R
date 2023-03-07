library(dplyr)
ionCount <- read.csv("ionCount.csv", header=FALSE, colClasses = c("numeric","numeric","numeric"))
colnames(ionCount) <- c("G2","Count","Energy(ev)")

ionCount <- ionCount %>% group_by(G2) %>% summarise(counts = sum(Count))

plot(ionCount, type = "l", xlab="Energy (eV)", ylab="Ion counts"); grid()

derivative <- c()
n <- dim(ionCount)[1]-1  
for (i in 2:n)
  {
  numerator <- with(ionCount, -(counts[i+1]-counts[i-1]) )
  denominator <- with(ionCount, (G2[i+1]-G2[i-1]) )
  if (denominator < 0) data <- 0
  else data <- numerator/denominator
  derivative <- rbind(derivative,data)
}
derivative <- derivative/max(derivative)
energyStep <- ionCount$G2[2]-ionCount$G2[1]
energy <- seq(2,n,1)*energyStep
plot(derivative ~ energy, type="l",xlab="Energy (eV)", ylab="IEDF"); grid()



#ION ENERGY DISTRIBUTION AS SEEN AT G0
ionEnergy <- read.csv("ionEnergy.csv", header=FALSE, colClasses = c("numeric","numeric"))
colnames(ionEnergy) <- c("eVz", "eV")
hist(as.vector(ionEnergy$eVz), breaks=n+1, 
     xlab="Energy (eV)", 
     ylab="Frequency", 
     main = "Energy (from vz only)", xlim=c(0,1500)); grid()
hist(as.vector(ionEnergy$eV), breaks=n+1, 
     xlab="Energy (eV)", 
     ylab="Frequency", 
     main = "Total Energy", xlim=c(0,1500)); grid()


#Alternative to ION ENERGY DISTRIBUTION AS SEEN AT G0
hist_obj <- hist(as.vector(ionEnergy$eVz), breaks = n+1)
IEDFcounts <- c(hist_obj$counts,0) / max(hist_obj$counts)
energyBins <- hist_obj$breaks
energyBins <- energyBins + energyStep/2


# PLOT IEDF AT G0 AND COLLECTOR

plot(derivative ~ energy, type="l",
     xlab="Energy (eV)", ylab="IEDF", col="blue",
     main = "Blue: C  /  Red: G0",
     xlim = c(0,1500))
lines(IEDFcounts ~ energyBins, type="l", col="red"); grid()
