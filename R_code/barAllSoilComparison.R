library(tidyr)
library(ggplot2)
library(dplyr)
library(patchwork)

# Function to read and summarize CSV files
read_and_summarize <- function(file) {
  data <- read.csv(file)
  summarized_data <- data %>%
    summarize(
      CO2 = mean(CO2_PPM, na.rm = TRUE),
      CH4 = mean(CH4_PPM, na.rm = TRUE),
      H2 = mean(H2_PPM, na.rm = TRUE)
    )
  summarized_data$Condition <- gsub(".csv", "", file) # Add the condition based on file name
  return(summarized_data)
}

# Read and summarize the empty chamber data
no_soil_data <- read_and_summarize("noSoilGasSample1.csv")

# Read and summarize the soil sample data
soil_data1 <- read_and_summarize("soilGasSample1.csv")
soil_data2 <- read_and_summarize("soilGasSample2.csv")
soil_data3 <- read_and_summarize("soilGasSample3.csv")
soil_data4 <- read_and_summarize("soilGasSample4.csv")

# Combine all summarized data
combined_data <- bind_rows(no_soil_data, soil_data1, soil_data2, soil_data3, soil_data4)

# Reshape the data for plotting
combined_data_long <- pivot_longer(combined_data, cols = -Condition, names_to = "Gas", values_to = "Value")

# Define colors for bars
colors <- c("#1f77b4", "#ff7f0e", "#2ca02c", "#d62728", "#9467bd")

# Function to create individual plots for each gas type
plot_gas <- function(gas_name) {
  ggplot(combined_data_long[combined_data_long$Gas == gas_name, ], aes(x = Condition, y = Value, fill = Condition)) +
    geom_bar(position = "dodge", stat = "identity") +
    labs(title = paste("Comparison of", gas_name, "Levels in Empty Chamber vs Soil Samples"),
         x = "Condition", y = "Mean Concentration (PPM)") +
    scale_fill_manual(values = colors, name = "Condition",
                      breaks = c("noSoilGasSample1", "soilGasSample1", "soilGasSample2", "soilGasSample3", "soilGasSample4"),
                      labels = c("Empty Chamber", "Soil Sample 1", "Soil Sample 2", "Soil Sample 3", "Soil Sample 4")) +
    theme_minimal()
}

# Create plots for each gas type
plot_CO2 <- plot_gas("CO2")
plot_CH4 <- plot_gas("CH4")
plot_H2 <- plot_gas("H2")

# Arrange plots side by side using patchwork
final_plot <- plot_CO2 + plot_CH4 + plot_H2 + plot_layout(ncol = 3)

# Print the final plot
print(final_plot)