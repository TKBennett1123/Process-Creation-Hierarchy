# Load File
library(readxl)
Final <- read_excel("C:/Users/super/Desktop/School/2020-2021/Spring 2021/CMS 330/Final.xlsx")
View(Final)

# mean version 1
mean(Final$`Version 1`)
# mean version 2
mean(Final$`Version 2`)

# median version 1
0.000178
# median version 2
0.000119

# five num summary version 1
summary(Final$`Version 1`)
# five num summary version 2
summary(Final$`Version 2`)

# Regular box plot comparison
boxplot(
  Final$`Version 2`, 
  Final$`Version 1`, 
  names=c("Version 2", "Version 1"), 
  main="Time to Complete 1000 Cycles of PCB Operations", 
  xlab="Time per 1000 Cycles (seconds)", 
  horizontal = TRUE
)

# Zoomed in box plot comparison
boxplot(
  Final$`Version 2`, 
  Final$`Version 1`, 
  names=c("Version 2", "Version 1"), 
  main="Time to Complete 1000 Cycles of PCB Operations (Zoomed in to show 0.00012-0.00018)", 
  xlab="Time per 1000 Cycles (seconds)", 
  horizontal = TRUE, 
  ylim=c(0.000115,0.000185)
)

# Zoomed in box plot Version 1 only
boxplot(
  Final$`Version 1`, 
  main="Version 1: Time to Complete 1000 Cycles of PCB Operations (Zoomed in)", 
  xlab="Time per 1000 Cycles (seconds)", 
  horizontal = TRUE, 
  ylim=c(0.00017,0.00019)
)

# Zoomed in box plot Version 2 only
boxplot(
  Final$`Version 2`, 
  main="Version 2: Time to Complete 1000 Cycles of PCB Operations (Zoomed in)", 
  xlab="Time per 1000 Cycles (seconds)", 
  horizontal = TRUE, 
  ylim=c(0.000115,0.00013)
)