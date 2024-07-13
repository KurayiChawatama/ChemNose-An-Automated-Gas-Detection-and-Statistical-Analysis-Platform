# Load necessary libraries
library(ggplot2)
library(dplyr)

# Read the CSV file
weather_data <- read.csv("WEATHER.CSV")

# Convert the datetime column to POSIXct
weather_data$datetime <- as.POSIXct(weather_data$datetime, format="%m/%d/%Y %H:%M:%S")

# Filter data for 07/12/2024 between 6:00 and 7:00
start_time <- as.POSIXct("07/12/2024 06:00:00", format="%m/%d/%Y %H:%M:%S")
end_time <- as.POSIXct("07/12/2024 07:00:00", format="%m/%d/%Y %H:%M:%S")
filtered_data <- weather_data %>%
  filter(datetime >= start_time & datetime <= end_time)

# Create a plot for each variable
plot_temperature <- ggplot(filtered_data, aes(x = datetime, y = temperature)) +
  geom_line(color = "blue") +
  labs(title = "Temperature Over Time (07/12/2024 6:00-7:00)", x = "Time", y = "Temperature (°C)")

plot_humidity <- ggplot(filtered_data, aes(x = datetime, y = humidity)) +
  geom_line(color = "red") +
  labs(title = "Humidity Over Time (07/12/2024 6:00-7:00)", x = "Time", y = "Humidity (%)")

plot_CO2 <- ggplot(filtered_data, aes(x = datetime, y = CO2_PPM)) +
  geom_line(color = "green") +
  labs(title = "CO2 Concentration Over Time (07/12/2024 6:00-7:00)", x = "Time", y = "CO2 (PPM)")

plot_CH4 <- ggplot(filtered_data, aes(x = datetime, y = CH4_PPM)) +
  geom_line(color = "purple") +
  labs(title = "CH4 Concentration Over Time (07/12/2024 6:00-7:00)", x = "Time", y = "CH4 (PPM)")

plot_H2 <- ggplot(filtered_data, aes(x = datetime, y = H2_PPM)) +
  geom_line(color = "orange") +
  labs(title = "H2 Concentration Over Time (07/12/2024 6:00-7:00)", x = "Time", y = "H2 (PPM)")

# Display the plots
print(plot_temperature)
print(plot_humidity)
print(plot_CO2)
print(plot_CH4)
print(plot_H2)
