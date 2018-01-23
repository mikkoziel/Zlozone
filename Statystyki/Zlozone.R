setwd("C:/Users/Windows 8.1/Desktop/Studia/Semestr 5/Zlo¿one SC/1Ostateczna wersja projektu/Statystyki")
setwd("C:/Users/Windows 8.1/Desktop/Studia/Semestr 5/Zlo¿one SC/1Ostateczna wersja projektu")

getwd()
library("ggplot2")
library("readr")

result = read.csv("text3.csv")

ggplot() +
  ggtitle("Wyniki") +
  geom_line(data=result, aes(x=y, y=aH, color='aH')) +
  geom_line(data=result, aes(x=y, y=aT, color='aT')) +
  geom_line(data=result, aes(x=y, y=sH, color='sH')) +
  scale_colour_manual(name = 'Metoda', values =c('aH'='orange', 'aT'='purple', 'sH'='green'))

ggplot() +
  ggtitle("Wyniki") +
  geom_point(data=result, aes(x=y, y=aH, color='aH')) +
  geom_point(data=result, aes(x=y, y=aT, color='aT')) +
  geom_point(data=result, aes(x=y, y=sH, color='sH')) +
  scale_colour_manual(name = 'Metoda', values =c('aH'='orange', 'aT'='purple', 'sH'='green'))


ggplot() +
  ggtitle("Wyniki") +
  geom_line(data=result, aes(x=y, y=aH, color='aH')) +
  geom_line(data=result, aes(x=y, y=aT, color='aT')) +
  geom_line(data=result, aes(x=y, y=sH, color='sH')) +
  geom_point(data=result, aes(x=y, y=aH, color='aH')) +
  geom_point(data=result, aes(x=y, y=aT, color='aT')) +
  geom_point(data=result, aes(x=y, y=sH, color='sH')) +
  scale_colour_manual(name = 'Metoda', values =c('aH'='orange', 'aT'='purple', 'sH'='green'))

ggplot() +
  ggtitle("aH") +
  geom_point(data=result, aes(x=y, y=aH, color='aH')) +
  geom_line(data=result, aes(x=y, y=aH, color='aH')) 

ggplot() +
  ggtitle("aT") +
  geom_point(data=result, aes(x=y, y=aT, color='aT')) +
  geom_line(data=result, aes(x=y, y=aT, color='aT')) 

ggplot() +
  ggtitle("sH") +
  geom_point(data=result, aes(x=y, y=sH, color='sH')) +
  geom_line(data=result, aes(x=y, y=sH, color='sH'))
