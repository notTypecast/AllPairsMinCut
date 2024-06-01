from os import system
from glob import glob
import cv2
from PIL import Image
import numpy as np

def pad_image(image):
    if image.height > 1080:
        image.thumbnail((image.width, 1080), Image.ANTIALIAS)
    if image.width > 1920:
        image.thumbnail((1920, image.height), Image.ANTIALIAS)
    new_image = Image.new("RGB", (1920, 1080), (255, 255, 255))
    paste_position = ((1920 - image.width) // 2, (1080 - image.height) // 2)
    new_image.paste(image, paste_position)
    return new_image

def create_slideshow(delay):
    images = sorted(glob("vis/*.png"), key=lambda fn: int(fn[6:fn.index(".")]))

    fcc = cv2.VideoWriter_fourcc(*"XVID")
    fps = 30
    video = cv2.VideoWriter("vis/slideshow.avi", fcc, fps, (1920, 1080))

    frame_delay = int(fps * delay / 1000)
    
    for image in images:
        img = Image.open(image)
        img = pad_image(img)
        img = cv2.cvtColor(np.array(img), cv2.COLOR_RGB2BGR)
        for _ in range(frame_delay):
            video.write(img)

    video.release()

if __name__ == "__main__":
    for dot_file in glob("vis/*.dot"):
        system(f"dot -Tpng {dot_file} -o {dot_file.replace('.dot', '.png')}")

    create_slideshow(1000)
    system("xdg-open vis/slideshow.avi")