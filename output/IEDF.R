#Load library dplyr to be able to use %>%
library(dplyr)

#List of folders with data from various parameter conditions
list <- c("out0.5", "out1.0", "out2.0", "out5.0", "out7.5", "out10.0")


#RFEA CURRENT AND 1ST DERIVATIVE ###################################
#Initialiaze the current data and the energy distribution
iCdata <- c( )
iedf <- c( )

#Run over all the data files in "list"
for (i in 1:length(list)) 
  {
   file <- paste(list[i],"ionCount.csv", sep="/")
   print(file)
   ionCount <- read.csv(file, header=FALSE)
   colnames(ionCount) <- c("G2","Count","Energy(ev)")
   iC <- ionCount %>% group_by(G2) %>% summarise(counts = sum(Count))
   iCdata <- cbind(iCdata, iC$counts)

   ionCount <- iC
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
   derivative <- derivative/max(derivative)
   iedf <- cbind(iedf, derivative)
   energyStep <- ionCount$G2[2]-ionCount$G2[1]
   energy <- seq(2,n,1)*energyStep
   
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

# Plot using ggplot2
IVplot <- ggplot(iCdata_long, aes(x = G2, y = value_offset, group = column)) +
  geom_line() +
  labs(x = "G2 Voltage (V)", y = "Ion counts at Collector") +
  theme_minimal() +
  theme_minimal() +
  theme(plot.background = element_rect(fill = "white"),
        panel.background = element_rect(fill = "white"))

IVplot

ggsave(filename = "IVcurve.jpeg", plot = IVplot, width = 5, height = 3, dpi = 300)



# Load necessary libraries
library(ggplot2)
library(tidyr)
library(dplyr)

#turn the data matrix into a data frame
iedf <- as.data.frame(iedf)

# Assuming iedf is a matrix and energy is a vector
# Convert the matrix to a data frame and add index column
iedf_df <- as.data.frame(iedf) %>%
  mutate(index = 1:n())

# Reshape the data frame to a long format
iedf_long <- iedf_df %>%
  pivot_longer(-index, names_to = "column", values_to = "value")

# Calculate the offsets
offsets <- c(0, -1, -2, -3, -4, -5)
names(offsets) <- colnames(iedf)

# Add the energy column and apply the offsets
iedf_long <- iedf_long %>%
  mutate(energy = energy[index], value_offset = value + offsets[as.character(column)])

# Create the ggplot2 plot
IEDFplot <- ggplot(iedf_long, aes(x = energy, y = value_offset, group = column)) +
  geom_line() +
  labs(x = "Energy (eV)", y = "Ion counts at Collector") +
  theme_minimal() +
  theme(axis.text.y = element_blank()) + # Omit y-axis values
  theme(plot.background = element_rect(fill = "white"),
        panel.background = element_rect(fill = "white"))

IEDFplot

ggsave(filename = "1stDerivative.jpeg", plot = IEDFplot, width = 2.5, height = 5, dpi = 300)









#IEDF AT G0  ###################################
#Run over the list and get the energy distribution at G0
g0iedf <- c( )

for (i in 1:length(list)) 
{
  file <- paste(list[i],"ionEnergy.csv", sep="/")
  print(file)
  ionEnergy <- read.csv(file, header=FALSE)
  colnames(ionEnergy) <- c("eVz", "eV")

  hist_obj <- hist(as.vector(ionEnergy$eVz), 
                   breaks = seq(0,1500,energyStep), plot=FALSE)
  IEDFcounts <- c(hist_obj$counts,0) / max(hist_obj$counts)
  energyBins <- hist_obj$breaks
  energyBins <- energyBins + energyStep/2
  
  g0iedf <- cbind(g0iedf, IEDFcounts)
}


################  Plot the IEDF at G0 ####################

# Load necessary libraries
library(ggplot2)
library(tidyr)
library(dplyr)

#turn the data matrix into a data frame
g0iedf <- as.data.frame(g0iedf)
colnames(g0iedf) <- c("V1","V2","V3","V4","V5","V6")

# Assuming iedf is a matrix and energy is a vector
# Convert the matrix to a data frame and add index column
g0iedf_df <- as.data.frame(g0iedf) %>%
  mutate(index = 1:n())

# Reshape the data frame to a long format
g0iedf_long <- g0iedf_df %>%
  pivot_longer(-index, names_to = "column", values_to = "value")

# Calculate the offsets
offsets <- c(0, -1, -2, -3, -4, -5)
names(offsets) <- colnames(g0iedf)

# Add the energy column and apply the offsets
g0iedf_long <- g0iedf_long %>%
  mutate(energy = energy[index], value_offset = value + offsets[as.character(column)])

# Create the ggplot2 plot
G0IEDFplot <- ggplot(g0iedf_long, aes(x = energy, y = value_offset, group = column)) +
  geom_line() +
  labs(x = "Energy (eV)", y = "IEDF at G0") +
  theme_minimal() +
  theme(axis.text.y = element_blank()) + # Omit y-axis values
  theme(plot.background = element_rect(fill = "white"),
        panel.background = element_rect(fill = "white"))

G0IEDFplot

ggsave(filename = "IEDFatG0.jpeg", plot = G0IEDFplot, width = 2.5, height = 5, dpi = 300)
