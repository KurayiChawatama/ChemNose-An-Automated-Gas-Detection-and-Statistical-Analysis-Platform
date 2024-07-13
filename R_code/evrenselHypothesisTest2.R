# Load the data
soil_data <- read.csv("soilGasSample1.csv")
norm_data <- read.csv("noSoilGasSample1.csv")

# Calculate means before and after 216 seconds
mean_before <- colMeans(norm_data[, c("CO2_PPM", "CH4_PPM", "H2_PPM")])
mean_after <- colMeans(soil_data[, c("CO2_PPM", "CH4_PPM", "H2_PPM")])

# Perform paired t-tests
test_CO2 <- t.test(gas_data_before_sampled$CO2_PPM, gas_data_after$CO2_PPM, paired = TRUE)
test_CH4 <- t.test(gas_data_before_sampled$CH4_PPM, gas_data_after$CH4_PPM, paired = TRUE)
test_H2 <- t.test(gas_data_before_sampled$H2_PPM, gas_data_after$H2_PPM, paired = TRUE)

# Output results
cat("Mean CO2 before 74s:", mean_before["CO2_PPM"], "\n")
cat("Mean CO2 after 74s:", mean_after["CO2_PPM"], "\n")
cat("Mean CH4 before 74s:", mean_before["CH4_PPM"], "\n")
cat("Mean CH4 after 74s:", mean_after["CH4_PPM"], "\n")
cat("Mean H2 before 74s:", mean_before["H2_PPM"], "\n")
cat("Mean H2 after 74s:", mean_after["H2_PPM"], "\n\n")

cat("Paired t-test results:\n")
cat("CO2 P-value:", test_CO2$p.value, "\n")
cat("CH4 P-value:", test_CH4$p.value, "\n")
cat("H2 P-value:", test_H2$p.value, "\n")
