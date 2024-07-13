# Load necessary libraries
library(ggplot2)
library(dplyr)

# Read the CSV file
weather_data <- read.csv("WEATHER.CSV")

# Convert the datetime column to POSIXct
weather_data$datetime <- as.POSIXct(weather_data$datetime, format="%m/%d/%Y %H:%M:%S")

# Calculate summary statistics for the whole dataset
summary_stats <- weather_data %>%
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

# Create box plots for each variable
boxplot_temperature <- ggplot(weather_data, aes(y = temperature)) +
  geom_boxplot(fill = "blue") +
  labs(title = "Boxplot of Temperature", y = "Temperature (°C)")

boxplot_humidity <- ggplot(weather_data, aes(y = humidity)) +
  geom_boxplot(fill = "red") +
  labs(title = "Boxplot of Humidity", y = "Humidity (%)")

boxplot_CO2 <- ggplot(weather_data, aes(y = CO2_PPM)) +
  geom_boxplot(fill = "green") +
  labs(title = "Boxplot of CO2 Concentration", y = "CO2 (PPM)")

boxplot_CH4 <- ggplot(weather_data, aes(y = CH4_PPM)) +
  geom_boxplot(fill = "purple") +
  labs(title = "Boxplot of CH4 Concentration", y = "CH4 (PPM)")

boxplot_H2 <- ggplot(weather_data, aes(y = H2_PPM)) +
  geom_boxplot(fill = "orange") +
  labs(title = "Boxplot of H2 Concentration", y = "H2 (PPM)")

# Display the box plots
print(boxplot_temperature)
print(boxplot_humidity)
print(boxplot_CO2)
print(boxplot_CH4)
print(boxplot_H2)
