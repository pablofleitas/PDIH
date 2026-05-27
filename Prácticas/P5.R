install.packages("tuneR")
install.packages("seewave")

library(tuneR)
library(seewave)

#Ejercicio 1: Leer sonidos
nombre <- readWave("Nombre.wav")
apellido <- readWave("Apellido.wav")

#Ejercicio 2: Dibujar formas de onda
plot(nombre)
plot(apellido)

#Ejercicio 3: Mostrar Información
str(nombre)
str(apellido)

#Ejercicio 4: Unir los sonidos
completo <- pastew(apellido, nombre)
listen(completo, f = apellido@samp.rate)

#Ejercicio 5: Dibujar ondas sonido conjunto
plot(completo)

#Ejercicio 6: Guardar onda conjunta
writeWave(completo, "basico.wav")

#Ejercicio 7: Aplicar filtro de frecuencia
filtrado <- bwfilter(completo, f=completo@samp.rate,
                     n=2000, from=10000, to=20000,
                     bandpass=FALSE)
writeWave(filtrado, "filtrado.wav")

#Ejercicio 8: Aplicar eco y revertir
eco <- echo(completo, f=completo@samp.rate,
            delay=1, amp=c(0.8,0.3))
writeWave(eco, "eco.wav")

reves <- revw(eco)
writeWave(reves, "alreves.wav")