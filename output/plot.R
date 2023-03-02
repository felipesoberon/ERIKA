data <- read.csv("VEz.csv", header=TRUE, colClasses = c("numeric","numeric","numeric"))
colnames(data) <- c("z","V","E")

plot(with(data, V ~ z), type = "l")
grid()

plot(with(data, E ~ z), type = "l")
grid()


traj <- read.csv("trajectory.csv", header=TRUE, colClasses = c("numeric","numeric","numeric"))
colnames(traj) <- c("t","z","vz")

plot(with(traj, z ~ t), type = "l")
grid()

plot(with(traj, vz ~ z), type = "l")
grid()




ionCount <- read.csv("ionCount.csv", header=TRUE, colClasses = c("numeric","numeric","numeric"))
colnames(ionCount) <- c("G2","Count","Energy(ev)")

plot(with(ionCount, Count ~ G2), type = "l")
grid()


