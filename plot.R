data <- read.csv("VEz.csv", header=TRUE, colClasses = c("numeric","numeric","numeric"))
colnames(data) <- c("z","V","E")

plot(with(data, V ~ z), type = "l")
grid()

plot(with(data, E ~ z), type = "l")
grid()
