import cv2
 
#Cargamos nuestro modelo classificador de Haar:
modelo = cv2.CascadeClassifier('.\modelos\haarcascade_frontalface_alt.xml')
  
#Cargamos la imagen
img = cv2.imread('.\images\imagen_caras.jpg')
imagen = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
 
#Buscamos los rostros:
rostros = modelo.detectMultiScale(imagen, scaleFactor=1.1, minNeighbors=3)

#Ahora recorremos el array 'rostros' y dibujamos los rectángulos sobre la imagen original:
for (x,y,ancho, alto) in rostros:
    cv2.rectangle(img, (x,y), (x+ancho, y+alto), (0,0,255) , 3)
  
#Abrimos una ventana con el resultado:
cv2.imshow('Output', img)
print("\nMostrando resultado. Pulsa cualquier tecla para salir.\n")
cv2.waitKey(0)
cv2.destroyAllWindows()

