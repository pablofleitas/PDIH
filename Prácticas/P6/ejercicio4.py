import cv2

modeloCara = cv2.CascadeClassifier(r'.\modelos\haarcascade_frontalface_default.xml')

modeloCuerpo = cv2.CascadeClassifier(r'.\modelos\haarcascade_fullbody.xml')

camara = cv2.VideoCapture(r'.\videos\v4.mp4')

while camara.isOpened():

    _, img = camara.read()

    gris = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    caras = modeloCara.detectMultiScale(gris,1.1,6)

    cuerpos = modeloCuerpo.detectMultiScale(gris,1.1,3)

    for (x, y, w, h) in caras:
        cv2.rectangle(img,(x, y),(x+w, y+h),(255,0,0),3)

    for (x, y, w, h) in cuerpos:
        cv2.rectangle(img,(x, y),(x+w, y+h),(0,255,0),3)

    cv2.imshow("Deteccion", img)
    key = cv2.waitKey(1)
    if key == 27:
        break

camara.release()
cv2.destroyAllWindows()