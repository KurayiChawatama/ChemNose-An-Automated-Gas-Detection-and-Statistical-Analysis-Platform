# Load necessary libraries
library(dplyr)
library(ggplot2)

# Example data (replace with your actual data)
data <- read.csv("Labstest1.csv")

# Calculate total gas produced from 8 seconds to the end
gas_concentration <- summarise(data, 
                               CO2_total = sum(CO2_PPM[(Seconds >= 8)]),
                               CH4_total = sum(CH4_PPM[(Seconds >= 8)]),
                               H2_total = sum(H2_PPM[(Seconds >= 8)]))

# Constants
chamber_volume <- 0.350  # mL, convert to liters for calculations
soil_weight <- 0.010      # grams, convert to kilograms for calculations

# Convert grams to kilograms
soil_weight_kg <- soil_weight / 1000

# Ideal gas law constants (density in g/L)
density_CO2 <- 1.977  # g/L at 25°C and 1 atm
density_CH4 <- 0.717  # g/L at 25°C and 1 atm
density_H2 <- 0.0899  # g/L at 25°C and 1 atm

# Calculate volume of gas produced in liters
volume_CO2 <- gas_concentration$CO2_total * chamber_volume / 1000
volume_CH4 <- gas_concentration$CH4_total * chamber_volume / 1000
volume_H2 <- gas_concentration$H2_total * chamber_volume / 1000

# Calculate mass of gas produced in grams
mass_CO2 <- volume_CO2 * density_CO2
mass_CH4 <- volume_CH4 * density_CH4
mass_H2 <- volume_H2 * density_H2

# Output results
cat("Total CO2 produced:", round(mass_CO2, 2), "grams\n")
cat("Total CH4 produced:", round(mass_CH4, 2), "grams\n")
cat("Total H2 produced:", round(mass_H2, 2), "grams\n")

# Plotting the results
library(ggplot2)

# Create a data frame for plotting
gas_data <- data.frame(
  Gas = c("CO2", "CH4", "H2"),
  Mass = c(mass_CO2, mass_CH4, mass_H2)
)

# Plot
print(ggplot(gas_data, aes(x = Gas, y = Mass, fill = Gas)) +
  geom_bar(stat = "identity", width = 0.5, color = "black", fill = c("skyblue", "lightcoral", "lightgreen")) +
  labs(
    title = "Total Gas Produced from 8 Seconds Onwards",
    y = "Mass of Gas Produced (grams)",
    x = "Gas Type"
  ) +
  theme_minimal())
