import cv2
import pytesseract

img = cv2.imread('prueba.jpeg')

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
_,thresh = cv2.threshold(
    gray, 150, 255,
    cv2.THRESH_BINARY
)

text1 = pytesseract.image_to_string(gray)
text2 = pytesseract.image_to_string(thresh)

print("Texto extraído de la imagen original con escala de grises:\n")
print(text1)
print("\n")
print("Texto extraído de la imagen umbralizada:\n")
print(text2)
