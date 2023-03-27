library(dplyr)

list <- c("out0.5", "out1.0", "out2.0", "out5.0", "out7.5", "out10.0")


iCdata <- c( )

for (i in 1:length(list)) 
  {
   file <- paste(list[i],"ionCount.csv", sep="/")
   print(file)
   ionCount <- read.csv(file, header=FALSE)
   colnames(ionCount) <- c("G2","Count","Energy(ev)")
   iC <- ionCount %>% group_by(G2) %>% summarise(counts = sum(Count))
   iCdata <- cbind(iCdata, iC$counts)
  }


jpeg(filename = "IVcurve.jpeg", width = 2500, height = 2500, units = "px", res = 300)
par(yaxt="s")
plot( iCdata[,1] ~ iC$G2, type = "l", xlab="Energy (eV)", ylab="Ion counts at Collector")
lines(iCdata[,2] ~ iC$G2)
lines(iCdata[,3] ~ iC$G2)
lines(iCdata[,4] ~ iC$G2)
lines(iCdata[,5] ~ iC$G2)
lines(iCdata[,6] ~ iC$G2)
# legend("bottom", legend = c("0.5","1.0","2.5","5.0","10.0"), lty=1, xjust=1.1, yjust=1.1)
grid()
dev.off()









iedf <- c( )

for (i in 1:length(list)) 
{
  file <- paste(list[i],"ionCount.csv", sep="/")
  print(file)
  ionCount <- read.csv(file, header=FALSE)
  colnames(ionCount) <- c("G2","Count","Energy(ev)")
  ionCount <- ionCount %>% group_by(G2) %>% summarise(counts = sum(Count))
  
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
  iedf <- cbind(iedf, derivative)
  energyStep <- ionCount$G2[2]-ionCount$G2[1]
  energy <- seq(2,n,1)*energyStep
}


jpeg(filename = "1stDerivative.jpeg", width = 2500, height = 2500, units = "px", res = 300)
par(yaxt="n")
plot( iedf[,1] ~ energy, type="l",xlab="Energy (eV)", ylab="IEDF (1st Derivative, normalized)", xlim=c(0,1500), ylim=c(-5,1))
lines(iedf[,2]-1  ~ energy)
lines(iedf[,3]-2  ~ energy)
lines(iedf[,4]-3  ~ energy)
lines(iedf[,5]-4  ~ energy)
lines(iedf[,6]-5  ~ energy)
grid()
dev.off()











g0iedf <- c( )

for (i in 1:length(list)) 
{
  file <- paste(list[i],"ionEnergy.csv", sep="/")
  print(file)
  ionEnergy <- read.csv(file, header=FALSE)
  colnames(ionEnergy) <- c("eVz", "eV")

  hist_obj <- hist(as.vector(ionEnergy$eVz), 
                   breaks = seq(0,1500,energyStep), plot=FALSE)
  IEDFcounts <- c(hist_obj$counts,0) / max(hist_obj$counts)
  energyBins <- hist_obj$breaks
  energyBins <- energyBins + energyStep/2
  
  g0iedf <- cbind(g0iedf, IEDFcounts)
}


jpeg(filename = "IEDFatG0.jpeg", width = 2500, height = 2500, units = "px", res = 300)
par(yaxt="n")
plot( g0iedf[,1] ~ energyBins, type="l", ylim=c(-5,1), xlim=c(0,1500),xlab="Energy (eV)", ylab="IEDF (normalized)")
lines(g0iedf[,2]-1 ~ energyBins)
lines(g0iedf[,3]-2 ~ energyBins)
lines(g0iedf[,4]-3 ~ energyBins)
lines(g0iedf[,5]-4 ~ energyBins)
lines(g0iedf[,6]-5 ~ energyBins)
grid()
dev.off()

