# Create a data frame with your results
test_results <- data.frame(
  Gas = c("CO2", "CH4", "H2"),
  Before = c(402.9467, 15.20722, 0.5111111),
  After1 = c(403.9578, 40.67278, 0.8094444),
  After2 = c(403.4683, 53.00167, 0.855),
  After3 = c(403.39, 36.54444, 0.7066667),
  After4 = c(403.5439, 46.33222, 0.8794444)
)

# Define colors for bars
colors <- c("#1f77b4", "#ff7f0e", "#2ca02c", "#d62728", "#9467bd")

# Reshape the data for plotting
library(tidyr)
test_results_long <- pivot_longer(test_results, cols = -Gas, names_to = "Condition", values_to = "Value")

# Plotting using ggplot2
library(ggplot2)
library(patchwork)

# Function to create individual plots for each gas type
plot_gas <- function(gas_name) {
  ggplot(test_results_long[test_results_long$Gas == gas_name, ], aes(x = Condition, y = Value, fill = Condition)) +
    geom_bar(position = "dodge", stat = "identity") +
    labs(title = paste("Comparison of", gas_name, "Levels Before and After Soil Test"),
         x = "Condition", y = "Mean Concentration") +
    scale_fill_manual(values = colors, name = "Condition",
                      breaks = c("Before", "After1", "After2", "After3", "After4"),
                      labels = c("Before", "After 1", "After 2", "After 3", "After 4")) +
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
