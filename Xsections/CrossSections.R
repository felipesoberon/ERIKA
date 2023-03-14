# The data contained in the cross section files is in essence
# the same as the data from Phelps and the formula provided by
# LXCat can be used instead of the file load and search
# algorithm.

el <- read.table("Ar++Ar.elastic.txt", header=FALSE, skip=3)
cx <- read.table("Ar++Ar.charge.exchange.txt", header=FALSE, skip=3)

el <- as.data.frame(el)
cx <- as.data.frame(cx)

colnames(el) <- c("eV","el")
colnames(cx) <- c("eV","cx")


plot(with(el, el ~ eV), type="l", log="x", col="red", 
     xlab="Energy (eV)", ylab="Cross Section (x10^-20 m2)")
lines(with(cx, cx ~ eV), col="blue") 
legend("topright", legend = c("el","cx"), col=c("red","blue"), lty=1)
grid()




# From LXCAT database, for the Phelps data set. 
# https://us.lxcat.net/home/

energy <- 10^seq(-2, 4, 0.1)
el <- 2E-19/(2.*energy)^0.5/(1.+2.*energy)+3E-19*2.*energy/(1.+2.*energy/3.)^2.3
cx <- 0.5*(1.15E-18*(1.+0.015/2./energy)^0.6/(2.*energy)^0.1-2E-19/(2.*energy)^0.5/(1.+2.*energy)-3E-19*2.*energy/(1.+2.*energy/3.)^2.3)

elP <- el/(10^(-20))
cxP <- cx/(10^(-20))

plot(el  ~ energy, type="n", ylim=c(0,150), xlim=c(0.1,10000), log="x",
     xlab="Energy (eV)", ylab="Cross section (x10^-20 m2)");
lines(elP      ~ energy, col="red")
lines(cxP      ~ energy, col="blue")
legend("topright", legend = c("el (LXCAT)","cx (LXCAT)"), col=c("red","blue"), lty=1)
grid()
