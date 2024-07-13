# Load necessary libraries
library(ggplot2)
library(dplyr)
library(patchwork)


# Read the CSV file
weather_data <- read.csv("WEATHER.CSV")
View(weather_data)

# Convert the datetime column to POSIXct
weather_data$datetime <- as.POSIXct(weather_data$datetime, format="%m/%d/%Y %H:%M:%S")

# Remove observations where Temperature or Humidity is 0
cleaned_data <- weather_data %>%
  filter(temperature != 0 & humidity != 0)

# Calculate summary statistics for the cleaned dataset
summary_stats <- cleaned_data %>%
  summarise(
    Temperature_mean = mean(temperature, na.rm = TRUE),
    Temperature_sd = sd(temperature, na.rm = TRUE),
    Temperature_min = min(temperature, na.rm = TRUE),
    Temperature_max = max(temperature, na.rm = TRUE),
    Humidity_mean = mean(humidity, na.rm = TRUE),
    Humidity_sd = sd(humidity, na.rm = TRUE),
    Humidity_min = min(humidity, na.rm = TRUE),
    Humidity_max = max(humidity, na.rm = TRUE),
    CO2_mean = mean(CO2_PPM, na.rm = TRUE),
    CO2_sd = sd(CO2_PPM, na.rm = TRUE),
    CO2_min = min(CO2_PPM, na.rm = TRUE),
    CO2_max = max(CO2_PPM, na.rm = TRUE),
    CH4_mean = mean(CH4_PPM, na.rm = TRUE),
    CH4_sd = sd(CH4_PPM, na.rm = TRUE),
    CH4_min = min(CH4_PPM, na.rm = TRUE),
    CH4_max = max(CH4_PPM, na.rm = TRUE),
    H2_mean = mean(H2_PPM, na.rm = TRUE),
    H2_sd = sd(H2_PPM, na.rm = TRUE),
    H2_min = min(H2_PPM, na.rm = TRUE),
    H2_max = max(H2_PPM, na.rm = TRUE)
  )

# Print summary statistics
print(summary_stats)

# Create a custom theme for the plots
custom_theme <- theme_minimal() +
  theme(
    text = element_text(family = "Arial", size = 12),
    plot.title = element_text(hjust = 0.5, face = "bold", size = 14),
    axis.title = element_text(face = "bold", size = 12),
    axis.text = element_text(size = 10),
    panel.grid.major = element_line(color = "grey80"),
    panel.grid.minor = element_line(color = "grey90")
  )

# Create box plots for each variable with horizontal lines and jitter points
boxplot_temperature <- ggplot(cleaned_data, aes(x = "", y = temperature)) +
  geom_boxplot(fill = "dodgerblue", outlier.shape = NA) +
  geom_jitter(color = "black", width = 0.2, alpha = 0.5) +
  labs(title = "Boxplot of Temperature", y = "Temperature (°C)", x = "") +
  custom_theme +
  geom_hline(yintercept = quantile(cleaned_data$temperature, probs = c(0.05, 0.95)), 
             color = "red", linetype = "dashed", size = 1)

boxplot_humidity <- ggplot(cleaned_data, aes(x = "", y = humidity)) +
  geom_boxplot(fill = "firebrick", outlier.shape = NA) +
  geom_jitter(color = "black", width = 0.2, alpha = 0.5) +
  labs(title = "Boxplot of Humidity", y = "Humidity (%)", x = "") +
  custom_theme +
  geom_hline(yintercept = quantile(cleaned_data$humidity, probs = c(0.05, 0.95)), 
             color = "red", linetype = "dashed", size = 1)

boxplot_CO2 <- ggplot(cleaned_data, aes(x = "", y = CO2_PPM)) +
  geom_boxplot(fill = "forestgreen", outlier.shape = NA) +
  geom_jitter(color = "black", width = 0.2, alpha = 0.5) +
  labs(title = "Boxplot of CO2 Concentration", y = "CO2 (PPM)", x = "") +
  custom_theme +
  geom_hline(yintercept = quantile(cleaned_data$CO2_PPM, probs = c(0.05, 0.95)), 
             color = "red", linetype = "dashed", size = 1)

boxplot_CH4 <- ggplot(cleaned_data, aes(x = "", y = CH4_PPM)) +
  geom_boxplot(fill = "purple", outlier.shape = NA) +
  geom_jitter(color = "black", width = 0.2, alpha = 0.5) +
  labs(title = "Boxplot of CH4 Concentration", y = "CH4 (PPM)", x = "") +
  custom_theme +
  geom_hline(yintercept = quantile(cleaned_data$CH4_PPM, probs = c(0.05, 0.95)), 
             color = "red", linetype = "dashed", size = 1)

boxplot_H2 <- ggplot(cleaned_data, aes(x = "", y = H2_PPM)) +
  geom_boxplot(fill = "orange", outlier.shape = NA) +
  geom_jitter(color = "black", width = 0.2, alpha = 0.5) +
  labs(title = "Boxplot of H2 Concentration", y = "H2 (PPM)", x = "") +
  custom_theme +
  geom_hline(yintercept = quantile(cleaned_data$H2_PPM, probs = c(0.05, 0.95)), 
             color = "red", linetype = "dashed", size = 1)

# Display the box plots
print(boxplot_temperature)
print(boxplot_humidity)
print(boxplot_CO2)
print(boxplot_CH4)
print(boxplot_H2)

# Combine plots using patchwork
print((boxplot_temperature | boxplot_humidity) /
  (boxplot_CO2 | boxplot_CH4 | boxplot_H2))
