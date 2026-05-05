import cv2
import pytesseract

drawing = False
ix, iy = -1, -1
fx, fy = -1, -1

def draw_rectangle(event, x, y, flags, param):
    global ix, iy, fx, fy, drawing

    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        ix, iy = x, y

    elif event == cv2.EVENT_MOUSEMOVE:
        if drawing:
            fx, fy = x, y

    elif event == cv2.EVENT_LBUTTONUP:
        drawing = False
        fx, fy = x, y

cap = cv2.VideoCapture(0)
captured = None

while True:
    ret, frame = cap.read()
    
    if not ret:
        print("Error al capturar")
        break

    cv2.imshow("Camara", frame)

    key = cv2.waitKey(1)

   # Captura
    if key == ord('c'):
        captured = frame.copy()
        cloned = captured.copy()

        cv2.namedWindow("Seleccion")
        cv2.setMouseCallback("Seleccion", draw_rectangle)

        while True:
            temp = cloned.copy()

            if ix != -1 and iy != -1 and fx != -1 and fy != -1:
                cv2.rectangle(temp, (ix, iy), (fx, fy), (0,255,0), 2)

            cv2.imshow("Seleccion", temp)
            k = cv2.waitKey(1)

            # Enter → confirmar selección
            if k == 13:
                break
        
        crop = captured[min(iy, fy):max(iy, fy), min(ix, fx):max(ix, fx)]

        cv2.imshow("Recorte", crop)

        # OCR
        crop = cv2.resize(crop, None, fx=2, fy=2, interpolation=cv2.INTER_CUBIC)
        gray = cv2.cvtColor(crop, cv2.COLOR_BGR2GRAY)

        # mejora ligera de contraste (NO agresiva)
        gray = cv2.convertScaleAbs(gray, alpha=1.3, beta=10)

        cv2.imshow("Mejora", gray)

        text = pytesseract.image_to_string(gray, config='--psm 6')

        print("Texto reconocido:")
        print(text)

    # Pulsar 'q' para salir
    if key == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()