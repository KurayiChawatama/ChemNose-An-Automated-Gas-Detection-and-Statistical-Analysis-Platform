# Load the data
norm_data <- read.csv("noSoilGasSample1.csv")
soil_data <- read.csv("soilGasSample1.csv")

# Calculate means before and after soil addition for the 37 seconds observation time
mean_no_soil <- colMeans(norm_data[, c("CO2_PPM", "CH4_PPM", "H2_PPM")])
mean_W_soil <- colMeans(soil_data[, c("CO2_PPM", "CH4_PPM", "H2_PPM")])

# Perform Wilcoxon signed-rank tests
test_CO2 <- wilcox.test(norm_data$CO2_PPM, soil_data$CO2_PPM, paired = TRUE)
test_CH4 <- wilcox.test(norm_data$CH4_PPM, soil_data$CH4_PPM, paired = TRUE)
test_H2 <- wilcox.test(norm_data$H2_PPM, soil_data$H2_PPM, paired = TRUE)

# Output means
cat("Mean CO2 before soil for 37s is:", mean_no_soil["CO2_PPM"], "\n")
cat("Mean CO2 after soil for 37s is:", mean_W_soil["CO2_PPM"], "\n")
cat("Mean CH4 before soil for 37s is:", mean_no_soil["CH4_PPM"], "\n")
cat("Mean CH4 after soil for 37s is:", mean_W_soil["CH4_PPM"], "\n")
cat("Mean H2 before soil for 37s is:", mean_no_soil["H2_PPM"], "\n")
cat("Mean H2 after soil for 37s is:", mean_W_soil["H2_PPM"], "\n\n")

# Output Wilcoxon signed-rank test results
cat("Wilcoxon signed-rank test results:\n")
cat("CO2 P-value:", test_CO2$p.value, "\n")
cat("CH4 P-value:", test_CH4$p.value, "\n")
cat("H2 P-value:", test_H2$p.value, "\n")

# Check for significant differences
if (test_CO2$p.value < 0.05) {
  cat("Significant change in CO2 levels after adding soil.\n")
} else {
  cat("No significant change in CO2 levels after adding soil.\n")
}

if (test_CH4$p.value < 0.05) {
  cat("Significant change in CH4 levels after adding soil.\n")
} else {
  cat("No significant change in CH4 levels after adding soil.\n")
}

if (test_H2$p.value < 0.05) {
  cat("Significant change in H2 levels after adding soil.\n")
} else {
  cat("No significant change in H2 levels after adding soil.\n")
}

