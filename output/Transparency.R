#Load library dplyr to be able to use %>%
library(dplyr)

#List of folders with data from various parameter conditions
list <- c("out0.5", "out1.0", "out2.0", "out5.0", "out7.5", "out10.0")


#RFEA CURRENT AND 1ST DERIVATIVE ###################################
#Initialiaze the current data and the energy distribution
iCdata <- c( )

#Run over all the data files in "list"
for (i in 1:length(list)) 
  {
   file <- paste(list[i],"ionCount.csv", sep="/")
   print(file)
   ionCount <- read.csv(file, header=FALSE)
   colnames(ionCount) <- c("G2","Count","Energy(ev)")
   iC <- ionCount %>% group_by(G2) %>% summarise(counts = sum(Count))
   iCdata <- cbind(iCdata, iC$counts)

  }


# PLOT THE RFEA CURRENT AND FIRST DERIVATIVE ###########################

# Load necessary libraries
library(ggplot2)
library(tidyr)
library(dplyr)

#turn the data matrix into a data frame
iCdata <- as.data.frame(iCdata)

# Assuming iCdata is a matrix and iC is a dataframe with a column G2
# Convert the matrix to a data frame and add index column
iCdata_df <- as.data.frame(iCdata) %>%
  mutate(index = 1:n())

# Reshape the data frame to a long format
iCdata_long <- iCdata_df %>%
  pivot_longer(-index, names_to = "column", values_to = "value")

# Calculate the offsets
offsets <- c(0, -1, -2, -3, -4, -5)
names(offsets) <- colnames(iCdata)

# Add the G2 column and apply the offsets
iCdata_long <- iCdata_long %>%
  mutate(G2 = iC$G2[index], value_offset = value + offsets[column])



pressure <- c(0.5, 1, 2, 5, 7.5, 10)
countThrough <- as.numeric(iCdata[1,])/25000
plot(countThrough ~ pressure, type="b", ylim=c(0,1))

data <- data.frame(Pressure = pressure, CollisionalTransparency = countThrough)

CollisionalTransparencyplot <- ggplot(data, aes(x = Pressure, y = CollisionalTransparency)) +
  geom_point(shape = 1, size = 2) + # shape = 1 for empty circles; adjust size as needed
  geom_line() +
  labs(x = "Pressure (Pa)", y = "Collisional Transparency (Pc)") +
  scale_y_continuous(limits = c(0, 1)) +
  theme_bw()

ggsave("CollisionalTransparency.jpeg", CollisionalTransparencyplot, width = 5, height = 3, dpi = 300)


