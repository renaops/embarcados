# Importing Libraries
import serial
import time
import pygame
import random

NUMBER_COD = "N"
COLOR_COD = "C"
POINTS = 0

pygame.init()

game_over = pygame.mixer.Sound("game-over.wav")

arduino = serial.Serial(port='COM7', baudrate=9600, timeout=.1)

COLORS = ["blue", "yellow", "red", "green"]
COLORS_SOUNDS = [
    pygame.mixer.Sound("dog.wav"),
    pygame.mixer.Sound("cat.wav"),
    pygame.mixer.Sound("goat.wav"),
    pygame.mixer.Sound("pig.wav"),
]

CURRENT_COLORS = []

def get_next_color():
    return random.randint(0, 3)

def write_number(number):
    arduino.write(bytes(number, 'utf-8'))
    time.sleep(0.01)
    data = arduino.readline()
    return data


def write_read(x):
    arduino.write(bytes(f"{x}", 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data


print("Começando jogo!\n")
flag = True
while True:
    time.sleep(1.5)

    if (flag):
        value = write_read(0)
        flag = False
        continue

    print("Começando Nova Rodada!\n")
    color = get_next_color()
    CURRENT_COLORS.append(color)

    for c in CURRENT_COLORS:
        value = write_read(c)
        if len(value) > 0:

            print(COLORS[c])
            COLORS_SOUNDS[c].play()

        time.sleep(1.5)

    print("AZUL = 0, AMARELHO = 1, VERMELHO = 2, VERDE = 3")
    print("Responda a sequencia separando os valores com uma virgula. eg? 1,3,0")
    seq = input("Qual a sequencia? ")

    answer = seq.split(",")
    answer_list = [int(num) for num in answer]
    
    if (answer_list != CURRENT_COLORS):
        game_over.play()
        print("GAME OVER")
        print(f"Voce fez {POINTS} pontos!")
        play_again = input("Jogar novamente?? (s, n)")
        if (play_again == "S" or play_again == "s"):
            continue
        else:
            print("Muito obrigado por jogar!")
            break
    else:
        print("Parabens! Você acertou!")
        POINTS = POINTS + len(CURRENT_COLORS) * 2
        print(f"Você tem um total de {POINTS} pontos")
