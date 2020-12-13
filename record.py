import time
import json

import pygame


class Recorder:
    def start(self):
        self.ts = time.time()
        self.actions = {}

    def add_action(self, action):
        time_delta = time.time() - self.ts
        self.actions[time_delta] = action
        self.ts = time.time()

    def head(self):
        self.add_action("head")

    def tail(self):
        self.add_action("tail")

    def rest(self):
        self.add_action("rest")

    def mouthOpen(self):
        self.add_action("mouthOpen")

    def mouthClosed(self):
        self.add_action("mouthClosed")

    def write(self, filename):
        with open(filename, "w") as file:
            json.dump(self.actions, file)


pygame.init()
screen = pygame.display.set_mode((500, 500))
pygame.display.set_caption("Fishy Movement Recorder")

clock = pygame.time.Clock()

pygame.mixer.init()
pygame.mixer.music.load("track001.mp3")

rec = Recorder()

running = True
timestamp_start = 0

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == ord("q"):
                running = False
            elif event.key == ord(" "):
                pygame.mixer.music.play()
                rec.start()
            elif event.key == ord("a"):
                rec.head()
            elif event.key == ord("d"):
                rec.tail()
            elif event.key == ord("s"):
                rec.mouthOpen()
        elif event.type == pygame.KEYUP:
            if event.key == ord("a"):
                rec.rest()
            elif event.key == ord("d"):
                rec.rest()
            elif event.key == ord("s"):
                rec.mouthClosed()

    pygame.display.flip()
    clock.tick(60)

rec.write("recorded.json")

pygame.quit()
