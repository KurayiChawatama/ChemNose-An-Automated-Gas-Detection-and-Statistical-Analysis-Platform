library(ggplot2)
library(tidyr)

# Read the CSV file
data <- read.csv("PeroxideTest1.csv")

# Convert data to long format for ggplot
data_long <- pivot_longer(data, 
                          cols = c(CO2_PPM, CH4_PPM, H2_PPM), 
                          names_to = "Gas", 
                          values_to = "PPM")

# Create the plot
print(ggplot(data_long, aes(x = Seconds, y = PPM, color = Gas)) +
  geom_line(size = 1) +  # Line thickness
  geom_point() +         # Add points
  labs(title = "Gas Levels Over Time",
       x = "Time (seconds)",
       y = "Concentration (PPM)",
       color = "Gas Type") +
  theme_classic() +      # Minimal theme
  theme(text = element_text(size = 12))) # Increase font size