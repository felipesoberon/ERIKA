ionEnergy <- read.csv("ionEnergy.csv", header=FALSE)
colnames(ionEnergy) <- c("eVz", "eV")

hist(as.vector(ionEnergy$eVz), breaks = seq(0,1500,10))
