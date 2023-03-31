data <- read.csv("VEz.csv", header=TRUE)
colnames(data) <- c("z","V0","V4","V2","E0","E4","E2")

plot(with(data, V0 ~ z), type = "l") 
lines(with(data, V4 ~ z))
lines(with(data, V2 ~ z))
grid()

plot(with(data, E0 ~ z), type = "l") 
lines(with(data, E4 ~ z))
lines(with(data, E2 ~ z))
grid()

############################

# Load necessary libraries
library(ggplot2)
library(grid)
library(gridExtra)

# Set the aspect ratio
aspect_ratio <- 1.25

# Read the data from the file
data <- read.csv('VEz.csv')
colnames(data) <- c("z","V0","V4","V2","E0","E4","E2")

# Create the first plot: V as a function of z
plot1 <- ggplot(data) +
  geom_line(aes(x = z * 1e2, y = V0)) +
  geom_line(aes(x = z * 1e2, y = V2)) +
  geom_line(aes(x = z * 1e2, y = V4)) +
  geom_vline(aes(xintercept = 0), linetype = "dashed", color = "grey") +
  geom_vline(aes(xintercept = -0.02), linetype = "dashed", color = "grey") +
  geom_vline(aes(xintercept = -0.05), linetype = "dashed", color = "grey") +
  geom_vline(aes(xintercept = -0.08), linetype = "dashed", color = "grey") +
  geom_vline(aes(xintercept = -0.1), linetype = "dashed", color = "grey")+
  labs(x = "z (cm)", y = "V") +
  theme_minimal() +
  theme(plot.background = element_rect(fill = "white"),
        panel.background = element_rect(fill = "white"))



# Create the second plot: E as a function of z
plot2 <- ggplot(data) +
  geom_line(aes(x = z * 1e2, y = E0/1e6)) +
  geom_line(aes(x = z * 1e2, y = E2/1e6)) +
  geom_line(aes(x = z * 1e2, y = E4/1e6)) +
  geom_vline(aes(xintercept = 0), linetype = "dashed", color = "grey") +
  geom_vline(aes(xintercept = -0.02), linetype = "dashed", color = "grey") +
  geom_vline(aes(xintercept = -0.05), linetype = "dashed", color = "grey") +
  geom_vline(aes(xintercept = -0.08), linetype = "dashed", color = "grey") +
  geom_vline(aes(xintercept = -0.1), linetype = "dashed", color = "grey")+
  labs(x = "z (cm)", y = "E (MV/m)") +
  theme_minimal() +
  theme(plot.background = element_rect(fill = "white"),
        panel.background = element_rect(fill = "white"))

# Combine the two plots vertically in the same frame
combined_plot <- grid.arrange(plot1, plot2, ncol = 1)

# Save the combined plot as a JPEG file
ggsave("VEz0.5Pa13.56MHz2kVStack2332.jpeg", combined_plot, width=5, height =5*aspect_ratio, dpi = 300)

