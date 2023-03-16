library(dplyr)

list <- c("out2")

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


plot( iCdata[,1] ~ iC$G2, type = "l", xlab="Energy (eV)", ylab="Ion counts")
grid()









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
  

plot( iedf[,1] ~ energy, type="l",xlab="Energy (eV)", ylab="IEDF")
grid()












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


plot( g0iedf[,1] ~ energyBins, type="l")
grid()

