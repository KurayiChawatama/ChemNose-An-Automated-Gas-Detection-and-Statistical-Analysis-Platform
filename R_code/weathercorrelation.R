# Load necessary libraries
library(ggplot2)
library(dplyr)
library(corrplot)

# Assume you have a data frame named gas_data with columns: CH4, CO2, H2, and time

# Calculate correlations
correlation_matrix <- cor(gas_data[, c("CH4", "CO2", "H2")], use = "complete.obs")

# Plot correlation matrix
corrplot(correlation_matrix, method = "circle")

# Scatter plot for CH4 vs CO2 and H2
ggplot(gas_data, aes(x = CO2, y = CH4)) +
  geom_point() +
  geom_smooth(method = "lm", se = FALSE, color = "blue") +
  labs(title = "CH4 vs CO2", x = "CO2 Levels (PPM)", y = "CH4 Levels (PPM)")

ggplot(gas_data, aes(x = H2, y = CH4)) +
  geom_point() +
  geom_smooth(method = "lm", se = FALSE, color = "blue") +
  labs(title = "CH4 vs H2", x = "H2 Levels (PPM)", y = "CH4 Levels (PPM)")

# Perform linear regression
model <- lm(CH4 ~ CO2 + H2, data = gas_data)
summary(model)

# ANOVA if comparing groups
anova_results <- aov(CH4 ~ treatment, data = gas_data)
summary(anova_results)
