plot_IEF_histogram <- function(energyStep) {
  ionEnergy <- read.csv("ionEnergy.csv", header=FALSE)
  colnames(ionEnergy) <- c("eVz", "eV")
  max_energy <- max(ionEnergy$eVz) * 1.5
  
  hist_obj <- hist(as.vector(ionEnergy$eVz), 
                   breaks = seq(0, max_energy, energyStep), plot=FALSE)
  IEDFcounts <- c(hist_obj$counts, 0) / max(hist_obj$counts)
  energyBins <- hist_obj$breaks
  energyBins <- energyBins + energyStep / 2
  
  plot(IEDFcounts ~ energyBins, type="l", xlab="Energy (eV)", ylab="Norm.")
  grid()
}

plot_IEF_histogram(5)

while(1) { plot_IEF_histogram(5);  Sys.sleep(1)}
