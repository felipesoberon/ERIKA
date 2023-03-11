traj <- read.csv("trajectory.csv", header=TRUE, colClasses = c("numeric","numeric","numeric","numeric"))
colnames(traj) <- c("t","z","vz","vp")

plot(with(traj, z ~ t), type = "l"); grid()
plot(with(traj, vz ~ z), type = "l"); grid()



