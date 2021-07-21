import cv2
import numpy as np


img = cv2.imread('D:/downloads/tr.PNG')


# Download the CRNN model and Load it
model = cv2.dnn.readNet('D:/downloads/crnn.onnx')


# ## Prepare the image
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

blob = cv2.dnn.blobFromImage(img_gray, scalefactor=1/127.5, size=(100,32), mean=127.5)


# Pass the image to network and extract per-timestep scores
model.setInput(blob)

scores = model.forward()
print(scores.shape)

alphabet_set = "0123456789abcdefghijklmnopqrstuvwxyz"
blank = '-'

char_set = blank + alphabet_set


# Decode the scores to text
def most_likely(scores, char_set):
    text = ""
    for i in range(scores.shape[0]):
        c = np.argmax(scores[i][0])
        text += char_set[c]
    return text


def map_rule(text):
    char_list = []
    for i in range(len(text)):
        if i == 0:
            if text[i] != '-':
                char_list.append(text[i])
        else:
            if text[i] != '-' and (not (text[i] == text[i - 1])):
                char_list.append(text[i])
    return ''.join(char_list)


def best_path(scores, char_set):
    text = most_likely(scores, char_set)
    final_text = map_rule(text)
    return final_text


out = best_path(scores, char_set)
print(out)




