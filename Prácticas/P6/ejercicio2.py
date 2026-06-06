import cv2

ruta1 = r'.\modelos\haarcascade_frontalface_default.xml'
ruta2 = r'.\videos\v2.mp4'
# Cargamos el modelo clasificador para la cara
modeloCara = cv2.CascadeClassifier(ruta1)

#Cargamos un vídeo:
camara = cv2.VideoCapture(ruta2)

while camara.isOpened():
    # Cargamos en img lo capturado por la cámara
    _, img = camara.read()

    color = cv2.cvtColor(img, cv2.COLOR_BGR2BGRA)

    # Detectamos la cara
    faces = modeloCara.detectMultiScale(color, 1.1, 4)

    # Pintamos el rectángulo sobre la cara
    for (x, y , w ,h) in faces:
        cv2.rectangle(img, (x,y), (x+w, y+h), (255, 0 , 0), 3)

    # Lo mostramos en pantalla mientras no pulsemos la tecla 'esc'
    cv2.imshow('img', img)
    key = cv2.waitKey(1)
    if key == 27:
        break

camara.release()
cv2.destroyAllWindows()
