import time
import pyautogui
import keyboard


def macro(d, m):
    time.sleep(float(d))

    pyautogui.typewrite(m)
    pyautogui.press('enter')


def main():
    # Get user input
    message = input('Type the desired message: ')

    mode = input('Set mode (loop / once): ')

    initdelay = input('Set initial delay (numeric value): ')

    delay = ''
    if mode == 'loop':
        delay = input('Set delay (numeric value): ')

    # Initial delay
    time.sleep(float(initdelay))

    # Perform macro
    if mode == 'once':
        macro(delay, message)
    elif mode == 'loop':
        global i
        i= 1
        while i == 1:
            if keyboard.is_pressed(' '):
                i = 0
            else:
                macro(delay, message)
    else:
        print('BURRO BURRO BURRO')


if __name__ == '__main__':
    main()
