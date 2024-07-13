# Load necessary libraries
library(ggplot2)
library(tidyr)
library(patchwork)

# Read the empty chamber data set
empty_chamber <- read.csv("noSoilGasSample1.csv")

# Read the individual soil test data (assuming you have them in separate CSV files)
soil_test1 <- read.csv("soilGasSample1.csv")
soil_test2 <- read.csv("soilGasSample2.csv")
soil_test3 <- read.csv("soilGasSample3.csv")
soil_test4 <- read.csv("soilGasSample4.csv")

plot_gas_line <- function(data, title) {
  # Convert data to long format for ggplot
  data_long <- pivot_longer(data, 
                            cols = c(CO2_PPM, CH4_PPM, H2_PPM), 
                            names_to = "Gas", 
                            values_to = "PPM")
  
  # Create the plot
  ggplot(data_long, aes(x = Seconds, y = PPM, color = Gas)) +
    geom_line(linewidth = 1) +  # Line thickness
    geom_point() +         # Add points
    labs(title = title,
         x = "Time (seconds)",
         y = "Concentration (PPM)",
         color = "Gas Type") +
    theme_minimal() +      # Minimal theme
    theme(text = element_text(size = 12)) # Increase font size
}

plot_empty_chamber <- plot_gas_line(empty_chamber, "Empty Chamber Gas Levels Over Time")

plot_soil_test1 <- plot_gas_line(soil_test1, "Soil Test 1 Gas Levels Over Time")
plot_soil_test2 <- plot_gas_line(soil_test2, "Soil Test 2 Gas Levels Over Time")
plot_soil_test3 <- plot_gas_line(soil_test3, "Soil Test 3 Gas Levels Over Time")
plot_soil_test4 <- plot_gas_line(soil_test4, "Soil Test 4 Gas Levels Over Time")

final_plot <- (plot_soil_test1 + plot_soil_test2 +
  plot_soil_test3 + plot_soil_test4 + plot_layout(ncol = 2)) + plot_empty_chamber +
  plot_layout(ncol = 2)

# Print the final combined plot
print(final_plot)
