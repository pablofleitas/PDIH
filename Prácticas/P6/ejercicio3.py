import cv2
 
modelo = cv2.CascadeClassifier('.\modelos\haarcascade_frontalcatface_extended.xml') 
 
img = cv2.imread('.\images\imagen_gatos.jpg')
imagen = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

gatos = modelo.detectMultiScale(imagen, scaleFactor=1.1, minNeighbors=6 )

for (x,y,ancho, alto) in gatos:
    cv2.rectangle(img, (x,y), (x+ancho, y+alto), (0,0,255) , 3)
  
cv2.imshow('Output', img)
print("\nMostrando resultado. Pulsa cualquier tecla para salir.\n")
cv2.waitKey(0)
cv2.destroyAllWindows()

