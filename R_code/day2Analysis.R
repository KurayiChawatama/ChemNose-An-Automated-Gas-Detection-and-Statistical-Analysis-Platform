library(ggplot2)
library(dplyr)
library(patchwork)
library(scales)

# Read the CSV file
day2_data <- read.csv("DAY2.CSV")

# Convert the datetime column to POSIXct
day2_data$datetime <- as.POSIXct(day2_data$datetime, format="%m/%d/%Y %H:%M:%S")

# Define a custom theme for the plots
custom_theme <- theme_minimal(base_size = 15) +
  theme(
    plot.background = element_rect(fill = "white", color = NA),
    panel.background = element_rect(fill = "white", color = NA),
    panel.grid.major = element_line(color = "gray80"),
    panel.grid.minor = element_line(color = "gray90"),
    axis.text.x = element_text(angle = 45, hjust = 1),
    axis.text.y = element_text(color = "black"),
    plot.title = element_text(hjust = 0.5, face = "bold"),
    legend.position = "none"
  )

# Create a plot for each variable
plot_temperature <- ggplot(day2_data, aes(x = datetime, y = temperature)) +
  geom_line(color = "blue", size = 1) +
  labs(title = "Temperature Over Time", x = "Time", y = "Temperature (°C)") +
  scale_x_datetime(date_breaks = "1 hour", date_labels = "%H:%M") +
  custom_theme

plot_humidity <- ggplot(day2_data, aes(x = datetime, y = humidity)) +
  geom_line(color = "red", size = 1) +
  labs(title = "Humidity Over Time", x = "Time", y = "Humidity (%)") +
  scale_x_datetime(date_breaks = "1 hour", date_labels = "%H:%M") +
  custom_theme

plot_CO2 <- ggplot(day2_data, aes(x = datetime, y = CO2_PPM)) +
  geom_line(color = "green", size = 1) +
  labs(title = "CO2 Concentration Over Time", x = "Time", y = "CO2 (PPM)") +
  scale_x_datetime(date_breaks = "1 hour", date_labels = "%H:%M") +
  custom_theme

plot_CH4 <- ggplot(day2_data, aes(x = datetime, y = CH4_PPM)) +
  geom_line(color = "purple", size = 1) +
  labs(title = "CH4 Concentration Over Time", x = "Time", y = "CH4 (PPM)") +
  scale_x_datetime(date_breaks = "1 hour", date_labels = "%H:%M") +
  custom_theme

plot_H2 <- ggplot(day2_data, aes(x = datetime, y = H2_PPM)) +
  geom_line(color = "orange", size = 1) +
  labs(title = "H2 Concentration Over Time", x = "Time", y = "H2 (PPM)") +
  scale_x_datetime(date_breaks = "1 hour", date_labels = "%H:%M") +
  custom_theme

# Combine and print the plots
print((plot_temperature | plot_humidity) /
        (plot_CO2 | plot_CH4 | plot_H2))
