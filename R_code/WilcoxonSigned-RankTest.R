# Load the data
norm_data <- read.csv("noSoilGasSample1.csv")
soil_data <- read.csv("soilGasSample1.csv")

# Calculate means before and after soil addition
mean_no_soil <- colMeans(norm_data[, c("CO2_PPM", "CH4_PPM", "H2_PPM")])
mean_W_soil <- colMeans(soil_data[, c("CO2_PPM", "CH4_PPM", "H2_PPM")])

# Perform Wilcoxon signed-rank tests
tests <- lapply(names(mean_no_soil), function(gas) {
  test <- wilcox.test(norm_data[[gas]], soil_data[[gas]], paired = TRUE)
  cat(paste("P-value for", gas, ":", test$p.value, "\n"))
  if (test$p.value < 0.05) {
    cat("Significant change in", gas, "levels after adding soil.\n")
  } else {
    cat("No significant change in", gas, "levels after adding soil.\n")
  }
})

# Output means
cat("Mean CO2 before soil for 37s is:", mean_no_soil["CO2_PPM"], "\n")
cat("Mean CO2 after soil for 37s is:", mean_W_soil["CO2_PPM"], "\n")
cat("Mean CH4 before soil for 37s is:", mean_no_soil["CH4_PPM"], "\n")
cat("Mean CH4 after soil for 37s is:", mean_W_soil["CH4_PPM"], "\n")
cat("Mean H2 before soil for 37s is:", mean_no_soil["H2_PPM"], "\n")
cat("Mean H2 after soil for 37s is:", mean_W_soil["H2_PPM"], "\n")
