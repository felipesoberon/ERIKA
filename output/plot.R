data <- read.csv("VEz.csv", header=TRUE, colClasses = c("numeric","numeric","numeric"))
colnames(data) <- c("z","V","E")

plot(with(data, V ~ z), type = "l"); grid()
plot(with(data, E ~ z), type = "l"); grid()


traj <- read.csv("trajectory.csv", header=TRUE, colClasses = c("numeric","numeric","numeric"))
colnames(traj) <- c("t","z","vz")

plot(with(traj, z ~ t), type = "l"); grid()
plot(with(traj, vz ~ z), type = "l"); grid()



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
energy <- seq(2,n,1)*10
plot(derivative ~ energy, type="l",xlab="Energy (eV)", ylab="IEDF"); grid()



#ION ENERGY DISTRIBUTION AS SEEN AT G0
ionEnergy <- read.csv("ionEnergy.csv", header=FALSE, colClasses = c("numeric"))
colnames(ionEnergy) <- c("eV")
hist(as.vector(ionEnergy$eV), breaks=100, 
     xlab="Energy (eV)", 
     ylab="Frequency", 
     main = "", xlim=c(0,1500)); grid()

