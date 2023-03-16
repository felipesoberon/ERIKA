sc <- read.csv("spaceCharge.csv", header=TRUE, colClasses = c("numeric","numeric","numeric"))
colnames(sc) <- c("z","vz","vp")

final <- sc[sc$z>-1.e-3,1]
hist(final, breaks=500, xlab="z(m)" )

plot(with(sc, vz ~ z), pch='.')
