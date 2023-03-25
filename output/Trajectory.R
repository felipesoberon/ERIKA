traj <- read.csv("trajectory.csv", header=TRUE)
colnames(traj) <- c("t","z","vz","vp")

plot(with(traj, z ~ t), type = "l"); grid()
plot(with(traj, vz ~ z), type = "l"); grid()

##############################

# Load necessary libraries
library(ggplot2)
library(grid)
library(gridExtra)

# Set the aspect ratio
aspect_ratio <- 1.25

# Create the first plot: position z as a function of time
plot1 <- ggplot(traj, aes(x = t*1e6, y = z*1e2)) +
  geom_line() +
  labs(x = "Time (us)", y = "z (cm)") +
  theme_minimal() +
  theme(plot.background = element_rect(fill = "white"),
        panel.background = element_rect(fill = "white"))

# Create the second plot: velocity in the z direction as a function of position in z
plot2 <- ggplot(traj, aes(x = z*1e2, y = vz/1e3)) +
  geom_line() +
  geom_vline(aes(xintercept = 0), linetype = "dashed", color = "grey") +
  geom_vline(aes(xintercept = -0.02), linetype = "dashed", color = "grey") +
  geom_vline(aes(xintercept = -0.05), linetype = "dashed", color = "grey") +
  geom_vline(aes(xintercept = -0.08), linetype = "dashed", color = "grey") +
  geom_vline(aes(xintercept = -0.1), linetype = "dashed", color = "grey")+
  labs(x = "z (cm)", y = "Velocity (Km/s)") +
  theme_minimal() +
  theme(plot.background = element_rect(fill = "white"),
        panel.background = element_rect(fill = "white"))

# Combine the two plots vertically in the same frame
combined_plot <- grid.arrange(plot1, plot2, ncol = 1)

# Save the combined plot as a JPEG file
ggsave("ionTrajectory2Pa13.56MHz2kVStack2332_Collisionless.jpeg", combined_plot, width=5, height=5*aspect_ratio, dpi = 300)

